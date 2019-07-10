//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�ꎞ��~���� [pause.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "pause.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "enemy.h"
#include "explosion.h"

//�}�N��
//�ǂݍ��ރe�N�X�`����
#define PAUSE_TEX01	("DATA\\TEX\\pause\\pause_BG.png")//�|�[�Y���̔w�i
#define PAUSE_TEX02	("DATA\\TEX\\pause\\pause_BG02.png")//�|�[�Y���̔w�i
#define PAUSE_TEX03	("DATA\\TEX\\pause\\pause_BG03.jpg")//�|�[�Y���̔w�i
#define PAUSE_TEX04	("DATA\\TEX\\pause\\pause_resumption.png")//�I��1
#define PAUSE_TEX05	("DATA\\TEX\\pause\\pause_retry.png")//�I��2
#define PAUSE_TEX06	("DATA\\TEX\\pause\\pause_Quit.png")//�I��3
//UI�̃T�C�Y��
#define E_SIZE_H	(30)
#define E_SIZE_W	(30)
//UI�̍U���Ԋu��
#define E_INTERVAL	(70)
//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CPause::m_pTexture[PAUSE_TEX] = {};
//=============================================================================
//+UI�̃R���X�g���N�^
//=============================================================================
CPause::CPause() :CScene2D(OBJ_DRAW::DRAW_PAUSE)
{
	m_nType = 0;

	m_nPauseMode = PAUSE00;

}

//=============================================================================
//+UI�̃f�X�g���N�^
//=============================================================================
CPause::~CPause()
{

}

//=============================================================================
//+UI�̕K�v���ǂݍ���
//=============================================================================
HRESULT CPause::Load(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEX01, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEX02, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEX03, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEX04, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEX05, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEX06, &m_pTexture[5]);

	return S_OK;
}
//=============================================================================
//+UI�𑼂̏����ɂ��폜�������Ȃ�
//=============================================================================
void CPause::UnLoad(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < PAUSE_TEX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
//+UI�̐�������
//=============================================================================
#if 1
CPause *CPause::Create(int nUI_NUM, int nPOS_X, int nPOS_Y, int nSIZE_X, int nSIZE_Y)
{
	CPause *pUI = NULL;
	if (pUI == NULL)
	{
		pUI = new CPause;
		pUI->Init(nUI_NUM);
		pUI->BindTexture(m_pTexture[nUI_NUM]);
		pUI->SetSize((float)nSIZE_X, (float)nSIZE_Y);//UI�̃T�C�Y
		pUI->SetPos(D3DXVECTOR3((float)nPOS_X, (float)nPOS_Y, 0.0f));//UI�����ʒu
	}
	return pUI;
}
#endif

//=============================================================================
//+UI�̏���������
//=============================================================================
HRESULT CPause::Init(int nUI_NUM)
{
	CScene2D::Init();

	m_nType = nUI_NUM;
	m_nPauseMode = PAUSE00;

	return S_OK;
}

//=============================================================================
//+UI�̏I������
//=============================================================================
void CPause::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//+UI�̍X�V����
//=============================================================================
void CPause::Update(void)
{
	CScene2D::Update();
	//�L�[�{�[�h���g�p���邽�߂̏�����
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//�Q�[���p�b�h�Ă�
	CInputXPad *pInputXPad = CManager::GetInputXPad();
	CGame *pGame = CManager::GetGame();

	//�|�[�Y�g�p�A�s�g�p���̏���
	m_PauseFlag = pGame->GetPauseFlag();
	if (m_PauseFlag == false)
	{
		
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));//�\�����Ȃ����
	}
	else
	{
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//�\�����Ă�����
			//�L�[�I������
			
			
			if (pInputXPad->GetTrigger(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || pInputKeyboard->GetTrigger(DIK_W) == true)
			//if (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
			{
				{
					m_nPauseMode -= 1;
					if (m_nPauseMode < PAUSE00)
					{
						m_nPauseMode = PAUSE02;
					}
					//apJoyState[0] = CInputXPad::INPUT_JOYSTATE_PUSH;
				}
			}

			if (pInputXPad->GetTrigger(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true || pInputKeyboard->GetTrigger(DIK_S) == true)
			//if (state.Gamepad.sThumbLY <= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
			{
				m_nPauseMode += 1;
				if (m_nPauseMode > PAUSE02)
				{
					m_nPauseMode = PAUSE00;
				}
			}
			//��Ԃ̔��f
			if (m_nType == m_nPauseMode)
			{
				CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			if (m_nType != m_nPauseMode)
			{
				CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
			//���[�h�̈ڍs
			if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				{
					if (m_nPauseMode == PAUSE00)
					{
						m_PauseFlag = false;

					}
					if (m_nPauseMode == PAUSE01)//�^�C�g����...
					{
						CFade::FADE pFade;
						pFade = CFade::GetFade();
						if (pFade == CFade::FADE_NONE)
						{
							CManager::GetFade()->SetFade(CManager::MODE_GAME);
						}
					}
					if (m_nPauseMode == PAUSE02)//�^�C�g����...
					{
						CFade::FADE pFade;
						pFade = CFade::GetFade();
						if (pFade == CFade::FADE_NONE)
						{
							CManager::GetFade()->SetFade(CManager::MODE_TITLE);
						}
					}
				}
			}
	}

	//UI�̈ʒu���̏������s�����߂̏�����
	D3DXVECTOR3 pos = CScene2D::GetPos();


	//UI�̈ړ����(�ύX�E�X�V)�̏�����
	CScene2D::SetPos(pos);
}

//=============================================================================
//+ UI�̕`�揈��
//=============================================================================
void CPause::Draw(void)
{
	CScene2D::Draw();
}

