//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					�I�u�W�F�N�g�������� [object.cpp]
//			Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "debugLog.h"
#include "sound.h"
#include "input.h"
#include "sceneX.h"
#include "object.h"
#include "game.h"
#include "player.h"
#include "particle.h"
#include "time.h"
#include "polygon2D.h"
#include "polygon3D.h"
//==============================================
//				�ÓI�����o�ϐ�
//==============================================
CSound *CObject::m_pSound = NULL;
//�e�L�X�g�ǂݍ��݊֘A
int CObject::m_nNumObject = NULL;
int CObject::m_nNumTexture = NULL;
char CObject::m_aFileNameObject[MAX_OBJECT][256] = {};
char CObject::m_aFileNameTexture[MAX_OBJECT][256] = {};
//���f�����
LPD3DXMESH CObject::m_pMesh[MAX_OBJECT] = {};
LPD3DXBUFFER CObject::m_pBuffMat[MAX_OBJECT] = {};
DWORD CObject::m_pNumMat[MAX_OBJECT] = {};
//�摜�֘A
LPDIRECT3DTEXTURE9 CObject::m_pTexture[OBJ_TEXTURE_NUM] = {};

int CObject::m_nCreateNum = 0;//�������ꂽ���̋L��
int CObject::m_nSwitchNum = 0;

//==============================================
//					�R���X�g���N�^
//==============================================
CObject::CObject(int nPriority, DATA_TYPE dataType) :CSceneX(nPriority, dataType)
{
	//m_pTexture = NULL;		//�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;		//���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);
	m_VtxMin = GetVtxMin();
	m_VtxMax = GetVtxMax();
	m_bRide = false;
	m_bSide = false;
	m_bGimmickFlag = false;
	m_bLadderFlag = false;
	m_nFlagTimeCnt = 0;
	m_bBlockUP = false;
	m_nUPCnt = 0;
	m_bRotGimmick = false;
	m_bDrillGimmick = false;
	m_nDrillCnt = 0;
}
//==============================================
//					�f�X�g���N�^
//==============================================
CObject::~CObject()
{

}

//==============================================
//					����
//==============================================
CObject *CObject::Create(int nObjType, int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_nCreateNum += 1;
	CObject *pObject = NULL;
	if (pObject == NULL)
	{
		pObject = new CObject;
		pObject->m_objType = nObjType;
		if (nObjType == 1)
		{
			m_nSwitchNum += 1;
		}
		pObject->BindObject(m_pBuffMat[nObjType], m_pNumMat[nObjType], m_pMesh[nObjType]);
		pObject->BindTexture(m_pTexture[nTexType]);	
		pObject->Init();
		pObject->SetPos(pos);
		pObject->SetRot(rot);
	}
	return pObject;
}
//==============================================
//					����������
//==============================================
HRESULT CObject::Init(void)
{
	CSceneX::Init();

	m_VtxMin = GetVtxMin();
	m_VtxMax = GetVtxMax();
	m_bRide = false;
	m_bSide = false;
	m_bGimmickFlag = false;
	m_bLadderFlag = false;
	m_nFlagTimeCnt = 0;
	m_bBlockUP = false;
	m_nUPCnt = 0;
	m_bRotGimmick = false;
	m_bDrillGimmick = false;
	m_nDrillCnt = 0;
	m_pSound = CManager::GetSound();

	return S_OK;
}

//==============================================
//					�I������
//==============================================
void CObject::Uninit(void)
{
	//���̃��[�h�̂��߂ɂ����Ő��l��0��
	m_nCreateNum = 0;
	m_nSwitchNum = 0;

	if (m_pSound != NULL)
	{
		m_pSound->StopSound();
	}

	CSceneX::Uninit();
}

