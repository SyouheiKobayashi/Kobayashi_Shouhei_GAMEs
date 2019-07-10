//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//プレイヤー処理 [player.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "manager.h"
#include "debugLog.h"
#include "sound.h"
#include "camera.h"
#include "input.h"
#include "game.h"
//#include "sceneX.h"
#include "model.h"
#include "player.h"
#include "object.h"
#include "scene3D.h"

//=====================================================================
//静的メンバ変数
//=====================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture[SAMPLE_OBJ_NUM] = {};
LPD3DXMESH CPlayer::m_pMesh[SAMPLE_OBJ_NUM] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat[SAMPLE_OBJ_NUM] = {};
DWORD CPlayer::m_pNumMat[SAMPLE_OBJ_NUM] = {};
CPlayer::KEY CPlayer::m_aKeyOffseet[SAMPLE_OBJ_NUM] = {};
int CPlayer::m_nNumModel = NULL;
int CPlayer::m_nNumTex = NULL;
char CPlayer::m_aFileNameModel[SAMPLE_OBJ_NUM][256] = {};
char CPlayer::m_aFileNameTex[SAMPLE_OBJ_NUM][256] = {};

//==============================================
//コンストラクタ
//==============================================
CPlayer::CPlayer(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	for (int nCnt = 0; nCnt < SAMPLE_OBJ_NUM; nCnt++)
	{
		m_pModel[nCnt] = NULL;
	}

	m_pos = D3DXVECTOR3(0, 0, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);

	m_nSampleObj_ViewType = 0;

}
//==============================================
//デストラクタ
//==============================================
CPlayer::~CPlayer()
{
}

//==============================================
//生成
//==============================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = NULL;
	CModel *pModel = NULL;

	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
		pPlayer->m_pos = pos;
		pPlayer->m_rot = rot;
		pPlayer->Init();

	}
	return pPlayer;
}
//==============================================
//初期化処理
//==============================================
HRESULT CPlayer::Init(void)
{
	ModelLode();//各モデルの位置、向き、親を決める
	m_move = D3DXVECTOR3(2.0f,2.0f,2.0f);//移動量
	m_nSampleObj_ViewType = 0;
	return S_OK;
} 

//==============================================
//終了処理
//==============================================
void CPlayer::Uninit(void)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		if (m_pModel[nCnt] != NULL)
		{
			m_pModel[nCnt]->Uninit();
			delete m_pModel[nCnt];
			m_pModel[nCnt] = NULL;
		}
	}

	Release();
}

//==============================================
//更新処理
//==============================================
void CPlayer::Update(void)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)//使用モデル分更新
	{
		m_pModel[nCnt]->Update();
	}

	//キーボード・コントローラーの取得処理
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	m_pInputMouse = CManager::GetInputMouse();
	m_pGame = CManager::GetGame();

	SampleChange();		//サンプルobjの変更
	OperationManual();	//操作の変更
	if (m_pGame != NULL)
	{
		if (m_pGame->GetInputMode() == 0)//入力モード(キーボード)
		{
			MOVE();	//移動
		}
	}

	if (m_pInputKeyboard->GetTrigger(DIK_RETURN) == true|| m_pInputKeyboard->GetTrigger(DIK_X) == true)//位置・向きのリセット
	{
		m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	//if (m_pInputKeyboard->GetPress(DIK_LSHIFT) == true)//向きを変える
	//{
	//	m_rot.y += 0.05f;
	//}


	Debug();//デバック

}

//==============================================
//描画処理
//==============================================
void CPlayer::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;


	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	m_pModel[m_nSampleObj_ViewType]->Draw();//使用するモデルの描画
}

//==============================================
//サンプルの変更
//==============================================
void CPlayer::SampleChange(void)
{
	//+ @   @   @   @   @   @   @   @   @   @   @   @
	//+						入力モード(キーボード時)
	//+ @   @   @   @   @   @   @   @   @   @   @   @

	if (m_pGame != NULL)
	{
		if (m_pGame->GetInputMode() == 0)
		{
			//キーによる変更
			if (m_pInputKeyboard->GetTrigger(DIK_2) == true)
			{
				m_nSampleObj_ViewType += 1;
				if (m_nSampleObj_ViewType > CModel::GetMaxCreateNum())
				{
					m_nSampleObj_ViewType = 0;
				}
			}
			if (m_pInputKeyboard->GetTrigger(DIK_1) == true)
			{
				m_nSampleObj_ViewType -= 1;
				if (m_nSampleObj_ViewType < 0)
				{
					m_nSampleObj_ViewType = CModel::GetMaxCreateNum();
				}
			}
		}
	}

	//+ @   @   @   @   @   @   @   @   @   @   @   @
	//+						入力モード(マウス時)
	//+ @   @   @   @   @   @   @   @   @   @   @   @
	if (m_pGame != NULL)
	{
		if (m_pGame->GetInputMode() == 1)
		{
			//マウスホイールによる変更
			if (m_pInputMouse->GetWheel().lZ < 0)
			{
				m_nSampleObj_ViewType += 1;
				if (m_nSampleObj_ViewType > CModel::GetMaxCreateNum())
				{
					m_nSampleObj_ViewType = 0;
				}
			}
			if (m_pInputMouse->GetWheel().lZ > 0)
			{
				m_nSampleObj_ViewType -= 1;
				if (m_nSampleObj_ViewType < 0)
				{
					m_nSampleObj_ViewType = CModel::GetMaxCreateNum();
				}
			}
			

		}
	}
}

