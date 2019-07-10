//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					�G�l�~�[���� [enemy.h]
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
#include "time.h"
#include "particle.h"

//==============================================
//				�ÓI�����o�ϐ�
//==============================================
CSound *CEnemy::m_pSound = NULL;
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = {};
LPD3DXMESH CEnemy::m_pMesh[ENEMY_PARTS] = {};
LPD3DXBUFFER CEnemy::m_pBuffMat[ENEMY_PARTS] = {};
DWORD CEnemy::m_pNumMat[ENEMY_PARTS] = {};
int CEnemy::m_nNumParts = NULL;
int CEnemy::m_aIndexParent[ENEMY_PARTS] = {};
CEnemy::KEY CEnemy::m_aKeyOffseet[ENEMY_PARTS] = {};
int CEnemy::m_nNumModel = NULL;
char CEnemy::m_aFileNameModel[ENEMY_PARTS][256] = {};
int CEnemy::m_nCreateNum = 0;//�������ꂽ���̋L��

//==============================================
//					�R���X�g���N�^
//==============================================
CEnemy::CEnemy(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	NULLCheck();

}
//==============================================
//					�f�X�g���N�^
//==============================================
CEnemy::~CEnemy()
{
}

//==============================================
//					����
//==============================================
CEnemy *CEnemy::Create(int nAIType, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_nCreateNum += 1;

	CEnemy *pEnemy = NULL;
	CModel *pModel = NULL;

	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;
		pEnemy->m_nAIType = nAIType;
		pEnemy->m_pos = pos;
		pEnemy->m_rot = rot;
		pEnemy->Init();

	}
	return pEnemy;
}
//==============================================
//					����������
//==============================================
HRESULT CEnemy::Init(void)
{
	m_OriginPos = m_pos;//����n�̋L��

	NULLCheck();

	ModelLode();
	m_pSound = CManager::GetSound();

	Vtx();
	return S_OK;
} 

//==============================================
//					�I������
//==============================================
void CEnemy::Uninit(void)
{
	m_nCreateNum = 0;

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
void CEnemy::Update(void)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)//�g�p���f�����X�V
	{
		m_pModel[nCnt]->Update();
	}
	m_posOld = m_pos;//�ߋ��̈ʒu�����L��

	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	m_pInputMouse = CManager::GetInputMouse();

	CurrentMode();//���݂̃��[�h�ɂ���ď���ς���
	Gravity();	//�d��
	MOVE();		//�ړ�
	JUMP();		//�W�����v
	CollObj();	//�I�u�W�F�N�g�̓����蔻��
	if (m_pPlayer != NULL)
	{
		if (m_bRide == true)//�v���C���[�ɓ��܂ꂽ�Ȃ�
		{
			m_bMoveStop = true;
		}
		
		if (m_bMoveStop == true)
		{
			CParticle3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y+50.0f, m_pos.z),//�ʒu
				D3DXVECTOR3((rand() % 40 - 20)*0.05f, (rand() % 20 + 1)*0.05f, (rand() % 40 - 20)*0.05f),//�ړ���
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),false, 20, 0.4f, 0);//��] �J���[ �������� �傫��

			motionType = STOP;
			m_MoveStopTime++;
			if (m_MoveStopTime >= 100)
			{
				m_bMoveStop = false;
				m_MoveStopTime = 0;
			}
		}
		
	}
	TitleEvent();//�^�C�g�����̉��o

	UpdateMotion();//���[�V�����̍X�V(�����̏��Ԃɂ��ق��̏�����������!!)

	Debug();//�f�o�b�N
}

//==============================================
//					�`�揈��
//==============================================
void CEnemy::Draw(void)
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

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_pModel[nCnt]->Draw();//�g�p���郂�f���̕`��
	}
}

//==============================================
//			���݂̃��[�h�ɂ���ď���ς���
//==============================================
void CEnemy::CurrentMode(void)
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
void CEnemy::Gravity(void)
{
	if (m_bMeshcheck == false || m_bObjRide[m_nCurrentObj] == false)//����Ă��Ȃ������ꍇ
	{
		if (m_pos.y <= 0)
		{
			m_pos.y = 0;
			m_move.y = 0;
		}
		else
		{
			m_move.y -= ENEMY_GRAVITY;//�d�͉��Z

		}
	}
}

