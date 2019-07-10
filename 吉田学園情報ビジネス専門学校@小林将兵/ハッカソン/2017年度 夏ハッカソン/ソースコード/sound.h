//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
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
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_CHARGESHOT,	//�`���[�W�V���b�g
	SOUND_LABEL_SE_CHARGE,		// �`���[�W
	SOUND_LABEL_SE_HIT000,		// �q�b�g��0
	SOUND_LABEL_SE_HIT001,		// �q�b�g��1
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_SELECT,		//�I����
	SOUND_LABEL_SE_DECIDE,		// ���艹
	SOUND_LABEL_SE_VALCAN,		// �o���J��call
	SOUND_LABEL_SE_SPREAD,		// �X�v���b�hcall
	SOUND_LABEL_SE_CANON,		// �L���m��call
	SOUND_LABEL_SE_CANON2,		// �L���m��
	SOUND_LABEL_SE_SPREAD2,		// �X�v���b�h
	SOUND_LABEL_SE_OVERHEAT,	//�I�[�o�[�q�[�g
	SOUND_LABEL_SE_WARNINGS,	//�x����
	SOUND_LABEL_SE_CHARGE2,		//
	SOUND_LABEL_SE_SLASH,		//�X���b�V����
	SOUND_LABEL_SE_SLASH2,		//�X���b�V����2
	SOUND_LABEL_MAX
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
