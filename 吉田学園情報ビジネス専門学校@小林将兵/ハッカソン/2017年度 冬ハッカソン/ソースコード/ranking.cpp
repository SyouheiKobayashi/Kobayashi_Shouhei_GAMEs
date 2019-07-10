//=============================================================================
//
// �����L���O���� [Ranking.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "ranking.h"
#include "main.h"
#include "fade.h"
#include "sound.h"
#include "input.h"
#include "bgtitle.h"
#include "block.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RANKING		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RANKING_CHARACTER	"data/TEXTURE/ranking.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RANKING_PLAYER	"data/TEXTURE/p01.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RANKING_SHOOTER	"data/TEXTURE/z.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

#define MAX_TEXTURE_TYPE (4) //�e�N�X�`����
#define RANKING_DIGIT (8)	//����
#define MAX_RANKING (5)	//�����L���O��
#define MAX_OTHER (3)
#define CHANGE_RANKING (6)//����ւ��p
#define MAX_NUMER (40) // �����̑���


#define RANKING_X (60.0f) //�����̑傫��_X
#define RANKING_Y (80.0f)//�����̑傫��_Y
#define RANK_CHARACTER_X	(280)
#define RANK_CHARACTER_Y	(250)


#define RANK_PLAYER_X	(280)
#define RANK_PLAYER_Y	(570)

#define RANK_SHOOTER_X	(270)
#define RANK_SHOOTER_Y	(400)


#define RANKING_POS ((D3DXVECTOR3(SCREEN_WIDTH/2 + RANKING_X * 4, 100.0f, 0.0f))) //�����L���O�̈ʒu
#define RANKINGPOS_X ((-(RANKING_X / 2) - (RANKING_X * nCntDigit)))	//�����L���O�w�ʒu�̂��炵
#define RANKINGPOS_Y ((- (RANKING_Y / 2) + ((40 + RANKING_Y) * nCntRanking)))	//�����L���O�x�ʒu�̂��炵

#define RANKING_CHARACTER_POS ((D3DXVECTOR3(SCREEN_WIDTH / 2 - 500, 80.0f , 0.0f))) 
#define RANKING_PLAYER_POS ((D3DXVECTOR3(SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT /2 + 70 , 0.0f))) 
#define RANKING_SHOOTER_POS ((D3DXVECTOR3(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT /2 + 80 , 0.0f))) 

int g_nCntRanking; //�^�C�g���ւ̈ڍs���Ԃ̃J�E���g
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRanking[MAX_TEXTURE_TYPE] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
static int				g_nRanking[MAX_RANKING] = { 7000, 6000, 5000, 4000, 3000 };					// �X�R�A
D3DXCOLOR				g_nScoreCol[MAX_RANKING + 1];								// ���̃X�R�A�̐F
int g_nYourScore;

bool bYourScore;
int nCntHighScore;
int g_nCntFade; //�����t�F�[�h

//=============================================================================
// ����������
//=============================================================================
void InitRanking(void)
{
	//�w�i������
	InitBGTitle();


	g_nCntFade = 0;
	nCntHighScore = 0;
	for (int nCnt = 0; nCnt < MAX_RANKING + 1; nCnt++)
	{
		g_nScoreCol[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//bYourScore = false;


	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// �e�N�X�`���̓ǂݍ���(����)
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING, &g_pTextureRanking[0]);
	// �e�N�X�`���̓ǂݍ���(�����L���O���W)
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING_CHARACTER, &g_pTextureRanking[1]);
	// �e�N�X�`���̓ǂݍ���(�����L���O�v���C���[)
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING_PLAYER, &g_pTextureRanking[2]);
	// �e�N�X�`���̓ǂݍ���(�����L���O�X�̐_)
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING_SHOOTER, &g_pTextureRanking[3]);

	// ���_���̍쐬
	MakeVertexRanking(pDevice);


	//PlaySound(SOUND_LABEL_SE_PEOPLE2);

}