//==============================================
//					�ړ�
//==============================================
void CEnemy::MOVE(void)
{
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		float fRotation = m_pCamera->GetRotation();
		m_pPlayer = CGame::GetPlayer();
		if (m_pPlayer != NULL && m_nAIType == 0)
		{
			if (m_pPlayer->GetSide(m_pPlayer->GetSideObjNum()) == false && m_bMoveStop == false)//�v���C���[���ǂɐG��Ă��Ȃ��ꍇ
			{
				if (m_pos.x + 100 > m_pPlayer->GetPos().x && m_pos.x - 100 < m_pPlayer->GetPos().x)
				{
					m_bSearchCheck = true;
					
					if (m_pos.x < m_pPlayer->GetPos().x && m_pos.y >= m_pPlayer->GetPos().y)//�v���C���[���E���ɂ���Ƃ�
					{
						motionType = WALK;
						m_pos.x += sinf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_pos.z += cosf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_Sabun.y = (-D3DX_PI / 2 + fRotation) - m_rot.y;
					}
					if (m_pos.x > m_pPlayer->GetPos().x && m_pos.y >= m_pPlayer->GetPos().y)//�v���C���[�������ɂ���Ƃ�
					{
						motionType = WALK;
						m_pos.x -= sinf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_pos.z -= cosf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_Sabun.y = ((D3DX_PI / 2) + fRotation) - m_rot.y;
					}
				}
				else//�v���C���[���͈͊O�Ȃ����̈ʒu�ɖ߂�
				{
					m_bSearchCheck = false;
					if (m_pos.x < m_OriginPos.x)//����̈ʒu���獶�ɂ���Ƃ�
					{
						motionType = WALK;
						m_pos.x += sinf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_pos.z += cosf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_Sabun.y = (-D3DX_PI / 2 + fRotation) - m_rot.y;
					}
					if (m_pos.x > m_OriginPos.x)//����̈ʒu����E�ɂ���Ƃ�
					{
						motionType = WALK;
						m_pos.x -= sinf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_pos.z -= cosf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_Sabun.y = ((D3DX_PI / 2) + fRotation) - m_rot.y;
					}
				}
			}
		}
		if (m_pPlayer != NULL && m_nAIType == 1)
		{
			if (m_pos.x+100.0f > m_pPlayer->GetPos().x && m_pos.x -130 < m_pPlayer->GetPos().x)
			{
				CDebug::DebugLog("\n�G�l�~�[�̎˒��͈͓��ł�,");
				motionType = WALK;
				if (m_pos.z >= -50.0f)
				{
					CParticle3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z),//�ʒu
						D3DXVECTOR3((rand() % 40 - 20)*0.05f, (rand() % 20 + 1)*0.1f, (rand() % 40 - 20)*0.05f),//�ړ���
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, 30, 0.2f, 1);//�J���[ ��] �������� �傫��
				}
				m_pos.x += sinf(D3DX_PI + fRotation) * m_move.z;
				m_pos.z += cosf(D3DX_PI + fRotation) * m_move.z;
				m_Sabun.y = fRotation - m_rot.y;
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
}

//==============================================
//					�W�����v
//==============================================
void CEnemy::JUMP(void)
{
	//if (m_bObjRide[m_nCurrentObj] == true|| m_pos.y <= 0)//�n�ʂɐG��Ă�����W�����v�\
	//{
	//	if (m_pInputKeyboard->GetTrigger(DIK_J) == true)
	//	{
	//		m_move.y = ENEMY_JUMP;//�W�����v���Z
	//	}
	//}
	m_pos.y += m_move.y;
}


