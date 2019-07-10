//=============================================================================
// �|���S������ [bullet.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "bullet.h"
#include "shadow.h"
#include "effect.h"
#include "explosion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME ("DATA\\TEXTURE\\���Hbullet.png")
#define MAX_BULLET (222)
#define BULLET_SIZE (5.0f)
#define BULLET_POS (5.0f)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;

BULLET g_Bullet[MAX_BULLET];

int g_nIdxShadowBullet[MAX_BULLET];

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_Bullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//g_Bullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCntBullet].bUse = false;
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureBullet);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet2 = 0; nCntBullet2 < MAX_BULLET; nCntBullet2++)
	{
		//���_���W�̐ݒ�
		//g_Bullet[nCntBullet2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE, BULLET_SIZE + BULLET_POS, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE + BULLET_POS, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE + BULLET_POS, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BULLET_SIZE, -BULLET_SIZE + BULLET_POS, 0.0f);

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
	g_pVtxBuffBullet->Unlock();

}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
//^^^^^^^^^^^^^^^^^^^^^^^^^^
//		�e�̔��ːݒ�
//^^^^^^^^^^^^^^^^^^^^^^^^^^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)	
	{
		if (g_Bullet[nCntBullet].bUse == true)	//�����g�p����Ă���
		{
			SetEffect(g_Bullet[nCntBullet].pos, D3DXCOLOR(15.0f, 15.0f, 15.0f, 15.0f), 15.0f, 20);

			//�e�̎ˏo�����֘A
			g_Bullet[nCntBullet].pos += g_Bullet[nCntBullet].move;

			//��莞�Ԍo��
			g_Bullet[nCntBullet].nLife--;
			if (g_Bullet[nCntBullet].nLife <= 0)
			{
				SetExplosion(D3DXVECTOR3(g_Bullet[nCntBullet].pos.x, 0.0f, g_Bullet[nCntBullet].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				g_Bullet[nCntBullet].bUse = false;
				DeleteShadow(g_nIdxShadowBullet[nCntBullet]);
			}
			SetPositionShadow(g_nIdxShadowBullet[nCntBullet], D3DXVECTOR3(g_Bullet[nCntBullet].pos.x, 0.0f, g_Bullet[nCntBullet].pos.z));

		}
		
	}
	
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	D3DXMATRIX mtxView, mtxTrans;//�v�Z�p�}�g���b�N�X

	 //�A���t�@�e�X�g����(�������ɂ��摜�̐؂��茻�ۂ𖳌��ɂ���)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);//REF = Reference:�Q��
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//FUNC = Function:�@�\ //GREATER = �`���傫��


	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Bullet[nCntBullet].mtxWorldBullet);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_Bullet[nCntBullet].mtxWorldBullet._11 = mtxView._11;
			g_Bullet[nCntBullet].mtxWorldBullet._12 = mtxView._21;
			g_Bullet[nCntBullet].mtxWorldBullet._13 = mtxView._31;
			g_Bullet[nCntBullet].mtxWorldBullet._21 = mtxView._12;
			g_Bullet[nCntBullet].mtxWorldBullet._22 = mtxView._22;
			g_Bullet[nCntBullet].mtxWorldBullet._23 = mtxView._32;
			g_Bullet[nCntBullet].mtxWorldBullet._31 = mtxView._13;
			g_Bullet[nCntBullet].mtxWorldBullet._32 = mtxView._23;
			g_Bullet[nCntBullet].mtxWorldBullet._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Bullet[nCntBullet].pos.x, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_Bullet[nCntBullet].mtxWorldBullet, &g_Bullet[nCntBullet].mtxWorldBullet, &mtxTrans);


			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCntBullet].mtxWorldBullet);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));


			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// ���̐ݒ�
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// ���_���̍쐬
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == false)
		{
			g_Bullet[nCntBullet].nLife = 100;//�e�̐�������/����
			g_Bullet[nCntBullet].pos = pos;
			g_Bullet[nCntBullet].move = move;
			g_Bullet[nCntBullet].bUse = true;
			g_nIdxShadowBullet[nCntBullet] = SetShadow(D3DXVECTOR3(g_Bullet[nCntBullet].pos.x, 0.0f, g_Bullet[nCntBullet].pos.z), D3DXVECTOR3(0, 0, 0));
			break;
		}
		//pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

