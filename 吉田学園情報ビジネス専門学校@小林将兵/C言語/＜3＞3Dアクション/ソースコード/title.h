//=========================================================================
// タイトル画面の処理 [title.h]
// Author:Kobayashi/小林 将兵
//=========================================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "game.h"

typedef enum
{
	TITLE_0 = 0,//透明
	TITLE_1,//見える見える
	TITLE_MAX//最大数
}TITLE_STATE;//状態
//=========================================================================
//プロトタイプ宣言
//=========================================================================
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif