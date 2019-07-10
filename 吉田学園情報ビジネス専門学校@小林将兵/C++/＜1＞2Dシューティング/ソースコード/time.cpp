//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �X�R�A���� [time.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "time.h"
#include "number.h"
#include "fade.h"
#include "UI.h"
#include "game.h"
#include "continuity.h"

//�}�N��
#define SCORE_SIZE_X	(18)
#define SCORE_SIZE_Y	(18)
#define SCORE_SPACE		(30)
#define SCORE_SIZE_posX	(SCREEN_WIDTH-320)
#define SCORE_SIZE_posY	(650)

#define INITIAL_TIME (30)//�����J�n����
#define END_TIME (0)//�Q�[���I������
#define ENEMY_CREATE_TIME	(90)

//�ÓI�����o�ϐ�

//=============================================================================
//+ �X�R�A�̃R���X�g���N�^
//=============================================================================
CTime::CTime() :CScene(OBJ_DRAW::DRAW_INFO)
{
	m_nTimeNow = INITIAL_TIME *100;
	m_nEnemyCreateTime = 0;
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_nTimeDigit[nCnt] = 0;
		m_apNumber[nCnt] = NULL;
	}

}
//=============================================================================
//+ �X�R�A�̃f�X�g���N�^
//=============================================================================
CTime::~CTime()
{

}
//=============================================================================
//+ �X�R�A�̐�������
//=============================================================================
CTime *CTime::Create(void)
{
	CTime *pTime = NULL;

	if (pTime == NULL)
	{
		pTime = new CTime;
		pTime->Init();
	}

	return pTime;
}
//=============================================================================
//+ �X�R�A�̏���������
//=============================================================================
HRESULT CTime::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apNumber[nCnt] = new CNumber;
		m_apNumber[nCnt]->Init();
		m_apNumber[nCnt]->SetSize(SCORE_SIZE_X, SCORE_SIZE_Y);
		m_apNumber[nCnt]->SetPos(D3DXVECTOR3(SCORE_SIZE_posX, SCORE_SIZE_posY, 0.0f), SCORE_SPACE, nCnt);
	}

	m_nTimeNow = INITIAL_TIME *100;
	m_nUnintTime = 0;
	m_nCheck = false;
	m_bPlayerFlag = true;
	m_nEnemyCreateTime = 0;
	return S_OK;
}
//=============================================================================
//+ �X�R�A�̏I������
//=============================================================================
void CTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apNumber[nCnt]->Uninit();
		m_apNumber[nCnt] = NULL;
	}
	//�������g��delete	<Scene>��delete�������g�p
	Release();
}
//=============================================================================
//+ �X�R�A�̍X�V����
//=============================================================================
void CTime::Update(void)
{
	
	
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apNumber[nCnt]->Update();
		m_apNumber[nCnt]->SetNumber(m_nTimeDigit[nCnt]);//�J�E���g���Ԋu��������
	}

	m_nTimeNow--;
	m_nEnemyCreateTime++;
	CContinuity *pContinuity = CGame::GetContinuity();
	bool Flag = pContinuity->GetGiveUpFlag();
	if (Flag == true)
	{
	
		m_nUnintTime++;//�t�F�[�h�������s���܂ł̎���
		m_nCheck = true;//UI�̕���������j�~
		m_bPlayerFlag = false;//�v���C���[����s��

		if (m_nCheck == true && m_nUnintTime == 1)
		{
			CUI::Create(17, SCREEN_WIDTH / 2, 350, 115, 115);//�Q�[���I�[�o�[�A�C�R��
			m_nCheck = false;
		}

		if (m_nUnintTime > (3 * 100))//������̎��Ԍo�߂�...
		{

			//�Q�[���̑J��
			CFade::FADE pFade;
			pFade = CFade::GetFade();
			if (pFade == CFade::FADE_NONE)
			{
				CManager::GetFade()->SetFade(CManager::MODE_RESULT);
				
			}
		}
	}
		m_nTimeDigit[0] = m_nTimeNow % 100000 / 10000;
		m_nTimeDigit[1] = m_nTimeNow % 10000 / 1000;
		m_nTimeDigit[2] = m_nTimeNow % 1000 / 100;

}
//=============================================================================
//+ �X�R�A�̕`�揈��
//=============================================================================
void CTime::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apNumber[nCnt]->Draw();
	}
}

void CTime::SetPos(D3DXVECTOR3 pos)
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

void CTime::AddScore(int nValue)
{
	m_nTimeNow += nValue;
}

void CTime::SetLife(int nAddLife)
{
	m_nTimeNow = nAddLife;
}
