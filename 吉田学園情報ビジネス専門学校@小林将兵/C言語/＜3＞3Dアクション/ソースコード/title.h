//=========================================================================
// �^�C�g����ʂ̏��� [title.h]
// Author:Kobayashi/���� ����
//=========================================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "game.h"

typedef enum
{
	TITLE_0 = 0,//����
	TITLE_1,//�����錩����
	TITLE_MAX//�ő吔
}TITLE_STATE;//���
//=========================================================================
//�v���g�^�C�v�錾
//=========================================================================
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif