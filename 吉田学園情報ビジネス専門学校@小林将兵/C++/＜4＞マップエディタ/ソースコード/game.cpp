//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�Q�[������ [game.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "game.h"
#include "fade.h"
#include "debugLog.h"
#include "light.h"
#include "camera.h"
#include "scene2D.h"
#include "tutorial2DTex.h"
#include "scene3D.h"
#include "meshField.h"
#include "sceneX.h"
#include "object.h"
#include "player.h"

//=====================================================================
//�ÓI�����o�ϐ�
//=====================================================================
CDebug *CGame::m_pDebug = NULL;
CLight *CGame::m_pLight = NULL;
CCamera *CGame::m_pCamera = NULL;
CScene2D *CGame::m_pScene2D = NULL;
CScene3D *CGame::m_pScene3D = NULL;
CMeshField *CGame::m_pMeshField = NULL;
CSceneX *CGame::m_pSceneX = NULL;
CObject *CGame::m_pObject[OBJ_CREATE] = {};
CPlayer *CGame::m_pPlayer = NULL;

//==============================================
//�R���X�g���N�^
//==============================================
CGame::CGame()
{
	m_nCreateCnt = 0;
}

//==============================================
//�f�X�g���N�^
//==============================================
CGame::~CGame()
{

}

//==============================================
//����
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
//������
//==============================================
HRESULT CGame::Init(void)
{
	m_nCreateCnt = 0;
	m_nInputMode = 0;
	NullCheck();		//�g�p����f�[�^����xNULL�ɂ���
	CTutorial2DTex::TextureLoad();
	CObject::ObjectLoad();
	CObject::TextureLoad();
	CPlayer::ModelLoad();
	CPlayer::TextureLoad();
	CreateData();		//�K�v�E�g�pobj�̐���

	return S_OK;
}
//==============================================
//�I��
//==============================================
void CGame::Uninit(void)
{
	CPlayer::TextureLoad();
	CPlayer::ModelUnLoad();
	CObject::TextureUnLoad();
	CObject::ObjectUnLoad();
	CTutorial2DTex::TextureUnLoad();


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
//�X�V
//==============================================
void CGame::Update(void)
{
	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	m_pInputMouse = CManager::GetInputMouse();

	//��ʑJ�ڏ���
	m_pFade = CFade::GetFade();
	//
	if (m_pLight != NULL)//���C�g
	{
		m_pLight->Update();		
	}
	if (m_pCamera != NULL)//�J����
	{
		m_pCamera->Update();	
	}

	ObjCreate();//�{�^�������ɂ��obj�́w�����x

	ObjDelete();//�{�^�������ɂ��obj�́w�폜�x

	Save();		//�{�^�������ɂ��obj���́w�ۑ��x

	if (m_pInputKeyboard->GetTrigger(DIK_F2) == true)
	{
		m_nInputMode += 1;
		if (m_nInputMode >= 2)
		{
			m_nInputMode = 0;
		}
	}

	/*switch (m_nInputMode)
	{
	case 0:

	case 1:

	case 2:
	}*/

	Debug();	//�f�o�b�N����p
}

//==============================================
//�`��
//==============================================
void CGame::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();//��ʂ̕`��ɕK�v
	}

}
//==============================================
//����������NULL����
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
		m_pScene2D = NULL;	//�V�[��2D
	}

	if (m_pScene3D != NULL)
	{
		m_pScene3D = NULL;	//�V�[��3D
	}

	if (m_pMeshField != NULL)
	{
		m_pMeshField = NULL;//���b�V���t�B�[���h
	}


	//if (m_pSceneX != NULL)
	//{
	//	m_pSceneX = NULL;	//�V�[��X
	//}

	for (int nCnt = 0; nCnt < OBJ_CREATE; nCnt++)
	{
		if (m_pObject[nCnt] != NULL)
		{
			m_pObject[nCnt] = NULL;	//�I�u�W�F�N�g
		}
	}
	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;	//�v���C���[
	}
}
//==============================================
//�g�p����f�ނ̐���
//==============================================
void CGame::CreateData(void)
{
	if (m_pDebug == NULL)
	{
		m_pDebug = CDebug::Create();		//�f�o�b�N
	}
	if (m_pLight == NULL)
	{
		m_pLight = CLight::Create();		//���C�g
	}
	if (m_pCamera == NULL)
	{
		m_pCamera = CCamera::Create();		//�J����
	}

	//if (m_pScene2D == NULL)
	//{
	//	m_pScene2D = CScene2D::Create();	//�V�[��2D
	//}

	//CTutorial2DTex::Create(0, D3DXVECTOR3(900.0f,50.0f,0.0f),500.0f,50.0f);
	//CTutorial2DTex::Create(1, D3DXVECTOR3(130.0f, 400.0f, 0.0f), 90.0f, 55.0f);

	if (m_pScene3D == NULL)
	{
		//m_pScene3D = CScene3D::Create();	//�V�[��3D
	}

	if (m_pMeshField == NULL)//���b�V���t�B�[���h
	{
		CMeshField::Create(0, CMeshField::XZ, D3DXVECTOR3(-300.0f, 0.0f, 200.0f), 50, 200, 10);
		CMeshField::Create(1, CMeshField::XY, D3DXVECTOR3(-300.0f, 200.0f, 200.0f), 50, 200, 4);
	}


	//if (m_pSceneX == NULL)
	//{
	//	m_pSceneX = CSceneX::Create();	//�V�[��X
	//}

	//�I�u�W�F�N�g
	//m_pObject[0] = CObject::Create(CObject::OBJ_TYPE01, D3DXVECTOR3(-50.0f, 30.0f, 0.0f));
	//m_pObject[1] = CObject::Create(CObject::OBJ_TYPE01, D3DXVECTOR3(100.0f, 30.0f, 0.0f));

	if (m_pPlayer == NULL)//�v���C���[
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//==============================================
//�{�^�������ɂ��obj�̐���
//==============================================
void  CGame::ObjCreate(void)
{
	if (m_nInputMode == 0)//���̓��[�h(�L�[�{�[�h��)
	{
		if (m_pInputKeyboard->GetTrigger(DIK_SPACE) == true)
		{
			int nObjType = m_pPlayer->GetSampleObjType();	//�T���v���Ɠ���OBJ�𐶐�����obj�̎��
			D3DXVECTOR3 pos = m_pPlayer->GetPos();		//��������ꏊ
			D3DXVECTOR3 rot = m_pPlayer->GetRot();
			m_pObject[m_nCreateCnt] = CObject::Create(nObjType, D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(rot.x, rot.y, rot.z));
			m_nCreateCnt += 1;
		}
	}

	if (m_nInputMode == 1)//���̓��[�h(�}�E�X��)
	{
		if (m_pInputMouse->GetTrigger(0) == true)
		{
			int nObjType = m_pPlayer->GetSampleObjType();	//�T���v���Ɠ���OBJ�𐶐�����obj�̎��
			D3DXVECTOR3 pos = m_pPlayer->GetPos();		//��������ꏊ
			D3DXVECTOR3 rot = m_pPlayer->GetRot();
			m_pObject[m_nCreateCnt] = CObject::Create(nObjType, D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(rot.x, rot.y, rot.z));
			m_nCreateCnt += 1;

		}
	}
}

//==============================================
//�{�^�������ɂ��obj�̍폜
//==============================================
void CGame::ObjDelete()
{
	if (m_pInputKeyboard->GetTrigger(DIK_BACK) == true)
	{
		m_nCreateCnt -= 1;
		if (m_nCreateCnt < 0)
		{
			m_nCreateCnt = 0;
		}
		if (m_pObject[m_nCreateCnt] != NULL)
		{
			m_pObject[m_nCreateCnt]->Uninit();
			m_pObject[m_nCreateCnt] = NULL;
		}
	}
}
//==============================================
//obj���̕ۑ��E�����o��
//==============================================
void  CGame::Save(void)
{
	FILE *pFile;
	
	if (m_pInputKeyboard->GetTrigger(DIK_F5) == true)
	{
		pFile = fopen("DATA\\TEXT\\OBJ_OUTPUT.txt", "w");

		if (pFile != NULL)
		{
			fprintf(pFile, "OBJ_CREATE_LOAD");
			fprintf(pFile, "\n\nMAX_OBJ_CREATE = %d", CObject::GetCreateNum());
			for (int nCnt = 0; nCnt <= CObject::GetCreateNum() - 1; nCnt++)
			{
				fprintf(pFile, "\n\nOBJ_SET");
				fprintf(pFile, "\n\tOBJ_TYPE = %d", m_pObject[nCnt]->GetSaveObjType());
				fprintf(pFile, "\n\tTEX_TYPE = %d", m_pObject[nCnt]->GetSaveObjType());
				fprintf(pFile, "\n\tPOS = %.1f %.1f %.1f", m_pObject[nCnt]->GetPos().x, m_pObject[nCnt]->GetPos().y, m_pObject[nCnt]->GetPos().z);
				fprintf(pFile, "\n\tROT = %.1f %.1f %.1f", m_pObject[nCnt]->GetRot().x, m_pObject[nCnt]->GetRot().y, m_pObject[nCnt]->GetRot().z);
				fprintf(pFile, "\nOBJ_SET_END");
			}
			fprintf(pFile, "\n\nOBJ_CREATE_LOAD_END");
		}
	}
}

//==============================================
//		�X�N���[�����W�����[���h���W�ɕϊ�
//==============================================
D3DXVECTOR3* CGame::ScreenToWorld
(D3DXVECTOR3* pout,
	int nScreenPosX,
	int nScreenPosY,
	float fProjectionSpace_Z,//�ˉe��Ԃ�Z�����߂�
	int ScreenWide,
	int ScreenHeight,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj)
{
	// �e�s��̋t�s����Z�o
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, View);
	D3DXMatrixInverse(&InvPrj, NULL, Prj);
	D3DXMatrixIdentity(&VP);
	VP._11 = ScreenWide / 2.0f; VP._22 = -ScreenHeight / 2.0f; 
	VP._41 = ScreenWide / 2.0f; VP._42 = ScreenHeight / 2.0f; 
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// �t�ϊ�
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(pout, &D3DXVECTOR3((float)nScreenPosX, (float)nScreenPosY, fProjectionSpace_Z), &tmp);

	return pout;
}

