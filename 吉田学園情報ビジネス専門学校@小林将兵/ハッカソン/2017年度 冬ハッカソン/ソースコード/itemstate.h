//=============================================================================
//
// �A�C�e���X�e�[�^�X���� [itemstate.h]
// Author : komatsu
//
//=============================================================================
#ifndef _ITEMSTATE_H_
#define _ITEMSTATE_H_

#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	int nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�����p�^�[��
	int nType;				//�A�C�e���̎��
	float fHeight;			//�A�C�e���̏c��
	float fWidth;			//�A�C�e���̉���
	bool bUse;				//�g�p���Ă��邩�ǂ���
}ItemState;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitItemState(void);
void UninitItemState(void);
void UpdateItemState(void);
void DrawItemState(void);
void SetItemState(int nType);
ItemState *GetItemState(void);
#endif
