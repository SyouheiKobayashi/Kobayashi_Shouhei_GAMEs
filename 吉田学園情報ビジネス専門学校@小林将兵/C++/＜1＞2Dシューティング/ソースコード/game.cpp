//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �Q�[������ [game.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "game.h"
#include "sound.h"
#include "manager.h"
#include "scene2D.h"
#include "fade.h"
#include "pause.h"
#include "continuity.h"
#include "bg.h"
#include "UI.h"
#include "number.h"
#include "score.h"
#include "time.h"
#include "gauge.h"
#include "life.h"
#include "bloodGauge.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "action.h"
#include "effect.h"
#include "explosion.h"

//�ÓI�����o�ϐ�
CGame *CGame::m_pGame = 0;
CPause *CGame::m_pPause = 0;
CContinuity *CGame::m_pContinuity = 0;
CBG *CGame::m_pBG = NULL;
CUI *CGame::m_pUI = NULL;
CNumber *CGame::m_pNumber = NULL;
CScore *CGame::m_pScore = NULL;
CTime *CGame::m_pTime = NULL;
CGauge *CGame::m_pGauge = NULL;
CLife *CGame::m_pLife = NULL;
CBloodGauge *CGame::m_pBloodGauge = NULL;
CPlayer *CGame::m_pPlayer = NULL;
CEnemy *CGame::m_pEnemy = NULL;

//! =============================================================================
//! �R���X�g���N�^
//! =============================================================================
CGame::CGame()
{
	m_bBossFlag = false;
	m_nCheck = 0;
	
}

//! =============================================================================
//! �f�X�g���N�^
//! =============================================================================
CGame::~CGame()
{

}

//! =============================================================================
//! ����
//! =============================================================================
CGame *CGame::Create(void)
{
	CGame *pGame;
	pGame = new CGame;
	pGame->Init();
	return pGame;
}

