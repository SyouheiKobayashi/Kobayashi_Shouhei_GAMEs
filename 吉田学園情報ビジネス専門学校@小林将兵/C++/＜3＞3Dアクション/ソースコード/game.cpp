//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//							�Q�[������ [game.h]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "game.h"
#include "fade.h"
#include "debugLog.h"
#include "sound.h"
#include "light.h"
#include "camera.h"
#include "scene2D.h"
#include "polygon2D.h"
#include "scene3D.h"
#include "polygon3D.h"
#include "bullet.h"
#include "particle.h"
#include "number.h"
#include "score.h"
#include "time.h"
#include "stencilShadow.h"
#include "object.h"
#include "player.h"
#include "enemy.h"

//=====================================================================
//							�ÓI�����o�ϐ�
//=====================================================================
CDebug *CGame::m_pDebug = NULL;
CSound *CGame::m_pSound = NULL;
CLight *CGame::m_pLight = NULL;
CCamera *CGame::m_pCamera = NULL;
CScene2D *CGame::m_pScene2D = NULL;
CPolygon2D *CGame::m_pPolygon2D[POLYGON2D_TEX_GAME] = {};
CScene3D *CGame::m_pScene3D[SCENE3D_CREATE] = {};
CPolygon3D *CGame::m_pPolygon3D[POLYGON3D_CREATE] = {};
CBullet *CGame::m_pBullet = NULL;
CParticle3D *CGame::m_pParticle3D = NULL;
CNumber *CGame::m_pNumber = NULL;
CScore *CGame::m_pScore = NULL;
CTime *CGame::m_pTime = NULL;
CStencilShadow *CGame::m_pStencilShadow = NULL;
CObject *CGame::m_pObject[OBJ_CREATE] = {};
CPlayer *CGame::m_pPlayer = NULL;
CEnemy *CGame::m_pEnemy[ENEMY_CREATE] = {};
int CGame::m_nStageCnt = STAGE_01;
int CGame::m_nSwitchFlagNum = 0;
bool CGame::m_bDivided = false;
bool CGame::m_bDivided02 = false;
bool CGame::m_bPageStop = false;
bool CGame::m_bDeath = false;
//==============================================
//					�R���X�g���N�^
//==============================================
CGame::CGame()
{

}

//==============================================
//					�f�X�g���N�^
//==============================================
CGame::~CGame()
{

}

