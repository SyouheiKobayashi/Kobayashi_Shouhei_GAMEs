//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					mesh処理 [mesh.h]
//			Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "meshField.h"
#include "manager.h"
#include "game.h"
#include "input.h"
#include "debugLog.h"
#include "player.h"

//==============================================
//					コンストラクタ
//==============================================
CMeshField::CMeshField(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_bCheck = false;
	m_DotPosY = 0.0f;
}
//==============================================
//					デストラクタ
//==============================================
CMeshField::~CMeshField()
{

}

//==============================================
//						生成
//==============================================
CMeshField *CMeshField::Create(int nTexType,MESH_TYPE type, D3DXVECTOR3 startPos, int nSize, int nNumX, int nNumZ)
{
	CMeshField *pMeshField = NULL;

	if (pMeshField == NULL)
	{
		pMeshField = new CMeshField;
		pMeshField->m_nSelectTex = nTexType;
		pMeshField->m_nMeshType = type;
		pMeshField->m_startPos = startPos;
		pMeshField->m_nSize = nSize;
		pMeshField->m_nNumX = nNumX;
		pMeshField->m_nNumZ = nNumZ;
		pMeshField->m_nNumIndxMeshField = (nNumX * nNumZ) * 2 + (nNumZ - 1) * 4 + 2;
		pMeshField->m_nNumPolygonMeshField = (nNumX * nNumZ) * 2 + (nNumZ - 1) * 4;
		pMeshField->m_nNumVertexMeshField = (nNumX + 1)*(nNumZ + 1);
		pMeshField->Init();
	}
	return pMeshField;
}
//==============================================
//				初期化処理
//==============================================
HRESULT CMeshField::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bCheck = false;
	m_DotPosY = 0.0f;

	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点情報の作成
	VERTEX_3D *pVtx;

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertexMeshField,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// インデックスバッファの作成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndxMeshField,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESH_TEX01, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, MESH_TEX02, &m_pTexture[1]);


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// メッシュフィールドの位置を設定

	for (int nCntZ = 0; nCntZ < m_nNumZ + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nNumX + 1; nCntX++)
		{
			//頂点
			if (m_nMeshType == XZ)
			{
				pVtx[nCntZ * (m_nNumX + 1) + nCntX].pos = D3DXVECTOR3((float)m_startPos.x + (float)(m_nSize*nCntX), m_startPos.y, (float)m_startPos.z + (float)(-m_nSize*nCntZ));
			}
			else if (m_nMeshType == XY)
			{
				pVtx[nCntZ * (m_nNumX + 1) + nCntX].pos = D3DXVECTOR3((float)m_startPos.x + (float)(m_nSize*nCntX), (float)m_startPos.z + (float)(-m_nSize*nCntZ), m_startPos.y);
			}
			//テクスチャ
			pVtx[nCntZ * (m_nNumX + 1) + nCntX].tex = D3DXVECTOR2((-1.0f*nCntX), (1.0f*nCntZ));
			//カラー
			pVtx[nCntZ * (m_nNumX + 1) + nCntX].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//法線(初期化処理のため必ずロック / アンロックの間に)
	CMeshField::MeshNormaVector();

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	WORD*pIdx;//インデックスデータのポインタ

	//インデックスバッファをロックし、インデックスデータへのポインタを所得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntT = 0, nCntIdx = 0; nCntT < m_nNumZ; nCntT++)
	{
		for (int nCntY = 0; nCntY < m_nNumX + 1; nCntY++, nCntIdx++)
		{
			pIdx[0] = (m_nNumX + 1) + nCntIdx;
			pIdx[1] = 0 + nCntIdx;
			pIdx += 2;

			//横に進んでいき１少なくなった数&&nCntYと自分の指定した横のサイズが一致したとき
			if (nCntT < m_nNumZ - 1 && nCntY == m_nNumX)
			{
				pIdx[0] = 0 + nCntIdx;
				pIdx[1] = (m_nNumX + 1) + nCntIdx + 1;
				pIdx += 2;
			}
		}
	}

	//インデックスバッファをアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//==============================================
//				終了処理
//==============================================
void CMeshField::Uninit(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//インデックスバッファの破棄
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	Release();
}

//==============================================
//				更新処理
//==============================================
void CMeshField::Update(void)
{
	//キーボードの取得処理
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//現在のモードを取得
	int mode = CManager::GetMode();

	//プレイヤー情報の取得処理
	if (mode == CManager::STATE_MODE::MODE_GAME)
	{
		m_pPlayer = CGame::GetPlayer();
	}

	if (m_pPlayer != NULL)
	{
		D3DXVECTOR3 playerPos = m_pPlayer->GetPos();
		m_DotPosY = GetHight(playerPos);
	}

	CMeshField::MeshNormaVector();//法線

}

//==============================================
//					描画処理
//==============================================
void CMeshField::Draw(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture[m_nSelectTex]);

	//メッシュフィールドの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertexMeshField, 0, m_nNumPolygonMeshField);

}

