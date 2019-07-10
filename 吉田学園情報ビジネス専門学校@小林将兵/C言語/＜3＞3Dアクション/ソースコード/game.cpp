//=========================================================================
// �Q�[������ [game.cpp]
// Author:Kobayashi/���� ����
//=========================================================================
#include "main.h"
#include "sound.h"
#include "fade.h"
#include "game.h"
#include "stage.h"//�X�e�[�W�i�t�B�[���h�j
#include "layout.h"
#include "timer.h"
#include "score.h"
#include "camera.h"
#include "light.h"
#include "polygon.h"
#include "meshField.h"
#include "wall.h"
#include "meshWall.h"
#include "shadow.h"
#include "player.h"
#include "dummymodel.h"
#include "collisionModel.h"
#include "fallingRocks.h"
#include "item.h"
#include "badItem.h"
#include "billboard.h"
#include "bullet.h"
#include "effect.h"
#include "explosion.h"

//=============================================================================
//�}�N����`
//=============================================================================

//=========================================================================
//�Q�[�� / �O���[�o���ϐ�
//=========================================================================
GAMESTATE g_gameState = GAMESTATE_NONE;	//�Q�[���̏��
int g_nCounterGameState;				//��ԊǗ��J�E���^�[

//=========================================================================
//�Q�[�� / ������
//=========================================================================
void InitGame(void)
{
	int nCnt;

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// �X�e�[�W�̏���������
	InitStage();


	// �X�R�A�̏���������
	InitScore();

	// �|���S���̏���������
	InitPolygon();

	//���b�V���t�B�[���h�̏���������
	InitMeshField();

	// �ǂ̏���������
	InitWall();

	//���b�V���ǂ̏���������
	InitMeshWall();

	// �e�̏���������
	InitShadow();

	// ���f���̏���������
	InitPlayer();

	// �_�~�[�̏���������
	InitDummyModel();

	// �Փ˗p���f���̏���������
	InitCollisionModle();

	//���΂̏���������
	InitFallingRocks();

	// �A�C�e���̏���������
	InitItem();

	// ���_�A�C�e���̏���������
	InitBadItem();

	// �r���{�[�h�̏���������
	InitBillboard();

	// �e�̏���������
	InitBullet();

	// �G�t�F�N�g�̏���������
	InitEffect();

	//�g��������������
	InitExplosion();

	// �������Ԃ̏���������
	InitTimer();

	//���C�A�E�g�̏�����
	InitLayout();

	PlaySound(SOUND_LABEL_GAME);

	//+ �ǂ̔z�u
	//SetWall(D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0));
	//SetWall(D3DXVECTOR3(0, 0, -100), D3DXVECTOR3(0, D3DX_PI, 0));
	//SetWall(D3DXVECTOR3(100, 0, 0), D3DXVECTOR3(0, D3DX_PI/2, 0));
	//SetWall(D3DXVECTOR3(-100, 0, 0), D3DXVECTOR3(0, -D3DX_PI/2, 0));

	SetMeshWall(D3DXVECTOR3(0, 0, 100), D3DXVECTOR3(0, 0, 0));
	SetMeshWall(D3DXVECTOR3(500, 0, -600), D3DXVECTOR3(0, D3DX_PI, 0));
	SetMeshWall(D3DXVECTOR3(600, 0, 0), D3DXVECTOR3(0, D3DX_PI / 2, 0));
	SetMeshWall(D3DXVECTOR3(-100, 0, -500), D3DXVECTOR3(0, -D3DX_PI / 2, 0));

//���r���{�[�h�z�u
	SetBillboard(D3DXVECTOR3(0, 10, 0), D3DXVECTOR3(0, 0, 0), 0);
	SetBillboard(D3DXVECTOR3(-2000, 0, 420), D3DXVECTOR3(0, -D3DX_PI / 2, 0), 2);//�������
	SetBillboard(D3DXVECTOR3(1000, 0, 420), D3DXVECTOR3(0, -D3DX_PI / 2, 0), 2);//�������

// ���A�C�e���z�u	
	for (nCnt = 0; nCnt < 5; nCnt++)
	{ 
		SetItem(D3DXVECTOR3(-400.0f + (nCnt * 170), 15.0f, -2100 + (nCnt * 700)), D3DXVECTOR3(0.4f,0.0f,0.0f));
	}

// ��<�f�����b�g>�A�C�e���z�u	
	for (nCnt = 0; nCnt < 5; nCnt++)
	{
		SetBadItem(D3DXVECTOR3(-450.0f + (nCnt * 170), 15.0f, -2300 + (nCnt * 700)), D3DXVECTOR3(3.0f, 0.0f, 0.0f));
	}

// �����Δz�u	
	SetFallingRocks(D3DXVECTOR3(-300.0f, 800.0f, -2000), D3DXVECTOR3(10.0f, 0.0f, 0.0f),0);
	SetFallingRocks(D3DXVECTOR3(-200.0f, 800.0f, -1200), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 1);
	SetFallingRocks(D3DXVECTOR3(-100.0f, 800.0f, -400), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 2);
	SetFallingRocks(D3DXVECTOR3(0.0f, 800.0f, 400), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 3);
	SetFallingRocks(D3DXVECTOR3(100.0f, 800.0f, 1200), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 4);
	SetFallingRocks(D3DXVECTOR3(200.0f, 800.0f, 2000), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 5);
	SetFallingRocks(D3DXVECTOR3(300.0f, 800.0f, 2200), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 6);

// ���N���A�n�_�ڈ���	
	for (nCnt = 0; nCnt < 39; nCnt++)
	{
		SetEffect(D3DXVECTOR3(-430.0f+(nCnt*25), 20.0f, 2800.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5.0f, 1.0f);
	}

	g_gameState = GAMESTATE_NORMAL;	//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
}
//=========================================================================
//�Q�[�� / �I��
//=========================================================================
void UninitGame(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// �X�e�[�W�̏I������
	UninitStage();

	

	// �X�R�A�̏I������
	UninitScore();

	// �|���S���̏I������
	UninitPolygon();

	//���b�V���t�B�[���h�̏I������
	UninitMeshField();

	// �ǂ̏I������
	UninitWall();

	//���b�V���ǂ̏I������
	UninitMeshWall();

	// �e�̏I������
	UninitShadow();

	// ���f���̏I������
	UninitPlayer();

	// �_�~�[�̏I������
	UninitDummyModel();

	// �Փ˗p���f���̏I������
	UninitCollisionModle();

	//���΂̏I������
	UninitFallingRocks();

	// �A�C�e���̏I������
	UninitItem();

	// ���_�A�C�e���̏I������
	UninitBadItem();

	// �r���{�[�h�̏I������
	UninitBillboard();

	// �e�̏I������
	UninitBullet();

	// �G�t�F�N�g�̏I������
	UninitEffect();

	//�g�����I������
	UninitExplosion();

	// �������Ԃ̏I������
	UninitTimer();

	//���C�A�E�g�̏I������
	InitLayout();

	StopSound();
}
//=========================================================================
//�Q�[�� / �X�V
//=========================================================================
void UpdateGame(void)
{
	// ���C�g�̍X�V����
	UpdateLight();

	// �X�e�[�W�̍X�V����
	UpdateStage();

	
	// �X�R�A�̍X�V����
	UpdateScore();

	// �|���S���̍X�V����
	UpdatePolygon();

	//���b�V���t�B�[���h�̍X�V����
	UpdateMeshField();

	// �ǂ̍X�V����
	UpdateWall();

	//���b�V���ǂ̍X�V����
	UpdateMeshWall();

	// �e�̍X�V����
	UpdateShadow();

	// ���f���̍X�V����
	UpdatePlayer();

	// �J�����̍X�V����
	UpdateCamera();

	// �_�~�[�̍X�V����
	UpdateDummyModel();

	// �Փ˗p���f���̍X�V����
	UpdateCollisionModle();

	//���΂̍X�V����
	UpdateFallingRocks();

	// �A�C�e���̍X�V����
	UpdateItem();

	// ���_�A�C�e���̍X�V����
	UpdateBadItem();

	// �r���{�[�h�̍X�V����
	UpdateBillboard();

	// �e�̍X�V����
	UpdateBullet();

	// �G�t�F�N�g�̍X�V����
	UpdateEffect();

	//�g�����X�V����
	UpdateExplosion();

	// �������Ԃ̍X�V����
	UpdateTimer();

	//���C�A�E�g�̍X�V����
	UpdateLayout();

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;

	case GAMESTATE_CLEAR:
		g_nCounterGameState++;

		if (g_nCounterGameState >= 50)//��ʐ؂�ւ��̗]�C / ����
		{
			g_gameState = GAMESTATE_NONE;
			SetFade(MODE_CLEAR);
		}
		break;

		case GAMESTATE_END:
			g_nCounterGameState++;

			if (g_nCounterGameState >= 50)//��ʐ؂�ւ��̗]�C / ����
			{
				g_gameState = GAMESTATE_NONE;
				SetFade(MODE_RESULT);
			}
			break;
	}
}