//==============================================
//					�X�V����
//==============================================
void CObject::Update(void)
{
	CSceneX::Update();
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	m_pPlayer = CGame::GetPlayer();

	SwitchFlag();

	if (m_objType == 18)//��q
	{
		CDebug::DebugLog("\n�C�x���g %d", m_bLadderFlag);

		if (m_pPlayer != NULL)
		{
			D3DXVECTOR3 pos = m_pPlayer->GetPos();
			CPolygon2D *pPolygon2D = CGame::GetPolygon2D(4);//�A�C�R���̕\��
			if (GetPos().x + 12 > pos.x && GetPos().x - 15 < pos.x)
			{
				
				if (pPolygon2D != NULL)
				{
					pPolygon2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				CDebug::DebugLog("\n��q�͈͓�");
				if (m_pInputKeyboard->GetTrigger(DIK_W) == true || 
					m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 0) == true)
				{
					m_bLadderFlag = true;
				}
			}
			else
			{
				if (pPolygon2D != NULL)
				{
					pPolygon2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				}
			}
		}
	}

	Gimmick();//�M�~�b�N�����̂܂Ƃ�
	
	
	Debug();
	//CDebug::DebugLog("\n����Ă���@%d", m_bRide);
	//CDebug::DebugLog("\n���ɐG��Ă���@%d", m_bSide);

}

//==============================================
//					�`�揈��
//==============================================
void CObject::Draw(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	if (m_objType == 20)
	{
		CSceneX::DrawShadow();
	}
	else
	{
		CSceneX::Draw();
	}
}

//==============================================
//	�I�u�W�F�N�g�ɏ���Ă��邩���m�F(��ɓG�_���[�W�ɂ��ӂ��Ƃ΂��ȂǂŎg�p����)
//==============================================
void CObject::SetRide(bool bRide)
{
	m_bRide = bRide;
}

//==============================================
//				�M�~�b�N�t���O
//==============================================
void CObject::SetGimmickFlag(bool bFlag)
{
	m_bGimmickFlag = bFlag;
}
void CObject::SetLadderFlag(bool bFlag)
{
	m_bLadderFlag = bFlag;
}
void CObject::Gimmick(void)
{
	if (m_objType == 21)//+ �㉺�u���b�N
	{
		D3DXVECTOR3 pos = GetPos();

		switch (m_bBlockUP)
		{
		case true:
			m_nUPCnt++;
			pos.y += 1.0f;
			SetPos(pos);
			if (m_nUPCnt >= 40)
			{
				m_bBlockUP = false;
				m_nUPCnt = 0;
			}
			break;

		case false:
			m_nUPCnt++;
			pos.y -= 1.0f;
			SetPos(pos);
			if (m_nUPCnt >= 40)
			{
				m_bBlockUP = true;
				m_nUPCnt = 0;
			}
			break;
		}
	}

	if (m_objType == 19)//+ ��]�n�M�~�b�N�̉�]
	{
		D3DXVECTOR3 rot = GetRot();
		rot.z++;
		SetRot(rot);
		if (m_pPlayer != NULL)
		{
			if (m_pPlayer->GetCurrentObj() == 11)
			{
				m_bRotGimmick = true;
			}
		}
	}
	if (m_bRotGimmick == true)
	{
		D3DXVECTOR3 pos = GetPos();//170

		if (pos.y >= 170.0f&&pos.x <= 650.0f)
		{
			pos.y -= 10.0f;
		}
		else if (pos.y <= 170.0f)
		{
			if (pos.x <= 550.0f)
			{
				CPolygon3D::Create(0, D3DXVECTOR3(pos.x / 2.0f + 20.0f, pos.y / 2.0f - 20.0f, pos.z - 10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 1, 4, 3, false);
			}
			pos.x += 3.0f;
		}
		if (pos.x >= 650.0f)
		{
			pos.y += 3.0f;
		}
		SetPos(pos);
	}
	if (m_objType == 20)//+ �h�����M�~�b�N�̉�]
	{
		D3DXVECTOR3 rot = GetRot();
		rot.z += 0.5f;
		SetRot(rot);
		D3DXVECTOR3 pos = GetPos();

		switch (m_bDrillGimmick)
		{
		case true:
			m_nDrillCnt++;
			pos.z -= 5.0f;
			SetPos(pos);
			if (m_nDrillCnt >= 70)
			{
				m_bDrillGimmick = false;
				m_nDrillCnt = 0;
			}
			break;

		case false:
			m_nDrillCnt++;
			pos.z += 5.0f;
			SetPos(pos);
			if (m_nDrillCnt >= 70)
			{
				m_bDrillGimmick = true;
				m_nDrillCnt = 0;
			}
			break;
		}
	}
}
//==============================================
//				�X�C�b�`�n�M�~�b�N
//==============================================
void CObject::SwitchFlag(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer != NULL)
	{
		if (m_objType == 1)//�X�C�b�`�n�M�~�b�N�ł����
		{
			D3DXVECTOR3 pos = GetPos();
			CPolygon2D *pPolygon2D = CGame::GetPolygon2D(2);//�u����v�A�C�R���̕\��

			if (pos.x + 50 > pPlayer->GetPos().x && pos.x - 50 < pPlayer->GetPos().x&&pos.y - 15.0f <= pPlayer->GetPos().y &&
				pos.z >= pPlayer->GetPos().z&& pos.y+10.0f >= pPlayer->GetPos().y)
			{
				CDebug::DebugLog("\nGimmick�͈͓�");
				if (m_bGimmickFlag == false)
				{
					if (pPolygon2D != NULL)
					{
						pPolygon2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					}
					if (m_pInputKeyboard->GetTrigger(DIK_RETURN) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
					{
						if (m_pSound != NULL)
						{
							m_pSound->PlaySound(CSound::SE_SWITCH);
						}
						m_bGimmickFlag = true;
						CGame::SetSwitchFlagNum();//���Z
					}
				}
				else if (m_bGimmickFlag == true)
				{
					if (pPolygon2D != NULL)
					{
						pPolygon2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
					}
				}
			}
			else if (pos.x - 50 > pPlayer->GetPos().x && pos.x - 150 < pPlayer->GetPos().x||
						pos.x + 50 < pPlayer->GetPos().x && pos.x + 150 > pPlayer->GetPos().x)
			{
				if (pPolygon2D != NULL)
				{
					pPolygon2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				}
			}

			if (m_bGimmickFlag == true)
			{
				D3DXVECTOR3 pos = GetPos();
				m_nFlagTimeCnt++;
				D3DXVECTOR3 rot = GetRot();
				if (m_nFlagTimeCnt <= 8)
				{
					rot.z -= 0.2f;
				}
				SetRot(rot);
			}
			else
			{
				CParticle3D::Create(D3DXVECTOR3(pos.x, pos.y, pos.z - 20),//�ʒu
					D3DXVECTOR3((float)(rand() % 50)*0.05f, (float)(rand() % 3) * 0.5f, (float)(rand() % 50)*0.05f),//�ړ���
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),//��] 
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), true,50, 0.2f, 0);//�J���[ �������� �g�嗦

			}
		}
	}
}

