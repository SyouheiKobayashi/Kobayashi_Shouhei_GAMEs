//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �G�E�G�l�~�[���� [enemy.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "scene2D.h"

//#define MAX_ENEMY_TYPE	(5)

class CBullet;
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �G�E�G�l�~�[CLASS(<scene2D>�̔h���N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CEnemy : public CScene2D
{
public:

	typedef enum
	{
		ENEMY01 = 0,
		ENEMY02,
		ENEMY03,
		ENEMY04,
		ENEMY05,
		ENEMY_BOSS,
		ENEMY_ALL
	}ENEMY_TYPE;

	CEnemy();
	~CEnemy();
	static HRESULT Load(void);//�e�N�X�`����K�v���ǂݍ���
	static void UnLoad(void);//�g�p���Ă���e�N�X�`���𑼂̏����ŏ������Ȃ��悤�ɂ���
	static CEnemy *Create(int nType ,int X_pos, int Y_pos,int Life);//(�c�T�C�Y,���T�C�Y,���C�t)

	HRESULT Init(int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void EnemyPattern(void);

	static CBullet *GetBullet(void) { return m_pBullet; }
	int GetEnemyType(void) { return m_nEnemyType; }//�^�C�v���̎擾

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[ENEMY_ALL];//���L�e�N�X�`���ւ̃|�C���^
	static CBullet *m_pBullet;

	//! <�|���S���̃A�j���[�V�����Ɋւ���ϐ�>
	int m_CntAnim;//�A�j���[�V�����̑���
	int m_PatternAnim;//�A�j���[�V�����̕�����

	
	D3DXVECTOR3 m_move;//�ړ��ϐ�
	int m_nIntervalAttack;//�U���Ԋu�ϐ�

	int m_nEnemyType;
	int m_nRndPattern;//�p�^�[��

	D3DXVECTOR3 m_PlayerPos;
	D3DXVECTOR3 m_EnemyPos;
};




#endif