//==============================================
//カメラの視点モードによる操作の変更
//==============================================
void CPlayer::OperationManual(void)
{
	CCamera *pCamera = CGame::GetCamera();
	if (m_pGame != NULL)
	{
		if (m_pGame->GetInputMode() == 1)
		{
			if (pCamera != NULL)
			{
				if (pCamera->GetCameraMode() == 0)
				{
					//変換座標でプレイヤーを動かす
					D3DXVECTOR3 pos;
					CGame::CalculationPoint(
						&pos,
						m_pInputMouse->GetPos().x,
						m_pInputMouse->GetPos().y,
						SCREEN_WIDTH,
						SCREEN_HEIGHT,
						&pCamera->GetMtxViex(),
						&pCamera->GetMtxProjection());

					m_pos.x = pos.x;
					m_pos.y = pos.y;
					if (m_pInputKeyboard->GetPress(DIK_W) == true)
					{
						m_pos.z += 4.0f;
					}
					else if (m_pInputKeyboard->GetPress(DIK_S) == true)
					{
						m_pos.z += -4.0f;
					}
				}
				if (pCamera->GetCameraMode() == 1)
				{
					//変換座標でプレイヤーを動かす
					D3DXVECTOR3 pos;
					CGame::CalculationPoint(
						&pos,
						m_pInputMouse->GetPos().x,
						m_pInputMouse->GetPos().y,
						SCREEN_WIDTH,
						SCREEN_HEIGHT,
						&pCamera->GetMtxViex(),
						&pCamera->GetMtxProjection());

					m_pos.x = pos.x;
					m_pos.z = pos.z;
				}
			}
		}
	}
}
//==============================================
//移動
//==============================================
void CPlayer::MOVE(void)
{
	if (m_pInputKeyboard->GetPress(DIK_W) == true)
	{
		m_pos.z += m_move.z;
	}

	if (m_pInputKeyboard->GetPress(DIK_S) == true)
	{
		m_pos.z -= m_move.z;
	}
	if (m_pInputKeyboard->GetPress(DIK_A) == true)
	{
		m_pos.x -= m_move.x;
	}

	if (m_pInputKeyboard->GetPress(DIK_D) == true)
	{
		m_pos.x += m_move.x;
	}

	if (m_pInputKeyboard->GetPress(DIK_E) == true)
	{
		m_pos.y += m_move.y;
	}

	if (m_pInputKeyboard->GetPress(DIK_Q) == true)
	{
		m_pos.y -= m_move.y;
	}

}

//==============================================
//位置情報の反映
//==============================================
void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==============================================
//回転軸情報の反映
//==============================================
void CPlayer::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//==============================================
//表示obj情報の反映
//==============================================
void CPlayer::SetSampleObj(int num)
{
	m_nSampleObj_ViewType = num;
}

//==============================================
//モデルの読み込み
//==============================================
HRESULT CPlayer::ModelLoad(void)
{
	FILE *pFile;

	char * pStrCur;//先頭文字列のポインタ
	char aLine[256];//文字列の読み込み
	char aStr[256];//文字列の抜き出し
	int nCnt = 0;

	//テキストの読み込み↓
	pFile = fopen(OBJ_TEXT, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "OBJECT_LOAD", strlen("OBJECT_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					//パーツ数の読み込み
					if (memcmp(pStrCur, "NUM_OBJECT = ", strlen("NUM_OBJECT = ")) == 0)
					{
						pStrCur += strlen("NUM_OBJECT = ");
						strcpy(aStr, pStrCur);
						m_nNumModel = atoi(aStr);
					}

					if (memcmp(pStrCur, "OBJECT_NAME ", strlen("OBJECT_NAME ")) == 0)
					{
						pStrCur += strlen("OBJECT_NAME ");

						strcpy(aStr, pStrCur);
						while (1)
						{
							if (pStrCur[strlen(pStrCur) - 1] != 'x')
							{
								pStrCur[strlen(pStrCur) - 1] = '\0';//改行文字をNULL文字に変換(参考サイト::http://hisashi.me/blog/?p=714)
							}

							else
							{
								break;
							}

							strcpy(&m_aFileNameModel[nCnt][0], pStrCur);
						}

						nCnt += 1;
					}

					//読み込みの終わり
					if (memcmp(pStrCur, "END_OBJECT_LOAD", strlen("END_OBJECT_LOAD")) == 0)
					{
						break;
					}
				}

			}
			//読み込みの終わり
			if (memcmp(pStrCur, "END_OBJECT_LOAD", strlen("END_OBJECT_LOAD")) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);

	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// Xファイルの読み込み
	for (int nCntLoad = 0; nCntLoad < m_nNumModel; nCntLoad++)
	{
		D3DXLoadMeshFromX(m_aFileNameModel[nCntLoad],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCntLoad],
			NULL,
			&m_pNumMat[nCntLoad],
			&m_pMesh[nCntLoad]);
	}

	return S_OK;
}