//==============================================
//				�����蔻�菈��
//==============================================
bool CObject::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, int nType)
{
	D3DXVECTOR3 pos = GetPos();
	if (m_objType != 10 && m_objType != 17)
	{
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
				pPos->y = (pos.y + m_VtxMax.y) + OBJ_Y;
			}
			//OBJ��ŃW�����v�����ۂ̏���
			if (pos.y + m_VtxMax.y < pPos->y + OBJ_Y)
			{
				m_bRide = false;
			}
		}
		else
		{
			m_bRide = false;
		}

		//������
		if (m_objType == 16|| m_objType == 24)
		{
			if (pos.x + m_VtxMin.x < pPos->x + 0.0f &&
				pos.x + m_VtxMax.x > pPos->x - 0.0f &&
				pos.z + m_VtxMin.z < pPos->z + 0.0f &&
				pos.z + m_VtxMax.z > pPos->z - 0.0f)
			{
				if (pos.y + m_VtxMin.y > pPosOld->y - 0 &&
					pos.y + m_VtxMin.y < pPos->y + 40)
				{

					pPos->y = (pos.y + m_VtxMin.y) - 40;
				}
			}
		}
	}
	return m_bRide;
}

bool CObject::CollSide(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,
	D3DXVECTOR3 *pMove, int nType)
{
	D3DXVECTOR3 pos = GetPos();
	CTime *pTime = CGame::GetTime();

	if (m_objType != 10 && m_objType != 17)
	{
		if (m_VtxMax.y + pos.y - 0.5f > pPos->y + OBJ_Y&&
			m_VtxMin.y + pos.y - 40.0f <= pPos->y + OBJ_Y)
		{
			//�O�㔻��
			if (m_objType == 20)
			{
				if (pos.x + m_VtxMin.x < pPos->x + 0.0f &&
					pos.x + m_VtxMax.x > pPos->x - 0.0f)
				{
					//��O�̔���
					if (pos.z + m_VtxMin.z >= pPosOld->z - OBJ_Z&&
						pos.z + m_VtxMin.z < pPos->z + OBJ_Z)
					{
						pPos->z = pos.z + m_VtxMin.z - OBJ_Z;
						if (nType == DATA_TYPE_PLAYER)
						{
							if (m_pSound != NULL)
							{
								m_pSound->PlaySound(CSound::SE_CRASH);
								m_pSound->PlaySound(CSound::SE_DAMAGE);
							}
							m_pPlayer->SetDamageState(CPlayer::OBJ,true);
							m_pPlayer->SetKnockBack(2);
							pTime->SetDemeritTime(10);

						}
					}
					//���̔���
					else if (pos.z + m_VtxMax.z <= pPosOld->z + OBJ_Z&&
						pos.z + m_VtxMax.z > pPos->z - OBJ_Z)
					{
						pPos->z = pos.z + m_VtxMax.z + OBJ_Z;
						if (nType == DATA_TYPE_PLAYER)
						{
							if (m_objType == 20)
							{
								m_pPlayer->SetDamageState(CPlayer::OBJ, true);
								m_pPlayer->SetKnockBack(3);
								pTime->SetDemeritTime(10);

							}
						}
					}
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
					pPos->x = pos.x + m_VtxMin.x - OBJ_X;
					if (nType == DATA_TYPE_PLAYER)
					{
						m_bSide = true;
						if (m_objType == 19)
						{
							if (m_pSound != NULL)
							{
								m_pSound->PlaySound(CSound::SE_DAMAGE);
							}
							m_pPlayer->SetDamageState(CPlayer::OBJ, true);
							m_pPlayer->SetKnockBack(0);//�E��
							pTime->SetDemeritTime(10);

						}
					}

				}
				//�E�̔���
				else if (pos.x + m_VtxMax.x <= pPosOld->x + OBJ_X&&
					pos.x + m_VtxMax.x > pPos->x - OBJ_X)
				{
					pPos->x = pos.x + m_VtxMax.x + OBJ_X;
					if (nType == DATA_TYPE_PLAYER)
					{
						m_bSide = true;
						if (m_objType == 19)
						{
							if (m_pSound != NULL)
							{
								m_pSound->PlaySound(CSound::SE_DAMAGE);
							}
							m_pPlayer->SetDamageState(CPlayer::OBJ, true);
							m_pPlayer->SetKnockBack(1);//����
							pTime->SetDemeritTime(10);

						}
					}
				}
				//���ɐG��ĂȂ��ꍇ
				if (pos.x + m_VtxMin.x > pPos->x + OBJ_X ||
					pos.x + m_VtxMax.x < pPos->x - OBJ_X)
				{
					if (nType == DATA_TYPE_PLAYER)
					{
						m_bSide = false;
					}
				}
			}

		}
		else
		{
			if (nType == DATA_TYPE_PLAYER)
			{
				m_bSide = false;
			}
		}
	}
	return m_bSide;
}


