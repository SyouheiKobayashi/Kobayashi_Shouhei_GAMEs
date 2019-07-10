//=============================================================================
// ��Q���p���f������ [badItem.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "badItem.h"
#include "sound.h"
#include "game.h"
#include "camera.h"
#include "score.h"
#include "timer.h"
#include "bullet.h"
#include "player.h"
#include "effect.h"
#include "shadow.h"
//#include "fade.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME ("DATA\\MODEL\\ITEM00.x")
#define TEXTURE_NAME ("DATA\\UV\\�A�C�e��00_UV.jpg")
#define MAX_ITEM (1)	//�g�p���郂�f���̎��
#define MAX_ARRANGEMENT (5)	//�z�u���郂�f���̐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshBadItem[MAX_ARRANGEMENT] = {};
LPD3DXBUFFER g_pBuffMatBadItem[MAX_ARRANGEMENT] = {};
LPDIRECT3DTEXTURE9 g_pTextureBadItem[MAX_ARRANGEMENT]= {};

DWORD g_nNumMatBadItem[MAX_ARRANGEMENT] = {};

BADITEM g_BadItem[MAX_ARRANGEMENT];

D3DXVECTOR3 g_SabunBI[MAX_ARRANGEMENT];//���炩�ȕ����]���̂��߂Ɏg��

int g_nIdxShadowBI[MAX_ARRANGEMENT];

int g_NumBadItem;//�A�C�e���̑���

