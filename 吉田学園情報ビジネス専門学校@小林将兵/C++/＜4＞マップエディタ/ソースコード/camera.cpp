//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�J�������� [camera.cpp]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "camera.h"
#include "manager.h"
#include "debugLog.h"
#include "input.h"
#include "game.h"

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
	//m_cameraMode = MODE_XYZ;
	m_nCameraMode = 1;
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
	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	m_pInputMouse = CManager::GetInputMouse();
	m_pGame = CManager::GetGame();

	if (m_pGame != NULL)
	{
		if (m_pGame->GetInputMode() == 0)//���̓��[�h(�L�[�{�[�h)
		{
			MOVE();//�J�����̈ړ� / �g�� / ������
			//PointViewRot();//�����_�����Ɏ��_�̉�]
			//NoteViewRot(); //���_�̉�]
		}
	}

	if (m_pGame != NULL)
	{
		if (m_pGame->GetInputMode() == 1)//���̓��[�h(�L�[�{�[�h)
		{
			MOVE02();//�J�����̈ړ� / �g�� / ������
		}
	}

	if (m_pInputKeyboard->GetTrigger(DIK_F1) == true)
	{
		m_nCameraMode += 1;
		if (m_nCameraMode >= MODE_MAX)
		{
			m_nCameraMode = MODE_XYZ;//�ŏ��̏�Ԃɖ߂�
		}

		if (m_nCameraMode == MODE_XYZ)
		{
			m_posV.y = 50.0f;
		}
		if (m_nCameraMode == MODE_XZ)
		{
			m_posV.y = 300.0f;
		}
	}
	

	
	//CDebug::DebugLog("VXXX %.1f", m_posV.x);
	CDebug::DebugLog("\nVZZZ %.1f,%.1f,%.1f", m_posV.x, m_posV.y,m_posV.z);
	CDebug::DebugLog("\nRZZZ %.1f,%.1f,%.1f", m_posR.x, m_posR.y,m_posR.z);

}

