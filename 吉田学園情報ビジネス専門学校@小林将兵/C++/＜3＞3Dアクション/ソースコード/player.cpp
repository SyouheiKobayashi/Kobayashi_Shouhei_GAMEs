//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					�v���C���[���� [player.h]
//			Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "manager.h"
#include "debugLog.h"
#include "sound.h"
#include "camera.h"
#include "input.h"
#include "title.h"
#include "timeCharge.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "model.h"
#include "player.h"
#include "enemy.h"
#include "object.h"
#include "scene3D.h"
#include "polygon2D.h"
#include "polygon3D.h"


//==============================================
//				�ÓI�����o�ϐ�
//==============================================
CSound *CPlayer::m_pSound = NULL;
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = {};
LPD3DXMESH CPlayer::m_pMesh[PLAYER_PARTS] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat[PLAYER_PARTS] = {};
DWORD CPlayer::m_pNumMat[PLAYER_PARTS] = {};
int CPlayer::m_nNumParts = NULL;
int CPlayer::m_aIndexParent[PLAYER_PARTS] = {};
CPlayer::KEY CPlayer::m_aKeyOffseet[PLAYER_PARTS] = {};
int CPlayer::m_nNumModel = NULL;
char CPlayer::m_aFileNameModel[PLAYER_PARTS][256] = {};

//==============================================
//					�R���X�g���N�^
//==============================================
CPlayer::CPlayer(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	NULLCheck();//NULL�`�F�b�N

}
//==============================================
//					�f�X�g���N�^
//==============================================
CPlayer::~CPlayer()
{
}

//==============================================
//					����
//==============================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = NULL;
	CModel *pModel = NULL;

	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
		pPlayer->m_pos = pos;
		pPlayer->m_rot = rot;
		pPlayer->Init();

	}
	return pPlayer;
}
//==============================================
//					����������
//==============================================
HRESULT CPlayer::Init(void)
{
	NULLCheck();//NULL�`�F�b�N

	ModelLode();//�g�p���郂�f���̓ǂݍ���
	m_pSound = CManager::GetSound();

	return S_OK;
} 

//==============================================
//					�I������
//==============================================
void CPlayer::Uninit(void)
{
	if (m_pSound != NULL)
	{
		m_pSound->StopSound();
	}

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		if (m_pModel[nCnt] != NULL)
		{
			m_pModel[nCnt]->Uninit();
			delete m_pModel[nCnt];
			m_pModel[nCnt] = NULL;
		}
	}

	Release();
}

//==============================================
//					�X�V����
//==============================================
void CPlayer::Update(void)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)//�g�p���f�����X�V
	{
		m_pModel[nCnt]->Update();
	}
	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	m_pInputMouse = CManager::GetInputMouse();

	m_posOld = m_pos;//�ߋ��̈ʒu�����L��

	CurrentMode();//���݂̃��[�h�ɂ���ď���ς���
	Gravity();	//�d��
	MOVE();		//�ړ�
	JUMP();		//�W�����v
	Polygon3D();
	CollObj();		//�I�u�W�F�N�g�̓����蔻��
	CollEnemy();	//�I�u�W�F�N�g�̓����蔻��
	LadderEvent();	//��q�̃C�x���g

	if (m_pos.z <= -230.0f)//�X�e�[�W�O�ɏo����
	{
		m_bOutStage = true;
	}
	if (m_bOutStage == true)
	{
		m_nReTime++;
		if (m_nReTime >= 60)
		{
			SetPos(D3DXVECTOR3(1150.0f, 100.0f, 0.0f));
			m_bOutStage = false;
			m_nReTime = 0;
		}
	}

	if (m_pos.z >= 220.0f)
	{
		if (m_pInputKeyboard->GetPress(DIK_D) == false && m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == false &&
			m_pInputKeyboard->GetPress(DIK_A) == false && m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == false&&
			 m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_RIGHT, 0) == false && m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_LEFT, 0) == false)
		{
			motionType = WINDOW_WAIT;
		}
		m_pos.x += -1.0f;
	}

	TitleEvent();

	if (CManager::GetMode() == CManager::MODE_RANKING)//RANKING�݂̂̃��[�V����
	{
		motionType = RANKING;

	}

	UpdateMotion();//���[�V�����̍X�V(�����̏��Ԃɂ��ق��̏�����������!!)


#ifdef _DEBUG
	Debug();					//�f�o�b�N����p
#endif

}

//==============================================
//					�`�揈��
//==============================================
void CPlayer::Draw(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;


	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	if (CGame::GetDeath() == false)
	{
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			m_pModel[nCnt]->Draw();//�g�p���郂�f���̕`��
		}
	}
}

