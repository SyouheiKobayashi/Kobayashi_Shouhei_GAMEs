//=============================================================================
//
// tutorial処理 [tutorial.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "tutorial.h"			// タイトル
#include "manager.h"		// マネージャー
#include "renderer.h"		// レンダラー
#include "input.h"			// 入力
#include "fade.h"			// フェード
#include "camera.h"			// カメラ
#include "block.h"			// ブロック
#include "3dobject.h"		// 3D背景オブジェクト
#include "UI.h"				// ui
#include "floor.h"			// 床
#include "wall.h"			// 壁
#include "effect.h"			// エフェクト
#include "sound.h"			// サウンド

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorial::Init(void)
{
	CUI::Load(CManager::MODE_TUTORIAL);	//  Uiの読み込み

	//	UIの生成
	CUI::CreateMode(CManager::MODE_TUTORIAL);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	CUI::Unload();				// Uiの読み込み
	CUI::Unload();				//  Uiの開放
	CScene::ReleaseMode();		//	モード終了
}

//=============================================================================
// 更新処理
//=============================================================================
void CTutorial::Update(void)
{
	CSound *pSound = CManager::GetSound();			//	サウンドの取得
	if (CFade::GetFade() == CFade::FADE_NONE)
	{// フェードしていない状態
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true )
		{// キーボード（ENTER）を入力したら
			CFade::Create(CManager::MODE_GAME, CFade::FADE_OUT, 3);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_PRESS);	//	決定音
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}