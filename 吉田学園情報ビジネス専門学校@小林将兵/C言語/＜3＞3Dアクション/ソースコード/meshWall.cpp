//=============================================================================
// �|���S������ [meshWall.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "meshWall.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME ("DATA\\TEXTURE\\�[�C_��.jpg")
#define POLYGON_SIZE (235)
#define TATE (1)
#define YOKO (3)
#define MAX_WALL (4)

#define INDEX ((TATE * YOKO )* 2+(TATE-1)*4+2)//�C���f�b�N�X
#define POLYGON ((TATE * YOKO )* 2+(TATE-1)*4)//�|���S��
#define VERTEX ((TATE+1)*(YOKO+1))//���_

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;

MESHWALL g_MeshWall[MAX_WALL];

//D3DXVECTOR3 g_posMeshWall;		//�ʒu
//D3DXVECTOR3 g_rotMeshWall;		//����
//D3DXMATRIX g_mtxWorldMeshWall;	//���[���h�}�g���b�N�X

int g_nNumIndxMeshWall;//�C���f�b�N�X��
int g_nNumPolygonMeshWall;//�|���S����
int g_nNumVertexMeshWall;//���_��


//=============================================================================
// ����������
//=============================================================================
void InitMeshWall(void)
{
	int nCntM;
	int nCntIdx;

	g_nNumIndxMeshWall = INDEX;
	g_nNumVertexMeshWall = VERTEX;
	g_nNumPolygonMeshWall = POLYGON;

	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_MeshWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCntWall].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureMeshWall);

	// ���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	for (int nCntZ = 0; nCntZ < TATE + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < YOKO + 1; nCntX++)
		{
			pVtx[nCntZ * (YOKO+1)+ nCntX].pos = D3DXVECTOR3(-100+(POLYGON_SIZE*nCntX), (230* TATE) + (-POLYGON_SIZE*nCntZ), 0.0f);

			pVtx[nCntZ * (YOKO + 1) + nCntX].tex = D3DXVECTOR2((-1.0*nCntX), (1.0*nCntZ));
			pVtx[nCntZ * (YOKO + 1) + nCntX].nor = D3DXVECTOR3(0, 1, 0);
			pVtx[nCntZ * (YOKO + 1) + nCntX].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshWall->Unlock();

	WORD*pIdx;//�C���f�b�N�X�f�[�^�ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^������
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X�̐ݒ�
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
	g_pIdxBuffMeshWall->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshWall(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshWall(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_MeshWall[nCntWall].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_MeshWall[nCntWall].mtxWorldWall);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall[nCntWall].rot.y, g_MeshWall[nCntWall].rot.x, g_MeshWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_MeshWall[nCntWall].mtxWorldWall, &g_MeshWall[nCntWall].mtxWorldWall, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_MeshWall[nCntWall].pos.x, g_MeshWall[nCntWall].pos.y, g_MeshWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_MeshWall[nCntWall].mtxWorldWall, &g_MeshWall[nCntWall].mtxWorldWall, &mtxTrans);


			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall[nCntWall].mtxWorldWall);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshWall);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VERTEX, 0, POLYGON);
		}
	}
}

//=============================================================================
// ���b�V���ǂ̐ݒ�
//=============================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���_���̍쐬
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_MeshWall[nCntWall].bUse == false)
		{
			g_MeshWall[nCntWall].pos = pos;
			g_MeshWall[nCntWall].rot = rot;
			g_MeshWall[nCntWall].bUse = true;
			break;
		}
		//pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshWall->Unlock();
}

