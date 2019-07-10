//=============================================================================
//
// �L�[�F�ς����� [pausemenu.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _PAUSEMENU_H_
#define _PAUSEMENU_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_PAUSEMENU	(128)	// �w�i�̍ő吔



//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	PAUSEMENUSTATE_NORMAL = 0,	//�ʏ���
	PAUSEMENUSTATE_SELECT,			//�I�����
	PAUSEMENUSTATE_MAX			//��ނ̑���
}PAUSEMENUSTATE;


typedef enum
{
	PAUSEMENUSTATE_NONE = 0,	//�ʏ���
	PAUSEMENUSTATE_USE,			//�I�����
	PAUSEMENU_STATE_MAX			//��ނ̑���
}PAUSESTATE;


typedef enum
{
	CONTINUE = 0,	//�R���e�B�j���[
	RETRY,			//���g���C
	QUIT,			//�N�E�B�b�g
	MAX_MENU		//����
}MENU;


typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;		//�J���[
	MENU menu;
	int nType;			//���
	PAUSEMENUSTATE state;	//�L�[�̏��
	PAUSESTATE uState;
	int nCntState;
	
	bool bUse;			//�g�p���Ă��邩�ǂ���
}PAUSEMENU;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPauseMenu(void);
void UnInitPauseMenu(void);
void UpdatePauseMenu(void);
void DrawPauseMenu(void);




//void PushPauseMenu(int nNowSelect);
void PushPauseMenu(void);

void SetPauseMenu(D3DXVECTOR3 pos, int nType);
#endif