//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//オブジェクト処理処理 [object.cpp]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "manager.h"
#include "debugLog.h"
#include "input.h"
#include "sceneX.h"
#include "object.h"
#include "game.h"

//=====================================================================
//静的メンバ変数
//=====================================================================
//テキスト読み込み関連
int CObject::m_nNumObject = NULL;
int CObject::m_nNumTexture = NULL;
char CObject::m_aFileNameObject[MAX_OBJECT][256] = {};
char CObject::m_aFileNameTexture[MAX_OBJECT][256] = {};
//モデル情報
int CObject::m_objType = 0;
LPD3DXMESH CObject::m_pMesh[MAX_OBJECT] = {};
LPD3DXBUFFER CObject::m_pBuffMat[MAX_OBJECT] = {};
DWORD CObject::m_pNumMat[MAX_OBJECT] = {};
//画像関連
LPDIRECT3DTEXTURE9 CObject::m_pTexture[OBJ_TEXTURE_NUM] = {};

int CObject::m_nCreateNum = 0;//生成された数の記憶

//==============================================
//コンストラクタ
//==============================================
CObject::CObject(int nPriority, DATA_TYPE dataType) :CSceneX(nPriority, dataType)
{
	//m_pTexture = NULL;		//テクスチャへのポインタ
	m_pVtxBuff = NULL;		//頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);
	m_VtxMin = GetVtxMin();
	m_VtxMax = GetVtxMax();
	
}
//==============================================
//デストラクタ
//==============================================
CObject::~CObject()
{

}

//==============================================
//生成
//==============================================
CObject *CObject::Create(int nObjType, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_nCreateNum += 1;
	CObject *pObject = NULL;
	if (pObject == NULL)
	{
		pObject = new CObject;
		m_objType = nObjType;
		pObject->BindObject(m_pBuffMat[nObjType], m_pNumMat[nObjType], m_pMesh[nObjType]);	//使用するオブジェクト
		pObject->BindTexture(m_pTexture[nObjType]);							//使用する画像
		pObject->Init();
		pObject->SetPos(pos);					//位置の反映
		pObject->SetRot(rot);
		pObject->SaveObjType(nObjType);
	}
	return pObject;
}
//==============================================
//初期化処理
//==============================================
HRESULT CObject::Init(void)
{
	CSceneX::Init();

	m_VtxMin = GetVtxMin();
	m_VtxMax = GetVtxMax();


	return S_OK;
}

//==============================================
//終了処理
//==============================================
void CObject::Uninit(void)
{
	m_nCreateNum -= 1;
	CSceneX::Uninit();
}

//==============================================
//更新処理
//==============================================
void CObject::Update(void)
{
	CSceneX::Update();
	
	Debug();
	
}

//==============================================
//描画処理
//==============================================
void CObject::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//pDevice->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE);

	CSceneX::Draw();

	//pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);


}

//==============================================
//当たり判定処理
//==============================================
bool CObject::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	D3DXVECTOR3 pos = GetPos();

	//上判定
	if (pos.x + m_VtxMin.x < pPos->x + OBJ_X &&
		pos.x + m_VtxMax.x > pPos->x - OBJ_X &&
		pos.z + m_VtxMin.z < pPos->z + OBJ_Z &&
		pos.z + m_VtxMax.z > pPos->z - OBJ_Z)
	{
		if (pos.y + m_VtxMax.y <= pPosOld->y + OBJ_Y &&
			pos.y + m_VtxMax.y > pPos->y - OBJ_Y)
		{
			//pPos->y = (pos.y + m_VtxMax.y) + OBJ_Y;
		}
	}

	//前後判定
	if (m_VtxMax.y + pos.y > pPos->y + OBJ_Y&&
		m_VtxMin.y - pos.y <= pPos->y + OBJ_Y)
	{
		if (pos.x + m_VtxMin.x < pPos->x + OBJ_X &&
			pos.x + m_VtxMax.x > pPos->x - OBJ_X)
		{
			//手前の判定
			if (pos.z + m_VtxMin.z >= pPosOld->z + OBJ_Z&&
				pos.z + m_VtxMin.z < pPos->z + OBJ_Z)
			{
				pPos->z = pos.z + m_VtxMin.z - OBJ_Z;
			}
			//奥の判定
			else if (pos.z + m_VtxMax.z <= pPosOld->z - OBJ_Z&&
				pos.z + m_VtxMax.z > pPos->z - OBJ_Z)
			{
				pPos->z = pos.z + m_VtxMax.z + OBJ_Z;
			}
		}

		//左右判定
		if (pos.z + m_VtxMin.z < pPos->z + OBJ_Z &&
			pos.z + m_VtxMax.z > pPos->z - OBJ_Z)
		{
			//左の判定
			if (pos.x + m_VtxMin.x >= pPosOld->x + OBJ_X&&
				pos.x + m_VtxMin.x < pPos->x + OBJ_X)
			{
				pPos->x = pos.x + m_VtxMin.x - OBJ_X;
				/*pPos->x -= 40.0f;
				pPos->y += 10.0f;*/

			}
			//右の判定
			else if (pos.x + m_VtxMax.x <= pPosOld->x - OBJ_X&&
				pos.x + m_VtxMax.x > pPos->x - OBJ_X)
			{
				pPos->x = pos.x + m_VtxMax.x + OBJ_X;
			}
		}
	}

	return 0;
}

