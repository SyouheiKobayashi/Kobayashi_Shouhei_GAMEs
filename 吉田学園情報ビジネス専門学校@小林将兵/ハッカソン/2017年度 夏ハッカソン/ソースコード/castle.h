//=============================================================================
//
// �|���S���̏��� [Castler.h]
// Author : Kishida Rei
//
//=============================================================================
#ifndef _CASTLE_H_
#define _CASTLE_H_

#include "main.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	CASTLESTATE_APPEAR = 0,	//�o�����
	CASTLESTATE_NORMAL,		//�ʏ���
	CASTLESTATE_DAMAGE,		//�_���[�W���
	CASTLESTATE_DEATH,		//���S���
	CASTLEYSTATE_MAX			//��ނ̑���
}CASTLESTATE;


typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	CASTLESTATE state;	//�X�e�[�g
	int nCounterState;	//��ԊǗ��̃J�E���^�[
	int nCntCharge;
	int nCntReload;		//�����[�h�J�E���g
	int nSpreadReload;	//�X�v���b�h�����[�h
	int nValcanReload; //�o���J�������[�h
	int nCanonReload;	//�L���m�������[�h
	int nLife;			//�G�̗̑�
	int nStock;			//�c�@
	bool bDisp;			//�g�p����Ă��邩
}CASTLE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCastle(void);
void UnInitCastle(void);
void UpdateCastle(void);
void DrawCastle(void);

 


CASTLE *GetCastle();

void HitCastle(int nDamage);
#endif