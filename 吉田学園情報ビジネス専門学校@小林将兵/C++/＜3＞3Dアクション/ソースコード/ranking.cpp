//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//						ランキング処理 [ranking.h]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "ranking.h"
#include "fade.h"
#include "debugLog.h"
#include "sound.h"
#include "light.h"
#include "camera.h"
#include "scene2D.h"
#include "polygon2D.h"
#include "scene3D.h"
#include "polygon3D.h"
#include "particle.h"
#include "number.h"
#include "score.h"
#include "object.h"
#include "player.h"
#include "enemy.h"

//=====================================================================
//							静的メンバ変数
//=====================================================================
CDebug *CRanking::m_pDebug = NULL;
CSound *CRanking::m_pSound = NULL;
CLight *CRanking::m_pLight = NULL;
CCamera *CRanking::m_pCamera = NULL;
CScene2D *CRanking::m_pScene2D = NULL;
CPolygon2D *CRanking::m_pPolygon2D = NULL;
CPolygon3D *CRanking::m_pPolygon3D = NULL;
CParticle3D *CRanking::m_pParticle3D = NULL;
CNumber *CRanking::m_pNumber = NULL;
CScore *CRanking::m_pScore = NULL;
CObject *CRanking::m_pObject[OBJ_CREATE] = {};
CPlayer *CRanking::m_pPlayer = NULL;

//==============================================
//					コンストラクタ
//==============================================
CRanking::CRanking()
{

}

//==============================================
//					デストラクタ
//==============================================
CRanking::~CRanking()
{

}

//==============================================
//						生成
//==============================================
CRanking *CRanking::Create()
{
	CRanking *pRanking = NULL;

	if (pRanking == NULL)
	{
		pRanking = new CRanking;
		pRanking->Init();
	}

	return pRanking;
}
//==============================================
//					初期化
//==============================================
HRESULT CRanking::Init(void)
{
	m_nDebugCnt = 0;
	NullCheck();				//使用するデータを一度NULLにする
	BulkLoadData();				//使用したモデルとテクスチャの解放
	MAP_LOAD();					//マップ情報の読み込み
	CreateData();				//読み込んだ情報をもとにobjの生成
	m_pCamera->SetV(D3DXVECTOR3(0.0f, 10.0f, -80.0f));//注視点からの距離
	m_pCamera->SetR(D3DXVECTOR3(0.0f, 50.0f, 0.0f));//注視点の位置
	m_pSound = CManager::GetSound();
	if (m_pSound != NULL)
	{
		m_pSound->PlaySound(CSound::BGM_SOUND_RANKING);
	}
	return S_OK;
}
//==============================================
//						終了
//==============================================
void CRanking::Uninit(void)
{
	if (m_pSound != NULL)
	{
		m_pSound->StopSound();
	}

	BulkUnLoadData();			//使用したモデルとテクスチャの解放

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
void CRanking::Update(void)
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

	//エンタキーで再度ゲームの開始
	if (m_pInputKeyboard->GetTrigger(DIK_RETURN) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
	{
		if (m_pFade == CFade::FADE_NONE)
		{
			if (m_pSound != NULL)
			{
				m_pSound->PlaySound(CSound::SE_BUTTON);
			}
			CManager::GetFade()->SetFade(CManager::MODE_TITLE);
		}
	}

#ifdef _DEBUG
	DebugLoop();			//デバック操作用
#endif
}

//==============================================
//					描画
//==============================================
void CRanking::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();//カメラ描画
	}

}
//==============================================
//				NULLチェック
//==============================================
void CRanking::NullCheck(void)
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

	if (m_pPolygon2D != NULL)
	{
		m_pPolygon2D = NULL;	//ポリゴン2D
	}

	if (m_pPolygon3D != NULL)
	{
		m_pPolygon3D = NULL;	//ポリゴン3D
	}
	if (m_pScore != NULL)
	{
		m_pScore = NULL;
	}

	for (int nCnt = 0; nCnt < m_nMaxObjCreateNum; nCnt++)
	{
		if (m_pObject[nCnt] != NULL)
		{
			m_pObject[nCnt] = NULL;	//オブジェクト
		}
	}

	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;		//プレイヤー
	}
}

//==============================================
//				　Load処理(読み込み)
//==============================================
void CRanking::BulkLoadData(void)
{
	CPolygon2D::TextureLoad();
	CPolygon3D::TextureLoad();
	CParticle3D::TextureLoad();
	CNumber::TextureLoad();
	CObject::ObjectLoad();
	CObject::TextureLoad();
	CPlayer::ModelLoad();
	CPlayer::TextureLoad();
	CEnemy::ModelLoad();
	CEnemy::TextureLoad();
}

