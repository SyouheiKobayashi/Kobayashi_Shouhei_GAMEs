//=============================================================================
//
// �A�C�e������ [item.h]
// Author : komatsu
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_ITEM			(128)							//�A�C�e���̍ő吔

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	int nType;
}ItemInfo;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXCOLOR col;			//�F
	int nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�����p�^�[��
	int nType;				//�A�C�e���̎��
	float fHeight;			//�A�C�e���̏c��
	float fWidth;			//�A�C�e���̉���
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Item;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, int nType);
void CollisionItem(D3DXVECTOR3  *pPos, D3DXVECTOR3 *pPosOld, float fHeight, float fWidth);

#endif
