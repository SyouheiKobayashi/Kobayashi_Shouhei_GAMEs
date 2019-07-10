//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�ꎞ��~���� [Continuity.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "continuity.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "enemy.h"
#include "explosion.h"

//�}�N��
//�ǂݍ��ރe�N�X�`����
#define CONTINUITY_TEX01	("DATA\\TEX\\pause\\pause_BG.png")//�|�[�Y���̔w�i
#define CONTINUITY_TEX02	("DATA\\TEX\\pause\\pause_BG02.png")//�|�[�Y���̔w�i
#define CONTINUITY_TEX03	("DATA\\TEX\\pause\\pause_BG03.jpg")//�|�[�Y���̔w�i
#define CONTINUITY_TEX04	("DATA\\TEX\\pause\\pause_Continue.png")//���g
#define CONTINUITY_TEX05	("DATA\\TEX\\pause\\pause_giveup.png")//���g
//UI�̃T�C�Y��
#define E_SIZE_H	(30)
#define E_SIZE_W	(30)
//UI�̍U���Ԋu��
#define E_INTERVAL	(70)
//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CContinuity::m_pTexture[CONTINUITY_TEX] = {};
//! =============================================================================
//! �R���X�g���N�^
//! =============================================================================
CContinuity::CContinuity() :CScene2D(OBJ_DRAW::DRAW_PAUSE)
{
	m_nType = 0;

	m_nContinuityMode = CONTINUITY00;
	m_GiveUpFlag = false;
}

//! =============================================================================
//! �f�X�g���N�^
//! =============================================================================
CContinuity::~CContinuity()
{

}

//! =============================================================================
//! Tex�ǂݍ���
//! =============================================================================
HRESULT CContinuity::Load(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, CONTINUITY_TEX01, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, CONTINUITY_TEX02, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, CONTINUITY_TEX03, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, CONTINUITY_TEX04, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, CONTINUITY_TEX05, &m_pTexture[4]);

	return S_OK;
}
//! =============================================================================
//! Tex�j��
//! =============================================================================
void CContinuity::UnLoad(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < CONTINUITY_TEX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//! =============================================================================
//! ����
//! =============================================================================
#if 1
CContinuity *CContinuity::Create(int nUI_NUM, int nPOS_X, int nPOS_Y, int nSIZE_X, int nSIZE_Y)
{
	CContinuity *pUI = NULL;
	if (pUI == NULL)
	{
		pUI = new CContinuity;
		pUI->Init(nUI_NUM);
		pUI->BindTexture(m_pTexture[nUI_NUM]);
		pUI->SetSize((float)nSIZE_X, (float)nSIZE_Y);//UI�̃T�C�Y
		pUI->SetPos(D3DXVECTOR3((float)nPOS_X, (float)nPOS_Y, 0.0f));//UI�����ʒu
	}
	return pUI;
}
#endif

//! =============================================================================
//! ������
//! =============================================================================
HRESULT CContinuity::Init(int nUI_NUM)
{
	CScene2D::Init();

	m_nType = nUI_NUM;
	m_nContinuityMode = CONTINUITY00;
	m_GiveUpFlag = false;
	return S_OK;
}

//! =============================================================================
//! �I��
//! =============================================================================
void CContinuity::Uninit(void)
{
	CScene2D::Uninit();
}

//! =============================================================================
//! �X�V
//! =============================================================================
void CContinuity::Update(void)
{
	CScene2D::Update();
	//�L�[�{�[�h���g�p���邽�߂̏�����
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//�Q�[���p�b�h�Ă�
	CInputXPad *pInputXPad = CManager::GetInputXPad();
	CGame *pGame = CManager::GetGame();

	int nUnintTime = 0;
	//nUnintTime++;

	//�|�[�Y�g�p�A�s�g�p���̏���
	m_ContinuityFlag = pGame->GetContinuityFlag();
	if (m_ContinuityFlag == false|| m_GiveUpFlag == true)
	{
		
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));//�\�����Ȃ����
		
	}
	else
	{
		
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//�\�����Ă�����
			//�L�[�I������
			//if (state.Gamepad.sThumbLY <= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
			if (pInputXPad->GetTrigger(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || pInputKeyboard->GetTrigger(DIK_W) == true)
			{
				m_nContinuityMode -= 1;
				if (m_nContinuityMode < CONTINUITY00)
				{
					m_nContinuityMode = CONTINUITY01;
				}
				
			}
			//if (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
			if (pInputXPad->GetTrigger(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true || pInputKeyboard->GetTrigger(DIK_S) == true)
			{
				
				m_nContinuityMode += 1;
				if (m_nContinuityMode > CONTINUITY01)
				{
					m_nContinuityMode = CONTINUITY00;
				}
			}
			//��Ԃ̔��f
			if (m_nType == m_nContinuityMode)
			{
				CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			if (m_nType != m_nContinuityMode)
			{
				CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}

			if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				{
					if (m_nContinuityMode == CONTINUITY01)
					{
						m_GiveUpFlag = true;
					}
				}
			}
		
	}

	//UI�̈ʒu���̏������s�����߂̏�����
	D3DXVECTOR3 pos = CScene2D::GetPos();


	//UI�̈ړ����(�ύX�E�X�V)�̏�����
	CScene2D::SetPos(pos);

}

//! =============================================================================
//! �`��
//! =============================================================================
void CContinuity::Draw(void)
{
	CScene2D::Draw();
}

