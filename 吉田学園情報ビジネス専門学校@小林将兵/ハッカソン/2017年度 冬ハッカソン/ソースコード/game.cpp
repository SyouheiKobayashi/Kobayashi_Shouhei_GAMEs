//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#include "game.h"
#include "fade.h"
#include "input.h"
#include "pause.h"
#include "pausemenu.h"
#include "block.h"
#include "callout.h"
#include "snow.h"
#include "bg.h"
#include "statusbar.h"
#include "player.h"
#include "score.h"
#include "time.h"
#include "item.h"
#include "itemstate.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BLOCK_NUM		(15)		// �u���b�N�̐�

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
GAMESTATE g_gameState = GAMESTATE_NONE;	// �Q�[���̏��
int g_nCounterGameState;				// ��ԊǗ��̃J�E���^�[
PAUSECHECK g_bPause;
BlockInfo g_aBlockInfo[] =
{//SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);
	{ D3DXVECTOR3(530.0f, 320.0f, 0.0f), 50.0f, 50.0f, 0 },
	{ D3DXVECTOR3(750.0f, 320.0f, 0.0f), 50.0f, 50.0f, 3 },
	{ D3DXVECTOR3(530.0f, 500.0f, 0.0f), 50.0f, 50.0f, 2 },
	{ D3DXVECTOR3(750.0f, 500.0f, 0.0f), 50.0f, 50.0f, 1 },

	{ D3DXVECTOR3(230.0f, 320.0f, 0.0f), 50.0f, 50.0f, 0 },
	{ D3DXVECTOR3(750.0f, 320.0f, 0.0f), 50.0f, 50.0f, 3 },
	{ D3DXVECTOR3(850.0f, 500.0f, 0.0f), 50.0f, 50.0f, 2 },
	{ D3DXVECTOR3(1050.0f, 500.0f, 0.0f), 50.0f, 50.0f, 1 },

	{ D3DXVECTOR3(530.0f, 120.0f, 0.0f), 50.0f, 50.0f, 3 },
	{ D3DXVECTOR3(750.0f, 120.0f, 0.0f), 50.0f, 50.0f, 0 },
	{ D3DXVECTOR3(530.0f, 700.0f, 0.0f), 50.0f, 50.0f, 1 },
	{ D3DXVECTOR3(750.0f, 700.0f, 0.0f), 50.0f, 50.0f, 2 },

	{ D3DXVECTOR3(230.0f, 120.0f, 0.0f), 50.0f, 50.0f, 1 },
	{ D3DXVECTOR3(750.0f, 120.0f, 0.0f), 50.0f, 50.0f, 2 },
	{ D3DXVECTOR3(850.0f, 700.0f, 0.0f), 50.0f, 50.0f, 3 },
	{ D3DXVECTOR3(1050.0f, 700.0f, 0.0f), 50.0f, 50.0f, 0 },
};

ItemInfo g_aItemInfo[] =
{//SetItem(D3DXVECTOR3 pos, int nType);
	{ D3DXVECTOR3(635.0f, 410.0f, 0.0f), 0 },
	{ D3DXVECTOR3(200.0f, 250.0f, 0.0f), 0 },
	{ D3DXVECTOR3(235.0f, 610.0f, 0.0f), 0 },
	{ D3DXVECTOR3(1035.0f, 200.0f, 0.0f), 0 },
	{ D3DXVECTOR3(1200.0f, 700.0f, 0.0f), 0 },

};

//=============================================================================
// �Q�[������������
//=============================================================================
void InitGame(void)
{
	// �C�G�F�F�F
	InitBlock();
	for (int nCntBlock = 0; nCntBlock < sizeof g_aBlockInfo / sizeof(BlockInfo); nCntBlock++)
	{
		SetBlock(g_aBlockInfo[nCntBlock].pos, g_aBlockInfo[nCntBlock].fWidth, g_aBlockInfo[nCntBlock].fHeight, g_aBlockInfo[nCntBlock].nType);
	}

	InitItem();
	for (int nCntItem = 0; nCntItem < sizeof g_aItemInfo / sizeof(ItemInfo); nCntItem++)
	{
		SetItem(g_aItemInfo[nCntItem].pos, g_aItemInfo[nCntItem].nType);
	}

	// �����o��
	InitCallout();

	// ��
	InitSnow();

	// �v���C���[
	InitPlayer();

	// �w�i
	InitBG();

	// �X�e�[�^�X�o�[
	InitStatusBar();
	InitItemState();
	InitTime();
	InitScore();

	// �|�[�Y����������
	InitPause();

	// �|�[�Y���j���[����������
	InitPmenu();

	g_gameState = GAMESTATE_NORMAL;	// �ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;

	g_bPause.bPause = false;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	// ��
	UninitBlock();

	UninitItem();

	// �����o��
	UninitCallout();

	// ��
	UninitSnow();

	// �v���C���[
	UninitPlayer();

	// �w�i
	UninitBG();

	// �X�e�[�^�X
	UninitStatusBar();
	UninitItemState();
	UninitTime();
	UninitScore();

	// �|�[�Y�I������
	UninitPause();

	// �|�[�Y���j���[�I������
	UninitPmenu();
}

//=============================================================================
// �Q�[���X�V����
//=============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{// �|�[�YON/OFF
		g_bPause.bPause = g_bPause.bPause ? false : true;
	}

	if (g_bPause.bPause == false)
	{
		// �n�E�X
		UpdateBlock();

		UpdateItem();

		// �ӂ����[
		UpdateCallout();

		// �䂫
		UpdateSnow();

		// �v���C���[
		UpdatePlayer();

		// �w�i
		UpdateBG();

		// �X�e�[�^�X�o�[
		UpdateStatusBar();
		UpdateItemState();
		UpdateTime();
		UpdateScore();

	}
	else
	{
		// �|�[�Y�X�V����
		UpdatePause();
		
		// �|�[�Y���j���[�X�V����
		UpdatePmenu();
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;

			// ���(���[�h)�̐ݒ�
			//SetFade(MODE_GAMEOVER);
		}
		break;

	case GAMESTATE_CLEAR:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;

			// ���(���[�h)�̐ݒ�
			SetFade(MODE_RESULT);
		}
		break;
	}
}

//=============================================================================
// �Q�[���`�揈��
//=============================================================================
void DrawGame(void)
{
	//�w�i
	DrawBG();

	// ������
	DrawBlock();

	DrawItem();

	// �ӂ�����
	DrawCallout();

	// �R�I
	DrawSnow();

	// �v���C���[
	DrawPlayer();

	// �X�e�[�^�X�o�[
	DrawStatusBar();
	DrawItemState();
	DrawTime();
	DrawScore();

	if (g_bPause.bPause == true)
	{
		// �|�[�Y�`�揈��
		DrawPause();

		// �|�[�Y���j���[�`�揈��
		DrawPmenu();
	}
}

//=============================================================================
// �Q�[���̏�Ԃ̐ݒ�
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//=============================================================================
// �Q�[���̏�Ԃ̎擾
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//=============================================================================
// �|�[�Y��Ԃ̎擾
//=============================================================================
PAUSECHECK *GetPauseMenu(void)
{
	return &g_bPause;
}
