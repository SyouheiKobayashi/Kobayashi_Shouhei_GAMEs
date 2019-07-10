//==============================================================================
// サウンド処理 [sound.h]
// Author:Kobayashi/小林 将兵
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=============================================================================
// サウンドファイル
//=============================================================================
typedef enum
{
	SOUND_LABEL_TITLE = 0,		// タイトル
	SOUND_LABEL_GAME,			// ゲーム
	SOUND_LABEL_RESULT,			// リザルト
	SOUND_LABEL_SE_FALL,		// 落下音
	SOUND_LABEL_SE_HIT000,		// ヒット音0
	SOUND_LABEL_SE_HIT001,		// ヒット音1
	SOUND_LABEL_SE_COIN,	// コイン音
	SOUND_LABEL_SE_DECIDE,		// 決定音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
