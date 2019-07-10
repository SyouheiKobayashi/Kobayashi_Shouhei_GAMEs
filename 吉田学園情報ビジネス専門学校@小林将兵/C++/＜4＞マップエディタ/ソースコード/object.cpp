//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�I�u�W�F�N�g�������� [object.cpp]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "debugLog.h"
#include "input.h"
#include "sceneX.h"
#include "object.h"
#include "game.h"

//=====================================================================
//�ÓI�����o�ϐ�
//=====================================================================
//�e�L�X�g�ǂݍ��݊֘A
int CObject::m_nNumObject = NULL;
int CObject::m_nNumTexture = NULL;
char CObject::m_aFileNameObject[MAX_OBJECT][256] = {};
char CObject::m_aFileNameTexture[MAX_OBJECT][256] = {};
//���f�����
int CObject::m_objType = 0;
LPD3DXMESH CObject::m_pMesh[MAX_OBJECT] = {};
LPD3DXBUFFER CObject::m_pBuffMat[MAX_OBJECT] = {};
DWORD CObject::m_pNumMat[MAX_OBJECT] = {};
//�摜�֘A
LPDIRECT3DTEXTURE9 CObject::m_pTexture[OBJ_TEXTURE_NUM] = {};

int CObject::m_nCreateNum = 0;//�������ꂽ���̋L��

//==============================================
//�R���X�g���N�^
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
	
}
//==============================================
//�f�X�g���N�^
//==============================================
CObject::~CObject()
{

}

//==============================================
//����
//==============================================
CObject *CObject::Create(int nObjType, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_nCreateNum += 1;
	CObject *pObject = NULL;
	if (pObject == NULL)
	{
		pObject = new CObject;
		m_objType = nObjType;
		pObject->BindObject(m_pBuffMat[nObjType], m_pNumMat[nObjType], m_pMesh[nObjType]);	//�g�p����I�u�W�F�N�g
		pObject->BindTexture(m_pTexture[nObjType]);							//�g�p����摜
		pObject->Init();
		pObject->SetPos(pos);					//�ʒu�̔��f
		pObject->SetRot(rot);
		pObject->SaveObjType(nObjType);
	}
	return pObject;
}
//==============================================
//����������
//==============================================
HRESULT CObject::Init(void)
{
	CSceneX::Init();

	m_VtxMin = GetVtxMin();
	m_VtxMax = GetVtxMax();


	return S_OK;
}

//==============================================
//�I������
//==============================================
void CObject::Uninit(void)
{
	m_nCreateNum -= 1;
	CSceneX::Uninit();
}

//==============================================
//�X�V����
//==============================================
void CObject::Update(void)
{
	CSceneX::Update();
	
	Debug();
	
}

//==============================================
//�`�揈��
//==============================================
void CObject::Draw(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//pDevice->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE);

	CSceneX::Draw();

	//pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);


}

//==============================================
//�����蔻�菈��
//==============================================
bool CObject::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	D3DXVECTOR3 pos = GetPos();

	//�㔻��
	if (pos.x + m_VtxMin.x < pPos->x + OBJ_X &&
		pos.x + m_VtxMax.x > pPos->x - OBJ_X &&
		pos.z + m_VtxMin.z < pPos->z + OBJ_Z &&
		pos.z + m_VtxMax.z > pPos->z - OBJ_Z)
	{
		if (pos.y + m_VtxMax.y <= pPosOld->y + OBJ_Y &&
			pos.y + m_VtxMax.y > pPos->y - OBJ_Y)
		{
			//pPos->y = (pos.y + m_VtxMax.y) + OBJ_Y;
		}
	}

	//�O�㔻��
	if (m_VtxMax.y + pos.y > pPos->y + OBJ_Y&&
		m_VtxMin.y - pos.y <= pPos->y + OBJ_Y)
	{
		if (pos.x + m_VtxMin.x < pPos->x + OBJ_X &&
			pos.x + m_VtxMax.x > pPos->x - OBJ_X)
		{
			//��O�̔���
			if (pos.z + m_VtxMin.z >= pPosOld->z + OBJ_Z&&
				pos.z + m_VtxMin.z < pPos->z + OBJ_Z)
			{
				pPos->z = pos.z + m_VtxMin.z - OBJ_Z;
			}
			//���̔���
			else if (pos.z + m_VtxMax.z <= pPosOld->z - OBJ_Z&&
				pos.z + m_VtxMax.z > pPos->z - OBJ_Z)
			{
				pPos->z = pos.z + m_VtxMax.z + OBJ_Z;
			}
		}

		//���E����
		if (pos.z + m_VtxMin.z < pPos->z + OBJ_Z &&
			pos.z + m_VtxMax.z > pPos->z - OBJ_Z)
		{
			//���̔���
			if (pos.x + m_VtxMin.x >= pPosOld->x + OBJ_X&&
				pos.x + m_VtxMin.x < pPos->x + OBJ_X)
			{
				pPos->x = pos.x + m_VtxMin.x - OBJ_X;
				/*pPos->x -= 40.0f;
				pPos->y += 10.0f;*/

			}
			//�E�̔���
			else if (pos.x + m_VtxMax.x <= pPosOld->x - OBJ_X&&
				pos.x + m_VtxMax.x > pPos->x - OBJ_X)
			{
				pPos->x = pos.x + m_VtxMax.x + OBJ_X;
			}
		}
	}

	return 0;
}

//==============================================
//�g�p����I�u�W�F�N�g�̓ǂݍ���
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
//�g�p�����I�u�W�F�N�g�̔j��
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
//�I�u�W�F�N�g�ɔ��f������摜�̓ǂݍ���
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
//�I�u�W�F�N�g�ɔ��f�������摜�̔j��
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
//�f�o�b�N
//==============================================
void CObject::Debug(void)
{

}

