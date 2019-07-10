//==============================================================================
// ���@�E����L�����̏���[player.h]
// Author:Kobayashi/���� ����
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//==============================================================================
// �v���C���[�\����
//==============================================================================
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//�o�����
	PLAYERSTATE_NORMAL,		//�ʏ펞���
	PLAYERSTATE_DEATH,		//���S���
	//PLAYERSTATE_END,		//�c�@�Ȃ�
	PLAYERSTATE_MAX			//�v���C���[�̏�Ԃ̑���
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;//���݂̈ʒu
	D3DXVECTOR3 posOld;//�O�� / �ЂƂO�̏���
	D3DXVECTOR3 move;//�ړ���
	
	PLAYERSTATE state;	//�v���C���[�̏��
	int nCounterState;	//��ԊǗ��̃J�E���^�[

	int nDirectionMove;//���@�������Ă������

	bool bwait;//���@���ҋ@���Ă��邩�ۂ� / �ړ����Ă��Ȃ�
	bool bJump;//�󒆂ɂ��邩�ۂ� / �W�����v���Ă��邩�ۂ�
	bool bTouch;
	bool bUse;
}Player;

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void); 
Player *GetPlayer(void);

#endif