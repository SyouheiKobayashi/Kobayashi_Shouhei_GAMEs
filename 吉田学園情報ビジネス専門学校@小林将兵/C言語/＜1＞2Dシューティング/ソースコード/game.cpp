//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//? �Q�[������ [game.cpp]
//? Kobayashi Syouhei / ���я���
//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "main.h"		//���C������
#include "game.h"		//�Q�[������
#include "player.h"		//�v���C���[����
#include "bg.h"			//�w�i����
#include "input.h"		//���͏���
#include "bullet.h"		//�e����
#include "explosion.h"	//��������
#include "enemy.h"		//�G����
#include "score.h"		//�X�R�A����
#include "effect.h"		//�G�t�F�N�g����
#include "fade.h"		//�t�F�[�h����
#include "sound.h"		//�T�E���h����
#include "pause.h"		//�|�[�Y����

//? ==================================================
//? �Q�[�� / �O���[�o���ϐ�
//? ==================================================
GAMESTATE g_gameState = GAMESTATE_NONE;	//�Q�[���̏��
int g_nCounterGameState;				//��ԊǗ��J�E���^�[
bool g_bPause;
//? ==================================================
//? �Q�[�� / ������
//? ==================================================
void InitGame(void)
{
	InitBG();
	InitScore();
	InitExplosion();
	InitBullet();
	InitEffect();
	InitEnemy();
	InitPlayer();
	InitPause();

	g_gameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_bPause = false;

	PlaySound(SOUND_GAME);

	//!+ <�G�̐�����>
	for (int nCnt = 0; nCnt<8; nCnt++)
	{
		SetEnemy(D3DXVECTOR3(330.0f+(90.0f*nCnt), 120.0f, 0.0f), 0);//�G�r
		SetEnemy(D3DXVECTOR3(300.0f + (90.0f*nCnt), 200.0f, 0.0f), 1);//�C�J
		SetEnemy(D3DXVECTOR3(330.0f + (90.0f*nCnt), 280.0f, 0.0f), 2);//��
		SetEnemy(D3DXVECTOR3(300.0f + (90.0f*nCnt), 360.0f, 0.0f), 3);//��
	}
}
//? ==================================================
//? �Q�[�� / �I��
//? ==================================================
void UninitGame(void)
{
	UninitBG();
	UninitScore();
	UninitExplosion();
	UninitBullet();
	UninitEffect();
	UninitEnemy();
	UninitPlayer();
	UninitPause();
	StopSound();
}
//? ==================================================
//�Q�[�� / �X�V
//? ==================================================
void UpdateGame(PLAYER * g_player)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	//�|�[�Y�̃I��/�I�t
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;
	}
	//�|�[�Y���̏���
	if (g_bPause == false)
	{
		UpdateBG();
		UpdateScore();
		UpdateExplosion();
		UpdateBullet();
		UpdateEffect();
		UpdateEnemy();
		UpdatePlayer();
	}
	else
	{
		UpdataPause();
	}

	if (pPlayer->bDisp == false)
	{
		if (GetKeyboardTrigger(DIK_RETURN))
		{
		//���[�h�I��
		SetMode(MODE_RESULT);
		}
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 120)//��ʐ؂�ւ��̗]�C / ����
		{
			//g_gameState = GAMESTATE_NORMAL;
			g_gameState = GAMESTATE_NONE;

			//���(���[�h)�̐ݒ�
			SetFade(MODE_RESULT);
		}
		break;
	}
}
//? ==================================================
//? �Q�[�� / �`��
//? ==================================================
void DrawGame(void)
{
	DrawBG();
	DrawScore();
	DrawExplosion();
	DrawBullet();
	DrawEffect();
	DrawEnemy();
	DrawPlayer();

	if (g_bPause == true)
	{
		DrawPause();
	}
}

//? ==================================================
//? �Q�[����Ԃ̐ݒ�
//? ==================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//? ==================================================
//? �Q�[����Ԃ̏���
//? ==================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}