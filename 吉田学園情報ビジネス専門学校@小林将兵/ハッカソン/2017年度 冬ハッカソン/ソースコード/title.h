//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	TITLESTATE_NONE = 0,
	TITLESTATE_USE,
	TITLESTATE_MAX
}TITLE_STATE;


typedef enum
{
	TITLETYPE_NONE = 0,
	TITLETYPE_NOW,
	TITLETYPE_NEXT
}TITLE_TYPE;


typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	TITLE_TYPE TitleType;
	int nType;	
	float fAngle;
	float fLength;
	float fHeight;
	float fWidth;
	bool bUse;
	TITLE_STATE state;//���
}TITLE;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);


#endif


