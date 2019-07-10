//=============================================================================
// 画面フェード処理 [fade.cpp]
// Author : Kobayashi / 小林
//=============================================================================
#include "main.h"
#include "fade.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FADE_POS_X (0)						 //背景の左上X座標
#define FADE_POS_Y (0)						 //背景の左上Y座標
#define BG_WIDTH (SCREEN_WIDTH)				 //背景の幅
#define BG_HEIGHT (SCREEN_HEIGHT)			 //背景の高さ
//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureFade = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	// 頂点バッファへのポインタ
FADE					g_fade;					// フェード状態
MODE					g_modeNext;				// 次のモード
D3DXCOLOR				g_colorFade;			// フェード色

//=============================================================================
// 初期化処理
//=============================================================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	g_fade = FADE_IN;	//フェードイン状態
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//黒い画面、不透明にする

	// 頂点情報の設定
	MakeVertexFade(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFade(void)
{
	// テクスチャの開放
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFade(void)
{
	if (g_fade != FADE_NONE)
	{
//[フェードイン状態]
		if (g_fade == FADE_IN)//フェードイン状態
		{
			g_colorFade.a -= 0.02f;//画面を透明に

			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;//何もしていない状態
			}
		}
//[フェードアウト状態]
		else if (g_fade == FADE_OUT)//フェードアウト状態
		{
			g_colorFade.a += 0.02f;//画面を不透明に

			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;//フェードイン状態

				SetMode(g_modeNext);
			}
		}

		VERTEX_2D*pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点データへのポインタを所得
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	//頂点情報(カラー)の更新
		pVtx[0].col = g_colorFade;
		pVtx[1].col =g_colorFade;
		pVtx[2].col =g_colorFade;
		pVtx[3].col =g_colorFade;
	//頂点バッファをアンロック
		g_pVtxBuffFade->Unlock();	
	}
}

//=============================================================================
// タイトル画面
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureFade);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	///LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

							  //デバイスの所得
	pDevice = GetDevice();
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice, "Data\\bg100.png", &g_pTextureFade);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	// 頂点バッファの情報を設定
	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(FADE_POS_X, FADE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(FADE_POS_X + BG_WIDTH, FADE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(FADE_POS_X, FADE_POS_Y + BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH,BG_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffFade->Unlock();

}

//=============================================================================
// フェードの設定
//=============================================================================
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=============================================================================
// フェードの取得
//=============================================================================
FADE *GetFade(void)
{
	return &g_fade;
}

