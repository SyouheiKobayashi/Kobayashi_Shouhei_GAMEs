//==============================================================================
// 自機・操作キャラの処理[player.h]
// Author:Kobayashi/小林 将兵
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//==============================================================================
// プレイヤー構造体
//==============================================================================
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//出現状態
	PLAYERSTATE_NORMAL,		//通常時状態
	PLAYERSTATE_DEATH,		//死亡状態
	//PLAYERSTATE_END,		//残機など
	PLAYERSTATE_MAX			//プレイヤーの状態の総数
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;//現在の位置
	D3DXVECTOR3 posOld;//前回 / ひとつ前の処理
	D3DXVECTOR3 move;//移動量
	
	PLAYERSTATE state;	//プレイヤーの状態
	int nCounterState;	//状態管理のカウンター

	int nDirectionMove;//自機が動いている方向

	bool bwait;//自機が待機しているか否か / 移動していない
	bool bJump;//空中にいるか否か / ジャンプしているか否か
	bool bTouch;
	bool bUse;
}Player;

//=============================================================================
//プロトタイプ宣言
//=============================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void); 
Player *GetPlayer(void);

#endif