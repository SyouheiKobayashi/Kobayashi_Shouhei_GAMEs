//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// UI���� [UI.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _UI_H_
#define _UI_H_
#include "main.h"
#include "scene2D.h"

#define MAX_UI	(21)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ UICLASS(<scene2D>�̔h���N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CUI : public CScene2D
{
public:
	CUI();
	~CUI();
	static HRESULT Load(void);//�e�N�X�`����K�v���ǂݍ���
	static void UnLoad(void);//�g�p���Ă���e�N�X�`���𑼂̏����ŏ������Ȃ��悤�ɂ���
	static CUI *Create(int nUI_NUM,int nPOS_X, int nPOS_Y,int nSIZE_X, int nSIZE_Y);

	HRESULT Init(int nUI_NUM);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetActionUI(int nSelectActionNo,int nMode,int UI_TEX);//�A�N�V�����I�����̏���
	

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_UI];//���L�e�N�X�`���ւ̃|�C���^
	

	//! <�|���S���̃A�j���[�V�����Ɋւ���ϐ�>
	int m_nType;
	int m_CntAnim;//�A�j���[�V�����̑���
	int m_PatternAnim;//�A�j���[�V�����̕�����

	bool m_bTimeCheck;

	float m_fCnt;//�Q�[���I�[�o�[UI�̕s������������
};




#endif