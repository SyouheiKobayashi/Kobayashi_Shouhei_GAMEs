//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// タイトル処理 [title.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "tutorial.h"
#include "manager.h"
#include "sound.h"
#include "scene2D.h"
#include "fade.h"
#include "bg.h"
#include "UI.h"
#include "number.h"
#include "score.h"
#include "gauge.h"
#include "life.h"
#include "bloodGauge.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "effect.h"
#include "explosion.h"


//静的メンバ変数
CTutorial CTutorial::*m_pGame = 0;
CBG *CTutorial::m_pBG = NULL;
CUI *CTutorial::m_pUI = NULL;


//=============================================================================
//+ ゲームのコンストラクタ
//=============================================================================
CTutorial::CTutorial()
{

}
//=============================================================================
//+ ゲームのデストラクタ
//=============================================================================
CTutorial::~CTutorial()
{

}

CTutorial *CTutorial::Create(void)
{
	CTutorial *pTutorial;
	pTutorial = new CTutorial;
	pTutorial->Init();
	return pTutorial;
}
//=============================================================================
//+ ゲームの初期化処理
//=============================================================================
HRESULT CTutorial::Init(void)
{
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_TITLE);
	//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
	//? 背景のテクスチャ生成
	CBG::Load();
	//? UIのテクスチャ生成
	CUI::Load();
	
	//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
	//! 背景の生成↓
	m_pBG = CBG::Create();
	//! UIの生成↓
	m_pUI = CUI::Create(20,620,335,550,300);

	//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

	return S_OK;
}
//=============================================================================
//+ ゲームの終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	//!+ <生成した逆順で破棄していく↓>
	//? UIのテクスチャ破棄
	CUI::UnLoad();
	//? 背景のテクスチャ破棄
	CBG::UnLoad();

	//? サウンドの停止
	CSound *pSound = CManager::GetSound();
	pSound->StopSound();

	//! 全てのデータ解放,終了処理
	CScene::ReleaseAll();
}
//=============================================================================
//+ ゲームの更新処理
//=============================================================================
void CTutorial::Update(void)
{
	//キーボードを使用するための処理↓
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//ゲームパッド呼び
	CInputXPad *pInputXPad = CManager::GetInputXPad();

	//ゲームの遷移
	CFade::FADE pFade;
	pFade = CFade::GetFade();
	if (pFade == CFade::FADE_NONE)
	{
		if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			{
				CManager::GetFade()->SetFade(CManager::MODE_GAME);
			}
		}
	}

}
//=============================================================================
//+ ゲームの描画処理
//=============================================================================
void CTutorial::Draw(void)
{
	
}