//==============================================
//			���݂̃��[�h�ɂ���ď���ς���
//==============================================
void CPlayer::CurrentMode(void)
{
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{
		m_pCamera = CTitle::GetCamera();//�J�������̎擾

	}
	if (CManager::GetMode() == CManager::MODE_CHARGETIME)
	{
		m_pCamera = CTimeCharge::GetCamera();//�J�������̎擾

	}
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		m_pCamera = CGame::GetCamera();//�J�������̎擾
	}
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{
		m_pCamera = CResult::GetCamera();//�J�������̎擾

	}
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{
		m_pCamera = CRanking::GetCamera();//�J�������̎擾
	}
}
//==============================================
//					�d��
//==============================================
void CPlayer::Gravity(void)
{
	if (m_bMeshcheck == false || m_bObjRide[m_nCurrentObj] == false || m_bEnemyRide[m_nCurrentEnemy] == false)//����Ă��Ȃ������ꍇ
	{
		if (m_pos.y <= 0)
		{
			m_pos.y = 0;
			m_move.y = 0;
		}
		else
		{
			m_move.y -= PLAYER_GRAVITY;//�d�͉��Z
		}
	}

}

//==============================================
//					�ړ�
//==============================================
void CPlayer::MOVE(void)
{
	CGame *pGame = CManager::GetGame();
	CPolygon3D *pPolygon3D = CGame::GetPolygon3D(0);//0�ɃQ�[�g��񂪂͂����Ă���
	float fRotation = m_pCamera->GetRotation();

	if (CGame::GetDeath() == false)
	{
		if (m_bLadderFlag == true)
		{

			if (m_pInputKeyboard->GetPress(DIK_W) == true ||
				m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 0) == true)
			{
				motionType = WALK;
				m_pos.x += sinf(fRotation) * 0.0f;
				m_pos.z += cosf(fRotation) * 0.0f;
				m_Sabun.y = D3DX_PI + fRotation - m_rot.y;
			}
		}

		//�C�x���g���N�����Ȃ�
		if (pGame != NULL&&pPolygon3D != NULL)
		{//�͈͓��ł��莟�̃X�e�[�W�ɍs������
			CDebug::DebugLog("\npPolygon3D->GetPos().x %.1f,", pPolygon3D->GetPos().x);
			if (pGame->GetNextStage() == true && (pPolygon3D->GetPos().x*2.0f) + 60 > m_pos.x && (pPolygon3D->GetPos().x*2.0f) - 60 < m_pos.x)
			{
				CPolygon2D *pPolygon2D = CGame::GetPolygon2D(3);//�u����v�A�C�R���̕\��
				if (pPolygon2D != NULL)
				{
					pPolygon2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				CDebug::DebugLog("\n�͈͓�");
				if (m_pInputKeyboard->GetPress(DIK_W) == true ||
					m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 0) == true)
				{
					m_bAutoMove = true;//������Z����
				}
			}
			else
			{
				CPolygon2D *pPolygon2D = CGame::GetPolygon2D(3);//�u����v�A�C�R���̔�\��
				if (pPolygon2D != NULL)
				{
					pPolygon2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				}
			}
		}
		//�����ꓹ
		if (m_bAutoMove == true || CGame::GetDivided() == true)//���̃X�e�[�W�ɍs���� / �����ꓹ��i�ނƂ�
		{
			motionType = WALK;
			m_pos.x += sinf(fRotation) * 1.2f;
			m_pos.z += cosf(fRotation) * 1.2f;
			m_Sabun.y = D3DX_PI + fRotation - m_rot.y;
		}
		if (CGame::GetDivided02() == true)//���̓��ɖ߂�Ƃ�
		{
			motionType = WALK;
			m_pos.x += sinf(D3DX_PI + fRotation) * PLAYER_SPEED;
			m_pos.z += cosf(D3DX_PI + fRotation) * PLAYER_SPEED;
			m_Sabun.y = fRotation - m_rot.y;
		}

		//�C�x���g�łȂ����
		if (m_bAutoMove == false && m_bLadderFlag == false && CGame::GetDivided() == false && CGame::GetDivided02() == false)
		{
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				if (CGame::GetPageStop() == true)
				{
					if (m_pInputKeyboard->GetPress(DIK_D) == true ||
						m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true || m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_RIGHT, 0) == true)
					{
						if (m_pos.z >= 220.0f)
						{
							motionType = WINDOW;
						}
						else
						{
							motionType = WALK;
						}
						m_pos.x += sinf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_pos.z += cosf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_Sabun.y = (-D3DX_PI / 2 + fRotation) - m_rot.y;
					}

					if (m_pInputKeyboard->GetPress(DIK_A) == true ||
						m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == true || m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_LEFT, 0) == true)
					{
						motionType = WALK;
						m_pos.x -= sinf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_pos.z -= cosf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_Sabun.y = ((D3DX_PI / 2) + fRotation) - m_rot.y;
					}
				}
			}
		}
	}
	if (m_Sabun.y > D3DX_PI)
	{
		m_Sabun.y -= D3DX_PI * 2;
	}
	else if (m_Sabun.y < -D3DX_PI)
	{
		m_Sabun.y += D3DX_PI * 2;
	}

	m_rot.y += m_Sabun.y * 0.25f;//�����]���̑���

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}

	m_Sabun.y = 0;

	m_bLoopCheck = false;//���[�V�������[�v�̉���

}

