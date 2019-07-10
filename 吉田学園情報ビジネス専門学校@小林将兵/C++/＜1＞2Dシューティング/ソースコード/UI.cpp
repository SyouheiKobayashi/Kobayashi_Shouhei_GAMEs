//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//UI���� [UI.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "game.h"
#include "UI.h"
#include"player.h"
#include "time.h"
#include "continuity.h"

//�}�N��
//�ǂݍ��ރe�N�X�`����
#define UI_01	("DATA\\TEX\\UI\\UI_title.png")//�^�C�g�����S
#define UI_02	("DATA\\GAME_UI00.png")//���g
#define UI_03	("DATA\\LIFE_ANIM03.png")//���C�t
#define UI_04	("DATA\\BLOOD_ANIM01.png")//���t�Q�[�W
#define UI_05	("DATA\\ActionIcon01.png")//�A�N�V����(��)
#define UI_06	("DATA\\ActionIcon02.png")//�A�N�V����(���ԑ���)
#define UI_07	("DATA\\GAME_UI01.png")//�A�N�V����(�K�E�Z)
#define UI_08	("DATA\\No_Use_Icon.png")//�g�p�s��
#define UI_09	("DATA\\No_Use_Icon.png")//�g�p�s��
#define UI_010	("DATA\\No_Use_Icon.png")//�g�p�s��
#define UI_011	("DATA\\TEX\\UI\\UI_ranking.png")//���U���g���S
#define UI_012	("DATA\\TEX\\UI\\UI_TimeIcon00.png")//���ԕ\�LUI(��]����)
#define UI_013	("DATA\\TEX\\UI\\UI_LifeFrame.png")//���C�t�Q�[�W�g
#define UI_014	("DATA\\TEX\\UI\\UI_BloodFrame.png")//���t�Q�[�W�g
#define UI_015	("DATA\\TEX\\UI\\UI_TimeFrame.png")//���v�g
#define UI_016	("DATA\\TEX\\UI\\UI_TimeParts.png")//���v�j
#define UI_017	("DATA\\TEX\\UI\\UI_TimeParts.png")//���v�j
#define UI_018	("DATA\\TEX\\pause\\pause_retry.png")//�Q�[���I�[�o�[
#define UI_019	("DATA\\TEX\\UI\\UI_Score.png")
#define UI_020	("DATA\\TEX\\UI\\UI_Time.png")
#define UI_021	("DATA\\TEX\\UI\\UI_tutorial.png")
//UI�̃T�C�Y��
#define E_SIZE_H	(30)
#define E_SIZE_W	(30)
//UI�̍U���Ԋu��
#define E_INTERVAL	(70)
//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CUI::m_pTexture[MAX_UI] = {};

//=============================================================================
//+UI�̃R���X�g���N�^
//=============================================================================
CUI::CUI() :CScene2D(OBJ_DRAW::DRAW_UI)
{
	m_nType = 0;
	m_CntAnim = 0;//�A�j���[�V�����̑���
	m_PatternAnim = 0;//�A�j���[�V�����̕�����
	m_bTimeCheck = false;
	m_fCnt = 0.0f;
}

//=============================================================================
//+UI�̃f�X�g���N�^
//=============================================================================
CUI::~CUI()
{

}