//==============================================
//			�I�u�W�F�N�g�̓ǂݍ���
//==============================================
HRESULT CObject::ObjectLoad(void)
{
	FILE *pFile;

	char * pStrCur;		//�擪������̃|�C���^
	char aLine[256];	//������̓ǂݍ���
	char aStr[256];		//������̔����o��
	int nCnt = 0;

	//�e�L�X�g�̓ǂݍ���
	pFile = fopen(OBJ_TEXT, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "OBJECT_LOAD", strlen("OBJECT_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = GetLIneTop(&aLine[0]);

					//�p�[�c���̓ǂݍ���
					if (memcmp(pStrCur, "NUM_OBJECT = ", strlen("NUM_OBJECT = ")) == 0)
					{
						pStrCur += strlen("NUM_OBJECT = ");
						strcpy(aStr, pStrCur);
						m_nNumObject = atoi(aStr);
					}
					//�g�p���閼�O�̊m�F
					if (memcmp(pStrCur, "OBJECT_NAME ", strlen("OBJECT_NAME ")) == 0)
					{
						pStrCur += strlen("OBJECT_NAME ");

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

							strcpy(&m_aFileNameObject[nCnt][0], pStrCur);
						}

						nCnt += 1;
					}

					//�ǂݍ��݂̏I���
					if (memcmp(pStrCur, "END_OBJECT_LOAD", strlen("END_OBJECT_LOAD")) == 0)
					{
						break;
					}
				}

			}
			//�ǂݍ��݂̏I���
			if (memcmp(pStrCur, "END_OBJECT_LOAD", strlen("END_OBJECT_LOAD")) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);

	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < m_nNumObject; nCnt++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_aFileNameObject[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCnt],
			NULL,
			&m_pNumMat[nCnt],
			&m_pMesh[nCnt]);
	}

	return S_OK;
}
//==============================================
//				�I�u�W�F�N�g�̔j��
//==============================================
void CObject::ObjectUnLoad(void)
{
	for (int nCnt = 0; nCnt < m_nNumObject; nCnt++)
	{
		//���b�V���̊J��
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		//�}�e���A���֘A�̊J��
		if (m_pNumMat[nCnt] != NULL)
		{
			m_pNumMat[nCnt] = NULL;
		}
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}
	}
}

