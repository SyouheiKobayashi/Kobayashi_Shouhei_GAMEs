//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// マネージャー処理 [manager.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
#include "renderer.h"
#include "input.h"


//クラスの呼び出し
class CSound;
class CFade;
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CScore;
//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ マネージャーCLASS(基本クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CManager
{
public:
	//モード種類
	typedef enum
	{
		MODE_TITLE = 0,//タイトル
		MODE_TUTORIAL,//タイトル
		MODE_GAME,//ゲーム本編
		MODE_RESULT,//リザルト
		MODE_MAX//最大遷移数
	}MODE;

	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);//画面サイズ
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
	static int nRank[5];//現在の順位
	static int m_LastScore;
private:
	static MODE m_Mode;//現在のゲームモード

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

