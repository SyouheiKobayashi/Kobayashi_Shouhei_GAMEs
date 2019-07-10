//=============================================================================
//
// ���j���[���� [menu.h]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#ifndef _MENU_H_
#define _MENU_H_

#include "main.h"
#include "input.h"
#include "game.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	MENUTYPE_GAME,
	MENUTYPE_TITLE,
	MENUTYPE_MAX
}MENUTYPE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nType;			//���
	MENUTYPE menu;		//���
} MENU;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMenu(void);
void UninitMenu(void);
void UpdateMenu(void);
void DrawMenu(void);
void SelectMenu(void);
#endif