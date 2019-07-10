//=============================================================================
//
// プレイヤーの処理 [Player.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _PLAYER_H_			//	2重インクルード防止のマクロ定義
#define _PLAYER_H_

//*****************************************************************************
//構造体
//*****************************************************************************
typedef enum
{
	//PLAYERSTATE_APPEAR=0,		//出現状態（無敵）
	PLAYERSTATE_NOMAL = 0,		//通常ダメージ
	PLAYERSTATE_DAMAGE,			//ダメージ状態
	PLAYERSTATE_DEATH,		//死亡状態
	PLAYERSTATE_END,
	PLAYERSTATE_MAX
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	PLAYERSTATE state;
	int nCounterState;  //状態管理のカウンター
	int nCounterAnim;									//アニメーションカウンター
	int nPatternAnim;									//アニメーションパターンNo、
	int nLife;			//体力
	bool bDisp;			//表示するかしないか｜初期はtreu
	int nType;			//種類

	//bool bUse;			//使用されているかどうか
}Player;


//*****************************************************************************
//プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);		//初期化処理ポリゴン
void UninitPlayer(void);		//終了処理ポリゴン
void UpdatePlayer(void);	//更新処理ポリゴン
void DrawPlayer(void);		//描画処理ポリゴン
void HitPlayer(int nDamage);
void SetPlayer(D3DXVECTOR3 pos, int nType);
Player *GetPlayer(void);

#endif // !

