//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//マネージャー処理 [manager.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "renderer.h"
#include "input.h"

//==============================================
//前方宣言
//※プログラマが完全な定義を与えていないプログラム要素を表すシンボルの事前宣言のことである。 変数、関数、型などに対するシンボルが含まれる。
//==============================================
class CSound;
class CFade;
class CGame;

//==============================================
//マネージャー(統括的プログラム)
//==============================================
class CManager
{
public:
	typedef enum//モードの種類
	{
		MODE_GAME = 0,	//ゲーム
		MODE_MAX		//最大数
	}STATE_MODE;

	//コンストラクタ / デストラクタ
	CManager();
	~CManager();

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	
	void Uninit(void);											
	void Update(void);											
	void Draw(void);	

	//Get関数(使用した変数などの情報を他のプログラムで使用する処理)
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CFade *GetFade(void) { return m_pFade; }								//画面遷移時の暗転処理
	static CSound *GetSound(void) { return m_pSound; }							//サウンド
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }	//キーボード入力
	static CInputXPad *GetInputXPad(void) { return m_pInputXPad; }				//コントローラー入力
	static CInputMouse *GetInputMouse(void) { return m_pInputMouse; }			//マウス入力

	//モードに関する関連
	static void SetStateMode(STATE_MODE state_mode);							//次のモードの準備
	static STATE_MODE GetMode(void) { return m_modeNow; }						//現在使用しているモード
	static CGame *GetGame(void) { return m_pGame; }								//ゲームで扱っている情報・処理の集積

private:
	static CRenderer *m_pRenderer;
	static CFade *m_pFade;
	static CSound *m_pSound;
	static CInputKeyboard *m_pInputKeyboard;
	static CInputXPad *m_pInputXPad;
	static CInputMouse *m_pInputMouse;

	//モードに関する関連
	static STATE_MODE m_modeNow;	//現在のモード
	static CGame *m_pGame;			//ゲーム
};

#endif

