//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//							�^�C�g������ [title.h]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "title.h"
#include "fade.h"
#include "debugLog.h"
#include "sound.h"
#include "light.h"
#include "camera.h"
#include "scene2D.h"
#include "polygon2D.h"
#include "scene3D.h"
#include "meshField.h"
#include "polygon3D.h"
#include "particle.h"
#include "object.h"
#include "player.h"
#include "enemy.h"
//=====================================================================
//							�ÓI�����o�ϐ�
//=====================================================================
CDebug *CTitle::m_pDebug = NULL;
CSound *CTitle::m_pSound = NULL;
CLight *CTitle::m_pLight = NULL;
CCamera *CTitle::m_pCamera = NULL;
CScene2D *CTitle::m_pScene2D = NULL;
CPolygon2D *CTitle::m_pPolygon2D = NULL;
CScene3D *CTitle::m_pScene3D = NULL;
CMeshField *CTitle::m_pMeshField = NULL;
CPolygon3D *CTitle::m_pPolygon3D = NULL;
CParticle3D *CTitle::m_pParticle3D = NULL;
CObject *CTitle::m_pObject[OBJ_CREATE] = {};
CPlayer *CTitle::m_pPlayer = NULL;
CEnemy *CTitle::m_pEnemy = NULL;

//==============================================
//					�R���X�g���N�^
//==============================================
CTitle::CTitle()
{

}

//==============================================
//					�f�X�g���N�^
//==============================================
CTitle::~CTitle()
{

}

//==============================================
//						����
//==============================================
CTitle *CTitle::Create()
{
	CTitle *pTitle = NULL;

	if (pTitle == NULL)
	{
		pTitle = new CTitle;
		pTitle->Init();
	}

	return pTitle;
}
//==============================================
//					������
//==============================================
HRESULT CTitle::Init(void)
{
	m_nDebugCnt = 0;
	m_bFadeCheck = false;
	m_nFadeStartTime = 0;
	NullCheck();				//�g�p����f�[�^����xNULL�ɂ���
	BulkLoadData();				//�g�p�������f���ƃe�N�X�`���̉��
	MAP_LOAD();					//�}�b�v���̓ǂݍ���
	CreateData();				//�ǂݍ��񂾏������Ƃ�obj�̐���
	m_pCamera->SetV(D3DXVECTOR3(150.0f, 140.0f, -220.0f));	//�����_����̋���
	m_pCamera->SetR(D3DXVECTOR3(150.0f, 120.0f, 0.0f));	//�����_�̈ʒu

	m_pSound = CManager::GetSound();
	if (m_pSound != NULL)
	{
		m_pSound->PlaySound(CSound::BGM_SOUND_TITLE);
	}
	return S_OK;
}
//==============================================
//						�I��
//==============================================
void CTitle::Uninit(void)
{
	if (m_pSound != NULL)
	{
		m_pSound->StopSound();
	}
	BulkUnLoadData();			//�g�p�������f���ƃe�N�X�`���̉��

	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();	//�J����
	}
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();		//���C�g
	}
	if (m_pDebug != NULL)
	{
		m_pDebug->Uninit();		//�f�o�b�N
	}

	//�g�p�����f�[�^�E�����������ׂĊJ��
	CScene::ReleaseAll();
}
//==============================================
//					�X�V
//==============================================
void CTitle::Update(void)
{
	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	
	m_pFade = CFade::GetFade();	//�t�F�[�h

	if (m_pLight != NULL)
	{
		m_pLight->Update();		//���C�g
	}
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();	//�J����
	}

	m_pPolygon2D->FlashTex();

	//��ʑJ��
	if (m_pInputKeyboard->GetTrigger(DIK_RETURN) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_START, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
	{
		if (m_bFadeCheck == false && m_pSound != NULL)
		{
			m_pSound->PlaySound(CSound::SE_BUTTON);
		}
		m_bFadeCheck = true;
			
	}
	if (m_bFadeCheck == true)//�J�ڎ��Ԃ������x�点��
	{
		m_nFadeStartTime++;

		if (m_pFade == CFade::FADE_NONE&&m_nFadeStartTime >= 80)
		{
			
			CManager::GetFade()->SetFade(CManager::MODE_CHARGETIME);
		}
	}

#ifdef _DEBUG
	DebugLoop();					//�f�o�b�N����p
#endif

}

//==============================================
//					�`��
//==============================================
void CTitle::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();//�J�����`��
	}

}
//==============================================
//				NULL�`�F�b�N
//==============================================
void CTitle::NullCheck(void)
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

	if (m_pPolygon2D != NULL)
	{
		m_pPolygon2D = NULL;	//�|���S��2D
	}

	if (m_pScene3D != NULL)
	{
		m_pScene3D = NULL;		//�V�[��3D
	}

	if (m_pMeshField != NULL)
	{
		m_pMeshField = NULL;	//���b�V���t�B�[���h
	}

	if (m_pPolygon3D != NULL)
	{
		m_pPolygon3D = NULL;	//�|���S��3D
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
	if (m_pEnemy != NULL)
	{
		m_pEnemy = NULL;		//�G�l�~�[
	}

}

