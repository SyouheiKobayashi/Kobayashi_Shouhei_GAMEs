//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�f�o�b�N���O���� [debugLog.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _DEBUG_H_
#define _DEBUG_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"

//==============================================
//�}�N����`
//==============================================
#define MAX_WORD	(1024)//�ő啶����

//==============================================
//�h���Ȃ� �� �f�o�b�N���O
//==============================================
class CDebug
{
public:
	//�R���X�g���N�^ / �f�X�g���N�^
	CDebug();
	~CDebug();

	//����
	static CDebug *Create(void);

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	void Init(void);
	void Uninit(void);
	static void DebugLog(char * fmt,...);//���̊֐����g�p���ĉ�ʏ�Ƀf�o�b�N�\�����s��
	static void Draw(void);

	
private:
	static LPD3DXFONT m_pFont;
	static char m_aStr[MAX_WORD];//������̕ۊ�
	
};

#endif