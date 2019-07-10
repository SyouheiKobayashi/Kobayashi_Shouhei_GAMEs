//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//							�^�C�g������ [title.h]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "timeCharge.h"
#include "fade.h"
#include "debugLog.h"
#include "sound.h"
#include "light.h"
#include "camera.h"
#include "scene2D.h"
#include "polygon2D.h"
#include "scene3D.h"
#include "meshField.h"
//#include "billboard.h"
#include "polygon3D.h"
#include "particle.h"
#include "number.h"
#include "time.h"
#include "object.h"
#include "player.h"

//=====================================================================
//							�ÓI�����o�ϐ�
//=====================================================================
CDebug *CTimeCharge::m_pDebug = NULL;
CSound *CTimeCharge::m_pSound = NULL;
CLight *CTimeCharge::m_pLight = NULL;
CCamera *CTimeCharge::m_pCamera = NULL;
CScene2D *CTimeCharge::m_pScene2D = NULL;
CPolygon2D *CTimeCharge::m_pPolygon2D[POLYGON2D_TEX_TC] = {};
CScene3D *CTimeCharge::m_pScene3D = NULL;
CMeshField *CTimeCharge::m_pMeshField = NULL;
//CBillboard *CTimeCharge::m_pBillboard = NULL;
CPolygon3D *CTimeCharge::m_pPolygon3D = NULL;
CParticle3D *CTimeCharge::m_pParticle3D = NULL;
CNumber *CTimeCharge::m_pNumber = NULL;
CTime *CTimeCharge::m_pTime = NULL;
CObject *CTimeCharge::m_pObject = NULL;
CPlayer *CTimeCharge::m_pPlayer = NULL;

//==============================================
//					�R���X�g���N�^
//==============================================
CTimeCharge::CTimeCharge()
{

}

//==============================================
//					�f�X�g���N�^
//==============================================
CTimeCharge::~CTimeCharge()
{

}

//==============================================
//						����
//==============================================
CTimeCharge *CTimeCharge::Create()
{
	CTimeCharge *pTitle = NULL;

	if (pTitle == NULL)
	{
		pTitle = new CTimeCharge;
		pTitle->Init();
	}

	return pTitle;
}
//==============================================
//					������
//==============================================
HRESULT CTimeCharge::Init(void)
{
	m_nDebugCnt = 0;
	
	NullCheck();				//�g�p����f�[�^����xNULL�ɂ���
	BulkLoadData();				//�g�p�������f���ƃe�N�X�`���̉��
	CreateData();				//�ǂݍ��񂾏������Ƃ�obj�̐���
	m_nCntTime = 0;
	m_bRotationSwitch = false;
	m_fRotation = 0;
	m_nChargeTime = 0;
	m_nCntChargeTime = 0;
	m_bFlag = false;
	m_bStartFlag = false;
	m_nStartCnt = 0;
	m_ChargeStart = false;
	m_pCamera->SetV(D3DXVECTOR3(-150.0f, 0.0f, -40.0f));//�����_����̋���
	m_pCamera->SetR(D3DXVECTOR3(-150.0f, 0.0f, 0.0f));//�����_�̈ʒu
	m_pSound = CManager::GetSound();
	if (m_pSound != NULL)
	{
		//m_pSound->PlaySound(CSound::BGM_SOUND_TITLE);
	}

	return S_OK;
}
//==============================================
//						�I��
//==============================================
void CTimeCharge::Uninit(void)
{
	if (m_pSound != NULL)
	{
		m_pSound->StopSound();
	}
	BulkUnLoadData();			//�g�p�������f���ƃe�N�X�`���̉��

	if (m_pTime != NULL)
	{
		m_pTime = NULL;			//�^�C��
	}

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
void CTimeCharge::Update(void)
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

	Event();//��A�̗���(�܂Ƃ�)
	
#ifdef _DEBUG
	Debug();
	//DebugLoop();
#endif
}

//==============================================
//					�`��
//==============================================
void CTimeCharge::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();//�J�����`��
	}

}

//==============================================
//				�C�x���g(��A�̗���)
//==============================================
void CTimeCharge::Event(void)
{
	//�������������J�E���g���I�������̐������Q�[���X�^�[�g

	if (m_pPolygon2D[3] != NULL)
	{
		if (m_pInputKeyboard->GetTrigger(DIK_SPACE) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
		{//����
			m_bStartFlag = true;
			if (m_pPolygon2D[3] != NULL)
			{
				m_pPolygon2D[3]->Uninit();
				m_pPolygon2D[3] = NULL;
			}
		}
	}
	if (m_bStartFlag == true)
	{//���Ԑ���
		m_nStartCnt++;
		if (m_pPolygon2D[4] == NULL)
		{
			m_pPolygon2D[4] = CPolygon2D::Create(14, false, D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200.0f, 200.0f, 50, 2, 2, false);

		}

		if (m_nStartCnt == 1 || m_nStartCnt == 50 || m_nStartCnt == 100)
		{
			if (m_pSound != NULL)
			{
				m_pSound->PlaySound(CSound::SE_COUNT);//�J�E���g��
			}
		}
		if (m_nStartCnt >= 150)//�A�j���̑���*���v�R�}���萔 = �����鎞��
		{
			m_bStartFlag = false;
			m_ChargeStart = true;
			if (m_pPolygon2D[4] != NULL)
			{
				m_pPolygon2D[4] = NULL;
			}
		}
	}
	if (m_ChargeStart == true)
	{
		if (m_pPolygon2D[0] == NULL&&m_pPolygon2D[1] == NULL)
		{//�A�ŕ�������
			m_pPolygon2D[0] = CPolygon2D::Create(6, false, D3DXVECTOR3(650.0f, 150.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130.0f, 50.0f, 1, 1, 1, true);
		}

		//���f���̉�]
		m_nCntChargeTime++;//�`���[�W�\����
		if (m_nCntChargeTime <= 200)
		{
			if (m_pInputKeyboard->GetTrigger(DIK_SPACE) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
			{
				if (m_pSound != NULL)
				{
					m_pSound->PlaySound(CSound::SE_CHARGE);//�`���[�W��
				}
				m_bRotationSwitch = true;
				m_nChargeTime += 7;
				//��]�Ɠ����ɃG�t�F�N�g�A�j���[�V�����𐶐�
				CPolygon3D::Create(0, D3DXVECTOR3(-75.0f, 5.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f), 2, 4, 3, false);
			}
			if (m_bRotationSwitch == true)
			{
				m_nCntTime++;
				m_fRotation += 0.1f;
				m_pObject->SetRot(D3DXVECTOR3(0.0f, m_fRotation, 0.0f));
				if (m_nCntTime >= 25)
				{
					m_bRotationSwitch = false;//��]���~�߂�
					m_nCntTime = 0;//�ēx�񂹂�悤�ɏ����n�ɖ߂�
				}
			}
		}
		else
		{
			if (m_pPolygon2D[0] != NULL)
			{
				m_pPolygon2D[0]->Uninit();//[�A��!]�A�C�R��������
				m_pPolygon2D[0] = NULL;
			}

		}
		if (m_nCntChargeTime >= 210)
		{
			m_bFlag = true;//�I���t���O�𗧂Ă�
			if (m_pPolygon2D[1] == NULL)
			{//[�I��!]�A�C�R���𐶐�
				if (m_pSound != NULL)
				{
					m_pSound->PlaySound(CSound::SE_TIMEUP);//�I����
				}
				m_pPolygon2D[1] = CPolygon2D::Create(7, false, D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200.0f, 120.0f, 1, 1, 1, true);
				m_pPolygon2D[2] = CPolygon2D::Create(8, false, D3DXVECTOR3(1050.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 190.0f, 45.0f, 1, 1, 1, true);

			}
			if (m_pInputKeyboard->GetTrigger(DIK_RETURN) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_START, 0) == true)
			{
				if (m_pFade == CFade::FADE_NONE)
				{
					if (m_pSound != NULL)
					{
						m_pSound->PlaySound(CSound::SE_BUTTON);
					}
					CManager::GetFade()->SetFade(CManager::MODE_GAME);
				}
			}
		}
	}
}

//==============================================
//				NULL�`�F�b�N
//==============================================
void CTimeCharge::NullCheck(void)
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

	for (int nCnt = 0; nCnt < POLYGON2D_TEX_TC; nCnt++)
	{
		if (m_pPolygon2D[nCnt] != NULL)
		{
			m_pPolygon2D[nCnt] = NULL;	//�|���S��2D
		}
	}

	if (m_pPolygon3D != NULL)
	{
		m_pPolygon3D = NULL;	//�|���S��3D
	}

	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;		//�v���C���[
	}
}

//==============================================
//				�@Load����(�ǂݍ���)
//==============================================
void CTimeCharge::BulkLoadData(void)
{
	CPolygon2D::TextureLoad();
	CPolygon3D::TextureLoad();
	CParticle3D::TextureLoad();
	CNumber::TextureLoad();
	CObject::ObjectLoad();
	CObject::TextureLoad();
	CPlayer::ModelLoad();
	CPlayer::TextureLoad();

}

//==============================================
//				�@UnLoad����(���)
//==============================================
void CTimeCharge::BulkUnLoadData(void)
{
	CPlayer::TextureUnLoad();
	CPlayer::ModelUnLoad();
	CObject::TextureUnLoad();
	CObject::ObjectUnLoad();
	CNumber::TextureUnLoad();
	CParticle3D::TextureUnLoad();
	CPolygon3D::TextureUnLoad();
	CPolygon2D::TextureUnLoad();
}

//==============================================
//					��������
//==============================================
void CTimeCharge::CreateData(void)
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

	if (m_pTime == NULL)//�^�C��
	{						//�}�l�[�W�������Ԃ��Ǘ����Ă���
		m_pTime = CTime::Create(10, D3DXVECTOR2(55.0f, 55.0f), D3DXVECTOR2(120.0f, 610.0f));
	}

	if (m_pPolygon2D[0] == NULL)//2D�e�N�X�`��
	{
		CPolygon2D::Create(9, false, D3DXVECTOR3(640.0f, 25.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 640.0f, 25.0f, 1, 1, 1, true);
		CPolygon2D::Create(10, false, D3DXVECTOR3(640.0f, 695.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 640.0f, 25.0f, 1, 1, 1, true);
		m_pPolygon2D[3] = CPolygon2D::Create(15, false, D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 400.0f, 300.0f, 1, 1, 1, true);
	}

	//�I�u�W�F�N�g
	m_pObject = CObject::Create(0, 0, D3DXVECTOR3(-150.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	
}

//==============================================
//				�f�o�b�N�p����
//==============================================
void  CTimeCharge::Debug(void)
{
	CDebug::DebugLog("\n������Charge���ꂽ�� %d", m_nChargeTime);

	//�G���^�L�[�ōēx�Q�[���̊J�n
	if (m_pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		if (m_pFade == CFade::FADE_NONE)
		{
			CManager::GetFade()->SetFade(CManager::MODE_GAME);
		}
	}
	CDebug::DebugLog("\nNULL�� %d", m_pPolygon2D[4]);
	
}
void  CTimeCharge::DebugLoop(void)
{
	m_nDebugCnt++;
	if (m_nDebugCnt >= 50)
	{
		if (m_pFade == CFade::FADE_NONE)
		{
			CManager::GetFade()->SetFade(CManager::MODE_GAME);
		}
	}
}
