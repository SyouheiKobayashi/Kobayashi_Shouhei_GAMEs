//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//? �e���� [bullet.cpp]
//? Author :���� / Kobayashi
//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "main.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "player.h"
#include "effect.h"
#include "sound.h"

//? ==================================================
//+ �}�N����`
//? ==================================================
#define	BULLET_MAX		(256)		// �e�̍ő吔
#define BULLET_SIZE	(15)
//? ==================================================
//+ �\����
//? ==================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nLife;				//����
	BULLETTYPE type;		//�e�̎��(�N�̒e��/�G��������)
	bool bUse;				//�g�p���Ă��邩�ǂ���
} Bullet;

//? ==================================================
//?+ �O���[�o���ϐ��錾
//? ==================================================
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[BULLET_MAX];						//���̏��

//? ==================================================
//?+ ����������
//? ==================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for(nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\���Hbullet.png", &g_pTextureBullet);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * BULLET_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//���_���̐ݒ�
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ� / �e�̐F
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx += 4;//���_�f�[�^�̏����S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//? ==================================================
//?+ �I������
//? ==================================================
void UninitBullet(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
	StopSound();
}

//? ==================================================
//?+ �X�V����
//? ==================================================
void UpdateBullet(void)
{
	//���_���̐ݒ�
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//!+ <�v���C���[�̒e>
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				//�e�̈ړ��X�V
				g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;

				//���_���W�̐ݒ� / �e�̑傫��
				pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);
				pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);

				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 15.0f, 20);
			}

			//!+ <�G�̒e>
			if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				//�e�̈ړ��X�V
				g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;

				//���_���W�̐ݒ� / �e�̑傫��
				pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);
				pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);

				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 15.0f, 20);

			}

			//!+ <�e�̎���>
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			//!+ <�e�̉�ʊO����>
			if (g_aBullet[nCntBullet].pos.y < -10)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			else if (SCREEN_HEIGHT + 10 < g_aBullet[nCntBullet].pos.y)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

			//!+ <�G�Ƃ̂����蔻��>
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				ENEMY *pEnemy;
				pEnemy = GetEnemy();

				for (int nCountEnemy = 0; nCountEnemy < ENEMY_MAX; nCountEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (pEnemy->pos.x - 60 < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + 60 > g_aBullet[nCntBullet].pos.x
							&& pEnemy->pos.y - 60 < g_aBullet[nCntBullet].pos.y&& pEnemy->pos.y + 60 > g_aBullet[nCntBullet].pos.y)
						{
							HitEnemy(nCountEnemy, 1);//�_���[�W����
							g_aBullet[nCntBullet].bUse = false;
						}
					}
				}
			}
			//!+ <�v���C���[�Ƃ̂����蔻��>
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				PLAYER *pPlayer;
				pPlayer = GetPlayer();//�v���C���[�ʒu�̎擾

				if (pPlayer->bDisp == true)
				{
					if (pPlayer->pos.x - 25 < g_aBullet[nCntBullet].pos.x && pPlayer->pos.x + 25 > g_aBullet[nCntBullet].pos.x
						&& pPlayer->pos.y - 25 < g_aBullet[nCntBullet].pos.y&& pPlayer->pos.y + 25 > g_aBullet[nCntBullet].pos.y)
					{
						HitPlayer(1);//�_���[�W����
						g_aBullet[nCntBullet].bUse = false;
					}
				}
			}
		}
	}
	pVtx += 4;
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}


//? ==================================================
//?+ �`�揈��
//? ==================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	// �|���S���̕`��
	for(nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)		//�����g�p����Ă���
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet*4, 2);
		}
	}
}

//? ==================================================
//?+ �e�̐ݒ菈��
//? ==================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type)
{
	//���_���̐ݒ�
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(int nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)	//�����g�p����Ă��Ȃ�
		{
			if (type == BULLETTYPE_PLAYER)
			{
				g_aBullet[nCntBullet].pos = pos;
				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].nLife = 80;//�e�̐�������/����
				g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
				g_aBullet[nCntBullet].bUse = true;

				break;
			}

			if (type == BULLETTYPE_ENEMY)
			{
				g_aBullet[nCntBullet].pos = pos;
				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].nLife = 160;//�e�̐�������/����160
				g_aBullet[nCntBullet].type = BULLETTYPE_ENEMY;
				g_aBullet[nCntBullet].bUse = true;

				break;
			}
		}
		
		pVtx += 4; //�|�C���^��i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

