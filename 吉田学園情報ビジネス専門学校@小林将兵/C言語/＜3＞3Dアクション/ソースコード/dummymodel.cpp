//=============================================================================
// ���f������ [DummyModel.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "DummyModel.h"
#include "camera.h"
#include "bullet.h"
#include "shadow.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME ("DATA\\MODEL\\�_�~�[���f�������.x")
#define TEXTURE_NAME ("DATA\\TEXTURE\\��揑 ��L����03.jpg")

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshDummyModel = NULL;
LPD3DXBUFFER g_pBuffMatDummyModel = NULL;
LPDIRECT3DTEXTURE9 g_pTextureDummyModel = NULL;

DWORD g_nNumMatDummyModel = 0;
D3DXVECTOR3 g_posDummyModel;
D3DXVECTOR3 g_rotDummyModel;
D3DXMATRIX g_mtxWorldDummyModel;

D3DXVECTOR3 g_SabunD;//���炩�ȕ����]���̂��߂Ɏg��

int g_nIdxShadowD;

//=============================================================================
// ����������
//=============================================================================
void InitDummyModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureDummyModel);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatDummyModel,
		NULL,
		&g_nNumMatDummyModel,
		&g_pMeshDummyModel);

	// �ʒu�E�����̏����ݒ�
	g_posDummyModel = D3DXVECTOR3(50, 0, 50);//�ʒu
	g_rotDummyModel = D3DXVECTOR3(0, 0, 0);//����
	g_SabunD = D3DXVECTOR3(0, 0, 0);//����

	g_nIdxShadowD = SetShadow(D3DXVECTOR3(g_posDummyModel.x,0.0f, g_posDummyModel.z), g_rotDummyModel);
}

//=============================================================================
// �I������
//=============================================================================
void UninitDummyModel(void)
{
	// ���b�V���̊J��
	if (g_pMeshDummyModel != NULL)
	{
		g_pMeshDummyModel->Release();
		g_pMeshDummyModel = NULL;
	}

	// �}�e���A���̊J��
	if (g_pBuffMatDummyModel != NULL)
	{
		g_pBuffMatDummyModel->Release();
		g_pBuffMatDummyModel = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pTextureDummyModel != NULL)
	{
		g_pTextureDummyModel->Release();
		g_pTextureDummyModel = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateDummyModel(void)
{
	g_rotDummyModel.y -= 0.01f;

//^^^^^^^^^^^^^^^^^^^^^^^^^^
//	�e�̔��ːݒ�
//^^^^^^^^^^^^^^^^^^^^^^^^^^
	//SetBullet(g_posDummyModel, D3DXVECTOR3(sinf(g_rotDummyModel.y - D3DX_PI)*3.3f, 0.0f, cosf(g_rotDummyModel.y - D3DX_PI)*3.3f));

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawDummyModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldDummyModel);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotDummyModel.y, g_rotDummyModel.x, g_rotDummyModel.z);
	D3DXMatrixMultiply(&g_mtxWorldDummyModel, &g_mtxWorldDummyModel, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posDummyModel.x, g_posDummyModel.y, g_posDummyModel.z);
	D3DXMatrixMultiply(&g_mtxWorldDummyModel, &g_mtxWorldDummyModel, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldDummyModel);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatDummyModel->GetBufferPointer();

	for(int nCntMat = 0; nCntMat<(int)g_nNumMatDummyModel;nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);
		pDevice->SetTexture(0, g_pTextureDummyModel);


		// ���f��(�p�[�c)�̕`��
		g_pMeshDummyModel->DrawSubset(nCntMat);

	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}
