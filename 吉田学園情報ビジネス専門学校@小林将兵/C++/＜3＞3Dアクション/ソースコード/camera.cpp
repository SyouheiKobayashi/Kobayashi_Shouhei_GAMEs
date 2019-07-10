//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//カメラ処理 [camera.cpp]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "camera.h"
#include "manager.h"
#include "debugLog.h"
#include "input.h"
#include "game.h"
#include "player.h"

//==============================================
//コンストラクタ
//==============================================
CCamera::CCamera()
{
	
}

//==============================================
//デストラクタ
//==============================================
CCamera::~CCamera()
{
}

//==============================================
//生成
//==============================================
CCamera *CCamera::Create(void)
{
	CCamera *pCamera = NULL;

	if (pCamera == NULL)
	{
		pCamera = new CCamera;
		pCamera->Init();

	}
	return pCamera;
}
//==============================================
//初期化
//==============================================
void CCamera::Init(void)
{
	m_posV = CAMERA_V;//視点
	m_posR = CAMERA_R;//注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0, 0, 0);//(目的の)視点
	m_posRDest = D3DXVECTOR3(0, 0, 0);//(目的の)注視点
	D3DXVECTOR3 rot = D3DXVECTOR3(0, 0, 0);//(現在の)向き
	D3DXVECTOR3 rotDest = D3DXVECTOR3(0, 0, 0);//(目的の)向き
	m_Radian = CAMERA_WIDTH;
	m_fRotation = 0;
	m_fCameraPosZ = 220.0f;
}

//==============================================
//終了
//==============================================
void CCamera::Uninit(void)
{
	delete this;
}
//==============================================
//更新
//==============================================
void CCamera::Update(void)
{
	if (CManager::GetMode() == CManager::MODE_GAME)//ゲームのみプレイヤーの追跡
	{
		CPlayer *pPlayer = CGame::GetPlayer();
		if (pPlayer != NULL)
		{

			if (pPlayer->GetOutStage() == false)//ステージ外にでたら更新を中断する
			{
				CameraView();
			}
		}
	}
	m_pInputKeyboard = CManager::GetInputKeyboard();
	//DebugCameraMove();//カメラ移動
}

//==============================================
//					カメラの設定
//==============================================
void CCamera::SetCamera(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(m_Radian),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	////潰したような描画表現
	/*D3DXMatrixOrthoLH(&m_mtxProjection,
		(float)SCREEN_WIDTH,
		(float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);*/

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxViex);

	//ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_mtxViex,
		&m_posV,
		&m_posR,
		&m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxViex);
}

//==============================================
//				カメラの見方
//==============================================
void CCamera::CameraView()
{
	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer != NULL)
	{
		if (pPlayer->GetPos().z >= 220.0f)
		{
			m_fCameraPosZ = 145.0f;
		}
		else
		{
			m_fCameraPosZ = 220.0f;
		}
		m_posRDest.x = pPlayer->GetPos().x - sinf(pPlayer->GetRot().y);
		m_posRDest.y = pPlayer->GetPos().y;
		m_posRDest.z = pPlayer->GetPos().z - cosf(pPlayer->GetRot().y);

		m_posVDest.x = m_posRDest.x - sinf(m_rot.y);
		m_posVDest.y = m_posRDest.y;
		m_posVDest.z = m_posRDest.z - cosf(m_rot.y);

		m_posR.x += (m_posRDest.x - m_posR.x + 100.0f)*0.09f;
		m_posR.y += (m_posRDest.y - m_posR.y + 50.0f)*0.05f;
		m_posR.z += (m_posRDest.z - m_posR.z)*0.09f;

		m_posV.x += (m_posVDest.x - m_posV.x + 50.0f)*0.09f;
		m_posV.y += (m_posVDest.y - m_posV.y + 60.0f)*0.05f;
		m_posV.z += (m_posVDest.z - m_posV.z - m_fCameraPosZ)*0.09f;

		m_posR.x = m_posV.x + sinf(D3DX_PI) * 200.0f;//値の調整で少し斜めにする
		m_posR.z = m_posV.z + cosf(m_fRotation) * 200.0f;
	}
}
//==============================================
//				カメラのキー移動
//==============================================
void CCamera::DebugCameraMove()
{
	if (m_pInputKeyboard->GetPress(DIK_NUMPAD6) == true)
	{
		m_posV.x += 4.0f;
		m_posR.x += 4.0f;
	}

	if (m_pInputKeyboard->GetPress(DIK_NUMPAD4) == true)
	{
		m_posV.x -= 4.0f;
		m_posR.x -= 4.0f;
	}

	if (m_pInputKeyboard->GetPress(DIK_NUMPAD7) == true)
	{
		m_posV.y += 4.0f;
		m_posR.y += 4.0f;
	}
	if (m_pInputKeyboard->GetPress(DIK_NUMPAD9) == true)
	{
		m_posV.y -= 4.0f;
		m_posR.y -= 4.0f;
	}

	if (m_pInputKeyboard->GetPress(DIK_NUMPAD8) == true)
	{
		m_posV.z += 4.0f;
		m_posR.z += 4.0f;
	}
	if (m_pInputKeyboard->GetPress(DIK_NUMPAD2) == true)
	{
		m_posV.z -= 4.0f;
		m_posR.z -= 4.0f;
	}
	//初期化
	if (m_pInputKeyboard->GetPress(DIK_NUMPAD5) == true)
	{
		m_posV = CAMERA_V;
		m_posR = CAMERA_R;
	}
}

void CCamera::SetV(D3DXVECTOR3 posV)
{
	m_posV = posV;
}
void CCamera::SetR(D3DXVECTOR3 posR)
{
	m_posR = posR;
}
