//=============================================================================
// ��Q���p���f������ [fallingRocks.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "fallingRocks.h"
#include "sound.h"
#include "game.h"
#include "fade.h"
#include "camera.h"
#include "timer.h"
#include "bullet.h"
#include "player.h"
#include "shadow.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME ("DATA\\MODEL\\STONE00.x")
#define TEXTURE_NAME ("DATA\\TEXTURE\\���A�V��.jpg")
#define MAX_ITEM (1)	//�g�p���郂�f���̎��
#define MAX_ARRANGEMENT (7)	//�z�u���郂�f���̐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshFallingRocks[MAX_ARRANGEMENT] = {};
LPD3DXBUFFER g_pBuffMatFallingRocks[MAX_ARRANGEMENT] = {};
LPDIRECT3DTEXTURE9 g_pTextureFallingRocks[MAX_ARRANGEMENT]= {};

DWORD g_nNumMatFallingRocks[MAX_ARRANGEMENT] = {};

FALLINGROCKS g_FallingRocks[MAX_ARRANGEMENT];

D3DXVECTOR3 g_SabunFR[MAX_ARRANGEMENT];//���炩�ȕ����]���̂��߂Ɏg��

//int g_nIdxShadowFR[MAX_ARRANGEMENT];

PLAYER *pPlayer;

