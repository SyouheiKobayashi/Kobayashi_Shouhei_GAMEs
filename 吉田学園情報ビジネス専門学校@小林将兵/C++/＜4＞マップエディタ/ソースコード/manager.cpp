//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�}�l�[�W���[���� [manager.cpp]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "manager.h"
#include "scene.h"
#include "fade.h"
//#include "sound.h"
#include "game.h"

//=====================================================================
//�ÓI�����o�ϐ�
//���I�u�W�F�N�g�ɑ����郁���o�ϐ��ł͂Ȃ��A�N���X�ɑ����郁���o�ϐ�
//���A�N�Z�X�������ݒ肳��Ă��邱�Ƃ������΁A�O���[�o���ϐ��Ɠ�������
//=====================================================================
CRenderer*CManager::m_pRenderer = NULL;
CFade *CManager::m_pFade = NULL;
//CSound *CManager::m_pSound = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputXPad *CManager::m_pInputXPad = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;

CManager::STATE_MODE CManager::m_modeNow = CManager::MODE_GAME;//�����̃��[�h
CGame *CManager::m_pGame = NULL;

//==============================================
//�R���X�g���N�^
//���N���X�̃C���X�^���X�������Ɏ��s����郁�\�b�h�A�N���X�̃����o�ϐ���������
//==============================================
CManager::CManager()
{

}

//==============================================
//�f�X�g���N�^
//���I�u�W�F�N�g����������ۂɌĂяo����Č㏈���Ȃǂ��s�Ȃ��֐�
//==============================================
CManager::~CManager()
{

}

//==============================================
//������
//==============================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�����_���[
	m_pRenderer = new CRenderer;
	if (m_pRenderer != NULL)
	{
		if (FAILED(m_pRenderer->Init(hWnd, true))) //true(�k���X�N���[��) / false(�t���X�N���[��)
		{
			return -1;
		}
	}

	//�t�F�[�h
	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create();//�t�F�[�h�̐���
	}

	//�T�E���h
	/*if (m_pSound == NULL)
	{
		m_pSound = CSound::Create(hWnd);
	}*/

	//�L�[�{�[�h
	m_pInputKeyboard = new CInputKeyboard;
	if (m_pInputKeyboard != NULL)
	{
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	//�R���g���[���[
	m_pInputXPad = new CInputXPad;
	if (m_pInputXPad != NULL)
	{
		m_pInputXPad->Init(hInstance,  hWnd);
		
	}

	//�}�E�X
	m_pInputMouse = new CInputMouse;
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Init(hInstance, hWnd);
	}

	SetStateMode(m_modeNow);//�ÓI�����o�ϐ��Őݒ肵���f�[�^������

	return S_OK;
}
//==============================================
//�I��
//==============================================
void CManager::Uninit(void)
{
	switch (m_modeNow)//���݂̏��
	{
	case MODE_GAME://�Q�[���̏I��
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
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
	/*if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}*/

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
//�X�V
//==============================================
void CManager::Update(void)
{
	switch (m_modeNow)//���݂̏��
	{
	
	case MODE_GAME://�Q�[���̍X�V

		m_pGame->Update();

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
//�`��
//==============================================
void CManager::Draw(void)
{
	switch (m_modeNow)//���݂̏��
	{
	
	case MODE_GAME://�Q�[���̕`��
		m_pGame->Draw();
		break;
	}

	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();//�����_���[�̍X�V
	}

}

//==============================================
//���[�h�̏��̎擾�E���f
//==============================================
void CManager::SetStateMode(STATE_MODE state_mode)
{
	switch (m_modeNow)//���݂̏��
	{
	case MODE_GAME://�Q�[���ł���ΏI��
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
	}

	switch (state_mode)//m_modeNow(���݂̃��[�h�̏��)�����������state_mode(�V�������[�h�̏��)���������E����������
	{
	case MODE_GAME://�Q�[���̐���
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
		}
		break;
	}
	m_modeNow = state_mode; //state_mode(�V�������[�h�̏��)������
}



