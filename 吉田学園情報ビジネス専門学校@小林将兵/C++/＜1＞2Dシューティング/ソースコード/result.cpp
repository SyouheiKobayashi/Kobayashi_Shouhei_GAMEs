//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �^�C�g������ [result.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "result.h"
#include "manager.h"
#include "sound.h"
#include "scene2D.h"
#include "fade.h"
#include "bg.h"
#include "UI.h"
#include "number.h"
#include "score.h"
#include "game.h"


//�ÓI�����o�ϐ�
CResult CResult::*m_pGame = 0;
CBG *CResult::m_pBG = NULL;
CUI *CResult::m_pUI = NULL;
CNumber *CResult::m_pNumber = NULL;
CScore *CResult::m_pScore = NULL;

//=============================================================================
//+ �Q�[���̃R���X�g���N�^
//=============================================================================
CResult::CResult()
{

}
//=============================================================================
//+ �Q�[���̃f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}

CResult *CResult::Create(void)
{
	CResult *pResult;
	pResult = new CResult;
	pResult->Init();
	return pResult;
}
//=============================================================================
//+ �Q�[���̏���������
//=============================================================================
HRESULT CResult::Init(void)
{
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_RANKING);
	
	//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
	//? �w�i�̃e�N�X�`������
	CBG::Load();
	//? UI�̃e�N�X�`������
	CUI::Load();
	//? ������tex����
	CNumber::Load();

	
	//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
	//! �w�i�̐�����
	m_pBG = CBG::Create();
	//! UI�̐�����
	m_pUI = CUI::Create(10,620,115,400,140);
	//! �X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(500, 200, 0),CScore::RANKING_SCORE);

	//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

	return S_OK;
}
//=============================================================================
//+ �Q�[���̏I������
//=============================================================================
void CResult::Uninit(void)
{
	//!+ <���������t���Ŕj�����Ă�����>
	//? ������tex�j��
	CNumber::UnLoad();
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
void CResult::Update(void)
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
			CManager::GetFade()->SetFade(CManager::MODE_TITLE);
			}
	}

}
//=============================================================================
//+ �Q�[���̕`�揈��
//=============================================================================
void CResult::Draw(void)
{

}