//=============================================================================
//+UI�̕K�v���ǂݍ���
//=============================================================================
HRESULT CUI::Load(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, UI_01, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, UI_02, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, UI_03, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, UI_04, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, UI_05, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, UI_06, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, UI_07, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, UI_08, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, UI_09, &m_pTexture[8]);
	D3DXCreateTextureFromFile(pDevice, UI_010, &m_pTexture[9]);
	D3DXCreateTextureFromFile(pDevice, UI_011, &m_pTexture[10]);
	D3DXCreateTextureFromFile(pDevice, UI_012, &m_pTexture[11]);
	D3DXCreateTextureFromFile(pDevice, UI_013, &m_pTexture[12]);
	D3DXCreateTextureFromFile(pDevice, UI_014, &m_pTexture[13]);
	D3DXCreateTextureFromFile(pDevice, UI_015, &m_pTexture[14]);
	D3DXCreateTextureFromFile(pDevice, UI_016, &m_pTexture[15]);
	D3DXCreateTextureFromFile(pDevice, UI_017, &m_pTexture[16]);
	D3DXCreateTextureFromFile(pDevice, UI_018, &m_pTexture[17]);
	D3DXCreateTextureFromFile(pDevice, UI_019, &m_pTexture[18]);
	D3DXCreateTextureFromFile(pDevice, UI_020, &m_pTexture[19]);
	D3DXCreateTextureFromFile(pDevice, UI_021, &m_pTexture[20]);


	return S_OK;
}
//=============================================================================
//+UI�𑼂̏����ɂ��폜�������Ȃ�
//=============================================================================
void CUI::UnLoad(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0;nCnt < MAX_UI;nCnt++)
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
CUI *CUI::Create(int nUI_NUM, int nPOS_X, int nPOS_Y, int nSIZE_X, int nSIZE_Y)
{
	CUI *pUI = NULL;
	if (pUI == NULL)
	{
		pUI = new CUI;
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
HRESULT CUI::Init(int nUI_NUM)
{
	CScene2D::Init();

	m_nType = nUI_NUM;
	m_CntAnim = 0;//�A�j���[�V�����̑���
	m_PatternAnim = 0;//�A�j���[�V�����̕�����
	m_bTimeCheck = false;
	m_fCnt = 0.0f;
	if (m_nType == 17)
	{
		CScene2D::SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}

	return S_OK;
}

//=============================================================================
//+UI�̏I������
//=============================================================================
void CUI::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//+UI�̍X�V����
//=============================================================================
void CUI::Update(void)
{
	CScene2D::Update();
	//�L�[�{�[�h���g�p���邽�߂̏�����
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//�Q�[���p�b�h�Ă�
	CInputXPad *pInputXPad = CManager::GetInputXPad();
	//UI�̈ʒu���̏������s�����߂̏�����
	D3DXVECTOR3 pos = CScene2D::GetPos();

	//UI�̈ړ����(�ύX�E�X�V)�̏�����
	CScene2D::SetPos(pos);
	bool Check = false;

	

	//CPlayer *pPlayer = CPlayer::GetMode();
	int NumAll = CScene::GetNumAll();

	for (int nCntP = 0; nCntP < OBJ_DRAW::DRAW_ALL; nCntP++)//�p�ӂ��ꂽobj��for����
	{
		for (int nCnt = 0; nCnt < NumAll; nCnt++)//�p�ӂ��ꂽobj��for����
		{
			CScene *pScene;
			pScene = CScene::GetScene(nCntP, nCnt);
			
			if (pScene != NULL)
			{

				CScene::OBJ_TYPE ObjType;
				ObjType = pScene->GetObjType();//�^�C�v�̊m�F

				if (ObjType == OBJ_TYPE::OBJTYPE_PLAYER)//�Gobj�Ȃ�
				{
					CScene2D *pScene2D = (CScene2D*)pScene;//Scene2D�ɃL���X�g
					CPlayer *pPlayer = (CPlayer*)pScene2D;//Bullet�ɃL���X�g
					int nActionMode = pPlayer->GetMode();//���ݑI�����Ă��郂�[�h�̏����擾
					D3DXVECTOR3 PlayerPos = pPlayer->GetPos();//�v���C���[�̈ʒu���
					//<�^�C�����Z>���I�΂ꂽ�ꍇ...
					CUI::SetActionUI(nActionMode, CPlayer::MODE::CURE, 4);
					//<���ȉ�>���I�΂ꂽ�ꍇ...
					CUI::SetActionUI(nActionMode, CPlayer::MODE::ADD_TIME, 5);
					//<�U���Z>���I�΂ꂽ�ꍇ...
					CUI::SetActionUI(nActionMode, CPlayer::MODE::SICKLE, 6);

					int nBloodLife = pPlayer->GetBloodLife();//���݂̌��t�����擾
					bool bUse01 = pPlayer->GetUse01();
					bool bUse02 = pPlayer->GetUse02();
					bool bUse03 = pPlayer->GetUse03();

					
					//! �Z�A�C�R��
					if (m_nType == 7)
					{
						if (bUse01 == true)
						{
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));//�\�����Ȃ�
						}
						else if (bUse01 == false)
						{
						
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//�\������

						}
					}
					if (m_nType == 8)
					{
						
						if (bUse02 == true)
						{
							
							
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));//�\�����Ȃ�
							
						}
						else if (bUse02 == false)
						{
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//�\������
							
						}
					}
					if (m_nType == 9)
					{
						if (bUse03 == true)
						{
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));//�\�����Ȃ�
						}
						else if (bUse03 == false)
						{
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//�\������
							
						}
					}
					
					CGame *pGame = CManager::GetGame();
					bool ContinuityFlag = pGame->GetContinuityFlag();
					int nCCC = pGame->GetCCC();

					//! ���ԕ\�L�A�C�R��
					if (m_nType == 11)
					{
						CScene2D::SetRot(-0.0011f);
					}
					if (m_nType == 11)
					{
						if (nActionMode == CPlayer::MODE::ADD_TIME &&bUse02 == true && pInputXPad->GetTrigger(XINPUT_GAMEPAD_Y, 0) == true)
						{
							{
								CManager::MODE mode;
								mode = CManager::GetMode();
								if (mode == CManager::MODE_GAME)
								{
									CTime *pTime = CGame::GetTime();
									int nTimeNow = pTime->GetTimeNow();
									if (nTimeNow > (1 * 100))
									{
										CScene2D::SetRot(1.11f);
									}
								}
							}
						}
						if (nCCC == 1)
						{
							nCCC = 0;
							CScene2D::SetRot(1.11f);
							pGame->SetCCC(nCCC);
						}
					}
					//! ���v�̐j
					if (m_nType == 15)
					{
						CScene2D::SetRot(-0.015f);
					}
					if (m_nType == 16)
					{
						CScene2D::SetRot(-0.05f);
					}
					//! �Q�[���I�[�o�[�\��
					if (m_nType == 17)
					{
						m_fCnt+=0.005f;
						CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fCnt));
						if (m_fCnt > 1.0f)
						{
							m_fCnt = 1.0f;
						}
					}

					//! �v���C���[�ʒu�����v�Əd�Ȃ�ʒu�ɂȂ�����s�����ɂ���
					if (PlayerPos.y <= 200)
					{
						if (m_nType == 11)
						{
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
						}
						if (m_nType == 14 || m_nType == 15 || m_nType == 16)
						{
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
						}
					}
					else
					{
						if (m_nType == 11 || m_nType == 14 || m_nType == 15 || m_nType == 16)
						{
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
						}
					}
				}
			}

		}
	}

	
	//! <�v���C���[�̃A�j���[�V��������>
		if (m_nType == 2||m_nType == 3)
		{
			m_CntAnim++; //�J�E���^�[�̉��Z �����̑��x
			if (m_CntAnim % 4 == 0)
			{
				m_PatternAnim = (m_PatternAnim + 1) % (5 * 3);//�p�^�[��No.�X�V
			}

			CScene2D::SetTexAnim(4, 5, 3, m_PatternAnim);
			
			if (m_PatternAnim >= (5 * 3) - 1)
			{
				m_PatternAnim = 0;
			}
		}
	
}

//=============================================================================
//+ UI�̕`�揈��
//=============================================================================
void CUI::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
//+ UI�̃A�C�R���\������
//=============================================================================

void CUI::SetActionUI(int nSelectActionNo, int nMode, int UI_TEX)
{
	
	if (nSelectActionNo == nMode)
	{
		if (m_nType == UI_TEX)
		{
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

	}
	else if (nSelectActionNo != nMode)
	{
		if (m_nType == UI_TEX)
		{
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
			
		}

	}
}
