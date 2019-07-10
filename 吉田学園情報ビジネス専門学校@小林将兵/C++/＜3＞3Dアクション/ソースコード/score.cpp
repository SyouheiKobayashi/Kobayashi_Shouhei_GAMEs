//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//						�����L���O���� [ranking.cpp]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "score.h"
#include "number.h"
#include "ranking.h"
#include "manager.h"
#include "game.h"
#include "time.h"
//==============================================
//					�R���X�g���N�^
//==============================================
CScore::CScore(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
	{
		m_nScoreNo[nCnt] = 0;
	}
}
//==============================================
//					�f�X�g���N�^
//==============================================
CScore::~CScore()
{

}
//==============================================
//					����
//==============================================
CScore *CScore::Create(D3DXVECTOR3 pos,SCORE_TYPE type)
{
	CScore *pScore = NULL;

	if (pScore == NULL)
	{
		switch (type)
		{
		case GAME_SCORE:
			pScore = new CGameScore;
			pScore->AddScore(0);//���[�h���ς���Ă���ɏ�����(�����p�������l)�X�R�A�̕\�����s��
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

//==============================================
//				�\���ʒu
//==============================================
void CScore::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-100, -100, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+100, -100, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-100, +100, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(+100, +100, 0.0f) + m_pos;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==============================================
//				�X�R�A�̉��Z
//==============================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
	m_nTotalScore = CManager::GetTotalScore();//�O�̃X�e�[�W�̃X�R�A�������p���\������
											 
	float digit = 10.0f;
	float newdigit01 = powf(digit, (float)MAX_SCOREDIGIT-1.0f);
	float newdigit02 = powf(digit, (float)MAX_SCOREDIGIT);

	for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
	{
		m_nScoreNo[nCnt] = ((m_nScore +m_nTotalScore) % (int)newdigit02) / (int)newdigit01;//[m_nTotalScore]�O�̃X�e�[�W�̃X�R�A��������
		newdigit01 = newdigit01 / 10;
		newdigit02 = newdigit02 / 10;
	}
}


// @   @   @   @   @   @   @   @   @   @   @   @
//!++			  �Q�[���X�R�A
// @   @   @   @   @   @   @   @   @   @   @   @
//==============================================
//					�R���X�g���N�^
//==============================================
CGameScore::CGameScore()
{
	
	for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

}
//==============================================
//					�f�X�g���N�^
//==============================================
CGameScore::~CGameScore()
{

}

//==============================================
//					������
//==============================================
HRESULT CGameScore::Init(void)
{
	return S_OK;
}
HRESULT CGameScore::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
	{
		m_apNumber[nCnt] = new CNumber;
		m_apNumber[nCnt]->Init();
		m_apNumber[nCnt]->SetSize(SCORE_SIZE_X, SCORE_SIZE_Y);
		m_apNumber[nCnt]->SetPos(pos, SCORE_SPACE, nCnt);
	}
	return S_OK;
}

//==============================================
//						�I��
//==============================================
void CGameScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = NULL;
		}
	}

	Release();
}

//==============================================
//					�X�V
//==============================================
void CGameScore::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
	{
		m_apNumber[nCnt]->Update();
		m_apNumber[nCnt]->SetNumber(m_nScoreNo[nCnt]);//�J�E���g�������𑝂₷(�����炵)
	}
}

//==============================================
//					�`��
//==============================================
void CGameScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}

// @   @   @   @   @   @   @   @   @   @   @   @
//!++		   �����L���O�X�R�A
// @   @   @   @   @   @   @   @   @   @   @   @
//==============================================
//					�R���X�g���N�^
//==============================================
CRankingScore::CRankingScore()
{
	for (int nRankNo = 0; nRankNo < MAX_RANK; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
		{
			m_apNumber[nRankNo][nCnt] = NULL;
			m_nDigt[nRankNo][nCnt] = 0;
		}
	}
	m_NewRecord = MAX_RANK;//�ő叇�ʕ�
}
//==============================================
//					�f�X�g���N�^
//==============================================
CRankingScore::~CRankingScore()
{

}

