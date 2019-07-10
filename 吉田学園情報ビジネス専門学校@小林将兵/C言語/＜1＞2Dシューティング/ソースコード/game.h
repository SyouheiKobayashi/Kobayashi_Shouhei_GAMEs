//? ◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//? ゲーム処理 [game.h]
//? Kobayashi Syouhei / 小林将兵
//? ◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "player.h"
//? ==================================================
//? 構造体
//? ==================================================
//[ゲームの状態]
typedef enum
{
	GAMESTATE_NONE = 0,		//何もしていない状態
	GAMESTATE_NORMAL,		//通常状態
	GAMESTATE_END,			//終了状態
	GAMESTATE_MAX,			//ゲーム状態の最大数
}GAMESTATE;
//? ==================================================
//? プロトタイプ宣言
//? ==================================================
void InitGame(void);
void UninitGame(void);
void UpdateGame(PLAYER * g_player);
void DrawGame(void);

void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);
#endif