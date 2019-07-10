//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�v���C���[���� [player.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "manager.h"
#include "debugLog.h"
#include "sound.h"
#include "camera.h"
#include "input.h"
#include "game.h"
//#include "sceneX.h"
#include "model.h"
#include "player.h"
#include "object.h"
#include "scene3D.h"

//=====================================================================
//�ÓI�����o�ϐ�
//=====================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture[SAMPLE_OBJ_NUM] = {};
LPD3DXMESH CPlayer::m_pMesh[SAMPLE_OBJ_NUM] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat[SAMPLE_OBJ_NUM] = {};
DWORD CPlayer::m_pNumMat[SAMPLE_OBJ_NUM] = {};
CPlayer::KEY CPlayer::m_aKeyOffseet[SAMPLE_OBJ_NUM] = {};
int CPlayer::m_nNumModel = NULL;
int CPlayer::m_nNumTex = NULL;
char CPlayer::m_aFileNameModel[SAMPLE_OBJ_NUM][256] = {};
char CPlayer::m_aFileNameTex[SAMPLE_OBJ_NUM][256] = {};

//==============================================
//�R���X�g���N�^
//==============================================
CPlayer::CPlayer(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	for (int nCnt = 0; nCnt < SAMPLE_OBJ_NUM; nCnt++)
	{
		m_pModel[nCnt] = NULL;
	}

	m_pos = D3DXVECTOR3(0, 0, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);

	m_nSampleObj_ViewType = 0;

}
//==============================================
//�f�X�g���N�^
//==============================================
CPlayer::~CPlayer()
{
}

//==============================================
//����
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
//����������
//==============================================
HRESULT CPlayer::Init(void)
{
	ModelLode();//�e���f���̈ʒu�A�����A�e�����߂�
	m_move = D3DXVECTOR3(2.0f,2.0f,2.0f);//�ړ���
	m_nSampleObj_ViewType = 0;
	return S_OK;
} 

//==============================================
//�I������
//==============================================
void CPlayer::Uninit(void)
{
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
//�X�V����
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
	m_pGame = CManager::GetGame();

	SampleChange();		//�T���v��obj�̕ύX
	OperationManual();	//����̕ύX
	if (m_pGame != NULL)
	{
		if (m_pGame->GetInputMode() == 0)//���̓��[�h(�L�[�{�[�h)
		{
			MOVE();	//�ړ�
		}
	}

	if (m_pInputKeyboard->GetTrigger(DIK_RETURN) == true|| m_pInputKeyboard->GetTrigger(DIK_X) == true)//�ʒu�E�����̃��Z�b�g
	{
		m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	//if (m_pInputKeyboard->GetPress(DIK_LSHIFT) == true)//������ς���
	//{
	//	m_rot.y += 0.05f;
	//}


	Debug();//�f�o�b�N

}

//==============================================
//�`�揈��
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

	m_pModel[m_nSampleObj_ViewType]->Draw();//�g�p���郂�f���̕`��
}

//==============================================
//�T���v���̕ύX
//==============================================
void CPlayer::SampleChange(void)
{
	//+ @   @   @   @   @   @   @   @   @   @   @   @
	//+						���̓��[�h(�L�[�{�[�h��)
	//+ @   @   @   @   @   @   @   @   @   @   @   @

	if (m_pGame != NULL)
	{
		if (m_pGame->GetInputMode() == 0)
		{
			//�L�[�ɂ��ύX
			if (m_pInputKeyboard->GetTrigger(DIK_2) == true)
			{
				m_nSampleObj_ViewType += 1;
				if (m_nSampleObj_ViewType > CModel::GetMaxCreateNum())
				{
					m_nSampleObj_ViewType = 0;
				}
			}
			if (m_pInputKeyboard->GetTrigger(DIK_1) == true)
			{
				m_nSampleObj_ViewType -= 1;
				if (m_nSampleObj_ViewType < 0)
				{
					m_nSampleObj_ViewType = CModel::GetMaxCreateNum();
				}
			}
		}
	}

	//+ @   @   @   @   @   @   @   @   @   @   @   @
	//+						���̓��[�h(�}�E�X��)
	//+ @   @   @   @   @   @   @   @   @   @   @   @
	if (m_pGame != NULL)
	{
		if (m_pGame->GetInputMode() == 1)
		{
			//�}�E�X�z�C�[���ɂ��ύX
			if (m_pInputMouse->GetWheel().lZ < 0)
			{
				m_nSampleObj_ViewType += 1;
				if (m_nSampleObj_ViewType > CModel::GetMaxCreateNum())
				{
					m_nSampleObj_ViewType = 0;
				}
			}
			if (m_pInputMouse->GetWheel().lZ > 0)
			{
				m_nSampleObj_ViewType -= 1;
				if (m_nSampleObj_ViewType < 0)
				{
					m_nSampleObj_ViewType = CModel::GetMaxCreateNum();
				}
			}
			

		}
	}
}