//==============================================
//					�W�����v
//==============================================
void CPlayer::JUMP(void)
{
	if (CGame::GetDeath() == false)
	{
		if (m_bObjRide[m_nCurrentObj] == true || m_bEnemyRide[m_nCurrentEnemy] == true || /*m_bBlockUpCheck == true|| */m_pos.y <= 0)//�n�ʂɐG��Ă�����W�����v�\
		{
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				if (CGame::GetPageStop() == true)
				{
					if (m_pInputKeyboard->GetTrigger(DIK_SPACE) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
					{
						if (m_pSound != NULL)
						{
							m_pSound->PlaySound(CSound::SE_JUMP);
						}
						m_move.y = PLAYER_JUMP;//�W�����v���Z
					}
					if (m_bAutoJump == true)//�G�̏�ɏ������
					{
						m_move.y = PLAYER_JUMP;//�W�����v���Z
						m_bAutoJump = false;
					}
				}
			}
		}
		else if (m_pScene3D != NULL)
		{
			if (m_bScene3DRide == false)
			{
				if (CManager::GetMode() == CManager::MODE_GAME)
				{
					if (m_bPolygon3DCheck[m_nCurrent3DPolygon] == true)
					{
						if (m_pInputKeyboard->GetTrigger(DIK_SPACE) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
						{
							m_bScene3DRide = true;
							if (m_pSound != NULL)
							{
								m_pSound->PlaySound(CSound::SE_JUMP);
							}
							m_move.y = PLAYER_JUMP;//�W�����v���Z
						}
					}


				}
			}
		}
	}
	m_pos.y += m_move.y;
}

//==============================================
//				3D�|���S���Ɋւ��鏈��
//==============================================
void CPlayer::Polygon3D(void)
{
	for (int nCnt = 0; nCnt < SCENE3D_CREATE; nCnt++)
	{
		m_pScene3D[nCnt] = CGame::GetScene3D(nCnt);
		if (m_pScene3D[nCnt] != NULL)
		{
			m_bPolygon3DCheck[nCnt] = m_pScene3D[nCnt]->GetCheck();
			if (m_bPolygon3DCheck[nCnt] == true)
			{
				m_nCurrent3DPolygon = nCnt;
				if (m_pos.y <= m_pScene3D[m_nCurrent3DPolygon]->GetDotPosY())
				{
					CDebug::DebugLog("\n����");
					m_bScene3DRide = false;
					m_pos.y = m_pScene3D[m_nCurrent3DPolygon]->GetDotPosY();//�ʒu�̔��f
					m_move.y = 0;
				}
			}
		}
	}
}

//==============================================
//				obj�Ƃ̓����蔻��
//==============================================
void CPlayer::CollObj(void)
{
	for (int nCnt = 0; nCnt < CObject::GetCreateNum(); nCnt++)
	{
		if (CManager::GetMode() == CManager::MODE_TITLE)
		{
			m_pObj = CTitle::GetObj(nCnt);
		}
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			m_pObj = CGame::GetObj(nCnt);
		}
		if (CManager::GetMode() == CManager::MODE_RANKING)
		{
			m_pObj = CRanking::GetObj(nCnt);
		}
		if (m_pObj != NULL)
		{
			//obj�̏�ɏ�����ꍇ
			if (m_pObj->Collision(&m_pos, &m_posOld, &m_move, GetDataType()) == true)
			{
				//m_move.y = 0;
				m_bObjRide[nCnt] = true;
				m_nCurrentObj = nCnt;
				m_move.y = 0;
			}
			else
			{
				m_bObjRide[nCnt] = false;
				if (CGame::GetStageCnt() == 2&&nCnt == 12)//��O�ŏ㉺�u���b�N�̂ݏ�ɏ���Ă����Ԃɂ��Ă���
				{
					m_bObjRide[nCnt] = true;
				}

			}

			//obj�̉��̏ꍇ
			if (m_pObj->CollSide(&m_pos, &m_posOld, &m_move, GetDataType()) == true)
			{
				m_bObjSide[nCnt] = true;
				m_nCurrentSideObj = nCnt;
			}
			else
			{
				m_bObjSide[nCnt] = false;
			}

			if (m_bDamageState[OBJ] == true)//�_���[�W���󂯂���
			{
				SetDamageAction(0.4f, 0.2f,OBJ);//�_���[�W���o����(�ǂꂭ�炢������Ԃ�)

			}

		}
	}
}

//==============================================
//				�G�l�~�[�Ƃ̓����蔻��
//==============================================
void CPlayer::CollEnemy(void)
{
	for (int nCnt = 0; nCnt < CEnemy::GetCreateNum(); nCnt++)
	{
		if (CManager::GetMode() == CManager::MODE_TITLE)
		{
			//m_pEnemy = CTitle::GetEnemy(nCnt);
		}
		if (CManager::GetMode() == CManager::MODE_CHARGETIME)
		{
			//m_pEnemy = CTimeCharge::GetEnemy(nCnt);
		}
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			m_pEnemy = CGame::GetEnemy(nCnt);
		}
		if (CManager::GetMode() == CManager::MODE_RESULT)
		{
			//m_pEnemy = CResult::GetEnemy(nCnt);

		}
		if (CManager::GetMode() == CManager::MODE_RANKING)
		{
			//m_pEnemy = CRanking::GetEnemy(nCnt);
		}
		if (m_pEnemy != NULL)
		{
			if (m_bDamageState[ENEMY] == false)//�_���[�W���󂯂ĂȂ����
			{
				//�G�l�~�[�̏�ɏ�����ꍇ
				if (m_pEnemy->Collision(&m_pos, &m_posOld, &m_move) == true)
				{
					m_bEnemyRide[nCnt] = true;
					m_nCurrentEnemy = nCnt;
					m_bAutoJump = true;
				}
				else
				{
					m_bEnemyRide[nCnt] = false;

				}
			}
			else if (m_bDamageState[ENEMY] == true)//�_���[�W���󂯂���
			{
				SetDamageAction(3.0f,3.0f,ENEMY);//�_���[�W���o����(�ǂꂭ�炢������Ԃ�)
			}
		}
	}
}

