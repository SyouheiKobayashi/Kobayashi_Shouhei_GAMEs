//=============================================================================
//
// �`���[�W�o�[���� [Stamina.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "stamina.h"
#include "main.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_POLYGON (2)
#define MAX_BAR (2)
#define STAMINA_WIDTH		(80)				//�w�i�̕�
#define STAMINA_HEIGHT		(5)				//�w�i�̍���

#define STAMINA_WIDTH2 (1.0f)

#define STAMINA_TEXTURENAME_0	"data/TEXTURE/chargebar.png"		//�w�i�̃e�N�X�`��1
#define STAMINA_TEXTURENAME_1	"data/TEXTURE/chargebar.png"		//�w�i�̃e�N�X�`��1

#define STAMINA_SPEED (5.0f)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexStamina(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureStamina[MAX_BAR] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStamina = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
STAMINA					g_Stamina[MAX_BAR];					// �t�F�[�h���

//=============================================================================
// ����������
//=============================================================================
void InitStamina(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntCharge = 0; nCntCharge < MAX_BAR; nCntCharge++)
	{
		g_Stamina[nCntCharge].pos = D3DXVECTOR3(560, 450, 0.0f);
		g_Stamina[nCntCharge].nType = nCntCharge;
	}




	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, STAMINA_TEXTURENAME_0, &g_pTextureStamina[0]);
	D3DXCreateTextureFromFile(pDevice, STAMINA_TEXTURENAME_1, &g_pTextureStamina[1]);


	// ���_���̐ݒ�
	MakeVertexStamina(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UnInitStamina(void)
{
	for (int nCntCharge = 0; nCntCharge < MAX_BAR; nCntCharge++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureStamina[nCntCharge] != NULL)
		{
			g_pTextureStamina[nCntCharge]->Release();
			g_pTextureStamina[nCntCharge] = NULL;
		}

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffStamina != NULL)
	{
		g_pVtxBuffStamina->Release();
		g_pVtxBuffStamina = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStamina(void)
{
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	PLAYER *pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();

	//float Stamina;

	switch (pPlayer->state)
	{


		case PLAYERSTATE_NORMAL:
		


			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffStamina->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[
			pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffStamina->Unlock();

			break;
		
	


	case PLAYERSTATE_TIRED:
	
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffStamina->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[
		pVtx[4].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�̍��W
		pVtx[4].pos = D3DXVECTOR3(g_Stamina[1].pos.x - 1, g_Stamina[1].pos.y - STAMINA_HEIGHT, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_Stamina[1].pos.x + 1, g_Stamina[1].pos.y - STAMINA_HEIGHT, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_Stamina[1].pos.x - 1, g_Stamina[1].pos.y + STAMINA_HEIGHT, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_Stamina[1].pos.x + 1, g_Stamina[1].pos.y + STAMINA_HEIGHT, 0.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffStamina->Unlock();
	
		break;

}
	
	if (pPlayer->state == PLAYERSTATE_NORMAL)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{

			pPlayer->nCntStamina++;

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffStamina->Lock(0, 0, (void**)&pVtx, 0);

			//���_�̍��W
			pVtx[4].pos = D3DXVECTOR3(g_Stamina[1].pos.x - 1.0f, g_Stamina[1].pos.y - STAMINA_HEIGHT, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(g_Stamina[1].pos.x + 1.0f + (STAMINA_SPEED * pPlayer->nCntStamina), g_Stamina[1].pos.y - STAMINA_HEIGHT, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(g_Stamina[1].pos.x - 1.0f, g_Stamina[1].pos.y + STAMINA_HEIGHT, 0.0f);
			pVtx[7].pos = D3DXVECTOR3(g_Stamina[1].pos.x + 1.0f + (STAMINA_SPEED * pPlayer->nCntStamina), g_Stamina[1].pos.y + STAMINA_HEIGHT, 0.0f);

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffStamina->Unlock();

		}
	}

	//if (GetKeyboardPress(DIK_RETURN) != true)
	//{

	//	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	//	g_pVtxBuffStamina->Lock(0, 0, (void**)&pVtx, 0);

	//	//���_�̍��W
	//	pVtx[4].pos = D3DXVECTOR3(g_Stamina[1].pos.x - 1, g_Stamina[1].pos.y - STAMINA_HEIGHT, 0.0f);
	//	pVtx[5].pos = D3DXVECTOR3(g_Stamina[1].pos.x + 1, g_Stamina[1].pos.y - STAMINA_HEIGHT, 0.0f);
	//	pVtx[6].pos = D3DXVECTOR3(g_Stamina[1].pos.x - 1, g_Stamina[1].pos.y + STAMINA_HEIGHT, 0.0f);
	//	pVtx[7].pos = D3DXVECTOR3(g_Stamina[1].pos.x + 1, g_Stamina[1].pos.y + STAMINA_HEIGHT, 0.0f);


	//	//���_�J���[
	//	pVtx[4].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[5].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[6].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[7].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

	//	//���_�o�b�t�@���A�����b�N
	//	g_pVtxBuffStamina->Unlock();
	//}
}

//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawStamina(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffStamina, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntCharge = 0; nCntCharge < MAX_BAR; nCntCharge++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureStamina[g_Stamina[nCntCharge].nType]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntCharge * 4, NUM_POLYGON);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexStamina(LPDIRECT3DDEVICE9 pDevice)
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
		&g_pVtxBuffStamina,
		NULL);


	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffStamina->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_Stamina[0].pos.x - 18, g_Stamina[0].pos.y - (STAMINA_HEIGHT + 6), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Stamina[0].pos.x + (STAMINA_WIDTH + 40), g_Stamina[0].pos.y - (STAMINA_HEIGHT + 6), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Stamina[0].pos.x - 18, g_Stamina[0].pos.y + (STAMINA_HEIGHT + 6), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Stamina[0].pos.x + (STAMINA_WIDTH + 40), g_Stamina[0].pos.y + (STAMINA_HEIGHT + 6), 0.0f);

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
	pVtx[0].pos = D3DXVECTOR3(g_Stamina[1].pos.x - 1, g_Stamina[1].pos.y - STAMINA_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Stamina[1].pos.x + 1, g_Stamina[1].pos.y - STAMINA_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Stamina[1].pos.x - 1, g_Stamina[1].pos.y + STAMINA_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Stamina[1].pos.x + 1, g_Stamina[1].pos.y + STAMINA_HEIGHT, 0.0f);

	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffStamina->Unlock();
}



