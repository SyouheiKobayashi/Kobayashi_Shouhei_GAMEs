//? ◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//? ゲーム処理 [game.cpp]
//? Kobayashi Syouhei / 小林将兵
//? ◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "main.h"		//メイン処理
#include "game.h"		//ゲーム処理
#include "player.h"		//プレイヤー処理
#include "bg.h"			//背景処理
#include "input.h"		//入力処理
#include "bullet.h"		//弾処理
#include "explosion.h"	//爆発処理
#include "enemy.h"		//敵処理
#include "score.h"		//スコア処理
#include "effect.h"		//エフェクト処理
#include "fade.h"		//フェード処理
#include "sound.h"		//サウンド処理
#include "pause.h"		//ポーズ処理

//? ==================================================
//? ゲーム / グローバル変数
//? ==================================================
GAMESTATE g_gameState = GAMESTATE_NONE;	//ゲームの状態
int g_nCounterGameState;				//状態管理カウンター
bool g_bPause;
//? ==================================================
//? ゲーム / 初期化
//? ==================================================
void InitGame(void)
{
	InitBG();
	InitScore();
	InitExplosion();
	InitBullet();
	InitEffect();
	InitEnemy();
	InitPlayer();
	InitPause();

	g_gameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_bPause = false;

	PlaySound(SOUND_GAME);

	//!+ <敵の生成↓>
	for (int nCnt = 0; nCnt<8; nCnt++)
	{
		SetEnemy(D3DXVECTOR3(330.0f+(90.0f*nCnt), 120.0f, 0.0f), 0);//エビ
		SetEnemy(D3DXVECTOR3(300.0f + (90.0f*nCnt), 200.0f, 0.0f), 1);//イカ
		SetEnemy(D3DXVECTOR3(330.0f + (90.0f*nCnt), 280.0f, 0.0f), 2);//菌
		SetEnemy(D3DXVECTOR3(300.0f + (90.0f*nCnt), 360.0f, 0.0f), 3);//魚
	}
}
//? ==================================================
//? ゲーム / 終了
//? ==================================================
void UninitGame(void)
{
	UninitBG();
	UninitScore();
	UninitExplosion();
	UninitBullet();
	UninitEffect();
	UninitEnemy();
	UninitPlayer();
	UninitPause();
	StopSound();
}
//? ==================================================
//ゲーム / 更新
//? ==================================================
void UpdateGame(PLAYER * g_player)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	//ポーズのオン/オフ
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;
	}
	//ポーズ時の処理
	if (g_bPause == false)
	{
		UpdateBG();
		UpdateScore();
		UpdateExplosion();
		UpdateBullet();
		UpdateEffect();
		UpdateEnemy();
		UpdatePlayer();
	}
	else
	{
		UpdataPause();
	}

	if (pPlayer->bDisp == false)
	{
		if (GetKeyboardTrigger(DIK_RETURN))
		{
		//モード選択
		SetMode(MODE_RESULT);
		}
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 120)//画面切り替えの余韻 / 時間
		{
			//g_gameState = GAMESTATE_NORMAL;
			g_gameState = GAMESTATE_NONE;

			//画面(モード)の設定
			SetFade(MODE_RESULT);
		}
		break;
	}
}
//? ==================================================
//? ゲーム / 描画
//? ==================================================
void DrawGame(void)
{
	DrawBG();
	DrawScore();
	DrawExplosion();
	DrawBullet();
	DrawEffect();
	DrawEnemy();
	DrawPlayer();

	if (g_bPause == true)
	{
		DrawPause();
	}
}

//? ==================================================
//? ゲーム状態の設定
//? ==================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//? ==================================================
//? ゲーム状態の所得
//? ==================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}