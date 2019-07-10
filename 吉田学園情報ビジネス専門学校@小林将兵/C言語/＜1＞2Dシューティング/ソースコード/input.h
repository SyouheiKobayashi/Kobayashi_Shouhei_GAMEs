//=============================================================================
//
// 入力処理 [input.h]
// Author :小林/ / Kobayashi
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);		//キャラの移動なら
bool GetKeyboardTrigger(int nKey);		//弾なら


#endif