//=============================================================================
// ��Q���p���f������ [item.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "item.h"
#include "sound.h"
#include "game.h"
#include "camera.h"
#include "score.h"
#include "timer.h"
#include "bullet.h"
#include "player.h"
#include "shadow.h"
//#include "fade.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME ("DATA\\MODEL\\ITEM00.x")
#define TEXTURE_NAME ("DATA\\UV\\�A�C�e��01_UV.jpg")
#define MAX_ITEM (1)	//�g�p���郂�f���̎��
#define MAX_ARRANGEMENT (5)	//�z�u���郂�f���̐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshItem[MAX_ARRANGEMENT] = {};
LPD3DXBUFFER g_pBuffMatItem[MAX_ARRANGEMENT] = {};
LPDIRECT3DTEXTURE9 g_pTextureItem[MAX_ARRANGEMENT]= {};

DWORD g_nNumMatItem[MAX_ARRANGEMENT] = {};

ITEM g_Item[MAX_ARRANGEMENT];

D3DXVECTOR3 g_SabunI[MAX_ARRANGEMENT];//���炩�ȕ����]���̂��߂Ɏg��

int g_nIdxShadowI[MAX_ARRANGEMENT];

int g_NumItem;//�A�C�e���̑���

//=============================================================================
// ����������
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// �ʒu�E�����̏����ݒ�
		g_Item[nCnt].pos = D3DXVECTOR3(0, 0, 0);//�ʒu
		g_Item[nCnt].move = D3DXVECTOR3(0, 0, 0);//�ړ�
		g_Item[nCnt].rot = D3DXVECTOR3(0, 0, 0);//����
		g_Item[nCnt].bUse = false;
		g_Item[nCnt].bTouch = false;
		g_SabunI[nCnt] = D3DXVECTOR3(0, 0, 0);//����
		g_NumItem = 0;

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureItem[nCnt]);

		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(MODEL_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatItem[nCnt],
			NULL,
			&g_nNumMatItem[nCnt],
			&g_pMeshItem[nCnt]);

		g_Item[nCnt].VtxMin = D3DXVECTOR3(10000, 10000, 10000);
		g_Item[nCnt].VtxMax = D3DXVECTOR3(-10000, -10000, -10000);

		int nNumVtx;										//���_��
		DWORD sizeFVF;										//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;										//���_�o�b�t�@�ւ̃|�C���^

		//���_�����擾
		nNumVtx = g_pMeshItem[nCnt]->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshItem[nCnt]->GetFVF());

		//���_�o�b�t�@�����b�N
		g_pMeshItem[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVer = 0; nCntVer < nNumVtx; nCntVer++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//���_���W�̑��

			if (g_Item[nCnt].VtxMin.x >= vtx.x)
			{
				g_Item[nCnt].VtxMin.x = vtx.x;
			}
			if (g_Item[nCnt].VtxMin.y >= vtx.y)
			{
				g_Item[nCnt].VtxMin.y = vtx.y;
			}
			if (g_Item[nCnt].VtxMin.z >= vtx.z)
			{
				g_Item[nCnt].VtxMin.z = vtx.z;
			}

			if (g_Item[nCnt].VtxMax.x <= vtx.x)
			{
				g_Item[nCnt].VtxMax.x = vtx.x;
			}
			if (g_Item[nCnt].VtxMax.y <= vtx.y)
			{
				g_Item[nCnt].VtxMax.y = vtx.y;
			}
			if (g_Item[nCnt].VtxMax.z <= vtx.z)
			{
				g_Item[nCnt].VtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//�T�C�Y���|�C���^��i�߂�
		}

		//���_�o�b�t�@���A�����b�N
		g_pMeshItem[nCnt]->UnlockVertexBuffer();

		//g_NumItem = 0;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// ���b�V���̊J��
		if (g_pMeshItem[nCnt] != NULL)
		{
			g_pMeshItem[nCnt]->Release();
			g_pMeshItem[nCnt] = NULL;
		}

		// �}�e���A���̊J��
		if (g_pBuffMatItem[nCnt] != NULL)
		{
			g_pBuffMatItem[nCnt]->Release();
			g_pBuffMatItem[nCnt] = NULL;
		}

		// �e�N�X�`���̔j��
		if (g_pTextureItem[nCnt] != NULL)
		{
			g_pTextureItem[nCnt]->Release();
			g_pTextureItem[nCnt] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{
	int nMove = 0;
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		if (g_Item[nCnt].bUse == true)
		{
			g_Item[nCnt].pos += g_Item[nCnt].move;

			if (g_Item[nCnt].pos.x > 300)
			{
				g_Item[nCnt].move.x = -2.0f;
			}
			if (g_Item[nCnt].pos.x < -300)
			{
				g_Item[nCnt].move.x = 2.0f;
			}

			g_Item[nCnt].rot.y += 0.05f;

			SetPositionShadow(g_nIdxShadowI[nCnt], D3DXVECTOR3(g_Item[nCnt].pos.x, 0.0f, g_Item[nCnt].pos.z));
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Item[nCnt].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Item[nCnt].rot.y, g_Item[nCnt].rot.x, g_Item[nCnt].rot.z);
		D3DXMatrixMultiply(&g_Item[nCnt].mtxWorld, &g_Item[nCnt].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Item[nCnt].pos.x, g_Item[nCnt].pos.y, g_Item[nCnt].pos.z);
		D3DXMatrixMultiply(&g_Item[nCnt].mtxWorld, &g_Item[nCnt].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Item[nCnt].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatItem[nCnt]->GetBufferPointer();

		if (g_Item[nCnt].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatItem[nCnt]; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureItem[nCnt]);

				// ���f��(�p�[�c)�̕`��
				g_pMeshItem[nCnt]->DrawSubset(nCntMat);

			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}


//=============================================================================
// �A�C�e���̐ݒ�
//=============================================================================

void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// ���_���̍쐬
	//VERTEX_3D *pVtx;

	int nNumVtx;				//���_��
	DWORD sizeFVF;				//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		//���_�����擾
		nNumVtx = g_pMeshItem[nCnt]->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshItem[nCnt]->GetFVF());


		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pMeshItem[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		if (g_Item[nCnt].bUse == false)	//�u���b�N���g�p���Ă���
		{
			g_Item[nCnt].pos = pos;
			g_Item[nCnt].move = move;
			g_Item[nCnt].bUse = true;
			g_nIdxShadowI[nCnt] = SetShadow(D3DXVECTOR3(g_Item[nCnt].pos.x, 0.0f, g_Item[nCnt].pos.z), D3DXVECTOR3(0, 0, 0));

			g_NumItem++;//�A�C�e���̑��������Z
			

			break;

		}

		// ���_�o�b�t�@���A�����b�N����
		g_pMeshItem[nCnt]->UnlockVertexBuffer();
	}
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
void CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMax,D3DXVECTOR3 *pVtxMin)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	TIMER *pTimer;
	pTimer = GetTimer();
	
	

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		if (g_Item[nCnt].bUse == true)
		{
			if (pPos->x+10 >= g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMin.x) &&
				pPos->x-10 <= g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMax.x))
			{
				if (pPos->z+10 >= g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMin.z) &&
					pPos->z-10 <= g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMax.z))
				{
					if (pPosOld->z+10 <= g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMin.z) &&
						pPos->z-10 >= g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMin.z))
					{//��O�̔���
						pPos->z = g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMin.z) - 10;
					}
					else if (pPosOld->z-10 >= g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMax.z) &&
						pPos->z-10 <= g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMax.z))
					{//���̔���
						pPos->z = g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMax.z) + 10;
					}
					if (pPosOld->x-10 >= g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMax.x) &&
						pPos->x-10 <= g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMax.x))
					{//�E�̔���
						pPos->x = g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMax.x) + 10;
					}
					else if (pPosOld->x+10 <= g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMin.x) &&
						pPos->x+10 >= g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMin.x))
					{//���̔���
						pPos->x = g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMin.x) - 10;
					}
					PlaySound(SOUND_LABEL_SE_HIT000);//�A�C�e�����莞�̉�

					AddScore(10000);//�A�C�e�����莞�̃|�C���g
					pTimer->nTime += 2 * 100;//���Ԃ̑���

					g_Item[nCnt].bUse = false;//�A�C�e����\�����Ȃ�
					DeleteShadow(g_nIdxShadowI[nCnt]);

					g_NumItem--;

					//if (g_NumItem <= 0)
					//{//�A�C�e�������ׂď���������
					//	SetGameState(GAMESTATE_END);
					//}
				}
			}
		}
	}
}

//=============================================================================
// ��Q���p���f�����̎擾
//=============================================================================
ITEM *GetItem(void)
{
		return &g_Item[MAX_ARRANGEMENT];
}
