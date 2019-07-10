//=============================================================================
// ポリゴン処理 [shadow.cpp]
// Author : Kobayashi/小林将兵
//=============================================================================
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME ("DATA\\TEXTURE\\shadow000.jpg")
#define	MAX_SHADOW (500)//影の最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 rot;			// 向き
	D3DXMATRIX mtxWorldShadow;	// ワールドマトリックス
	bool bUse;					// 使用しているか否か

	//D3DXCOLOR col;			// 色
	//float fRadius;			// 半径(大きさ)
	//int nLife;				// 表示時間(寿命)
	
} SHADOW;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;

SHADOW	g_Shadow[MAX_SHADOW];

//D3DXVECTOR3 g_posShadow;		//位置
//D3DXVECTOR3 g_rotShadow;		//向き
//D3DXMATRIX g_mtxWorldShadow;	//ワールドマトリックス

//=============================================================================
// 初期化処理
//=============================================================================
void InitShadow(void)
{
	int nCntShadow;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	//影情報の初期化
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_Shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureShadow);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-20.0f,0.0f, 20.0f);
		pVtx[1].pos = D3DXVECTOR3(20.0f ,0.0f, 20.0f);
		pVtx[2].pos = D3DXVECTOR3(-20.0f,0.0f, -20.0f);
		pVtx[3].pos = D3DXVECTOR3(20.0f, 0.0f, -20.0f);
	
		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		//法線の設定
		pVtx[0].nor = D3DXVECTOR3(0, 1.0, 0);
		pVtx[1].nor = D3DXVECTOR3(0, 1.0, 0);
		pVtx[2].nor = D3DXVECTOR3(0, 1.0, 0);
		pVtx[3].nor = D3DXVECTOR3(0, 1.0, 0);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);

		pVtx += 4;//頂点データの情報を４つ分進める

	}
	//頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitShadow(void)
{
	// テクスチャの破棄
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateShadow(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	// αブレンディングを減算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureShadow);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Shadow[nCntShadow].mtxWorldShadow);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].rot.y, g_Shadow[nCntShadow].rot.x, g_Shadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorldShadow, &g_Shadow[nCntShadow].mtxWorldShadow, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].pos.x, g_Shadow[nCntShadow].pos.y, g_Shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorldShadow, &g_Shadow[nCntShadow].mtxWorldShadow, &mtxTrans);


			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].mtxWorldShadow);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));


			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);


			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);
		}
	}

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成


	// 頂点情報の設定

}

//=============================================================================
// 影の設定
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	for(nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == false)
		{
			g_Shadow[nCntShadow].pos = pos;
			g_Shadow[nCntShadow].rot = rot;
			g_Shadow[nCntShadow].bUse = true;
			break;
		}
	}
	return nCntShadow;//使用している影の番号を返すらしい
}

void DeleteShadow(int nIdxShadow)
{
	g_Shadow[nIdxShadow].bUse = false;
}
//=============================================================================
// 影の位置を設定
//=============================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{
			g_Shadow[nIdxShadow].pos = pos;
		}
	}
}