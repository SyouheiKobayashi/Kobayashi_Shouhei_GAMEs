//=============================================================================
// ポリゴン処理 [meshWall.cpp]
// Author : Kobayashi/小林将兵
//=============================================================================
#include "meshWall.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME ("DATA\\TEXTURE\\深海_壁.jpg")
#define POLYGON_SIZE (235)
#define TATE (1)
#define YOKO (3)
#define MAX_WALL (4)

#define INDEX ((TATE * YOKO )* 2+(TATE-1)*4+2)//インデックス
#define POLYGON ((TATE * YOKO )* 2+(TATE-1)*4)//ポリゴン
#define VERTEX ((TATE+1)*(YOKO+1))//頂点

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;

MESHWALL g_MeshWall[MAX_WALL];

//D3DXVECTOR3 g_posMeshWall;		//位置
//D3DXVECTOR3 g_rotMeshWall;		//向き
//D3DXMATRIX g_mtxWorldMeshWall;	//ワールドマトリックス

int g_nNumIndxMeshWall;//インデックス数
int g_nNumPolygonMeshWall;//ポリゴン数
int g_nNumVertexMeshWall;//頂点数


//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshWall(void)
{
	int nCntM;
	int nCntIdx;

	g_nNumIndxMeshWall = INDEX;
	g_nNumVertexMeshWall = VERTEX;
	g_nNumPolygonMeshWall = POLYGON;

	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_MeshWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCntWall].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureMeshWall);

	// 頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	// インデックスバッファの作成
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	VERTEX_3D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	for (int nCntZ = 0; nCntZ < TATE + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < YOKO + 1; nCntX++)
		{
			pVtx[nCntZ * (YOKO+1)+ nCntX].pos = D3DXVECTOR3(-100+(POLYGON_SIZE*nCntX), (230* TATE) + (-POLYGON_SIZE*nCntZ), 0.0f);

			pVtx[nCntZ * (YOKO + 1) + nCntX].tex = D3DXVECTOR2((-1.0*nCntX), (1.0*nCntZ));
			pVtx[nCntZ * (YOKO + 1) + nCntX].nor = D3DXVECTOR3(0, 1, 0);
			pVtx[nCntZ * (YOKO + 1) + nCntX].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffMeshWall->Unlock();

	WORD*pIdx;//インデックスデータへのポインタ

	// インデックスバッファをロックし、インデックスデータへのポインタを所得
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	//インデックスの設定
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
	g_pIdxBuffMeshWall->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshWall(void)
{
	// テクスチャの破棄
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	// インデックスバッファの破棄
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshWall(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_MeshWall[nCntWall].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_MeshWall[nCntWall].mtxWorldWall);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall[nCntWall].rot.y, g_MeshWall[nCntWall].rot.x, g_MeshWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_MeshWall[nCntWall].mtxWorldWall, &g_MeshWall[nCntWall].mtxWorldWall, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_MeshWall[nCntWall].pos.x, g_MeshWall[nCntWall].pos.y, g_MeshWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_MeshWall[nCntWall].mtxWorldWall, &g_MeshWall[nCntWall].mtxWorldWall, &mtxTrans);


			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall[nCntWall].mtxWorldWall);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			// インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMeshWall);

			// ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VERTEX, 0, POLYGON);
		}
	}
}

//=============================================================================
// メッシュ壁の設定
//=============================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 頂点情報の作成
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_MeshWall[nCntWall].bUse == false)
		{
			g_MeshWall[nCntWall].pos = pos;
			g_MeshWall[nCntWall].rot = rot;
			g_MeshWall[nCntWall].bUse = true;
			break;
		}
		//pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffMeshWall->Unlock();
}

