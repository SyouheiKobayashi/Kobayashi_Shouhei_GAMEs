//=============================================================================
// 入力処理 [input.h]
// Author:Kobayashi/小林 将兵
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);		//長押し
bool GetKeyboardTrigger(int nKey);		//単発押し


#endif