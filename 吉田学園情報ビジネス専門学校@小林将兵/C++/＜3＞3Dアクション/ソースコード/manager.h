//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					�}�l�[�W���[���� [manager.h]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "renderer.h"
#include "input.h"

#define OBJ_CREATE	(50)


//==============================================
//					�O���錾
//���v���O���}�����S�Ȓ�`��^���Ă��Ȃ��v���O�����v�f��\���V���{���̎��O�錾�̂��Ƃł���B �ϐ��A�֐��A�^�Ȃǂɑ΂���V���{�����܂܂��B
//==============================================
class CSound;
class CFade;
class CTitle;
class CTimeCharge;
class CGame;
class CResult;
class CRanking;

//==============================================
//		�}�l�[�W���[(�����I�v���O����)
//==============================================
class CManager
{
public:
	typedef enum//���[�h�̎��
	{
		MODE_TITLE = 0,	//�^�C�g��
		MODE_CHARGETIME,//�������Ԃ����߂�
		MODE_GAME,		//�Q�[��
		MODE_RESULT,	//���U���g
		MODE_RANKING,	//�����L���O
		MODE_MAX		//�ő吔
	}STATE_MODE;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				�R���X�g���N�^�E�f�X�g���N�^
	// @   @   @   @   @   @   @   @   @   @   @   @
	CManager();
	~CManager();

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					��Պ֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	
	void Uninit(void);											
	void Update(void);											
	void Draw(void);	

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CFade *GetFade(void) { return m_pFade; }								//��ʑJ�ڎ��̈Ó]����
	static CSound *GetSound(void) { return m_pSound; }							//�T�E���h

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				���͂Ɋւ��鏈��
	// @   @   @   @   @   @   @   @   @   @   @   @
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }	//�L�[�{�[�h����
	static CInputXPad *GetInputXPad(void) { return m_pInputXPad; }				//�R���g���[���[����
	static CInputMouse *GetInputMouse(void) { return m_pInputMouse; }			//�}�E�X����

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				���[�h�Ɋւ��鏈��
	// @   @   @   @   @   @   @   @   @   @   @   @
	static void SetStateMode(STATE_MODE state_mode);			//���̃��[�h�̏���
	static STATE_MODE GetMode(void) { return m_modeNow; }						
	static CTitle *GetTitle(void) { return m_pTitle; }	
	static CTimeCharge *GetTimeCharge(void) { return m_pTimeCharge; }
	static CGame *GetGame(void) { return m_pGame; }								
	static CResult *GetResul(void) { return m_pResult; }							
	static CRanking *GetRanking(void) { return m_pRanking; }		

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				���Ԋ֌W�Ɋւ��鏈��
	// @   @   @   @   @   @   @   @   @   @   @   @
	static int GetChargeTime(void) { return m_nChargeTime; }
	static void SetChargeTime(int nChargeTime);//���̃X�e�[�W�Ɉ����p�����߂�

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				�X�R�A�E�����L���O�Ɋւ���֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	static int m_nRank[5];//���ʕ��z��p��
	//static void SetAddTotalScore(int nScore) { m_nTotalScore += nScore;}//���v�X�R�A�����Z���Ă���
	//static int GetTotalScore(void) { return m_nTotalScore;}//���v�X�R�A
	static int GetTotalScore(void) { return m_nChargeTime; }//���v�^�C��

	static bool GetResult() { return m_bResult; }
	static void SetResult(bool bResultType);

private:
	static CRenderer *m_pRenderer;
	static CFade *m_pFade;
	static CSound *m_pSound;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				���͂Ɋւ���ϐ�
	// @   @   @   @   @   @   @   @   @   @   @   @
	static CInputKeyboard *m_pInputKeyboard;
	static CInputXPad *m_pInputXPad;
	static CInputMouse *m_pInputMouse;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				���[�h�Ɋւ���ϐ�
	// @   @   @   @   @   @   @   @   @   @   @   @
	static STATE_MODE m_modeNow;	//���݂̃��[�h
	static CTitle *m_pTitle;
	static CTimeCharge *m_pTimeCharge;
	static CGame *m_pGame;			
	static CResult *m_pResult;
	static CRanking *m_pRanking;	

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				���Ԋ֌W�Ɋւ���ϐ�
	// @   @   @   @   @   @   @   @   @   @   @   @
	static int m_nChargeTime;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				�X�R�A�E�����L���O�Ɋւ���ϐ�
	// @   @   @   @   @   @   @   @   @   @   @   @
	static int m_nTotalScore;//���v�X�R�A

	static bool m_bResult;

};

#endif

