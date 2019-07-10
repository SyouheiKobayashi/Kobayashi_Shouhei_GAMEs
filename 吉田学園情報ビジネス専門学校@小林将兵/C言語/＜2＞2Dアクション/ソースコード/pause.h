//=============================================================================
// ポーズの処理 [pause.h]
// Author:Kobayashi/小林 将兵
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	PAUSETYPE_CONTINUE = 0,
	PAUSETYPE_RETRY,
	//PAUSETYPE_QUIT,
	PAUSETYPE_MAX
}PAUSETYPE;
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 Initpos;// 初期位置
	D3DXCOLOR col;		// 色
	D3DXVECTOR3 move;	// 移動 
	int nType;			// 種類
	int nCounterAnim;	// カウンター
	int nPatternAnim;	// パターン
	bool bUse;			// 使用しているかどうか
} PAUSE;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
void SetPause(D3DXVECTOR3 pos, D3DXCOLOR col, int nType);
#endif

