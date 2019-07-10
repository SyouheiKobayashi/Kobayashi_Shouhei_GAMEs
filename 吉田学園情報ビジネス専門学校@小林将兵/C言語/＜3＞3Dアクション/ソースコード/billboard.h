//=============================================================================
// �|���S������ [billboard.h]
// Author : Kobayashi/���я���
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//��]��
	D3DXMATRIX mtxWorldBillboard;	//���[���h�}�g���b�N�X
	int nType;
	bool bUse;
}BILLBOARD;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);

void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType);

#endif
