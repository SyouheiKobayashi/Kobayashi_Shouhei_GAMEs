//=============================================================================
// ��Q���p���f������ [item.h]
// Author :Kobayashi/���я���//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

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
}ITEM;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move);

void CollisionItem(D3DXVECTOR3 * pPos,		//���@�̌��݂̈ʒu
	D3DXVECTOR3 * pPosOld,	//���@�̂ЂƂO�̈ʒu
	D3DXVECTOR3 * pMove,//���@�̈ړ���
	D3DXVECTOR3 *pVtxMax,
	D3DXVECTOR3 *pVtxMin);	


ITEM *GetItem(void);


#endif
