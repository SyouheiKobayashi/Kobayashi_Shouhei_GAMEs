//=============================================================================
//
// �|���S���̏��� [player.h]
// Author : Kishida Rei
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//�o�����
	PLAYERSTATE_NORMAL,		//�ʏ���
	PLAYERSTATE_CHARGE,		//�ʏ���
	PLAYERSTATE_TIRED,		//�����[�h���
	PLAYERSTATE_A,
	PLAYERSTATE_B,
	PLAYERYSTATE_MAX			//��ނ̑���
}PLAYERSTATE;

typedef enum
{
	WEAPON_SPREAD = 0,	//�X�v���b�h
	WEAPON_VALCAN,		//�o���J��
	WEAPON_CANON,		//�L���m��
	WEAPON_MAX			//�ő吔
}PLAYERWEAPON;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	PLAYERSTATE state;	//�v���C���[�̏��
	int nCounterState;	//��ԊǗ��̃J�E���^�[
	int nCntCharge;
	int nCntStamina;		//�X�^�~�i�J�E���g
	int nCounterAnim;
	int nPatternAnim;
	bool bDisp;			//�g�p����Ă��邩
}PLAYER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UnInitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer();

void HitPlayer(int nDamage);
#endif