//==============================================
//			�����蔻��Ɋւ��鏈��
//==============================================
void CEnemy::Vtx(void)
{
	int nNumVtx;
	DWORD sizeFVF;
	BYTE *pVtxBuff;

	m_VtxMin = D3DXVECTOR3(10000, 10000, 10000);	//�ő�l
	m_VtxMax = D3DXVECTOR3(-10000, -10000, -10000);	//�ŏ��l

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{

		//���_���̎擾
		nNumVtx = m_pMesh[nCnt]->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(m_pMesh[nCnt]->GetFVF());

		//���_�o�b�t�@�����b�N
		m_pMesh[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVer = 0; nCntVer < nNumVtx; nCntVer++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (m_VtxMin.x >= vtx.x)
			{
				m_VtxMin.x = vtx.x;
			}
			if (m_VtxMin.y >= vtx.y)
			{
				m_VtxMin.y = vtx.y;
			}
			if (m_VtxMin.z >= vtx.z)
			{
				m_VtxMin.z = vtx.z;
			}

			if (m_VtxMax.x <= vtx.x)
			{
				m_VtxMax.x = vtx.x;
			}
			if (m_VtxMax.y <= vtx.y)
			{
				m_VtxMax.y = vtx.y;
			}
			if (m_VtxMax.z <= vtx.z)
			{
				m_VtxMax.z = vtx.z;
			}
			//�T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//D3DXVECTOR3 size = GetModelSize();
		//m_VtxMin = D3DXVECTOR3(m_VtxMin.x * m_modelSize.x, m_VtxMin.y * m_modelSize.y, m_VtxMin.z * m_modelSize.z);
		//m_VtxMax = D3DXVECTOR3(m_VtxMax.x * m_modelSize.x, m_VtxMax.y * m_modelSize.y, m_VtxMax.z * m_modelSize.z);

		//m_VtxMin = D3DXVECTOR3(m_VtxMin.x, m_VtxMin.y, m_VtxMin.z);
		//m_VtxMax = D3DXVECTOR3(m_VtxMax.x, m_VtxMax.y, m_VtxMax.z);

		//���_�o�b�t�@���A�����b�N
		m_pMesh[nCnt]->UnlockVertexBuffer();
	}
}

//==============================================
//				�����蔻�菈��
//==============================================
bool CEnemy::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	D3DXVECTOR3 pos = GetPos();
	m_pObj = CGame::GetObj(m_nCurrentObj);
	CTime *pTime = CGame::GetTime();

	//�㔻��
	if (pos.x + m_VtxMin.x < pPos->x + 0.0f &&//���l��ς���Ɣ��蕔�����ς��
		pos.x + m_VtxMax.x > pPos->x - 0.0f &&

		pos.z + m_VtxMin.z < pPos->z + 0.0f &&
		pos.z + m_VtxMax.z > pPos->z - 0.0f)
	{
		if (pos.y - m_VtxMax.y <= pPosOld->y + OBJ_Y &&
			pos.y + m_VtxMax.y > pPos->y - OBJ_Y)
		{
  			m_bRide = true;
			m_pObj->SetRide(false);//����Ă��Ȃ���Ԃɂ��Ă���
			pPos->y = (pos.y + m_VtxMax.y) + OBJ_Y;
		}
		//OBJ��ŃW�����v�����ۂ̏���
		if (pos.y + m_VtxMax.y >= pPosOld->y + OBJ_Y &&
			pos.y + m_VtxMax.y < pPos->y - OBJ_Y)
		{
			m_bRide = false;
			//pPos->y = (pos.y + m_VtxMax.y) + OBJ_Y;
		}
	}
	else
	{
		m_bRide = false;
	}


	if (m_VtxMax.y + pos.y - 0.5f > pPos->y + OBJ_Y&&
		m_VtxMin.y + pos.y - 40.0f <= pPos->y + OBJ_Y)
	{
		//�O�㔻��
		if (pos.x + m_VtxMin.x < pPos->x + 0.0f &&
			pos.x + m_VtxMax.x > pPos->x - 0.0f)
		{
			//��O�̔���
			if (pos.z + m_VtxMin.z >= pPosOld->z - OBJ_Z&&
				pos.z + m_VtxMin.z < pPos->z + OBJ_Z)
			{
				pPos->z = pos.z + m_VtxMin.z - OBJ_Z;
			}
			//���̔���
			else if (pos.z + m_VtxMax.z <= pPosOld->z + OBJ_Z&&
				pos.z + m_VtxMax.z > pPos->z - OBJ_Z)
			{
				pPos->z = pos.z + m_VtxMax.z + OBJ_Z;
			}
		}

		//���E����
		if (pos.z + m_VtxMin.z < pPos->z + 0.0f &&
			pos.z + m_VtxMax.z > pPos->z - 0.0f)
		{
			//���̔���
			if (pos.x + m_VtxMin.x >= pPosOld->x - OBJ_X&&
				pos.x + m_VtxMin.x < pPos->x + OBJ_X)
			{
				if (m_pSound != NULL)
				{
					m_pSound->PlaySound(CSound::SE_DAMAGE);
				}
				pPos->x = pos.x + m_VtxMin.x - OBJ_X;
				m_pObj->SetRide(false);//����Ă��Ȃ���Ԃɂ��Ă���
				m_pPlayer->SetDamageState(CPlayer::ENEMY, true);
				m_pPlayer->SetKnockBack(0);//�E��
				pTime->SetDemeritTime(3);
			}
			//�E�̔���
			else if (pos.x + m_VtxMax.x <= pPosOld->x + OBJ_X&&
				pos.x + m_VtxMax.x > pPos->x - OBJ_X)
			{
				if (m_pSound != NULL)
				{
					m_pSound->PlaySound(CSound::SE_DAMAGE);
				}
				pPos->x = pos.x + m_VtxMax.x + OBJ_X;
				m_pObj->SetRide(false);//����Ă��Ȃ���Ԃɂ��Ă���
				m_pPlayer->SetDamageState(CPlayer::ENEMY, true);
				m_pPlayer->SetKnockBack(1);//����
				pTime->SetDemeritTime(3);
			}
		}
	}

	return m_bRide;
}

