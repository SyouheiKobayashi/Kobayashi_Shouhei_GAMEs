//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// �T�E���h�t�@�C��
//*************************************
typedef enum
{
	SOUND_LABEL_TITLE000 = 0,		// BGM0
	SOUND_LABEL_GAME000,			// BGM1
	SOUND_LABEL_RANKING,			// BGM2
	SOUND_LABEL_TUTORIAL000,		// BGM4
	SOUND_LABEL_SE_DECIDE,			// ���艹
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
