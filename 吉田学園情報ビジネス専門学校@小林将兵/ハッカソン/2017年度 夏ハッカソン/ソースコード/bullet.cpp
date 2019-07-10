//=============================================================================
//
// �e���� [bullet.cpp]
// Author : KishidaRei
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include "player.h"
#include "game.h"
#include "main.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BULLET	(128)	// �e�̍ő吔
#define BULLET_TEXTURENAME	"data/TEXTURE/slash.png"



//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];	//�e�̏��

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;	//�e�̃J�E���g



	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
		g_aBullet[nCntBullet].fRadius = 0.0f;

		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURENAME, &g_pTextureBullet);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fRadius, 0.0f);

		//1.0f�ŌŒ�
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UnInitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	int nCntBullet;
	
	MODE *pMode;
	pMode = GetMode();
	
	

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
	
			if (g_aBullet[nCntBullet].bUse == true)	//�e���g�p����Ă���
			{
				
		
				//�e�̈ʒu���ړ�������
				g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
				g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				//���_�̍��W
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fRadius, 0.0f);

				if (g_aBullet[nCntBullet].pos.y < 0)
				{
					g_aBullet[nCntBullet].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
				}
				//��莞�Ԍo��
				g_aBullet[nCntBullet].nLife--;
				if (g_aBullet[nCntBullet].nLife <= 0)
				{
					//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					g_aBullet[nCntBullet].bUse = false;
				}



				if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER) //�v���C���[�̒e
				{
					//�e�̈ʒu���ړ�������
					g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
					g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;

					
					ENEMY *pEnemy;
					pEnemy = GetEnemy();
					int nCntEnemy;
					for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
					{
						if (pEnemy->bUse == true)	//�G���g�p���Ă���
						{
							if (g_aBullet[nCntBullet].pos.x > pEnemy->pos.x - 30
								&& g_aBullet[nCntBullet].pos.x < pEnemy->pos.x + 30
								&& g_aBullet[nCntBullet].pos.y >  pEnemy->pos.y - 30
								&& g_aBullet[nCntBullet].pos.y < pEnemy->pos.y + 30)
							{
								HitEnemy(nCntEnemy, 1);

								g_aBullet[nCntBullet].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
							}
						}
					}
				}

				
				
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
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
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	//�e���g�p����Ă���
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBullet, 2);
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type, float fRadius, int nLife)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	int nCntBullet;


	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
		if (g_aBullet[nCntBullet].bUse == false)	//�e���g�p����Ă��Ȃ�
		{
			pVtx += (nCntBullet * 4);

			if (type == BULLETTYPE_PLAYER)
			{
				g_aBullet[nCntBullet].pos = pos;
				g_aBullet[nCntBullet].fRadius = fRadius;
				g_aBullet[nCntBullet].nLife = nLife;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fRadius, 0.0f);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].bUse = true;	//�g�p���Ă����Ԃɂ���

				
				break;
			}

			
			

			else if (type == BULLETTYPE_ENEMY)
			{
				g_aBullet[nCntBullet].pos = pos;
				g_aBullet[nCntBullet].nLife = nLife;
				g_aBullet[nCntBullet].fRadius = fRadius;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fRadius, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fRadius, 0.0f);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				g_aBullet[nCntBullet].type = BULLETTYPE_ENEMY;
				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].bUse = true;	//�g�p���Ă����Ԃɂ���
				break;

			}
			
		}
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffBullet->Unlock();
	}
	
}
//=============================================================================
// �e�̎擾
//=============================================================================
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}