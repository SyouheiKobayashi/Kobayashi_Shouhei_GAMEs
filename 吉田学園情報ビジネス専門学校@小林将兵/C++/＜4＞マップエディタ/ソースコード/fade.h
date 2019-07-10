//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�t�F�[�h���� [fade.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _FADE_H_
#define _FADE_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "manager.h"

//==============================================
//�}�l�[�W���[�Ǘ� �� �t�F�[�h(��ʈÓ])
//==============================================
class CFade : public CManager
{
public:
	typedef enum
	{
		FADE_NONE = 0,		//�g�p���ĂȂ����
		FADE_IN,			//��ʂ������
		FADE_OUT,			//��ʂ����X�ɏ�����
		FADE_MAX
	} FADE;

	//�R���X�g���N�^ / �f�X�g���N�^
	CFade();
	~CFade();

	//����
	static CFade *Create(void);

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//Get�֐�(���g�ň��������𑼂̃v���O�����Ŏg�p���鏈��)
	static FADE GetFade(void) { return m_fade; }

	//Set�֐�(�������̐��l�A�f�[�^�����炢�K�� / ��ɔh��(�q)�N���X�Ŏg�p)
	void SetFade(STATE_MODE nextMode);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	static FADE m_fade;//���݂̃t�F�[�h��Ԃ��L��
	STATE_MODE m_NextMode;//���̃��[�h
	D3DXCOLOR m_Color;//�t�F�[�h�̐F

};




#endif