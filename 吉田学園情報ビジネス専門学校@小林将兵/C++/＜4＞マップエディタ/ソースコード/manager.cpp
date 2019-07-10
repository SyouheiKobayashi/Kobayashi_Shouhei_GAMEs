//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//マネージャー処理 [manager.cpp]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "manager.h"
#include "scene.h"
#include "fade.h"
//#include "sound.h"
#include "game.h"

//=====================================================================
//静的メンバ変数
//※オブジェクトに属するメンバ変数ではなく、クラスに属するメンバ変数
//※アクセス制限が設定されていることを除けば、グローバル変数と同じもの
//=====================================================================
CRenderer*CManager::m_pRenderer = NULL;
CFade *CManager::m_pFade = NULL;
//CSound *CManager::m_pSound = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputXPad *CManager::m_pInputXPad = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;

CManager::STATE_MODE CManager::m_modeNow = CManager::MODE_GAME;//初期のモード
CGame *CManager::m_pGame = NULL;

//==============================================
//コンストラクタ
//※クラスのインスタンス生成時に実行されるメソッド、クラスのメンバ変数を初期化
//==============================================
CManager::CManager()
{

}

//==============================================
//デストラクタ
//※オブジェクトを消去する際に呼び出されて後処理などを行なう関数
//==============================================
CManager::~CManager()
{

}

//==============================================
//初期化
//==============================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//レンダラー
	m_pRenderer = new CRenderer;
	if (m_pRenderer != NULL)
	{
		if (FAILED(m_pRenderer->Init(hWnd, true))) //true(縮小スクリーン) / false(フルスクリーン)
		{
			return -1;
		}
	}

	//フェード
	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create();//フェードの生成
	}

	//サウンド
	/*if (m_pSound == NULL)
	{
		m_pSound = CSound::Create(hWnd);
	}*/

	//キーボード
	m_pInputKeyboard = new CInputKeyboard;
	if (m_pInputKeyboard != NULL)
	{
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	//コントローラー
	m_pInputXPad = new CInputXPad;
	if (m_pInputXPad != NULL)
	{
		m_pInputXPad->Init(hInstance,  hWnd);
		
	}

	//マウス
	m_pInputMouse = new CInputMouse;
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Init(hInstance, hWnd);
	}

	SetStateMode(m_modeNow);//静的メンバ変数で設定したデータが入る

	return S_OK;
}
//==============================================
//終了
//==============================================
void CManager::Uninit(void)
{
	switch (m_modeNow)//現在の状態
	{
	case MODE_GAME://ゲームの終了
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
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
	/*if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}*/

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
//更新
//==============================================
void CManager::Update(void)
{
	switch (m_modeNow)//現在の状態
	{
	
	case MODE_GAME://ゲームの更新

		m_pGame->Update();

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
//描画
//==============================================
void CManager::Draw(void)
{
	switch (m_modeNow)//現在の状態
	{
	
	case MODE_GAME://ゲームの描画
		m_pGame->Draw();
		break;
	}

	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();//レンダラーの更新
	}

}

//==============================================
//モードの情報の取得・反映
//==============================================
void CManager::SetStateMode(STATE_MODE state_mode)
{
	switch (m_modeNow)//現在の状態
	{
	case MODE_GAME://ゲームであれば終了
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
	}

	switch (state_mode)//m_modeNow(現在のモードの情報)を消した後にstate_mode(新しいモードの情報)を初期化・生成させる
	{
	case MODE_GAME://ゲームの生成
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
		}
		break;
	}
	m_modeNow = state_mode; //state_mode(新しいモードの情報)が入る
}



