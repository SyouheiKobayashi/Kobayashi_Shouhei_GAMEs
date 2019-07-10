//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//? �G���� [enemy.h]
//? Author :���� / Kobayashi
//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//? ==================================================
//? �}�N����`
//? ==================================================
#define	ENEMY_MAX	(256)	// �G�̍ő吔
#define	ENEMY_TYPE		(4)						// �G�̎��
#define ENEMY_INTERVAL	(90)//�U���Ԋu
#define ENEMY_SIZE	(20)

//? ==================================================
//? �\���̒�`
//? ==================================================
//�񋓌^
typedef enum
{
	ENEMYSTATE_NORMAL=0,	//�ʏ펞���
	ENEMYSTATE_DAMAGE,		//�_���[�W�����
	ENEMYSTATE_MAX			//�G�̏�Ԃ̑���
}ENEMYSTATE;

typedef enum
{
	MOVE_L  = 0,
	MOVE_R,
	MOVE_MAX
}MOVE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ�
	int nType;			//���
	ENEMYSTATE state;	//�G�̏��
	int nCounterState;	//��ԊǗ��̃J�E���^�[
	int nLife;			//�̗�
	int nPatternAnimE;
	int nCountAnimE;
	bool bUse;			//�g�p���Ă邩�ۂ�
}ENEMY;

//? ==================================================
//? �v���g�^�C�v�錾
//? ==================================================
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

void SetEnemy(D3DXVECTOR3 pos, int nType);
ENEMY *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif
