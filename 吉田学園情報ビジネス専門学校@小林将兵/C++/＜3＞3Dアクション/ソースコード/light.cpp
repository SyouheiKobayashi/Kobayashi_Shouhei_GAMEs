//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�J�������� [camera.cpp]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "light.h"
#include "input.h"
#include "manager.h"

//==============================================
//�R���X�g���N�^
//==============================================
CLight::CLight()
{
	

}
//==============================================
//�f�X�g���N�^
//==============================================
CLight::~CLight()
{

}
//==============================================
//����
//==============================================
CLight *CLight::Create(void)
{
	CLight *pLight = NULL;

	if (pLight == NULL)
	{
		pLight = new CLight;
		pLight->Init();

	}
	return pLight;
}

//==============================================
//������
//==============================================
void CLight::Init(void)
{
	//���C�g�̏�����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		
		m_Light[nCnt] = {};
		m_vecDir[nCnt] = {};

	}

	SetDirectionla(0,D3DXCOLOR(10.0f,10.0f,10.0f,10.0f), D3DXVECTOR3(-0.5f,-1.0f,1.0f));
	SetDirectionla(1, D3DXCOLOR(10.0f, 10.0f, 10.0f, 10.0f), D3DXVECTOR3(0.5f, -1.0f, 1.0f));
	//SetPoint(0, D3DXCOLOR(10.0f, 10.0f, 10.0f, 10.0f), D3DXVECTOR3(-100.0f, 1.0f, 0.0f),D3DXVECTOR3(-0.5f, -1.0f, 1.0f));
	//SetSpot(0, D3DXCOLOR(100000.0f, 100000.0f, 100000.0f, 100000.0f), D3DXVECTOR3(100.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

}

//==============================================
//�I��
//==============================================
void CLight::Uninit(void)
{
	delete this;
}

//==============================================
//�X�V
//==============================================
void CLight::Update(void)
{

}

//==============================================
//				�f�B���N�V���i�����C�g
//==============================================
void CLight::SetDirectionla(int lightNum, D3DXCOLOR col, D3DXVECTOR3 rot)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));

	///�����̎��:���s����(�f�B���N�V���i������)
	m_Light[lightNum].Type = D3DLIGHT_DIRECTIONAL;
	///�g�U��
	m_Light[lightNum].Diffuse.r = col.r;
	m_Light[lightNum].Diffuse.g = col.g;
	m_Light[lightNum].Diffuse.b = col.b;
	m_Light[lightNum].Diffuse.a = col.a;
	///����(���邭�Ȃ�)
	m_Light[lightNum].Ambient.r = 0.1f;
	m_Light[lightNum].Ambient.g = 0.1f;
	m_Light[lightNum].Ambient.b = 0.1f;
	m_Light[lightNum].Ambient.a = 1.0f;
	///�����̌���
	///�X�|�b�g�����A�f�B���N�V���i�������̏ꍇ�݈̂Ӗ�������B
	m_Light[lightNum].Direction.x = rot.x;
	m_Light[lightNum].Direction.y = rot.y;
	m_Light[lightNum].Direction.z = rot.z;
	//�����̗L���͈�:1000
	m_Light[lightNum].Range = 1000.0f;

	//���C�g���Z�b�g
	pDevice->SetLight(lightNum, &m_Light[lightNum]);
	//���C�g��L���ɂ���B
	pDevice->LightEnable(lightNum, TRUE);
	//���C�e�B���O���܂��B
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//���C�g�Ƃ͕ʎ��Ń��C�e�B���O���ʂ𐶂݂܂��B
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x00444444);
}

