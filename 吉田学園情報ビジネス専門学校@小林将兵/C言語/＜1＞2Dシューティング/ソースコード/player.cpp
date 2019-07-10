//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//? [Player.cpp]
//? Author : Kobayashi / ����
//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "game.h"
#include "sound.h"
//? ==================================================
//? �O���[�o���ϐ�
//? ==================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;

int g_nCountAnim; //�A�j���[�V�����J�E���^�[
int g_nPatternAnim;//�A�j���[�V�����p�^�[��No.
PLAYER g_player;

//? ==================================================
//? ������
//? ==================================================
void InitPlayer(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �v���C���[�̏��̏�����	
	g_player.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.state = PLAYERSTATE_NORMAL;
	g_player.nCounterState = 0;
	g_player.nLife = PLAYER_LIFE;
	g_player.bDisp = true;

	//�A�j���[�V����
	g_nCountAnim = 0;
	g_nPatternAnim = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\PLAYER\\player000.png", &g_pTexturePlayer);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-PLAYER_SIZE + g_player.pos.x, g_player.pos.y - PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PLAYER_SIZE + g_player.pos.x, g_player.pos.y - PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-PLAYER_SIZE + g_player.pos.x, g_player.pos.y + PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PLAYER_SIZE + g_player.pos.x, g_player.pos.y + PLAYER_SIZE, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//? ==================================================
//? �I��
//? ==================================================
void UninitPlayer(void)
{
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//? ==================================================
//? �X�V
//? ==================================================
void UpdatePlayer(void)
{
	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL://�ʏ펞�̏���
		break;

	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;//�ʏ��Ԏ�

		//[���_�J���[�̐ݒ�]
			VERTEX_2D *pVtx;
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_pVtxBuffPlayer->Unlock();
		}
		break;

	case PLAYERSTATE_DEATH:
		SetGameState(GAMESTATE_END);
		g_player.state = PLAYERSTATE_END;
		break;
	}

	//�A�j���[�V����
#if 0
	g_nCountAnim++; //�J�E���^�[�̉��Z
	if ((g_nCountAnim % 8) == 0)
	{
		g_nPatternAnim++;
		g_nPatternAnim = (g_nPatternAnim + 1) % 10;//�p�^�[��No.�X�V
	}
#endif
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//!+ <�e�̔��ˏ���>
	if (g_player.bDisp == true)
	{
		if (GetKeyboardTrigger(DIK_SPACE) == true)//�X�y�[�X�����Ă̒e�̎ˏo
		{
			PlaySound(SOUND_BULLET);
			SetBullet(g_player.pos, D3DXVECTOR3(0.0f, -11.0f, 0.0f), BULLETTYPE_PLAYER);//��
			SetBullet(g_player.pos, D3DXVECTOR3(-7.0f, -11.0f, 0.0f), BULLETTYPE_PLAYER);
			SetBullet(g_player.pos, D3DXVECTOR3(7.0f, -11.0f, 0.0f), BULLETTYPE_PLAYER);
		}
	}

	//!+ <�ړ��Ɋւ��鏈��>
	//��
	if (GetKeyboardPress(DIK_A) == true)
	{
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_player.move.x += sinf(-3.14f * 0.75f)*Player_Speed;
			g_player.move.y += cosf(-3.14f * 0.75f)*Player_Speed;
			if (g_player.pos.y < 20)
			{
				g_player.move.y = 0;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_player.move.x += sinf(-3.14f * 0.25f)*Player_Speed;
			g_player.move.y += cosf(-3.14f * 0.25f)*Player_Speed;
			if (g_player.pos.y > 670)//�E�B���h�E�̍��� - ���@�̍��� = 680
			{
				g_player.move.y = 0;
			}
		}
		else
		{
			g_player.move.x -= Player_Speed; //�|���S���̈ʒu�����Ɉړ�(����)
		}
		if (g_player.pos.x < 25)
		{
			g_player.move.x = 0;
		}
	}
	//�E
	else if (GetKeyboardPress(DIK_D) == true)
	{
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_player.move.x += sinf(3.14f * 0.75f)*Player_Speed;
			g_player.move.y += cosf(3.14f * 0.75f)*Player_Speed;
			if (g_player.pos.y < 20)
			{
				g_player.move.y = 0;
			}

		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_player.move.x += sinf(3.14f * 0.25f)*Player_Speed;
			g_player.move.y += cosf(3.14f * 0.25f)*Player_Speed;
			if (g_player.pos.y > 670)//�E�B���h�E�̍��� - ���@�̍��� = 680
			{
				g_player.move.y = 0;
			}
		}
		else
		{
			g_player.move.x += Player_Speed; //�|���S���̈ʒu���E�Ɉړ�
		}
		if (g_player.pos.x > 1255)
		{
			g_player.move.x = 0;
		}
	}

	//��
	else if (GetKeyboardPress(DIK_W) == true)
	{
		g_player.move.y -= Player_Speed; //�|���S���̈ʒu����Ɉړ�
		if (g_player.pos.y < 20)
		{
			g_player.move.y = 0;
		}
	}

	//��
	else if (GetKeyboardPress(DIK_S) == true)
	{
		g_player.move.y += Player_Speed; //�|���S���̈ʒu�����Ɉړ�
		if (g_player.pos.y > 670)//�E�B���h�E�̍��� - ���@�̍��� = 680
		{
			g_player.move.y = 0;
		}
	}

	//�ʒu�X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;
	//�΂߈ړ��X�V
	g_player.move.x += (0.0f - g_player.move.x)*0.2f;
	g_player.move.y += (0.0f - g_player.move.y)*0.2f;

#if 0
	/*pVtx[0].tex = D3DXVECTOR2(g_nPatternAnim*0.2f,          0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_nPatternAnim*0.2f + 0.2f,	0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnim*0.2f,          1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_nPatternAnim*0.2f + 0.2f,	1.0f);*/


	/*pVtx[0].tex = D3DXVECTOR2(g_nPatternAnim*0.2f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_nPatternAnim*0.2f + 0.2f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnim*0.2f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(g_nPatternAnim*0.2f + 0.2f, 0.5f);*/

	//[2�i]
	/*pVtx[0].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5),			0.5f*(g_nPatternAnim / 5));
	pVtx[1].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5) + 0.2f,		0.5f*(g_nPatternAnim / 5));
	pVtx[2].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5),			0.5f*(g_nPatternAnim / 5)+0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5) + 0.2f,		0.5f*(g_nPatternAnim / 5) + 0.5f);*/

	//[4�i]
	//pVtx[0].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5),		0.25f*(g_nPatternAnim / 5));
	//pVtx[1].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5) + 0.2f, 0.25f*(g_nPatternAnim / 5));
	//pVtx[2].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5),		0.25f*(g_nPatternAnim / 5) + 0.25f);
	//pVtx[3].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5) + 0.2f, 0.25f*(g_nPatternAnim / 5) + 0.25f);
#endif

	//���_���W�̐ݒ� / �傫��
	pVtx[0].pos = D3DXVECTOR3(-PLAYER_SIZE + g_player.pos.x, g_player.pos.y - PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PLAYER_SIZE + g_player.pos.x, g_player.pos.y - PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-PLAYER_SIZE + g_player.pos.x, g_player.pos.y + PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PLAYER_SIZE + g_player.pos.x, g_player.pos.y + PLAYER_SIZE, 0.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//? ==================================================
//? �`��
//? ==================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X����������
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_player.bDisp == true)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//? ==================================================
//? �v���C���[�̒ʏ�A�_���[�W���̕\������
//? ==================================================
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;
	if (g_player.nLife <= 0)//�̗͂�0�ȉ�
	{
		PlaySound(SOUND_EXPLOSION);
		SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_player.bDisp = false;
		g_player.state = PLAYERSTATE_DEATH;
		g_player.nCounterState = 60;
	}
	else//�_���[�W�̕\��
	{
		PlaySound(SOUND_EXPLOSION);
		g_player.state = PLAYERSTATE_DAMAGE;//�_���[�W��Ԏ�
		g_player.nCounterState = 5;//�_���[�W�p���̎���
	
		VERTEX_2D *pVtx;

		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		g_pVtxBuffPlayer->Unlock();
	}
}

//? ==================================================
//? �v���C���[�̒ʏ�A�_���[�W���̕\������
//? ==================================================
PLAYER *GetPlayer(void)
{
	return &g_player;
}