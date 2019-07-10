//=============================================================================
// ��Q���p���f������ [badItem.h]
// Author :Kobayashi/���я���//
//=============================================================================
#ifndef _BADITEM_H_
#define _BADITEM_H_

#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 move;			//�ړ�
	D3DXVECTOR3 rot;			//��]
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 VtxMin; //�ŏ��l
	D3DXVECTOR3 VtxMax;//�ő�l
	bool bUse;
	bool bTouch;
}BADITEM;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBadItem(void);
void UninitBadItem(void);
void UpdateBadItem(void);
void DrawBadItem(void);

void SetBadItem(D3DXVECTOR3 pos, D3DXVECTOR3 move);

void CollisionBadItem(D3DXVECTOR3 * pPos,		//���@�̌��݂̈ʒu
	D3DXVECTOR3 * pPosOld,	//���@�̂ЂƂO�̈ʒu
	D3DXVECTOR3 * pMove,//���@�̈ړ���
	D3DXVECTOR3 *pVtxMax,
	D3DXVECTOR3 *pVtxMin);	


BADITEM *GetBadItem(void);


#endif
