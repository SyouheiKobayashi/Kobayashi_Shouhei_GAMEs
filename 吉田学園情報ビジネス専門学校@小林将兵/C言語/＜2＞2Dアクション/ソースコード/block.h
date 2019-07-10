//=============================================================================
// ���E�ǁA��Q�����̏��� [block.h]
// Author:Kobayashi/���� ����
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_BLOCK	(255)	// �u���b�N�̍ő吔

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ�
	float fWidth;		//�u���b�N�̕�
	float fHeight;		//�u���b�N�̍���
	int nBlockType;		//�u���b�N�̃^�C�v����
	bool bUse;			//�g�p���Ă邩�ۂ�
	bool Determine;	//�u���b�N�P��̔���
}Block;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, int nBlockType);

bool CollisionBlock(D3DXVECTOR3 *pPos,		//���@�̌��݂̈ʒu
					D3DXVECTOR3 *pPosOld,	//���@�̂ЂƂO�̈ʒu
					D3DXVECTOR3 * pMove,	//���@�̈ړ���
					float fWidth,
					float fHeight);

Block *GetBlock(void);

#endif
