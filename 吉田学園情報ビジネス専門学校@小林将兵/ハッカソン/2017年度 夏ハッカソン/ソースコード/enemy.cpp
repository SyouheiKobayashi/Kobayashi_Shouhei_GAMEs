//=============================================================================
//
// �G���� [enemy.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "enemy.h"
#include "bullet.h"
#include "game.h"
#include "sound.h"
#include "player.h"
#include "main.h"
#include "bullet.h"
#include <stdlib.h> 
#include <time.h>   

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_ENEMY		(3)								// �G�̎��
#define ENEMY_TEXTURENAME_0	"data/TEXTURE/ENEMY0A.png"		//�G�̃e�N�X�`��1
#define ENEMY_TEXTURENAME_1	"data/TEXTURE/ENEMY0B.png"		//�G�̃e�N�X�`��2
#define ENEMY_TEXTURENAME_2	"data/TEXTURE/ENEMY0C.png"		//�G�̃e�N�X�`��3

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// ���_�o�b�t�@�ւ̃|�C���^

ENEMY g_aEnemy[MAX_ENEMY];

int g_nNumEnemy;	//�G�̑���
//=============================================================================
// ����������
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;	//�G�̃J�E���g

					// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�̏��̏�����
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURENAME_0, &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURENAME_1, &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURENAME_2, &g_apTextureEnemy[2]);

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.33f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.33f, 1.0f);


		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

	g_nNumEnemy = 0; //�G�̑����̃N���A

}

//=============================================================================
// �I������
//=============================================================================
void UnInitEnemy(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}


	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;

	// ���_���̍쐬
	VERTEX_2D *pVtx;



	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		g_aEnemy[nCntEnemy].nCountAnim++;
		if ((g_aEnemy[nCntEnemy].nCountAnim % 20) == 0)
		{
			g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % 3;//�A�j���[�V�����̃p�^�[��No.�������l�ɖ߂�

			if (g_aEnemy[nCntEnemy].bUse == true)	//�G���g�p����Ă���
			{
				//�e�N�X�`�����W���X�V
				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.33f * g_aEnemy[nCntEnemy].nPatternAnim), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.33f + (0.33f * g_aEnemy[nCntEnemy].nPatternAnim), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.33f * g_aEnemy[nCntEnemy].nPatternAnim), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.33f + (0.33f * g_aEnemy[nCntEnemy].nPatternAnim), 1.0f);
			}
		}


		if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_NORMAL ||
			g_aEnemy[nCntEnemy].state == ENEMYSTATE_DAMAGE)
		{
			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;
			//���_�̍��W
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);

		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�

	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

	//�G�̏�ԑJ��
	for (nCntEnemy = 0; nCntEnemy <= MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL: //�ʏ펞
				
			
					// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
					g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
					pVtx += (nCntEnemy * 4);

					//���_�J���[
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					// ���_�o�b�t�@���A�����b�N����
					g_pVtxBuffEnemy->Unlock();
				
				break;

			case ENEMYSTATE_DAMAGE: //�q�b�g��
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
					g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
					pVtx += (nCntEnemy * 4);

					//���_�J���[
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					// ���_�o�b�t�@���A�����b�N����
					g_pVtxBuffEnemy->Unlock();
				}


				break;
			}
		}
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	// �|���S���̕`��

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{

			// �f�o�C�X�̎擾
			pDevice = GetDevice();

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);



			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//=============================================================================
// �G�̃_���[�W����
//=============================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	PlaySound(SOUND_LABEL_SE_HIT001);

	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		g_aEnemy[nCntEnemy].bUse = false;
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		g_nNumEnemy--;

		MODE *pMode;
		pMode = GetMode();
		
		//SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		//SetPerticle(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 0.0f, 60);
		/*if (g_nNumEnemy <= 0)
		{
			SetGameState(GAMESTATE_CLEAR);
		}*/
		
	}

	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 8;
		VERTEX_2D *pVtx;
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntEnemy * 4);	//�Y���̈ʒu�܂œ�����

									//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEnemy->Unlock();
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType, int nLife)
{
	int nCntEnemy;
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)	//�G���g�p����Ă��Ȃ�
		{
			g_aEnemy[nCntEnemy].pos = pos;

			//���_�̍��W
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);

			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nLife = nLife;
			g_aEnemy[nCntEnemy].bUse = true;	//�g�p���Ă����Ԃɂ���

			g_nNumEnemy++;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �G�̎擾
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}
