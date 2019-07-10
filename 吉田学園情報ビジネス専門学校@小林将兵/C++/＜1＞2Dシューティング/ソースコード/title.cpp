//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// タイトル処理 [title.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "title.h"
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
CTitle CTitle::*m_pGame = 0;
CBG *CTitle::m_pBG = NULL;
CUI *CTitle::m_pUI = NULL;


//=============================================================================
//+ ゲームのコンストラクタ
//=============================================================================
CTitle::CTitle()
{

}
//=============================================================================
//+ ゲームのデストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

CTitle *CTitle::Create(void)
{
	CTitle *pGame;
	pGame = new CTitle;
	pGame->Init();
	return pGame;
}
//=============================================================================
//+ ゲームの初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
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
	m_pUI = CUI::Create(0,620,305,550,300);

	//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

	return S_OK;
}
//=============================================================================
//+ ゲームの終了処理
//=============================================================================
void CTitle::Uninit(void)
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
void CTitle::Update(void)
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
				CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
			}
		}
	}

}
//=============================================================================
//+ ゲームの描画処理
//=============================================================================
void CTitle::Draw(void)
{
	
}
