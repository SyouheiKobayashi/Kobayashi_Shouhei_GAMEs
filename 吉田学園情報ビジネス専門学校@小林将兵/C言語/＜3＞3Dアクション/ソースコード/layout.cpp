//=============================================================================
// スコア処理 [layout.cpp]
// Author:Kobayashi/小林 将兵
//=============================================================================
#include "layout.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_Layout		"DATA\\TEXTURE\\LAYOUT01.png"	// 読み込むテクスチャファイル名
#define TATE_POS (35)
#define YOKO_POS (925)
#define TATE_SIZE (25)
#define YOKO_SIZE (25)
//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexLayout(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureLayout = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLayout = NULL;		// 頂点バッファへのポインタ
int						g_nLayout;					// スコア
//D3DXVECTOR3				g_posLayout;					// 位置

//=============================================================================
// 初期化処理
//=============================================================================
void InitLayout(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スコアの初期化
	g_nLayout = 0;

	//g_posLayout = D3DXVECTOR3(YOKO_POS, TATE_POS, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_Layout,		// ファイルの名前
								&g_pTextureLayout);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexLayout(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLayout(void)
{
	// テクスチャの開放
	if (g_pTextureLayout != NULL)
	{
		g_pTextureLayout->Release();
		g_pTextureLayout = NULL;
	}

	// 頂点バッファの開放
	if (g_pTextureLayout != NULL)
	{
		g_pTextureLayout->Release();
		g_pTextureLayout = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLayout(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLayout(void)
{
	int nCount;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffLayout, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLayout);

	
	// ポリゴンの描画
	/*for (nCount = 0; nCount < 1; nCount++)
	{*/
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0/*4 * nCount*/,2);
	//}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexLayout(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntLayout;

	// [頂点バッファを生成]
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4/* * 1*/,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLayout,
		NULL);

	// [頂点情報を設定]
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLayout->Lock(0, 0, (void**)&pVtx, 0);

	
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//pVtx += 4;

	// 頂点バッファをアンロックする
	g_pVtxBuffLayout->Unlock();
}