//=============================================================================
// �I������
//=============================================================================
void UninitRanking(void)
{
	UninitBGTitle();



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
	UpdateBGTitle();




	// ���_���̍쐬
	VERTEX_2D *pVtx;
	FADE pFade;
	pFade = *GetFade();

	// ���_���̍쐬
	//VERTEX_2D *pVtx;

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//���[�h�I��
			//SetMode(MODE_TITLE);
			SetFade(MODE_TITLE);
			bYourScore = false;
		}
	}
	g_nCntFade++;
	if (g_nCntFade % 620 == 0)
	{
		if (pFade == FADE_NONE)
		{
			g_nCntFade = 0;
			//���[�h�I��
			SetFade(MODE_TITLE);
			bYourScore = false;

		}
	}




	nCntHighScore++;
	nCntHighScore = nCntHighScore % 4;
	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);
	if (bYourScore == true)
	{

		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			for (int nCnt = 0; nCnt < 8; nCnt++, pVtx += 4)
			{
				if (g_nRanking[nCntRanking] == g_nYourScore)
				{
					if (nCntHighScore < 2)
					{
						g_nScoreCol[nCntRanking] = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					}
					else if (nCntHighScore >= 2)
					{
						g_nScoreCol[nCntRanking] = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f);
					}
					// ���_�J���[�̐ݒ�
					pVtx[0].col = g_nScoreCol[nCntRanking];
					pVtx[1].col = g_nScoreCol[nCntRanking];
					pVtx[2].col = g_nScoreCol[nCntRanking];
					pVtx[3].col = g_nScoreCol[nCntRanking];

				}
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
	DrawBGTitle();


	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);



	//=============================================================//
	//					�����L���O�X�̐_						   //
	//=============================================================//
	// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pTextureRanking[3]);
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * (8 * MAX_RANKING) + 12, 2);

	////=============================================================//
	////					�����L���O�v���C���[					   //
	////=============================================================//
	//// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pTextureRanking[2]);
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * (8 * MAX_RANKING) + 8, 2);



	//=============================================================//
	//					�����L���O����							   //
	//=============================================================//
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRanking[1]);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * (8 * MAX_RANKING) + 4, 2);



	//=============================================================//
	//					�����L���O����							   //
	//=============================================================//
	// �e�N�X�`���̐ݒ�

	for (int nCntRanking = 0; nCntRanking < (8 * MAX_RANKING); nCntRanking++)
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
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8 * (MAX_RANKING + 2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);



	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//=============================================================================//
	// �����L���O�̃X�R�A(����)													   //
	//=============================================================================//
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{

		for (int nCntDigit = 0; nCntDigit < 8; nCntDigit++, pVtx += 4)
		{

			pVtx[0].pos = D3DXVECTOR3(-(RANKING_X / 2) - (RANKING_X * nCntDigit), -(RANKING_Y / 2) + ((30 + RANKING_Y) * nCntRanking), 0.0f) + RANKING_POS;
			pVtx[1].pos = D3DXVECTOR3((RANKING_X / 2) - (RANKING_X * nCntDigit), -(RANKING_Y / 2) + ((30 + RANKING_Y) * nCntRanking), 0.0f) + RANKING_POS;
			pVtx[2].pos = D3DXVECTOR3(-(RANKING_X / 2) - (RANKING_X * nCntDigit), (RANKING_Y / 2) + ((30 + RANKING_Y) * nCntRanking), 0.0f) + RANKING_POS;
			pVtx[3].pos = D3DXVECTOR3((RANKING_X / 2) - (RANKING_X * nCntDigit), (RANKING_Y / 2) + ((30 + RANKING_Y) * nCntRanking), 0.0f) + RANKING_POS;

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
				pVtx[0].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			}
			else if (nCntRanking == 2)
			{
				// ���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.7f, 0.2f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.7f, 0.2f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.7f, 0.2f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.7f, 0.2f, 0.0f, 1.0f);
			}
			else
			{
				// ���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
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
	//=============================================================================//
	// ����̃����L���O�̕���											    	   //
	//=============================================================================//
	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(-RANK_CHARACTER_X / 2, -RANK_CHARACTER_Y / 2, 0.0f) + RANKING_CHARACTER_POS;
	pVtx[1].pos = D3DXVECTOR3(RANK_CHARACTER_X / 2, -RANK_CHARACTER_Y / 2, 0.0f) + RANKING_CHARACTER_POS;
	pVtx[2].pos = D3DXVECTOR3(-RANK_CHARACTER_X / 2, RANK_CHARACTER_Y / 2, 0.0f) + RANKING_CHARACTER_POS;
	pVtx[3].pos = D3DXVECTOR3(RANK_CHARACTER_X / 2, RANK_CHARACTER_Y / 2, 0.0f) + RANKING_CHARACTER_POS;
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


	//=============================================================================//
	// �v���C���[�����G													    	   //
	//=============================================================================//
	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(-RANK_PLAYER_X / 2, -RANK_PLAYER_Y / 2, 0.0f) + RANKING_PLAYER_POS;
	pVtx[1].pos = D3DXVECTOR3(RANK_PLAYER_X / 2, -RANK_PLAYER_Y / 2, 0.0f) + RANKING_PLAYER_POS;
	pVtx[2].pos = D3DXVECTOR3(-RANK_PLAYER_X / 2, RANK_PLAYER_Y / 2, 0.0f) + RANKING_PLAYER_POS;
	pVtx[3].pos = D3DXVECTOR3(RANK_PLAYER_X / 2, RANK_PLAYER_Y / 2, 0.0f) + RANKING_PLAYER_POS;
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


	//=============================================================================//
	// �X�̐_�����G														    	   //
	//=============================================================================//
	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(-RANK_SHOOTER_X / 2, -RANK_SHOOTER_Y / 2, 0.0f) + RANKING_SHOOTER_POS;
	pVtx[1].pos = D3DXVECTOR3(RANK_SHOOTER_X / 2, -RANK_SHOOTER_Y / 2, 0.0f) + RANKING_SHOOTER_POS;
	pVtx[2].pos = D3DXVECTOR3(-RANK_SHOOTER_X / 2, RANK_SHOOTER_Y / 2, 0.0f) + RANKING_SHOOTER_POS;
	pVtx[3].pos = D3DXVECTOR3(RANK_SHOOTER_X / 2, RANK_SHOOTER_Y / 2, 0.0f) + RANKING_SHOOTER_POS;
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
#endif
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);


}


//=============================================================================
// �X�R�A�̃Z�b�g
//=============================================================================
void SetRanking(int nScore)
{
	int nRank;
	int aEmptyData[6];
	aEmptyData[5] = nScore;

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
	bYourScore = true;

	g_nYourScore = nScore;

}