//==============================================
//					法線処理
//==============================================
void CMeshField::MeshNormaVector(void)
{
	//頂点情報の作成
	VERTEX_3D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntZ = 0; nCntZ < m_nNumZ + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nNumX + 1; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;//各メッシュ頂点の情報
			D3DXVECTOR3 vec0, vec1, vec2;//各メッシュ頂点の繋ぎ

			if (nCntZ == 0)
			{
				if (nCntX == 0)
				{
					pPos0 = &pVtx[0].pos;
					pPos1 = &pVtx[m_nNumX + 1].pos;
					pPos2 = &pVtx[m_nNumX + 2].pos;
					pPos3 = &pVtx[1].pos;

					vec0 = *pPos1 - *pPos0;
					vec1 = *pPos2 - *pPos0;
					vec2 = *pPos3 - *pPos0;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//正規化

					D3DXVec3Cross(&m_nor[1], &vec2, &vec1);
					D3DXVec3Normalize(&m_nor[1], &m_nor[1]);//正規化

					pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 0))].nor = (m_nor[0] + m_nor[1]) / 2;

				}
				else if (nCntX == m_nNumX)
				{				
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX - 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX * 3 - (nCntX - 1)))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].pos;

					vec0 = *pPos0 - *pPos3;
					vec1 = *pPos2 - *pPos3;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//正規化
					pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].nor = m_nor[0];
				}
				else
				{
					//左側
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) * (nCntX + 0))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + ((m_nNumX + 1) + (nCntX)))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].pos;

					vec0 = *pPos0 - *pPos3;
					vec1 = *pPos2 - *pPos3;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//正規化

					//右側
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 0))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + m_nNumX + 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + m_nNumX + 1))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 1))].pos;

					vec0 = *pPos1 - *pPos0;
					vec1 = *pPos2 - *pPos0;
					vec2 = *pPos3 - *pPos0;

					D3DXVec3Cross(&m_nor[1], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[1], &m_nor[1]);//正規化
					D3DXVec3Cross(&m_nor[2], &vec2, &vec1);
					D3DXVec3Normalize(&m_nor[2], &m_nor[2]);//正規化

					pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 0))].nor = (m_nor[0] + m_nor[1] + m_nor[2]) / 3;
				}

			}
			else if (nCntZ == m_nNumZ)
			{
				if (nCntX == 0)
				{	
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) - (m_nNumX + 1))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 0))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 1))].pos;

					vec0 = *pPos2 - *pPos1;
					vec1 = *pPos0 - *pPos1;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//正規化
					pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 0))].nor = m_nor[0];

				}
				else if (nCntX == m_nNumX)
				{			
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) - 2)].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX - 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) - (nCntX - (nCntX - 1)))].pos;

					vec0 = *pPos3 - *pPos2;
					vec1 = *pPos0 - *pPos2;
					vec2 = *pPos1 - *pPos2;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//正規化
					D3DXVec3Cross(&m_nor[1], &vec2, &vec1);
					D3DXVec3Normalize(&m_nor[1], &m_nor[1]);//正規化

					pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].nor = (m_nor[0] + m_nor[1]) / 2;

				}
				else
				{
					//x1z02		
					//左側
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) - (m_nNumX + 1))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (1))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) - (3))].pos;

					vec0 = *pPos3 - *pPos2;
					vec1 = *pPos0 - *pPos2;
					vec2 = *pPos1 - *pPos2;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//正規化
					D3DXVec3Cross(&m_nor[1], &vec2, &vec1);
					D3DXVec3Normalize(&m_nor[1], &m_nor[1]);//正規化

															//右側
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) - (2))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (m_nNumX))].pos;

					vec0 = *pPos2 - *pPos1;
					vec1 = *pPos0 - *pPos1;

					D3DXVec3Cross(&m_nor[2], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[2], &m_nor[2]);//正規化

					pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].nor = (m_nor[0] + m_nor[1] + m_nor[2]) / 3;
				}

			}
			else
			{
				if (nCntX == 0)
				{
					//上側
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) - (m_nNumX + 1))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + 1)].pos;

					vec0 = *pPos2 - *pPos1;
					vec1 = *pPos0 - *pPos1;

					D3DXVec3Cross(&m_nor[2], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[2], &m_nor[2]);//正規化

					//下側
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 0))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + m_nNumX + 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + m_nNumX + 2))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 1))].pos;

					vec0 = *pPos1 - *pPos0;
					vec1 = *pPos2 - *pPos0;
					vec2 = *pPos3 - *pPos0;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//正規化
					D3DXVec3Cross(&m_nor[1], &vec2, &vec1);
					D3DXVec3Normalize(&m_nor[1], &m_nor[1]);//正規化

					pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].nor = (m_nor[0] + m_nor[1] + m_nor[2]) / 3;
				}
				else if (nCntX == m_nNumX)
				{
					//上側
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) - (2))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + (m_nNumX - 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (m_nNumX))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) - (1))].pos;

					vec0 = *pPos3 - *pPos2;
					vec1 = *pPos0 - *pPos2;
					vec2 = *pPos1 - *pPos2;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//正規化
					D3DXVec3Cross(&m_nor[1], &vec2, &vec1);
					D3DXVec3Normalize(&m_nor[1], &m_nor[1]);//正規化

					//下側
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) + (m_nNumX - 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1)) + ((m_nNumX * 2) + 1)].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) + m_nNumX)].pos;

					vec0 = *pPos0 - *pPos3;
					vec1 = *pPos2 - *pPos3;

					D3DXVec3Cross(&m_nor[2], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[2], &m_nor[2]);//正規化

					pVtx[(nCntZ*(m_nNumX + 1) + m_nNumX)].nor = (m_nor[0] + m_nor[1] + m_nor[2]) / 3;
				}
				else
				{
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) - ((m_nNumX + 1) - nCntX))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + nCntX)].pos;

					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (1 + nCntX))].pos;

					vec0 = *pPos2 - *pPos1;
					vec1 = *pPos0 - *pPos1;

					D3DXVec3Cross(&m_nor[2], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[2], &m_nor[2]);//正規化
					//----------------------------------------------

					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX - 1))].pos;

					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + ((m_nNumX + 1) + (nCntX)))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) + nCntX)].pos;

					vec0 = *pPos0 - *pPos3;
					vec1 = *pPos2 - *pPos3;

					D3DXVec3Cross(&m_nor[3], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[3], &m_nor[3]);//正規化
					////----------------------------------------------

					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) + nCntX)].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + (m_nNumX + nCntX) + 1)].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (m_nNumX + nCntX) + 2)].pos;

					vec0 = *pPos1 - *pPos0;
					vec1 = *pPos2 - *pPos0;

					D3DXVec3Cross(&m_nor[4], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[4], &m_nor[4]);//正規化
					////----------------------------------------------

					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) + nCntX)].pos;

					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (m_nNumX + 2) + nCntX)].pos;

					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) + nCntX) + 1].pos;

					vec0 = *pPos2 - *pPos0;
					vec1 = *pPos3 - *pPos0;

					D3DXVec3Cross(&m_nor[5], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[5], &m_nor[5]);//正規化

					pVtx[(nCntZ*(m_nNumX + 1) + nCntX)].nor = (m_nor[2] + m_nor[3] + m_nor[4] + m_nor[5]) / 4;
				}
			}
		}
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//==============================================
//				起伏の当たり判定
//==============================================
float CMeshField::GetHight(D3DXVECTOR3 pos)
{
	if (m_nMeshType == XZ)
	{
		//ローカル
		D3DXVECTOR3 vector1[6];
		D3DXVECTOR3 vector2[6];
		float fVectorPos[6];
		float fHeight = 0.0f;

		//プレイヤー情報の取得処理↓
		int mode = CManager::GetMode();

		if (mode == CManager::STATE_MODE::MODE_GAME)
		{
			m_pPlayer = CGame::GetPlayer();
		}

		if (m_pPlayer != NULL)
		{
			D3DXVECTOR3 playerPos = m_pPlayer->GetPos();//位置

			//頂点情報の作成
			VERTEX_3D *pVtx;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			int nMeshX, nMeshZ;

			int p0, p1, p2, p3;

			//範囲内チェック
			if (pVtx[0].pos.x < playerPos.x && playerPos.x< pVtx[m_nNumX].pos.x&&pVtx[0].pos.z > playerPos.z && playerPos.z > pVtx[m_nNumZ*(m_nNumX + 1)].pos.z)
			{
				m_bCheck = true;

				//メッシュ頂点0
				nMeshX = (int)(pos.x - pVtx[0].pos.x) / m_nSize;
				nMeshZ = (int)(pos.z - pVtx[0].pos.z) / -m_nSize;

				//各メッシュの頂点を決める
				p0 = nMeshZ*(m_nNumX + 1) + nMeshX;//左上
				p1 = nMeshZ*(m_nNumX + 1) + nMeshX + 1;//右上
				p2 = (nMeshZ + 1)*(m_nNumX + 1) + (nMeshX + 1);//右下
				p3 = (nMeshZ + 1)*(m_nNumX + 1) + nMeshX;//左下

				vector1[0] = pVtx[p2].pos - pVtx[p0].pos;//中心点
				vector2[0] = playerPos - pVtx[p0].pos;//プレイヤーとの中心点

				D3DXVECTOR3 V01 = pVtx[p3].pos;//軸となる頂点
				D3DXVECTOR3 V02 = pVtx[p0].pos;//軸頂点とつながる頂点
				D3DXVECTOR3 V03 = pVtx[p2].pos;//軸頂点とつながる頂点

				fVectorPos[0] = (vector1[0].z*vector2[0].x) - (vector1[0].x * vector2[0].z);//頂点を繋ぐ

				if (fVectorPos[0] < 0)
				{
					V01 = pVtx[p1].pos;
				}

				float fSave;//頂点情報の保存
				fSave = V01.y;

				//全体のy軸頂点を下げる
				V03.y -= V01.y;
				V02.y -= V01.y;
				V01.y -= V01.y;

				//法線
				D3DXVECTOR3 DotNor;
				m_vec0 = V02 - V01;
				m_vec1 = V03 - V01;
				D3DXVec3Cross(&DotNor, &m_vec0, &m_vec1);
				D3DXVec3Normalize(&DotNor, &DotNor);//正規化

				//VecAを求める(プレイヤーの頂点とポリゴンの頂点)
				D3DXVECTOR3 VecA;
				VecA = pos - V01;

				//逆算
				fHeight = -((VecA.x * DotNor.x) + (VecA.z * DotNor.z)) / DotNor.y + fSave;
			}
			else
			{
				m_bCheck = false;
			}

			// 頂点バッファをアンロックする
			m_pVtxBuff->Unlock();


		}
		return fHeight;
	}
}

//==============================================
//			　　起伏の生成
//==============================================
void CMeshField::SetHight(D3DXVECTOR3 pos, float fValue, float fRange)
{
	if (m_nMeshType == XZ)
	{
		//頂点情報の作成
		VERTEX_3D *pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntZ = 0; nCntZ <= m_nNumZ; nCntZ++)
		{
			for (int nCntX = 0; nCntX <= m_nNumX; nCntX++)
			{
				float fLength = (float)sqrt((pos.x - pVtx->pos.x)*(pos.x - pVtx->pos.x) + (pos.z - pVtx->pos.z)*(pos.z - pVtx->pos.z));//対象の頂点の距離
				if (fLength <= fRange)//範囲内チェック
				{
					float fHight = cosf((D3DX_PI / 2)*(fLength / fRange))*fValue;//距離の比率に応じた高さ
					pVtx->pos.y += fHight;
				}

				pVtx++;//4頂点を動かす
			}
		}

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}

}