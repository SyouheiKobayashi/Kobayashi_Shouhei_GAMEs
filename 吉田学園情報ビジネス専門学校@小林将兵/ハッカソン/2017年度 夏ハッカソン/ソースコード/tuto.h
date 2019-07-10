//=============================================================================
//
// �Q�[����� [Tuto.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _TUTO_H_
#define _TUTO_H_

#include "main.h"

//*****************************************************************************
// �\����
//*****************************************************************************
typedef enum
{
	TUTOSTATE_NONE = 0,	//�������Ă��Ȃ����
	TUTOSTATE_NORMAL,	//�ʏ���
	TUTOSTATE_CLEAR,		//�I�����
	TUTOSTATE_FAILED,		//�I�����
	TUTOSTATE_MAX		//�ő吔
}TUTOSTATE;

typedef struct
{
	bool bPause;
}TUTOPAUSECHECK;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTuto(void);
void UnInitTuto(void);
void UpdateTuto(void);
void DrawTuto(void);

void SetTutoState(TUTOSTATE state);
TUTOSTATE *GetTutoState(void);
TUTOSTATE *GetTutoState2(void);

//TUTOPAUSECHECK *GetPauseCheck(void);
#endif

