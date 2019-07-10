//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//? [Player.h]
//? Author : Kobayashi / ����
//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _PLAYER_H_
#define _PLAYER_H_

//? ==================================================
//? �}�N����`
//? ==================================================
#define PLAYER_SIZE	(20)
#define PLAYER_LIFE	(22)
#define Player_Speed	(2.0f)			// �|���S���̑��x

//? ==================================================
//? �\����
//? ==================================================
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//�o�����
	PLAYERSTATE_NORMAL,		//�ʏ펞���
	PLAYERSTATE_DAMAGE,		//�_���[�W�����
	PLAYERSTATE_DEATH,		//���S���
	PLAYERSTATE_END,
	PLAYERSTATE_MAX			//�v���C���[�̏�Ԃ̑���
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	PLAYERSTATE state;	//�v���C���[�̏��
	int nCounterState;	//��ԊǗ��̃J�E���^�[
	int nLife;			//�̗�
	bool bDisp;			//�\�����邩�ۂ�
}PLAYER;

//? ==================================================
//? �v���g�^�C�v�錾
//? ==================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
void HitPlayer(int nDamage);
#endif
