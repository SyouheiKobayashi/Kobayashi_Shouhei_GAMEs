//? ◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//? [Player.h]
//? Author : Kobayashi / 小林
//? ◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _PLAYER_H_
#define _PLAYER_H_

//? ==================================================
//? マクロ定義
//? ==================================================
#define PLAYER_SIZE	(20)
#define PLAYER_LIFE	(22)
#define Player_Speed	(2.0f)			// ポリゴンの速度

//? ==================================================
//? 構造体
//? ==================================================
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//出現状態
	PLAYERSTATE_NORMAL,		//通常時状態
	PLAYERSTATE_DAMAGE,		//ダメージ時状態
	PLAYERSTATE_DEATH,		//死亡状態
	PLAYERSTATE_END,
	PLAYERSTATE_MAX			//プレイヤーの状態の総数
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	PLAYERSTATE state;	//プレイヤーの状態
	int nCounterState;	//状態管理のカウンター
	int nLife;			//体力
	bool bDisp;			//表示するか否か
}PLAYER;

//? ==================================================
//? プロトタイプ宣言
//? ==================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
void HitPlayer(int nDamage);
#endif
