//=============================================================================
//
// �v���C���[���� [Castle.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "main.h"
#include "Castle.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "main.h"
#include "castle.h"
#include "enemy.h"
#include "life.h"
#include "explosion.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PATTERN (10)
#define POS_X (0.2f * (g_nPatternAnim % 5))
#define POS_Y (0.5f * (g_nPatternAnim / 5))
#define MOVE (1.2f)

#define HALF_X (180.0f)	//X������
#define HALF_Y (180.0f)	//Y������

#define LIMIT_MIN_X (45)	//��ʒ[-X
#define LIMIT_MAX_X (1250)	//��ʒ[X
#define LIMIT_MIN_Y (25)	//��ʒ[-Y
#define LIMIT_MAX_Y (700)	//��ʒ[Y




//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pcastlePolygon = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxCastlePolygon = NULL;	//���_�o�b�t�@�ւ̃|�C���^
CASTLE g_Castle;	//�v���C���[
//=============================================================================
// �v���C���[��������
//=============================================================================
void InitCastle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

								//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Castle.pos = D3DXVECTOR3(150, 410, 0.0f);//�v���C���[���S���W
	g_Castle.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���
	g_Castle.nStock = 4;	//�X�g�b�N
	g_Castle.nLife = 5;		//���C�t


	g_Castle.state = CASTLESTATE_NORMAL;
	g_Castle.bDisp = true;



	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/castle.png", &g_pcastlePolygon);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxCastlePolygon,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxCastlePolygon->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W

	pVtx[0].pos = D3DXVECTOR3(g_Castle.pos.x - HALF_X, g_Castle.pos.y - HALF_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Castle.pos.x + HALF_X, g_Castle.pos.y - HALF_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Castle.pos.x - HALF_X, g_Castle.pos.y + HALF_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Castle.pos.x + HALF_X, g_Castle.pos.y + HALF_Y, 0.0f);


	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxCastlePolygon->Unlock();
}
//=============================================================================
// �v���C���[��������
//=============================================================================
void UnInitCastle(void)
{
	//�e�N�X�`���̔j��
	if (g_pcastlePolygon != NULL)
	{
		g_pcastlePolygon->Release();
		g_pcastlePolygon = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxCastlePolygon != NULL)
	{
		g_pVtxCastlePolygon->Release();
		g_pVtxCastlePolygon = NULL;
	}
}
//=============================================================================
// �v���C���[�X�V����
//=============================================================================
void UpdateCastle(void)
{
	int nReload = 0;
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	MODE *pMode;
	pMode = GetMode();

	switch (g_Castle.state)
	{
	case CASTLESTATE_NORMAL:

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxCastlePolygon->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxCastlePolygon->Unlock();
		break;

	case CASTLESTATE_DAMAGE:
		g_Castle.nCounterState--;
		if (g_Castle.nCounterState <= 0)
		{
			g_Castle.state = CASTLESTATE_NORMAL;

			// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxCastlePolygon->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// ���_�o�b�t�@���A�����b�N����
			g_pVtxCastlePolygon->Unlock();

			g_Castle.nCounterState = 0;
		}
		break;

	}

		ENEMY *pEnemy;
		pEnemy = GetEnemy();



		if (g_Castle.state == CASTLESTATE_NORMAL)
		{
			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				if (pEnemy->bUse == true)	//�G���g�p���Ă���
				{
					if (g_Castle.pos.x > pEnemy->pos.x - 200
						&& g_Castle.pos.x < pEnemy->pos.x + 200
						&& g_Castle.pos.y >  pEnemy->pos.y - 200
						&& g_Castle.pos.y < pEnemy->pos.y + 200)
					{
						
							HitCastle(1);
							pEnemy->bUse = false;
					}
				}
			}
		}
	
}
	

	
	



//=============================================================================
// �v���C���[�`�揈��
//=============================================================================
void DrawCastle(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

							  //�f�o�C�X���擾����
	pDevice = GetDevice();

	if (g_Castle.bDisp == true)
	{

		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxCastlePolygon, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`��
		pDevice->SetTexture(0, g_pcastlePolygon);


		//�v���C���[�`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);
	}
}


void HitCastle(int nDamage)
{
	LIFE *pLife;
	pLife = GetLife();


	PlaySound(SOUND_LABEL_SE_HIT000);
	g_Castle.nLife -= nDamage;
	AddLife(g_Castle.nLife);
	if (g_Castle.nLife <= 0)
	{
		g_Castle.bDisp = false;
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		SetExplosion(g_Castle.pos, D3DXCOLOR(1.0f, 0.4f, 0.0f, 1.0f));
		g_Castle.nCounterState = 100;
		g_Castle.state = CASTLESTATE_DEATH;
		FADE pFade;

		pFade = *GetFade();
				
		//���[�h�ݒ�
		SetFade(MODE_RESULT);
			
		
		
	}

	

	else
	{

		g_Castle.state = CASTLESTATE_DAMAGE;

		VERTEX_2D *pVtx;
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxCastlePolygon->Lock(0, 0, (void**)&pVtx, 0);
		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		// ���_�o�b�t�@���A�����b�N����
		g_pVtxCastlePolygon->Unlock();

		g_Castle.nCounterState = 15;
	}

}


//=============================================================================
// �v���C���[�̎擾
//=============================================================================
//Castle *GetCastle(void)
//{
//	return &g_Castle;
//}


