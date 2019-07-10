//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�V�[������ [scene.cpp]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "scene.h"
#include "renderer.h"
#include "debugLog.h"

//!�ÓI����
int CScene::m_NumALL = 0;
int CScene::m_nNumPriority[DRAW_MAX] = {};
CScene *CScene::m_pTop[DRAW_MAX] = {};
CScene *CScene::m_pCur[DRAW_MAX] = {};
//? ==============================================
//?+ �R���X�g���N�^
//? ==============================================
CScene::CScene(int nPriority, DATA_TYPE nObjType)
{
	m_nPriority = nPriority;
	m_DataType = nObjType;
	m_bDeath = false;

	if (m_pTop[nPriority] == NULL)
	{
		m_pTop[nPriority] = this;//�擪�f�[�^�̐���

	}
	if (m_pCur[nPriority] != NULL)
	{
		m_pCur[nPriority]->m_pNext = this;//���݂̍Ō���̃f�[�^��莟�ɐV�����f�[�^����

	}

	this->m_pPrev = m_pCur[nPriority];//�J�����g���g�Ȃ�&&NULL
	this->m_pNext = NULL;
	m_pCur[nPriority] = this;//scene��������

	m_nNumPriority[m_nPriority]++;

	m_NumALL++;//�������ꂽobj�̑����𑝂₷
}

//? ==============================================
//?+ �f�X�g���N�^
//? ==============================================
CScene::~CScene()
{

}

//? ==============================================
//?+ �I���E�S�f�[�^�������
//? ==============================================
void CScene::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < DRAW_MAX; nCnt++)
	{
		CScene *pTop, *pNext;
		pNext = m_pTop[nCnt];

		while (pNext != NULL)//NULL�ɂȂ�܂�
		{
			pTop = pNext;
			pNext = pTop->m_pNext;
			pTop->Uninit();
		}

		//! ------------------------------------------------
		//!+ ���S�t���O�Ώ�obj�̍폜
		//! ------------------------------------------------
		CScene *pSceneTop;
		pSceneTop = m_pTop[nCnt];
		while (pSceneTop != NULL)//NULL�ɂȂ�܂�
		{
			CScene *pSceneNext;
			pSceneNext = pSceneTop->m_pNext;//���̋L��
			if (pSceneTop->m_bDeath == true)//���S�t���O��true�Ȃ�...
			{
				pSceneTop->Delete();
			}
			pSceneTop = pSceneNext;
		}

		m_pTop[nCnt] = NULL;
		m_pCur[nCnt] = NULL;
	}
	m_NumALL = 0;//�������ꂽobj�̑�����0��...
}

//? ==============================================
//?+ �X�V����
//? ==============================================
void CScene::UpdateAll()
{	
	for (int nCnt = 0; nCnt < DRAW_MAX; nCnt++)
	{


		CScene *pSceneTop;
		pSceneTop = m_pTop[nCnt];

		while (pSceneTop != NULL)//NULL�ɂȂ�܂�
		{
			CScene *pSceneNext;
			pSceneNext = pSceneTop->m_pNext;//��<�L������ID�̕��@�Ǝ��Ă���> && ��񂪏����Ȃ��悤��...
			pSceneTop->Update();
 			pSceneTop = pSceneNext;
		}
	}
		//! ------------------------------------------------
		//!+ ���S�t���O�Ώ�obj�̍폜
		//! ------------------------------------------------
	for (int nCnt = 0; nCnt < DRAW_MAX; nCnt++)
	{
		CScene *pSceneTop;
		pSceneTop = m_pTop[nCnt];
		while (pSceneTop != NULL)//NULL�ɂȂ�܂�
		{
			CScene *pSceneNext;
			pSceneNext = pSceneTop->m_pNext;//���̋L��
			if (pSceneTop->m_bDeath == true)//���S�t���O��true�Ȃ�...
			{
				pSceneTop->Delete();
			}
			pSceneTop = pSceneNext;
		}
	}
}

//? ==============================================
//?+ �`�揈��
//? ==============================================
void CScene::DrawAll()
{
	for (int nCnt = 0; nCnt < DRAW_MAX; nCnt++)
	{
		CScene *pSceneTop;
		pSceneTop = m_pTop[nCnt];

		while (pSceneTop != NULL)//NULL�ɂȂ�܂�
		{
			CScene *pSceneNext;
			pSceneNext = pSceneTop->m_pNext;//��<�L������ID�̕��@�Ǝ��Ă���> && ��񂪏����Ȃ��悤��...
			pSceneTop->Draw();
			pSceneTop = pSceneNext;
		}
	}
}
//? ==============================================
//?+ ���S�t���O�����Ă�
//? ==============================================
void CScene::Release(void)
{
	m_bDeath = true;
}

//? ==============================================
//?+ ���S�t���O�������Ă���Ώ�obj�̍폜
//? ==============================================
void  CScene::Delete(void)
{
		if (m_pPrev != NULL)//top��cur�̊Ԃ������ꍇ...
		{
			m_pPrev->m_pNext = m_pNext;
		}
		if (m_pNext != NULL)//top��cur�̊Ԃ������ꍇ...
		{
			m_pNext->m_pPrev = m_pPrev;
		}
		if (this == m_pTop[m_nPriority])	//top�������ꍇ...
		{
			m_pTop[m_nPriority] = m_pTop[m_nPriority]->m_pNext;
		}

		if (this == m_pCur[m_nPriority])//cur�������ꍇ...
		{
			m_pCur[m_nPriority] = m_pCur[m_nPriority]->m_pPrev;
		}

		m_nNumPriority[m_nPriority]--;
	delete this;//�����𖞂�������Ɏ��g������

	

	m_NumALL--;//�������ꂽobj�̑��������炷
}

//? ==============================================
//?+ ���S�t���O�������Ă���Ώ�obj�̍폜
//? ==============================================
void CScene::SetDataType(DATA_TYPE dataType)//
{
	m_DataType = dataType;//����������obj�̏����擾����
}
