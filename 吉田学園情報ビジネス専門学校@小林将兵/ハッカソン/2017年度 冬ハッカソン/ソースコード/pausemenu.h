//=============================================================================
//
// �|�[�Y���j���[���� [pausemenu.h]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#ifndef _PAUSEMENU_H_
#define _PAUSEMENU_H_

#include "main.h"
#include "input.h"
#include "game.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	CONTINUE,
	RETRY,
	QUIT,
	MAX_PAUSEMENU
}PAUSEMENUSTATE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nType;			//���
	PAUSEMENUSTATE pmenu;		//���
} PAUSEMENU;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPmenu(void);
void UninitPmenu(void);
void UpdatePmenu(void);
void DrawPmenu(void);
void SelectPmenu(void);
#endif