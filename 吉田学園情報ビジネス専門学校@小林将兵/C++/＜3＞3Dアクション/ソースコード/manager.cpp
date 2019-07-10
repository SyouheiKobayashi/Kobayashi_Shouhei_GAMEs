//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					マネージャー処理 [manager.cpp]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "manager.h"
#include "scene.h"
#include "fade.h"
#include "sound.h"
#include "title.h"
#include "timeCharge.h"
#include "game.h"
#include "result.h"
#include "ranking.h"

//=====================================================================
//							静的メンバ変数
//※オブジェクトに属するメンバ変数ではなく、クラスに属するメンバ変数
//※アクセス制限が設定されていることを除けば、グローバル変数と同じもの
//=====================================================================
CRenderer*CManager::m_pRenderer = NULL;
CFade *CManager::m_pFade = NULL;
CSound *CManager::m_pSound = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputXPad *CManager::m_pInputXPad = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CManager::STATE_MODE CManager::m_modeNow = CManager::MODE_TITLE;//初期に開始するモード
CTitle *CManager::m_pTitle = NULL;
CTimeCharge *CManager::m_pTimeCharge = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CRanking  *CManager::m_pRanking = NULL;
int CManager::m_nChargeTime = 0;
int CManager::m_nRank[5] = {0,0,0,0,0};
int CManager::m_nTotalScore = 0;
bool CManager::m_bResult = false;

//==============================================
//					コンストラクタ
//※クラスのインスタンス生成時に実行されるメソッド、クラスのメンバ変数を初期化
//==============================================
CManager::CManager()
{

}

//==============================================
//					デストラクタ
//※オブジェクトを消去する際に呼び出されて後処理などを行なう関数
//==============================================
CManager::~CManager()
{

}

//==============================================
//					初期化
//==============================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	m_nChargeTime = 0;
	
	m_pRenderer = new CRenderer;//レンダラー
	if (m_pRenderer != NULL)
	{
		if (FAILED(m_pRenderer->Init(hWnd, true))) //true(縮小スクリーン) / false(フルスクリーン)
		{
			return -1;
		}
	}

	
	if (m_pFade == NULL)//フェード
	{
		m_pFade = CFade::Create();//フェードの生成
	}

	
	if (m_pSound == NULL)//サウンド
	{
		m_pSound = CSound::Create(hWnd);
	}

	
	m_pInputKeyboard = new CInputKeyboard;//キーボード
	if (m_pInputKeyboard != NULL)
	{
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	m_pInputXPad = new CInputXPad;//コントローラー
	if (m_pInputXPad != NULL)
	{
		m_pInputXPad->Init(hInstance,  hWnd);
		
	}

	m_pInputMouse = new CInputMouse;//マウス
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Init(hInstance, hWnd);
	}

	//初期モード
	SetStateMode(m_modeNow);//静的メンバ変数で設定した値が入る

	return S_OK;
}
//==============================================
//					終了
//==============================================
void CManager::Uninit(void)
{
	switch (m_modeNow)//現在の状態
	{
	case MODE_TITLE://タイトルの終了
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
	case MODE_CHARGETIME://制限時間処理の終了
		if (m_pTimeCharge != NULL)
		{
			m_pTimeCharge->Uninit();
			delete m_pTimeCharge;
			m_pTimeCharge = NULL;
		}
		break;
	case MODE_GAME://ゲームの終了
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT://リザルトの終了
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	case MODE_RANKING://ランキングの終了
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();
			delete m_pRanking;
			m_pRanking = NULL;
		}
		break;
	}

	//マウスの終了
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	//コントローラーの終了
	if (m_pInputXPad != NULL)
	{
		m_pInputXPad->Uninit();
		delete m_pInputXPad;
		m_pInputXPad = NULL;
	}

	//キーボードの終了
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//サウンドの終了
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//フェードの終了
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}

	// レンダリングの終了
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//作成・使用したデータの全削除
	if (m_pRenderer != NULL)
	{
		CScene::ReleaseAll();
	}

	
}
//==============================================
//					更新
//==============================================
void CManager::Update(void)
{
	switch (m_modeNow)//現在の状態
	{
	case MODE_TITLE://タイトルの更新
		m_pTitle->Update();
		break;
	case MODE_CHARGETIME://制限時間処理の更新
		m_pTimeCharge->Update();
		break;
	case MODE_GAME://ゲームの更新
		m_pGame->Update();
		break;
	case MODE_RESULT://リザルトの更新
		m_pResult->Update();
		break;
	case MODE_RANKING://ランキングの更新
		m_pRanking->Update();
		break;

	}

	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();//レンダラーの更新
	}

	m_pFade->Update();//フェードの更新

	m_pInputKeyboard->Update();//キーボードの更新

	m_pInputXPad->Update();//コントローラーの更新

	m_pInputMouse->Update();//マウスの更新


}
//==============================================
//					描画
//==============================================
void CManager::Draw(void)
{
	switch (m_modeNow)//現在の状態
	{
	case MODE_TITLE://タイトルの描画
		m_pTitle->Draw();
		break;
	case MODE_CHARGETIME://制限時間処理の描画
		m_pTimeCharge->Draw();
		break;
	case MODE_GAME://ゲームの描画
		m_pGame->Draw();
		break;
	case MODE_RESULT://リザルトの描画
		m_pResult->Draw();
		break;
	case MODE_RANKING://ランキングの描画
		m_pRanking->Draw();
		break;
	}

	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();//レンダラーの更新
	}

}

//==============================================
//			モードの情報の取得・反映
//==============================================
void CManager::SetStateMode(STATE_MODE state_mode)
{
	switch (m_modeNow)//現在の状態
	{
	case MODE_TITLE://タイトルの終了
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
	case MODE_CHARGETIME://制限時間処理の終了
		if (m_pTimeCharge != NULL)
		{
			m_nChargeTime = m_pTimeCharge->GetChargeTime();
			m_pTimeCharge->Uninit();
			delete m_pTimeCharge;
			m_pTimeCharge = NULL;
		}
		break;
	case MODE_GAME://ゲームの終了
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT://リザルトの終了
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	case MODE_RANKING://ランキングの終了
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();
			delete m_pRanking;
			m_pRanking = NULL;
			m_nTotalScore = 0;//ここでスコアリセット

		}
		break;
	}

	switch (state_mode)//m_modeNow(現在のモードの情報)を消した後にstate_mode(新しいモードの情報)を初期化・生成させる
	{
	case MODE_TITLE://タイトルの生成
		if (m_pTitle == NULL)
		{
			m_nChargeTime = 0;
			m_nTotalScore = 0;//ここでスコアリセット
			m_pTitle = CTitle::Create();
		}
		break;
	case MODE_CHARGETIME://制限時間処理の生成
		if (m_pTimeCharge == NULL)
		{
			m_pTimeCharge = CTimeCharge::Create();
		}
		break;

	case MODE_GAME://ゲームの生成
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
		}
		break;
	case MODE_RESULT://リザルトの生成
		if (m_pResult == NULL)
		{
			m_pResult = CResult::Create();
		}
		break;
	case MODE_RANKING://ランキングの生成
		if (m_pGame == NULL)
		{
			m_pRanking = CRanking::Create();
		}
		break;
	}
	m_modeNow = state_mode; //state_mode(新しいモードの情報)が入る
}

//==============================================
//			次のステージに引き継ぐために
//==============================================
void CManager::SetChargeTime(int nChargeTime)
{
	m_nChargeTime = nChargeTime;
}

//==============================================
//				リザルト結果
//==============================================
void CManager::SetResult(bool bResultType)
{
	m_bResult = bResultType;
}

