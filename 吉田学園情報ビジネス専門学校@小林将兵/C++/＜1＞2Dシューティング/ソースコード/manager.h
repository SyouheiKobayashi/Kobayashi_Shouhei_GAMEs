//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �}�l�[�W���[���� [manager.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
#include "renderer.h"
#include "input.h"


//�N���X�̌Ăяo��
class CSound;
class CFade;
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CScore;
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �}�l�[�W���[CLASS(��{�N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CManager
{
public:
	//���[�h���
	typedef enum
	{
		MODE_TITLE = 0,//�^�C�g��
		MODE_TUTORIAL,//�^�C�g��
		MODE_GAME,//�Q�[���{��
		MODE_RESULT,//���U���g
		MODE_MAX//�ő�J�ڐ�
	}MODE;

	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);//��ʃT�C�Y
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetMode(MODE mode);

	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CInputXPad *GetInputXPad(void) { return m_pInputXPad; }
	static CSound *GetSound(void) { return m_pSound; }
	static CFade *GetFade(void) { return m_pFade; }
	static CGame *GetGame(void) { return m_pGame; }
	static MODE GetMode(void) { return m_Mode; }
	
	static int GetLastScore(void) { return m_LastScore; }
	static void SetLastScore(int nScore) { m_LastScore = nScore; }
	static int nRank[5];//���݂̏���
	static int m_LastScore;
private:
	static MODE m_Mode;//���݂̃Q�[�����[�h

	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	static CInputXPad *m_pInputXPad;
	static CSound *m_pSound;
	static CFade *m_pFade;
	static CTitle *m_pTitle;
	static CTutorial *m_pTutorial;
	static CGame *m_pGame;
	static CResult *m_pResult;

	
};

#endif

