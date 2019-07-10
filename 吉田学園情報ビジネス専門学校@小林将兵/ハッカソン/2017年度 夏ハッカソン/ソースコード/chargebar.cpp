//=============================================================================
//
// �`���[�W�o�[���� [chargebar.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "chargebar.h"
#include "main.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_POLYGON (2)
#define MAX_BAR (2)
#define CHARGEBAR_WIDTH		(80)				//�w�i�̕�
#define CHARGEBAR_HEIGHT		(5)				//�w�i�̍���
#define CHARGEBAR_POS_X		(0)							//�w�i����X���W
#define CHARGEBAR_POS_Y		(0)							//�w�i����Y���W

#define CHARGEBAR_TEXTURENAME_0	"data/TEXTURE/chargebar.png"		//�w�i�̃e�N�X�`��1
#define CHARGEBAR_TEXTURENAME_1	"data/TEXTURE/chargebar.png"		//�w�i�̃e�N�X�`��1

#define CHARGE_SPEED (0.55f)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexChargebar(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureChargebar[MAX_BAR] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffChargebar = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
CHARGEBAR					g_aChargebar[MAX_BAR];					// �t�F�[�h���

//=============================================================================
// ����������
//=============================================================================
void InitChargebar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntCharge = 0; nCntCharge < MAX_BAR; nCntCharge++)
	{
		g_aChargebar[nCntCharge].pos = D3DXVECTOR3(560, 420, 0.0f);
		g_aChargebar[nCntCharge].nType = nCntCharge;
	}
	
	


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, CHARGEBAR_TEXTURENAME_0, &g_pTextureChargebar[0]);
	D3DXCreateTextureFromFile(pDevice, CHARGEBAR_TEXTURENAME_1, &g_pTextureChargebar[1]);


	// ���_���̐ݒ�
	MakeVertexChargebar(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UnInitChargebar(void)
{
	for (int nCntCharge = 0; nCntCharge < MAX_BAR; nCntCharge++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureChargebar[nCntCharge] != NULL)
		{
			g_pTextureChargebar[nCntCharge]->Release();
			g_pTextureChargebar[nCntCharge] = NULL;
		}

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffChargebar != NULL)
	{
		g_pVtxBuffChargebar->Release();
		g_pVtxBuffChargebar = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateChargebar(void)
{
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	PLAYER *pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();

	//int ChargeBar;

	if (pPlayer->state == PLAYERSTATE_NORMAL )
	{
		if (GetKeyboardPress(DIK_RETURN) == true)
		{

			pPlayer->nCntCharge++;

			//ChargeBar = (0.8f * pPlayer->nCounterState);

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffChargebar->Lock(0, 0, (void**)&pVtx, 0);

			//���_�̍��W
			pVtx[4].pos = D3DXVECTOR3(g_aChargebar[1].pos.x - 1.0f, g_aChargebar[1].pos.y - CHARGEBAR_HEIGHT, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(g_aChargebar[1].pos.x + 1.0f + (CHARGE_SPEED * pPlayer->nCntCharge), g_aChargebar[1].pos.y - CHARGEBAR_HEIGHT, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(g_aChargebar[1].pos.x - 1.0f, g_aChargebar[1].pos.y + CHARGEBAR_HEIGHT, 0.0f);
			pVtx[7].pos = D3DXVECTOR3(g_aChargebar[1].pos.x + 1.0f + (CHARGE_SPEED * pPlayer->nCntCharge), g_aChargebar[1].pos.y + CHARGEBAR_HEIGHT, 0.0f);

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffChargebar->Unlock();

		}
	}

	if (pPlayer->state == PLAYERSTATE_CHARGE)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffChargebar->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[
		pVtx[4].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffChargebar->Unlock();
	}


	if (GetKeyboardPress(DIK_RETURN) != true)
	{

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffChargebar->Lock(0, 0, (void**)&pVtx, 0);

		//���_�̍��W
		pVtx[4].pos = D3DXVECTOR3(g_aChargebar[1].pos.x - 1, g_aChargebar[1].pos.y - CHARGEBAR_HEIGHT, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_aChargebar[1].pos.x + 1, g_aChargebar[1].pos.y - CHARGEBAR_HEIGHT, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_aChargebar[1].pos.x - 1, g_aChargebar[1].pos.y + CHARGEBAR_HEIGHT, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_aChargebar[1].pos.x + 1, g_aChargebar[1].pos.y + CHARGEBAR_HEIGHT, 0.0f);


		//���_�J���[
		pVtx[4].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffChargebar->Unlock();
	}
}

//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawChargebar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffChargebar, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntCharge = 0; nCntCharge < MAX_BAR; nCntCharge++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureChargebar[g_aChargebar[nCntCharge].nType]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntCharge * 4, NUM_POLYGON);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexChargebar(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BAR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffChargebar,
		NULL);

	
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffChargebar->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aChargebar[0].pos.x - 18, g_aChargebar[0].pos.y - (CHARGEBAR_HEIGHT + 8), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aChargebar[0].pos.x + (CHARGEBAR_WIDTH + 40), g_aChargebar[0].pos.y - (CHARGEBAR_HEIGHT + 8), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aChargebar[0].pos.x - 18, g_aChargebar[0].pos.y + (CHARGEBAR_HEIGHT + 8), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aChargebar[0].pos.x + (CHARGEBAR_WIDTH + 40), g_aChargebar[0].pos.y + (CHARGEBAR_HEIGHT + 8), 0.0f);

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
	pVtx[0].pos = D3DXVECTOR3(g_aChargebar[1].pos.x - 1,g_aChargebar[1].pos.y - CHARGEBAR_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aChargebar[1].pos.x + 1, g_aChargebar[1].pos.y - CHARGEBAR_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aChargebar[1].pos.x - 1, g_aChargebar[1].pos.y + CHARGEBAR_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aChargebar[1].pos.x + 1, g_aChargebar[1].pos.y + CHARGEBAR_HEIGHT, 0.0f);

	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffChargebar->Unlock();
}



