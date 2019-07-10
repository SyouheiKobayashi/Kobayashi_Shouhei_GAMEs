//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//							タイトル処理 [title.h]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "timeCharge.h"
#include "fade.h"
#include "debugLog.h"
#include "sound.h"
#include "light.h"
#include "camera.h"
#include "scene2D.h"
#include "polygon2D.h"
#include "scene3D.h"
#include "meshField.h"
//#include "billboard.h"
#include "polygon3D.h"
#include "particle.h"
#include "number.h"
#include "time.h"
#include "object.h"
#include "player.h"

//=====================================================================
//							静的メンバ変数
//=====================================================================
CDebug *CTimeCharge::m_pDebug = NULL;
CSound *CTimeCharge::m_pSound = NULL;
CLight *CTimeCharge::m_pLight = NULL;
CCamera *CTimeCharge::m_pCamera = NULL;
CScene2D *CTimeCharge::m_pScene2D = NULL;
CPolygon2D *CTimeCharge::m_pPolygon2D[POLYGON2D_TEX_TC] = {};
CScene3D *CTimeCharge::m_pScene3D = NULL;
CMeshField *CTimeCharge::m_pMeshField = NULL;
//CBillboard *CTimeCharge::m_pBillboard = NULL;
CPolygon3D *CTimeCharge::m_pPolygon3D = NULL;
CParticle3D *CTimeCharge::m_pParticle3D = NULL;
CNumber *CTimeCharge::m_pNumber = NULL;
CTime *CTimeCharge::m_pTime = NULL;
CObject *CTimeCharge::m_pObject = NULL;
CPlayer *CTimeCharge::m_pPlayer = NULL;

//==============================================
//					コンストラクタ
//==============================================
CTimeCharge::CTimeCharge()
{

}

//==============================================
//					デストラクタ
//==============================================
CTimeCharge::~CTimeCharge()
{

}

//==============================================
//						生成
//==============================================
CTimeCharge *CTimeCharge::Create()
{
	CTimeCharge *pTitle = NULL;

	if (pTitle == NULL)
	{
		pTitle = new CTimeCharge;
		pTitle->Init();
	}

	return pTitle;
}
//==============================================
//					初期化
//==============================================
HRESULT CTimeCharge::Init(void)
{
	m_nDebugCnt = 0;
	
	NullCheck();				//使用するデータを一度NULLにする
	BulkLoadData();				//使用したモデルとテクスチャの解放
	CreateData();				//読み込んだ情報をもとにobjの生成
	m_nCntTime = 0;
	m_bRotationSwitch = false;
	m_fRotation = 0;
	m_nChargeTime = 0;
	m_nCntChargeTime = 0;
	m_bFlag = false;
	m_bStartFlag = false;
	m_nStartCnt = 0;
	m_ChargeStart = false;
	m_pCamera->SetV(D3DXVECTOR3(-150.0f, 0.0f, -40.0f));//注視点からの距離
	m_pCamera->SetR(D3DXVECTOR3(-150.0f, 0.0f, 0.0f));//注視点の位置
	m_pSound = CManager::GetSound();
	if (m_pSound != NULL)
	{
		//m_pSound->PlaySound(CSound::BGM_SOUND_TITLE);
	}

	return S_OK;
}
//==============================================
//						終了
//==============================================
void CTimeCharge::Uninit(void)
{
	if (m_pSound != NULL)
	{
		m_pSound->StopSound();
	}
	BulkUnLoadData();			//使用したモデルとテクスチャの解放

	if (m_pTime != NULL)
	{
		m_pTime = NULL;			//タイム
	}

	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();	//カメラ
	}
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();		//ライト
	}
	if (m_pDebug != NULL)
	{
		m_pDebug->Uninit();		//デバック
	}

	//使用したデータ・メモリをすべて開放
	CScene::ReleaseAll();
}
//==============================================
//					更新
//==============================================
void CTimeCharge::Update(void)
{
	//キーボード・コントローラーの取得処理
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	
	m_pFade = CFade::GetFade();	//フェード

	if (m_pLight != NULL)
	{
		m_pLight->Update();		//ライト
	}
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();	//カメラ
	}

	Event();//一連の流れ(まとめ)
	
