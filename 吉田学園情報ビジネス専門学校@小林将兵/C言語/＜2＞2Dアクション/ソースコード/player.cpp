//==============================================================================
// ���@�E����L�����̏���[player.cpp]
// Author:Kobayashi/���� ����
//=============================================================================
#include "main.h"
#include "sound.h"
#include "game.h"
#include "input.h"
#include "player.h"
#include "block.h"
#include "item.h"
#include "fade.h"
#include "score.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define PLAYER_SIZE (25)//���@�̑傫��
#define PLAYER_SPEED (0.8f)//���@�̑���
#define PLAYER_MAX_JUMP (2)//�ő�W�����v��
#define PLAYER_JUMP_POWER (14)//�W�����v�̍��� / �p���[
#define GRAVITY (1.0f)//�d��

//==============================================================================
//�O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;
//D3DXVECTOR3 g_player.pos.x; //�|���S���̈ʒu���
//D3DXVECTOR3 g_movePlayer; //�|���S���̈ړ��ʏ��
int g_jumpPlayer;//������W�����v�ϐ�

int SpeedAnimation;//�A�j���[�V�������x
int PatternAnimation;//�A�j���[�V�����̃p�^�[����
int TextureAnimation;//���E���]�\�����邽�߂̕ϐ�
int JumpAnimation;//�W�����v���̃e�N�X�`��

Player g_player;
Player *GetPlayer(void)
{
	return &g_player;
}

//==============================================================================
// �v���C���[�̏�����
//==============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	// �v���C���[�̏��̏�����
	g_player.pos = D3DXVECTOR3(50.0f, 630.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.state = PLAYERSTATE_NORMAL;//�v���C���[���
	g_player.nCounterState = 0;//�v���C���[�̏�ԊǗ�
	g_jumpPlayer = 0;
	SpeedAnimation = 0;
	PatternAnimation = 0;
	TextureAnimation = 0;
	JumpAnimation = 0;
	g_player.bwait = true;//�ҋ@ / �����Ă��邩�ۂ�
	g_player.bJump = false;//�W�����v / �󒆂��邩�ۂ�
	g_player.bUse = true; //true=�g�p���Ă��� / false=�g�p���Ă��Ȃ�

	//[�|���S���̈ʒu���]
	//g_player.pos.x = D3DXVECTOR3(290, 300, 0.0f); //�����ʒu
	//g_movePlayer = D3DXVECTOR3(0, 0, 0.0f);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\player000.png", &g_pTexturePlayer);

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

//�ʒu�@�摜�@rhw�@�F�̐ݒ�
#if 1
	//�ʒu
	/*pVtx[0].pos = D3DXVECTOR3(g_player.pos.x.x- PLAYER_SIZE, g_player.pos.x.y - PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x.x+ PLAYER_SIZE, g_player.pos.x.y - PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x.x- PLAYER_SIZE, g_player.pos.x.y + PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x.x+ PLAYER_SIZE, g_player.pos.x.y + PLAYER_SIZE, 0.0f);*/

	//�߂荞�񂾎��̃u���b�N�̊�ƂȂ� / �u���b�N�ɑ΂��锻��
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE, g_player.pos.y - PLAYER_SIZE*2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE, g_player.pos.y - PLAYER_SIZE*2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x+ PLAYER_SIZE, g_player.pos.y, 0.0f);

	//�摜
	//�����G
	/*pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);*/
	//�z�z�L����
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�F
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
#endif

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//==============================================================================
// �v���C���[�̏I��
//==============================================================================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
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

//==============================================================================
// �v���C���[�̍X�V
//==============================================================================
void UpdatePlayer(void)
{
	if (g_player.pos.y > SCREEN_HEIGHT + 50)//���@��������ʂ����ɗ������ꍇ
	{
		GAMESTATE pGameState; //game.cpp�ɂ���u�Q�[����Ԃ̎擾�v�����邽�߂�pGameState(�ϐ�)��p�ӂ���
		pGameState = GetGameState(); //pGameState(�ϐ�)��game.cpp�́u�Q�[����Ԃ̎擾�v�ɂ���g_gameState��������

		if (pGameState != GAMESTATE_END && pGameState == GAMESTATE_NORMAL)//GAMESTATE��NORMAL�̂Ƃ�
		{
			SetGameState(GAMESTATE_END);
		}
		g_player.bUse = false;//�g���Ȃ�����
		g_player.state = PLAYERSTATE_DEATH;//���S���
	}

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL://�ʏ펞�̏���
		break;

	case PLAYERSTATE_DEATH:
		break;
		
	}

	g_player.posOld = g_player.pos;//���݂̎��@�ʒu����posOld�ɕۑ����Ƃ�

	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

   //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	SpeedAnimation++;
	if ((SpeedAnimation % 8) == 0)
	{
		PatternAnimation = (PatternAnimation + 1) % 4;//�p�^�[��No.�X�V
	}
