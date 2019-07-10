//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//ゲーム処理 [game.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "game.h"
#include "fade.h"
#include "debugLog.h"
#include "light.h"
#include "camera.h"
#include "scene2D.h"
#include "tutorial2DTex.h"
#include "scene3D.h"
#include "meshField.h"
#include "sceneX.h"
#include "object.h"
#include "player.h"

//=====================================================================
//静的メンバ変数
//=====================================================================
CDebug *CGame::m_pDebug = NULL;
CLight *CGame::m_pLight = NULL;
CCamera *CGame::m_pCamera = NULL;
CScene2D *CGame::m_pScene2D = NULL;
CScene3D *CGame::m_pScene3D = NULL;
CMeshField *CGame::m_pMeshField = NULL;
CSceneX *CGame::m_pSceneX = NULL;
CObject *CGame::m_pObject[OBJ_CREATE] = {};
CPlayer *CGame::m_pPlayer = NULL;

//==============================================
//コンストラクタ
//==============================================
CGame::CGame()
{
	m_nCreateCnt = 0;
}

//==============================================
//デストラクタ
//==============================================
CGame::~CGame()
{

}

//==============================================
//生成
//==============================================
CGame *CGame::Create()
{
	CGame *pGame = NULL;

	if (pGame == NULL)
	{
		pGame = new CGame;
		pGame->Init();
	}

	return pGame;
}
//==============================================
//初期化
//==============================================
HRESULT CGame::Init(void)
{
	m_nCreateCnt = 0;
	m_nInputMode = 0;
	NullCheck();		//使用するデータを一度NULLにする
	CTutorial2DTex::TextureLoad();
	CObject::ObjectLoad();
	CObject::TextureLoad();
	CPlayer::ModelLoad();
	CPlayer::TextureLoad();
	CreateData();		//必要・使用objの生成

	return S_OK;
}
//==============================================
//終了
//==============================================
void CGame::Uninit(void)
{
	CPlayer::TextureLoad();
	CPlayer::ModelUnLoad();
	CObject::TextureUnLoad();
	CObject::ObjectUnLoad();
	CTutorial2DTex::TextureUnLoad();


	if (m_pCamera != NULL)//カメラ
	{
		m_pCamera->Uninit();	
	}
	if (m_pLight != NULL)//ライト
	{
		m_pLight->Uninit();		
	}
	if (m_pDebug != NULL)//デバック
	{
		m_pDebug->Uninit();		
	}

	//使用したデータ・メモリをすべて開放
	CScene::ReleaseAll();
}
//==============================================
//更新
//==============================================
void CGame::Update(void)
{
	//キーボード・コントローラーの取得処理
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	m_pInputMouse = CManager::GetInputMouse();

	//画面遷移処理
	m_pFade = CFade::GetFade();
	//
	if (m_pLight != NULL)//ライト
	{
		m_pLight->Update();		
	}
	if (m_pCamera != NULL)//カメラ
	{
		m_pCamera->Update();	
	}

	ObjCreate();//ボタン押下によるobjの『生成』

	ObjDelete();//ボタン押下によるobjの『削除』

	Save();		//ボタン押下によるobj情報の『保存』

	if (m_pInputKeyboard->GetTrigger(DIK_F2) == true)
	{
		m_nInputMode += 1;
		if (m_nInputMode >= 2)
		{
			m_nInputMode = 0;
		}
	}

	/*switch (m_nInputMode)
	{
	case 0:

	case 1:

	case 2:
	}*/

	Debug();	//デバック操作用
}