//==============================================
//						����
//==============================================
CGame *CGame::Create()
{
	CGame *pGame = NULL;

	if (pGame == NULL)
	{
		pGame = new CGame;
		pGame->Init();
	}

	return pGame;
}
//==============================================
//					������
//==============================================
HRESULT CGame::Init(void)
{
	m_nDebugCnt = 0;
	m_bDeath = false;
	m_nFadeTime = 0;
	m_bPageStop = false;
	m_nPageCnt = 0;
	m_bDivided02 = false;
	m_bDivided = false;
	m_BulletTime = 0;;
	m_fBillCnt = 0.0f;
	m_nSwitchFlagNum = 0;
	bNextStage = false;

	//�ő�X�e�[�W�ȏ�܂��͂���ȊO�ł���ΐ��l��0��(�X�e�[�W01�ɂ��ǂ�)
	if (m_nStageCnt < STAGE_01 || STAGE_MAX <= m_nStageCnt)
	{
		m_nStageCnt = STAGE_01;
	}

	NullCheck();				//�g�p����f�[�^����xNULL�ɂ���
	BulkLoadData();				//�g�p�������f���ƃe�N�X�`���̉��
	MAP_LOAD();					//�}�b�v���̓ǂݍ���
	CreateData();				//�ǂݍ��񂾏������Ƃ�obj�̐���

	//�X�e�[�W�ɂ����BGM��ς���
	m_pSound = CManager::GetSound();
	if (m_pSound != NULL)
	{
		if (m_nStageCnt == STAGE_01)
		{
			m_pSound->PlaySound(CSound::BGM_SOUND_GAME01);
		}
		if (m_nStageCnt == STAGE_02)
		{
			m_pSound->PlaySound(CSound::BGM_SOUND_GAME02);
		}
		if (m_nStageCnt == STAGE_03)
		{
			m_pSound->PlaySound(CSound::BGM_SOUND_GAME03);
		}
	}
	return S_OK;
}
//==============================================
//						�I��
//==============================================
void CGame::Uninit(void)
{
	CManager::SetChargeTime(m_pTime->GetTime() / 100);

	if (m_pSound != NULL)
	{
		m_pSound->StopSound();
	}

	BulkUnLoadData();			//�g�p�������f���ƃe�N�X�`���̉��

	if (m_pTime != NULL)//�^�C��
	{
		m_pTime = NULL;			
	}
	if (m_pScore != NULL)//�X�R�A
	{
		m_pScore = NULL;		
	}

	if (m_pCamera != NULL)//�J����
	{
		m_pCamera->Uninit();	
	}
	if (m_pLight != NULL)//���C�g
	{
		m_pLight->Uninit();		
	}
	if (m_pDebug != NULL)//�f�o�b�N
	{
		m_pDebug->Uninit();		
	}

	//�g�p�����f�[�^�E�����������ׂĊJ��
	CScene::ReleaseAll();
}
//==============================================
//					�X�V
//==============================================
void CGame::Update(void)
{
	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	
	m_pFade = CFade::GetFade();	//�t�F�[�h

	if (m_pLight != NULL)//���C�g
	{
		m_pLight->Update();		
	}
	if (m_pCamera != NULL)//�J����
	{
		m_pCamera->Update();	
	}

	SwitchFlag();		//�X�C�b�`��S�ċN��������
	GameModeCheck();	//���̃X�e�[�W�ɐi�ނ��A����Ƃ����U���g��
	EventStage01();		//�X�e�[�W01�p�C�x���g
	EventStage02();		//�X�e�[�W02�p�C�x���g
	EventStage03();		//�X�e�[�W03�p�C�x���g

	if (m_pPolygon3D[1] != NULL)//�G�̃A�C�R���\��
	{
		if (m_pEnemy[0] != NULL)
		{
			m_pPolygon3D[1]->SetPos(D3DXVECTOR3(m_pEnemy[0]->GetPos().x / 2.0f, m_pEnemy[0]->GetPos().y + 40, m_pEnemy[0]->GetPos().z));
			if (m_pEnemy[0]->GetSearchCheck() == true && m_pEnemy[0]->GetMoveStop() == false)//����������ԂȂ�
			{
				m_pPolygon3D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (m_pEnemy[0]->GetSearchCheck() == false || m_pEnemy[0]->GetMoveStop() == true)//�������Ă��Ȃ���� / ���܂ꂽ���
			{
				m_pPolygon3D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
		}
	}

	
	
#ifdef _DEBUG
	Debug();					//�f�o�b�N����p
	//DebugLoop();
#endif
}

//==============================================
//					�`��
//==============================================
void CGame::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();//�J�����`��
	}

}

//==============================================
//				�X�C�b�`�����������̂�
//==============================================
void CGame::SetSwitchFlagNum()
{
	m_nSwitchFlagNum += 1;
}