//==============================================
//				��q�̃C�x���g
//==============================================
void CPlayer::LadderEvent(void)
{
	if (m_pObj != NULL)
	{
		m_bLadderFlag = m_pObj->GetLadderFlag();
		if (m_bLadderFlag == true)
		{
			motionType = EVENT;
			m_move.y += PLAYER_GRAVITY + 0.05f;
			if (m_pos.y >= 120.0f)
			{
				m_bLoopCheck = false;//���[�V�������[�v�̉���
				m_pos.x += 5.0f;
				if (m_pos.x >= 950.0f)
				{
					m_rot.y = -D3DX_PI / 2;
					m_pObj->SetLadderFlag(false);
				}
			}
		}
	}
}

//==============================================
//				�_���[�W���󂯂��ۂ̉��o����
//==============================================
void CPlayer::SetDamageAction(float fX, float fY, int nType)
{
	m_nStateCnt++;

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_pModel[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	}

	if (m_bObjSide[m_nCurrentSideObj] == false&& nType == ENEMY)//�ǂɐG��Ă��Ȃ��Ȃ�&&�^�C�v�͓G
	{
		if (m_nKnockBack == LEFT)
		{
			m_pos.x -= fX;
			m_pos.y += fY;
		}
		else if (m_nKnockBack == RIGHT)
		{

			m_pos.x += fX;
			m_pos.y += fY;
		}
	}
	else if(nType == OBJ)//�^�C�v�̓M�~�b�Nobj
	{
		if (m_nKnockBack == FRONT)//��O����
		{

			m_pos.z -= 1.2f;
			m_pos.y += 0.5f;
		}
		if (m_nKnockBack == LEFT)
		{
			m_pos.x -= fX;
			m_pos.y += fY;
		}
		else if (m_nKnockBack == RIGHT)
		{

			m_pos.x += fX;
			m_pos.y += fY;
		}
	}

	//�_���[�W�\�L����
	if (nType == OBJ)
	{
		if (m_nKnockBack == FRONT)
		{
			if (m_nStateCnt >= 200)
			{
				for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
				{
					m_pModel[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				m_nStateCnt = 0;
				m_bDamageState[OBJ] = false;
			}
		}
		else
		{
			if (m_nStateCnt >= 150)
			{
				for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
				{
					m_pModel[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				m_nStateCnt = 0;
				m_bDamageState[OBJ] = false;
			}
		}
	}
	if(nType == ENEMY)
	{
		if (m_nStateCnt >= 13)
		{
			for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
			{
				m_pModel[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			m_nStateCnt = 0;
			m_bDamageState[ENEMY] = false;
		}
	}
}

//==============================================
//				�^�C�g�����̉��o
//==============================================
void CPlayer::TitleEvent(void)
{
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{
		if (m_pInputKeyboard->GetTrigger(DIK_RETURN) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_START, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
		{
			m_bStop = true;
		}
			float fRotation = m_pCamera->GetRotation();
			if (m_bStop == false)
			{
				m_nTitleEventCnt++;//�����̐؂�ւ�

				if (m_bTitleEvent == false)//�E��
				{
					motionType = WALK;
					m_pos.x += sinf(D3DX_PI / 2 + fRotation) * m_move.x;
					m_pos.z += cosf(D3DX_PI / 2 + fRotation) * m_move.x;
					m_Sabun.y = (-D3DX_PI / 2 + fRotation) - m_rot.y;

					if (m_nTitleEventCnt >= 320)
					{
						m_bTitleEvent = true;
						m_nTitleEventCnt = 0;
					}
				}

				if (m_bTitleEvent == true)//����
				{
					motionType = WALK;
					m_pos.x -= sinf(D3DX_PI / 2 + fRotation) * m_move.x;
					m_pos.z -= cosf(D3DX_PI / 2 + fRotation) * m_move.x;
					m_Sabun.y = ((D3DX_PI / 2) + fRotation) - m_rot.y;
					if (m_nTitleEventCnt % 60 == 0)
					{
						m_move.y = PLAYER_JUMP;//�W�����v���Z
					}
					if (m_nTitleEventCnt >= 320)
					{
						m_bTitleEvent = false;
						m_nTitleEventCnt = 0;
					}
				}
			}
			else if (m_bStop == true)
			{
				motionType = RANKING;
				m_pos.x += sinf(D3DX_PI + fRotation) * 0.0f;
				m_pos.z += cosf(D3DX_PI + fRotation) * 0.0f;
				m_Sabun.y = fRotation - m_rot.y;

			}

			if (m_Sabun.y > D3DX_PI)
			{
				m_Sabun.y -= D3DX_PI * 2;
			}
			else if (m_Sabun.y < -D3DX_PI)
			{
				m_Sabun.y += D3DX_PI * 2;
			}

			m_rot.y += m_Sabun.y * 0.25f;//�����]���̑���

			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2;
			}
			else if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2;
			}

			m_Sabun.y = 0;

			m_bLoopCheck = false;//���[�V�������[�v�̉���
		
	}
}

//==============================================
//				�ʒu�̔��f
//==============================================
void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==============================================
//				���݂̏��
//==============================================
void CPlayer::SetDamageState(int nType, bool bState)
{
	m_bDamageState[nType] = bState;
}
void CPlayer::SetKnockBack(int nState)
{
	m_nKnockBack = nState;
}

//==============================================
//				�ꊇNULL�� / ������
//==============================================
void CPlayer::NULLCheck(void)
{
	m_pCamera = NULL;
	for (int nCnt = 0; nCnt < PLAYER_PARTS; nCnt++)
	{
		m_pModel[nCnt] = NULL;
	}
	m_move = D3DXVECTOR3(PLAYER_SPEED, PLAYER_SPEED, 1.2f);
	m_nKey = 0;
	motionType = NEUTRAL;
	m_nUseMotionType = NEUTRAL;
	m_bLoopCheck = false;
	for (int nCnt = 0; nCnt < SCENE3D_CREATE; nCnt++)
	{
		m_bPolygon3DCheck[nCnt] = false;
	}
	m_bMeshcheck = false;
	for (int nCnt = 0; nCnt < OBJ_CREATE; nCnt++)
	{
		m_bObjRide[nCnt] = false;
	}
	for (int nCnt = 0; nCnt < OBJ_CREATE; nCnt++)
	{
		m_bObjSide[nCnt] = false;
	}

	for (int nCnt = 0; nCnt < ENEMY_CREATE; nCnt++)
	{
		m_bEnemyRide[nCnt] = false;
	}
	m_nCurrent3DPolygon = 0;
	m_nCurrentObj = 0;
	m_nCurrentSideObj = 0;
	m_bScene3DRide = false;
	m_bDamageState[TYPE_MAX] = {};
	m_nStateCnt = 0;
	m_bLadderFlag = false;
	m_bBlockUpCheck = true;
	m_bOutStage = false;
	m_nReTime = 0;
	m_nTitleEventCnt = 0;
	m_bTitleEvent = false;
	m_bStop = false;
	m_bAutoJump = false;
}


//==============================================
//				���f���̓ǂݍ���
//==============================================
HRESULT CPlayer::ModelLoad(void)
{
	FILE *pFile;

	char * pStrCur;//�擪������̃|�C���^
	char aLine[256];//������̓ǂݍ���
	char aStr[256];//������̔����o��
	int nCnt = 0;

	//�e�L�X�g�̓ǂݍ��݁�
	pFile = fopen("DATA\\TEXT\\PLAYER_LODE.txt", "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "MODEL_LOAD", strlen("MODEL_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					//�p�[�c���̓ǂݍ���
					if (memcmp(pStrCur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
					{
						pStrCur += strlen("NUM_MODEL = ");
						strcpy(aStr, pStrCur);
						m_nNumModel = atoi(aStr);
					}

					if (memcmp(pStrCur, "MODEL_NAME ", strlen("MODEL_NAME ")) == 0)
					{
						pStrCur += strlen("MODEL_NAME ");

						strcpy(aStr, pStrCur);
						while (1)
						{
							if (pStrCur[strlen(pStrCur) - 1] != 'x')
							{
								pStrCur[strlen(pStrCur) - 1] = '\0';//���s������NULL�����ɕϊ�(�Q�l�T�C�g::http://hisashi.me/blog/?p=714)
							}

							else
							{
								break;
							}

							strcpy(&m_aFileNameModel[nCnt][0], pStrCur);
						}

						nCnt += 1;
					}

					//�ǂݍ��݂̏I���
					if (memcmp(pStrCur, "END_MODEL_LOAD", strlen("END_MODEL_LOAD")) == 0)
					{
						break;
					}
				}

			}
			//�ǂݍ��݂̏I���
			if (memcmp(pStrCur, "END_MODEL_LOAD", strlen("END_MODEL_LOAD")) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);

	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	for (int nCntLoad = 0; nCntLoad < m_nNumModel; nCntLoad++)
	{
		D3DXLoadMeshFromX(m_aFileNameModel[nCntLoad],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCntLoad],
			NULL,
			&m_pNumMat[nCntLoad],
			&m_pMesh[nCntLoad]);
	}

	return S_OK;
}

//==============================================
//					���f���̔j��
//==============================================
void CPlayer::ModelUnLoad(void)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		//�}�e���A���̐��̉��
		if (m_pNumMat[nCnt] != NULL)
		{
			m_pNumMat[nCnt] = NULL;
		}
		//�}�e���A���̏��̊J��
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}
		//���b�V���̊J��
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
	}
}

//==============================================
//					UV�ǂݍ���
//==============================================
HRESULT CPlayer::TextureLoad(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MODEL_UV, &m_pTexture);

	return S_OK;
}

//==============================================
//					UV�̔j��
//==============================================
void CPlayer::TextureUnLoad(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//===================================================
//			�e���f���̈ʒu�A�����A�e�����߂�
//===================================================
void CPlayer::ModelLode(void)
{
	FILE *pFile;
	char * pStrCur;//�擪������̃|�C���^
	char aLine[256];//������̓ǂݍ���
	char aStr[256];//������̔����o��
	int nCnt = 0;
	int nWord;
	int nParent[PLAYER_PARTS];

	//�e�L�X�g�̓ǂݍ��݁�
	pFile = fopen("DATA\\TEXT\\PLAYER_LODE.txt", "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "CHARACTERSET", strlen("CHARACTERSET")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					if (memcmp(pStrCur, "PARTSSET", strlen("PARTSSET")) == 0)
					{
						while (1)
						{
							fgets(&aLine[0], 256, pFile);
							pStrCur = CSceneX::GetLIneTop(&aLine[0]);

							//�p�[�c�̃C���f�b�N�X(�̂Ȃ�0,���Ȃ�1�Ȃ�)
							if (memcmp(pStrCur, "INDEX = ", strlen("INDEX = ")) == 0)
							{
								pStrCur += strlen("INDEX = ");
								strcpy(aStr, pStrCur);
								m_aIndexParent[nCnt] = atoi(aStr);
							}
							//�e�p�[�c�̐e�����߂�A�m��
							if (memcmp(pStrCur, "PARENT = ", strlen("PARENT = ")) == 0)
							{
								pStrCur += strlen("PARENT = ");

								strcpy(aStr, pStrCur);

								nParent[nCnt] = atoi(aStr);
							}
							//�e�p�[�c��POS�̓ǂݍ��݁�
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
										m_aKeyOffseet[nCnt].fPosX = (float)atof(aStr);

									}
									else if (nCntWord == 1)//y
									{
										m_aKeyOffseet[nCnt].fPosY = (float)atof(aStr);
									}
									else//z
									{
										m_aKeyOffseet[nCnt].fPosZ = (float)atof(aStr);
									}
								}
							}
							//�e�p�[�c��ROT�̓ǂݍ��݁�
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
										m_aKeyOffseet[nCnt].fRotX = (float)atof(aStr);

									}
									else if (nCntWord == 1)//y
									{
										m_aKeyOffseet[nCnt].fRotY = (float)atof(aStr);
									}
									else//z
									{
										m_aKeyOffseet[nCnt].fRotZ = (float)atof(aStr);
									}
								}
							}

							//�p�[�c�ǂݍ��݂̏I���
							if (memcmp(pStrCur, "END_PARTSSET", strlen("END_PARTSSET")) == 0)
							{
								nCnt++;
								break;
							}
						}
					}
					//�ǂݍ��݂̏I���
					if (memcmp(pStrCur, "END_CHARACTERSET", strlen("END_CHARACTERSET")) == 0)
					{
						break;
					}
				}
			}

			//�ǂݍ��݂̏I���
			if (memcmp(pStrCur, "END_CHARACTERSET", strlen("END_CHARACTERSET")) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);

	//�ǂݍ��񂾃��f���������f���̐��A���f������
	for (int nCntLoad = 0; nCntLoad < m_nNumModel; nCntLoad++)
	{
		//�e�p�[�c�̏����ʒu�����߂遫
		m_pModel[nCntLoad] = CModel::Create(D3DXVECTOR3(m_aKeyOffseet[nCntLoad].fPosX, m_aKeyOffseet[nCntLoad].fPosY, m_aKeyOffseet[nCntLoad].fPosZ));
		//�e�p�[�c�̃��f�������߂遫
		m_pModel[nCntLoad]->BindModel(m_pBuffMat[nCntLoad], m_pNumMat[nCntLoad], m_pMesh[nCntLoad]);
		//�e�p�[�c�̃��f�������߂遫
		m_pModel[nCntLoad]->BindTexture(m_pTexture);
		//�e�p�[�c�̐e�����߂遫
		m_pModel[nCntLoad]->SetParent(m_pModel[nParent[nCntLoad]]);
	}
}

