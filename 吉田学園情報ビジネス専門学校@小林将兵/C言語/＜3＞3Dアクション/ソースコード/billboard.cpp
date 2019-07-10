//=============================================================================
// �|���S������ [billboard.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "billboard.h"
#include "player.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME ("DATA\\TEXTURE\\error00.png")
#define TEXTURE_NAME02 ("DATA\\TEXTURE\\�����N�����.png")
#define TEXTURE_NAME03 ("DATA\\TEXTURE\\arrow.png")
#define MAX_BILLBOARD (50)
#define MAX_TYPE (3)

PLAYER *pPlayer_BillBoard;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureBillboard[MAX_TYPE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;

BILLBOARD g_Billboard[MAX_BILLBOARD];

//int g_nIdxShadowB[MAX_BILLBOARD];

//=============================================================================
// ����������
//=============================================================================
void InitBillboard(void)
{
	int nCntBillboard;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_Billboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCntBillboard].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCntBillboard].nType = 0;
		g_Billboard[nCntBillboard].bUse = false;
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureBillboard[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME02, &g_pTextureBillboard[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME03, &g_pTextureBillboard[2]);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

				   //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		//���_���W�̐ݒ�
		//g_posBillboard = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	g_pVtxBuffBillboard->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBillboard(void)
{
	for (int nCnt = 0; nCnt < MAX_TYPE; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureBillboard[nCnt] != NULL)
		{
			g_pTextureBillboard[nCnt]->Release();
			g_pTextureBillboard[nCnt] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBillboard(void)
{
	pPlayer_BillBoard = GetPlayer();

	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

				   //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == true)
		{
			if (g_Billboard[nCntBillboard].nType == 2)
			{
				//g_Billboard[nCntBillboard].pos.x++;
			}
			
			//SetPositionShadow(g_nIdxShadowB[nCntBillboard], D3DXVECTOR3(g_Billboard[nCntBillboard].pos.x, 0.0f, g_Billboard[nCntBillboard].pos.z));
			if (g_Billboard[nCntBillboard].pos.x > 300)
			{
				//g_Billboard[nCntBillboard].pos.x = 0;
			}
		}
		if (g_Billboard[nCntBillboard].nType == 0)
		{//���v���C���[����ɕ\��
			g_Billboard[nCntBillboard].pos.x = pPlayer_BillBoard->pos.x;
			g_Billboard[nCntBillboard].pos.z = pPlayer_BillBoard->pos.z;
			//���w��͈͂̏ꍇ�댯�������}�[�N��\��
			if (pPlayer_BillBoard->pos.z > -2400&& pPlayer_BillBoard->pos.z < -2300||
				pPlayer_BillBoard->pos.z > -1600 && pPlayer_BillBoard->pos.z < -1500||
				pPlayer_BillBoard->pos.z > -800 && pPlayer_BillBoard->pos.z < -700||
				pPlayer_BillBoard->pos.z > 0 && pPlayer_BillBoard->pos.z < 100||
				pPlayer_BillBoard->pos.z > 800 && pPlayer_BillBoard->pos.z < 900||
				pPlayer_BillBoard->pos.z > 1600 && pPlayer_BillBoard->pos.z < 1700||
				pPlayer_BillBoard->pos.z > 1800 && pPlayer_BillBoard->pos.z < 1900)
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else//���w��͈͊O�̏ꍇ�͔�\��
			{
				
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBillboard->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBillboard(void)
{
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	D3DXMATRIX mtxView, mtxTrans, mtxRot;//�v�Z�p�}�g���b�N�X

	 //�A���t�@�e�X�g����(�������ɂ��摜�̐؂��茻�ۂ𖳌��ɂ���)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);//REF = Reference:�Q��
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//FUNC = Function:�@�\ //GREATER = �`���傫��

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Billboard[nCntBillboard].mtxWorldBillboard);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			if (g_Billboard[nCntBillboard].nType == 0 || g_Billboard[nCntBillboard].nType == 1)
			{
				g_Billboard[nCntBillboard].mtxWorldBillboard._11 = mtxView._11;
				g_Billboard[nCntBillboard].mtxWorldBillboard._12 = mtxView._21;
				g_Billboard[nCntBillboard].mtxWorldBillboard._13 = mtxView._31;
				g_Billboard[nCntBillboard].mtxWorldBillboard._21 = mtxView._12;
				g_Billboard[nCntBillboard].mtxWorldBillboard._22 = mtxView._22;
				g_Billboard[nCntBillboard].mtxWorldBillboard._23 = mtxView._32;
				g_Billboard[nCntBillboard].mtxWorldBillboard._31 = mtxView._13;
				g_Billboard[nCntBillboard].mtxWorldBillboard._32 = mtxView._23;
				g_Billboard[nCntBillboard].mtxWorldBillboard._33 = mtxView._33;
			}

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Billboard[nCntBillboard].pos.x, g_Billboard[nCntBillboard].pos.y, g_Billboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_Billboard[nCntBillboard].mtxWorldBillboard, &g_Billboard[nCntBillboard].mtxWorldBillboard, &mtxTrans);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Billboard[nCntBillboard].rot.y, g_Billboard[nCntBillboard].rot.x, g_Billboard[nCntBillboard].rot.z);
			D3DXMatrixMultiply(&g_Billboard[nCntBillboard].mtxWorldBillboard, &g_Billboard[nCntBillboard].mtxWorldBillboard, &mtxRot);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Billboard[nCntBillboard].mtxWorldBillboard);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
			{
				if (g_Billboard[nCntBillboard].bUse == true)
				{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureBillboard[g_Billboard[nCntBillboard].nType]);
					// �|���S���̕`��
					pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillboard * 4, 2);
				}
			}
		}
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// �r���{�[�h�̐ݒ�
//=============================================================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{

	int nSize = 0;
	// ���_���̍쐬
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == false)
		{
			g_Billboard[nCntBillboard].pos = pos;
			g_Billboard[nCntBillboard].rot = rot;
			g_Billboard[nCntBillboard].nType = nType;
			g_Billboard[nCntBillboard].bUse = true;
			//g_nIdxShadowB[nCntBillboard] = SetShadow(D3DXVECTOR3(g_Billboard[nCntBillboard].pos.x, 0.0f, g_Billboard[nCntBillboard].pos.z), D3DXVECTOR3(0, 0, 0));

			if (nType == 0|| nType == 1)
			{
				nSize = 10;
			}

			if (nType == 2)
			{
				nSize = 50;
			}

			pVtx[0].pos = D3DXVECTOR3(-10.0f- nSize, 20.0f + (nSize*2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(10.0f + nSize, 20.0f + (nSize*2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-10.0f - nSize, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(10.0f + nSize, 0.0f, 0.0f);


			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBillboard->Unlock();
}