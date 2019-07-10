//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �t�F�[�h���� [fade.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "manager.h"

//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �t�F�[�hCLASS(�}�l�[�W���h��)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CFade : public CManager
{
public:
	typedef enum
	{
		FADE_NONE = 0,// �g�p���ĂȂ����
		FADE_IN,// �t�F�[�h�C�����
		FADE_OUT,// �t�F�[�h�A�E�g���
		FADE_MAX
	} FADE;

	CFade();
	~CFade();

	static CFade *Create(void);//�t�F�[�h�̐�������

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetFade(MODE modeNext);
	static FADE GetFade(void) { return m_fade; }


private:
	//! �����o�ϐ���
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	 static FADE m_fade;					// ���݂̃t�F�[�h��Ԃ��L��
	MODE m_modeNext;				// ���̃��[�h
	D3DXCOLOR m_colorFade;			// �t�F�[�h�̐F

};




#endif