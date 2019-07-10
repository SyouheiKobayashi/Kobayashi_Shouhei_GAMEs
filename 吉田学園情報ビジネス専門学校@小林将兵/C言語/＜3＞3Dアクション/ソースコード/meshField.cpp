//=============================================================================
// �|���S������ [meshField.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "meshField.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME ("DATA\\TEXTURE\\�[�C_��.jpg")
#define BLOCK_SIZE (50)
#define TATE (14)
#define YOKO (14)

#define INDEX ((TATE * YOKO )* 2+(TATE-1)*4+2)//�C���f�b�N�X
#define POLYGON ((TATE * YOKO )* 2+(TATE-1)*4)//�|���S��
#define VERTEX ((TATE+1)*(YOKO+1))//���_

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;

D3DXVECTOR3 g_posMeshField;		//�ʒu
D3DXVECTOR3 g_rotMeshField;		//����
D3DXMATRIX g_mtxWorldMeshField;	//���[���h�}�g���b�N�X

int g_nNumIndxMeshField;//�C���f�b�N�X��
int g_nNumPolygonMeshField;//�|���S����
int g_nNumVertexMeshField;//���_��


//=============================================================================
// ����������
//=============================================================================
void InitMeshField(void)
{
	int nCntIdx;

	g_nNumIndxMeshField = INDEX;
	g_nNumVertexMeshField = VERTEX;
	g_nNumPolygonMeshField = POLYGON;

	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

												//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureMeshField);

	// ���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	for (int nCntZ = 0; nCntZ < TATE + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < YOKO + 1; nCntX++)
		{
			pVtx[nCntZ * (YOKO+1)+ nCntX].pos = D3DXVECTOR3(-100+(BLOCK_SIZE*nCntX), 0.0f, 100+(-BLOCK_SIZE*nCntZ));

			pVtx[nCntZ * (YOKO + 1) + nCntX].tex = D3DXVECTOR2((-1.0*nCntX), (1.0*nCntZ));
			pVtx[nCntZ * (YOKO + 1) + nCntX].nor = D3DXVECTOR3(0, 1, 0);
			pVtx[nCntZ * (YOKO + 1) + nCntX].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshField->Unlock();

	WORD*pIdx;//�C���f�b�N�X�f�[�^�ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^������
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	/*pIdx[0] = 2; pIdx[1] = 0; pIdx[2] = 3; pIdx[3] = 1;*/

	//pIdx[0] = 3; pIdx[1] = 0; pIdx[2] = 4; pIdx[3] = 1; pIdx[4] = 5; pIdx[5] = 2; pIdx[6] = 2;
	//pIdx[7] = 6; pIdx[8] = 6; pIdx[9] = 3; pIdx[10] = 7; pIdx[11] = 4; pIdx[12] = 8; pIdx[13] = 5;

	//���_���W�̐ݒ�
	for (int nCntT = 0, nCntIdx = 0;  nCntT<TATE; nCntT++)//�c
	{
		for (int nCntY = 0; nCntY < YOKO + 1; nCntY++,nCntIdx++)//��
		{
			pIdx[0] = (YOKO + 1) + nCntIdx;
			pIdx[1] = 0 + nCntIdx;
			pIdx += 2;
 			if (nCntT < TATE - 1 && nCntY == YOKO)//���ɐi��ł����P���Ȃ��Ȃ�����&&nCntY�Ǝ����̎w�肵�����̃T�C�Y����v�����Ƃ�
			{
				pIdx[0] = 0 + nCntIdx;
				pIdx[1] = (YOKO + 1) + nCntIdx + 1;
				pIdx += 2;
			}
		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshField->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);


	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0,0, VERTEX,0, POLYGON);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

