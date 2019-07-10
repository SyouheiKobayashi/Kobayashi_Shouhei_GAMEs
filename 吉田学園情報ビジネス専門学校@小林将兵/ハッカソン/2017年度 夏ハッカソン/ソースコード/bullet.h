//=============================================================================
//
// �e���� [bullet.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
//�e�̎��
typedef enum
{
	BULLETTYPE_PLAYER = 0,		//�v���C���[�̒e
	BULLETTYPE_ENEMY,
	BULLETYPE_MAX				//��ނ̑���
}BULLETTYPE;


typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	BULLETTYPE type;	//�e�̎��
	float fRadius;		//�e�̔��a
	float fangle;		//�p�x
	int nLife;			//�e�̎���
	bool bUse;			//�g�p���Ă��邩�ǂ���
} Bullet;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UnInitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move , BULLETTYPE type, float fRadius, int nLife);

Bullet *GetBullet(void);
#endif
