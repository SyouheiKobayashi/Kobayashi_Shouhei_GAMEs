//=============================================================================
// 障害物用モデル処理 [fallingRocks.h]
// Author :Kobayashi/小林将兵//
//=============================================================================
#ifndef _FALLINGROCKS_H_
#define _FALLINGROCKS_H_

#include "main.h"

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 move;			//移動
	D3DXVECTOR3 rot;			//回転
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXVECTOR3 VtxMin; //最小値
	D3DXVECTOR3 VtxMax;//最大値
	int nType;
	bool bUse;
	bool bTouch;
}FALLINGROCKS;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitFallingRocks(void);
void UninitFallingRocks(void);
void UpdateFallingRocks(void);
void DrawFallingRocks(void);

void SetFallingRocks(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType);

void CollisionFallingRocks(D3DXVECTOR3 * pPos,		//自機の現在の位置
	D3DXVECTOR3 * pPosOld,	//自機のひとつ前の位置
	D3DXVECTOR3 * pMove,//自機の移動量
	D3DXVECTOR3 *pVtxMax,
	D3DXVECTOR3 *pVtxMin);	


FALLINGROCKS *GetFallingRocks(void);


#endif