//==============================================
//				�@Load����(�ǂݍ���)
//==============================================
void CTitle::BulkLoadData(void)
{
	CPolygon2D::TextureLoad();
	CPolygon3D::TextureLoad();
	CParticle3D::TextureLoad();
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
void CTitle::BulkUnLoadData(void)
{
	CEnemy::TextureUnLoad();
	CEnemy::ModelUnLoad();
	CPlayer::TextureUnLoad();
	CPlayer::ModelUnLoad();
	CObject::TextureUnLoad();
	CObject::ObjectUnLoad();
	CParticle3D::TextureUnLoad();
	CPolygon3D::TextureUnLoad();
	CPolygon2D::TextureUnLoad();
}

//==============================================
//					��������
//==============================================
void CTitle::CreateData(void)
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

	if (m_pPolygon2D == NULL)//2D�e�N�X�`��
	{
		CPolygon2D::Create(0, false,D3DXVECTOR3(640.0f, 210.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350.0f, 200.0f,1,1,1,true);
		CPolygon2D::Create(1, true, D3DXVECTOR3(450.0f, 180.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80.0f, 80.0f, 1, 1, 1, true);
		CPolygon2D::Create(2, true, D3DXVECTOR3(580.0f, 150.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80.0f, 80.0f, 1, 1, 1, true);
		CPolygon2D::Create(3, true, D3DXVECTOR3(710.0f, 180.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80.0f, 80.0f, 1, 1, 1, true);
		CPolygon2D::Create(4, true, D3DXVECTOR3(840.0f, 150.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80.0f, 80.0f, 1, 1, 1, true);
		CPolygon2D::Create(5, false,D3DXVECTOR3(640.0f, 160.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 280.0f, 160.0f, 1, 1, 1, true);
		m_pPolygon2D = CPolygon2D::Create(24, false, D3DXVECTOR3(640.0f, 600.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200.0f, 40.0f, 1, 1, 1, true);

	}

	if (m_pPolygon3D == NULL)//3D�e�N�X�`��
	{
		CPolygon3D::Create(4, D3DXVECTOR3(50.0f, 140.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(4, D3DXVECTOR3(450.0f, 140.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(4, D3DXVECTOR3(850.0f, 140.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(4, D3DXVECTOR3(1250.0f, 140.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(4, D3DXVECTOR3(-100.0f, 140.0f, 150.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(4, D3DXVECTOR3(875.0f, 140.0f, 875.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);

	}

	//�I�u�W�F�N�g
	for (int nCnt = 0; nCnt < m_nMaxObjCreateNum; nCnt++)
	{
		m_pObject[nCnt] = CObject::Create(m_nObjType[nCnt], m_nTexType[nCnt],
			D3DXVECTOR3(m_ObjOffseet[nCnt].fPosX, m_ObjOffseet[nCnt].fPosY, m_ObjOffseet[nCnt].fPosZ),
			D3DXVECTOR3(m_ObjOffseet[nCnt].fRotX, m_ObjOffseet[nCnt].fRotY, m_ObjOffseet[nCnt].fRotZ));
	}

	if (m_pPlayer == NULL)//�v���C���[
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(-90.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	if (m_pEnemy == NULL)//�G�l�~�[
	{
		m_pEnemy = CEnemy::Create(0, D3DXVECTOR3(-130.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//==============================================
//				�f�o�b�N�p����
//==============================================
void  CTitle::DebugLoop(void)
{
	m_nDebugCnt++;
	if (m_nDebugCnt >= 50)
	{
		if (m_pFade == CFade::FADE_NONE)
		{
			CManager::GetFade()->SetFade(CManager::MODE_CHARGETIME);
		}
	}
}

//==============================================
//		�O���f�[�^����}�b�v���̓ǂݍ���
//==============================================
void CTitle::MAP_LOAD(void)
{
	FILE *pFile;
	char * pStrCur;	//�擪������̃|�C���^
	char aLine[256];//������̓ǂݍ���
	char aStr[256];	//������̔����o��
	int nCnt = 0;
	int nWord;

	//�O���e�L�X�g�̓ǂݍ���
	pFile = fopen("DATA\\TEXT\\TITLE.txt", "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "OBJ_CREATE_LOAD", strlen("OBJ_CREATE_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
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
							fgets(&aLine[0], 256, pFile);
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
	fclose(pFile);
}