//==============================================
//�J�����̎��_���[�h�ɂ�鑀��̕ύX
//==============================================
void CPlayer::OperationManual(void)
{
	CCamera *pCamera = CGame::GetCamera();
	if (m_pGame != NULL)
	{
		if (m_pGame->GetInputMode() == 1)
		{
			if (pCamera != NULL)
			{
				if (pCamera->GetCameraMode() == 0)
				{
					//�ϊ����W�Ńv���C���[�𓮂���
					D3DXVECTOR3 pos;
					CGame::CalculationPoint(
						&pos,
						m_pInputMouse->GetPos().x,
						m_pInputMouse->GetPos().y,
						SCREEN_WIDTH,
						SCREEN_HEIGHT,
						&pCamera->GetMtxViex(),
						&pCamera->GetMtxProjection());

					m_pos.x = pos.x;
					m_pos.y = pos.y;
					if (m_pInputKeyboard->GetPress(DIK_W) == true)
					{
						m_pos.z += 4.0f;
					}
					else if (m_pInputKeyboard->GetPress(DIK_S) == true)
					{
						m_pos.z += -4.0f;
					}
				}
				if (pCamera->GetCameraMode() == 1)
				{
					//�ϊ����W�Ńv���C���[�𓮂���
					D3DXVECTOR3 pos;
					CGame::CalculationPoint(
						&pos,
						m_pInputMouse->GetPos().x,
						m_pInputMouse->GetPos().y,
						SCREEN_WIDTH,
						SCREEN_HEIGHT,
						&pCamera->GetMtxViex(),
						&pCamera->GetMtxProjection());

					m_pos.x = pos.x;
					m_pos.z = pos.z;
				}
			}
		}
	}
}
//==============================================
//�ړ�
//==============================================
void CPlayer::MOVE(void)
{
	if (m_pInputKeyboard->GetPress(DIK_W) == true)
	{
		m_pos.z += m_move.z;
	}

	if (m_pInputKeyboard->GetPress(DIK_S) == true)
	{
		m_pos.z -= m_move.z;
	}
	if (m_pInputKeyboard->GetPress(DIK_A) == true)
	{
		m_pos.x -= m_move.x;
	}

	if (m_pInputKeyboard->GetPress(DIK_D) == true)
	{
		m_pos.x += m_move.x;
	}

	if (m_pInputKeyboard->GetPress(DIK_E) == true)
	{
		m_pos.y += m_move.y;
	}

	if (m_pInputKeyboard->GetPress(DIK_Q) == true)
	{
		m_pos.y -= m_move.y;
	}

}

//==============================================
//�ʒu���̔��f
//==============================================
void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==============================================
//��]�����̔��f
//==============================================
void CPlayer::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//==============================================
//�\��obj���̔��f
//==============================================
void CPlayer::SetSampleObj(int num)
{
	m_nSampleObj_ViewType = num;
}

//==============================================
//���f���̓ǂݍ���
//==============================================
HRESULT CPlayer::ModelLoad(void)
{
	FILE *pFile;

	char * pStrCur;//�擪������̃|�C���^
	char aLine[256];//������̓ǂݍ���
	char aStr[256];//������̔����o��
	int nCnt = 0;

	//�e�L�X�g�̓ǂݍ��݁�
	pFile = fopen(OBJ_TEXT, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "OBJECT_LOAD", strlen("OBJECT_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					//�p�[�c���̓ǂݍ���
					if (memcmp(pStrCur, "NUM_OBJECT = ", strlen("NUM_OBJECT = ")) == 0)
					{
						pStrCur += strlen("NUM_OBJECT = ");
						strcpy(aStr, pStrCur);
						m_nNumModel = atoi(aStr);
					}

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

							strcpy(&m_aFileNameModel[nCnt][0], pStrCur);
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
//���f���̔j��
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
//���f���ɔ��f������摜�̓ǂݍ���
//==============================================
HRESULT CPlayer::TextureLoad(void)
{
	FILE *pFile;

	char * pStrCur;//�擪������̃|�C���^
	char aLine[256];//������̓ǂݍ���
	char aStr[256];//������̔����o��
	int nCnt = 0;

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

					//�p�[�c���̓ǂݍ���
					if (memcmp(pStrCur, "NUM_TEXTURE = ", strlen("NUM_TEXTURE = ")) == 0)
					{
						pStrCur += strlen("NUM_TEXTURE = ");
						strcpy(aStr, pStrCur);
						m_nNumTex = atoi(aStr);
					}

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

							strcpy(&m_aFileNameTex[nCnt][0], pStrCur);
						}

						nCnt += 1;
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
	for (int nCntLoad = 0; nCntLoad < m_nNumTex; nCntLoad++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aFileNameTex[nCntLoad], &m_pTexture[nCntLoad]);
	}

	return S_OK;
}

//==============================================
//���f���ɔ��f�������摜�̔j��
//==============================================
void CPlayer::TextureUnLoad(void)
{
	// �e�N�X�`���̔j��
	for (int nCntLoad = 0; nCntLoad < m_nNumTex; nCntLoad++)
	{

		if (m_pTexture[nCntLoad] != NULL)
		{
			m_pTexture[nCntLoad]->Release();
			m_pTexture[nCntLoad] = NULL;
		}
	}
}

//===================================================
//�e���f���̈ʒu�A�����A�e�����߂�
//===================================================
void CPlayer::ModelLode(void)
{
	//�ǂݍ��񂾃��f���������f���̐��A���f������
	for (int nCntLoad = 0; nCntLoad < m_nNumModel; nCntLoad++)
	{
		//�e�p�[�c�̏����ʒu�����߂遫
		m_pModel[nCntLoad] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		//�e�p�[�c�̃��f�������߂遫
		m_pModel[nCntLoad]->BindModel(m_pBuffMat[nCntLoad], m_pNumMat[nCntLoad], m_pMesh[nCntLoad]);
		//�e�p�[�c�̃��f�������߂遫
		m_pModel[nCntLoad]->BindTexture(m_pTexture[nCntLoad]);
		//�e�p�[�c�̐e�����߂遫
		//m_pModel[nCntLoad]->SetParent(m_pModel[nParent[nCntLoad]]);
	}
}

//==============================================
//�f�o�b�N�p����
//==============================================
void CPlayer::Debug(void)
{
	CDebug::DebugLog("\n�v���C���[��XXX�ʒu %f", m_pos.x);
	CDebug::DebugLog("\n�v���C���[��ZZZ�ʒu %f", m_pos.z);

}