//==============================================
//		�p�ӂ��ꂽ�X�C�b�`���S�ċN�����ꂽ��
//==============================================
void CGame::SwitchFlag()
{
	if (m_nSwitchFlagNum == CObject::GetSwitchNum())
	{
		if (m_pPolygon2D[1] != NULL)
		{
			m_pPolygon2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		bNextStage = true;//���̃X�e�[�W�֍s����
		if (m_pPolygon3D[0] == NULL)//3D�e�N�X�`��
		{
			if (m_pSound != NULL)
			{
				m_pSound->PlaySound(CSound::SE_GATE);//�Q�[�g���J���ꂽ��
			}
			//�Q�[�g
			if (m_nStageCnt == STAGE_01)
			{
				m_pPolygon3D[0] = CPolygon3D::Create(1, D3DXVECTOR3(180.0f, 50.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, 4, 4, true);
			}
			if (m_nStageCnt == STAGE_02)
			{
				m_pPolygon3D[0] = CPolygon3D::Create(1, D3DXVECTOR3(940.0f, 50.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, 4, 4, true);
			}
			if (m_nStageCnt == STAGE_03)
			{
				m_pPolygon3D[0] = CPolygon3D::Create(1, D3DXVECTOR3(395.0f, 50.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, 4, 4, true);
			}

		}
	}
}

//==============================================
//		���̃X�e�[�W�ɐi�ނ��A����Ƃ����U���g��
//==============================================
void CGame::GameModeCheck(void)
{
	if (m_pTime->GetTime() <= 0)//���C�t���������Ԃ�0�ɂȂ�����
	{
		m_bDeath = true;//���S���
		m_nFadeTime++;

		if (m_pPolygon3D[5] == NULL)//�����|���S��
		{
			m_pPolygon3D[5] = CPolygon3D::Create(10, D3DXVECTOR3(m_pPlayer->GetPos().x/2, m_pPlayer->GetPos().y/2+20.0f, -30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(120.0f, 120.0f, 0.0f), 6, 3, 2, false);
		}

		if (m_nFadeTime >= 80)
		{
			if (m_pFade == CFade::FADE_NONE)
			{
				m_nStageCnt = STAGE_01;
				CManager::SetResult(false);
				CManager::GetFade()->SetFade(CManager::MODE_RESULT);
			}
		}
	}

	if (bNextStage == true && m_pPlayer->GetPos().z >= 30)//���̃X�e�[�W�ɍs������ / �v���C���[��������̈ʒu�ɗ�����
	{
		if (m_pFade == CFade::FADE_NONE)
		{
			m_nStageCnt += 1;//�I��邽�тɉ��Z�A�ǂݍ��ރX�e�[�W��ς��Ă���

			if (m_nStageCnt <= STAGE_MAX - 1)
			{
				CManager::SetChargeTime(m_pTime->GetTime() / 100);//���̃X�e�[�W�֎��Ԃ����p��
				CManager::GetFade()->SetFade(CManager::MODE_GAME);
			}
			else//�Ō�̃X�e�[�W�Ȃ�
			{
				m_nStageCnt = STAGE_01;
				CManager::SetResult(true);
				CManager::GetFade()->SetFade(CManager::MODE_RESULT);

			}
		}
	}
}

//==============================================
//					01�C�x���g
//==============================================
void CGame::EventStage01()
{
	if (m_nStageCnt == STAGE_01)
	{
		//�`���[�g���A����ʂ̕\��
		if (m_pInputKeyboard->GetPress(DIK_SPACE) == true || m_pInputKeyboard->GetPress(DIK_RETURN) == true ||
			m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
		{
			m_nPageCnt += 1;
			if (m_nPageCnt == 1)
			{
				m_pPolygon2D[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_pPolygon2D[6]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			if (m_nPageCnt == 2)
			{
				m_pPolygon2D[6]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_bPageStop = true;
			}
		}
	}
	else
	{
		m_bPageStop = true;

	}

}

//==============================================
//					02�C�x���g
//==============================================
void CGame::EventStage02()
{
	// @   @   @   @   @   @   @   @   @   @   @   @
	//					�o���b�g�ނ̐���
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_nStageCnt == STAGE_02)
	{
		if (m_pEnemy[1] != NULL)
		{
			m_BulletTime++;
			if (m_BulletTime % 60 == 0 && m_pEnemy[1]->GetPos().z >= 0.0f)//�������� / �w��ꏊ�ȊO�ł͐������Ȃ�
			{
				CBullet::Create(80,D3DXVECTOR3(m_pEnemy[1]->GetPos().x / 2.0f, (m_pEnemy[1]->GetPos().y - m_pEnemy[1]->GetPos().y / 2.0f) + 15.0f, m_pEnemy[1]->GetPos().z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), 0, 5, 4, 3, true);
			}
			//����
			if (m_BulletTime % 80 == 0 && m_pPlayer->GetPos().z >= 200.0f)//�������� / �w��ꏊ�ȊO�ł͐������Ȃ�
			{
				CBullet::Create(120,D3DXVECTOR3(400.0f, (rand() % 20) + 30.0f, 120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 1, 1, 1, 1, true);
			}
		}
	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					���˂̉��̐���
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_nStageCnt == STAGE_02)
	{
		CParticle3D::Create(D3DXVECTOR3(940.0f, 320.0f, 100.0f),//�ʒu
			D3DXVECTOR3((rand() % 20 - 10)*0.08f, (rand() % 20 + 1)*0.1f, (rand() % 20 - 10)*0.08f),//�ړ���
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, 30, 0.5f, 2);//�J���[ ��] �������� �傫��
	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				Z���ړ��̕��|���S��
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_nStageCnt == STAGE_02)
	{
		if (m_pPolygon3D[4] != NULL)
		{
			D3DXVECTOR3 pos = m_pPolygon3D[4]->GetPos();
			pos.x = 45.0f;
			pos.y += 0.7f;
			pos.z += 1.0f;
			m_pPolygon3D[4]->SetPos(pos);
			if (m_pPolygon3D[4]->GetPos().z >= 100.0f)
			{
				D3DXCOLOR col = m_pPolygon3D[4]->GetCol();
				col.a -= 0.03f;
				m_pPolygon3D[4]->SetCol(col);
				if (m_pPolygon3D[4]->GetPos().z >= 200.0f)
				{
					m_pPolygon3D[4]->SetPos(D3DXVECTOR3(45.0f, 20.0f, -30.0f));
				}
			}
			else
			{
				m_pPolygon3D[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
			}
		}
	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					�����ꓹ
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_nStageCnt == STAGE_02)//�����ꓹ����
	{
		if (m_pPlayer->GetPos().x >= 80.0f && m_pPlayer->GetPos().x <= 150.0f)//���͈̔͂Ƀv���C���[����������
		{
			if (m_bDivided == false && m_pPlayer->GetPos().z <= 0)
			{//�A�C�R���̕\��
				m_pPolygon3D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (m_bDivided == true)
			{//�A�C�R���̔�\��
				m_pPolygon3D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
			if (m_pInputKeyboard->GetPress(DIK_W) == true ||
				m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 0) == true)
			{
				m_bDivided = true;//Z���̓���I�΂ꂽ

			}
			if (m_bDivided == true && m_pPlayer->GetPos().z >= 220.0f)//�ǂ��܂Ői�߂�̂�
			{
				m_bDivided = false;
			}
		}
		else//�A�C�R���̔�\��
		{
			m_pPolygon3D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}

		//�߂蓹
		if (m_pPlayer->GetPos().x >= 730 && m_pPlayer->GetPos().x <= 800)//���͈̔͂ɓ�������
		{
			if (m_bDivided02 == false && m_pPlayer->GetPos().z >= 200.0f)
			{//�A�C�R���̕\��
				m_pPolygon3D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			if (m_bDivided02 == true)
			{//�A�C�R���̔�\��
				m_pPolygon3D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
			if (m_pInputKeyboard->GetPress(DIK_S) == true ||
				m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true || m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true)
			{
				m_bDivided02 = true;//Z���̓���I�΂ꂽ
			}
			if (m_bDivided02 == true && m_pPlayer->GetPos().z <= 0.0f)//�ǂ��܂Ői�߂�̂�
			{
				m_bDivided02 = false;
			}
		}
		else
		{//�A�C�R���̔�\��
			m_pPolygon3D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
}

//==============================================
//					03�C�x���g
//==============================================
void CGame::EventStage03()
{
	// @   @   @   @   @   @   @   @   @   @   @   @
	//				�X�e�[�W�O�ɂł���
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_pPlayer != NULL)
	{
		if (m_pPlayer->GetOutStage() == true)
		{//����K���X��2D�|����\��
			m_pPolygon2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{//�\���㏙�X�ɔ���
			D3DXCOLOR col = m_pPolygon2D[0]->GetCol();
			col.a -= 0.05f;
			m_pPolygon2D[0]->SetCol(col);
		}
	}
}
//==============================================
//				NULL�`�F�b�N
//==============================================
void CGame::NullCheck(void)
{
	if (m_pDebug != NULL)
	{
		m_pDebug = NULL;		//�f�o�b�N
	}
	if (m_pLight != NULL)
	{
		m_pLight = NULL;		//���C�g
	}
	if (m_pCamera != NULL)
	{
		m_pCamera = NULL;		//�J����
	}

	if (m_pScene2D != NULL)
	{
		m_pScene2D = NULL;		//�V�[��2D
	}
	for (int nCnt = 0; nCnt < POLYGON2D_TEX_GAME; nCnt++)
	{
		if (m_pPolygon2D[nCnt] != NULL)
		{
			m_pPolygon2D[nCnt] = NULL;	//�|���S��2D
		}
	}
	for (int nCnt = 0; nCnt < SCENE3D_CREATE; nCnt++)
	{
		if (m_pScene3D[nCnt] != NULL)
		{
			m_pScene3D[nCnt] = NULL;		//�V�[��3D
		}
	}
	
	for (int nCnt = 0; nCnt < POLYGON3D_CREATE; nCnt++)
	{
		if (m_pPolygon3D[nCnt] != NULL)
		{
			m_pPolygon3D[nCnt] = NULL;	//�|���S��3D
		}
	}
	if (m_pBullet != NULL)
	{
		m_pBullet = NULL;
	}
	if (m_pStencilShadow != NULL)
	{
		m_pStencilShadow = NULL;	//�X�e���V���V���h�E
	}

	for (int nCnt = 0; nCnt < m_nMaxObjCreateNum; nCnt++)
	{
		if (m_pObject[nCnt] != NULL)
		{
			m_pObject[nCnt] = NULL;	//�I�u�W�F�N�g
		}
	}

	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;		//�v���C���[
	}
	for (int nCnt = 0; nCnt < ENEMY_CREATE; nCnt++)
	{
		if (m_pEnemy[nCnt] != NULL)
		{
			m_pEnemy[nCnt] = NULL;		//�G�l�~�[
		}
	}
}

//==============================================
//				�@Load����(�ǂݍ���)
//==============================================
void CGame::BulkLoadData(void)
{
	CPolygon2D::TextureLoad();
	CPolygon3D::TextureLoad();
	CBullet::TextureLoad();
	CParticle3D::TextureLoad();
	CNumber::TextureLoad();
	CStencilShadow::ObjectLoad();
	CObject::ObjectLoad();
	CObject::TextureLoad();
	CPlayer::ModelLoad();
	CPlayer::TextureLoad();
	CEnemy::ModelLoad();
	CEnemy::TextureLoad();

}

//==============================================
//				�@UnLoad����(���)
//==============================================
void CGame::BulkUnLoadData(void)
{
	CEnemy::TextureUnLoad();
	CEnemy::ModelUnLoad();
	CPlayer::TextureUnLoad();
	CPlayer::ModelUnLoad();
	CObject::TextureUnLoad();
	CObject::ObjectUnLoad();
	CStencilShadow::ObjectUnLoad();
	CNumber::TextureUnLoad();
	CParticle3D::TextureUnLoad();
	CBullet::TextureUnLoad();
	CPolygon3D::TextureUnLoad();
	CPolygon2D::TextureUnLoad();
}

//==============================================
//					��������
//==============================================
void CGame::CreateData(void)
{
	if (m_pDebug == NULL)//�f�o�b�N
	{
		m_pDebug = CDebug::Create();
	}
	if (m_pLight == NULL)//���C�g
	{
		m_pLight = CLight::Create();
	}
	if (m_pCamera == NULL)//�J����
	{
		m_pCamera = CCamera::Create();
	}

	if (m_pScene2D == NULL)//�V�[��2D
	{
		m_pScene2D = CScene2D::Create();
	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					2D�e�N�X�`��
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_pPolygon2D[0] == NULL)
	{
		m_pPolygon2D[7] = CPolygon2D::Create(16, false, D3DXVECTOR3(640.0f, 650.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 640.0f, 45.0f, 1, 1, 1, true);
		m_pPolygon2D[0] = CPolygon2D::Create(11, false, D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 640.0f, 360.0f, 1, 1, 1, true);
		m_pPolygon2D[1] = CPolygon2D::Create(17, false, D3DXVECTOR3(640.0f, 650.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 640.0f, 45.0f, 1, 1, 1, true);
		m_pPolygon2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		//����A�C�R��
		m_pPolygon2D[2] = CPolygon2D::Create(18, false, D3DXVECTOR3(1000.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150.0f, 70.0f, 6, 2, 1, true);
		m_pPolygon2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pPolygon2D[3] = CPolygon2D::Create(19, false, D3DXVECTOR3(1000.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150.0f, 70.0f, 6, 2, 1, true);
		m_pPolygon2D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pPolygon2D[4] = CPolygon2D::Create(20, false, D3DXVECTOR3(1000.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150.0f, 70.0f, 6, 2, 1, true);
		m_pPolygon2D[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		CPolygon2D::Create(21, false, D3DXVECTOR3(220.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200.0f, 80.0f, 1, 1, 1, true);

	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					�΂ߔ���
	// @   @   @   @   @   @   @   @   @   @   @   @

	if (m_nStageCnt == STAGE_02)
	{
		if (m_pScene3D[0] == NULL)
		{
			m_pScene3D[0] = CScene3D::Create(D3DXVECTOR3(350.0f, 14.0, 0.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f), 75.0f, -100.0f, 75.0f, -100.0f);

		}
		if (m_pScene3D[1] == NULL)
		{
			m_pScene3D[1] = CScene3D::Create(D3DXVECTOR3(570.0f, 125.0, 0.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f), 0.0f, 85.0f, 0.0f, 85.0f);
		}

		if (m_pScene3D[2] == NULL)
		{
			m_pScene3D[2] = CScene3D::Create(D3DXVECTOR3(765.0f, 35.0, 0.0f), D3DXVECTOR3(110.0f, 0.0f, 100.0f), 165.0f, -40.0f, 165.0f, -40.0f);
		}
	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					3D�|���S��
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_pPolygon3D[1] == NULL)
	{
		m_pPolygon3D[1] = CPolygon3D::Create(6, D3DXVECTOR3(70.0f, 40.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 1, 1, 1, true);
		m_pPolygon3D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pPolygon3D[2] = CPolygon3D::Create(7, D3DXVECTOR3(50.0f, 40.0f, 0.0f), D3DXVECTOR3(0.5f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 1, 1, 1, true);
		m_pPolygon3D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pPolygon3D[3] = CPolygon3D::Create(8, D3DXVECTOR3(380.0f, 80.0f, 100.0f), D3DXVECTOR3(0.5f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 1, 1, 1, true);
		m_pPolygon3D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		if (m_nStageCnt == STAGE_02)
		{
			m_pPolygon3D[4] = CPolygon3D::Create(9, D3DXVECTOR3(45.0f, 20.0f, -30.0f), D3DXVECTOR3(1.5f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 1, 1, 1, true);
			m_pPolygon3D[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
		}

	}

	//�w�i�p
	if (m_nStageCnt == STAGE_01)
	{
		CPolygon3D::Create(2, D3DXVECTOR3(50.0f, 50.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(2, D3DXVECTOR3(450.0f, 50.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(2, D3DXVECTOR3(-100.0f, 50.0f, 150.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(200.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(2, D3DXVECTOR3(620.0f, 50.0f, 620.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(200.0f, 300.0f, 0.0f), 1, 1, 1, true);
	}
	if (m_nStageCnt == STAGE_02)
	{
		CPolygon3D::Create(3, D3DXVECTOR3(50.0f, 140.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(3, D3DXVECTOR3(450.0f, 140.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(3, D3DXVECTOR3(850.0f, 140.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(3, D3DXVECTOR3(1250.0f, 140.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(3, D3DXVECTOR3(-100.0f, 140.0f, 150.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(3, D3DXVECTOR3(1160.0f, 140.0f, 1160.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
	}
	if (m_nStageCnt == STAGE_03)
	{
		CPolygon3D::Create(4, D3DXVECTOR3(50.0f, 140.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(4, D3DXVECTOR3(450.0f, 140.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(4, D3DXVECTOR3(850.0f, 140.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(4, D3DXVECTOR3(1250.0f, 140.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(4, D3DXVECTOR3(1650.0f, 140.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(4, D3DXVECTOR3(-100.0f, 140.0f, 150.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
	}

	if (m_pTime == NULL)//�^�C��
	{	//�}�l�[�W�������Ԃ��Ǘ����Ă���
		int nTime = CManager::GetChargeTime();
		if (nTime <= 0 && m_nStageCnt == STAGE_01)//���Ԃ̉��Z�s�ׂ�����Ȃ����...
		{
			nTime = DEFAULT_TIME;
		}
		m_pTime = CTime::Create(nTime, D3DXVECTOR2(40.0f, 40.0f), D3DXVECTOR2(147.0f, 92.0f));
	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				2D�e�N�X�`��(�D��`��)
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_pPolygon2D[5] == NULL)//2D�e�N�X�`��
	{
		if (m_nStageCnt == STAGE_01)
		{
			m_pPolygon2D[5] = CPolygon2D::Create(25, false, D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 600.0f, 300.0f, 6, 2, 1, true);
			m_pPolygon2D[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pPolygon2D[6] = CPolygon2D::Create(26, false, D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 600.0f, 300.0f, 6, 2, 1, true);
			m_pPolygon2D[6]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}

	//�X�e���V���V���h�E
	if (m_pStencilShadow == NULL)
	{
		m_pStencilShadow = CStencilShadow::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}


	//�O������ǂݍ��񂾃I�u�W�F�N�g�������Ƃɐ���
	for (int nCnt = 0; nCnt < m_nMaxObjCreateNum; nCnt++)
	{
		m_pObject[nCnt] = CObject::Create(m_nObjType[nCnt], m_nTexType[nCnt],
			D3DXVECTOR3(m_ObjOffseet[nCnt].fPosX, m_ObjOffseet[nCnt].fPosY, m_ObjOffseet[nCnt].fPosZ),
			D3DXVECTOR3(m_ObjOffseet[nCnt].fRotX, m_ObjOffseet[nCnt].fRotY, m_ObjOffseet[nCnt].fRotZ));
	}

	if (m_pPlayer == NULL)//�v���C���[
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(-100.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					�G�̔z�u
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_nStageCnt == STAGE_01)
	{
		if (m_pEnemy[0] == NULL)
		{
			m_pEnemy[0] = CEnemy::Create(0, D3DXVECTOR3(80.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}
	if (m_nStageCnt == STAGE_02)
	{
		if (m_pEnemy[0] == NULL)
		{
			//m_pEnemy[0] = CEnemy::Create(0, D3DXVECTOR3(80.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		if (m_pEnemy[1] == NULL)
		{
			m_pEnemy[1] = CEnemy::Create(1, D3DXVECTOR3(550.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/2, 0.0f));
		}
	}
	if (m_nStageCnt == STAGE_03)
	{
		if (m_pEnemy[0] == NULL)
		{
			m_pEnemy[0] = CEnemy::Create(0,D3DXVECTOR3(140.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}
}

//==============================================
//				�f�o�b�N�p����
//==============================================
void  CGame::Debug(void)
{
	CDebug::DebugLog("STAGE�i���o�[ %d", m_nStageCnt);
	CDebug::DebugLog("\nGimmick�t���O�� %d", m_nSwitchFlagNum);
	CDebug::DebugLog("\nGimmick�����t���O�� %d", CObject::GetSwitchNum());

}

void  CGame::DebugLoop(void)
{
	m_nDebugCnt++;
	if (m_nDebugCnt >= 50)
	{
		if (m_pFade == CFade::FADE_NONE)
		{
			m_nStageCnt += 1;//�I��邽�тɉ��Z�A�ǂݍ��ރX�e�[�W��ς��Ă���

			if (m_nStageCnt <= STAGE_MAX - 1)
			{
				CManager::SetChargeTime(m_pTime->GetTime() / 100);//�O��̃X�e�[�W�̎��Ԃ������p��
				CManager::GetFade()->SetFade(CManager::MODE_GAME);
			}
			else
			{
				m_nStageCnt = STAGE_01;
				CManager::GetFade()->SetFade(CManager::MODE_RESULT);

			}
		}
	}

}
//==============================================
//		�O���f�[�^����}�b�v���̓ǂݍ���
//==============================================
void CGame::MAP_LOAD(void)
{
	char * pStrCur;	//�擪������̃|�C���^
	char aLine[256];//������̓ǂݍ���
	char aStr[256];	//������̔����o��
	int nCnt = 0;
	int nWord;

	//�O���e�L�X�g�̓ǂݍ���
	if (m_nStageCnt == STAGE_01)
	{
		m_pFile = fopen("DATA\\TEXT\\STAGE01.txt", "r");
	}
	if (m_nStageCnt == STAGE_02)
	{
		m_pFile = fopen("DATA\\TEXT\\STAGE02.txt", "r");
	}
	if (m_nStageCnt == STAGE_03)
	{
		m_pFile = fopen("DATA\\TEXT\\STAGE03.txt", "r");
	}


	if (m_pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(m_pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "OBJ_CREATE_LOAD", strlen("OBJ_CREATE_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, m_pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					//�I�u�W�F�N�g�����ǂݍ��ނ�
					if (memcmp(pStrCur, "MAX_OBJ_CREATE = ", strlen("MAX_OBJ_CREATE = ")) == 0)
					{
						pStrCur += strlen("MAX_OBJ_CREATE = ");
						strcpy(aStr, pStrCur);
						m_nMaxObjCreateNum = atoi(aStr);
					}
					if (memcmp(pStrCur, "OBJ_SET", strlen("OBJ_SET")) == 0)
					{
						while (1)
						{
							fgets(&aLine[0], 256, m_pFile);
							pStrCur = CSceneX::GetLIneTop(&aLine[0]);

							//�g�p����I�u�W�F�N�g�ԍ�
							if (memcmp(pStrCur, "OBJ_TYPE = ", strlen("OBJ_TYPE = ")) == 0)
							{
								pStrCur += strlen("OBJ_TYPE = ");
								strcpy(aStr, pStrCur);
								m_nObjType[nCnt] = atoi(aStr);
							}
							//�I�u�W�F�N�g�ɒ���t����UV�ԍ�
							if (memcmp(pStrCur, "TEX_TYPE = ", strlen("TEX_TYPE = ")) == 0)
							{
								pStrCur += strlen("TEX_TYPE = ");

								strcpy(aStr, pStrCur);

								m_nTexType[nCnt] = atoi(aStr);
							}
							//�z�u����ʒu
							if (memcmp(pStrCur, "POS =", strlen("POS =")) == 0)
							{

								pStrCur += strlen("POS =");
								strcpy(aStr, pStrCur);

								for (int nCntWord = 0; nCntWord < 3; nCntWord++)
								{
									nWord = CSceneX::PopString(pStrCur, aStr);
									pStrCur += nWord;//�ǂݍ��ݕ����ʒu�����炷
									strcpy(aStr, pStrCur);

									if (nCntWord == 0)//x
									{
										m_ObjOffseet[nCnt].fPosX = (float)atof(aStr);

									}
									else if (nCntWord == 1)//y
									{
										m_ObjOffseet[nCnt].fPosY = (float)atof(aStr);
									}
									else//z
									{
										m_ObjOffseet[nCnt].fPosZ = (float)atof(aStr);
									}
								}
							}
							//����
							if (memcmp(pStrCur, "ROT =", strlen("ROT =")) == 0)
							{
								pStrCur += strlen("ROT =");
								strcpy(aStr, pStrCur);

								//x,y,z����
								for (int nCntWord = 0; nCntWord < 3; nCntWord++)
								{
									nWord = CSceneX::PopString(pStrCur, aStr);
									pStrCur += nWord;//�ǂݍ��ݕ����ʒu�����炷
									strcpy(aStr, pStrCur);

									if (nCntWord == 0)//x
									{
										m_ObjOffseet[nCnt].fRotX = (float)atof(aStr);

									}
									else if (nCntWord == 1)//y
									{
										m_ObjOffseet[nCnt].fRotY = (float)atof(aStr);
									}
									else//z
									{
										m_ObjOffseet[nCnt].fRotZ = (float)atof(aStr);
									}
								}
							}

							//�ǂݍ��ݏI��
							if (memcmp(pStrCur, "OBJ_SET_END", strlen("OBJ_SET_END")) == 0)
							{
								nCnt++;
								break;
							}
						}
					}
					//�ǂݍ��ݏI��
					if (memcmp(pStrCur, "OBJ_CREATE_LOAD_END", strlen("OBJ_CREATE_LOAD_END")) == 0)
					{
						break;
					}
				}
			}

			//�ǂݍ��ݏI��
			if (memcmp(pStrCur, "OBJ_CREATE_LOAD_END", strlen("OBJ_CREATE_LOAD_END")) == 0)
			{
				break;
			}
		}
	}
	fclose(m_pFile);
}




