//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					�}�l�[�W���[���� [manager.cpp]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "manager.h"
#include "scene.h"
#include "fade.h"
#include "sound.h"
#include "title.h"
#include "timeCharge.h"
#include "game.h"
#include "result.h"
#include "ranking.h"

//=====================================================================
//							�ÓI�����o�ϐ�
//���I�u�W�F�N�g�ɑ����郁���o�ϐ��ł͂Ȃ��A�N���X�ɑ����郁���o�ϐ�
//���A�N�Z�X�������ݒ肳��Ă��邱�Ƃ������΁A�O���[�o���ϐ��Ɠ�������
//=====================================================================
CRenderer*CManager::m_pRenderer = NULL;
CFade *CManager::m_pFade = NULL;
CSound *CManager::m_pSound = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputXPad *CManager::m_pInputXPad = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CManager::STATE_MODE CManager::m_modeNow = CManager::MODE_TITLE;//�����ɊJ�n���郂�[�h
CTitle *CManager::m_pTitle = NULL;
CTimeCharge *CManager::m_pTimeCharge = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CRanking  *CManager::m_pRanking = NULL;
int CManager::m_nChargeTime = 0;
int CManager::m_nRank[5] = {0,0,0,0,0};
int CManager::m_nTotalScore = 0;
bool CManager::m_bResult = false;

//==============================================
//					�R���X�g���N�^
//���N���X�̃C���X�^���X�������Ɏ��s����郁�\�b�h�A�N���X�̃����o�ϐ���������
//==============================================
CManager::CManager()
{

}

//==============================================
//					�f�X�g���N�^
//���I�u�W�F�N�g����������ۂɌĂяo����Č㏈���Ȃǂ��s�Ȃ��֐�
//==============================================
CManager::~CManager()
{

}

//==============================================
//					������
//==============================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	m_nChargeTime = 0;
	
	m_pRenderer = new CRenderer;//�����_���[
	if (m_pRenderer != NULL)
	{
		if (FAILED(m_pRenderer->Init(hWnd, true))) //true(�k���X�N���[��) / false(�t���X�N���[��)
		{
			return -1;
		}
	}

	
	if (m_pFade == NULL)//�t�F�[�h
	{
		m_pFade = CFade::Create();//�t�F�[�h�̐���
	}

	
	if (m_pSound == NULL)//�T�E���h
	{
		m_pSound = CSound::Create(hWnd);
	}

	
	m_pInputKeyboard = new CInputKeyboard;//�L�[�{�[�h
	if (m_pInputKeyboard != NULL)
	{
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	m_pInputXPad = new CInputXPad;//�R���g���[���[
	if (m_pInputXPad != NULL)
	{
		m_pInputXPad->Init(hInstance,  hWnd);
		
	}

	m_pInputMouse = new CInputMouse;//�}�E�X
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Init(hInstance, hWnd);
	}

	//�������[�h
	SetStateMode(m_modeNow);//�ÓI�����o�ϐ��Őݒ肵���l������

	return S_OK;
}
//==============================================
//					�I��
//==============================================
void CManager::Uninit(void)
{
	switch (m_modeNow)//���݂̏��
	{
	case MODE_TITLE://�^�C�g���̏I��
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
	case MODE_CHARGETIME://�������ԏ����̏I��
		if (m_pTimeCharge != NULL)
		{
			m_pTimeCharge->Uninit();
			delete m_pTimeCharge;
			m_pTimeCharge = NULL;
		}
		break;
	case MODE_GAME://�Q�[���̏I��
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT://���U���g�̏I��
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	case MODE_RANKING://�����L���O�̏I��
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();
			delete m_pRanking;
			m_pRanking = NULL;
		}
		break;
	}

	//�}�E�X�̏I��
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	//�R���g���[���[�̏I��
	if (m_pInputXPad != NULL)
	{
		m_pInputXPad->Uninit();
		delete m_pInputXPad;
		m_pInputXPad = NULL;
	}

	//�L�[�{�[�h�̏I��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�T�E���h�̏I��
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//�t�F�[�h�̏I��
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}

	// �����_�����O�̏I��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//�쐬�E�g�p�����f�[�^�̑S�폜
	if (m_pRenderer != NULL)
	{
		CScene::ReleaseAll();
	}

	
}
//==============================================
//					�X�V
//==============================================
void CManager::Update(void)
{
	switch (m_modeNow)//���݂̏��
	{
	case MODE_TITLE://�^�C�g���̍X�V
		m_pTitle->Update();
		break;
	case MODE_CHARGETIME://�������ԏ����̍X�V
		m_pTimeCharge->Update();
		break;
	case MODE_GAME://�Q�[���̍X�V
		m_pGame->Update();
		break;
	case MODE_RESULT://���U���g�̍X�V
		m_pResult->Update();
		break;
	case MODE_RANKING://�����L���O�̍X�V
		m_pRanking->Update();
		break;

	}

	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();//�����_���[�̍X�V
	}

	m_pFade->Update();//�t�F�[�h�̍X�V

	m_pInputKeyboard->Update();//�L�[�{�[�h�̍X�V

	m_pInputXPad->Update();//�R���g���[���[�̍X�V

	m_pInputMouse->Update();//�}�E�X�̍X�V


}
//==============================================
//					�`��
//==============================================
void CManager::Draw(void)
{
	switch (m_modeNow)//���݂̏��
	{
	case MODE_TITLE://�^�C�g���̕`��
		m_pTitle->Draw();
		break;
	case MODE_CHARGETIME://�������ԏ����̕`��
		m_pTimeCharge->Draw();
		break;
	case MODE_GAME://�Q�[���̕`��
		m_pGame->Draw();
		break;
	case MODE_RESULT://���U���g�̕`��
		m_pResult->Draw();
		break;
	case MODE_RANKING://�����L���O�̕`��
		m_pRanking->Draw();
		break;
	}

	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();//�����_���[�̍X�V
	}

}

