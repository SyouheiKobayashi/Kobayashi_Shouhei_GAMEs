//=============================================================================
//
// �Q�[������ [game.h]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "block.h"

#define SCREEN_HALF (SCREEN_WIDTH / 2)	// ��ʂ̔���

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,	// �������Ă��Ȃ����
	GAMESTATE_NORMAL,	// �ʏ���
	GAMESTATE_END,		// �Q�[���I�[�o�[
	GAMESTATE_CLEAR,	// �Q�[���N���A
	GAMESTATE_MAX
}GAMESTATE;

// �|�[�YON/OFF�̍\����
typedef struct
{
	bool bPause;
}PAUSECHECK;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

PAUSECHECK *GetPauseMenu(void); 

#endif