//==============================================
//				　UnLoad処理(解放)
//==============================================
void CRanking::BulkUnLoadData(void)
{
	CEnemy::TextureUnLoad();
	CEnemy::ModelUnLoad();
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
void CRanking::CreateData(void)
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

	if (m_pPolygon2D == NULL)//2Dテクスチャ
	{
		CPolygon2D::Create(12, false, D3DXVECTOR3(640.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300.0f, 70.0f, 1, 1, 1, true);
		CPolygon2D::Create(13, false, D3DXVECTOR3(390.0f, 420.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 70.0f, 275.0f, 1, 1, 1, true);

	}

	if (m_pPolygon3D == NULL)//3Dテクスチャ
	{
		CPolygon3D::Create(5, D3DXVECTOR3(70.0f, 40.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), 2, 5, 5, true);
		CPolygon3D::Create(5, D3DXVECTOR3(-100.0f, 120.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), 2, 5, 5, true);
		CPolygon3D::Create(5, D3DXVECTOR3(-60.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), 2, 5, 5, true);

	}

	if (m_pScore == NULL)
	{
		m_pScore = CScore::Create(D3DXVECTOR3(580, 205, 0), CScore::RANKING_SCORE);
	}


	if (m_pPlayer == NULL)//プレイヤー
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(-60.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.8f, 0.0f));
	}
	CEnemy::Create(0, D3DXVECTOR3(60.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
}

//==============================================
//				デバック用処理
//==============================================
void  CRanking::DebugLoop(void)
{
	m_nDebugCnt++;
	if (m_nDebugCnt >= 50)
	{
		if (m_pFade == CFade::FADE_NONE)
		{
			CManager::GetFade()->SetFade(CManager::MODE_TITLE);
		}
	}
}

//==============================================
//		外部データからマップ情報の読み込み
//==============================================
void CRanking::MAP_LOAD(void)
{
	FILE *pFile;
	char * pStrCur;	//先頭文字列のポインタ
	char aLine[256];//文字列の読み込み
	char aStr[256];	//文字列の抜き出し
	int nCnt = 0;
	int nWord;

	//外部テキストの読み込み
	pFile = fopen("DATA\\TEXT\\STAGE01.txt", "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "OBJ_CREATE_LOAD", strlen("OBJ_CREATE_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					//オブジェクトを何個読み込むか
					if (memcmp(pStrCur, "MAX_OBJ_CREATE = ", strlen("MAX_OBJ_CREATE = ")) == 0)
					{
						pStrCur += strlen("MAX_OBJ_CREATE = ");
						strcpy(aStr, pStrCur);
						m_nMaxObjCreateNum = atoi(aStr);
					}
					if (memcmp(pStrCur, "OBJ_SET", strlen("OBJ_SET")) == 0)
					{
						while (1)
						{
							fgets(&aLine[0], 256, pFile);
							pStrCur = CSceneX::GetLIneTop(&aLine[0]);

							//使用するオブジェクト番号
							if (memcmp(pStrCur, "OBJ_TYPE = ", strlen("OBJ_TYPE = ")) == 0)
							{
								pStrCur += strlen("OBJ_TYPE = ");
								strcpy(aStr, pStrCur);
								m_nObjType[nCnt] = atoi(aStr);
							}
							//オブジェクトに張り付けるUV番号
							if (memcmp(pStrCur, "TEX_TYPE = ", strlen("TEX_TYPE = ")) == 0)
							{
								pStrCur += strlen("TEX_TYPE = ");

								strcpy(aStr, pStrCur);

								m_nTexType[nCnt] = atoi(aStr);
							}
							//配置する位置
							if (memcmp(pStrCur, "POS =", strlen("POS =")) == 0)
							{

								pStrCur += strlen("POS =");
								strcpy(aStr, pStrCur);

								for (int nCntWord = 0; nCntWord < 3; nCntWord++)
								{
									nWord = CSceneX::PopString(pStrCur, aStr);
									pStrCur += nWord;//読み込み文字位置をずらす
									strcpy(aStr, pStrCur);

									if (nCntWord == 0)//x
									{
										m_ObjOffseet[nCnt].fPosX = (float)atof(aStr);

									}
									else if (nCntWord == 1)//y
									{
										m_ObjOffseet[nCnt].fPosY = (float)atof(aStr);
									}
									else//z
									{
										m_ObjOffseet[nCnt].fPosZ = (float)atof(aStr);
									}
								}
							}
							//向き
							if (memcmp(pStrCur, "ROT =", strlen("ROT =")) == 0)
							{
								pStrCur += strlen("ROT =");
								strcpy(aStr, pStrCur);

								//x,y,z分回す
								for (int nCntWord = 0; nCntWord < 3; nCntWord++)
								{
									nWord = CSceneX::PopString(pStrCur, aStr);
									pStrCur += nWord;//読み込み文字位置をずらす
									strcpy(aStr, pStrCur);

									if (nCntWord == 0)//x
									{
										m_ObjOffseet[nCnt].fRotX = (float)atof(aStr);

									}
									else if (nCntWord == 1)//y
									{
										m_ObjOffseet[nCnt].fRotY = (float)atof(aStr);
									}
									else//z
									{
										m_ObjOffseet[nCnt].fRotZ = (float)atof(aStr);
									}
								}
							}

							//読み込み終了
							if (memcmp(pStrCur, "OBJ_SET_END", strlen("OBJ_SET_END")) == 0)
							{
								nCnt++;
								break;
							}
						}
					}
					//読み込み終了
					if (memcmp(pStrCur, "OBJ_CREATE_LOAD_END", strlen("OBJ_CREATE_LOAD_END")) == 0)
					{
						break;
					}
				}
			}

			//読み込み終了
			if (memcmp(pStrCur, "OBJ_CREATE_LOAD_END", strlen("OBJ_CREATE_LOAD_END")) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);
}




