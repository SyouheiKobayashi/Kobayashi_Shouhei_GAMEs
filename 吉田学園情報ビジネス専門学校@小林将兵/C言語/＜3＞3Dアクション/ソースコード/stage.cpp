//=============================================================================
// ���f������ [stage.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "stage.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME ("DATA\\MODEL\\STAGE00.x")
#define TEXTURE_NAME ("DATA\\UV\\STAGE_UV�ҏW.png")

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshStage = NULL;
LPD3DXBUFFER g_pBuffMatStage = NULL;
LPDIRECT3DTEXTURE9 g_pTextureStage = NULL;

DWORD g_nNumMatStage = 0;
D3DXVECTOR3 g_posStage;
D3DXVECTOR3 g_rotStage;
D3DXMATRIX g_mtxWorldStage;

//=============================================================================
// ����������
//=============================================================================
void InitStage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureStage);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatStage,
		NULL,
		&g_nNumMatStage,
		&g_pMeshStage);

	// �ʒu�E�����̏����ݒ�
	g_posStage = D3DXVECTOR3(50, 0, 50);//�ʒu
	g_rotStage = D3DXVECTOR3(0, D3DX_PI, 0);//����
}

//=============================================================================
// �I������
//=============================================================================
void UninitStage(void)
{
	// ���b�V���̊J��
	if (g_pMeshStage != NULL)
	{
		g_pMeshStage->Release();
		g_pMeshStage = NULL;
	}

	// �}�e���A���̊J��
	if (g_pBuffMatStage != NULL)
	{
		g_pBuffMatStage->Release();
		g_pBuffMatStage = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pTextureStage != NULL)
	{
		g_pTextureStage->Release();
		g_pTextureStage = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStage(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldStage);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotStage.y, g_rotStage.x, g_rotStage.z);
	D3DXMatrixMultiply(&g_mtxWorldStage, &g_mtxWorldStage, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posStage.x, g_posStage.y, g_posStage.z);
	D3DXMatrixMultiply(&g_mtxWorldStage, &g_mtxWorldStage, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldStage);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatStage->GetBufferPointer();

	for(int nCntMat = 0; nCntMat<(int)g_nNumMatStage;nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);
		pDevice->SetTexture(0, g_pTextureStage);


		// ���f��(�p�[�c)�̕`��
		g_pMeshStage->DrawSubset(nCntMat);

	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}