//==============================================
//					������
//==============================================
HRESULT CRankingScore::Init(void)
{
	return S_OK;
}
HRESULT CRankingScore::Init(D3DXVECTOR3 pos)
{

	for (int nRankNo = 0; nRankNo < MAX_RANK; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
		{
			m_apNumber[nRankNo][nCnt] = new CNumber;
			m_apNumber[nRankNo][nCnt]->Init();
			m_apNumber[nRankNo][nCnt]->SetSize(15.0f, 35.0f);
			m_apNumber[nRankNo][nCnt]->SetPos(pos + D3DXVECTOR3(0.0f,(110.0f* (float)nRankNo),0.0f), 75.0f, nCnt);
		}
	}

	int nScore = CManager::GetTotalScore();//����̃^�C�����擾����
	SetRankingSort(nScore);

	return S_OK;
 }
//==============================================
//						�I��
//==============================================
void CRankingScore::Uninit(void)
{
	for (int nRankNo = 0; nRankNo < MAX_RANK; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
		{
			m_apNumber[nRankNo][nCnt]->Uninit();
			m_apNumber[nRankNo][nCnt] = NULL;
		}
	}

	Release();
}
//==============================================
//					�X�V
//==============================================
void CRankingScore::Update(void)
{
	for (int nRankNo = 0; nRankNo < MAX_RANK; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
		{
			if(m_NewRecord < 5)
			{
				//m_apNumber[m_NewRecord][nCnt]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				m_apNumber[m_NewRecord][nCnt]->SetScale(100, 0.05f);
			}
			
		}
	}
}

//==============================================
//					�`��
//==============================================
void CRankingScore::Draw(void)
{
	for (int nRankNo = 0; nRankNo < MAX_RANK; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
		{
			m_apNumber[nRankNo][nCnt]->Draw();
		}
	}
}

//==============================================
//					�\�[�g(�����E�~����)
//==============================================
void CRankingScore::SetRankingSort(int nScore)
{
	int nRank = 0;
	int nSave = 0;
	nRank  = nScore;
	int nSave02 = 0;
	
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		if (nRank > CManager::m_nRank[nCnt])//�L�^�X�V������...
		{
			nSave = CManager::m_nRank[nCnt];
			CManager::m_nRank[nCnt] = nRank;
			nRank = nSave;
			m_NewRecord = nCnt;
			for (int nSortCnt = nCnt + 1; nSortCnt < MAX_RANK; nSortCnt++)
			{
				
				nSave02 = CManager::m_nRank[nSortCnt];
				CManager::m_nRank[nSortCnt] = nRank;
				nRank = nSave02;
			}
			break;
		}
	}
	
	//���Ɋւ��鏈��
	float digit = 10;//������
	float newdigit01 = powf(digit, (float)MAX_SCOREDIGIT - 1.0f);//������ς���
	float newdigit02 = powf(digit, (float)MAX_SCOREDIGIT);//������ς���

	for (int Rank = 0; Rank < MAX_RANK; Rank++)
	{
		for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
		{
			m_nDigt[Rank][nCnt] = (CManager::m_nRank[Rank] % (int)newdigit02) / (int)newdigit01;
			
			m_apNumber[Rank][nCnt]->SetNumber(m_nDigt[Rank][nCnt]);
			newdigit01 = newdigit01 / 10;
			newdigit02 = newdigit02 / 10;
			if (nCnt == MAX_SCOREDIGIT - 1)
			{
				 newdigit01 = powf(digit, MAX_SCOREDIGIT - 1);//������ς���
				 newdigit02 = powf(digit, MAX_SCOREDIGIT);//������ς���
			}
		}
	}

	//CManager::SetLastScore(0);//���̃X�R�A�̂��߂�0������
}