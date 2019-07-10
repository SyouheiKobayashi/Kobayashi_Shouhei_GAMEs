//=============================================================================
//
// �v���C���[���� [player.h]
// Author : komatsu
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "block.h"

//=============================================================================
// �v���[���[�̍\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	float fHeight;
	float fWidth;
	int nCounterAnim;
	int nPatternAnim;
	int nDirectionMove;
	bool bChange;
	bool bItem;
}Player;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);

#endif