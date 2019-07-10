//=============================================================================
//
// �Ꮘ�� [snow.cpp]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#include "snow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SNOW_TEXTURENAME	"data/TEXTURE/shadow000.jpg"
#define MAX_SNOW		(2020)	// ��̍ő吔
#define SNOW_APPEAR		(65)		// �o������Ԋu

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSnow = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSnow = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
SNOW g_aSnow[MAX_SNOW];
int g_nCntSnow;

//=============================================================================
// �|���S������������
//=============================================================================
void InitSnow(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �W�F�l���[�^�̏���������
	for (int nCntSnow = 0; nCntSnow < MAX_SNOW; nCntSnow++)
	{
		g_aSnow[nCntSnow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSnow[nCntSnow].fRadius = 0;
		g_aSnow[nCntSnow].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aSnow[nCntSnow].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSnow[nCntSnow].bUse = false;
	}

	g_nCntSnow = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, SNOW_TEXTURENAME, &g_pTextureSnow);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SNOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSnow,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSnow->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�̍��W
	for (int nCntSnow = 0; nCntSnow < MAX_SNOW; nCntSnow++)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aSnow[nCntSnow].fRadius, -g_aSnow[nCntSnow].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aSnow[nCntSnow].fRadius, -g_aSnow[nCntSnow].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aSnow[nCntSnow].fRadius, g_aSnow[nCntSnow].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aSnow[nCntSnow].fRadius, g_aSnow[nCntSnow].fRadius, 0.0f);

		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffSnow->Unlock();
}

//=============================================================================
// �|���S���I������
//=============================================================================
void UninitSnow(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureSnow != NULL)
	{
		g_pTextureSnow->Release();
		g_pTextureSnow = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffSnow != NULL)
	{
		g_pVtxBuffSnow->Release();
		g_pVtxBuffSnow = NULL;
	}
}

//=============================================================================
// �|���S���X�V����
//=============================================================================
void UpdateSnow(void)
{
	int nCntSnow;
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSnow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSnow = 0; nCntSnow < MAX_SNOW; nCntSnow++)
	{
		g_nCntSnow = (g_nCntSnow + 1) % SNOW_APPEAR;	// ����o���Ԋu�̃J�E���^

		if (g_aSnow[nCntSnow].bUse == true)
		{// �g���Ă���
			if (g_aSnow[nCntSnow].pos.y > SCREEN_HEIGHT || g_aSnow[nCntSnow].pos.x < 0 || g_aSnow[nCntSnow].pos.x > SCREEN_WIDTH)
			{
				g_aSnow[nCntSnow].bUse = false;
			}

			g_aSnow[nCntSnow].pos += g_aSnow[nCntSnow].move;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aSnow[nCntSnow].pos.x - g_aSnow[nCntSnow].fRadius, g_aSnow[nCntSnow].pos.y - g_aSnow[nCntSnow].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aSnow[nCntSnow].pos.x + g_aSnow[nCntSnow].fRadius, g_aSnow[nCntSnow].pos.y - g_aSnow[nCntSnow].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSnow[nCntSnow].pos.x - g_aSnow[nCntSnow].fRadius, g_aSnow[nCntSnow].pos.y + g_aSnow[nCntSnow].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aSnow[nCntSnow].pos.x + g_aSnow[nCntSnow].fRadius, g_aSnow[nCntSnow].pos.y + g_aSnow[nCntSnow].fRadius, 0.0f);
		}
		else
		{
			if (g_nCntSnow == 0)
			{// ��莞�Ԍo�߂Ő���~�炷
				g_aSnow[nCntSnow].pos = D3DXVECTOR3(rand() % SCREEN_WIDTH * 1.0f, -10.0f, 0.0f);
				g_aSnow[nCntSnow].move = D3DXVECTOR3(rand() % 3 * 0.1f, 1.0f, 0.0f);
				g_aSnow[nCntSnow].fRadius = 5.0f;
				g_aSnow[nCntSnow].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
				g_aSnow[nCntSnow].bUse = true;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(-g_aSnow[nCntSnow].fRadius, -g_aSnow[nCntSnow].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aSnow[nCntSnow].fRadius, -g_aSnow[nCntSnow].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_aSnow[nCntSnow].fRadius, g_aSnow[nCntSnow].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aSnow[nCntSnow].fRadius, g_aSnow[nCntSnow].fRadius, 0.0f);

				// ���_�J���[
				pVtx[0].col = g_aSnow[nCntSnow].col;
				pVtx[1].col = g_aSnow[nCntSnow].col;
				pVtx[2].col = g_aSnow[nCntSnow].col;
				pVtx[3].col = g_aSnow[nCntSnow].col;

				break;
			}
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffSnow->Unlock();
}

//=============================================================================
// �|���S���`�揈��
//=============================================================================
void DrawSnow(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntSnow = 0; nCntSnow < MAX_SNOW; nCntSnow++)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pVtxBuffSnow, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		if (g_aSnow[nCntSnow].bUse == true)
		{//�u���b�N���g�p����Ă���
		 //�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSnow);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntSnow, 2);
		}
	}

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
