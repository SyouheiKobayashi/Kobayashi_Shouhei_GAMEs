//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#include "callout.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_CALLOUT0		"data/TEXTURE/callout_00.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_CALLOUT1		"data/TEXTURE/callout_01.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_CALLOUT2		"data/TEXTURE/callout_02.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_CALLOUT3		"data/TEXTURE/callout_03.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_CALLOUT4		"data/TEXTURE/callout_04.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_CALLOUT5		"data/TEXTURE/callout_05.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define MAX_TEXTURE	(2)

#define MAX_CALLOUT	(1)

#define CALLOUT_SIZE	(100.0f)	// �傫��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexCallout(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureCallout[MAX_TEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCallout = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPresent = NULL;
CALLOUT g_aCallout[MAX_CALLOUT];

//=============================================================================
// ����������
//=============================================================================
void InitCallout(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntCallout = 0; nCntCallout < MAX_CALLOUT; nCntCallout++)
	{
		// ������
		g_aCallout[nCntCallout].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCallout[nCntCallout].nType = 0;
		g_aCallout[nCntCallout].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_CALLOUT0, &g_pTextureCallout[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_CALLOUT1, &g_pTextureCallout[1]);

	// ���_���̍쐬
	MakeVertexCallout(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitCallout(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (g_pTextureCallout[nCntTex] != NULL)
		{
			g_pTextureCallout[nCntTex]->Release();
			g_pTextureCallout[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCallout != NULL)
	{
		g_pVtxBuffCallout->Release();
		g_pVtxBuffCallout = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCallout(void)
{
	for (int nCntCallout = 0; nCntCallout < MAX_CALLOUT; nCntCallout++)
	{
		if (g_aCallout[nCntCallout].bUse == true)
		{
			switch (g_aCallout[nCntCallout].type)
			{
			case CALLOUTTYPE_NONE:
				break;

			case CALLOUTTYPE_CHANGE:
				g_aCallout[nCntCallout].nType = 0;
				break;

			case CALLOUTTYPE_PRESENT1:
				g_aCallout[nCntCallout].nType = 1;
				break;

			case CALLOUTTYPE_PRESENT2:
				g_aCallout[nCntCallout].nType = 2;
				break;

			case CALLOUTTYPE_PRESENT3:
				g_aCallout[nCntCallout].nType = 3;
				break;

			case CALLOUTTYPE_PRESENT4:
				g_aCallout[nCntCallout].nType = 4;
				break;

			case CALLOUTTYPE_PRESENT5:
				g_aCallout[nCntCallout].nType = 5;
				break;

			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCallout(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCallout, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntCallout = 0; nCntCallout < MAX_CALLOUT; nCntCallout++)
	{
		if(g_aCallout[nCntCallout].bUse == true)
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureCallout[g_aCallout[nCntCallout].nType]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntCallout, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexCallout(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntCallout;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_CALLOUT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCallout,
		NULL);

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCallout->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCallout = 0; nCntCallout < MAX_CALLOUT; nCntCallout++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aCallout[nCntCallout].pos.x - CALLOUT_SIZE, g_aCallout[nCntCallout].pos.y - CALLOUT_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aCallout[nCntCallout].pos.x + CALLOUT_SIZE, g_aCallout[nCntCallout].pos.y - CALLOUT_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aCallout[nCntCallout].pos.x - CALLOUT_SIZE, g_aCallout[nCntCallout].pos.y + CALLOUT_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCallout[nCntCallout].pos.x + CALLOUT_SIZE, g_aCallout[nCntCallout].pos.y + CALLOUT_SIZE, 0.0f);

		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCallout->Unlock();
}

//=============================================================================
// �����o���̐ݒ�
//=============================================================================
int SetCallout(D3DXVECTOR3 pos, CALLOUTTYPE type)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	int nCntCallout;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCallout->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCallout = 0; nCntCallout < MAX_CALLOUT; nCntCallout++)
	{
		if (g_aCallout[nCntCallout].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ�
			g_aCallout[nCntCallout].pos = pos;
			g_aCallout[nCntCallout].type = type;
			g_aCallout[nCntCallout].bUse = true;	//�g�p���Ă����Ԃɂ���

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aCallout[nCntCallout].pos.x - CALLOUT_SIZE, g_aCallout[nCntCallout].pos.y - CALLOUT_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aCallout[nCntCallout].pos.x + CALLOUT_SIZE, g_aCallout[nCntCallout].pos.y - CALLOUT_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aCallout[nCntCallout].pos.x - CALLOUT_SIZE, g_aCallout[nCntCallout].pos.y + CALLOUT_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aCallout[nCntCallout].pos.x + CALLOUT_SIZE, g_aCallout[nCntCallout].pos.y + CALLOUT_SIZE, 0.0f);

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffCallout->Unlock();

	return nCntCallout;
}

//=============================================================================
// �����o��������
//=============================================================================
void DeleteCallout(int nIdxCallout)
{
	if (g_aCallout[nIdxCallout].bUse == true)
	{
		g_aCallout[nIdxCallout].bUse = false;
	}
}
