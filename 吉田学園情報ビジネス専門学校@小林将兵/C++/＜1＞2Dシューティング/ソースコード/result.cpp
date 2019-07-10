//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// タイトル処理 [result.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "result.h"
#include "manager.h"
#include "sound.h"
#include "scene2D.h"
#include "fade.h"
#include "bg.h"
#include "UI.h"
#include "number.h"
#include "score.h"
#include "game.h"


//静的メンバ変数
CResult CResult::*m_pGame = 0;
CBG *CResult::m_pBG = NULL;
CUI *CResult::m_pUI = NULL;
CNumber *CResult::m_pNumber = NULL;
CScore *CResult::m_pScore = NULL;

//=============================================================================
//+ ゲームのコンストラクタ
//=============================================================================
CResult::CResult()
{

}
//=============================================================================
//+ ゲームのデストラクタ
//=============================================================================
CResult::~CResult()
{

}

CResult *CResult::Create(void)
{
	CResult *pResult;
	pResult = new CResult;
	pResult->Init();
	return pResult;
}
//=============================================================================
//+ ゲームの初期化処理
//=============================================================================
HRESULT CResult::Init(void)
{
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_RANKING);
	
	//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
	//? 背景のテクスチャ生成
	CBG::Load();
	//? UIのテクスチャ生成
	CUI::Load();
	//? 数字のtex生成
	CNumber::Load();

	
	//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
	//! 背景の生成↓
	m_pBG = CBG::Create();
	//! UIの生成↓
	m_pUI = CUI::Create(10,620,115,400,140);
	//! スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(500, 200, 0),CScore::RANKING_SCORE);

	//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

	return S_OK;
}
//=============================================================================
//+ ゲームの終了処理
//=============================================================================
void CResult::Uninit(void)
{
	//!+ <生成した逆順で破棄していく↓>
	//? 数字のtex破棄
	CNumber::UnLoad();
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
void CResult::Update(void)
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
			CManager::GetFade()->SetFade(CManager::MODE_TITLE);
			}
	}

}
//=============================================================================
//+ ゲームの描画処理
//=============================================================================
void CResult::Draw(void)
{

}

