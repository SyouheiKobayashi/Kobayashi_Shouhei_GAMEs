//=========================================================================
// チュートリアル処理 [tutorial.h]
// Author:Kobayashi/小林 将兵
//=========================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_


typedef enum
{
	TUTORIAL_0 = 0,//透明
	TUTORIAL_1,//見える見える
	TUTORIAL_MAX//最大数
}TUTORIAL_STATE;//状態
//=========================================================================
//プロトタイプ宣言
//=========================================================================
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

#endif