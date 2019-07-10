//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�J�������� [camera.cpp]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "camera.h"
#include "manager.h"
#include "debugLog.h"
#include "input.h"
#include "game.h"
#include "player.h"

//==============================================
//�R���X�g���N�^
//==============================================
CCamera::CCamera()
{
	
}

//==============================================
//�f�X�g���N�^
//==============================================
CCamera::~CCamera()
{
}

//==============================================
//����
//==============================================
CCamera *CCamera::Create(void)
{
	CCamera *pCamera = NULL;

	if (pCamera == NULL)
	{
		pCamera = new CCamera;
		pCamera->Init();

	}
	return pCamera;
}
//==============================================
//������
//==============================================
void CCamera::Init(void)
{
	m_posV = CAMERA_V;//���_
	m_posR = CAMERA_R;//�����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0, 0, 0);//(�ړI��)���_
	m_posRDest = D3DXVECTOR3(0, 0, 0);//(�ړI��)�����_
	D3DXVECTOR3 rot = D3DXVECTOR3(0, 0, 0);//(���݂�)����
	D3DXVECTOR3 rotDest = D3DXVECTOR3(0, 0, 0);//(�ړI��)����
	m_Radian = CAMERA_WIDTH;
	m_fRotation = 0;
	m_fCameraPosZ = 220.0f;
}

//==============================================
//�I��
//==============================================
void CCamera::Uninit(void)
{
	delete this;
}
//==============================================
//�X�V
//==============================================
void CCamera::Update(void)
{
	if (CManager::GetMode() == CManager::MODE_GAME)//�Q�[���̂݃v���C���[�̒ǐ�
	{
		CPlayer *pPlayer = CGame::GetPlayer();
		if (pPlayer != NULL)
		{

			if (pPlayer->GetOutStage() == false)//�X�e�[�W�O�ɂł���X�V�𒆒f����
			{
				CameraView();
			}
		}
	}
	m_pInputKeyboard = CManager::GetInputKeyboard();
	//DebugCameraMove();//�J�����ړ�
}

//==============================================
//					�J�����̐ݒ�
//==============================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(m_Radian),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	////�ׂ����悤�ȕ`��\��
	/*D3DXMatrixOrthoLH(&m_mtxProjection,
		(float)SCREEN_WIDTH,
		(float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);*/

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxViex);

	//�r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxViex,
		&m_posV,
		&m_posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxViex);
}

//==============================================
//				�J�����̌���
//==============================================
void CCamera::CameraView()
{
	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer != NULL)
	{
		if (pPlayer->GetPos().z >= 220.0f)
		{
			m_fCameraPosZ = 145.0f;
		}
		else
		{
			m_fCameraPosZ = 220.0f;
		}
		m_posRDest.x = pPlayer->GetPos().x - sinf(pPlayer->GetRot().y);
		m_posRDest.y = pPlayer->GetPos().y;
		m_posRDest.z = pPlayer->GetPos().z - cosf(pPlayer->GetRot().y);

		m_posVDest.x = m_posRDest.x - sinf(m_rot.y);
		m_posVDest.y = m_posRDest.y;
		m_posVDest.z = m_posRDest.z - cosf(m_rot.y);

		m_posR.x += (m_posRDest.x - m_posR.x + 100.0f)*0.09f;
		m_posR.y += (m_posRDest.y - m_posR.y + 50.0f)*0.05f;
		m_posR.z += (m_posRDest.z - m_posR.z)*0.09f;

		m_posV.x += (m_posVDest.x - m_posV.x + 50.0f)*0.09f;
		m_posV.y += (m_posVDest.y - m_posV.y + 60.0f)*0.05f;
		m_posV.z += (m_posVDest.z - m_posV.z - m_fCameraPosZ)*0.09f;

		m_posR.x = m_posV.x + sinf(D3DX_PI) * 200.0f;//�l�̒����ŏ����΂߂ɂ���
		m_posR.z = m_posV.z + cosf(m_fRotation) * 200.0f;
	}
}
//==============================================
//				�J�����̃L�[�ړ�
//==============================================
void CCamera::DebugCameraMove()
{
	if (m_pInputKeyboard->GetPress(DIK_NUMPAD6) == true)
	{
		m_posV.x += 4.0f;
		m_posR.x += 4.0f;
	}

	if (m_pInputKeyboard->GetPress(DIK_NUMPAD4) == true)
	{
		m_posV.x -= 4.0f;
		m_posR.x -= 4.0f;
	}

	if (m_pInputKeyboard->GetPress(DIK_NUMPAD7) == true)
	{
		m_posV.y += 4.0f;
		m_posR.y += 4.0f;
	}
	if (m_pInputKeyboard->GetPress(DIK_NUMPAD9) == true)
	{
		m_posV.y -= 4.0f;
		m_posR.y -= 4.0f;
	}

	if (m_pInputKeyboard->GetPress(DIK_NUMPAD8) == true)
	{
		m_posV.z += 4.0f;
		m_posR.z += 4.0f;
	}
	if (m_pInputKeyboard->GetPress(DIK_NUMPAD2) == true)
	{
		m_posV.z -= 4.0f;
		m_posR.z -= 4.0f;
	}
	//������
	if (m_pInputKeyboard->GetPress(DIK_NUMPAD5) == true)
	{
		m_posV = CAMERA_V;
		m_posR = CAMERA_R;
	}
}

void CCamera::SetV(D3DXVECTOR3 posV)
{
	m_posV = posV;
}
void CCamera::SetR(D3DXVECTOR3 posR)
{
	m_posR = posR;
}
