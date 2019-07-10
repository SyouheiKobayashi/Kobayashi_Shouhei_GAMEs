//=============================================================================
// �|���S������ [polygon.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME ("DATA\\TEXTURE\\��.png")

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;

D3DXVECTOR3 g_posPolygon;		//�ʒu
D3DXVECTOR3 g_rotPolygon;		//����
D3DXMATRIX g_mtxWorldPolygon;	//���[���h�}�g���b�N�X


//=============================================================================
// ����������
//=============================================================================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTexturePolygon);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 3000.0f);
	pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 3000.0f);
	pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, 2800.0f);
	pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, 2800.0f);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPolygon->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{
	// �e�N�X�`���̔j��
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y,g_rotPolygon.x,g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);


	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorldPolygon);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolygon);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

