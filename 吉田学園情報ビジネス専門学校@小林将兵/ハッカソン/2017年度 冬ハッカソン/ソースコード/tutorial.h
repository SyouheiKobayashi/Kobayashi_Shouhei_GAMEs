//=============================================================================
//
// �`���[�g���A������ [tutorial.h]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	TUTORIALSTATE_NORMAL = 0,
	TUTORIALSTATE_MOVE_R,
	TUTORIALSTATE_MOVE_L,
	TUTORIALSTATE_MIDDLE,
	TUTORIALSTATE_END,
	TUTORIALSTATE_MAX
}TUTORIALSTATE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
	int nTransparent;
	int nType;
}TUTORIAL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

#endif