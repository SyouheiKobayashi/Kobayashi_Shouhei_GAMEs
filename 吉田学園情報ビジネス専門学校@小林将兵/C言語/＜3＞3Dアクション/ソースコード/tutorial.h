//=========================================================================
// �`���[�g���A������ [tutorial.h]
// Author:Kobayashi/���� ����
//=========================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_


typedef enum
{
	TUTORIAL_0 = 0,//����
	TUTORIAL_1,//�����錩����
	TUTORIAL_MAX//�ő吔
}TUTORIAL_STATE;//���
//=========================================================================
//�v���g�^�C�v�錾
//=========================================================================
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

#endif