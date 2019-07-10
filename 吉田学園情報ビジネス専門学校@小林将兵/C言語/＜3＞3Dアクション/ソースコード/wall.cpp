//=============================================================================
// ポリゴン処理 [wall.cpp]
// Author : Kobayashi/小林将兵
//=============================================================================
#include "wall.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME ("DATA\\TEXTURE\\wall000.jpg")
#define MAX_WALL (4)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;

WALL g_Wall[MAX_WALL];

//D3DXVECTOR3 g_posWall;		//位置
//D3DXVECTOR3 g_rotWall;		//向き
//D3DXMATRIX g_mtxWorldWall;	//ワールドマトリックス

//=============================================================================
// 初期化処理
//=============================================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_Wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].bUse = false;
	}
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureWall);

		// 頂点情報の作成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffWall,
			NULL);

		VERTEX_3D*pVtx;//頂点情報へのポインタ

		//頂点バッファをロックし、頂点データへのポインタを所得
		g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntWall2 = 0; nCntWall2 < MAX_WALL; nCntWall2++)
		{
			//頂点座標の設定
			//g_posWall = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
			pVtx[0].pos = D3DXVECTOR3(-100.0f, 150.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(100.0f, 150.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);

			//g_Wall[nCntWall2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f) * D3DX_PI;//壁の回転

			//テクスチャの設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//法線の設定
			pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
			pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
			pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
			pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);

			pVtx += 4;//頂点データの情報を４つ分進める
		}

	//頂点バッファをアンロック
	g_pVtxBuffWall->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWall(void)
{
	// テクスチャの破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWall(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Wall[nCntWall].mtxWorldWall);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].rot.y, g_Wall[nCntWall].rot.x, g_Wall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorldWall, &g_Wall[nCntWall].mtxWorldWall, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].pos.x, g_Wall[nCntWall].pos.y, g_Wall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorldWall, &g_Wall[nCntWall].mtxWorldWall, &mtxTrans);


			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].mtxWorldWall);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));


			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureWall);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
		}
	}

}

//=============================================================================
// 壁の設定
//=============================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 頂点情報の作成
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == false)
		{
			g_Wall[nCntWall].pos = pos;
			g_Wall[nCntWall].rot = rot;
			g_Wall[nCntWall].bUse = true;
			break;
		}
		//pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成


	// 頂点情報の設定

}

