//=============================================================================
// アイテム処理 [item.h]
// Author:Kobayashi/小林 将兵
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_ITEM	(255)	//アイテムの最大数

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	float fWidth;		//ブロックの幅
	float fHeight;		//ブロックの高さ
	int nItemType;		//アイテムのタイプ分け
	int SpeedAnimation;
	int PatternAnimation;
	bool bUse;			//表示するか否か
	bool bTouch; //触れているか否か
}Item;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

void SetItem(D3DXVECTOR3 pos, int nItemType);

Item *GetItem(void);

bool CollisionItem(D3DXVECTOR3 *pPos,//アイテムの現在の位置
	D3DXVECTOR3 *pPosOld,	//アイテムのひとつ前の位置
	D3DXVECTOR3 * pMove,	//アイテムの移動量
	float fWidth,
	float fHeight);

#endif
