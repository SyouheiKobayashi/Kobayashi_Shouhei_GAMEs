//=============================================================================
// ��Q���p���f������ [fallingRocks.h]
// Author :Kobayashi/���я���//
//=============================================================================
#ifndef _FALLINGROCKS_H_
#define _FALLINGROCKS_H_

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
	int nType;
	bool bUse;
	bool bTouch;
}FALLINGROCKS;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitFallingRocks(void);
void UninitFallingRocks(void);
void UpdateFallingRocks(void);
void DrawFallingRocks(void);

void SetFallingRocks(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType);

void CollisionFallingRocks(D3DXVECTOR3 * pPos,		//���@�̌��݂̈ʒu
	D3DXVECTOR3 * pPosOld,	//���@�̂ЂƂO�̈ʒu
	D3DXVECTOR3 * pMove,//���@�̈ړ���
	D3DXVECTOR3 *pVtxMax,
	D3DXVECTOR3 *pVtxMin);	


FALLINGROCKS *GetFallingRocks(void);


#endif