//=============================================================================
// ����������
//=============================================================================
void InitFallingRocks(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// �ʒu�E�����̏����ݒ�
		g_FallingRocks[nCnt].pos = D3DXVECTOR3(0, 0, 0);//�ʒu
		g_FallingRocks[nCnt].move = D3DXVECTOR3(0, 0, 0);//�ړ�
		g_FallingRocks[nCnt].rot = D3DXVECTOR3(0, 0, 0);//����
		g_FallingRocks[nCnt].nType = 0;
		g_FallingRocks[nCnt].bUse = false;
		g_FallingRocks[nCnt].bTouch = false;
		g_SabunFR[nCnt] = D3DXVECTOR3(0, 0, 0);//����

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureFallingRocks[nCnt]);

		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(MODEL_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatFallingRocks[nCnt],
			NULL,
			&g_nNumMatFallingRocks[nCnt],
			&g_pMeshFallingRocks[nCnt]);

		g_FallingRocks[nCnt].VtxMin = D3DXVECTOR3(10000, 10000, 10000);
		g_FallingRocks[nCnt].VtxMax = D3DXVECTOR3(-10000, -10000, -10000);

		int nNumVtx;										//���_��
		DWORD sizeFVF;										//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;										//���_�o�b�t�@�ւ̃|�C���^

		//���_�����擾
		nNumVtx = g_pMeshFallingRocks[nCnt]->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshFallingRocks[nCnt]->GetFVF());

		//���_�o�b�t�@�����b�N
		g_pMeshFallingRocks[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVer = 0; nCntVer < nNumVtx; nCntVer++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//���_���W�̑��

			if (g_FallingRocks[nCnt].VtxMin.x >= vtx.x)
			{
				g_FallingRocks[nCnt].VtxMin.x = vtx.x;
			}
			if (g_FallingRocks[nCnt].VtxMin.y >= vtx.y)
			{
				g_FallingRocks[nCnt].VtxMin.y = vtx.y;
			}
			if (g_FallingRocks[nCnt].VtxMin.z >= vtx.z)
			{
				g_FallingRocks[nCnt].VtxMin.z = vtx.z;
			}

			if (g_FallingRocks[nCnt].VtxMax.x <= vtx.x)
			{
				g_FallingRocks[nCnt].VtxMax.x = vtx.x;
			}
			if (g_FallingRocks[nCnt].VtxMax.y <= vtx.y)
			{
				g_FallingRocks[nCnt].VtxMax.y = vtx.y;
			}
			if (g_FallingRocks[nCnt].VtxMax.z <= vtx.z)
			{
				g_FallingRocks[nCnt].VtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//�T�C�Y���|�C���^��i�߂�
		}

		//���_�o�b�t�@���A�����b�N
		g_pMeshFallingRocks[nCnt]->UnlockVertexBuffer();

		//g_NumFallingRocks = 0;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitFallingRocks(void)
{
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// ���b�V���̊J��
		if (g_pMeshFallingRocks[nCnt] != NULL)
		{
			g_pMeshFallingRocks[nCnt]->Release();
			g_pMeshFallingRocks[nCnt] = NULL;
		}

		// �}�e���A���̊J��
		if (g_pBuffMatFallingRocks[nCnt] != NULL)
		{
			g_pBuffMatFallingRocks[nCnt]->Release();
			g_pBuffMatFallingRocks[nCnt] = NULL;
		}

		// �e�N�X�`���̔j��
		if (g_pTextureFallingRocks[nCnt] != NULL)
		{
			g_pTextureFallingRocks[nCnt]->Release();
			g_pTextureFallingRocks[nCnt] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFallingRocks(void)
{
	int nMove = 0;
	pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		if (g_FallingRocks[nCnt].bUse == true)
		{
			g_FallingRocks[nCnt].pos += g_FallingRocks[nCnt].move;

			if (g_FallingRocks[nCnt].pos.x > 300)
			{
				g_FallingRocks[nCnt].move.x = -2.0f;
			}
			if (g_FallingRocks[nCnt].pos.x < -300)
			{
				g_FallingRocks[nCnt].move.x = 2.0f;
			}

			if (g_FallingRocks[nCnt].nType == 0)
			{
				if (pPlayer->pos.z > -2400)//�v���C���[�w��ʒu�ɓ��B�����ꍇ
				{
					
					g_FallingRocks[nCnt].move.y = -19.0f;
					
				}
			}
			if (g_FallingRocks[nCnt].nType == 1)
			{
				if (pPlayer->pos.z > -1600)//�v���C���[�w��ʒu�ɓ��B�����ꍇ
				{
					g_FallingRocks[nCnt].move.y = -19.0f;
				}
			}
			if (g_FallingRocks[nCnt].nType == 2)
			{
				if (pPlayer->pos.z > -800)//�v���C���[�w��ʒu�ɓ��B�����ꍇ
				{
					g_FallingRocks[nCnt].move.y = -19.0f;
				}
			}
			if (g_FallingRocks[nCnt].nType == 3)
			{
				if (pPlayer->pos.z > 0)//�v���C���[�w��ʒu�ɓ��B�����ꍇ
				{
					g_FallingRocks[nCnt].move.y = -19.0f;
				}
			}
			if (g_FallingRocks[nCnt].nType == 4)
			{
				if (pPlayer->pos.z > 800)//�v���C���[�w��ʒu�ɓ��B�����ꍇ
				{
					g_FallingRocks[nCnt].move.y = -19.0f;
				}
			}
			if (g_FallingRocks[nCnt].nType == 5)
			{
				if (pPlayer->pos.z > 1600)//�v���C���[�w��ʒu�ɓ��B�����ꍇ
				{
					g_FallingRocks[nCnt].move.y = -19.0f;
				}
			}
			if (g_FallingRocks[nCnt].nType == 6)
			{
				if (pPlayer->pos.z > 1800)//�v���C���[�w��ʒu�ɓ��B�����ꍇ
				{
					g_FallingRocks[nCnt].move.y = -19.0f;
				}
			}
			//�����Ύw��pos���B���Amove��0(move��0�ɂ����ꍇ�A�������蔻��ɏ�����Ă��鏈�����s��)
			if (g_FallingRocks[nCnt].pos.y <= 0)
			{
				g_FallingRocks[nCnt].move.y = 0;
				g_FallingRocks[nCnt].move.x = 0;
				
					
			}
			if (g_FallingRocks[nCnt].pos.y >= 650&& g_FallingRocks[nCnt].pos.y <= 700)
			{
				PlaySound(SOUND_LABEL_SE_FALL);//�A�C�e�����莞�̉�
			}

			//SetPositionShadow(g_nIdxShadowFR[nCnt], D3DXVECTOR3(g_FallingRocks[nCnt].pos.x, 0.0f, g_FallingRocks[nCnt].pos.z));
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFallingRocks(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_FallingRocks[nCnt].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_FallingRocks[nCnt].rot.y, g_FallingRocks[nCnt].rot.x, g_FallingRocks[nCnt].rot.z);
		D3DXMatrixMultiply(&g_FallingRocks[nCnt].mtxWorld, &g_FallingRocks[nCnt].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_FallingRocks[nCnt].pos.x, g_FallingRocks[nCnt].pos.y, g_FallingRocks[nCnt].pos.z);
		D3DXMatrixMultiply(&g_FallingRocks[nCnt].mtxWorld, &g_FallingRocks[nCnt].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_FallingRocks[nCnt].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatFallingRocks[nCnt]->GetBufferPointer();

		if (g_FallingRocks[nCnt].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatFallingRocks[nCnt]; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureFallingRocks[nCnt]);

				// ���f��(�p�[�c)�̕`��
				g_pMeshFallingRocks[nCnt]->DrawSubset(nCntMat);

			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}


//=============================================================================
// �A�C�e���̐ݒ�
//=============================================================================

void SetFallingRocks(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType)
{
	// ���_���̍쐬
	//VERTEX_3D *pVtx;

	int nNumVtx;				//���_��
	DWORD sizeFVF;				//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		//���_�����擾
		nNumVtx = g_pMeshFallingRocks[nCnt]->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshFallingRocks[nCnt]->GetFVF());


		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pMeshFallingRocks[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		if (g_FallingRocks[nCnt].bUse == false)	//�u���b�N���g�p���Ă���
		{
			g_FallingRocks[nCnt].pos = pos;
			g_FallingRocks[nCnt].move = move;
			g_FallingRocks[nCnt].nType = nType;
			g_FallingRocks[nCnt].bUse = true;
			//g_nIdxShadowFR[nCnt] = SetShadow(D3DXVECTOR3(g_FallingRocks[nCnt].pos.x, 0.0f, g_FallingRocks[nCnt].pos.z), D3DXVECTOR3(0, 0, 0));

			break;

		}

		// ���_�o�b�t�@���A�����b�N����
		g_pMeshFallingRocks[nCnt]->UnlockVertexBuffer();
	}
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
void CollisionFallingRocks(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMax,D3DXVECTOR3 *pVtxMin)
{
	
	pPlayer = GetPlayer();

	TIMER *pTimer;
	pTimer = GetTimer();
	
	

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		if (g_FallingRocks[nCnt].bUse == true)
		{
			if (pPos->x+10 >= g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMin.x) &&
				pPos->x-10 <= g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMax.x))
			{
				if (pPos->z+10 >= g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMin.z) &&
					pPos->z-10 <= g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMax.z))
				{
					if (pPos->y + 10 >= g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMin.y) &&
						pPos->y - 10 <= g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMax.y))
					{
						if (g_FallingRocks[nCnt].move.y != 0)
						{
							FADE pFade;

							pFade = *GetFade();

							//���[�h�ݒ�
							SetFade(MODE_RESULT);

							pPlayer->move = D3DXVECTOR3(0, 0, 0);//�ړ��ʂ�0�ɂ���
						}

						if (pPosOld->z + 10 <= g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMin.z) &&
							pPos->z + 10 >= g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMin.z))
						{//��O�̔���
							pPos->z = g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMin.z) - 10;
						}
						else if (pPosOld->z - 10 >= g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMax.z) &&
							pPos->z - 10 <= g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMax.z))
						{//���̔���
							pPos->z = g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMax.z) + 10;
						}
						if (pPosOld->x - 10 >= g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMax.x) &&
							pPos->x - 10 <= g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMax.x))
						{//�E�̔���
							pPos->x = g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMax.x) + 10;
						}
						else if (pPosOld->x + 10 <= g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMin.x) &&
							pPos->x + 10 >= g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMin.x))
						{//���̔���
							pPos->x = g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMin.x) - 10;
						}

						if (pPosOld->y + 10 <= g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMin.y) &&
							pPos->y - 10 >= g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMin.y))
						{//���̔���
							pPos->y = g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMin.y) - 10;

						

						}
						else if (pPosOld->y - 10 >= g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMax.y) &&
							pPos->y - 10 <= g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMax.y))
						{//��̔���
							pPos->y = g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMax.y) + 10;

						}
					}
					
				}
			}

		}
	}
}

//=============================================================================
// ��Q���p���f�����̎擾
//=============================================================================
FALLINGROCKS *GetFallingRocks(void)
{
		return &g_FallingRocks[MAX_ARRANGEMENT];
}
