//=============================================================================
// 障害物用モデル処理 [item.h]
// Author :Kobayashi/小林将兵//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

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
	bool bUse;
	bool bTouch;
}ITEM;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move);

void CollisionItem(D3DXVECTOR3 * pPos,		//自機の現在の位置
	D3DXVECTOR3 * pPosOld,	//自機のひとつ前の位置
	D3DXVECTOR3 * pMove,//自機の移動量
	D3DXVECTOR3 *pVtxMax,
	D3DXVECTOR3 *pVtxMin);	


ITEM *GetItem(void);


#endif