void CLight::SetPoint(int lightNum, D3DXCOLOR col, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));

	///�����̎��:���s����(�f�B���N�V���i������)
	m_Light[lightNum].Type = D3DLIGHT_POINT;
	///�g�U��
	m_Light[lightNum].Diffuse.r = col.r;
	m_Light[lightNum].Diffuse.g = col.g;
	m_Light[lightNum].Diffuse.b = col.b;
	m_Light[lightNum].Diffuse.a = col.a;
	///����(���邭�Ȃ�)
	m_Light[lightNum].Ambient.r = 0.1f;
	m_Light[lightNum].Ambient.g = 0.1f;
	m_Light[lightNum].Ambient.b = 0.1f;
	m_Light[lightNum].Ambient.a = 1.0f;

	///�����̈ʒu
	m_Light[lightNum].Position.x = pos.x;
	m_Light[lightNum].Position.y = pos.y;
	m_Light[lightNum].Position.z = pos.z;

	///�����̌���
	///�X�|�b�g�����A�f�B���N�V���i�������̏ꍇ�݈̂Ӗ�������B
	m_Light[lightNum].Direction.x = rot.x;
	m_Light[lightNum].Direction.y = rot.y;
	m_Light[lightNum].Direction.z = rot.z;

	//���C�g�̋��x�A
	m_Light[lightNum].Attenuation0 = 0.0f;
	m_Light[lightNum].Attenuation1 = 0.0f;
	m_Light[lightNum].Attenuation2 = 0.0f;

	//�����̗L���͈�:1000
	m_Light[lightNum].Range = 1000.0f;

	//���C�g���Z�b�g
	pDevice->SetLight(lightNum, &m_Light[lightNum]);
	//���C�g��L���ɂ���B
	pDevice->LightEnable(lightNum, TRUE);
	//���C�e�B���O���܂��B
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//���C�g�Ƃ͕ʎ��Ń��C�e�B���O���ʂ𐶂݂܂��B
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x00444444);
}

void CLight::SetSpot(int lightNum, D3DXCOLOR col, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	ZeroMemory(&m_Light[lightNum], sizeof(D3DLIGHT9));

	///�����̎��:���s����(�f�B���N�V���i������)
	m_Light[lightNum].Type = D3DLIGHT_SPOT;
	///�g�U��
	m_Light[lightNum].Diffuse.r = col.r;
	m_Light[lightNum].Diffuse.g = col.g;
	m_Light[lightNum].Diffuse.b = col.b;
	m_Light[lightNum].Diffuse.a = col.a;
	///����(���邭�Ȃ�)
	m_Light[lightNum].Ambient.r = 0.1f;
	m_Light[lightNum].Ambient.g = 0.1f;
	m_Light[lightNum].Ambient.b = 0.1f;
	m_Light[lightNum].Ambient.a = 1.0f;

	///�����̈ʒu
	m_Light[lightNum].Position.x = pos.x;
	m_Light[lightNum].Position.y = pos.y;
	m_Light[lightNum].Position.z = pos.z;

	///�����̌���
	///�X�|�b�g�����A�f�B���N�V���i�������̏ꍇ�݈̂Ӗ�������B
	m_Light[lightNum].Direction.x = rot.x;
	m_Light[lightNum].Direction.y = rot.y;
	m_Light[lightNum].Direction.z = rot.z;

	//���C�g�̋��x�A
	m_Light[lightNum].Attenuation0 = 1.0f;
	m_Light[lightNum].Attenuation1 = 1.0f;
	m_Light[lightNum].Attenuation2 = 1.0f;

	m_Light[lightNum].Theta = 2.00f;	//�悭����������ꏊ
	m_Light[lightNum].Phi = 3.00f;	//�኱����������ꏊ

	
	//�����̗L���͈� / �ő�1000.0f
	m_Light[lightNum].Range = 1000.0f;

	//���C�g���Z�b�g
	pDevice->SetLight(lightNum, &m_Light[lightNum]);
	//���C�g��L���ɂ���B
	pDevice->LightEnable(lightNum, TRUE);
	//���C�e�B���O���܂��B
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//���C�g�Ƃ͕ʎ��Ń��C�e�B���O���ʂ𐶂݂܂��B
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x00444444);
}