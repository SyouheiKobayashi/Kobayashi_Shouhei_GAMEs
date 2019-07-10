//=============================================================================
// �e�̏��� [bullet.h]
// Author : Kobayashi/���я���
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	int nLife;					//�e�̎���
	D3DXVECTOR3 pos;			//�ʒu
	//D3DXVECTOR3 rot;			//��]
	D3DXVECTOR3 move;			//�ړ�
	D3DXMATRIX mtxWorldBullet;	//���[���h�}�g���b�N�X
	bool bUse;
}BULLET;

//typedef enum
//{
//	BULLETTYPE_PLAYER = 0,//�v���C���[�̒e
//	//BULLETTYPE_ENEMY,	  //�G�̒e
//	BULLETTYPE_MAX
//}BULLETTYPE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);

#endif