//==============================================
//				obj�Ƃ̓����蔻��
//==============================================
void CEnemy::CollObj(void)
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
		}
	}
}

//==============================================
//				�^�C�g�����̉��o
//==============================================
void CEnemy::TitleEvent(void)
{
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{
		if (m_pInputKeyboard->GetTrigger(DIK_RETURN) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_START, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
		{
			m_bStop = true;
			m_nTitleEventCnt = 0;
		}
		float fRotation = m_pCamera->GetRotation();

		if (m_bStop == false)
		{
			m_nTitleEventCnt++;//�����̐؂�ւ� / JUMP�Ԋu

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
				if (m_nTitleEventCnt >= 320)
				{
					m_bTitleEvent = false;
					m_nTitleEventCnt = 0;
				}
			}
		}
		else if (m_bStop == true)
		{
			m_nTitleEventCnt++;
			m_pos.x += sinf(D3DX_PI + fRotation) * 0.0f;
			m_pos.z += cosf(D3DX_PI + fRotation) * 0.0f;
			m_Sabun.y = fRotation - m_rot.y;
			if (m_nTitleEventCnt % 40 == 0)
			{
				m_move.y = ENEMY_JUMP;//�W�����v���Z
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
}

//==============================================
//				�ꊇNULL�� / ������
//==============================================
void CEnemy::NULLCheck(void)
{

	m_move = D3DXVECTOR3(ENEMY_SPEED, ENEMY_SPEED, ENEMY_SPEED);
	m_nKey = 0;
	motionType = NEUTRAL;
	m_nUseMotionType = NEUTRAL;
	m_pCamera = NULL;
	m_bLoopCheck = false;
	m_bMeshcheck = false;
	for (int nCnt = 0; nCnt < OBJ_CREATE; nCnt++)
	{
		m_bObjRide[nCnt] = false;

	}
	for (int nCnt = 0; nCnt < OBJ_CREATE; nCnt++)
	{
		m_bObjSide[nCnt] = false;
	}
	m_nCurrentObj = 0;
	m_nTitleEventCnt = 0;
	m_bTitleEvent = false;
	m_bStop = false;
	m_bSearchCheck = false;
	m_bMoveStop = false;
	m_MoveStopTime = 0;
}
//==============================================
//				�ʒu�̔��f
//==============================================
void CEnemy::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==============================================
//				���f���̓ǂݍ���
//==============================================
HRESULT CEnemy::ModelLoad(void)
{
	FILE *pFile;

	char * pStrCur;//�擪������̃|�C���^
	char aLine[256];//������̓ǂݍ���
	char aStr[256];//������̔����o��
	int nCnt = 0;

	//�e�L�X�g�̓ǂݍ��݁�
	pFile = fopen("DATA\\TEXT\\ENEMY01.txt", "r");

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
void CEnemy::ModelUnLoad(void)
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
HRESULT CEnemy::TextureLoad(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, ENEMY01_UV, &m_pTexture);

	return S_OK;
}

//==============================================
//					UV�̔j��
//==============================================
void CEnemy::TextureUnLoad(void)
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
void CEnemy::ModelLode(void)
{
	FILE *pFile;
	char * pStrCur;//�擪������̃|�C���^
	char aLine[256];//������̓ǂݍ���
	char aStr[256];//������̔����o��
	int nCnt = 0;
	int nWord;
	int nParent[ENEMY_PARTS];

	//�e�L�X�g�̓ǂݍ��݁�
	pFile = fopen("DATA\\TEXT\\ENEMY01.txt", "r");

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
void CEnemy::MotionLoad(void)
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
	pFile = fopen("DATA\\TEXT\\ENEMY01.txt", "r");

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
void CEnemy::UpdateMotion(void)
{
	CEnemy::MotionLoad();//�O���e�[�^����̃��[�V�����̓ǂݍ���

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
void CEnemy::Debug(void)
{
		CDebug::DebugLog("\n�d�� %0.1f,", m_move.y);
	CDebug::DebugLog("\n����Ă��邩 %d,", m_bObjRide[m_nCurrentObj]);
	CDebug::DebugLog("\n�G�̈ʒu %.f,%.f,%.f", m_pos.x, m_pos.y,m_pos.z);

}
