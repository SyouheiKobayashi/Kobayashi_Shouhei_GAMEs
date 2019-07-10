//=============================================================================
//
// �G���� [enemy.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ENEMY	(128)	// �G�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//�ʏ���
	ENEMYSTATE_DAMAGE,		//�_���[�W���
	ENEMYSTATE_MAX			//��ނ̑���
}ENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	ENEMYSTATE state;	//�G�̏��
	int nCountAnim;		//�A�j���[�V�����J�E���^�[
	int nPatternAnim;	//�A�j���[�V�����p�^�[��No.
	int nCounterState;	//��ԊǗ��̃J�E���^�[
	int nType;			//���
	int nLife;			//�G�̗̑�
	int nCountTime;		//�J�E���g
	float fSpeed;		//����
	bool bUse;			//�g�p���Ă��邩�ǂ���
}ENEMY;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy(void);
void UnInitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

void HitEnemy(int nCntEnemy, int nDamage);

void SetEnemy(D3DXVECTOR3 pos, int nType, int nLife);
ENEMY *GetEnemy(void);


#endif
