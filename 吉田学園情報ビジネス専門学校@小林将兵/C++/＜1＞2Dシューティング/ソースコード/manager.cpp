//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// マネージャー処理 [manager.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "manager.h"
#include "sound.h"
#include "scene2D.h"
#include "fade.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"

//静的メンバ変数
CManager::MODE CManager::m_Mode = CManager::MODE_TITLE;//初期画面の設定
CRenderer*CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputXPad *CManager::m_pInputXPad = NULL;
CSound *CManager::m_pSound = NULL;
CFade *CManager::m_pFade = NULL;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
int CManager::nRank[5] = {0,0,0,0,0};
int CManager::m_LastScore = 0;
//=============================================================================
//+ マネージャーのコンストラクタ
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
//+ マネージャーのデストラクタ
//=============================================================================
CManager::~CManager()
{

}
//=============================================================================
//+ マネージャーの初期化
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//! レンダリングクラスの生成
	m_pRenderer = new CRenderer;

	//! レンダリング初期化処理
	if (m_pRenderer != NULL)
	{
		if (FAILED(m_pRenderer->Init(hWnd, TRUE))) //true(縮小画面)	false(フルスクリーン)
		{
			return -1;
		}
	}

	//! インプットクラス(キーボード)の生成
	m_pInputKeyboard = new CInputKeyboard;

	//! インプットクラス(キーボード)の初期化処理
	if (m_pInputKeyboard != NULL)
	{
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	m_pInputXPad = new CInputXPad;
	if (m_pInputXPad != NULL)
	{
		m_pInputXPad->Init(hInstance,  hWnd);

	}
	//! サウンドの生成↓
	m_pSound = CSound::Create(hWnd);
	//! フェードの生成↓
	m_pFade = CFade::Create();

	SetMode(m_Mode);//↑静的メンバ変数の初期設定が入る
	
	return S_OK;
}
//=============================================================================
//+ マネージャーの終了
//=============================================================================
void CManager::Uninit(void)
{
	//!+ <生成した逆順で破棄していく↓>
	switch (m_Mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{//! タイトルの終了処理
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{//! タイトルの終了処理
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{//! ゲームの終了処理
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{//! ゲームの終了処理
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	}

	//! サウンドの終了処理
	m_pSound->Uninit();
	//! フェードの終了処理
	m_pFade->Uninit();

	//! インプットクラス(キーボード)の終了処理
	if (m_pInputXPad != NULL)
	{
		m_pInputXPad->Uninit();
		delete m_pInputXPad;
		m_pInputXPad = NULL;
	}

	//! インプットクラス(キーボード)の終了処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//! ポリゴンの終了処理
	if (m_pRenderer != NULL)
	{
	CScene::ReleaseAll();
	}
	//! レンダリング終了処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}
//=============================================================================
//+ マネージャーの更新
//=============================================================================
void CManager::Update(void)
{
	switch (m_Mode)
	{
	case MODE_TITLE:
		//! タイトル更新処理
		m_pTitle->Update();

		break;
	case MODE_TUTORIAL:
		//! タイトル更新処理
		m_pTutorial->Update();

		break;
	case MODE_GAME:
		//! ゲーム更新処理
		m_pGame->Update();
		
		break;

	case MODE_RESULT:
		//! ゲーム更新処理
		m_pResult->Update();
		break;
	}

	//! インプット(キーボード)更新処理(Sceneの更新処理の情報も含まれている)
	m_pInputKeyboard->Update();

	m_pInputXPad->Update();

	//! レンダリング更新処理(Sceneの更新処理の情報も含まれている)
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	

	//! フェード更新処理
	m_pFade->Update();
}
//=============================================================================
//+ マネージャーの描画
//=============================================================================
void CManager::Draw(void)
{
	switch (m_Mode)
	{
	case MODE_TITLE:
		//! タイトル描画処理
		m_pTitle->Draw();
		break;

	case MODE_TUTORIAL:
		//! タイトル描画処理
		m_pTutorial->Draw();
		break;

	case MODE_GAME:
		//! ゲーム描画処理
		m_pGame->Draw();
		break;

	case MODE_RESULT:
		//! ゲーム描画処理
		m_pResult->Draw();
		break;
	}

	//! レンダリング描画処理(Sceneの更新処理の情報も含まれている)
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
//+ ゲームモード(画面遷移)の設定
//=============================================================================
void CManager::SetMode(MODE mode)
{
	
	switch (m_Mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{//! タイトルの終了処理
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{//! タイトルの終了処理
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{//! ゲームの終了処理
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;

	case MODE_RESULT:
		if (m_pResult != NULL)
		{//! ゲームの終了処理
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	}
	
	switch (mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{//! タイトルの生成
			m_pTitle = CTitle::Create();
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{//! タイトルの生成
			m_pTutorial = CTutorial::Create();
		}
		break;
	case MODE_GAME:
		if (m_pGame == NULL)
		{//! ゲームの生成
			m_pGame = CGame::Create();
		}
		break;
	case MODE_RESULT:
		if (m_pResult == NULL)
		{//! ゲームの生成
			m_pResult = CResult::Create();
		}
		break;
	}
	m_Mode = mode;

}



