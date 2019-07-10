//=============================================================================
//
// �Q�[����� [game.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//*****************************************************************************
// �\����
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,	//�������Ă��Ȃ����
	GAMESTATE_NORMAL,	//�ʏ���
	GAMESTATE_CLEAR,		//�I�����
	GAMESTATE_FAILED,		//�I�����
	GAMESTATE_MAX		//�ő吔
}GAMESTATE;

typedef struct
{
	bool bPause;
}PAUSECHECK;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGame(void);
void UnInitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetEnemyGame(void);

void SetGameState(GAMESTATE state);
GAMESTATE *GetGameState(void);
GAMESTATE *GetGameState2(void);

PAUSECHECK *GetPauseCheck(void);
#endif