//==============================================
//描画
//==============================================
void CGame::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();//画面の描画に必要
	}

}
//==============================================
//初期化時にNULLする
//==============================================
void CGame::NullCheck(void)
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
		m_pScene2D = NULL;	//シーン2D
	}

	if (m_pScene3D != NULL)
	{
		m_pScene3D = NULL;	//シーン3D
	}

	if (m_pMeshField != NULL)
	{
		m_pMeshField = NULL;//メッシュフィールド
	}


	//if (m_pSceneX != NULL)
	//{
	//	m_pSceneX = NULL;	//シーンX
	//}

	for (int nCnt = 0; nCnt < OBJ_CREATE; nCnt++)
	{
		if (m_pObject[nCnt] != NULL)
		{
			m_pObject[nCnt] = NULL;	//オブジェクト
		}
	}
	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;	//プレイヤー
	}
}
//==============================================
//使用する素材の生成
//==============================================
void CGame::CreateData(void)
{
	if (m_pDebug == NULL)
	{
		m_pDebug = CDebug::Create();		//デバック
	}
	if (m_pLight == NULL)
	{
		m_pLight = CLight::Create();		//ライト
	}
	if (m_pCamera == NULL)
	{
		m_pCamera = CCamera::Create();		//カメラ
	}

	//if (m_pScene2D == NULL)
	//{
	//	m_pScene2D = CScene2D::Create();	//シーン2D
	//}

	//CTutorial2DTex::Create(0, D3DXVECTOR3(900.0f,50.0f,0.0f),500.0f,50.0f);
	//CTutorial2DTex::Create(1, D3DXVECTOR3(130.0f, 400.0f, 0.0f), 90.0f, 55.0f);

	if (m_pScene3D == NULL)
	{
		//m_pScene3D = CScene3D::Create();	//シーン3D
	}

	if (m_pMeshField == NULL)//メッシュフィールド
	{
		CMeshField::Create(0, CMeshField::XZ, D3DXVECTOR3(-300.0f, 0.0f, 200.0f), 50, 200, 10);
		CMeshField::Create(1, CMeshField::XY, D3DXVECTOR3(-300.0f, 200.0f, 200.0f), 50, 200, 4);
	}


	//if (m_pSceneX == NULL)
	//{
	//	m_pSceneX = CSceneX::Create();	//シーンX
	//}

	//オブジェクト
	//m_pObject[0] = CObject::Create(CObject::OBJ_TYPE01, D3DXVECTOR3(-50.0f, 30.0f, 0.0f));
	//m_pObject[1] = CObject::Create(CObject::OBJ_TYPE01, D3DXVECTOR3(100.0f, 30.0f, 0.0f));

	if (m_pPlayer == NULL)//プレイヤー
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//==============================================
//ボタン押下によるobjの生成
//==============================================
void  CGame::ObjCreate(void)
{
	if (m_nInputMode == 0)//入力モード(キーボード時)
	{
		if (m_pInputKeyboard->GetTrigger(DIK_SPACE) == true)
		{
			int nObjType = m_pPlayer->GetSampleObjType();	//サンプルと同じOBJを生成するobjの種類
			D3DXVECTOR3 pos = m_pPlayer->GetPos();		//生成する場所
			D3DXVECTOR3 rot = m_pPlayer->GetRot();
			m_pObject[m_nCreateCnt] = CObject::Create(nObjType, D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(rot.x, rot.y, rot.z));
			m_nCreateCnt += 1;
		}
	}

	if (m_nInputMode == 1)//入力モード(マウス時)
	{
		if (m_pInputMouse->GetTrigger(0) == true)
		{
			int nObjType = m_pPlayer->GetSampleObjType();	//サンプルと同じOBJを生成するobjの種類
			D3DXVECTOR3 pos = m_pPlayer->GetPos();		//生成する場所
			D3DXVECTOR3 rot = m_pPlayer->GetRot();
			m_pObject[m_nCreateCnt] = CObject::Create(nObjType, D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(rot.x, rot.y, rot.z));
			m_nCreateCnt += 1;

		}
	}
}

//==============================================
//ボタン押下によるobjの削除
//==============================================
void CGame::ObjDelete()
{
	if (m_pInputKeyboard->GetTrigger(DIK_BACK) == true)
	{
		m_nCreateCnt -= 1;
		if (m_nCreateCnt < 0)
		{
			m_nCreateCnt = 0;
		}
		if (m_pObject[m_nCreateCnt] != NULL)
		{
			m_pObject[m_nCreateCnt]->Uninit();
			m_pObject[m_nCreateCnt] = NULL;
		}
	}
}
//==============================================
//obj情報の保存・書き出し
//==============================================
void  CGame::Save(void)
{
	FILE *pFile;
	
	if (m_pInputKeyboard->GetTrigger(DIK_F5) == true)
	{
		pFile = fopen("DATA\\TEXT\\OBJ_OUTPUT.txt", "w");

		if (pFile != NULL)
		{
			fprintf(pFile, "OBJ_CREATE_LOAD");
			fprintf(pFile, "\n\nMAX_OBJ_CREATE = %d", CObject::GetCreateNum());
			for (int nCnt = 0; nCnt <= CObject::GetCreateNum() - 1; nCnt++)
			{
				fprintf(pFile, "\n\nOBJ_SET");
				fprintf(pFile, "\n\tOBJ_TYPE = %d", m_pObject[nCnt]->GetSaveObjType());
				fprintf(pFile, "\n\tTEX_TYPE = %d", m_pObject[nCnt]->GetSaveObjType());
				fprintf(pFile, "\n\tPOS = %.1f %.1f %.1f", m_pObject[nCnt]->GetPos().x, m_pObject[nCnt]->GetPos().y, m_pObject[nCnt]->GetPos().z);
				fprintf(pFile, "\n\tROT = %.1f %.1f %.1f", m_pObject[nCnt]->GetRot().x, m_pObject[nCnt]->GetRot().y, m_pObject[nCnt]->GetRot().z);
				fprintf(pFile, "\nOBJ_SET_END");
			}
			fprintf(pFile, "\n\nOBJ_CREATE_LOAD_END");
		}
	}
}

//==============================================
//		スクリーン座標をワールド座標に変換
//==============================================
D3DXVECTOR3* CGame::ScreenToWorld
(D3DXVECTOR3* pout,
	int nScreenPosX,
	int nScreenPosY,
	float fProjectionSpace_Z,//射影空間のZを求める
	int ScreenWide,
	int ScreenHeight,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj)
{
	// 各行列の逆行列を算出
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, View);
	D3DXMatrixInverse(&InvPrj, NULL, Prj);
	D3DXMatrixIdentity(&VP);
	VP._11 = ScreenWide / 2.0f; VP._22 = -ScreenHeight / 2.0f; 
	VP._41 = ScreenWide / 2.0f; VP._42 = ScreenHeight / 2.0f; 
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// 逆変換
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(pout, &D3DXVECTOR3((float)nScreenPosX, (float)nScreenPosY, fProjectionSpace_Z), &tmp);

	return pout;
}

