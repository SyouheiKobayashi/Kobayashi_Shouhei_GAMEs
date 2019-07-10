//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �^�C�g������ [title.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "title.h"
#include "manager.h"
#include "sound.h"
#include "scene2D.h"
#include "fade.h"
#include "bg.h"
#include "UI.h"
#include "number.h"
#include "score.h"
#include "gauge.h"
#include "life.h"
#include "bloodGauge.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "effect.h"
#include "explosion.h"


//�ÓI�����o�ϐ�
CTitle CTitle::*m_pGame = 0;
CBG *CTitle::m_pBG = NULL;
CUI *CTitle::m_pUI = NULL;


//=============================================================================
//+ �Q�[���̃R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{

}
//=============================================================================
//+ �Q�[���̃f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

CTitle *CTitle::Create(void)
{
	CTitle *pGame;
	pGame = new CTitle;
	pGame->Init();
	return pGame;
}
//=============================================================================
//+ �Q�[���̏���������
//=============================================================================
HRESULT CTitle::Init(void)
{
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_TITLE);
	//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
	//? �w�i�̃e�N�X�`������
	CBG::Load();
	//? UI�̃e�N�X�`������
	CUI::Load();
	
	//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
	//! �w�i�̐�����
	m_pBG = CBG::Create();
	//! UI�̐�����
	m_pUI = CUI::Create(0,620,305,550,300);

	//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

	return S_OK;
}
//=============================================================================
//+ �Q�[���̏I������
//=============================================================================
void CTitle::Uninit(void)
{
	//!+ <���������t���Ŕj�����Ă�����>
	//? UI�̃e�N�X�`���j��
	CUI::UnLoad();
	//? �w�i�̃e�N�X�`���j��
	CBG::UnLoad();

	//? �T�E���h�̒�~
	CSound *pSound = CManager::GetSound();
	pSound->StopSound();

	//! �S�Ẵf�[�^���,�I������
	CScene::ReleaseAll();
}
//=============================================================================
//+ �Q�[���̍X�V����
//=============================================================================
void CTitle::Update(void)
{
	//�L�[�{�[�h���g�p���邽�߂̏�����
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//�Q�[���p�b�h�Ă�
	CInputXPad *pInputXPad = CManager::GetInputXPad();

	//�Q�[���̑J��
	CFade::FADE pFade;
	pFade = CFade::GetFade();
	if (pFade == CFade::FADE_NONE)
	{
		if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			{
				CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
			}
		}
	}

}
//=============================================================================
//+ �Q�[���̕`�揈��
//=============================================================================
void CTitle::Draw(void)
{
	
}
