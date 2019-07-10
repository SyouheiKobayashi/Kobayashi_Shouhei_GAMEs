//=============================================================================
//
// �`���[�W�o�[���� [CastleLife.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "castlelife.h"
#include "main.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_POLYGON (2)
#define MAX_BAR (2)
#define CASTLELIFE_WIDTH		(80)				//�w�i�̕�
#define CASTLELIFE_HEIGHT		(5)				//�w�i�̍���

#define CASTLELIFE_WIDTH2 (1.0f)

#define CASTLELIFE_TEXTURENAME_0	"data/TEXTURE/chargebar.png"		//�w�i�̃e�N�X�`��1
#define CASTLELIFE_TEXTURENAME_1	"data/TEXTURE/chargebar.png"		//�w�i�̃e�N�X�`��1

#define CASTLELIFE_SPEED (5.0f)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexCastleLife(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureCastleLife[MAX_BAR] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCastleLife = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
CASTLELIFE					g_CastleLife[MAX_BAR];					// �t�F�[�h���

//=============================================================================
// ����������
//=============================================================================
void InitCastleLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntCastleLife = 0; nCntCastleLife < MAX_BAR; nCntCastleLife++)
	{
		g_CastleLife[nCntCastleLife].pos = D3DXVECTOR3(110, 220, 0.0f);
		g_CastleLife[nCntCastleLife].nType = nCntCastleLife;
	}




	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, CASTLELIFE_TEXTURENAME_0, &g_pTextureCastleLife[0]);
	D3DXCreateTextureFromFile(pDevice, CASTLELIFE_TEXTURENAME_1, &g_pTextureCastleLife[1]);


	// ���_���̐ݒ�
	MakeVertexCastleLife(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UnInitCastleLife(void)
{
	for (int nCntCastleLife = 0; nCntCastleLife < MAX_BAR; nCntCastleLife++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureCastleLife[nCntCastleLife] != NULL)
		{
			g_pTextureCastleLife[nCntCastleLife]->Release();
			g_pTextureCastleLife[nCntCastleLife] = NULL;
		}

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCastleLife != NULL)
	{
		g_pVtxBuffCastleLife->Release();
		g_pVtxBuffCastleLife = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCastleLife(void)
{
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	PLAYER *pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();

	//float CastleLife;

	switch (pPlayer->state)
	{


	case PLAYERSTATE_NORMAL:



		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffCastleLife->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[
		pVtx[4].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);



		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffCastleLife->Unlock();

		break;

	}


	
	

	//if (GetKeyboardPress(DIK_RETURN) != true)
	//{

	//	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	//	g_pVtxBuffCastleLife->Lock(0, 0, (void**)&pVtx, 0);

	//	//���_�̍��W
	//	pVtx[4].pos = D3DXVECTOR3(g_CastleLife[1].pos.x - 1, g_CastleLife[1].pos.y - CASTLELIFE_HEIGHT, 0.0f);
	//	pVtx[5].pos = D3DXVECTOR3(g_CastleLife[1].pos.x + 1, g_CastleLife[1].pos.y - CASTLELIFE_HEIGHT, 0.0f);
	//	pVtx[6].pos = D3DXVECTOR3(g_CastleLife[1].pos.x - 1, g_CastleLife[1].pos.y + CASTLELIFE_HEIGHT, 0.0f);
	//	pVtx[7].pos = D3DXVECTOR3(g_CastleLife[1].pos.x + 1, g_CastleLife[1].pos.y + CASTLELIFE_HEIGHT, 0.0f);


	//	//���_�J���[
	//	pVtx[4].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[5].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[6].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[7].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

	//	//���_�o�b�t�@���A�����b�N
	//	g_pVtxBuffCastleLife->Unlock();
	//}
}

//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawCastleLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffCastleLife, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntCastleLife = 0; nCntCastleLife < MAX_BAR; nCntCastleLife++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureCastleLife[g_CastleLife[nCntCastleLife].nType]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntCastleLife * 4, NUM_POLYGON);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexCastleLife(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	PLAYER *pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BAR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCastleLife,
		NULL);


	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCastleLife->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_CastleLife[0].pos.x - 18, g_CastleLife[0].pos.y - (CASTLELIFE_HEIGHT + 10), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_CastleLife[0].pos.x + (CASTLELIFE_WIDTH + 30), g_CastleLife[0].pos.y - (CASTLELIFE_HEIGHT + 10), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_CastleLife[0].pos.x - 18, g_CastleLife[0].pos.y + (CASTLELIFE_HEIGHT + 10), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_CastleLife[0].pos.x + (CASTLELIFE_WIDTH + 30), g_CastleLife[0].pos.y + (CASTLELIFE_HEIGHT + 10), 0.0f);

	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.5f);
	pVtx[1].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.5f);
	pVtx[2].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.5f);
	pVtx[3].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.5f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;


	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_CastleLife[1].pos.x - 1, g_CastleLife[1].pos.y - CASTLELIFE_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_CastleLife[1].pos.x + CASTLELIFE_WIDTH, g_CastleLife[1].pos.y - CASTLELIFE_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_CastleLife[1].pos.x - 1, g_CastleLife[1].pos.y + CASTLELIFE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_CastleLife[1].pos.x + CASTLELIFE_WIDTH, g_CastleLife[1].pos.y + CASTLELIFE_HEIGHT, 0.0f);

	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[4].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);


	//�e�N�X�`�����W
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffCastleLife->Unlock();
}


//=============================================================================
// �_���[�W
//=============================================================================
//void HitCastle(int nDamage)
//{
//	
//	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^
//
//			
//
//			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
//			g_pVtxBuffCastleLife->Lock(0, 0, (void**)&pVtx, 0);
//
//			//���_�̍��W
//			pVtx[4].pos = D3DXVECTOR3(g_CastleLife[1].pos.x - 1.0f, g_CastleLife[1].pos.y - CASTLELIFE_HEIGHT, 0.0f);
//			pVtx[5].pos = D3DXVECTOR3(g_CastleLife[1].pos.x + 1.0f + (CASTLELIFE_SPEED * nDamage), g_CastleLife[1].pos.y - CASTLELIFE_HEIGHT, 0.0f);
//			pVtx[6].pos = D3DXVECTOR3(g_CastleLife[1].pos.x - 1.0f, g_CastleLife[1].pos.y + CASTLELIFE_HEIGHT, 0.0f);
//			pVtx[7].pos = D3DXVECTOR3(g_CastleLife[1].pos.x + 1.0f + (CASTLELIFE_SPEED * nDamage), g_CastleLife[1].pos.y + CASTLELIFE_HEIGHT, 0.0f);
//
//			//���_�o�b�t�@���A�����b�N
//			g_pVtxBuffCastleLife->Unlock();
//
//		
//	
//}