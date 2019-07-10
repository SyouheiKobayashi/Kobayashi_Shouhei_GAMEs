//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �I�u�W�F�N�g���� [scene.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "scene.h"
#include "renderer.h"
//#include "scene2D.h"


//! �ÓI����
CScene *CScene::m_apScene[OBJ_DRAW::DRAW_ALL][MAX_SCENE] = {};
int CScene::m_NumALL = 0;
//=============================================================================
//+ �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CScene::CScene()
{
	
}

//=============================================================================
//+ �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority = 3)
{
	for (int nCntS = 0; nCntS < MAX_SCENE; nCntS++)
	{
			if (m_apScene[nPriority][nCntS] == NULL)
			{
				m_apScene[nPriority][nCntS] = this;//cSnene2D���͂���
				m_nID = nCntS;//�������g�̔ԍ����o��������
				m_nPriority = nPriority;
				m_NumALL++;
				break;
			}
	}
}

//=============================================================================
//+ �I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
//+ �I�u�W�F�N�g�̏I���E�f�[�^�������
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntP = 0; nCntP < OBJ_DRAW::DRAW_ALL; nCntP++)
	{
		for (int nCntS = 0; nCntS < MAX_SCENE; nCntS++)
		{
			if (m_apScene[nCntP][nCntS] != NULL)//��������̏�񂪓����Ă����ꍇ
			{
				m_apScene[nCntP][nCntS]->Uninit();

				delete m_apScene[nCntP][nCntS];//���̏����̂Ă�
				m_apScene[nCntP][nCntS] = NULL;//NULL�ɖ߂�
			}
		}
	}
}
//=============================================================================
//+ �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CScene::UpdateAll()
{
	for (int nCntP = 0; nCntP < OBJ_DRAW::DRAW_ALL; nCntP++)
	{
		for (int nCntS = 0; nCntS < MAX_SCENE; nCntS++)
		{
			if (m_apScene[nCntP][nCntS] != NULL)//��񂪓����Ă���Ȃ�
			{
				m_apScene[nCntP][nCntS]->Update();
			}
		}
	}
}

void CScene::UpdateAll(OBJ_DRAW DrowType)
{

	for (int nCntS = 0; nCntS < MAX_SCENE; nCntS++)
	{
		if (m_apScene[DrowType][nCntS] != NULL)//��񂪓����Ă���Ȃ�
		{
			m_apScene[DrowType][nCntS]->Update();
		}
	}

}
//=============================================================================
//+ �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CScene::DrawAll()
{
	for (int nCntP = 0; nCntP < OBJ_DRAW::DRAW_ALL; nCntP++)
	{
		for (int nCntS = 0; nCntS < MAX_SCENE; nCntS++)
		{
			if (m_apScene[nCntP][nCntS] != NULL)//��񂪓����Ă���Ȃ�
			{
				m_apScene[nCntP][nCntS]->Draw();
			}
		}
	}
}
//=============================================================================
//+ �I�u�W�F�N�g��delete����
//=============================================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)//��񂪓����Ă���Ȃ�
	{
		int nID;//m_nID�̏����o�������Ă���(delete�����u��m_nID�̏�񂪎����邽��)
		nID = m_nID;

		int nPriority;//�D�揇�ʂ̋L��(delete�����u��m_nPriority�̏�񂪎����邽��)
		nPriority = m_nPriority;

		//delete������
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_NumALL--;
	}
}

//=============================================================================
//+ obj��Set����
//=============================================================================
void CScene::SetObjType(OBJ_TYPE ObjType)//
{
	m_ObjType= ObjType;//����������obj�̏����擾����
}




