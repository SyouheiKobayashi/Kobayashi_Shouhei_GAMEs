//=============================================================================
//
// タイトル処理 [title.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _TITLE_H_			//	2重インクルード防止のマクロ定義
#define _TITLE_H_

//*****************************************************************************
//構造体
//*****************************************************************************
typedef enum
{
	TITLE_NOMAL = 0,		//通常
	TITLE_END,
	TITLE_MAX
}TITLESTATE;
//*****************************************************************************
//プロトタイプ宣言
//*****************************************************************************
void InitTitle(void);		//初期化処理タイトル
void UninitTitle(void);		//終了処理タイトル
void UpdateTitle(void);		//更新処理タイトル
void DrawTitle(void);		//描画処理タイトル

#endif // !
