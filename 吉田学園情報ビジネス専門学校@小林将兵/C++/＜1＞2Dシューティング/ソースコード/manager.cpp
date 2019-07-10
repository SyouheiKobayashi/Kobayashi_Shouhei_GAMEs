//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �}�l�[�W���[���� [manager.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "sound.h"
#include "scene2D.h"
#include "fade.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"

//�ÓI�����o�ϐ�
CManager::MODE CManager::m_Mode = CManager::MODE_TITLE;//������ʂ̐ݒ�
CRenderer*CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputXPad *CManager::m_pInputXPad = NULL;
CSound *CManager::m_pSound = NULL;
CFade *CManager::m_pFade = NULL;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
int CManager::nRank[5] = {0,0,0,0,0};
int CManager::m_LastScore = 0;
//=============================================================================
//+ �}�l�[�W���[�̃R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
//+ �}�l�[�W���[�̃f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}
//=============================================================================
//+ �}�l�[�W���[�̏�����
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//! �����_�����O�N���X�̐���
	m_pRenderer = new CRenderer;

	//! �����_�����O����������
	if (m_pRenderer != NULL)
	{
		if (FAILED(m_pRenderer->Init(hWnd, TRUE))) //true(�k�����)	false(�t���X�N���[��)
		{
			return -1;
		}
	}

	//! �C���v�b�g�N���X(�L�[�{�[�h)�̐���
	m_pInputKeyboard = new CInputKeyboard;

	//! �C���v�b�g�N���X(�L�[�{�[�h)�̏���������
	if (m_pInputKeyboard != NULL)
	{
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	m_pInputXPad = new CInputXPad;
	if (m_pInputXPad != NULL)
	{
		m_pInputXPad->Init(hInstance,  hWnd);

	}
	//! �T�E���h�̐�����
	m_pSound = CSound::Create(hWnd);
	//! �t�F�[�h�̐�����
	m_pFade = CFade::Create();

	SetMode(m_Mode);//���ÓI�����o�ϐ��̏����ݒ肪����
	
	return S_OK;
}
//=============================================================================
//+ �}�l�[�W���[�̏I��
//=============================================================================
void CManager::Uninit(void)
{
	//!+ <���������t���Ŕj�����Ă�����>
	switch (m_Mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{//! �^�C�g���̏I������
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{//! �^�C�g���̏I������
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{//! �Q�[���̏I������
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{//! �Q�[���̏I������
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	}

	//! �T�E���h�̏I������
	m_pSound->Uninit();
	//! �t�F�[�h�̏I������
	m_pFade->Uninit();

	//! �C���v�b�g�N���X(�L�[�{�[�h)�̏I������
	if (m_pInputXPad != NULL)
	{
		m_pInputXPad->Uninit();
		delete m_pInputXPad;
		m_pInputXPad = NULL;
	}

	//! �C���v�b�g�N���X(�L�[�{�[�h)�̏I������
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//! �|���S���̏I������
	if (m_pRenderer != NULL)
	{
	CScene::ReleaseAll();
	}
	//! �����_�����O�I������
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}
//=============================================================================
//+ �}�l�[�W���[�̍X�V
//=============================================================================
void CManager::Update(void)
{
	switch (m_Mode)
	{
	case MODE_TITLE:
		//! �^�C�g���X�V����
		m_pTitle->Update();

		break;
	case MODE_TUTORIAL:
		//! �^�C�g���X�V����
		m_pTutorial->Update();

		break;
	case MODE_GAME:
		//! �Q�[���X�V����
		m_pGame->Update();
		
		break;

	case MODE_RESULT:
		//! �Q�[���X�V����
		m_pResult->Update();
		break;
	}

	//! �C���v�b�g(�L�[�{�[�h)�X�V����(Scene�̍X�V�����̏����܂܂�Ă���)
	m_pInputKeyboard->Update();

	m_pInputXPad->Update();

	//! �����_�����O�X�V����(Scene�̍X�V�����̏����܂܂�Ă���)
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	

	//! �t�F�[�h�X�V����
	m_pFade->Update();
}
//=============================================================================
//+ �}�l�[�W���[�̕`��
//=============================================================================
void CManager::Draw(void)
{
	switch (m_Mode)
	{
	case MODE_TITLE:
		//! �^�C�g���`�揈��
		m_pTitle->Draw();
		break;

	case MODE_TUTORIAL:
		//! �^�C�g���`�揈��
		m_pTutorial->Draw();
		break;

	case MODE_GAME:
		//! �Q�[���`�揈��
		m_pGame->Draw();
		break;

	case MODE_RESULT:
		//! �Q�[���`�揈��
		m_pResult->Draw();
		break;
	}

	//! �����_�����O�`�揈��(Scene�̍X�V�����̏����܂܂�Ă���)
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
//+ �Q�[�����[�h(��ʑJ��)�̐ݒ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	
	switch (m_Mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{//! �^�C�g���̏I������
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{//! �^�C�g���̏I������
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{//! �Q�[���̏I������
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;

	case MODE_RESULT:
		if (m_pResult != NULL)
		{//! �Q�[���̏I������
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	}
	
	switch (mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{//! �^�C�g���̐���
			m_pTitle = CTitle::Create();
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{//! �^�C�g���̐���
			m_pTutorial = CTutorial::Create();
		}
		break;
	case MODE_GAME:
		if (m_pGame == NULL)
		{//! �Q�[���̐���
			m_pGame = CGame::Create();
		}
		break;
	case MODE_RESULT:
		if (m_pResult == NULL)
		{//! �Q�[���̐���
			m_pResult = CResult::Create();
		}
		break;
	}
	m_Mode = mode;

}