//==============================================
//				���[�V�����̓ǂݍ���
//==============================================
void CPlayer::MotionLoad(void)
{
	FILE *pFile;

	char * pStrCur;//�擪������̃|�C���^
	char aLine[256];//������̓ǂݍ���
	char aStr[256];//������̔����o��
	int nMotionKeyCnt = 0;//��̃��[�V�����Ɋ܂܂��L�[�̐�
	int nParts = 0;//�p�[�c�̌���
	int nWord;
	m_nUseMotionType = NEUTRAL;

	//�e�L�X�g�̓ǂݍ��݁�
	pFile = fopen("DATA\\TEXT\\PLAYER_LODE.txt", "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "MOTIONSET", strlen("MOTIONSET")) == 0 && motionType == m_nUseMotionType)
			{

				fgets(&aLine[0], 256, pFile);
				pStrCur = CSceneX::GetLIneTop(&aLine[0]);
				if (memcmp(pStrCur, "LOOP = ", strlen("LOOP = ")) == 0)
				{
					pStrCur += strlen("LOOP = ");
					strcpy(aStr, pStrCur);
					m_aMotionInfo[m_nUseMotionType].nLoop = atoi(aStr);
				}

				fgets(&aLine[0], 256, pFile);
				pStrCur = CSceneX::GetLIneTop(&aLine[0]);
				if (memcmp(pStrCur, "NUM_KEY = ", strlen("NUM_KEY = ")) == 0)
				{
					pStrCur += strlen("NUM_KEY = ");
					strcpy(aStr, pStrCur);
					m_aMotionInfo[m_nUseMotionType].nNumKey = atoi(aStr);
				}

				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					if (memcmp(pStrCur, "KEYSET", strlen("KEYSET")) == 0)
					{
						fgets(&aLine[0], 256, pFile);
						pStrCur = CSceneX::GetLIneTop(&aLine[0]);
						if (memcmp(pStrCur, "FRAME = ", strlen("FRAME = ")) == 0)
						{
							pStrCur += strlen("FRAME = ");
							strcpy(aStr, pStrCur);
							m_aKeyInfo000[nMotionKeyCnt].nFrame = atoi(aStr);
						}
						while (1)
						{
							fgets(&aLine[0], 256, pFile);
							pStrCur = CSceneX::GetLIneTop(&aLine[0]);

							if (memcmp(pStrCur, "KEY", strlen("KEY")) == 0)
							{
								while (1)
								{
									//�e�p�[�c��POS�̓ǂݍ��݁�
									fgets(&aLine[0], 256, pFile);
									pStrCur = CSceneX::GetLIneTop(&aLine[0]);
									if (memcmp(pStrCur, "POS =", strlen("POS =")) == 0)
									{
										pStrCur += strlen("POS =");
										strcpy(aStr, pStrCur);

										for (int nCntWord = 0; nCntWord < 3; nCntWord++)//x,y,z����
										{
											nWord = CSceneX::PopString(pStrCur, aStr);
											pStrCur += nWord;//�ǂݍ��ޕ����ʒu�����炷
											strcpy(aStr, pStrCur);

											if (nCntWord == 0)//x
											{
												m_aMotionInfo[m_nUseMotionType].aKeyInfo[nMotionKeyCnt].aKey[nParts].fPosX = (float)atof(aStr);

											}
											else if (nCntWord == 1)//y
											{
												m_aMotionInfo[m_nUseMotionType].aKeyInfo[nMotionKeyCnt].aKey[nParts].fPosY = (float)atof(aStr);
											}
											else//z
											{
												m_aMotionInfo[m_nUseMotionType].aKeyInfo[nMotionKeyCnt].aKey[nParts].fPosZ = (float)atof(aStr);
											}
										}
									}

									//�e�p�[�c��ROT�̓ǂݍ��݁�
									fgets(&aLine[0], 256, pFile);
									pStrCur = CSceneX::GetLIneTop(&aLine[0]);
									if (memcmp(pStrCur, "ROT =", strlen("ROT =")) == 0)
									{
										pStrCur += strlen("ROT =");
										strcpy(aStr, pStrCur);

										for (int nCntWord = 0; nCntWord < 3; nCntWord++)//x,y,z����
										{
											nWord = CSceneX::PopString(pStrCur, aStr);
											pStrCur += nWord;//�ǂݍ��ޕ����ʒu�����炷
											strcpy(aStr, pStrCur);

											if (nCntWord == 0)//x
											{
												m_aMotionInfo[m_nUseMotionType].aKeyInfo[nMotionKeyCnt].aKey[nParts].fRotX = (float)atof(aStr);

											}
											else if (nCntWord == 1)//y
											{
												m_aMotionInfo[m_nUseMotionType].aKeyInfo[nMotionKeyCnt].aKey[nParts].fRotY = (float)atof(aStr);
											}
											else//z
											{
												m_aMotionInfo[m_nUseMotionType].aKeyInfo[nMotionKeyCnt].aKey[nParts].fRotZ = (float)atof(aStr);
											}
										}
									}

									fgets(&aLine[0], 256, pFile);
									pStrCur = CSceneX::GetLIneTop(&aLine[0]);
									if (memcmp(pStrCur, "END_KEY", strlen("END_KEY")) == 0)
									{
										nParts++;
										break;
									}
								}
							}

							if (memcmp(pStrCur, "END_KEYSET", strlen("END_KEYSET")) == 0)
							{
								nParts = 0;
								nMotionKeyCnt++;
								break;
							}
						}
					}
					//�ǂݍ��݂̏I���
					if (memcmp(pStrCur, "END_MOTIONSET", strlen("END_MOTIONSET")) == 0)
					{
						nParts = 0;
						nMotionKeyCnt = 0;
						break;
					}
				}
			}

			//�ǂݍ��݂̏I���

			if (memcmp(pStrCur, "END_MOTIONSET", strlen("END_MOTIONSET")) == 0)
			{
				if (motionType == m_nUseMotionType)
				{
					nParts = 0;
					nMotionKeyCnt = 0;
					break;
				}
				else if (motionType != m_nUseMotionType)
				{
					m_nUseMotionType++;
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);
				}
			}
		}
	}
	fclose(pFile);
}