#ifdef _DEBUG
	Debug();
	//DebugLoop();
#endif
}

//==============================================
//					描画
//==============================================
void CTimeCharge::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();//カメラ描画
	}

}

//==============================================
//				イベント(一連の流れ)
//==============================================
void CTimeCharge::Event(void)
{
	//説明→消す→カウント→終了文字の生成→ゲームスタート

	if (m_pPolygon2D[3] != NULL)
	{
		if (m_pInputKeyboard->GetTrigger(DIK_SPACE) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
		{//説明
			m_bStartFlag = true;
			if (m_pPolygon2D[3] != NULL)
			{
				m_pPolygon2D[3]->Uninit();
				m_pPolygon2D[3] = NULL;
			}
		}
	}
	if (m_bStartFlag == true)
	{//時間生成
		m_nStartCnt++;
		if (m_pPolygon2D[4] == NULL)
		{
			m_pPolygon2D[4] = CPolygon2D::Create(14, false, D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200.0f, 200.0f, 50, 2, 2, false);

		}

		if (m_nStartCnt == 1 || m_nStartCnt == 50 || m_nStartCnt == 100)
		{
			if (m_pSound != NULL)
			{
				m_pSound->PlaySound(CSound::SE_COUNT);//カウント音
			}
		}
		if (m_nStartCnt >= 150)//アニメの速さ*合計コマ割り数 = 消える時間
		{
			m_bStartFlag = false;
			m_ChargeStart = true;
			if (m_pPolygon2D[4] != NULL)
			{
				m_pPolygon2D[4] = NULL;
			}
		}
	}
	if (m_ChargeStart == true)
	{
		if (m_pPolygon2D[0] == NULL&&m_pPolygon2D[1] == NULL)
		{//連打文字生成
			m_pPolygon2D[0] = CPolygon2D::Create(6, false, D3DXVECTOR3(650.0f, 150.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130.0f, 50.0f, 1, 1, 1, true);
		}

		//モデルの回転
		m_nCntChargeTime++;//チャージ可能時間
		if (m_nCntChargeTime <= 200)
		{
			if (m_pInputKeyboard->GetTrigger(DIK_SPACE) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
			{
				if (m_pSound != NULL)
				{
					m_pSound->PlaySound(CSound::SE_CHARGE);//チャージ音
				}
				m_bRotationSwitch = true;
				m_nChargeTime += 7;
				//回転と同時にエフェクトアニメーションを生成
				CPolygon3D::Create(0, D3DXVECTOR3(-75.0f, 5.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f), 2, 4, 3, false);
			}
			if (m_bRotationSwitch == true)
			{
				m_nCntTime++;
				m_fRotation += 0.1f;
				m_pObject->SetRot(D3DXVECTOR3(0.0f, m_fRotation, 0.0f));
				if (m_nCntTime >= 25)
				{
					m_bRotationSwitch = false;//回転を止める
					m_nCntTime = 0;//再度回せるように初期地に戻す
				}
			}
		}
		else
		{
			if (m_pPolygon2D[0] != NULL)
			{
				m_pPolygon2D[0]->Uninit();//[連打!]アイコンを消す
				m_pPolygon2D[0] = NULL;
			}

		}
		if (m_nCntChargeTime >= 210)
		{
			m_bFlag = true;//終了フラグを立てる
			if (m_pPolygon2D[1] == NULL)
			{//[終了!]アイコンを生成
				if (m_pSound != NULL)
				{
					m_pSound->PlaySound(CSound::SE_TIMEUP);//終了音
				}
				m_pPolygon2D[1] = CPolygon2D::Create(7, false, D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200.0f, 120.0f, 1, 1, 1, true);
				m_pPolygon2D[2] = CPolygon2D::Create(8, false, D3DXVECTOR3(1050.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 190.0f, 45.0f, 1, 1, 1, true);

			}
			if (m_pInputKeyboard->GetTrigger(DIK_RETURN) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_START, 0) == true)
			{
				if (m_pFade == CFade::FADE_NONE)
				{
					if (m_pSound != NULL)
					{
						m_pSound->PlaySound(CSound::SE_BUTTON);
					}
					CManager::GetFade()->SetFade(CManager::MODE_GAME);
				}
			}
		}
	}
}

//==============================================
//				NULLチェック
//==============================================
void CTimeCharge::NullCheck(void)
{
	if (m_pDebug != NULL)
	{
		m_pDebug = NULL;		//デバック
	}
	if (m_pLight != NULL)
	{
		m_pLight = NULL;		//ライト
	}
	if (m_pCamera != NULL)
	{
		m_pCamera = NULL;		//カメラ
	}

	if (m_pScene2D != NULL)
	{
		m_pScene2D = NULL;		//シーン2D
	}

	for (int nCnt = 0; nCnt < POLYGON2D_TEX_TC; nCnt++)
	{
		if (m_pPolygon2D[nCnt] != NULL)
		{
			m_pPolygon2D[nCnt] = NULL;	//ポリゴン2D
		}
	}

	if (m_pPolygon3D != NULL)
	{
		m_pPolygon3D = NULL;	//ポリゴン3D
	}

	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;		//プレイヤー
	}
}

//==============================================
//				　Load処理(読み込み)
//==============================================
void CTimeCharge::BulkLoadData(void)
{
	CPolygon2D::TextureLoad();
	CPolygon3D::TextureLoad();
	CParticle3D::TextureLoad();
	CNumber::TextureLoad();
	CObject::ObjectLoad();
	CObject::TextureLoad();
	CPlayer::ModelLoad();
	CPlayer::TextureLoad();

}

//==============================================
//				　UnLoad処理(解放)
//==============================================
void CTimeCharge::BulkUnLoadData(void)
{
	CPlayer::TextureUnLoad();
	CPlayer::ModelUnLoad();
	CObject::TextureUnLoad();
	CObject::ObjectUnLoad();
	CNumber::TextureUnLoad();
	CParticle3D::TextureUnLoad();
	CPolygon3D::TextureUnLoad();
	CPolygon2D::TextureUnLoad();
}

//==============================================
//					生成処理
//==============================================
void CTimeCharge::CreateData(void)
{
	if (m_pDebug == NULL)//デバック
	{
		m_pDebug = CDebug::Create();
	}
	if (m_pLight == NULL)//ライト
	{
		m_pLight = CLight::Create();
	}
	if (m_pCamera == NULL)//カメラ
	{
		m_pCamera = CCamera::Create();
	}

	if (m_pScene2D == NULL)//シーン2D
	{
		m_pScene2D = CScene2D::Create();
	}

	if (m_pTime == NULL)//タイム
	{						//マネージャが時間を管理している
		m_pTime = CTime::Create(10, D3DXVECTOR2(55.0f, 55.0f), D3DXVECTOR2(120.0f, 610.0f));
	}

	if (m_pPolygon2D[0] == NULL)//2Dテクスチャ
	{
		CPolygon2D::Create(9, false, D3DXVECTOR3(640.0f, 25.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 640.0f, 25.0f, 1, 1, 1, true);
		CPolygon2D::Create(10, false, D3DXVECTOR3(640.0f, 695.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 640.0f, 25.0f, 1, 1, 1, true);
		m_pPolygon2D[3] = CPolygon2D::Create(15, false, D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 400.0f, 300.0f, 1, 1, 1, true);
	}

	//オブジェクト
	m_pObject = CObject::Create(0, 0, D3DXVECTOR3(-150.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	
}

//==============================================
//				デバック用処理
//==============================================
void  CTimeCharge::Debug(void)
{
	CDebug::DebugLog("\nいくらChargeされたか %d", m_nChargeTime);

	//エンタキーで再度ゲームの開始
	if (m_pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		if (m_pFade == CFade::FADE_NONE)
		{
			CManager::GetFade()->SetFade(CManager::MODE_GAME);
		}
	}
	CDebug::DebugLog("\nNULLか %d", m_pPolygon2D[4]);
	
}
void  CTimeCharge::DebugLoop(void)
{
	m_nDebugCnt++;
	if (m_nDebugCnt >= 50)
	{
		if (m_pFade == CFade::FADE_NONE)
		{
			CManager::GetFade()->SetFade(CManager::MODE_GAME);
		}
	}
}
