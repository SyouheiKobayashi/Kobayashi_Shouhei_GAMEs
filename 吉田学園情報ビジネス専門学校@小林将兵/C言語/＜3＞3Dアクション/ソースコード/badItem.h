//=============================================================================
// 障害物用モデル処理 [badItem.h]
// Author :Kobayashi/小林将兵//
//=============================================================================
#ifndef _BADITEM_H_
#define _BADITEM_H_

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
}BADITEM;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBadItem(void);
void UninitBadItem(void);
void UpdateBadItem(void);
void DrawBadItem(void);

void SetBadItem(D3DXVECTOR3 pos, D3DXVECTOR3 move);

void CollisionBadItem(D3DXVECTOR3 * pPos,		//自機の現在の位置
	D3DXVECTOR3 * pPosOld,	//自機のひとつ前の位置
	D3DXVECTOR3 * pMove,//自機の移動量
	D3DXVECTOR3 *pVtxMax,
	D3DXVECTOR3 *pVtxMin);	


BADITEM *GetBadItem(void);


#endif
