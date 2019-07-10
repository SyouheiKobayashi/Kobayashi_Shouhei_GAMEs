//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//カメラ処理 [camera.cpp]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "camera.h"
#include "manager.h"
#include "debugLog.h"
#include "input.h"
#include "game.h"

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
	//m_cameraMode = MODE_XYZ;
	m_nCameraMode = 1;
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
	//キーボード・コントローラーの取得処理
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	m_pInputMouse = CManager::GetInputMouse();
	m_pGame = CManager::GetGame();

	if (m_pGame != NULL)
	{
		if (m_pGame->GetInputMode() == 0)//入力モード(キーボード)
		{
			MOVE();//カメラの移動 / 拡大 / 初期化
			//PointViewRot();//注視点を軸に視点の回転
			//NoteViewRot(); //視点の回転
		}
	}

	if (m_pGame != NULL)
	{
		if (m_pGame->GetInputMode() == 1)//入力モード(キーボード)
		{
			MOVE02();//カメラの移動 / 拡大 / 初期化
		}
	}

	if (m_pInputKeyboard->GetTrigger(DIK_F1) == true)
	{
		m_nCameraMode += 1;
		if (m_nCameraMode >= MODE_MAX)
		{
			m_nCameraMode = MODE_XYZ;//最初の状態に戻す
		}

		if (m_nCameraMode == MODE_XYZ)
		{
			m_posV.y = 50.0f;
		}
		if (m_nCameraMode == MODE_XZ)
		{
			m_posV.y = 300.0f;
		}
	}
	

	
	//CDebug::DebugLog("VXXX %.1f", m_posV.x);
	CDebug::DebugLog("\nVZZZ %.1f,%.1f,%.1f", m_posV.x, m_posV.y,m_posV.z);
	CDebug::DebugLog("\nRZZZ %.1f,%.1f,%.1f", m_posR.x, m_posR.y,m_posR.z);

}

//==============================================
//移動 / 拡大・縮小 / 初期化
//==============================================
void CCamera::MOVE(void)
{

	//上下左右
	if (m_pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{
		m_posV.x += 4.0f;
		m_posR.x += 4.0f;
	}

	if (m_pInputKeyboard->GetPress(DIK_LEFT) == true)
	{
		m_posV.x -= 4.0f;
		m_posR.x -= 4.0f;
	}

	if (m_pInputKeyboard->GetPress(DIK_UP) == true)
	{
		m_posV.y += 4.0f;
		m_posR.y += 4.0f;
	}
	if (m_pInputKeyboard->GetPress(DIK_DOWN) == true)
	{
		m_posV.y -= 4.0f;
		m_posR.y -= 4.0f;
	}
	//カメラ位置の初期化
	if (m_pInputKeyboard->GetPress(DIK_0) == true)
	{
		if (m_nCameraMode == MODE_XYZ)
		{
			m_posV = D3DXVECTOR3(0.0f, 50.0f, -400.0f);
		}
		if (m_nCameraMode == MODE_XZ)
		{
			m_posV = D3DXVECTOR3(0.0f, 300.0f, -400.0f);
		}
		
		m_posR = CAMERA_R;
		m_fRotation = 0.0f;
	}
}

void CCamera::MOVE02(void)
{
	//マウスの横移動を感知、カメラ(注視点)の回転
	if (m_pInputMouse->GetPress(1) == true)
	{
		if (m_pInputMouse->GetWheel().lX < 0)
		{
			m_fRotation -= 0.03f;
			if (m_fRotation > D3DX_PI)
			{
				m_fRotation = -D3DX_PI;
			}
			m_posR.x = m_posV.x + sinf(m_fRotation) * CAMERA_INIT_V;
			m_posR.z = m_posV.z + cosf(m_fRotation) * CAMERA_INIT_V;
		}
		if (m_pInputMouse->GetWheel().lX > 0)
		{
			m_fRotation += 0.03f;
			if (m_fRotation > D3DX_PI)
			{
				m_fRotation = -D3DX_PI;
			}
			m_posR.x = m_posV.x + sinf(m_fRotation) * CAMERA_INIT_V;
			m_posR.z = m_posV.z + cosf(m_fRotation) * CAMERA_INIT_V;
		}
	}

	//上下左右
	if (m_pInputKeyboard->GetPress(DIK_D) == true)
	{
		m_posV.x += 4.0f;
		m_posR.x += 4.0f;
	}

	if (m_pInputKeyboard->GetPress(DIK_A) == true)
	{
		m_posV.x -= 4.0f;
		m_posR.x -= 4.0f;
	}

	if (m_pInputKeyboard->GetPress(DIK_E) == true)
	{
		m_posV.y += 4.0f;
		m_posR.y += 4.0f;
	}
	if (m_pInputKeyboard->GetPress(DIK_Q) == true)
	{
		m_posV.y -= 4.0f;
		m_posR.y -= 4.0f;
	}
	//前進・後退
	if (m_pInputKeyboard->GetPress(DIK_W) == true)
	{
		m_posV.z += 4.0f;
		m_posR.z += 4.0f;
	}
	if (m_pInputKeyboard->GetPress(DIK_S) == true)
	{
		m_posV.z -= 4.0f;
		m_posR.z -= 4.0f;
	}
	//カメラ位置の初期化
	if (m_pInputKeyboard->GetPress(DIK_X) == true)
	{
		m_posV = CAMERA_V;
		m_posR = CAMERA_R;
		m_fRotation = 0.0f;
	}

	CDebug::DebugLog("\nマウスaaa %.f", m_pInputMouse->GetWheel().lX);

}

//==============================================
//注視点を軸に視点の回転
//==============================================
void CCamera::PointViewRot(void)
{
	if ((m_pInputKeyboard->GetPress(DIK_UP) == true))//回転
	{

		m_fRotation += 0.02f;
		if (m_fRotation > D3DX_PI)
		{
			m_fRotation = -D3DX_PI;
		}
		m_posV.x = m_posR.x - sinf(m_fRotation) * CAMERA_INIT_V;
		m_posV.z = m_posR.z - cosf(m_fRotation) * CAMERA_INIT_V;
	}
	if ((m_pInputKeyboard->GetPress(DIK_DOWN) == true))//回転
	{

		m_fRotation -= 0.02f;
		if (m_fRotation > D3DX_PI)
		{
			m_fRotation = -D3DX_PI;
		}
		m_posV.x = m_posR.x - sinf(m_fRotation) * CAMERA_INIT_V;
		m_posV.z = m_posR.z - cosf(m_fRotation) * CAMERA_INIT_V;
	}
}

//==============================================
//視点の回転
//==============================================
void CCamera::NoteViewRot(void)
{
	if ((m_pInputKeyboard->GetPress(DIK_LEFT) == true))//回転
	{
		m_fRotation -= 0.03f;
		if (m_fRotation > D3DX_PI)
		{
			m_fRotation = -D3DX_PI;
		}
		m_posR.x = m_posV.x + sinf(m_fRotation) * CAMERA_INIT_V;
		m_posR.z = m_posV.z + cosf(m_fRotation) * CAMERA_INIT_V;

	}

	if ((m_pInputKeyboard->GetPress(DIK_RIGHT) == true))//回転
	{
		m_fRotation += 0.03f;
		if (m_fRotation > D3DX_PI)
		{
			m_fRotation = -D3DX_PI;
		}
		m_posR.x = m_posV.x + sinf(m_fRotation) * CAMERA_INIT_V;
		m_posR.z = m_posV.z + cosf(m_fRotation) * CAMERA_INIT_V;

	}

}

//==============================================
//カメラの設定
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