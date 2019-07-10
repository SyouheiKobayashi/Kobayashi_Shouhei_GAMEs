//=============================================================================
//
// ���C�t���� [Life.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "life.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_LIFE		"data/TEXTURE/life000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);

#define LIFE_X (15.0f)
#define LIFE_Y (30.0f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLife = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LIFE					g_aLife[MAX_LIFE];					// �X�R�A

//=============================================================================
// ����������
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�X�R�A������
	for (int nCntLife = 0; nCntLife < MAX_LIFE  ; nCntLife++)
	{
		g_aLife[nCntLife].pos = D3DXVECTOR3( 40, 40, 0.0f);
		g_aLife[nCntLife].nLife = MAX_LIFE;
		g_aLife[nCntLife].bUse = true;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_LIFE,		// �t�@�C���̖��O
		&g_pTextureLife);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexLife(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitLife(void)
{

	// �e�N�X�`���̊J��
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLife(void)
{
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLife(void)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureLife);

	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;


	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);



	// ���_����ݒ�
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{

			pVtx[0].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x - LIFE_X, g_aLife[nCntLife].pos.y - LIFE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + LIFE_X, g_aLife[nCntLife].pos.y - LIFE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x - LIFE_X, g_aLife[nCntLife].pos.y + LIFE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + LIFE_X, g_aLife[nCntLife].pos.y + LIFE_Y, 0.0f);


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

			pVtx += 4;

			for (int nCntLife2 = 0; nCntLife2 < MAX_LIFE; nCntLife2++)
			{
				g_aLife[nCntLife2].pos.x += 50;
			}
			


	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();
}


//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddLife(int nLife)
{
	
	if (g_aLife[nLife].bUse == true)
	{
		g_aLife[nLife].bUse = false;
	}
}


//=============================================================================
// ���C�t�̎擾
//=============================================================================
LIFE *GetLife(void)
{
	return &g_aLife[0];
}



