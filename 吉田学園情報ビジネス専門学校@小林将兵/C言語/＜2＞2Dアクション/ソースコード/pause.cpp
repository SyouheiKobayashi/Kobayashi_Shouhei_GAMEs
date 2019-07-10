//=============================================================================
// ポーズの処理 [pause.cpp]
// Author:Kobayashi/小林 将兵
//=============================================================================
#include "main.h"
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "game.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define PAUSE_TEXTURENAME	""								// 読み込むテクスチャ
#define PAUSE_TEXTURENAME1	""		// 読み込むテクスチャ1
#define PAUSE_TEXTURENAME2	""		// 読み込むテクスチャ2
#define PAUSE_TEXTURENAME3	""		// 読み込むテクスチャ2
#define PAUSE_TEXTURENAME4	""		// 読み込むテクスチャ2
#define PAUSE_POS_X		(0)							// 背景の左上X座標
#define PAUSE_POS_Y		(0)							// 背景の左上Y座標
#define PAUSE_POS_X1	(SCREEN_WIDTH)				// ポーズ1の大きさ
#define PAUSE_POS_Y1	(SCREEN_HEIGHT)				// ポーズ1の大きさ
#define PAUSE_POS_X2	(620)						// ポーズ2の大きさ
#define PAUSE_POS_Y2	(130)						// ポーズ2の大きさ
#define PAUSE_POS_X3	(620)						// ポーズ3の大きさ
#define PAUSE_POS_Y3	(130)						// ポーズ3の大きさ
#define PAUSE_POS_X4	(620)						// ポーズ4の大きさ
#define PAUSE_POS_Y4	(130)						// ポーズ4の大きさ
#define MAX_PAUSE		(5)							// 背景の数
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_PAUSE] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;		// 頂点バッファへのポインタ
PAUSE g_aPause[MAX_PAUSE];
int g_nSelect;
bool g_bSelect;
int g_nPressCounter;
//=============================================================================
// 初期化処理（ポリゴン）
//=============================================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスへのポインタ
	VERTEX_2D*pVtx;				// 頂点情報へのポインタ
	// デバイスの取得
	pDevice = GetDevice();

	// 背景の情報の初期化
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		g_aPause[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 座標
		g_aPause[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 初期座標
		g_aPause[nCntPause].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);// 色
		g_aPause[nCntPause].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 背景の移動量
		g_aPause[nCntPause].nType = 0;								// タイプ
		g_aPause[nCntPause].nCounterAnim = 0;						// カウンター
		g_aPause[nCntPause].nPatternAnim = 0;						// パターンNo
		g_aPause[nCntPause].bUse = false;							// 使用されているかどうか
	}
	g_nSelect = PAUSETYPE_CONTINUE;
	g_bSelect = false;
	g_nPressCounter = 0;
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
							PAUSE_TEXTURENAME1,
							&g_pTexturePause[1]);
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
							PAUSE_TEXTURENAME2,
							&g_pTexturePause[2]);
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
							PAUSE_TEXTURENAME3,
							&g_pTexturePause[3]);
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
							PAUSE_TEXTURENAME4,
							&g_pTexturePause[4]);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE,
							D3DUSAGE_WRITEONLY,
							FVF_VERTEX_2D,
							D3DPOOL_MANAGED,
							&g_pVtxBuffPause,
							NULL);

	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(-(SCREEN_WIDTH / 2), -(SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2), -(SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;
	pVtx[2].pos = D3DXVECTOR3(-(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;

	pVtx[4].pos = D3DXVECTOR3(-(PAUSE_POS_X1 / 2), -(PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;
	pVtx[5].pos = D3DXVECTOR3((PAUSE_POS_X1 / 2), -(PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;
	pVtx[6].pos = D3DXVECTOR3(-(PAUSE_POS_X1 / 2), (PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;
	pVtx[7].pos = D3DXVECTOR3((PAUSE_POS_X1 / 2), (PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;

	pVtx[8].pos = D3DXVECTOR3(-(PAUSE_POS_X2 / 2), -(PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;
	pVtx[9].pos = D3DXVECTOR3((PAUSE_POS_X2 / 2), -(PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;
	pVtx[10].pos = D3DXVECTOR3(-(PAUSE_POS_X2 / 2), (PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;
	pVtx[11].pos = D3DXVECTOR3((PAUSE_POS_X2 / 2), (PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;

	pVtx[12].pos = D3DXVECTOR3(-(PAUSE_POS_X3 / 2), -(PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;
	pVtx[13].pos = D3DXVECTOR3((PAUSE_POS_X3 / 2), -(PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;
	pVtx[14].pos = D3DXVECTOR3(-(PAUSE_POS_X3 / 2), (PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;
	pVtx[15].pos = D3DXVECTOR3((PAUSE_POS_X3 / 2), (PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;

	/*pVtx[16].pos = D3DXVECTOR3(-(PAUSE_POS_X4 / 2), -(PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;
	pVtx[17].pos = D3DXVECTOR3((PAUSE_POS_X4 / 2), -(PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;
	pVtx[18].pos = D3DXVECTOR3(-(PAUSE_POS_X4 / 2), (PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;
	pVtx[19].pos = D3DXVECTOR3((PAUSE_POS_X4 / 2), (PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;*/
	// テクスチャ座標の設定
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);
	/*pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[17].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[19].tex = D3DXVECTOR2(1.0f, 1.0f);*/
	for (int nCntPause = 0 ; nCntPause < MAX_PAUSE; nCntPause++,pVtx += 4)
	{
		
		// rhwの設定
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].rhw = 1.0f;
		}

		// 頂点カラーの設定
		pVtx[0].col = g_aPause[nCntPause].col;
		pVtx[1].col = g_aPause[nCntPause].col;
		pVtx[2].col = g_aPause[nCntPause].col;
		pVtx[3].col = g_aPause[nCntPause].col;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

}
//=============================================================================
// 終了処理（ポリゴン）
//=============================================================================
void UninitPause(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < MAX_PAUSE; nCntTex++)
	{
		if (g_pTexturePause[nCntTex] != NULL)
		{
			g_pTexturePause[nCntTex]->Release();
			g_pTexturePause[nCntTex] = NULL;
		}
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}
//=============================================================================
// 更新処理（ポリゴン）
//=============================================================================
void UpdatePause(void)
{
	VERTEX_2D*pVtx;
	FADE pFADE;
	pFADE = GetFade();

	if (pFADE == FADE_NONE)
	{
		if (g_nSelect == PAUSETYPE_CONTINUE)
		{// continu
			g_aPause[g_nSelect + 2].col = D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f);
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				ReleaseGamePause();
			}
		}
		else if (g_nSelect == PAUSETYPE_RETRY)
		{// retry
			g_aPause[g_nSelect + 2].col = D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f);
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				SetFade(MODE_GAME);
			}
		}
		//else if (g_nSelect == PAUSETYPE_QUIT)
		//{// quit
		//	g_aPause[g_nSelect + 2].col = D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f);
		//	if (GetKeyboardTrigger(DIK_RETURN) == true)
		//	{
		//		SetFade(MODE_TITLE);
		//		SetGameState(GAMESTATE_NONE);
		//	}
		//}
	}
	if (GetKeyboardTrigger(DIK_S) == true)
	{// 下に移動(単体）
		g_aPause[g_nSelect + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		g_nSelect = (g_nSelect + 1) % PAUSETYPE_MAX;
	}
	else if (GetKeyboardTrigger(DIK_W) == true)
	{// 上に移動(単体)
		g_aPause[g_nSelect + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		g_nSelect = (g_nSelect + (PAUSETYPE_MAX-1)) % PAUSETYPE_MAX;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{// 下に移動(連続)
		g_nPressCounter++;
		if (g_nPressCounter >= 30)
		{
			if (g_nPressCounter % 10 == 0)
			{
				g_aPause[g_nSelect + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				g_nSelect = (g_nSelect + 1) % PAUSETYPE_MAX;
			}
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{// 上に移動(連続)
		g_nPressCounter++;
		if (g_nPressCounter >= 30)
		{
			if (g_nPressCounter % 10 == 0)
			{
				g_aPause[g_nSelect + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				g_nSelect = (g_nSelect + (PAUSETYPE_MAX-1)) % PAUSETYPE_MAX;
			}
		}
	}
	if (GetKeyboardTrigger(DIK_W) == true)
	{// 離したらカウンターリセット
		g_nPressCounter = 0;
	}
	else if (GetKeyboardTrigger(DIK_S) == true)
	{// 離したらカウンターリセット
		g_nPressCounter = 0;
	}
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		for (int nCnt = 0; nCnt < PAUSETYPE_MAX; nCnt++)
		{
			g_aPause[nCnt + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		}
		g_nSelect = 0;
	}

	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++, pVtx += 4)
	{
		// 頂点カラーの設定
		pVtx[0].col = g_aPause[nCntPause].col;
		pVtx[1].col = g_aPause[nCntPause].col;
		pVtx[2].col = g_aPause[nCntPause].col;
		pVtx[3].col = g_aPause[nCntPause].col;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}
//=============================================================================
// 描画処理（ポリゴン）
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスへのポインタ
	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePause[g_aPause[nCntPause].nType]);
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
								nCntPause * 4,
								2);
	}
}
//=============================================================================
// ポーズの設定
//=============================================================================
void SetPause(D3DXVECTOR3 pos,D3DXCOLOR col, int nType)
{
	VERTEX_2D*pVtx;

	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		if (g_aPause[nCntPause].bUse == false)
		{// 背景が使用されていない
			g_aPause[nCntPause].pos = pos;
			g_aPause[nCntPause].Initpos = pos;
			g_aPause[nCntPause].col = col;
			g_aPause[nCntPause].nType = nType;			
			g_aPause[nCntPause].bUse = true;	// 使用している状態にする
			break;
		}
	}
	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(-(SCREEN_WIDTH / 2), -(SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2), -(SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;
	pVtx[2].pos = D3DXVECTOR3(-(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;
	pVtx[4].pos = D3DXVECTOR3(-(PAUSE_POS_X1 / 2), -(PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;
	pVtx[5].pos = D3DXVECTOR3((PAUSE_POS_X1 / 2), -(PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;
	pVtx[6].pos = D3DXVECTOR3(-(PAUSE_POS_X1 / 2), (PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;
	pVtx[7].pos = D3DXVECTOR3((PAUSE_POS_X1 / 2), (PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;
	pVtx[8].pos = D3DXVECTOR3(-(PAUSE_POS_X2 / 2), -(PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;
	pVtx[9].pos = D3DXVECTOR3((PAUSE_POS_X2 / 2), -(PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;
	pVtx[10].pos = D3DXVECTOR3(-(PAUSE_POS_X2 / 2), (PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;
	pVtx[11].pos = D3DXVECTOR3((PAUSE_POS_X2 / 2), (PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;
	pVtx[12].pos = D3DXVECTOR3(-(PAUSE_POS_X3 / 2), -(PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;
	pVtx[13].pos = D3DXVECTOR3((PAUSE_POS_X3 / 2), -(PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;
	pVtx[14].pos = D3DXVECTOR3(-(PAUSE_POS_X3 / 2), (PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;
	pVtx[15].pos = D3DXVECTOR3((PAUSE_POS_X3 / 2), (PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;
	/*pVtx[16].pos = D3DXVECTOR3(-(PAUSE_POS_X4 / 2), -(PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;
	pVtx[17].pos = D3DXVECTOR3((PAUSE_POS_X4 / 2), -(PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;
	pVtx[18].pos = D3DXVECTOR3(-(PAUSE_POS_X4 / 2), (PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;
	pVtx[19].pos = D3DXVECTOR3((PAUSE_POS_X4 / 2), (PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;*/
	g_pVtxBuffPause->Unlock();
}