//==============================================
//					UV�̓ǂݍ���
//==============================================
HRESULT CObject::TextureLoad(void)
{
	FILE *pFile;

	char * pStrCur;//�擪������̃|�C���^
	char aLine[256];//������̓ǂݍ���
	char aStr[256];//������̔����o��
	int nCntTexture = 0;

	//�e�L�X�g�̓ǂݍ��݁�
	pFile = fopen(OBJ_TEXT, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "TEXTURE_LOAD", strlen("TEXTURE_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					//�I�u�W�F�N�g�Ɏg�p����摜�̐�
					if (memcmp(pStrCur, "NUM_TEXTURE = ", strlen("NUM_TEXTURE = ")) == 0)
					{
						pStrCur += strlen("NUM_TEXTURE = ");
						strcpy(aStr, pStrCur);
						m_nNumTexture = atoi(aStr);
					}

					//�I�u�W�F�N�g�Ɏg�p����摜�̖��O
					if (memcmp(pStrCur, "TEXTURE_NAME ", strlen("TEXTURE_NAME ")) == 0)
					{
						pStrCur += strlen("TEXTURE_NAME ");

						strcpy(aStr, pStrCur);
						while (1)
						{
							if (pStrCur[strlen(pStrCur) - 1] != 'g')
							{
								pStrCur[strlen(pStrCur) - 1] = '\0';//���s������NULL�����ɕϊ�(�Q�l�T�C�g::http://hisashi.me/blog/?p=714)

							}

							else
							{
								break;
							}

							strcpy(&m_aFileNameTexture[nCntTexture][0], pStrCur);
						}

						nCntTexture += 1;
					}

					//�ǂݍ��݂̏I���
					if (memcmp(pStrCur, "END_TEXTURE_LOAD", strlen("END_TEXTURE_LOAD")) == 0)
					{
						break;
					}
				}

			}
			//�ǂݍ��݂̏I���
			if (memcmp(pStrCur, "END_TEXTURE_LOAD", strlen("END_TEXTURE_LOAD")) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);

	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	for (int nCnt = 0; nCnt < m_nNumTexture; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aFileNameTexture[nCnt], &m_pTexture[nCnt]);
	}

	return S_OK;
}
//==============================================
//					UV�̔j��
//==============================================
void CObject::TextureUnLoad(void)
{
	for (int nCnt = 0; nCnt < m_nNumTexture; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}


//==============================================
//					�f�o�b�N
//==============================================
void CObject::Debug(void)
{
	D3DXVECTOR3 pos = GetPos();

	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	if (m_objType == 20)
	{
		if (m_pInputKeyboard->GetPress(DIK_UP) == true)
		{
			pos.z -= 3.0f;
		}
		if (m_pInputKeyboard->GetPress(DIK_DOWN) == true)
		{
			pos.z += 3.0f;
		}

		if (m_pInputKeyboard->GetPress(DIK_LEFT) == true)
		{
			pos.x -= 1.0f;
		}
		if (m_pInputKeyboard->GetPress(DIK_RIGHT) == true)
		{
			pos.x += 1.0f;
		}
	}
	SetPos(pos);

	//CDebug::DebugLog("\n�I�u�W�F�N�g�������@%d", m_nCreateNum);

}

