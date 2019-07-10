//=============================================================================
// ��Q���p���f������ [collisionModle.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "collisionModel.h"
#include "camera.h"
#include "fade.h"
#include "bullet.h"
#include "player.h"
#include "shadow.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME ("DATA\\MODEL\\STONE00.x")
#define TEXTURE_NAME ("DATA\\TEXTURE\\���A�V��.jpg")

#define C_X_SIZE (10)	//�����蔻��̑傫���␳
#define C_Z_SIZE (10)	//�����蔻��̑傫���␳

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshCollisionModle = NULL;
LPD3DXBUFFER g_pBuffMatCollisionModle = NULL;
LPDIRECT3DTEXTURE9 g_pTextureCollisionModle = NULL;

DWORD g_nNumMatCollisionModle = 0;

COLLISIONMODEL g_Collision;

D3DXVECTOR3 g_SabunCM;//���炩�ȕ����]���̂��߂Ɏg��

int g_nIdxShadowCM;

//=============================================================================
// ����������
//=============================================================================
void InitCollisionModle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ʒu�E�����̏����ݒ�
	g_Collision.pos = D3DXVECTOR3(200, 200, -210);//�ʒu
	g_Collision.rot = D3DXVECTOR3(0, 0, 0);//����
	g_Collision.bUse = true;
	g_SabunCM = D3DXVECTOR3(0, 0, 0);//����
	g_nIdxShadowCM = SetShadow(D3DXVECTOR3(g_Collision.pos.x, 0.0f, g_Collision.pos.z), g_Collision.rot);
	g_Collision.VtxMin = D3DXVECTOR3(10000, 10000, 10000);
	g_Collision.VtxMax = D3DXVECTOR3(-10000, -10000, -10000);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureCollisionModle);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatCollisionModle,
		NULL,
		&g_nNumMatCollisionModle,
		&g_pMeshCollisionModle);


	int nNumVtx;										//���_��
	DWORD sizeFVF;										//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;										//���_�o�b�t�@�ւ̃|�C���^

	//���_�����擾
	nNumVtx = g_pMeshCollisionModle->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshCollisionModle->GetFVF());

	//���_�o�b�t�@�����b�N
	g_pMeshCollisionModle->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVer = 0; nCntVer < nNumVtx; nCntVer++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//���_���W�̑��

		if (g_Collision.VtxMin.x >= vtx.x)
		{
			g_Collision.VtxMin.x = vtx.x;
		}
		if (g_Collision.VtxMin.y >= vtx.y)
		{
			g_Collision.VtxMin.y = vtx.y;
		}
		if (g_Collision.VtxMin.z >= vtx.z)
		{
			g_Collision.VtxMin.z = vtx.z;
		}

		if (g_Collision.VtxMax.x <= vtx.x)
		{
			g_Collision.VtxMax.x = vtx.x;
		}
		if (g_Collision.VtxMax.y <= vtx.y)
		{
			g_Collision.VtxMax.y = vtx.y;
		}
		if (g_Collision.VtxMax.z <= vtx.z)
		{
			g_Collision.VtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;//�T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pMeshCollisionModle->UnlockVertexBuffer();

}

//=============================================================================
// �I������
//=============================================================================
void UninitCollisionModle(void)
{
	// ���b�V���̊J��
	if (g_pMeshCollisionModle != NULL)
	{
		g_pMeshCollisionModle->Release();
		g_pMeshCollisionModle = NULL;
	}

	// �}�e���A���̊J��
	if (g_pBuffMatCollisionModle != NULL)
	{
		g_pBuffMatCollisionModle->Release();
		g_pBuffMatCollisionModle = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pTextureCollisionModle != NULL)
	{
		g_pTextureCollisionModle->Release();
		g_pTextureCollisionModle = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCollisionModle(void)
{
	if (g_Collision.bUse == true)
	{
		//SetPositionShadow(g_nIdxShadowCM, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCollisionModle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Collision.mtxWorldCollision);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Collision.rot.y, g_Collision.rot.x, g_Collision.rot.z);
	D3DXMatrixMultiply(&g_Collision.mtxWorldCollision, &g_Collision.mtxWorldCollision, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Collision.pos.x, g_Collision.pos.y, g_Collision.pos.z);
	D3DXMatrixMultiply(&g_Collision.mtxWorldCollision, &g_Collision.mtxWorldCollision, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Collision.mtxWorldCollision);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatCollisionModle->GetBufferPointer();

	for (int nCntMat = 0; nCntMat<(int)g_nNumMatCollisionModle; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureCollisionModle);

		// ���f��(�p�[�c)�̕`��
		g_pMeshCollisionModle->DrawSubset(nCntMat);

	}
	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// ��Q���p���f�����̎擾
//=============================================================================
COLLISIONMODEL *GetCollision(void)
{
	return &g_Collision;
}
//=============================================================================
// �����蔻�菈��
//=============================================================================
void CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMax,D3DXVECTOR3 *pVtxMin)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	if (g_Collision.bUse == true)
	{
		if (pPos->x + C_X_SIZE >= g_Collision.pos.x + (g_Collision.VtxMin.x) &&
			pPos->x - C_X_SIZE <= g_Collision.pos.x + (g_Collision.VtxMax.x))
		{
			if (pPos->z + C_Z_SIZE >= g_Collision.pos.z + (g_Collision.VtxMin.z) &&
				pPos->z - C_Z_SIZE <= g_Collision.pos.z + (g_Collision.VtxMax.z))
			{
				//FADE pFade;

				//pFade = *GetFade();

				////���[�h�ݒ�
				//SetFade(MODE_RESULT);
				//
				//pPlayer->move = D3DXVECTOR3(0, 0, 0);//�ړ��ʂ�0�ɂ���

				//if (pPosOld->z + C_Z_SIZE <= g_Collision.pos.z + (g_Collision.VtxMin.z) &&
				//	pPos->z + C_Z_SIZE >= g_Collision.pos.z + (g_Collision.VtxMin.z))
				//{//��O�̔���
				//	pPos->z = g_Collision.pos.z + (g_Collision.VtxMin.z) - C_Z_SIZE;
				//}
				//else if (pPosOld->z - C_Z_SIZE >= g_Collision.pos.z + (g_Collision.VtxMax.z ) &&
				//	pPos->z - C_Z_SIZE <= g_Collision.pos.z + (g_Collision.VtxMax.z))
				//{//���̔���
				//	pPos->z = g_Collision.pos.z + (g_Collision.VtxMax.z) + C_Z_SIZE;
				//}


				//if (pPosOld->x - C_X_SIZE >= g_Collision.pos.x + (g_Collision.VtxMax.x) &&
				//	pPos->x - C_X_SIZE <= g_Collision.pos.x + (g_Collision.VtxMax.x))
				//{//�E�̔���
				//	pPos->x = g_Collision.pos.x + (g_Collision.VtxMax.x)+ C_X_SIZE;
				//}
				//else if (pPosOld->x + C_X_SIZE <= g_Collision.pos.x+ (g_Collision.VtxMin.x) &&
				//	pPos->x + C_X_SIZE >= g_Collision.pos.x + (g_Collision.VtxMin.x))
				//{//���̔���
				//	pPos->x = g_Collision.pos.x + (g_Collision.VtxMin.x)- C_X_SIZE;
				//}
			}
		}
	}
}

