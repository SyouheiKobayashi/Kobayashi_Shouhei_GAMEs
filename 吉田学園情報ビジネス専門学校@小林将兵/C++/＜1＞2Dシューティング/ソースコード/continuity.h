//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �ꎞ��~���� [continuity.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _CONTINUITY_H_
#define _CONTINUITY_H_
#include "main.h"
#include "scene2D.h"

#define CONTINUITY_TEX	(5)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ UICLASS(<scene2D>�̔h���N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CContinuity : public CScene2D
{
public:
	typedef enum
	{
		CONTINUITY_BG01 = 0,
		CONTINUITY_BG02,
		CONTINUITY_BG03,
		CONTINUITY00,//���A
		CONTINUITY01,//���U���g��
		
	}MENU;

	CContinuity();
	~CContinuity();
	static HRESULT Load(void);//�e�N�X�`����K�v���ǂݍ���
	static void UnLoad(void);//�g�p���Ă���e�N�X�`���𑼂̏����ŏ������Ȃ��悤�ɂ���
	static CContinuity *Create(int nUI_NUM, int nPOS_X, int nPOS_Y, int nSIZE_X, int nSIZE_Y);

	HRESULT Init(int nUI_NUM);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetContinuityMode(void) { return m_nContinuityMode; }
	bool GetContinuityFlag(void) { return m_ContinuityFlag; }

	bool GetGiveUpFlag(void) { return m_GiveUpFlag; }
		
	//void SetActionUI(int nSelectActionNo, int nMode, int UI_TEX);//�A�N�V�����I�����̏���

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[CONTINUITY_TEX];//���L�e�N�X�`���ւ̃|�C���^


												 //! <�|���S���̃A�j���[�V�����Ɋւ���ϐ�>
	int m_nType;
	int m_nContinuityMode;
	bool m_ContinuityFlag;
	bool m_GiveUpFlag;
	//int m_CntAnim;//�A�j���[�V�����̑���
	//int m_PatternAnim;//�A�j���[�V�����̕�����
};




#endif