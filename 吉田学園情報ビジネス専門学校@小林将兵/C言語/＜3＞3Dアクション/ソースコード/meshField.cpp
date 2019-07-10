//=============================================================================
// ポリゴン処理 [meshField.cpp]
// Author : Kobayashi/小林将兵
//=============================================================================
#include "meshField.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME ("DATA\\TEXTURE\\深海_床.jpg")
#define BLOCK_SIZE (50)
#define TATE (14)
#define YOKO (14)

#define INDEX ((TATE * YOKO )* 2+(TATE-1)*4+2)//インデックス
#define POLYGON ((TATE * YOKO )* 2+(TATE-1)*4)//ポリゴン
#define VERTEX ((TATE+1)*(YOKO+1))//頂点

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;

D3DXVECTOR3 g_posMeshField;		//位置
D3DXVECTOR3 g_rotMeshField;		//向き
D3DXMATRIX g_mtxWorldMeshField;	//ワールドマトリックス

int g_nNumIndxMeshField;//インデックス数
int g_nNumPolygonMeshField;//ポリゴン数
int g_nNumVertexMeshField;//頂点数


//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshField(void)
{
	int nCntIdx;

	g_nNumIndxMeshField = INDEX;
	g_nNumVertexMeshField = VERTEX;
	g_nNumPolygonMeshField = POLYGON;

	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

												//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureMeshField);

	// 頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	// インデックスバッファの作成
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	VERTEX_3D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	for (int nCntZ = 0; nCntZ < TATE + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < YOKO + 1; nCntX++)
		{
			pVtx[nCntZ * (YOKO+1)+ nCntX].pos = D3DXVECTOR3(-100+(BLOCK_SIZE*nCntX), 0.0f, 100+(-BLOCK_SIZE*nCntZ));

			pVtx[nCntZ * (YOKO + 1) + nCntX].tex = D3DXVECTOR2((-1.0*nCntX), (1.0*nCntZ));
			pVtx[nCntZ * (YOKO + 1) + nCntX].nor = D3DXVECTOR3(0, 1, 0);
			pVtx[nCntZ * (YOKO + 1) + nCntX].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffMeshField->Unlock();

	WORD*pIdx;//インデックスデータへのポインタ

	// インデックスバッファをロックし、インデックスデータへのポインタを所得
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	/*pIdx[0] = 2; pIdx[1] = 0; pIdx[2] = 3; pIdx[3] = 1;*/

	//pIdx[0] = 3; pIdx[1] = 0; pIdx[2] = 4; pIdx[3] = 1; pIdx[4] = 5; pIdx[5] = 2; pIdx[6] = 2;
	//pIdx[7] = 6; pIdx[8] = 6; pIdx[9] = 3; pIdx[10] = 7; pIdx[11] = 4; pIdx[12] = 8; pIdx[13] = 5;

	//頂点座標の設定
	for (int nCntT = 0, nCntIdx = 0;  nCntT<TATE; nCntT++)//縦
	{
		for (int nCntY = 0; nCntY < YOKO + 1; nCntY++,nCntIdx++)//横
		{
			pIdx[0] = (YOKO + 1) + nCntIdx;
			pIdx[1] = 0 + nCntIdx;
			pIdx += 2;
 			if (nCntT < TATE - 1 && nCntY == YOKO)//横に進んでいき１少なくなった数&&nCntYと自分の指定した横のサイズが一致したとき
			{
				pIdx[0] = 0 + nCntIdx;
				pIdx[1] = (YOKO + 1) + nCntIdx + 1;
				pIdx += 2;
			}
		}
	}

	//インデックスバッファをアンロック
	g_pIdxBuffMeshField->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshField(void)
{
	// テクスチャの破棄
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	// インデックスバッファの破棄
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshField(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);


	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshField);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0,0, VERTEX,0, POLYGON);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成


	// 頂点情報の設定

}

