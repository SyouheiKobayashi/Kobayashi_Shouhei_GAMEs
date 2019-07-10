//=============================================================================
// 障害物用モデル処理 [collisionModle.h]
// Author :Kobayashi/小林将兵//
//=============================================================================
#ifndef _COLLISIONMODEL_H_
#define _COLLISIONMODEL_H_

#include "main.h"

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//回転
	D3DXMATRIX mtxWorldCollision;	//ワールドマトリックス
	D3DXVECTOR3 VtxMin; //最小値
	D3DXVECTOR3 VtxMax;//最大値
	bool bUse;
}COLLISIONMODEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCollisionModle(void);
void UninitCollisionModle(void);
void UpdateCollisionModle(void);
void DrawCollisionModle(void);

void CollisionModel(D3DXVECTOR3 * pPos,		//自機の現在の位置
	D3DXVECTOR3 * pPosOld,	//自機のひとつ前の位置
	D3DXVECTOR3 * pMove,//自機の移動量
	D3DXVECTOR3 *pVtxMax,
	D3DXVECTOR3 *pVtxMin);	


COLLISIONMODEL *GetCollision(void);


#endif
