//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �X�R�A���� [score.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "score.h"
#include "number.h"
#include "result.h"
#include "manager.h"

//�}�N��
#define SCORE_SIZE_X	(18)
#define SCORE_SIZE_Y	(18)
#define SCORE_SPACE		(30)
#define SCORE_SIZE_posX	(SCREEN_WIDTH-510)
#define SCORE_SIZE_posY	(100)

//�ÓI�����o�ϐ�

//=============================================================================
//+ �X�R�A�̃R���X�g���N�^
//=============================================================================
CScore::CScore():CScene(OBJ_DRAW::DRAW_INFO)
{
	m_nScore = 0;
	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		m_nScoreNo[nCnt] = 0;
		
	}

}
//=============================================================================
//+ �X�R�A�̃f�X�g���N�^
//=============================================================================
CScore::~CScore()
{

}
//=============================================================================
//+ �X�R�A�̐�������
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos,SCORE_TYPE type)
{
	CScore *pScore = NULL;

	if (pScore == NULL)
	{
		switch (type)
		{
		case GAME_SCORE:
			pScore = new CGameScore;
			pScore->Init(pos);

			break;

		case RANKING_SCORE:
			pScore = new CRankingScore;
			pScore->Init(pos);

			break;
		}

	}

	return pScore;
}

void CScore::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ʏ�\���w�i(�T�C�Y�ω��A��]�Ȃ�,�e.cpp�ŃT�C�Y�̏���������)
	pVtx[0].pos = D3DXVECTOR3(-100, -100, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+100, -100, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-100, +100, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(+100, +100, 0.0f) + m_pos;


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CScore::SetScore(int nNowScore)
{
	m_nScore = nNowScore;
	
	
}

void CScore::AddScore(int nValue)
{
	m_nScore += nValue;

	float digit = 10;//������
	float newdigit01 = powf(digit, MAX-1);//������ς���
	float newdigit02 = powf(digit, MAX);//������ς���

	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		m_nScoreNo[nCnt] = (m_nScore % (int)newdigit02) / (int)newdigit01;
		newdigit01 = newdigit01 / 10;
		newdigit02 = newdigit02 / 10;
	}
}

void CScore::SaveScore(int nValue)
{
	m_nScore = nValue;

	float digit = 10;//������
	float newdigit01 = powf(digit, MAX - 1);//������ς���
	float newdigit02 = powf(digit, MAX);//������ς���

	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		m_nScoreNo[nCnt] = (m_nScore % (int)newdigit02) / (int)newdigit01;
		newdigit01 = newdigit01 / 10;
		newdigit02 = newdigit02 / 10;
	}
}

//!+ �Q�[���p
//=============================================================================
//+ �X�R�A�̃R���X�g���N�^
//=============================================================================
CGameScore::CGameScore()
{
	
	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

}
//=============================================================================
//+ �X�R�A�̃f�X�g���N�^
//=============================================================================
CGameScore::~CGameScore()
{

}

//=============================================================================
//+ �X�R�A�̏���������
//=============================================================================
HRESULT CGameScore::Init(void)
{
	return S_OK;
}
HRESULT CGameScore::Init(D3DXVECTOR3 pos)
{
	
	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apNumber[nCnt] = new CNumber;
		m_apNumber[nCnt]->Init();
		m_apNumber[nCnt]->SetSize(SCORE_SIZE_X, SCORE_SIZE_Y);
		m_apNumber[nCnt]->SetPos(pos, SCORE_SPACE, nCnt);
	}
	return S_OK;
}
//=============================================================================
//+ �X�R�A�̏I������
//=============================================================================
void CGameScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apNumber[nCnt]->Uninit();
		m_apNumber[nCnt] = NULL;
	}
	CManager::SetLastScore(m_nScore);//�}�l�[�W���ɍŏI�X�R�A�ۊ�
	//�������g��delete	<Scene>��delete�������g�p
	Release();
}
//=============================================================================
//+ �X�R�A�̍X�V����
//=============================================================================
void CGameScore::Update(void)
{
	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apNumber[nCnt]->Update();
		m_apNumber[nCnt]->SetNumber(m_nScoreNo[nCnt]);//�J�E���g���Ԋu��������
	}

	//CResult::SetLastScore(m_nScore);
}
//=============================================================================
//+ �X�R�A�̕`�揈��
//=============================================================================
void CGameScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apNumber[nCnt]->Draw();
	}
}

