//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : komatsu
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "sound.h"
#include "time.h"
#include "fade.h"
#include "game.h"
#include "item.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define PLAYER_TEXTURENAME	"data/TEXTURE/player000.png"	//�\������t�@�C���̖��O
#define PLAYER_POS_X		(30.0f)							//�v���C���[��X�̒���
#define PLAYER_POS_Y		(30.0f)							//�v���C���[��Y�̒���
#define MAX_PATTERN			(4)								//�p�^�[���̐�
#define TEXTURE_UPDATE		(20)							//�A�j���[�V�������x
#define MOVE_SPEED			(2.0f)							//�ړ����x
#define TEX_X				(0.25f)							//�e�N�X�`����X
#define TEX_Y				(0.25f)							//�e�N�X�`����Y

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Player g_player;									//�v���C���[�̏��

//=============================================================================
// �|���S������������
//=============================================================================
void InitPlayer(void)
{
	VERTEX_2D *pVtx;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	g_player.nCounterAnim = 0;							//�J�E���^��������
	g_player.nPatternAnim = 0;							//�p�^�[��No.��������
	g_player.nDirectionMove = 0;						//������������
	g_player.fHeight = PLAYER_POS_Y * 2;				//������������
	g_player.fWidth = PLAYER_POS_X;						//����������
	g_player.pos = D3DXVECTOR3(340.0f, 200.0f, 0.0f);	//�J�n�ʒu�̐ݒ�
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��ʒu�̏�����
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏�����
	g_player.bChange = false;
	g_player.bItem = false;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURENAME, &g_pTexturePlayer);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffPlayer,
								NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y, g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y, g_player.pos.z);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TEX_X, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TEX_Y);
	pVtx[3].tex = D3DXVECTOR2(TEX_X, TEX_Y);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer-> Release();
		g_pTexturePlayer = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;					//���_�o�b�t�@�ւ̃|�C���^
	TIME pTime = GetTime();			//�^�C�������擾
	g_player.posOld = g_player.pos;		//�O��ʒu�̕ۑ�
	g_player.nCounterAnim++;			//�J�E���^���Z

	//���_�o�b�t�@�����b�N
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (pTime.nTime > 0)
	{
		if (GetKeyboardPress(DIK_W) == true)	//W�L�[
		{//��ړ�
			g_player.move.y -= MOVE_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)	//S�L�[
		{//���ړ�
			g_player.move.y += MOVE_SPEED;
		}
		else if (GetKeyboardPress(DIK_A) == true)	//A�L�[
		{//���ړ�
			g_player.move.x -= MOVE_SPEED;		
		}
		else if (GetKeyboardPress(DIK_D) == true)	//D�L�[
		{//�E�ړ�
			g_player.move.x += MOVE_SPEED;
		}
	}

	if (pTime.nTime > 0)
	{
		//�e�N�X�`��
		if (GetKeyboardPress(DIK_W) == true)
		{//��ړ�(�n��)
			if ((g_player.nCounterAnim % TEXTURE_UPDATE) == 0)	//�J�E���^�[������
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1 % MAX_PATTERN);
			}
			g_player.nDirectionMove = 1;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//���ړ�(�n��)
			if ((g_player.nCounterAnim % TEXTURE_UPDATE) == 0)	//�J�E���^�[������
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1 % MAX_PATTERN);
			}
			g_player.nDirectionMove = 0;
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{//���ړ�(�n��)
			if ((g_player.nCounterAnim % TEXTURE_UPDATE) == 0)	//�J�E���^�[������
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1 % MAX_PATTERN);
			}
			g_player.nDirectionMove = 2;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//�E�ړ�(�n��)
			if ((g_player.nCounterAnim % TEXTURE_UPDATE) == 0)	//�J�E���^�[������
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1 % MAX_PATTERN);
			}
			g_player.nDirectionMove = 3;
		}
		else if (g_player.nPatternAnim != 0)
		{//�e�N�X�`�����W��0�ɖ߂�
			if ((g_player.nCounterAnim % TEXTURE_UPDATE) == 0)	//�J�E���^�[������
			{
				g_player.nPatternAnim = 0;
			}
		}
	}

	//�e�N�X�`���X�V
	pVtx[0].tex = D3DXVECTOR2(TEX_X * (g_player.nPatternAnim % MAX_PATTERN), 0.25f * g_player.nDirectionMove);
	pVtx[1].tex = D3DXVECTOR2(TEX_X * (g_player.nPatternAnim % MAX_PATTERN) + TEX_X, 0.25f * g_player.nDirectionMove);
	pVtx[2].tex = D3DXVECTOR2(TEX_X * (g_player.nPatternAnim % MAX_PATTERN), 0.25f * g_player.nDirectionMove + 0.25f);
	pVtx[3].tex = D3DXVECTOR2(TEX_X * (g_player.nPatternAnim % MAX_PATTERN) + TEX_X, 0.25f * g_player.nDirectionMove + 0.25f);

	//�ʒu�X�V
	g_player.pos += g_player.move;

	//��ʒ[
	if (g_player.pos.y < g_player.fHeight + 80.0f)
	{//��[
		g_player.pos.y = g_player.fHeight + 80.0f;
		g_player.move.y = 0.0f;
	}
	else if (g_player.pos.y > SCREEN_HEIGHT)
	{//���[
		g_player.pos.y = SCREEN_HEIGHT;
		g_player.move.y = 0.0f;
	}
	if (g_player.pos.x < g_player.fWidth)
	{//���[
		g_player.pos.x = 0.0f + g_player.fWidth;
		g_player.move.x = 0.0f;
	}
	else if (g_player.pos.x >= SCREEN_WIDTH - g_player.fWidth)
	{//�E�[
		g_player.pos.x = SCREEN_WIDTH - g_player.fWidth;
		g_player.move.x = 0.0f;
	}

	//����
	g_player.move.x += (0.0f - g_player.move.x) * 1.0f;
	g_player.move.y += (0.0f - g_player.move.y) * 1.0f;

	Block *pBlock;
	pBlock = GetBlock();

	CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, g_player.fHeight, g_player.fWidth);

	CollisionItem(&g_player.pos, &g_player.posOld, g_player.fHeight, g_player.fWidth);

	//���_���W�X�V
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y, g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y, g_player.pos.z);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X���擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}