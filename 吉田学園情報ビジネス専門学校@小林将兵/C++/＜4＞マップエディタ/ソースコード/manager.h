//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�}�l�[�W���[���� [manager.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "renderer.h"
#include "input.h"

//==============================================
//�O���錾
//���v���O���}�����S�Ȓ�`��^���Ă��Ȃ��v���O�����v�f��\���V���{���̎��O�錾�̂��Ƃł���B �ϐ��A�֐��A�^�Ȃǂɑ΂���V���{�����܂܂��B
//==============================================
class CSound;
class CFade;
class CGame;

//==============================================
//�}�l�[�W���[(�����I�v���O����)
//==============================================
class CManager
{
public:
	typedef enum//���[�h�̎��
	{
		MODE_GAME = 0,	//�Q�[��
		MODE_MAX		//�ő吔
	}STATE_MODE;

	//�R���X�g���N�^ / �f�X�g���N�^
	CManager();
	~CManager();

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	
	void Uninit(void);											
	void Update(void);											
	void Draw(void);	

	//Get�֐�(�g�p�����ϐ��Ȃǂ̏��𑼂̃v���O�����Ŏg�p���鏈��)
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CFade *GetFade(void) { return m_pFade; }								//��ʑJ�ڎ��̈Ó]����
	static CSound *GetSound(void) { return m_pSound; }							//�T�E���h
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }	//�L�[�{�[�h����
	static CInputXPad *GetInputXPad(void) { return m_pInputXPad; }				//�R���g���[���[����
	static CInputMouse *GetInputMouse(void) { return m_pInputMouse; }			//�}�E�X����

	//���[�h�Ɋւ���֘A
	static void SetStateMode(STATE_MODE state_mode);							//���̃��[�h�̏���
	static STATE_MODE GetMode(void) { return m_modeNow; }						//���ݎg�p���Ă��郂�[�h
	static CGame *GetGame(void) { return m_pGame; }								//�Q�[���ň����Ă�����E�����̏W��

private:
	static CRenderer *m_pRenderer;
	static CFade *m_pFade;
	static CSound *m_pSound;
	static CInputKeyboard *m_pInputKeyboard;
	static CInputXPad *m_pInputXPad;
	static CInputMouse *m_pInputMouse;

	//���[�h�Ɋւ���֘A
	static STATE_MODE m_modeNow;	//���݂̃��[�h
	static CGame *m_pGame;			//�Q�[��
};

#endif

