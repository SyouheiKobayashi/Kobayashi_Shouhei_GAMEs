//=============================================================================
// ポリゴン処理 [meshWall.h]
// Author : Kobayashi/小林将兵
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//回転
	D3DXMATRIX mtxWorldWall;	//ワールドマトリックス

	bool bUse;
}MESHWALL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);

void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

#endif
