//? ◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//? 敵処理 [enemy.h]
//? Author :小林 / Kobayashi
//? ◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//? ==================================================
//? マクロ定義
//? ==================================================
#define	ENEMY_MAX	(256)	// 敵の最大数
#define	ENEMY_TYPE		(4)						// 敵の種類
#define ENEMY_INTERVAL	(90)//攻撃間隔
#define ENEMY_SIZE	(20)

//? ==================================================
//? 構造体定義
//? ==================================================
//列挙型
typedef enum
{
	ENEMYSTATE_NORMAL=0,	//通常時状態
	ENEMYSTATE_DAMAGE,		//ダメージ時状態
	ENEMYSTATE_MAX			//敵の状態の総数
}ENEMYSTATE;

typedef enum
{
	MOVE_L  = 0,
	MOVE_R,
	MOVE_MAX
}MOVE;

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動
	int nType;			//種類
	ENEMYSTATE state;	//敵の状態
	int nCounterState;	//状態管理のカウンター
	int nLife;			//体力
	int nPatternAnimE;
	int nCountAnimE;
	bool bUse;			//使用してるか否か
}ENEMY;

//? ==================================================
//? プロトタイプ宣言
//? ==================================================
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

void SetEnemy(D3DXVECTOR3 pos, int nType);
ENEMY *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif
