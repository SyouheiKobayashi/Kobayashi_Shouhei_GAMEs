//=============================================================================
//
// �u���b�N���� [block.h]
// Author : komatsu
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nType;
}BlockInfo;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nCounterAnim;		//�A�j���[�V�����J�E���^
	int nPatternAnim;		//�A�j���[�V�����p�^�[��
	float fWidth;			//��
	float fHeight;			//����
	int nType;				//�e�N�X�`���̃^�C�v
	bool bChange;
	bool bUse;				//�g�p
}Block;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);
bool CollisionBlock(D3DXVECTOR3  *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth);

Block *GetBlock(void);
#endif