//!+ RANKING�p
//=============================================================================
//+ �X�R�A�̃R���X�g���N�^
//=============================================================================
CRankingScore::CRankingScore()
{
	for (int nRankNo = 0; nRankNo < 5; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX; nCnt++)
		{
			m_apNumber[nRankNo][nCnt] = NULL;
			m_nDigt[nRankNo][nCnt] = 0;
		}
	}
}
//=============================================================================
//+ �X�R�A�̃f�X�g���N�^
//=============================================================================
CRankingScore::~CRankingScore()
{

}

//=============================================================================
//+ �X�R�A�̏���������
//=============================================================================
HRESULT CRankingScore::Init(void)
{
	return S_OK;
}
HRESULT CRankingScore::Init(D3DXVECTOR3 pos)
{

	for (int nRankNo = 0; nRankNo < 5; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX; nCnt++)
		{
			//���Ăяo����number�������g��
			m_apNumber[nRankNo][nCnt] = new CNumber;
			m_apNumber[nRankNo][nCnt]->Init();
			m_apNumber[nRankNo][nCnt]->SetSize(35, 35);
			m_apNumber[nRankNo][nCnt]->SetPos(pos+D3DXVECTOR3(0.0f,(114.0f* nRankNo),0.0f), 55, nCnt);
		}
	}
	SetRankingSort(CManager::GetLastScore());

	return S_OK;
 }
//=============================================================================
//+ �X�R�A�̏I������
//=============================================================================
void CRankingScore::Uninit(void)
{
	for (int nRankNo = 0; nRankNo < 5; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX; nCnt++)
		{
			//���Ăяo����number�������g��
			m_apNumber[nRankNo][nCnt]->Uninit();
			m_apNumber[nRankNo][nCnt] = NULL;
		}
	}
	//�������g��delete	<Scene>��delete�������g�p
	Release();
}
//=============================================================================
//+ �X�R�A�̍X�V����
//=============================================================================
void CRankingScore::Update(void)
{
	for (int nRankNo = 0; nRankNo < 5; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX; nCnt++)
		{
			//���Ăяo����number�������g��
			m_apNumber[nRankNo][nCnt]->Update();
		
		}
	}

	//CResult::SetLastScore(m_nScore);
}
//=============================================================================
//+ �X�R�A�̕`�揈��
//=============================================================================
void CRankingScore::Draw(void)
{
	for (int nRankNo = 0; nRankNo < 5; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX; nCnt++)
		{
			//���Ăяo����number�������g��
			m_apNumber[nRankNo][nCnt]->Draw();
		}

	}
}

void CRankingScore::SetRankingSort(int nScore)
{
	int nRank = 0;
	int nSave = 0;
	nRank  = nScore;
	int nSave02 = 0;

	
	//�X�R�A�̃\�[�g����
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		if (nRank > CManager::nRank[nCnt])
		{
			nSave = CManager::nRank[nCnt];
			CManager::nRank[nCnt] = nRank;
			nRank = nSave;
			for (int nSortCnt = nCnt + 1; nSortCnt < 5; nSortCnt++)
			{
				nSave02 = CManager::nRank[nSortCnt];
				CManager::nRank[nSortCnt] = nRank;
				nRank = nSave02;
			}
			break;
		}
	}
	//���Ɋւ��鏈��
	float digit = 10;//������
	float newdigit01 = powf(digit, MAX - 1);//������ς���
	float newdigit02 = powf(digit, MAX);//������ς���

	for (int Rank = 0; Rank < 5; Rank++)
	{
		for (int nCnt = 0; nCnt < MAX; nCnt++)
		{
			m_nDigt[Rank][nCnt] = (CManager::nRank[Rank] % (int)newdigit02) / (int)newdigit01;
			
			m_apNumber[Rank][nCnt]->SetNumber(m_nDigt[Rank][nCnt]);
			newdigit01 = newdigit01 / 10;
			newdigit02 = newdigit02 / 10;
			if (nCnt == MAX - 1)
			{
				 newdigit01 = powf(digit, MAX - 1);//������ς���
				 newdigit02 = powf(digit, MAX);//������ς���
			}

		}
	}
	CManager::SetLastScore(0);//���������Ȃ���ΐ������Ȃ�Ranking�ɂȂ�
}