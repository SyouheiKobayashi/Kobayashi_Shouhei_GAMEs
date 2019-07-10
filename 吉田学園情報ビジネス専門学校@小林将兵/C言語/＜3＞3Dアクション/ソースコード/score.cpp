//=============================================================================
// �X�R�A���� [score.cpp]
// Author:Kobayashi/���� ����
//=============================================================================
#include "score.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_SCORE		"DATA\\TEXTURE\\number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TATE_POS (35)
#define YOKO_POS (925)
#define TATE_SIZE (25)
#define YOKO_SIZE (25)
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int						g_nScore;					// �X�R�A
D3DXVECTOR3				g_posScore;					// �ʒu

//=============================================================================
// ����������
//=============================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nScore = 0;

	g_posScore = D3DXVECTOR3(YOKO_POS, TATE_POS, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,		// �t�@�C���̖��O
								&g_pTextureScore);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexScore(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	int nCount;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	
	// �|���S���̕`��
	for (nCount = 0; nCount < 8; nCount++)
	{
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCount,2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntScore;

	// [���_�o�b�t�@�𐶐�]
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// [���_����ݒ�]
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - YOKO_SIZE, g_posScore.y - TATE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + YOKO_SIZE, g_posScore.y - TATE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - YOKO_SIZE, g_posScore.y + TATE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + YOKO_SIZE, g_posScore.y + TATE_SIZE, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
		g_posScore.x += 40;//�Ԋu
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddScore(int nValue)
{
	int nScoreNo[8];
	int nCntScoreNo;

	g_nScore += nValue;

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	nScoreNo[0] = g_nScore / 10000000;
	nScoreNo[1] = g_nScore % 10000000 / 1000000;
	nScoreNo[2] = g_nScore % 1000000 / 100000;
	nScoreNo[3] = g_nScore % 100000 / 10000;
	nScoreNo[4] = g_nScore % 10000 / 1000;
	nScoreNo[5] = g_nScore % 1000 / 100;
	nScoreNo[6] = g_nScore % 100 / 10;
	nScoreNo[7] = g_nScore % 10;

	for (nCntScoreNo = 0; nCntScoreNo < 8; nCntScoreNo++)
	{
	pVtx[0].tex = D3DXVECTOR2(0.0f + nScoreNo[nCntScoreNo] * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + nScoreNo[nCntScoreNo] * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + nScoreNo[nCntScoreNo] * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + nScoreNo[nCntScoreNo] * 0.1f, 1.0f);

	pVtx += 4;

	}
	
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
 }
