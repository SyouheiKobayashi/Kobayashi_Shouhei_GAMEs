//=============================================================================
// �|���S������ [meshWall.h]
// Author : Kobayashi/���я���
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//��]
	D3DXMATRIX mtxWorldWall;	//���[���h�}�g���b�N�X

	bool bUse;
}MESHWALL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);

void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

#endif
