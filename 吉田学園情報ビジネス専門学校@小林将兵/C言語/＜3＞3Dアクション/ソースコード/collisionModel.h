//=============================================================================
// ��Q���p���f������ [collisionModle.h]
// Author :Kobayashi/���я���//
//=============================================================================
#ifndef _COLLISIONMODEL_H_
#define _COLLISIONMODEL_H_

#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//��]
	D3DXMATRIX mtxWorldCollision;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 VtxMin; //�ŏ��l
	D3DXVECTOR3 VtxMax;//�ő�l
	bool bUse;
}COLLISIONMODEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCollisionModle(void);
void UninitCollisionModle(void);
void UpdateCollisionModle(void);
void DrawCollisionModle(void);

void CollisionModel(D3DXVECTOR3 * pPos,		//���@�̌��݂̈ʒu
	D3DXVECTOR3 * pPosOld,	//���@�̂ЂƂO�̈ʒu
	D3DXVECTOR3 * pMove,//���@�̈ړ���
	D3DXVECTOR3 *pVtxMax,
	D3DXVECTOR3 *pVtxMin);	


COLLISIONMODEL *GetCollision(void);


#endif
