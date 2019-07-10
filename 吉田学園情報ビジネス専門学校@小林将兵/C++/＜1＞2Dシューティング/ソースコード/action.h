//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �A�N�V�������� [action.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _ACTION_H_
#define _ACTION_H_
#include "main.h"
#include "scene2D.h"

#define ACTION_TEX	(1)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �A�N�V����CLASS(<scene2D>�̔h���N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CAction : public CScene2D
{
public:
	

	CAction();
	~CAction();
	static HRESULT Load(void);//�e�N�X�`����K�v���ǂݍ���
	static void UnLoad(void);//�g�p���Ă���e�N�X�`���𑼂̏����ŏ������Ȃ��悤�ɂ���
	static CAction *Create(D3DXVECTOR3 pos,OBJ_TYPE ObjType);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBulletType(OBJ_TYPE ObjType);//�N�̒e���𔻕�
	

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[ACTION_TEX];//���L�e�N�X�`���ւ̃|�C���^
	CScene2D *m_apScene2D[ACTION_TEX];
	D3DXVECTOR3 m_move;//�ړ�����
	OBJ_TYPE m_ActionType;//�N�̒e���𔻕�

	int m_nActionTime;//�\������

	float m_fAngle;//���݂̊p�x
	float m_fActionAngle;//�������@�ɑ΂��ē����p�x
	float m_fRange;//���@�Ɗ��̋���

	

};

#endif