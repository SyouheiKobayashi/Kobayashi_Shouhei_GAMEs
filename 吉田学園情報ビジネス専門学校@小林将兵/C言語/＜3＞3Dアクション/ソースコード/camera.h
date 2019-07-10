//=============================================================================
// �J�������� [camera.h]
// Author : Kobayashi/���я���
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �J�����̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posV;		//(���݂�)���_
	D3DXVECTOR3 posR;		//(���݂�)�����_
	D3DXVECTOR3 vecU;

	D3DXVECTOR3 posVDest;	//(�ړI��)���_
	D3DXVECTOR3 posRDest;	//(�ړI��)�����_

	//�J�����̉�荞��
	D3DXVECTOR3 rot;		//(���݂�)����
	D3DXVECTOR3 rotDest;	//(�ړI��)����

	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxViex;
	float Radian;//�J�����̋���
	float fKaiten;
}camera;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);

camera *GetCamera(void);

#endif
