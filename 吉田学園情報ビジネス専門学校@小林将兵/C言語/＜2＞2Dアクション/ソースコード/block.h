//=============================================================================
// 床・壁、障害物等の処理 [block.h]
// Author:Kobayashi/小林 将兵
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_BLOCK	(255)	// ブロックの最大数

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動
	float fWidth;		//ブロックの幅
	float fHeight;		//ブロックの高さ
	int nBlockType;		//ブロックのタイプ分け
	bool bUse;			//使用してるか否か
	bool Determine;	//ブロック１つ一つの判定
}Block;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, int nBlockType);

bool CollisionBlock(D3DXVECTOR3 *pPos,		//自機の現在の位置
					D3DXVECTOR3 *pPosOld,	//自機のひとつ前の位置
					D3DXVECTOR3 * pMove,	//自機の移動量
					float fWidth,
					float fHeight);

Block *GetBlock(void);

#endif