//==============================================
//			���[�h�̏��̎擾�E���f
//==============================================
void CManager::SetStateMode(STATE_MODE state_mode)
{
	switch (m_modeNow)//���݂̏��
	{
	case MODE_TITLE://�^�C�g���̏I��
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
	case MODE_CHARGETIME://�������ԏ����̏I��
		if (m_pTimeCharge != NULL)
		{
			m_nChargeTime = m_pTimeCharge->GetChargeTime();
			m_pTimeCharge->Uninit();
			delete m_pTimeCharge;
			m_pTimeCharge = NULL;
		}
		break;
	case MODE_GAME://�Q�[���̏I��
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT://���U���g�̏I��
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	case MODE_RANKING://�����L���O�̏I��
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();
			delete m_pRanking;
			m_pRanking = NULL;
			m_nTotalScore = 0;//�����ŃX�R�A���Z�b�g

		}
		break;
	}

	switch (state_mode)//m_modeNow(���݂̃��[�h�̏��)�����������state_mode(�V�������[�h�̏��)���������E����������
	{
	case MODE_TITLE://�^�C�g���̐���
		if (m_pTitle == NULL)
		{
			m_nChargeTime = 0;
			m_nTotalScore = 0;//�����ŃX�R�A���Z�b�g
			m_pTitle = CTitle::Create();
		}
		break;
	case MODE_CHARGETIME://�������ԏ����̐���
		if (m_pTimeCharge == NULL)
		{
			m_pTimeCharge = CTimeCharge::Create();
		}
		break;

	case MODE_GAME://�Q�[���̐���
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
		}
		break;
	case MODE_RESULT://���U���g�̐���
		if (m_pResult == NULL)
		{
			m_pResult = CResult::Create();
		}
		break;
	case MODE_RANKING://�����L���O�̐���
		if (m_pGame == NULL)
		{
			m_pRanking = CRanking::Create();
		}
		break;
	}
	m_modeNow = state_mode; //state_mode(�V�������[�h�̏��)������
}

//==============================================
//			���̃X�e�[�W�Ɉ����p�����߂�
//==============================================
void CManager::SetChargeTime(int nChargeTime)
{
	m_nChargeTime = nChargeTime;
}

//==============================================
//				���U���g����
//==============================================
void CManager::SetResult(bool bResultType)
{
	m_bResult = bResultType;
}

