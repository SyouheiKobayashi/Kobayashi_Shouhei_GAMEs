//=============================================================================
// �X�R�A���� [layout.cpp]
// Author:Kobayashi/���� ����
//=============================================================================
#include "layout.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_Layout		"DATA\\TEXTURE\\LAYOUT01.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TATE_POS (35)
#define YOKO_POS (925)
#define TATE_SIZE (25)
#define YOKO_SIZE (25)
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexLayout(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureLayout = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLayout = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int						g_nLayout;					// �X�R�A
//D3DXVECTOR3				g_posLayout;					// �ʒu

//=============================================================================
// ����������
//=============================================================================
void InitLayout(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nLayout = 0;

	//g_posLayout = D3DXVECTOR3(YOKO_POS, TATE_POS, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_Layout,		// �t�@�C���̖��O
								&g_pTextureLayout);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexLayout(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitLayout(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureLayout != NULL)
	{
		g_pTextureLayout->Release();
		g_pTextureLayout = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pTextureLayout != NULL)
	{
		g_pTextureLayout->Release();
		g_pTextureLayout = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLayout(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLayout(void)
{
	int nCount;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffLayout, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureLayout);

	
	// �|���S���̕`��
	/*for (nCount = 0; nCount < 1; nCount++)
	{*/
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0/*4 * nCount*/,2);
	//}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexLayout(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntLayout;

	// [���_�o�b�t�@�𐶐�]
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4/* * 1*/,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLayout,
		NULL);

	// [���_����ݒ�]
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLayout->Lock(0, 0, (void**)&pVtx, 0);

	
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//pVtx += 4;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLayout->Unlock();
}