//==============================================
//モデルの破棄
//==============================================
void CPlayer::ModelUnLoad(void)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		//マテリアルの数の解放
		if (m_pNumMat[nCnt] != NULL)
		{
			m_pNumMat[nCnt] = NULL;
		}
		//マテリアルの情報の開放
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}
		//メッシュの開放
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
	}
}

//==============================================
//モデルに反映させる画像の読み込み
//==============================================
HRESULT CPlayer::TextureLoad(void)
{
	FILE *pFile;

	char * pStrCur;//先頭文字列のポインタ
	char aLine[256];//文字列の読み込み
	char aStr[256];//文字列の抜き出し
	int nCnt = 0;

	//テキストの読み込み↓
	pFile = fopen(OBJ_TEXT, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "TEXTURE_LOAD", strlen("TEXTURE_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					//パーツ数の読み込み
					if (memcmp(pStrCur, "NUM_TEXTURE = ", strlen("NUM_TEXTURE = ")) == 0)
					{
						pStrCur += strlen("NUM_TEXTURE = ");
						strcpy(aStr, pStrCur);
						m_nNumTex = atoi(aStr);
					}

					if (memcmp(pStrCur, "TEXTURE_NAME ", strlen("TEXTURE_NAME ")) == 0)
					{
						pStrCur += strlen("TEXTURE_NAME ");

						strcpy(aStr, pStrCur);
						while (1)
						{
							if (pStrCur[strlen(pStrCur) - 1] != 'g')
							{
								pStrCur[strlen(pStrCur) - 1] = '\0';//改行文字をNULL文字に変換(参考サイト::http://hisashi.me/blog/?p=714)
							}

							else
							{
								break;
							}

							strcpy(&m_aFileNameTex[nCnt][0], pStrCur);
						}

						nCnt += 1;
					}

					//読み込みの終わり
					if (memcmp(pStrCur, "END_TEXTURE_LOAD", strlen("END_TEXTURE_LOAD")) == 0)
					{
						break;
					}
				}

			}
			//読み込みの終わり
			if (memcmp(pStrCur, "END_TEXTURE_LOAD", strlen("END_TEXTURE_LOAD")) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);

	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	for (int nCntLoad = 0; nCntLoad < m_nNumTex; nCntLoad++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aFileNameTex[nCntLoad], &m_pTexture[nCntLoad]);
	}

	return S_OK;
}

//==============================================
//モデルに反映させた画像の破棄
//==============================================
void CPlayer::TextureUnLoad(void)
{
	// テクスチャの破棄
	for (int nCntLoad = 0; nCntLoad < m_nNumTex; nCntLoad++)
	{

		if (m_pTexture[nCntLoad] != NULL)
		{
			m_pTexture[nCntLoad]->Release();
			m_pTexture[nCntLoad] = NULL;
		}
	}
}

//===================================================
//各モデルの位置、向き、親を決める
//===================================================
void CPlayer::ModelLode(void)
{
	//読み込んだモデル情報をモデルの数、反映させる
	for (int nCntLoad = 0; nCntLoad < m_nNumModel; nCntLoad++)
	{
		//各パーツの初期位置を決める↓
		m_pModel[nCntLoad] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		//各パーツのモデルを決める↓
		m_pModel[nCntLoad]->BindModel(m_pBuffMat[nCntLoad], m_pNumMat[nCntLoad], m_pMesh[nCntLoad]);
		//各パーツのモデルを決める↓
		m_pModel[nCntLoad]->BindTexture(m_pTexture[nCntLoad]);
		//各パーツの親を決める↓
		//m_pModel[nCntLoad]->SetParent(m_pModel[nParent[nCntLoad]]);
	}
}

//==============================================
//デバック用処理
//==============================================
void CPlayer::Debug(void)
{
	CDebug::DebugLog("\nプレイヤーのXXX位置 %f", m_pos.x);
	CDebug::DebugLog("\nプレイヤーのZZZ位置 %f", m_pos.z);

}
