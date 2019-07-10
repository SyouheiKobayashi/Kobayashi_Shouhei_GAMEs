//=============================================================================
// �A�C�e������ [item.h]
// Author:Kobayashi/���� ����
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_ITEM	(255)	//�A�C�e���̍ő吔

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	float fWidth;		//�u���b�N�̕�
	float fHeight;		//�u���b�N�̍���
	int nItemType;		//�A�C�e���̃^�C�v����
	int SpeedAnimation;
	int PatternAnimation;
	bool bUse;			//�\�����邩�ۂ�
	bool bTouch; //�G��Ă��邩�ۂ�
}Item;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

void SetItem(D3DXVECTOR3 pos, int nItemType);

Item *GetItem(void);

bool CollisionItem(D3DXVECTOR3 *pPos,//�A�C�e���̌��݂̈ʒu
	D3DXVECTOR3 *pPosOld,	//�A�C�e���̂ЂƂO�̈ʒu
	D3DXVECTOR3 * pMove,	//�A�C�e���̈ړ���
	float fWidth,
	float fHeight);

#endif