//==============================================
//	�X�N���[�����W��XZ���ʂ̃��[���h���W����_�Z�o
//==============================================
D3DXVECTOR3* CGame::CalculationPoint
(D3DXVECTOR3* pout,
	int nScreenPosX,
	int nScreenPosY,
	int ScreenWide,
	int ScreenHeight,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj)
{
	D3DXVECTOR3 nearPoint;	//�߂�����������
	D3DXVECTOR3 farPoint;	//��������������
	D3DXVECTOR3 ray;		//���[���h��̕��ʂɓ��Ă����

	//�X�N���[�����W�����ƌ�������
	ScreenToWorld(&nearPoint, nScreenPosX, nScreenPosY, 0.0f, ScreenWide, ScreenHeight, View, Prj);
	//�X�N���[�����W�����ƌ������Ȃ�
	ScreenToWorld(&farPoint, nScreenPosX, nScreenPosY, 1.0f, ScreenWide, ScreenHeight, View, Prj);

	//�����̒l���Z�o�E���K��
	ray = farPoint - nearPoint;
	D3DXVec3Normalize(&ray, &ray);

	//������ӂ̓T�C�g�����p��
	CInputKeyboard *m_pInputKeyboard = CManager::GetInputKeyboard();
	CCamera *pCamera = CGame::GetCamera();
	if (pCamera != NULL)
	{
		if (pCamera->GetCameraMode() == 0)
		{
			if (ray.z <= 1) //���ƌ�������
			{
				// ����_
				float Lray = D3DXVec3Dot(&ray, &D3DXVECTOR3(0, 0, 1));
				float LP0 = D3DXVec3Dot(&(-nearPoint), &D3DXVECTOR3(0, 0, 1));
				CDebug::DebugLog("\nLray%f", Lray);
				CDebug::DebugLog("\nLP0%f", LP0);

				//*pout = nearPoint + (LP0 / Lray)*ray;
				CDebug::DebugLog("\npout->�@X%f Y%f Z%f", pout->x, pout->y, pout->z);

				pout->x = (nearPoint.x + (LP0 / Lray)*ray.x);
				pout->y = (nearPoint.y + (LP0 / Lray)*ray.y);
				pout->z = (nearPoint.z + (LP0 / Lray)*ray.z);

				CDebug::DebugLog("\n�ŏIpout->�@X%f Y%f Z%f", pout->x, pout->y, pout->z);
			}
			else //���ƌ������Ȃ�
			{
				*pout = farPoint;

			}

		}

		if (pCamera->GetCameraMode() == 1)
		{

			if (ray.y <= 0) //���ƌ�������
			{
				// ����_
				float Lray = D3DXVec3Dot(&ray, &D3DXVECTOR3(0, 1, 0));
				float LP0 = D3DXVec3Dot(&(-nearPoint), &D3DXVECTOR3(0, 1, 0));
				*pout = nearPoint + (LP0 / Lray)*ray;
			}
			else //���ƌ������Ȃ�
			{
				*pout = farPoint;
			}
		}
		
	}	
	return pout;
}


//==============================================
//�f�o�b�N�p����
//==============================================
void  CGame::Debug(void)
{
	CDebug::DebugLog("\n���݂̐����� %d", m_nCreateCnt);
}





