//==============================================================================
// �T�E���h���� [sound.h]
// Author:Kobayashi/���� ����
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=============================================================================
// �T�E���h�t�@�C��
//=============================================================================
typedef enum
{
	SOUND_LABEL_TITLE = 0,		// �^�C�g��
	SOUND_LABEL_GAME,			// �Q�[��
	SOUND_LABEL_RESULT,			// ���U���g
	SOUND_LABEL_SE_FALL,		// ������
	SOUND_LABEL_SE_HIT000,		// �q�b�g��0
	SOUND_LABEL_SE_HIT001,		// �q�b�g��1
	SOUND_LABEL_SE_COIN,	// �R�C����
	SOUND_LABEL_SE_DECIDE,		// ���艹
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
