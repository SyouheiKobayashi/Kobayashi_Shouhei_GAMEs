//=============================================================================
// �����L���O�̏��� [ranking.cpp]
// Author : Kobayashi / ���� ����
//=============================================================================
#include "ranking.h"
#include "main.h"
#include "fade.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RANKING		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RANKING_CHARACTER	"data/TEXTURE/ranking000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

#define MAX_TEXTURE_TYPE (2) //�e�N�X�`����
#define MAX_DIGIT (5)	//����
#define MAX_RANKING (5)	//�����L���O��
#define MAX_OTHER (3)
#define CHANGE_RANKING (6)//����ւ��p
#define MAX_NUMER (40) // �����̑���

#define SCORE_No_X (60.0f) //�X�R�A�i���o�[�̕��T�C�Y
#define SCORE_No_Y (80.0f)//�X�R�A�i���o�[�̏c�T�C�Y

#define RANKING_POS ((D3DXVECTOR3(750.0f, 180.0f, 0.0f))) //�����L���O�̈ʒu

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRanking[MAX_TEXTURE_TYPE] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
static int				g_nRanking[MAX_RANKING] = { 3333, 600, 4000, 2222, 1800 };//�����X�R�A
D3DXCOLOR				g_Collar[MAX_RANKING + 1];
int g_NewScore;

int nCntHighScore;
int g_nCntFade; //�����t�F�[�h

//=============================================================================
// ����������
//=============================================================================
void InitRanking(void)
{
	g_nCntFade = 0;
	nCntHighScore = 0;
	g_nCntFade = 0;
	for (int nCnt = 0; nCnt < MAX_RANKING + 1; nCnt++)
	{
		g_Collar[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING, &g_pTextureRanking[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING_CHARACTER, &g_pTextureRanking[1]);

	// ���_���̍쐬
	MakeVertexRanking(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitRanking(void)
{
	for (int nCntRankingTex = 0; nCntRankingTex < MAX_TEXTURE_TYPE; nCntRankingTex++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureRanking[nCntRankingTex] != NULL)
		{
			g_pTextureRanking[nCntRankingTex]->Release();
			g_pTextureRanking[nCntRankingTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRanking(void)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	FADE pFade;
	pFade = *GetFade();

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//���[�h�I��
			SetFade(MODE_TITLE);
		}
	}

	g_nCntFade++;
	if (g_nCntFade >= 200)
	{
		if (pFade == FADE_NONE)
		{
			
			//���[�h�I��
			SetFade(MODE_TITLE);

		}
	}

	nCntHighScore++;
	nCntHighScore = nCntHighScore % 4;
	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++, pVtx += 4)
			{
				if (g_nRanking[nCntRanking] == g_NewScore)
				{
					if (nCntHighScore < 2)
					{
						g_Collar[nCntRanking] = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					}
					else if (nCntHighScore >= 2)
					{
						g_Collar[nCntRanking] = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f);
					}
					// ���_�J���[�̐ݒ�
					pVtx[0].col = g_Collar[nCntRanking];
					pVtx[1].col = g_Collar[nCntRanking];
					pVtx[2].col = g_Collar[nCntRanking];
					pVtx[3].col = g_Collar[nCntRanking];
				}
			}
		}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//+ �����L���O���S
		// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRanking[1]);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * (MAX_DIGIT * MAX_RANKING) + 4, 2);

	//+ �����L���O�i���o�[
		// �e�N�X�`���̐ݒ�

	for (int nCntRanking = 0; nCntRanking < (MAX_DIGIT * MAX_RANKING); nCntRanking++)
	{
		pDevice->SetTexture(0, g_pTextureRanking[0]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntRanking, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DIGIT * (MAX_RANKING + 2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//+ �����L���O�X�R�A�i���o�[
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		for (int nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++, pVtx += 4)
		{
			pVtx[0].pos = D3DXVECTOR3(-(SCORE_No_X / 2) - (SCORE_No_X * nCntDigit), -(SCORE_No_Y / 2) + ((30 + SCORE_No_Y) * nCntRanking), 0.0f) + RANKING_POS;
			pVtx[1].pos = D3DXVECTOR3((SCORE_No_X / 2) - (SCORE_No_X * nCntDigit), -(SCORE_No_Y / 2) + ((30 + SCORE_No_Y) * nCntRanking), 0.0f) + RANKING_POS;
			pVtx[2].pos = D3DXVECTOR3(-(SCORE_No_X / 2) - (SCORE_No_X * nCntDigit), (SCORE_No_Y / 2) + ((30 + SCORE_No_Y) * nCntRanking), 0.0f) + RANKING_POS;
			pVtx[3].pos = D3DXVECTOR3((SCORE_No_X / 2) - (SCORE_No_X * nCntDigit), (SCORE_No_Y / 2) + ((30 + SCORE_No_Y) * nCntRanking), 0.0f) + RANKING_POS;

			//1.0f�ŌŒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			if (nCntRanking == 0)
			{
				// ���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			}
			else if (nCntRanking == 1)
			{
				// ���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			}
			else if (nCntRanking == 2)
			{
				// ���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			}
			else
			{
				// ���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			}

			int nData = 1;

			for (int nCntData = nCntDigit; nCntData != 0; nCntData--)
			{
				nData *= 10;
			}

			pVtx[0].tex = D3DXVECTOR2((g_nRanking[nCntRanking] % (10 * nData) / nData)* 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_nRanking[nCntRanking] % (10 * nData) / nData)* 0.1f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_nRanking[nCntRanking] % (10 * nData) / nData)* 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_nRanking[nCntRanking] % (10 * nData) / nData)* 0.1f + 0.1f, 1.0f);
		}
	}

	pVtx += 4;

#if 1
	//+ �����L���O���S
		// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(350, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(950, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(350, 150, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(950, 150, 0.0f);
	// rhw�̐ݒ�
	for (int nCntrhw = 0; nCntrhw < 4; nCntrhw++)
	{
		pVtx[nCntrhw].rhw = 1.0f;
	}
	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

#endif
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);
}

//=============================================================================
// �X�R�A�̃Z�b�g
//=============================================================================
void SetRanking(int g_nScore)
{
	int nRank;
	int aEmptyData[6];
	aEmptyData[5] = g_nScore;

	for (int nCntNum = 0; nCntNum < MAX_RANKING; nCntNum++)
	{
		aEmptyData[nCntNum] = g_nRanking[nCntNum];
	}

	for (int nCntNum = 1; nCntNum < 6; nCntNum++)
	{
		for (int nCntNum1 = nCntNum; nCntNum1 > 0; nCntNum1--)
		{
			if (aEmptyData[nCntNum1 - 1] <= aEmptyData[nCntNum1])
			{
				nRank = aEmptyData[nCntNum1];
				aEmptyData[nCntNum1] = aEmptyData[nCntNum1 - 1];
				aEmptyData[nCntNum1 - 1] = nRank;
			}
		}
	}

	for (int nCntNum = 0; nCntNum < 5; nCntNum++)
	{
		g_nRanking[nCntNum] = aEmptyData[nCntNum];
	}
	g_NewScore = g_nScore;
}
