//=============================================================================
// ���f������ [player.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "player.h"
#include "input.h"
#include "game.h"
#include "camera.h"
#include "collisionModel.h"
#include "item.h"
#include "badItem.h"
#include "fallingRocks.h"
#include "bullet.h"
#include "shadow.h" 
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME ("DATA\\MODEL\\car000.x")
#define MODEL_NAME2 ("DATA\\MODEL\\PLAYER_head00.x")


#define TEXTURE_NAME ("DATA\\TEXTURE\\�����N�����.jpg")
#define TEXTURE_NAME2 ("DATA\\TEXTURE\\��揑 ��L����03.jpg")

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PLAYER g_Player;

D3DXVECTOR3 g_Sabun;//���炩�ȕ����]���̂��߂Ɏg��

camera *pCamera;

int g_nIdxShadow;

//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_Player.aModel[1].pTexture);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME2, &g_Player.aModel[2].pTexture);

//=============================================================================
//+ X�t�@�C���̓ǂݍ���
//=============================================================================
	D3DXLoadMeshFromX(MODEL_NAME,//�{��
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[0].pBuffMat,
		NULL,
		&g_Player.aModel[0].nNumMat,
		&g_Player.aModel[0].pMesh);

	D3DXLoadMeshFromX(MODEL_NAME2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[1].pBuffMat,
		NULL,
		&g_Player.aModel[1].nNumMat,
		&g_Player.aModel[1].pMesh);

	//D3DXLoadMeshFromX(MODEL_NAME2,//�X�q
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_Player.aModel[2].pBuffMat,
	//	NULL,
	//	&g_Player.aModel[2].nNumMat,
	//	&g_Player.aModel[2].pMesh);
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	// �ʒu�E�����̏����ݒ�
	g_Player.pos = D3DXVECTOR3(0, 0, -2800);//�ʒu
	g_Player.posOld = D3DXVECTOR3(0, 0, 0);//�ʒu
	g_Player.move = D3DXVECTOR3(0, 0, 0);//�ړ�
	g_Player.rot = D3DXVECTOR3(0, -D3DX_PI, 0);//����
	g_Sabun = D3DXVECTOR3(0, 0, 0);//����

	g_Player.aModel[0].pos = D3DXVECTOR3(0, 0, 0);
	g_Player.aModel[0].rot = D3DXVECTOR3(0, 0, 0);
	g_Player.aModel[0].nIdxModelParent = -1;

	g_Player.aModel[1].pos = D3DXVECTOR3(0, 0, -13);
	g_Player.aModel[1].rot = D3DXVECTOR3(0, 0, 0);
	g_Player.aModel[1].nIdxModelParent = 0;

	/*g_Player.aModel[2].pos = D3DXVECTOR3(20, 15, 0);
	g_Player.aModel[2].rot = D3DXVECTOR3(0, 0, 0);
	g_Player.aModel[2].nIdxModelParent = 0;*/

	g_nIdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z), g_Player.rot);

	int nNumVtx;										//���_��
	DWORD sizeFVF;										//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;										//���_�o�b�t�@�ւ̃|�C���^

														//���_�����擾
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		nNumVtx = g_Player.aModel[nCnt].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCnt].pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		g_Player.aModel[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVer = 0; nCntVer < nNumVtx; nCntVer++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//���_���W�̑��

			if (g_Player.VtxMin.x >= vtx.x)
			{
				g_Player.VtxMin.x = vtx.x;
			}
			if (g_Player.VtxMin.y >= vtx.y)
			{
				g_Player.VtxMin.y = vtx.y;
			}
			if (g_Player.VtxMin.z >= vtx.z)
			{
				g_Player.VtxMin.z = vtx.z;
			}

			if (g_Player.VtxMax.x <= vtx.x)
			{
				g_Player.VtxMax.x = vtx.x;
			}
			if (g_Player.VtxMax.y <= vtx.y)
			{
				g_Player.VtxMax.y = vtx.y;
			}
			if (g_Player.VtxMax.z <= vtx.z)
			{
				g_Player.VtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//�T�C�Y���|�C���^��i�߂�
		}

		//���_�o�b�t�@���A�����b�N
		g_Player.aModel[nCnt].pMesh->UnlockVertexBuffer();
	}

	
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
		// ���b�V���̊J��
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_Player.aModel[nCnt].pMesh != NULL)
		{
			g_Player.aModel[nCnt].pMesh->Release();
			g_Player.aModel[nCnt].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_Player.aModel[nCnt].pBuffMat != NULL)
		{
			g_Player.aModel[nCnt].pBuffMat->Release();
			g_Player.aModel[nCnt].pBuffMat = NULL;
		}

		// �e�N�X�`���̔j��
		if (g_Player.aModel[nCnt].pTexture != NULL)
		{
			g_Player.aModel[nCnt].pTexture ->Release();
			g_Player.aModel[nCnt].pTexture = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	pCamera = GetCamera();

	g_Player.posOld = g_Player.pos;

	//g_Player.aModel[2].rot.y++;

//^^^^^^^^^^^^^^^^^^^^^^^^^^
//			������
//^^^^^^^^^^^^^^^^^^^^^^^^^^
//	if (GetKeyboardPress(DIK_Q) == true)
//	{
//		g_Player.pos = D3DXVECTOR3(0, 0, 0);//�ʒu
//		g_Player.rot = D3DXVECTOR3(0, 0, 0);//����
//		g_Sabun = D3DXVECTOR3(0, 0, 0);//����
//	}

//^^^^^^^^^^^^^^^^^^^^^^^^^^
//	�e�̔��ːݒ�
//^^^^^^^^^^^^^^^^^^^^^^^^^^
	//if (GetKeyboardTrigger(DIK_SPACE) == true)//�X�y�[�X�����Ă̒e�̎ˏo
	//{//																	�����̔��˕���&&���̑��x
	//	SetBullet(g_Player.pos, D3DXVECTOR3(sinf(g_Player.rot.y - D3DX_PI)*3.3f, 0.0f, cosf(g_Player.rot.y - D3DX_PI)*3.3f));
	//}

//^^^^^^^^^^^^^^^^^^^^^^^^^^
//	���f���ړ�[��][��][��][��]
//^^^^^^^^^^^^^^^^^^^^^^^^^^
	if (GetKeyboardPress(DIK_UP) == true)
	{
			g_Player.move.x += sinf(pCamera->rot.y) * 1.0f;
			g_Player.move.z += cosf(pCamera->rot.y) * 1.0f;
			g_Sabun.y = (D3DX_PI + pCamera->rot.y) - g_Player.rot.y;
			if (g_Player.pos.z > 3037)
			{
				g_Player.move.z = 0;
			}
		
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
			g_Player.move.x += sinf(D3DX_PI + pCamera->rot.y) * 1.0f;
			g_Player.move.z += cosf(D3DX_PI + pCamera->rot.y) * 1.0f;
			g_Sabun.y = (pCamera->rot.y) - g_Player.rot.y;
			//g_Player.rot.y = 3.14f + pCamera->rot.y; �o�b�N���@�ɂȂ��
			if (g_Player.pos.z < -2837)
			{
				g_Player.move.z = 0;
			}
		
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)//��
	{
		if (GetKeyboardPress(DIK_UP) == true)//�΂�
		{
			g_Player.move.x += sinf(D3DX_PI * 0.5f + pCamera->rot.y) * 0.3f;
			g_Player.move.z += cosf(D3DX_PI * 0.5f + pCamera->rot.y) * 0.3f;
			g_Sabun.y = ((-D3DX_PI *0.75f) + pCamera->rot.y) - g_Player.rot.y;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)//�΂�
		{
			g_Player.move.x += sinf(D3DX_PI * 0.5f + pCamera->rot.y) * 0.3f;
			g_Player.move.z += cosf(D3DX_PI * 0.5f + pCamera->rot.y) * 0.3f;
			g_Sabun.y = ((-D3DX_PI *0.25f) + pCamera->rot.y) - g_Player.rot.y;
		}
		else
		{
			g_Player.move.x += sinf(D3DX_PI / 2 + pCamera->rot.y) * 0.4f;
			g_Player.move.z += cosf(D3DX_PI / 2 + pCamera->rot.y) * 0.4f;
			g_Sabun.y = ((-D3DX_PI / 2) + pCamera->rot.y) - g_Player.rot.y;
		}
		if (g_Player.pos.x > 537)
		{
			g_Player.move.x = 0;
		}
	}
	if (GetKeyboardPress(DIK_LEFT) == true)//��
	{
		if (GetKeyboardPress(DIK_UP) == true)//�΂�
		{
			g_Player.move.x -= sinf(D3DX_PI * 0.5f + pCamera->rot.y)*0.3f;
			g_Player.move.z -= cosf(D3DX_PI * 0.5f + pCamera->rot.y)*0.3f;
			g_Sabun.y = ((D3DX_PI *0.75f) + pCamera->rot.y) - g_Player.rot.y;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)//�΂�
		{
			g_Player.move.x -= sinf(D3DX_PI * 0.5f + pCamera->rot.y) * 0.3f;
			g_Player.move.z -= cosf(D3DX_PI * 0.5f + pCamera->rot.y) * 0.3f;
			g_Sabun.y = ((D3DX_PI *0.25f) + pCamera->rot.y) - g_Player.rot.y;
		}
		else
		{
			g_Player.move.x -= sinf(D3DX_PI / 2 + pCamera->rot.y) * 0.4f;
			g_Player.move.z -= cosf(D3DX_PI / 2 + pCamera->rot.y) * 0.4f;
			g_Sabun.y = ((D3DX_PI / 2) + pCamera->rot.y) - g_Player.rot.y;
		
		}
		if (g_Player.pos.x < -437)
		{
			g_Player.move.x = 0;
		}
	}
	if (g_Sabun.y >  D3DX_PI)
	{
		g_Sabun.y -= D3DX_PI * 2;
	}
	if (g_Sabun.y <  -D3DX_PI)
	{
		g_Sabun.y += D3DX_PI * 2;
	}

	g_Player.rot.y += g_Sabun.y * 0.16f;

	if (g_Player.rot.y >  D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI * 2;
	}
	if (g_Player.rot.y <  -D3DX_PI)
	{
		g_Player.rot.y += D3DX_PI * 2;
	}

	g_Sabun.y = 0;

	g_Player.move += (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - g_Player.move)*0.1f;
	g_Player.pos += g_Player.move;

	//g_Player.aModel[1].rot.y -= 0.05f;
	//g_Player.aModel[2].rot.y += 0.05f;

	SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z));

//�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��
//+	�v���C���[�ɑ΂��邠���蔻��̏���	
//�� ��	�� �� �� �� �� �� �� ��	�� �� �� �� �� �� �� ��	�� �� �� �� �� �� �� ��	�� �� �� �� �� ��
	CollisionModel(&g_Player.pos, &g_Player.posOld, &g_Player.move,&g_Player.VtxMax,&g_Player.VtxMin);
	CollisionItem(&g_Player.pos, &g_Player.posOld, &g_Player.move, &g_Player.VtxMax, &g_Player.VtxMin);
	CollisionBadItem(&g_Player.pos, &g_Player.posOld, &g_Player.move, &g_Player.VtxMax, &g_Player.VtxMin);
	CollisionFallingRocks(&g_Player.pos, &g_Player.posOld, &g_Player.move, &g_Player.VtxMax, &g_Player.VtxMin);


//�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��
//+	�v���C���[�ɑ΂���J�����̒ǔ�����	
//�� ��	�� �� �� �� �� �� �� ��	�� �� �� �� �� �� �� ��	�� �� �� �� �� �� �� ��	�� �� �� �� �� ��
	pCamera->posRDest.x= (g_Player.pos.x) - sinf(pCamera->rot.y) * 80;
	pCamera->posRDest.y = (g_Player.pos.y);
	pCamera->posRDest.z = (g_Player.pos.z) - cosf(pCamera->rot.y) * 60;

	pCamera->posVDest.x = pCamera->posRDest.x - sinf(pCamera->rot.y) * 200;
	pCamera->posVDest.y = pCamera->posRDest.y;
	pCamera->posVDest.z = pCamera->posRDest.z - cosf(pCamera->rot.y) * 200;

	pCamera->posR.x += (pCamera->posRDest.x - pCamera->posR.x)*0.09f;
	pCamera->posR.y += (pCamera->posRDest.y - pCamera->posR.y)*0.05f;
	pCamera->posR.z += (pCamera->posRDest.z - pCamera->posR.z)*0.09f;

	pCamera->posV.x += (pCamera->posVDest.x - pCamera->posV.x)*0.09f;
	pCamera->posV.y += (pCamera->posVDest.y - pCamera->posV.y+50)*0.05f;
	pCamera->posV.z += (pCamera->posVDest.z - pCamera->posV.z)*0.09f;

//�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��
//+	�v���C���[���ړI�̒l(pos)�ȏ�ɓ��B���ꍇ&&�N���A����	
//�� ��	�� �� �� �� �� �� �� ��	�� �� �� �� �� �� �� ��	�� �� �� �� �� �� �� ��	�� �� �� �� �� ��
	if (g_Player.pos.z < 2837)
	{
		SetGameState(GAMESTATE_CLEAR);
	}
}

//=============================================================================
//=============================================================================
//++ �`�揈��
//=============================================================================
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	D3DXMATRIX mtxParent;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);
	
	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_Player.aModel[nCnt].nIdxModelParent == -1)
		{
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			mtxParent = g_Player.aModel[g_Player.aModel[nCnt].nIdxModelParent].mtxWorld;
		}

		//--------------------------------------------------------------------------------------
		//!+ Model(�e)
		//--------------------------------------------------------------------------------------
			// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.aModel[nCnt].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCnt].rot.y, g_Player.aModel[nCnt].rot.x, g_Player.aModel[nCnt].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCnt].mtxWorld, &g_Player.aModel[nCnt].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[nCnt].pos.x, g_Player.aModel[nCnt].pos.y, g_Player.aModel[nCnt].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCnt].mtxWorld, &g_Player.aModel[nCnt].mtxWorld, &mtxTrans);

		D3DXMatrixMultiply(&g_Player.aModel[nCnt].mtxWorld, &g_Player.aModel[nCnt].mtxWorld, &mtxParent);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCnt].mtxWorld);

		//+ X�t�@�C���̕`��
		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCnt].nNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
			pDevice->SetTexture(0, g_Player.aModel[nCnt].pTexture);


			// ���f��(�p�[�c)�̕`��
			g_Player.aModel[nCnt].pMesh->DrawSubset(nCntMat);

		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}

//=============================================================================
// �v���C���[���̏���
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}