//==============================================
//使用するオブジェクトの読み込み
//==============================================
HRESULT CObject::ObjectLoad(void)
{
	FILE *pFile;

	char * pStrCur;		//先頭文字列のポインタ
	char aLine[256];	//文字列の読み込み
	char aStr[256];		//文字列の抜き出し
	int nCnt = 0;

	//テキストの読み込み
	pFile = fopen(OBJ_TEXT, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "OBJECT_LOAD", strlen("OBJECT_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = GetLIneTop(&aLine[0]);

					//パーツ数の読み込み
					if (memcmp(pStrCur, "NUM_OBJECT = ", strlen("NUM_OBJECT = ")) == 0)
					{
						pStrCur += strlen("NUM_OBJECT = ");
						strcpy(aStr, pStrCur);
						m_nNumObject = atoi(aStr);
					}
					//使用する名前の確認
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

							strcpy(&m_aFileNameObject[nCnt][0], pStrCur);
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

	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < m_nNumObject; nCnt++)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX(m_aFileNameObject[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCnt],
			NULL,
			&m_pNumMat[nCnt],
			&m_pMesh[nCnt]);
	}

	return S_OK;
}
//==============================================
//使用したオブジェクトの破棄
//==============================================
void CObject::ObjectUnLoad(void)
{
	for (int nCnt = 0; nCnt < m_nNumObject; nCnt++)
	{
		//メッシュの開放
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		//マテリアル関連の開放
		if (m_pNumMat[nCnt] != NULL)
		{
			m_pNumMat[nCnt] = NULL;
		}
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}
	}
}

//==============================================
//オブジェクトに反映させる画像の読み込み
//==============================================
HRESULT CObject::TextureLoad(void)
{
	FILE *pFile;

	char * pStrCur;//先頭文字列のポインタ
	char aLine[256];//文字列の読み込み
	char aStr[256];//文字列の抜き出し
	int nCntTexture = 0;

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

					//オブジェクトに使用する画像の数
					if (memcmp(pStrCur, "NUM_TEXTURE = ", strlen("NUM_TEXTURE = ")) == 0)
					{
						pStrCur += strlen("NUM_TEXTURE = ");
						strcpy(aStr, pStrCur);
						m_nNumTexture = atoi(aStr);
					}

					//オブジェクトに使用する画像の名前
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

							strcpy(&m_aFileNameTexture[nCntTexture][0], pStrCur);
						}

						nCntTexture += 1;
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
	for (int nCnt = 0; nCnt < m_nNumTexture; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aFileNameTexture[nCnt], &m_pTexture[nCnt]);
	}

	return S_OK;
}
//==============================================
//オブジェクトに反映させた画像の破棄
//==============================================
void CObject::TextureUnLoad(void)
{
	for (int nCnt = 0; nCnt < m_nNumTexture; nCnt++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//==============================================
//デバック
//==============================================
void CObject::Debug(void)
{

}

