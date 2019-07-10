//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					マネージャー処理 [manager.h]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "renderer.h"
#include "input.h"

#define OBJ_CREATE	(50)


//==============================================
//					前方宣言
//※プログラマが完全な定義を与えていないプログラム要素を表すシンボルの事前宣言のことである。 変数、関数、型などに対するシンボルが含まれる。
//==============================================
class CSound;
class CFade;
class CTitle;
class CTimeCharge;
class CGame;
class CResult;
class CRanking;

//==============================================
//		マネージャー(統括的プログラム)
//==============================================
class CManager
{
public:
	typedef enum//モードの種類
	{
		MODE_TITLE = 0,	//タイトル
		MODE_CHARGETIME,//制限時間を決める
		MODE_GAME,		//ゲーム
		MODE_RESULT,	//リザルト
		MODE_RANKING,	//ランキング
		MODE_MAX		//最大数
	}STATE_MODE;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				コンストラクタ・デストラクタ
	// @   @   @   @   @   @   @   @   @   @   @   @
	CManager();
	~CManager();

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					基盤関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	
	void Uninit(void);											
	void Update(void);											
	void Draw(void);	

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CFade *GetFade(void) { return m_pFade; }								//画面遷移時の暗転処理
	static CSound *GetSound(void) { return m_pSound; }							//サウンド

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				入力に関する処理
	// @   @   @   @   @   @   @   @   @   @   @   @
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }	//キーボード入力
	static CInputXPad *GetInputXPad(void) { return m_pInputXPad; }				//コントローラー入力
	static CInputMouse *GetInputMouse(void) { return m_pInputMouse; }			//マウス入力

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				モードに関する処理
	// @   @   @   @   @   @   @   @   @   @   @   @
	static void SetStateMode(STATE_MODE state_mode);			//次のモードの準備
	static STATE_MODE GetMode(void) { return m_modeNow; }						
	static CTitle *GetTitle(void) { return m_pTitle; }	
	static CTimeCharge *GetTimeCharge(void) { return m_pTimeCharge; }
	static CGame *GetGame(void) { return m_pGame; }								
	static CResult *GetResul(void) { return m_pResult; }							
	static CRanking *GetRanking(void) { return m_pRanking; }		

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				時間関係に関する処理
	// @   @   @   @   @   @   @   @   @   @   @   @
	static int GetChargeTime(void) { return m_nChargeTime; }
	static void SetChargeTime(int nChargeTime);//次のステージに引き継ぐために

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				スコア・ランキングに関する関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	static int m_nRank[5];//順位分配列用意
	//static void SetAddTotalScore(int nScore) { m_nTotalScore += nScore;}//合計スコアを加算していく
	//static int GetTotalScore(void) { return m_nTotalScore;}//合計スコア
	static int GetTotalScore(void) { return m_nChargeTime; }//合計タイム

	static bool GetResult() { return m_bResult; }
	static void SetResult(bool bResultType);

private:
	static CRenderer *m_pRenderer;
	static CFade *m_pFade;
	static CSound *m_pSound;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				入力に関する変数
	// @   @   @   @   @   @   @   @   @   @   @   @
	static CInputKeyboard *m_pInputKeyboard;
	static CInputXPad *m_pInputXPad;
	static CInputMouse *m_pInputMouse;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				モードに関する変数
	// @   @   @   @   @   @   @   @   @   @   @   @
	static STATE_MODE m_modeNow;	//現在のモード
	static CTitle *m_pTitle;
	static CTimeCharge *m_pTimeCharge;
	static CGame *m_pGame;			
	static CResult *m_pResult;
	static CRanking *m_pRanking;	

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				時間関係に関する変数
	// @   @   @   @   @   @   @   @   @   @   @   @
	static int m_nChargeTime;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				スコア・ランキングに関する変数
	// @   @   @   @   @   @   @   @   @   @   @   @
	static int m_nTotalScore;//合計スコア

	static bool m_bResult;

};

#endif

