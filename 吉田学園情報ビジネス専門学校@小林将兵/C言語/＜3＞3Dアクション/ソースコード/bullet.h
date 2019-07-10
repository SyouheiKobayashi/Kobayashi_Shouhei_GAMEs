//=============================================================================
// 弾の処理 [bullet.h]
// Author : Kobayashi/小林将兵
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	int nLife;					//弾の寿命
	D3DXVECTOR3 pos;			//位置
	//D3DXVECTOR3 rot;			//回転
	D3DXVECTOR3 move;			//移動
	D3DXMATRIX mtxWorldBullet;	//ワールドマトリックス
	bool bUse;
}BULLET;

//typedef enum
//{
//	BULLETTYPE_PLAYER = 0,//プレイヤーの弾
//	//BULLETTYPE_ENEMY,	  //敵の弾
//	BULLETTYPE_MAX
//}BULLETTYPE;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);

#endif
