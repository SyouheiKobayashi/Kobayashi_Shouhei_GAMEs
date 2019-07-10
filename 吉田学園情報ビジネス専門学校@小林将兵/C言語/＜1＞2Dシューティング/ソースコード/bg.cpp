//? ◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//? 背景処理[bg.cpp]
//? Author : 小林将兵 / Kobayashi Shouhei
//? ◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "main.h"
#include "bg.h"

//? ==================================================
//?+ マクロ
//? ==================================================
#define BG_TEXTURENAME "DATA\\TEXTURE\\bg000.png" //読み込むテクスチャ
#define BG_POS_X (0)						 //背景の左上X座標
#define BG_POS_Y (0)						 //背景の左上Y座標
#define BG_WIDTH (SCREEN_WIDTH)				 //背景の幅
#define BG_HEIGHT (SCREEN_HEIGHT)			 //背景の高さ

//? ==================================================
//+ グローバル変数
//? ==================================================
LPDIRECT3DTEXTURE9 g_pTextureBG[2] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;

int g_nCountAnimBG; //アニメーションカウンター

//? ==================================================
//+ 初期化
//? ==================================================
void InitBG(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCountAnimBG = 0;//アクションカウント

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME, &g_pTextureBG[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffBG->Unlock();
}

//? ==================================================
//+ 終了
//? ==================================================

void UninitBG(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_pTextureBG[nCnt] != NULL)
		{
			g_pTextureBG[nCnt]->Release();
			g_pTextureBG[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//? ==================================================
//+ 更新
//? ==================================================
void UpdateBG(void)
{
	g_nCountAnimBG++;//アニメーションのカウントアップ
	
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (0.001f * g_nCountAnimBG));
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (0.001f * g_nCountAnimBG));
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (0.001f * g_nCountAnimBG));
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (0.001f * g_nCountAnimBG));

	/*pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (0.01f * g_nCountAnimBG));
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (0.01f * g_nCountAnimBG));
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (0.01f * g_nCountAnimBG));
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (0.01f * g_nCountAnimBG));*/

	if (pVtx[0].tex.x < 0.0f)
	{
		pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	if (pVtx[1].tex.x < 0.0f)
	{
		pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	}
	//頂点バッファをアンロック
	g_pVtxBuffBG->Unlock();
}

//? ==================================================
//+ 描画
//? ==================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを所得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBG[nCnt]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}