//==============================================
//				���[�V�����̍X�V
//==============================================
void CPlayer::UpdateMotion(void)
{
	CPlayer::MotionLoad();//�O���e�[�^����̃��[�V�����̓ǂݍ���

	KEY *pKey, *pKeyNext;//���݁A���̃L�[
	float fRateMotion;//���[�V�����̑��Βl
	float fDiffMotion;//�ЂƂO�̃��[�V�����Ƃ̍���
	D3DXVECTOR3 posMotion;//���[�V�����̎��̉�]�Ɏg�p
	D3DXVECTOR3 rotMotion;//���[�V�����̎��̉�]�Ɏg�p

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		if (m_pModel[nCnt] != NULL)
		{
			//���݂̃L�[���擾

			pKey = &m_aMotionInfo[m_nUseMotionType].aKeyInfo[m_nKey].aKey[nCnt];
			//���̃L�[���擾
			pKeyNext = &m_aMotionInfo[m_nUseMotionType].aKeyInfo[(m_nKey + 1) % m_aMotionInfo[m_nUseMotionType].nNumKey].aKey[nCnt];

			//���Βl
			fRateMotion = (float)(m_nCntFrame + 1) / (float)m_aKeyInfo000[m_nKey].nFrame;//�����_�̒l�����邽��
																						 //���������Ƃ߂āA���f���̌�����ݒ�
			fDiffMotion = pKeyNext->fRotX - pKey->fRotX;
			rotMotion.x = pKey->fRotX + (fDiffMotion*fRateMotion);//���݃L�[+(����*���Βl)

			fDiffMotion = pKeyNext->fRotY - pKey->fRotY;
			rotMotion.y = pKey->fRotY + (fDiffMotion*fRateMotion);

			fDiffMotion = pKeyNext->fRotZ - pKey->fRotZ;
			rotMotion.z = pKey->fRotZ + (fDiffMotion*fRateMotion);

			m_pModel[nCnt]->SetRot(rotMotion);//���[�V�����̔��f
		}
	}

	if (m_aMotionInfo[m_nUseMotionType].nLoop == 1 && m_bLoopCheck == true)//���[�v���郂�[�V�����ł����...
	{
		m_nCntFrame++;//�t���[���J�E���^�[�̉��Z
		if (m_nCntFrame > m_aKeyInfo000[m_nKey].nFrame)
		{
			m_nCntFrame = 0;//�������[�V�����ɂ��ǂ�
			m_nKey = (m_nKey + 1) % m_aMotionInfo[m_nUseMotionType].nNumKey;//�p�^�[�����L�[��i�߂�
		}

	}
	else//���[�v���Ȃ��ꍇ
	{
		m_nCntFrame++;//�t���[���J�E���^�[�̉��Z

		if (m_aKeyInfo000[m_nKey].nFrame < m_nCntFrame)
		{
			if (m_nKey == m_aMotionInfo[m_nUseMotionType].nNumKey - 1)//�Ō�̃L�[�̏ꍇ
			{
				if (m_aKeyInfo000[m_nKey].nFrame < m_nCntFrame)
				{
					m_nKey = 0;//�L�[��0��
					m_nCntFrame = 0;//�����t���[���ɂ��ǂ�
					motionType = NEUTRAL;
				}
			}
			else
			{
				m_nCntFrame = 0;//�����t���[���ɂ��ǂ�
				m_nKey = (m_nKey + 1) % m_aMotionInfo[m_nUseMotionType].nNumKey;//�p�^�[�����L�[��i�߂�
			}
		}
	}
}

//==============================================
//				�f�o�b�N�p����
//==============================================
void CPlayer::Debug(void)
{
	CDebug::DebugLog("\n���f���t���[�� %d/%d", m_nCntFrame, m_aKeyInfo000[m_nKey].nFrame);
	CDebug::DebugLog("\n�v���C���[�̈ʒu %.f,%.f,%.f", m_pos.x,m_pos.y, m_pos.z);
	//CDebug::DebugLog("\n�d�� %0.1f,", m_move.y);
	CDebug::DebugLog("\n����Ă��邩 %d,%d", m_bObjRide[m_nCurrentObj], m_nCurrentObj);
	//CDebug::DebugLog("\n�|���S���ɏ���Ă��� %d ,", m_bPolygon3DCheck[m_nCurrent3DPolygon]);
	CDebug::DebugLog("\n�G�l�~�[�ɏ���Ă��邩 %d,", m_bEnemyRide[m_nCurrentEnemy]);
	//CDebug::DebugLog("\n���݂̃A�N�V���� %d,", m_nUseMotionType);

}
