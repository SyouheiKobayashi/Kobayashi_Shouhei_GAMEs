//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �ꎞ��~���� [pause.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "main.h"
#include "scene2D.h"

#define PAUSE_TEX	(6)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ UICLASS(<scene2D>�̔h���N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CPause : public CScene2D
{
public:
	typedef enum
	{
		PAUSE_BG = 0,
		PAUSE_BG02,
		PAUSE_BG03,
		PAUSE00,//�Q�[���̍ĊJ
		PAUSE01,//�P����
		PAUSE02,//�^�C�g����
	}MENU;

	CPause();
	~CPause();
	static HRESULT Load(void);//�e�N�X�`����K�v���ǂݍ���
	static void UnLoad(void);//�g�p���Ă���e�N�X�`���𑼂̏����ŏ������Ȃ��悤�ɂ���
	static CPause *Create(int nUI_NUM, int nPOS_X, int nPOS_Y, int nSIZE_X, int nSIZE_Y);

	HRESULT Init(int nUI_NUM);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetPauseMode(void) { return m_nPauseMode; }
	
		
	//void SetActionUI(int nSelectActionNo, int nMode, int UI_TEX);//�A�N�V�����I�����̏���

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[PAUSE_TEX];//���L�e�N�X�`���ւ̃|�C���^

												 //! <�|���S���̃A�j���[�V�����Ɋւ���ϐ�>
	int m_nType;
	int m_nPauseMode;
	bool m_PauseFlag;
	//int m_CntAnim;//�A�j���[�V�����̑���
	//int m_PatternAnim;//�A�j���[�V�����̕�����
};




#endif