//=========================================================================
//�Q�[�� / �`��
//=========================================================================
void DrawGame(void)
{
	// �J�����̐ݒ�
	SetCamera();

	// �X�e�[�W�̕`�揈��
	DrawStage();

	

	// �X�R�A�̕`�揈��
	//DrawScore();

	//���b�V���t�B�[���h�̕`�揈��
	//DrawMeshField();

	// �|���S���̕`�揈��
	//DrawPolygon();

	// �ǂ̕`�揈��
	DrawWall();

	// �e�̕`�揈��
	DrawShadow();

	//���b�V���ǂ̕`�揈��
	//DrawMeshWall();

	// ���f���̕`�揈��
	DrawPlayer();

	// �_�~�[�̕`�揈��
	//DrawDummyModel();

	// �Փ˗p���f���̕`�揈��
	//DrawCollisionModle();

	//���΂̕`�揈��
	DrawFallingRocks();

	// �A�C�e���̕`�揈��
	DrawItem();

	// ���_�A�C�e���̕`�揈��
	DrawBadItem();

	//�r���{�[�h�̕`�揈��
	DrawBillboard();

	// �e�̕`�揈��
	DrawBullet();

	// �G�t�F�N�g�̏���������
	DrawEffect();

	//�g�����`�揈��
	DrawExplosion();

	//���C�A�E�g�̕`�揈��
	DrawLayout();

	// �������Ԃ̕`�揈��
	DrawTimer();
}
//=========================================================================
//�Q�[����Ԃ̐ݒ�
//=========================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//=========================================================================
//�Q�[����Ԃ̎擾
//=========================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}