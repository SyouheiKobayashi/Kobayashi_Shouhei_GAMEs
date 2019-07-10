//=============================================================================
// �g�������� [explosion.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "main.h"
#include "explosion.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_EXPLOSION		(128)		// �g�����ő�ۊǐ�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �����̍\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	int nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�����p�^�[��No.
	D3DXMATRIX mtxWorldExplosion;	//���[���h�}�g���b�N�X
	bool bUse;
} Explosion;

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];				//�g�������

//=============================================================================
// ����������
//=============================================================================
void InitExplosion(void)
{
	int nCntExplosion;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �g�������̏�����
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\���j�G�t�F�N�g.png", &g_pTextureExplosion);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-25, 25, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(25, 25, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-25, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(25, 0.0f, 0.0f);
		//pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�e�N�X�`���̐ݒ�
		/*pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);*/
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.166f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.166f);
		pVtx[3].tex = D3DXVECTOR2(0.166f, 0.166f);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
		pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
		pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
		pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		pVtx += 4;			//���_�f�[�^�̏����S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	
	VERTEX_3D*pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
		{
			if (g_aExplosion[nCntExplosion].bUse == true)	//�g�����g�p���
			{
				g_aExplosion[nCntExplosion].nCounterAnim++; //�J�E���^�[�̉��Z �����̑��x
				if (g_aExplosion[nCntExplosion].nCounterAnim % 3 == 0)
				{
					g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 30;//�p�^�[��No.�X�V
				}

				//	pVtx[nCntExplosion * 4].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 80, g_aExplosion[nCntExplosion].pos.y - 80, 0.0f);
				//	pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 80, g_aExplosion[nCntExplosion].pos.y - 80, 0.0f);
				//	pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 80, g_aExplosion[nCntExplosion].pos.y + 80, 0.0f);
				//	pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 80, g_aExplosion[nCntExplosion].pos.y+ 80, 0.0f);

					//���T�����@�c�U����
					pVtx[nCntExplosion*4].tex = D3DXVECTOR2(0.2f*g_aExplosion[nCntExplosion].nPatternAnim, 0.166f*(g_aExplosion[nCntExplosion].nPatternAnim / 5));
					pVtx[nCntExplosion*4+1].tex = D3DXVECTOR2(0.2f*g_aExplosion[nCntExplosion].nPatternAnim+0.2f, 0.166f*(g_aExplosion[nCntExplosion].nPatternAnim / 5));
					pVtx[nCntExplosion*4+2].tex = D3DXVECTOR2(0.2f*g_aExplosion[nCntExplosion].nPatternAnim, 0.166f*(g_aExplosion[nCntExplosion].nPatternAnim / 5)+0.166f);
					pVtx[nCntExplosion*4+3].tex = D3DXVECTOR2(0.2f*g_aExplosion[nCntExplosion].nPatternAnim+0.2f, 0.166f*(g_aExplosion[nCntExplosion].nPatternAnim / 5)+0.166f);

				if (g_aExplosion[nCntExplosion].nPatternAnim >= 29)
				{
					g_aExplosion[nCntExplosion].nPatternAnim = 0;
					g_aExplosion[nCntExplosion].bUse = false;
				}


				/*pVtx[nCntExplosion * 4].tex = D3DXVECTOR2(0.125f*g_aExplosion[nCntExplosion].nPatternAnim, 0.0f);
				pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2(0.125f*g_aExplosion[nCntExplosion].nPatternAnim + 0.125f, 0.0f);
				pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2(0.125f*g_aExplosion[nCntExplosion].nPatternAnim, 1.0f);
				pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2(0.125f*g_aExplosion[nCntExplosion].nPatternAnim + 0.125f, 1.0f);

				if (g_aExplosion[nCntExplosion].nPatternAnim >= 7)
				{
					g_aExplosion[nCntExplosion].nPatternAnim = 0;
					g_aExplosion[nCntExplosion].bUse = false;
				}*/


				//if (g_aExplosion[nCntExplosion].pos.y < -10)		//���̈ʒu����ʊO�ɂȂ�����
				//{
				//	g_aExplosion[nCntExplosion].bUse = false;
				//}

			}
		}
				//���_�o�b�t�@���A�����b�N
				g_pVtxBuffExplosion->Unlock();
}


//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplosion(void)
{
	int nCntExplosion;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxView, mtxTrans;//�v�Z�p�}�g���b�N�X


	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtxWorldExplosion);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_aExplosion[nCntExplosion].mtxWorldExplosion._11 = mtxView._11;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._12 = mtxView._21;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._13 = mtxView._31;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._21 = mtxView._12;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._22 = mtxView._22;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._23 = mtxView._32;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._31 = mtxView._13;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._32 = mtxView._23;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, g_aExplosion[nCntExplosion].pos.z);
			D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorldExplosion, &g_aExplosion[nCntExplosion].mtxWorldExplosion, &mtxTrans);


			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtxWorldExplosion);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureExplosion);

			// �|���S���̕`��
			if (g_aExplosion[nCntExplosion].bUse == true)		//�g�����g�p���
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
			}
		}
	}
}

//=============================================================================
// ���e�̐ݒ菈��
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DCOLOR col)
{
	int nCntExplosion;

	////���_���̐ݒ�
	//VERTEX_3D*pVtx;
	////���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	//g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)	//�g�����g�p���
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			g_aExplosion[nCntExplosion].bUse = true;//�g�p���Ă����Ԃɂ���
			break;
		}
		//pVtx += 4; //�|�C���^��i�߂�
	}
	////���_�o�b�t�@���A�����b�N
	//g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}


