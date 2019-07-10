//=============================================================================
//
// �Ꮘ�� [snow.h]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#ifndef _SNOW_H_
#define _SNOW_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	float fRadius;
	bool bUse;
	int nIdxShadow;
	D3DXMATRIX mtxWorld;
}SNOW;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSnow(void);
void UninitSnow(void);
void UpdateSnow(void);
void DrawSnow(void);

#endif