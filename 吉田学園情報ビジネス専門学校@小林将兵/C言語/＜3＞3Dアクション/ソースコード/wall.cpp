//=============================================================================
// �|���S������ [wall.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "wall.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME ("DATA\\TEXTURE\\wall000.jpg")
#define MAX_WALL (4)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;

WALL g_Wall[MAX_WALL];

//D3DXVECTOR3 g_posWall;		//�ʒu
//D3DXVECTOR3 g_rotWall;		//����
//D3DXMATRIX g_mtxWorldWall;	//���[���h�}�g���b�N�X

//=============================================================================
// ����������
//=============================================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_Wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].bUse = false;
	}
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureWall);

		// ���_���̍쐬
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffWall,
			NULL);

		VERTEX_3D*pVtx;//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
		g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntWall2 = 0; nCntWall2 < MAX_WALL; nCntWall2++)
		{
			//���_���W�̐ݒ�
			//g_posWall = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
			pVtx[0].pos = D3DXVECTOR3(-100.0f, 150.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(100.0f, 150.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);

			//g_Wall[nCntWall2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f) * D3DX_PI;//�ǂ̉�]

			//�e�N�X�`���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//�@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
			pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
			pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
			pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);

			pVtx += 4;//���_�f�[�^�̏����S���i�߂�
		}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffWall->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitWall(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWall(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Wall[nCntWall].mtxWorldWall);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].rot.y, g_Wall[nCntWall].rot.x, g_Wall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorldWall, &g_Wall[nCntWall].mtxWorldWall, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].pos.x, g_Wall[nCntWall].pos.y, g_Wall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorldWall, &g_Wall[nCntWall].mtxWorldWall, &mtxTrans);


			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].mtxWorldWall);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));


			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
		}
	}

}

//=============================================================================
// �ǂ̐ݒ�
//=============================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���_���̍쐬
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == false)
		{
			g_Wall[nCntWall].pos = pos;
			g_Wall[nCntWall].rot = rot;
			g_Wall[nCntWall].bUse = true;
			break;
		}
		//pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

