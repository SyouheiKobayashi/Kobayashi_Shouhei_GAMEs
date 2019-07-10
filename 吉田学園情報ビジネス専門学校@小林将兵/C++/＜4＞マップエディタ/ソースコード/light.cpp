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
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		m_light[nCnt] = {};
		m_vecDir[nCnt] = {};
	}

	SetLight(0, D3DXVECTOR3(0.5f, -0.7f, 0.2f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetLight(1, D3DXVECTOR3(3.5f, 0.1f, -0.8f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetLight(2, D3DXVECTOR3(0.1f, -0.8f, 2.1f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//? *�w�������pos���l�ʂ�ɂ�����x�������΃��C�g���ǂ̕����Ɍ����Č��𓖂ĂĂ���̂���̂킩��͂�
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
//���C�g�̐ݒ�
//==============================================
void CLight::SetLight(int nLightNumber, D3DXVECTOR3 pos, D3DXCOLOR col)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	ZeroMemory(&m_light, sizeof(D3DLIGHT9));// ���C�g�̃N���A

	m_light[nLightNumber].Type = D3DLIGHT_DIRECTIONAL;// ���C�g�̎�ނ�ݒ�

	m_light[nLightNumber].Diffuse = col;// ���C�g�̊g�U����ݒ�

	// ���C�g�̕����̐ݒ�

	m_vecDir[nLightNumber] = pos;

	D3DXVec3Normalize(&m_vecDir[nLightNumber], &m_vecDir[nLightNumber]);
	m_light[nLightNumber].Direction = m_vecDir[nLightNumber];

	pDevice->SetLight(nLightNumber, &m_light[nLightNumber]);	// ���C�g�̃^�C�v�ݒ�

	pDevice->LightEnable(nLightNumber, TRUE);// ���C�g��L����
}

