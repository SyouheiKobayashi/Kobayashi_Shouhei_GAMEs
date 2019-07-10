//=============================================================================
// ���C�g���� [light.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "light.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIGHT (3)//���C�g�̐�
#define LIGHT_1 D3DXVECTOR3(0.2f, -0.8f, 0.4f)
#define LIGHT_2 D3DXVECTOR3(10.2f, -0.8f, -1.4f)
#define LIGHT_3 D3DXVECTOR3(-10.2f, -0.8f, -1.4f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9 g_light[MAX_LIGHT];

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir[MAX_LIGHT];

//���C�g1
#if 1
	// ���C�g���N���A����
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	// ���C�g�̕����̐ݒ�
	vecDir[0] = LIGHT_1;
	D3DXVec3Normalize(&vecDir[0], &vecDir[0]);
	g_light[0].Direction = vecDir[0];

	// ���C�g��ݒ肷��
	pDevice->SetLight(0, &g_light[0]);//���C�g�̃^�C�v0

	// ���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
#endif

//���C�g2
#if 1
	// ���C�g���N���A����
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g�̕����̐ݒ�
	vecDir[1] = LIGHT_2;
	D3DXVec3Normalize(&vecDir[1], &vecDir[1]);
	g_light[1].Direction = vecDir[1];

	// ���C�g��ݒ肷��
	pDevice->SetLight(1, &g_light[1]);//���C�g�̃^�C�v1

	// ���C�g��L���ɂ���
	pDevice->LightEnable(1, TRUE);
#endif

//���C�g3
#if 1
	// ���C�g���N���A����
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	g_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g�̕����̐ݒ�
	vecDir[2] = LIGHT_3;
	D3DXVec3Normalize(&vecDir[2], &vecDir[2]);
	g_light[2].Direction = vecDir[2];

	// ���C�g��ݒ肷��
	pDevice->SetLight(2, &g_light[2]);//���C�g�̃^�C�v2

	// ���C�g��L���ɂ���
	pDevice->LightEnable(2, TRUE);
#endif
	

}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{
	
}

