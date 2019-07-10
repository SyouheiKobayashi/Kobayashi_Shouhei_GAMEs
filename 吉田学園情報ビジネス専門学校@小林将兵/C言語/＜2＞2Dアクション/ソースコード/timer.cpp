//=============================================================================
// 制限時間の処理 [timer.cpp]
// Author : Kobayashi / 小林 将兵
//=============================================================================
#include "main.h"
#include "game.h"
#include "timer.h"
#include "fade.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_NAME	"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define TIMER_SET (16)//制限時間
#define MAX_DISPLAY (3)//表示桁数
#define TIMER_WIDTH (25.0f)//横サイズ
#define TIMER_HEIGHT (35.0f)//縦サイズ

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nCounter;	//状態管理のカウンター
	int nTime;		//タイム
}TIMER;

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTimer = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;		//頂点バッファへのポインタ

TIMER g_Timer;					//スコア

int g_nTimer[MAX_DISPLAY];		//表示する桁

//=============================================================================
// 初期化処理
 //=============================================================================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//スコア初期化
	g_Timer.nTime = TIMER_SET*100;

	g_Timer.pos = D3DXVECTOR3(600, 50, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,TEXTURE_NAME,&g_pTextureTimer);

	// 頂点情報の作成
	MakeVertexTimer(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTimer(void)
{
	// テクスチャの開放
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTimer(void)
{
	bool bSize = false; //サイズは3桁分

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点情報を設定
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	g_Timer.nTime--;//時間を減らす

	if (g_Timer.nTime == 0)//残り時間0になったら
	{
		FADE pFade;

		pFade = GetFade();
				
		//モード設定
		//SetFade(MODE_RESULT);
		
		g_Timer.nTime = 0;
		SetGameState(GAMESTATE_END);
	}

	for (int nCntTimer = 0; nCntTimer < MAX_DISPLAY; nCntTimer++)
	{
			//数値3桁動かす↓
#if 1
			g_nTimer[0] = g_Timer.nTime % 100000 / 10000;
			g_nTimer[1] = g_Timer.nTime % 10000 / 1000;
			g_nTimer[2] = g_Timer.nTime % 1000 / 100;
#endif
			//数値2桁動かす↓
#if 0
			g_nTimer[0] = g_Timer.nTime % 10000 / 1000;
			g_nTimer[1] = g_Timer.nTime % 1000 / 100;
#endif

			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.0f + 0.1f * g_nTimer[nCntTimer], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + 0.1f * g_nTimer[nCntTimer], 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + 0.1f * g_nTimer[nCntTimer], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f * g_nTimer[nCntTimer], 1.0f);

			if (g_Timer.nTime == 1100)//残り時間10になったら
			{
				//表示される制限時間のカラー
				pVtx[0].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
			}
			if (g_Timer.nTime == 600)//残り時間5になったら
			{
				//表示される制限時間のカラー
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}

			pVtx += 4;
	}
		// 頂点バッファをアンロックする
		g_pVtxBuffTimer->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTimer(void)
{
	int nCntTimer;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTimer);

	for (nCntTimer = 0; nCntTimer < MAX_DISPLAY; nCntTimer++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTimer * 4, 2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;


	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DISPLAY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	// 頂点情報を設定
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTimer = 0; nCntTimer < MAX_DISPLAY; nCntTimer++)
	{
		pVtx[0].pos = D3DXVECTOR3(g_Timer.pos.x - TIMER_WIDTH, g_Timer.pos.y - TIMER_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Timer.pos.x + TIMER_WIDTH, g_Timer.pos.y - TIMER_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Timer.pos.x - TIMER_WIDTH, g_Timer.pos.y + TIMER_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Timer.pos.x + TIMER_WIDTH, g_Timer.pos.y + TIMER_HEIGHT, 0.0f);

		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//表示される制限時間のカラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
		g_Timer.pos.x += 45;//表示間隔
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffTimer->Unlock();
}