//! =============================================================================
//!�@������
//! =============================================================================
HRESULT CGame::Init(void)
{
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_GAME);
	m_bPause = false;
	m_bContinuity = false;
	m_nCCC = 0;
	m_bBossFlag = false;
	m_nCheck = 0;
	
	//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
	//? �ꎞ��~�̃e�N�X�`������
	CPause::Load();
	CContinuity::Load();
	//? �w�i�̃e�N�X�`������
	CBG::Load();
	//? UI�̃e�N�X�`������
	CUI::Load();
	//? �����E�i���o�[(�X�R�A��^�C���Ɏg�p)�̃e�N�X�`������
	CNumber::Load();
	//? ���C�t�̃e�N�X�`������
	CLife::Load();
	//? ���t�̃e�N�X�`������
	CBloodGauge::Load();
	//? �v���C���[�̃e�N�X�`������
	CPlayer::Load();
	//? �G�E�G�l�~�[�̃e�N�X�`������
	CEnemy::Load();
	//? �e�̃e�N�X�`������
	CBullet::Load();
	//? �Z�̃e�N�X�`������
	CAction::Load();
	//? �G�t�F�N�g�̃e�N�X�`������
	CEffect::Load();
	//? �����G�t�F�N�g�̃e�N�X�`������
	CExplosion::Load();

	//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
	//! �ꎞ��~�̐�����
	m_pPause = CPause::Create(0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH/2, SCREEN_HEIGHT / 2);
	m_pPause = CPause::Create(1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_pPause = CPause::Create(2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH /6 , SCREEN_HEIGHT / 4);
	m_pPause = CPause::Create(3, SCREEN_WIDTH / 2, 240, 200, 50);
	m_pPause = CPause::Create(4, SCREEN_WIDTH / 2, 360, 200, 50);
	m_pPause = CPause::Create(5, SCREEN_WIDTH / 2, 490, 140, 50);

	m_pContinuity = CContinuity::Create(0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_pContinuity = CContinuity::Create(1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_pContinuity = CContinuity::Create(2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5);
	m_pContinuity = CContinuity::Create(3, SCREEN_WIDTH / 2, 280, 200, 50);
	m_pContinuity = CContinuity::Create(4, SCREEN_WIDTH / 2, 410, 200, 50);

	//! �w�i�̐�����
	m_pBG = CBG::Create();
	//! UI�̐�����
	m_pUI = CUI::Create(1, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2,400);
	m_pUI = CUI::Create(4,640, SCREEN_HEIGHT-60, 50, 50);
	m_pUI = CUI::Create(5, 750, SCREEN_HEIGHT - 60, 50, 50);
	m_pUI = CUI::Create(6, 860, SCREEN_HEIGHT - 60, 50, 50);
	m_pUI = CUI::Create(7, 640, SCREEN_HEIGHT - 60, 50, 50);
	m_pUI = CUI::Create(8, 750, SCREEN_HEIGHT - 60, 50, 50);
	m_pUI = CUI::Create(9, 860, SCREEN_HEIGHT - 60, 50, 50);
	//! ���C�t�Q�[�W�̐�����
	m_pLife = CLife::Create();
	//! ���t�Q�[�W�̐�����
	m_pBloodGauge = CBloodGauge::Create();
	//! UI�̐�����
	m_pUI = CUI::Create(12, 285, SCREEN_HEIGHT - 77, 240, 20);//���C�t�Q�[�W�t���[��
	m_pUI = CUI::Create(13, 285, SCREEN_HEIGHT - 25, 240, 20);//���t�Q�[�W�t���[��
	m_pUI = CUI::Create(2, 40, SCREEN_HEIGHT - 88, 35, 35);
	m_pUI = CUI::Create(3, 40, SCREEN_HEIGHT - 28, 30, 30);
	m_pUI = CUI::Create(11, SCREEN_WIDTH / 2, 95, 115, 115);//���ԕ\���A�C�R��
	m_pUI = CUI::Create(14, SCREEN_WIDTH / 2, 75, 90, 90);//���Ԙg�A�C�R��
	m_pUI = CUI::Create(15, SCREEN_WIDTH / 2, 95, 90, 90);//���Ԑj
	m_pUI = CUI::Create(16, SCREEN_WIDTH / 2, 95, 70, 70);//���Ԑj
	m_pUI = CUI::Create(18, 1100, 670, 50, 13);//���Ԑj
	m_pUI = CUI::Create(19, 1000, 620, 50, 13);//���Ԑj
	//! �X�R�A�̐�����
	m_pScore = CScore::Create(D3DXVECTOR3(1020,700,0), CScore::GAME_SCORE);
	//! �������Ԃ̐�����
	m_pTime = CTime::Create();
	//! �v���C���[�̐�����
	m_pPlayer = CPlayer::Create(0.0f, 0.0f, 15);
	//! �G�E�G�l�~�[�̐�����
	//m_pEnemy = CEnemy::Create(SCREEN_WIDTH+40, 300.0f, 3);//(�ʒuX,�ʒuY,Life)
	//m_pEnemy = CEnemy::Create(SCREEN_WIDTH, 200.0f, 3);
	//m_pEnemy = CEnemy::Create(SCREEN_WIDTH+30, 100.0f, 3);

	//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
	
	return S_OK;
}

//! =============================================================================
//! �I��
//! =============================================================================
void CGame::Uninit(void)
{
	//!+ <���������t���Ŕj�����Ă�����>
	//? �����G�t�F�N�g�̃e�N�X�`���̔j��
	CExplosion::UnLoad();
	//? �G�t�F�N�g�̃e�N�X�`������
	CEffect::UnLoad();
	//? �Z�̃e�N�X�`���̔j��
	CAction::UnLoad();
	//? �e�̃e�N�X�`���̔j��
	CBullet::UnLoad();
	//? �G�E�G�l�~�[�̃e�N�X�`���̔j��
	CEnemy::UnLoad();
	//? �v���C���[�̃e�N�X�`���̔j��
	CPlayer::UnLoad();
	//? ���t�̃e�N�X�`���̔j��
	CBloodGauge::UnLoad();
	//? ���C�t�̃e�N�X�`���̔j��
	CLife::UnLoad();
	//? �����E�i���o�[(�X�R�A��^�C���Ɏg�p)�̃e�N�X�`������
	CNumber::UnLoad();
	//? UI�̃e�N�X�`���j��
	CUI::UnLoad();
	//? �w�i�̃e�N�X�`���j��
	CBG::UnLoad();
	CContinuity::UnLoad();
	//? �ꎞ��~�̃e�N�X�`���j��
	CPause::UnLoad();
	CSound *pSound = CManager::GetSound();
	pSound->StopSound();
	//! �S�Ẵf�[�^���,�I������
	CScene::ReleaseAll();
}

//? =============================================================================
//? �X�V����
//? =============================================================================
void CGame::Update(void)
{
	//! =============================================================================
	//! ���͏����Ɋւ��鏈��
	//! =============================================================================
	//�L�[�{�[�h���g�p���邽�߂̏�����
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//�Q�[���p�b�h�Ă�
	CInputXPad *pInputXPad = CManager::GetInputXPad();
	//! =============================================================================

	CFade::FADE pFade;
	pFade = CFade::GetFade();
	CPlayer *pBloodLife = CGame::GetPlayer();
	int nBllodLife = pBloodLife->GetBloodLife();
	CTime *pTime = CGame::GetTime();
	int TimeNow = pTime->GetTimeNow();
	CScore*pScore = CGame::GetScore();
	int nNowScore = pScore->GetNowScore();
	bool bPlayerFlag = pTime->GetPlayerFlag();
	CContinuity *pContinuity = CGame::GetContinuity();
	bool bFlag = pContinuity->GetContinuityFlag();
	CPause *pPause = CGame::GetPause();
	int nUse = pPause->GetPauseMode();

	//! =============================================================================
	//! �|�[�Y�Ɋւ��鏈��
	//! =============================================================================

	if (pFade == CFade::FADE_NONE)
	{
		if (bPlayerFlag == true)
		{
			if (pInputKeyboard->GetTrigger(DIK_R) == true)
			{
				CManager::GetFade()->SetFade(CManager::MODE_RESULT);
			}

			if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_START, 0) == true || pInputKeyboard->GetTrigger(DIK_P) == true)
			{
				if (bFlag == false)
				{
					{
						m_bPause = m_bPause ? false : true;
					}
				}
			}
		}
	}

	
	if (nUse == CPause::MENU::PAUSE00)//�|�[�Y�̉���
	{
		if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			{
				m_bPause = false;
			}

		}
	}

	//! =============================================================================
	//! �R���e�B�j���[�Ɋւ��鏈��
	//! =============================================================================
	
	//��obj�����̊l��&&�g����悤�Ƀ��[�J���ɏ���^����
	int NumAll = CScene::GetNumAll();

	for (int nCntP = 0; nCntP < CScene::OBJ_DRAW::DRAW_ALL; nCntP++)//�p�ӂ��ꂽobj��for����
	{
		for (int nCnt = 0; nCnt < NumAll; nCnt++)//�p�ӂ��ꂽobj��for����
		{
			CScene *pScene;
			pScene = CScene::GetScene(nCntP, nCnt);

			if (pScene != NULL)
			{
				CScene::OBJ_TYPE ObjType;
				ObjType = pScene->GetObjType();//�^�C�v�̊m�F

				if (ObjType == CScene::OBJ_TYPE::OBJTYPE_PLAYER)//�v���C���[obj�Ȃ�
				{
					CScene2D *pPlayer = (CScene2D*)pScene;//CScene2D��GetPos���g����悤�ɃL���X�g(�ϊ�)����
					
					int nLife = pPlayer->GetLife();//�v���C���[�̗̑͂��擾

					
					if (nLife <= 0||TimeNow <= 0)//P�̗̑͂������͎��Ԃ�0�̏ꍇ...
					{
						m_bContinuity = true;
						
						int nUse = pContinuity->GetContinuityMode();
						if (nUse == CContinuity::MENU::CONTINUITY00)
						{
							if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
							{
								
								{
									m_bContinuity = false;


									if (nLife <= 0)//�̗͂�0�̏ꍇ��...
									{
										nLife = 10;
										CLife *pLife = CGame::GetLife();
										pLife->SetLife(nLife);
										pPlayer->SetLife(nLife);
									}


									TimeNow += (10 * 100);//���Ԃ̉��Z
									pTime->SetLife(TimeNow);

									pScore->SetScore(nNowScore / 2);//���X�R�A�𔼌�

									pPlayer->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//�v���C���[�\��

									m_nCCC = 1;//���ԉ�]�A�C�R���֌W
									break;
								}
								
							}
						}
					}
				}
			}
		}
	}

	//! =============================================================================
	//! �G���������Ɋւ��鏈��
	//! =============================================================================
	srand((unsigned)time(NULL));
	//CTime::GetEnemyCreateTime();
	if (m_bContinuity == false)
	{
			int ECT = pTime->GetEnemyCreateTime();
		if (m_nCheck == 0)
		{
			if (ECT < 12 * 100)//12�b��
			{
				if (ECT % (3 * 100) == 0)//3�b�Ԋu
				{
					CEnemy::Create(CEnemy::ENEMY01, SCREEN_WIDTH + (100 + rand() % 200), 110 + (rand() % 300), 3);
					CEnemy::Create(CEnemy::ENEMY01, SCREEN_WIDTH + (100 + rand() % 200), 660 - (rand() % 200), 3);
					CEnemy::Create(CEnemy::ENEMY02, SCREEN_WIDTH + (100 + rand() % 200), SCREEN_HEIGHT / 2 - 80, 5);
				}
			}
			if (ECT > 7 * 100)//7�b��
			{
				if (ECT % (5 * 100) == 0)//5�b�Ԋu
				{
					CEnemy::Create(CEnemy::ENEMY01, SCREEN_WIDTH + (100 + rand() % 200), 140 + (rand() % 380), 3);
					CEnemy::Create(CEnemy::ENEMY01, SCREEN_WIDTH + (100 + rand() % 200), 590 - (rand() % 210), 3);
					CEnemy::Create(CEnemy::ENEMY02, SCREEN_WIDTH + (100 + rand() % 200), SCREEN_HEIGHT / 2 + 95, 5);
				}
			}
			if (ECT > 10 * 100)//10�b��
			{
				if (ECT % (4 * 100) == 0)//5�b�Ԋu
				{
					CEnemy::Create(CEnemy::ENEMY03, SCREEN_WIDTH + (100 + rand() % 200), 60, 3);
				}
			}
			if (ECT > 18 * 100)//18�b��
			{
				if (ECT % (4 * 100) == 0)//5�b�Ԋu
				{
					CEnemy::Create(CEnemy::ENEMY04, 150 + (rand() % 530), SCREEN_HEIGHT + 50, 3);
				}
			}
			if (ECT > 25 * 100)//25�b��
			{
				if (ECT % (7 * 100) == 0)//5�b�Ԋu
				{
					CEnemy::Create(CEnemy::ENEMY05, SCREEN_WIDTH + (100 + rand() % 200), 100 + (rand() % 190), 3);
					CEnemy::Create(CEnemy::ENEMY05, SCREEN_WIDTH + (100 + rand() % 200), SCREEN_HEIGHT / 2 + 95, 5);
					CEnemy::Create(CEnemy::ENEMY05, SCREEN_WIDTH + (100 + rand() % 200), 560 - (rand() % 140), 3);
				}
			}
		}
		if (ECT > 35 * 100&& ECT < 36 * 100)//35�b��
		{
			m_bBossFlag = true;
			m_nCheck++;
			if (m_bBossFlag == true && m_nCheck == 1)
			{
				m_bBossFlag = false;
				m_pEnemy = CEnemy::Create(CEnemy::ENEMY_BOSS, SCREEN_WIDTH, SCREEN_HEIGHT / 2, 10);
			}
		}
	}
	
	CEnemy*pEnemy = CGame::GetEnemy();
	if (pEnemy != NULL)
	{
		int Life = pEnemy->GetLife();
		if (Life <= 0)
		{
			CFade::FADE pFade;
			pFade = CFade::GetFade();
			if (pFade == CFade::FADE_NONE)
			{
				{
					pEnemy = NULL;
					CManager::GetFade()->SetFade(CManager::MODE_RESULT);
				}
			}
		}
	}
}

//? =============================================================================
//? �Q�[���̕`�揈��
//? =============================================================================
void CGame::Draw(void)
{

}

//���ԕ\���A�C�R���Ɋւ��鏈��
void CGame::SetCCC(int nCCC)
{
	m_nCCC = nCCC;
}

