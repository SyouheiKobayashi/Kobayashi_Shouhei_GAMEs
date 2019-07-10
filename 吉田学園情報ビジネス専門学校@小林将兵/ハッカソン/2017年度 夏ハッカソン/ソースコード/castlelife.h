//=============================================================================
//
// 城体力処理 [castlelife.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _CASTELIFE_H_
#define _CASTLELIFE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_CASTLELIFE	(128)	// ポーズの最大数



//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXCOLOR col;
	bool bUse;			//使用しているかどうか
	int nType;
}CASTLELIFE;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCastleLife(void);
void UnInitCastleLife(void);
void UpdateCastleLife(void);
void DrawCastleLife(void);


void HitCastle(int nDamage);

//void SetPause(D3DXVECTOR3 pos, int nType, float fSpeed);

#endif