//-------------------
// ���@�̑���ݒ�
//-------------------
	//���C�ӂ̃L�[(D�L�[)�������ꂽ���ǂ��� / ���@�̉E�ړ��̏�����
	if (GetKeyboardPress(DIK_D) == true)
	{
		TextureAnimation = 0;//0�ɂ���
		g_player.bwait = false;//�ҋ@���Ă��Ȃ���Ԃɂ���
			g_player.move.x += PLAYER_SPEED;

			if (g_player.pos.x > SCREEN_WIDTH)//�X�N���[���O�ɏo���ꍇ�̏���
			{
				g_player.pos.x = 0;
			}

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			//�摜
			//�����G
			/*pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);*/
			//�z�z�L����
			/*pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);*/
			//�z�z�L�����A�j���[�V����
			pVtx[0].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 0.5f);
			pVtx[3].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 0.5f);
			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffPlayer->Unlock();
	}

	//���C�ӂ̃L�[(A�L�[)�������ꂽ���ǂ��� / ���@�̍��ړ��̏�����
	if (GetKeyboardPress(DIK_A) == true)
	{
		TextureAnimation = 1;//1�ɂ���
		g_player.bwait = false;//�ҋ@���Ă��Ȃ���Ԃɂ���
		g_player.move.x -= PLAYER_SPEED;

		if (g_player.pos.x < 0)//�X�N���[���O�ɏo���ꍇ�̏���
		{
			g_player.pos.x = SCREEN_WIDTH;
		}

		//if (g_player.pos.x < 25)//�X�N���[���O�ɏo���ꍇ�̏���
		//{
		//	g_player.pos.x = 25;
		//}

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		//�摜
		//�����G
		/*pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);*/
		//�z�z�L����
		/*pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);*/
		//�z�z�L�����A�j���[�V����(�������]D�L�[��0��1�A2��3���t�ɂ���)
		/*pVtx[0].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 0.5f);*/

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffPlayer->Unlock();
		
	}

	//���C�ӂ̃L�[(SPACE�L�[)�������ꂽ���ǂ��� / ���@�̃W�����v�̏�����
	if (g_player.bJump == false)
	{
		if (GetKeyboardTrigger(DIK_SPACE) == true)//�X�y�[�X��������&&�W�����v�͍ő�PLAYER_MAX_JUMP��܂�
		{
			PlaySound(SOUND_LABEL_SE_JUMP);//�W�����v��
			g_jumpPlayer++;
			g_player.move.y -= PLAYER_JUMP_POWER;//���@�̔�ԗ�
			g_player.bJump = true;
		}
	}
	g_player.move.y += GRAVITY;//�d�͉��Z

		g_player.pos.x += g_player.move.x;//���ړ�
		g_player.pos.y += g_player.move.y;//����

		
//---------------------------------------------------------------------
	//�ʒu�X�V(�ړ�)
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//����
	g_player.move.x += (0.0f - g_player.move.x)*0.2f;
	//g_movePlayer.y += (0.0f - g_movePlayer.y)*0.2f;

	/*g_player.pos = g_player.pos.x;
	g_player.move = g_movePlayer;*/

	if (CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, 0, 0) == true)
	{
		g_player.bJump = false;//�W�����v���Ă��Ȃ�
	}
	else
	{
		g_player.bJump = true;//�W�����v���Ă���
	}

//-------------------------------------------------------------------
//						�R�C�����_����
//-------------------------------------------------------------------
	if (CollisionItem(&g_player.pos, &g_player.posOld, &g_player.move, 0, 0) == true)
	{
		g_player.bTouch = false;//�G��Ă��Ȃ�
	}
	else
	{
		g_player.bTouch = true;//�G��Ă���
	}

	//���̍��� // S�L�[�������ꍇ����ȏ�A���ɍs�����Ȃ�����
	/*if (g_player.pos.y >= 650)
	{
		g_player.pos.y = 650;
		g_player.move.y = 0.0f;
		g_jumpPlayer = 0;
		g_player.bJump = false;
	}*/

	////�z�z�L�����A�j���[�V����
	//�ړ��L�[�������Ă��Ȃ��Ƃ��̏��� / �ҋ@����
	if (GetKeyboardPress(DIK_D) == false&& GetKeyboardPress(DIK_A) == false)
	{
		g_player.bwait = true;
		if (TextureAnimation == 0 && g_player.bwait == true)//�E
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);
		}
		if (TextureAnimation == 1 && g_player.bwait == true)//��
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.25f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);
		}

	}
	//�E�����̎��̃e�N�X�`���A�j���[�V�����\���̏���
	if (TextureAnimation == 0&& g_player.bwait == false)//�E
	{
		pVtx[0].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 0.5f);
	}
	//�������̎��̃e�N�X�`���A�j���[�V�����\���̏���
	if (TextureAnimation == 1&& g_player.bwait == false)//��
	{
		pVtx[0].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 0.5f);
		pVtx[1].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 1.0f);
	}

	//���_���W�̐ݒ� / ���@�̑傫��
	/*pVtx[0].pos = D3DXVECTOR3(g_player.pos.x.x - PLAYER_SIZE, g_player.pos.x.y - PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x.x + PLAYER_SIZE, g_player.pos.x.y - PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x.x - PLAYER_SIZE, g_player.pos.x.y + PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x.x + PLAYER_SIZE, g_player.pos.x.y + PLAYER_SIZE, 0.0f);*/

	//�߂荞�񂾎��̃u���b�N�̊�ƂȂ� / �u���b�N�ɑ΂��锻��(�X�V��)
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE, g_player.pos.y - PLAYER_SIZE * 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE, g_player.pos.y - PLAYER_SIZE * 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE, g_player.pos.y, 0.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//==============================================================================
// �v���C���[�̕`��
//==============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X����������
	pDevice = GetDevice();
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	if (g_player.bUse == true)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
