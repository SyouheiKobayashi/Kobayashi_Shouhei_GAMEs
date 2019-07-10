//=============================================================================
//
// �X�R�A���� [Ranking.h]
// Author : Kishida Rei
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	RANKINGTYPE_NUMBER = 0, //����
	RANKINGTYPE_CHARACTER,
	RANKINGTYPE_MAX
}RANKINGTYPE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;
	bool bUse;
	int nType;
	int g_aRankingNumber;
	int nRankScore;
}RANKING;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);

void SetRanking(int nScore);

//void SetRankingpos(D3DXVECTOR3 pos);

#endif
