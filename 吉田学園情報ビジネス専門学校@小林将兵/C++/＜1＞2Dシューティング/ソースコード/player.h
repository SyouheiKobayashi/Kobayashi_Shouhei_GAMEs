//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// 2D�|���S������ [player.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "scene2D.h"

class CBullet;
class CAction;
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �v���C���[CLASS(<scene2D>�̔h���N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CPlayer : public CScene2D
{
public:
	typedef enum
	{
		CURE = 0,//���ȉ�
		ADD_TIME,//�^�C�����Z
		SICKLE//�U���Z
	}MODE;


	CPlayer();
	~CPlayer();
	static HRESULT Load(void);//�e�N�X�`����K�v���ǂݍ���
	static void UnLoad(void);//�g�p���Ă���e�N�X�`���𑼂̏����ŏ������Ȃ��悤�ɂ���
	static CPlayer *Create(float fWIDTH,float fHEIGHT,int nLife);//(���T�C�Y,�c�T�C�Y)

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBloodLife(int nSetBloodLife);
	int GetBloodLife(void) { return m_nBloodLife; }

	int GetMode(void) { return m_nActionMode; }//���݂̏�Ԃ��擾

	bool GetUse01(void) { return m_bUse01; }//�g�p�\�󋵂̊m�F
	bool GetUse02(void) { return m_bUse02; }//�g�p�\�󋵂̊m�F
	bool GetUse03(void) { return m_bUse03; }//�g�p�\�󋵂̊m�F

	
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//���L�e�N�X�`���ւ̃|�C���^
	static CAction *m_pAction;

	D3DXVECTOR3 m_Move;
	//! <�|���S���̃A�j���[�V�����Ɋւ���ϐ�>
	int m_CntAnim;//�A�j���[�V�����̑���
	int m_PatternAnim;//�A�j���[�V�����̕�����
	int m_nBloodLife;
	int m_nActionPos;//�A�N�V�����g�p����pos���Z����

	int m_nActionMode;//���݂̏��

	MODE m_mode;

	bool m_bUse01, m_bUse02, m_bUse03,m_bTimeCheck;//�g�p�\���ǂ���


};




#endif