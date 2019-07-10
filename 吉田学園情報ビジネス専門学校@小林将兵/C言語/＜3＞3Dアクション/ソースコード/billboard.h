//=============================================================================
// ポリゴン処理 [billboard.h]
// Author : Kobayashi/小林将兵
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//回転軸
	D3DXMATRIX mtxWorldBillboard;	//ワールドマトリックス
	int nType;
	bool bUse;
}BILLBOARD;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);

void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType);

#endif
