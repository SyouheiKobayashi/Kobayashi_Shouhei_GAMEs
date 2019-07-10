//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �e�E�o���b�g���� [bullet.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
#include "scene2D.h"

#define MAX_B_TEX	(2)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �e�E�o���b�gCLASS(<scene2D>�̔h���N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CBullet : public CScene2D
{
public:
	typedef enum//�A�N�V�����ɂ��G�̒e�������������߂ɕK�v�ȏ���
	{
		NONE = 0,
		PLAYER,
		ENEMY
	}TYPE;

	typedef enum//�e�ˏo�̃o���G�[�V�����p�^�[��
	{
		PATTERN_PLAYER = 0,
		PATTERN01,
		PATTERN02,
		PATTERN03,
		PATTERN04,
		PATTERN05,
		PATTERN06,
		PATTERN07,
		PATTERN08,
		PATTERN09,
		PATTERN_ALL
	}BULLET_PATTERN;

	CBullet();
	~CBullet();
	static HRESULT Load(void);//�e�N�X�`����K�v���ǂݍ���
	static void UnLoad(void);//�g�p���Ă���e�N�X�`���𑼂̏����ŏ������Ȃ��悤�ɂ���
	static CBullet *Create(D3DXVECTOR3 pos, int size, OBJ_TYPE ObjType, TYPE type,int nTexType, BULLET_PATTERN pattern);//�e�̐���(�ʒu���,�e�̔���)

	HRESULT Init(BULLET_PATTERN pattern);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBulletType(OBJ_TYPE ObjType, TYPE type);//�N�̒e���𔻕�

	int GetType(void) { return m_nRType; }

	bool GetPauseFlag(void) { return m_bPause; }//���݂̃t���O�̎擾

	

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_B_TEX];//���L�e�N�X�`���ւ̃|�C���^
	CScene2D *m_apScene2D[MAX_B_TEX];
	D3DXVECTOR3 m_move;//�ړ�����
	OBJ_TYPE m_BulletType;//�N�̒e���𔻕�

	int m_nRType;
	bool m_bPause;

	int m_nBulletPattern;

	D3DXVECTOR3 m_PlayerPos;
	D3DXVECTOR3 m_EnemyPos;
	bool m_Die;
};

#endif