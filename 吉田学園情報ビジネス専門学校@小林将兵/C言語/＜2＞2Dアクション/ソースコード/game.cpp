//=========================================================================
// ゲーム処理 [game.cpp]
// Author:Kobayashi/小林 将兵
//=========================================================================
#include "main.h"		//メイン処理
#include "sound.h"		//サウンド処理
#include "pause.h"		//ポーズ処理
#include "game.h"		//ゲーム処理
#include "bg.h"			//背景処理
#include "fade.h"
#include "input.h"		//入力処理
#include "player.h"		//プレイヤー処理
#include "block.h"
#include "item.h"
#include "explosion.h"
#include "timer.h"
#include "score.h"		//スコア処理

//=============================================================================
// マクロ定義
//=============================================================================
#define UPYUKA_SPEED (-2.0f)//↑スピード
#define DOWNYUKA_SPEED (0.7f)//↓スピード
#define HIDARI_SPEED (-2.0f)//←スピード

//=========================================================================
//ゲーム / グローバル変数
//=========================================================================
GAMESTATE g_gameState = GAMESTATE_NONE;	//ゲームの状態
int g_nCounterGameState;				//状態管理カウンター
bool g_bPause;//ポーズ処理

Block g_BlockP[MAX_BLOCK];
Block *GetBlockP(void)
{
	return &g_BlockP[MAX_BLOCK];
}
//=========================================================================
//ゲーム / 初期化
//=========================================================================
void InitGame(void)
{
	InitBG();
	InitBlock();
	InitPlayer();
	InitItem();
	InitExplosion();
	InitTimer();
	InitScore();
	InitPause();

	PlaySound(SOUND_LABEL_GAME);

//-----------------------------------------------------------------------------
//ブロックの配置情報
//-----------------------------------------------------------------------------
	int nCntI;//アイテム用

	//★基礎床
	//		　位置							　移動							幅		高
	SetBlock(D3DXVECTOR3(-100.0f, 670.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 590.0f, 50.0f, 0);
	//SetBlock(D3DXVECTOR3(470.0f, 670.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 50.0f, 1);//穴ふさぎ
	SetBlock(D3DXVECTOR3(570.0f, 670.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 610.0f, 50.0f, 0);//右側画面用外含む
	//SetBlock(D3DXVECTOR3(-100.0f, 670.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 50.0f, 0);//左側画面用(100.0f分)

	
	//壁
	SetBlock(D3DXVECTOR3(350.0f, 150.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25.0f, 520.0f, 0);
	SetBlock(D3DXVECTOR3(450.0f, 165.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25.0f, 180.0f, 0);
	SetBlock(D3DXVECTOR3(550.0f, 55.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25.0f, 270.0f, 0);

	//床
	SetBlock(D3DXVECTOR3(227.0f, 488.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 380.0f, 25.0f, 0);//横
	SetBlock(D3DXVECTOR3(707.0f, 488.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 165.0f, 25.0f, 0);//横
	SetBlock(D3DXVECTOR3(0.0f, 385.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 105.0f, 25.0f, 0);//横
	SetBlock(D3DXVECTOR3(130.0f, 238.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 580.0f, 25.0f, 0);//横
	SetBlock(D3DXVECTOR3(1150.0f, 238.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 130.0f, 25.0f, 0);//横

	//移動床
	SetBlock(D3DXVECTOR3(607.0f, 488.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 25.0f, 3);//沈む床
	SetBlock(D3DXVECTOR3(1180.0f, 670.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 25.0f, 5);//沈む床
	SetBlock(D3DXVECTOR3(880.0f, 238.0f, 0), D3DXVECTOR3(HIDARI_SPEED, 0.0f, 0.0f), 100.0f, 25.0f, 6);//横移動
	SetBlock(D3DXVECTOR3(450.0f, 175.0f, 0), D3DXVECTOR3(0.0f, -2.0f, 0.0f), 25.0f, 160.0f, 4);//移動壁

//★基礎床
#if 0
	//		　位置							　移動							幅		高さ
	SetBlock(D3DXVECTOR3(100.0f, 530.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 220.0f, 0);
	SetBlock(D3DXVECTOR3(150.0f, 530.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 220.0f, 0);
	SetBlock(D3DXVECTOR3(200.0f, 550.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 205.0f, 50.0f, 1);
	SetBlock(D3DXVECTOR3(250.0f, 600.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 200.0f, 2);
	SetBlock(D3DXVECTOR3(395.0f, 480.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 250.0f, 0);
	SetBlock(D3DXVECTOR3(445.0f, 480.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 250.0f, 0);
	SetBlock(D3DXVECTOR3(495.0f, 550.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 130.0f, 120.0f, 3);
	SetBlock(D3DXVECTOR3(615.0f, 380.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 250.0f, 0);
	SetBlock(D3DXVECTOR3(665.0f, 380.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 250.0f, 0);
	SetBlock(D3DXVECTOR3(615.0f, 630.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 250.0f, 0);
	SetBlock(D3DXVECTOR3(665.0f, 630.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 250.0f, 0);
	SetBlock(D3DXVECTOR3(715.0f, 500.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 130.0f, 120.0f, 3);
	SetBlock(D3DXVECTOR3(835.0f, 550.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 250.0f, 0);
	SetBlock(D3DXVECTOR3(885.0f, 550.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 250.0f, 0);
	SetBlock(D3DXVECTOR3(835.0f, 300.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 250.0f, 0);
	SetBlock(D3DXVECTOR3(885.0f, 300.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 250.0f, 0);
	SetBlock(D3DXVECTOR3(935.0f, 300.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 100.0f, 0);
	SetBlock(D3DXVECTOR3(935.0f, 630.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 100.0f, 0);
	SetBlock(D3DXVECTOR3(985.0f, 300.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 100.0f, 0);
#endif
	//上移動用
	//SetBlock(D3DXVECTOR3(1035.0f, 450.0f, 0), D3DXVECTOR3(0.0f, UPYUKA_SPEED-1.0f, 0.0f), 100.0f, 50.0f, 4);
	//SetBlock(D3DXVECTOR3(1135.0f, 600.0f, 0), D3DXVECTOR3(0.0f, UPYUKA_SPEED, 0.0f), 100.0f, 50.0f, 5);

	////左移動床
	//SetBlock(D3DXVECTOR3(1085.0f, 150.0f, 0), D3DXVECTOR3(HIDARI_SPEED, 0.0f, 0.0f), 150.0f, 50.0f, 6);


	
//-----------------------------------------------------------------------------
//アイテムの配置情報
//-----------------------------------------------------------------------------
	for (nCntI = 0; nCntI < 6; nCntI++)
	{
	SetItem(D3DXVECTOR3(80.0f+(nCntI*45.0f), 620.0f, 0.0f), 0);
	}
	for (nCntI = 0; nCntI < 7; nCntI++)
	{
		SetItem(D3DXVECTOR3(550.0f + (nCntI * 45.0f), 620.0f, 0.0f), 0);
	}
	for (nCntI = 0; nCntI < 7; nCntI++)
	{
		SetItem(D3DXVECTOR3(920.0f + (nCntI * 45.0f), 620.0f, 0.0f), 0);
	}
	for (nCntI = 0; nCntI < 3; nCntI++)
	{
		SetItem(D3DXVECTOR3(210.0f + (nCntI * 45.0f), 430.0f, 0.0f), 0);
	}
	for (nCntI = 0; nCntI < 4; nCntI++)
	{
		SetItem(D3DXVECTOR3(170.0f, 430.0f +(nCntI*50.0f) , 0.0f), 0);
	}

	SetItem(D3DXVECTOR3(10, 20, 0), 1);
	SetItem(D3DXVECTOR3(385, 258, 0), 1);
	SetItem(D3DXVECTOR3(385, 538, 0), 1);
	SetItem(D3DXVECTOR3(1000, 10, 0), 1);
	SetItem(D3DXVECTOR3(1060, 260, 0), 1);
	SetItem(D3DXVECTOR3(760, 260, 0), 1);
	SetItem(D3DXVECTOR3(1200, 178, 0), 1);
	SetItem(D3DXVECTOR3(300.0f, 520.0f, 0), 1);
	SetItem(D3DXVECTOR3(300.0f, 270.0f, 0), 1);

	//危険物
	SetItem(D3DXVECTOR3(385, 185, 0), 2);
	SetItem(D3DXVECTOR3(485, 185, 0), 2);
	SetItem(D3DXVECTOR3(585, 185, 0), 2);
	SetItem(D3DXVECTOR3(870, 615, 0), 2);

	SetPause(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f), 0);			// 背景
	SetPause(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), 1);			// ポーズ土台
	SetPause(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2);// Continue
	SetPause(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3);			// retry
	//SetPause(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 130.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 4);// Quit

	g_gameState = GAMESTATE_NORMAL;	//通常状態に設定
	g_nCounterGameState = 0;
	g_bPause = false;
}
//=========================================================================
//ゲーム / 終了
//=========================================================================
void UninitGame(void)
{
	UninitBG();
	UninitBlock();
	UninitPlayer();
	UninitItem();
	UninitExplosion();
	UninitTimer();
	UninitScore();
	UninitPause();

	StopSound();
}
//=========================================================================
//ゲーム / 更新
//=========================================================================
void UpdateGame(void)//順番の違いでエラーが起こる
{
	

	//ポーズのオン/オフ
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;
	}
	//ポーズ時の処理
	if (g_bPause == false)
	{
		UpdateBG();
		UpdateBlock();
		UpdatePlayer();
		UpdateItem();
		UpdateExplosion();
		UpdateTimer();
		UpdateScore();
	}
	else
	{
		UpdatePause();
	}
	//FADE pFade;
	//pFade = *GetFade();
	
	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;

	case GAMESTATE_END:
		g_nCounterGameState++;

		if (g_nCounterGameState >= 50)//画面切り替えの余韻 / 時間
		{
			//g_gameState = GAMESTATE_NORMAL;
			g_gameState = GAMESTATE_NONE;
				//画面(モード)の設定
				SetFade(MODE_RESULT);
		}
		break;

	case GAMESTATE_CLEAR:
		g_nCounterGameState++;

		if (g_nCounterGameState >= 50)//画面切り替えの余韻 / 時間
		{
			//g_gameState = GAMESTATE_NORMAL;
			g_gameState = GAMESTATE_NONE;
			//画面(モード)の設定
			SetFade(MODE_CLEAR);
		}
		break;
	}
}
//=========================================================================
//ゲーム / 描画
//=========================================================================
void DrawGame(void)
{
	DrawBG();
	DrawBlock();
	DrawPlayer();
	DrawItem();
	DrawExplosion();
	DrawTimer();
	DrawScore();
	if (g_bPause == true)
	{
		DrawPause();
	}
}

//=========================================================================
//ゲーム状態の設定
//=========================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//=========================================================================
//ゲーム状態の取得
//=========================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//=============================================================================
// ポーズ状態を変える
//=============================================================================
void ReleaseGamePause(void)
{
	g_bPause = g_bPause ? false : true;
}