//==============================================
//�ړ� / �g��E�k�� / ������
//==============================================
void CCamera::MOVE(void)
{

	//�㉺���E
	if (m_pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{
		m_posV.x += 4.0f;
		m_posR.x += 4.0f;
	}

	if (m_pInputKeyboard->GetPress(DIK_LEFT) == true)
	{
		m_posV.x -= 4.0f;
		m_posR.x -= 4.0f;
	}

	if (m_pInputKeyboard->GetPress(DIK_UP) == true)
	{
		m_posV.y += 4.0f;
		m_posR.y += 4.0f;
	}
	if (m_pInputKeyboard->GetPress(DIK_DOWN) == true)
	{
		m_posV.y -= 4.0f;
		m_posR.y -= 4.0f;
	}
	//�J�����ʒu�̏�����
	if (m_pInputKeyboard->GetPress(DIK_0) == true)
	{
		if (m_nCameraMode == MODE_XYZ)
		{
			m_posV = D3DXVECTOR3(0.0f, 50.0f, -400.0f);
		}
		if (m_nCameraMode == MODE_XZ)
		{
			m_posV = D3DXVECTOR3(0.0f, 300.0f, -400.0f);
		}
		
		m_posR = CAMERA_R;
		m_fRotation = 0.0f;
	}
}

void CCamera::MOVE02(void)
{
	//�}�E�X�̉��ړ������m�A�J����(�����_)�̉�]
	if (m_pInputMouse->GetPress(1) == true)
	{
		if (m_pInputMouse->GetWheel().lX < 0)
		{
			m_fRotation -= 0.03f;
			if (m_fRotation > D3DX_PI)
			{
				m_fRotation = -D3DX_PI;
			}
			m_posR.x = m_posV.x + sinf(m_fRotation) * CAMERA_INIT_V;
			m_posR.z = m_posV.z + cosf(m_fRotation) * CAMERA_INIT_V;
		}
		if (m_pInputMouse->GetWheel().lX > 0)
		{
			m_fRotation += 0.03f;
			if (m_fRotation > D3DX_PI)
			{
				m_fRotation = -D3DX_PI;
			}
			m_posR.x = m_posV.x + sinf(m_fRotation) * CAMERA_INIT_V;
			m_posR.z = m_posV.z + cosf(m_fRotation) * CAMERA_INIT_V;
		}
	}

	//�㉺���E
	if (m_pInputKeyboard->GetPress(DIK_D) == true)
	{
		m_posV.x += 4.0f;
		m_posR.x += 4.0f;
	}

	if (m_pInputKeyboard->GetPress(DIK_A) == true)
	{
		m_posV.x -= 4.0f;
		m_posR.x -= 4.0f;
	}

	if (m_pInputKeyboard->GetPress(DIK_E) == true)
	{
		m_posV.y += 4.0f;
		m_posR.y += 4.0f;
	}
	if (m_pInputKeyboard->GetPress(DIK_Q) == true)
	{
		m_posV.y -= 4.0f;
		m_posR.y -= 4.0f;
	}
	//�O�i�E���
	if (m_pInputKeyboard->GetPress(DIK_W) == true)
	{
		m_posV.z += 4.0f;
		m_posR.z += 4.0f;
	}
	if (m_pInputKeyboard->GetPress(DIK_S) == true)
	{
		m_posV.z -= 4.0f;
		m_posR.z -= 4.0f;
	}
	//�J�����ʒu�̏�����
	if (m_pInputKeyboard->GetPress(DIK_X) == true)
	{
		m_posV = CAMERA_V;
		m_posR = CAMERA_R;
		m_fRotation = 0.0f;
	}

	CDebug::DebugLog("\n�}�E�Xaaa %.f", m_pInputMouse->GetWheel().lX);

}

//==============================================
//�����_�����Ɏ��_�̉�]
//==============================================
void CCamera::PointViewRot(void)
{
	if ((m_pInputKeyboard->GetPress(DIK_UP) == true))//��]
	{

		m_fRotation += 0.02f;
		if (m_fRotation > D3DX_PI)
		{
			m_fRotation = -D3DX_PI;
		}
		m_posV.x = m_posR.x - sinf(m_fRotation) * CAMERA_INIT_V;
		m_posV.z = m_posR.z - cosf(m_fRotation) * CAMERA_INIT_V;
	}
	if ((m_pInputKeyboard->GetPress(DIK_DOWN) == true))//��]
	{

		m_fRotation -= 0.02f;
		if (m_fRotation > D3DX_PI)
		{
			m_fRotation = -D3DX_PI;
		}
		m_posV.x = m_posR.x - sinf(m_fRotation) * CAMERA_INIT_V;
		m_posV.z = m_posR.z - cosf(m_fRotation) * CAMERA_INIT_V;
	}
}

//==============================================
//���_�̉�]
//==============================================
void CCamera::NoteViewRot(void)
{
	if ((m_pInputKeyboard->GetPress(DIK_LEFT) == true))//��]
	{
		m_fRotation -= 0.03f;
		if (m_fRotation > D3DX_PI)
		{
			m_fRotation = -D3DX_PI;
		}
		m_posR.x = m_posV.x + sinf(m_fRotation) * CAMERA_INIT_V;
		m_posR.z = m_posV.z + cosf(m_fRotation) * CAMERA_INIT_V;

	}

	if ((m_pInputKeyboard->GetPress(DIK_RIGHT) == true))//��]
	{
		m_fRotation += 0.03f;
		if (m_fRotation > D3DX_PI)
		{
			m_fRotation = -D3DX_PI;
		}
		m_posR.x = m_posV.x + sinf(m_fRotation) * CAMERA_INIT_V;
		m_posR.z = m_posV.z + cosf(m_fRotation) * CAMERA_INIT_V;

	}

}

//==============================================
//�J�����̐ݒ�
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