//=============================================================================
// ����������
//=============================================================================
void InitBadItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// �ʒu�E�����̏����ݒ�
		g_BadItem[nCnt].pos = D3DXVECTOR3(0, 0, 0);//�ʒu
		g_BadItem[nCnt].move = D3DXVECTOR3(0, 0, 0);//�ړ�
		g_BadItem[nCnt].rot = D3DXVECTOR3(0, 0, 0);//����
		g_BadItem[nCnt].bUse = false;
		g_BadItem[nCnt].bTouch = false;
		g_SabunBI[nCnt] = D3DXVECTOR3(0, 0, 0);//����
		g_NumBadItem = 0;

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureBadItem[nCnt]);

		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(MODEL_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatBadItem[nCnt],
			NULL,
			&g_nNumMatBadItem[nCnt],
			&g_pMeshBadItem[nCnt]);

		g_BadItem[nCnt].VtxMin = D3DXVECTOR3(10000, 10000, 10000);
		g_BadItem[nCnt].VtxMax = D3DXVECTOR3(-10000, -10000, -10000);

		int nNumVtx;										//���_��
		DWORD sizeFVF;										//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;										//���_�o�b�t�@�ւ̃|�C���^

		//���_�����擾
		nNumVtx = g_pMeshBadItem[nCnt]->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshBadItem[nCnt]->GetFVF());

		//���_�o�b�t�@�����b�N
		g_pMeshBadItem[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVer = 0; nCntVer < nNumVtx; nCntVer++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//���_���W�̑��

			if (g_BadItem[nCnt].VtxMin.x >= vtx.x)
			{
				g_BadItem[nCnt].VtxMin.x = vtx.x;
			}
			if (g_BadItem[nCnt].VtxMin.y >= vtx.y)
			{
				g_BadItem[nCnt].VtxMin.y = vtx.y;
			}
			if (g_BadItem[nCnt].VtxMin.z >= vtx.z)
			{
				g_BadItem[nCnt].VtxMin.z = vtx.z;
			}

			if (g_BadItem[nCnt].VtxMax.x <= vtx.x)
			{
				g_BadItem[nCnt].VtxMax.x = vtx.x;
			}
			if (g_BadItem[nCnt].VtxMax.y <= vtx.y)
			{
				g_BadItem[nCnt].VtxMax.y = vtx.y;
			}
			if (g_BadItem[nCnt].VtxMax.z <= vtx.z)
			{
				g_BadItem[nCnt].VtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//�T�C�Y���|�C���^��i�߂�
		}

		//���_�o�b�t�@���A�����b�N
		g_pMeshBadItem[nCnt]->UnlockVertexBuffer();

		//g_NumBadItem = 0;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitBadItem(void)
{
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// ���b�V���̊J��
		if (g_pMeshBadItem[nCnt] != NULL)
		{
			g_pMeshBadItem[nCnt]->Release();
			g_pMeshBadItem[nCnt] = NULL;
		}

		// �}�e���A���̊J��
		if (g_pBuffMatBadItem[nCnt] != NULL)
		{
			g_pBuffMatBadItem[nCnt]->Release();
			g_pBuffMatBadItem[nCnt] = NULL;
		}

		// �e�N�X�`���̔j��
		if (g_pTextureBadItem[nCnt] != NULL)
		{
			g_pTextureBadItem[nCnt]->Release();
			g_pTextureBadItem[nCnt] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBadItem(void)
{
	int nMove = 0;
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		if (g_BadItem[nCnt].bUse == true)
		{
			g_BadItem[nCnt].pos += g_BadItem[nCnt].move;

			//SetEffect(g_BadItem[nCnt].pos, D3DXCOLOR(15.0f, 15.0f, 15.0f, 15.0f), 15.0f, 20);

			if (g_BadItem[nCnt].pos.x > 300)
			{
				g_BadItem[nCnt].move.x = -3.0f;
			}
			if (g_BadItem[nCnt].pos.x < -300)
			{
				g_BadItem[nCnt].move.x = 3.0f;
			}

			g_BadItem[nCnt].rot.y -= 0.05f;

			SetPositionShadow(g_nIdxShadowBI[nCnt], D3DXVECTOR3(g_BadItem[nCnt].pos.x, 0.0f, g_BadItem[nCnt].pos.z));
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBadItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_BadItem[nCnt].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_BadItem[nCnt].rot.y, g_BadItem[nCnt].rot.x, g_BadItem[nCnt].rot.z);
		D3DXMatrixMultiply(&g_BadItem[nCnt].mtxWorld, &g_BadItem[nCnt].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_BadItem[nCnt].pos.x, g_BadItem[nCnt].pos.y, g_BadItem[nCnt].pos.z);
		D3DXMatrixMultiply(&g_BadItem[nCnt].mtxWorld, &g_BadItem[nCnt].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_BadItem[nCnt].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatBadItem[nCnt]->GetBufferPointer();

		if (g_BadItem[nCnt].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatBadItem[nCnt]; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureBadItem[nCnt]);

				// ���f��(�p�[�c)�̕`��
				g_pMeshBadItem[nCnt]->DrawSubset(nCntMat);

			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}


//=============================================================================
// �A�C�e���̐ݒ�
//=============================================================================

void SetBadItem(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// ���_���̍쐬
	//VERTEX_3D *pVtx;

	int nNumVtx;				//���_��
	DWORD sizeFVF;				//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		//���_�����擾
		nNumVtx = g_pMeshBadItem[nCnt]->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshBadItem[nCnt]->GetFVF());


		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pMeshBadItem[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		if (g_BadItem[nCnt].bUse == false)	//�u���b�N���g�p���Ă���
		{
			g_BadItem[nCnt].pos = pos;
			g_BadItem[nCnt].move = move;
			g_BadItem[nCnt].bUse = true;
			g_nIdxShadowBI[nCnt] = SetShadow(D3DXVECTOR3(g_BadItem[nCnt].pos.x, 0.0f, g_BadItem[nCnt].pos.z), D3DXVECTOR3(0, 0, 0));

			g_NumBadItem++;//�A�C�e���̑��������Z
			

			break;

		}

		// ���_�o�b�t�@���A�����b�N����
		g_pMeshBadItem[nCnt]->UnlockVertexBuffer();
	}
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
void CollisionBadItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMax,D3DXVECTOR3 *pVtxMin)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	TIMER *pTimer;
	pTimer = GetTimer();
	
	

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		if (g_BadItem[nCnt].bUse == true)
		{
			if (pPos->x+10 >= g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMin.x) &&
				pPos->x-10 <= g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMax.x))
			{
				if (pPos->z+10 >= g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMin.z) &&
					pPos->z-10 <= g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMax.z))
				{
					if (pPosOld->z+10 <= g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMin.z) &&
						pPos->z-10 >= g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMin.z))
					{//��O�̔���
						pPos->z = g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMin.z) - 10;
					}
					else if (pPosOld->z-10 >= g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMax.z) &&
						pPos->z-10 <= g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMax.z))
					{//���̔���
						pPos->z = g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMax.z) + 10;
					}
					if (pPosOld->x-10 >= g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMax.x) &&
						pPos->x-10 <= g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMax.x))
					{//�E�̔���
						pPos->x = g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMax.x) + 10;
					}
					else if (pPosOld->x+10 <= g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMin.x) &&
						pPos->x+10 >= g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMin.x))
					{//���̔���
						pPos->x = g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMin.x) - 10;
					}

					PlaySound(SOUND_LABEL_SE_HIT001);//�A�C�e�����莞�̉�

					AddScore(10000);//�A�C�e�����莞�̃|�C���g
					pTimer->nTime -= 2 * 100;//���Ԃ̑���

					g_BadItem[nCnt].bUse = false;//�A�C�e����\�����Ȃ�
					DeleteShadow(g_nIdxShadowBI[nCnt]);

					g_NumBadItem--;

					//if (g_NumBadItem <= 0)
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
BADITEM *GetBadItem(void)
{
		return &g_BadItem[MAX_ARRANGEMENT];
}