//==============================================
//	スクリーン座標とXZ平面のワールド座標を交点算出
//==============================================
D3DXVECTOR3* CGame::CalculationPoint
(D3DXVECTOR3* pout,
	int nScreenPosX,
	int nScreenPosY,
	int ScreenWide,
	int ScreenHeight,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj)
{
	D3DXVECTOR3 nearPoint;	//近い部分を見る
	D3DXVECTOR3 farPoint;	//遠い部分を見る
	D3DXVECTOR3 ray;		//ワールド上の平面に当てる光線

	//スクリーン座標が床と交差する
	ScreenToWorld(&nearPoint, nScreenPosX, nScreenPosY, 0.0f, ScreenWide, ScreenHeight, View, Prj);
	//スクリーン座標が床と交差しない
	ScreenToWorld(&farPoint, nScreenPosX, nScreenPosY, 1.0f, ScreenWide, ScreenHeight, View, Prj);

	//光線の値を算出・正規化
	ray = farPoint - nearPoint;
	D3DXVec3Normalize(&ray, &ray);

	//ここら辺はサイトを活用↓
	CInputKeyboard *m_pInputKeyboard = CManager::GetInputKeyboard();
	CCamera *pCamera = CGame::GetCamera();
	if (pCamera != NULL)
	{
		if (pCamera->GetCameraMode() == 0)
		{
			if (ray.z <= 1) //床と交差する
			{
				// 床交点
				float Lray = D3DXVec3Dot(&ray, &D3DXVECTOR3(0, 0, 1));
				float LP0 = D3DXVec3Dot(&(-nearPoint), &D3DXVECTOR3(0, 0, 1));
				CDebug::DebugLog("\nLray%f", Lray);
				CDebug::DebugLog("\nLP0%f", LP0);

				//*pout = nearPoint + (LP0 / Lray)*ray;
				CDebug::DebugLog("\npout->　X%f Y%f Z%f", pout->x, pout->y, pout->z);

				pout->x = (nearPoint.x + (LP0 / Lray)*ray.x);
				pout->y = (nearPoint.y + (LP0 / Lray)*ray.y);
				pout->z = (nearPoint.z + (LP0 / Lray)*ray.z);

				CDebug::DebugLog("\n最終pout->　X%f Y%f Z%f", pout->x, pout->y, pout->z);
			}
			else //床と交差しない
			{
				*pout = farPoint;

			}

		}

		if (pCamera->GetCameraMode() == 1)
		{

			if (ray.y <= 0) //床と交差する
			{
				// 床交点
				float Lray = D3DXVec3Dot(&ray, &D3DXVECTOR3(0, 1, 0));
				float LP0 = D3DXVec3Dot(&(-nearPoint), &D3DXVECTOR3(0, 1, 0));
				*pout = nearPoint + (LP0 / Lray)*ray;
			}
			else //床と交差しない
			{
				*pout = farPoint;
			}
		}
		
	}	
	return pout;
}


//==============================================
//デバック用処理
//==============================================
void  CGame::Debug(void)
{
	CDebug::DebugLog("\n現在の生成数 %d", m_nCreateCnt);
}





