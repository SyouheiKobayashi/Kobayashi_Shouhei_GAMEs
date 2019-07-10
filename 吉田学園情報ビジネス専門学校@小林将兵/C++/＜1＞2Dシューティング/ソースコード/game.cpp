//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// ゲーム処理 [game.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "game.h"
#include "sound.h"
#include "manager.h"
#include "scene2D.h"
#include "fade.h"
#include "pause.h"
#include "continuity.h"
#include "bg.h"
#include "UI.h"
#include "number.h"
#include "score.h"
#include "time.h"
#include "gauge.h"
#include "life.h"
#include "bloodGauge.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "action.h"
#include "effect.h"
#include "explosion.h"

//静的メンバ変数
CGame *CGame::m_pGame = 0;
CPause *CGame::m_pPause = 0;
CContinuity *CGame::m_pContinuity = 0;
CBG *CGame::m_pBG = NULL;
CUI *CGame::m_pUI = NULL;
CNumber *CGame::m_pNumber = NULL;
CScore *CGame::m_pScore = NULL;
CTime *CGame::m_pTime = NULL;
CGauge *CGame::m_pGauge = NULL;
CLife *CGame::m_pLife = NULL;
CBloodGauge *CGame::m_pBloodGauge = NULL;
CPlayer *CGame::m_pPlayer = NULL;
CEnemy *CGame::m_pEnemy = NULL;

//! =============================================================================
//! コンストラクタ
//! =============================================================================
CGame::CGame()
{
	m_bBossFlag = false;
	m_nCheck = 0;
	
}

//! =============================================================================
//! デストラクタ
//! =============================================================================
CGame::~CGame()
{

}

//! =============================================================================
//! 生成
//! =============================================================================
CGame *CGame::Create(void)
{
	CGame *pGame;
	pGame = new CGame;
	pGame->Init();
	return pGame;
}

//! =============================================================================
//!　初期化
//! =============================================================================
HRESULT CGame::Init(void)
{
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_GAME);
	m_bPause = false;
	m_bContinuity = false;
	m_nCCC = 0;
	m_bBossFlag = false;
	m_nCheck = 0;
	
	//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
	//? 一時停止のテクスチャ生成
	CPause::Load();
	CContinuity::Load();
	//? 背景のテクスチャ生成
	CBG::Load();
	//? UIのテクスチャ生成
	CUI::Load();
	//? 数字・ナンバー(スコアやタイムに使用)のテクスチャ生成
	CNumber::Load();
	//? ライフのテクスチャ生成
	CLife::Load();
	//? 血液のテクスチャ生成
	CBloodGauge::Load();
	//? プレイヤーのテクスチャ生成
	CPlayer::Load();
	//? 敵・エネミーのテクスチャ生成
	CEnemy::Load();
	//? 弾のテクスチャ生成
	CBullet::Load();
	//? 技のテクスチャ生成
	CAction::Load();
	//? エフェクトのテクスチャ生成
	CEffect::Load();
	//? 爆発エフェクトのテクスチャ生成
	CExplosion::Load();

	//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
	//! 一時停止の生成↓
	m_pPause = CPause::Create(0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH/2, SCREEN_HEIGHT / 2);
	m_pPause = CPause::Create(1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_pPause = CPause::Create(2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH /6 , SCREEN_HEIGHT / 4);
	m_pPause = CPause::Create(3, SCREEN_WIDTH / 2, 240, 200, 50);
	m_pPause = CPause::Create(4, SCREEN_WIDTH / 2, 360, 200, 50);
	m_pPause = CPause::Create(5, SCREEN_WIDTH / 2, 490, 140, 50);

	m_pContinuity = CContinuity::Create(0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_pContinuity = CContinuity::Create(1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_pContinuity = CContinuity::Create(2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5);
	m_pContinuity = CContinuity::Create(3, SCREEN_WIDTH / 2, 280, 200, 50);
	m_pContinuity = CContinuity::Create(4, SCREEN_WIDTH / 2, 410, 200, 50);

	//! 背景の生成↓
	m_pBG = CBG::Create();
	//! UIの生成↓
	m_pUI = CUI::Create(1, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2,400);
	m_pUI = CUI::Create(4,640, SCREEN_HEIGHT-60, 50, 50);
	m_pUI = CUI::Create(5, 750, SCREEN_HEIGHT - 60, 50, 50);
	m_pUI = CUI::Create(6, 860, SCREEN_HEIGHT - 60, 50, 50);
	m_pUI = CUI::Create(7, 640, SCREEN_HEIGHT - 60, 50, 50);
	m_pUI = CUI::Create(8, 750, SCREEN_HEIGHT - 60, 50, 50);
	m_pUI = CUI::Create(9, 860, SCREEN_HEIGHT - 60, 50, 50);
	//! ライフゲージの生成↓
	m_pLife = CLife::Create();
	//! 血液ゲージの生成↓
	m_pBloodGauge = CBloodGauge::Create();
	//! UIの生成↓
	m_pUI = CUI::Create(12, 285, SCREEN_HEIGHT - 77, 240, 20);//ライフゲージフレーム
	m_pUI = CUI::Create(13, 285, SCREEN_HEIGHT - 25, 240, 20);//血液ゲージフレーム
	m_pUI = CUI::Create(2, 40, SCREEN_HEIGHT - 88, 35, 35);
	m_pUI = CUI::Create(3, 40, SCREEN_HEIGHT - 28, 30, 30);
	m_pUI = CUI::Create(11, SCREEN_WIDTH / 2, 95, 115, 115);//時間表現アイコン
	m_pUI = CUI::Create(14, SCREEN_WIDTH / 2, 75, 90, 90);//時間枠アイコン
	m_pUI = CUI::Create(15, SCREEN_WIDTH / 2, 95, 90, 90);//時間針
	m_pUI = CUI::Create(16, SCREEN_WIDTH / 2, 95, 70, 70);//時間針
	m_pUI = CUI::Create(18, 1100, 670, 50, 13);//時間針
	m_pUI = CUI::Create(19, 1000, 620, 50, 13);//時間針
	//! スコアの生成↓
	m_pScore = CScore::Create(D3DXVECTOR3(1020,700,0), CScore::GAME_SCORE);
	//! 制限時間の生成↓
	m_pTime = CTime::Create();
	//! プレイヤーの生成↓
	m_pPlayer = CPlayer::Create(0.0f, 0.0f, 15);
	//! 敵・エネミーの生成↓
	//m_pEnemy = CEnemy::Create(SCREEN_WIDTH+40, 300.0f, 3);//(位置X,位置Y,Life)
	//m_pEnemy = CEnemy::Create(SCREEN_WIDTH, 200.0f, 3);
	//m_pEnemy = CEnemy::Create(SCREEN_WIDTH+30, 100.0f, 3);

	//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
	
	return S_OK;
}

//! =============================================================================
//! 終了
//! =============================================================================
void CGame::Uninit(void)
{
	//!+ <生成した逆順で破棄していく↓>
	//? 爆発エフェクトのテクスチャの破棄
	CExplosion::UnLoad();
	//? エフェクトのテクスチャ生成
	CEffect::UnLoad();
	//? 技のテクスチャの破棄
	CAction::UnLoad();
	//? 弾のテクスチャの破棄
	CBullet::UnLoad();
	//? 敵・エネミーのテクスチャの破棄
	CEnemy::UnLoad();
	//? プレイヤーのテクスチャの破棄
	CPlayer::UnLoad();
	//? 血液のテクスチャの破棄
	CBloodGauge::UnLoad();
	//? ライフのテクスチャの破棄
	CLife::UnLoad();
	//? 数字・ナンバー(スコアやタイムに使用)のテクスチャ生成
	CNumber::UnLoad();
	//? UIのテクスチャ破棄
	CUI::UnLoad();
	//? 背景のテクスチャ破棄
	CBG::UnLoad();
	CContinuity::UnLoad();
	//? 一時停止のテクスチャ破棄
	CPause::UnLoad();
	CSound *pSound = CManager::GetSound();
	pSound->StopSound();
	//! 全てのデータ解放,終了処理
	CScene::ReleaseAll();
}

//? =============================================================================
//? 更新処理
//? =============================================================================
void CGame::Update(void)
{
	//! =============================================================================
	//! 入力処理に関する処理
	//! =============================================================================
	//キーボードを使用するための処理↓
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//ゲームパッド呼び
	CInputXPad *pInputXPad = CManager::GetInputXPad();
	//! =============================================================================

	CFade::FADE pFade;
	pFade = CFade::GetFade();
	CPlayer *pBloodLife = CGame::GetPlayer();
	int nBllodLife = pBloodLife->GetBloodLife();
	CTime *pTime = CGame::GetTime();
	int TimeNow = pTime->GetTimeNow();
	CScore*pScore = CGame::GetScore();
	int nNowScore = pScore->GetNowScore();
	bool bPlayerFlag = pTime->GetPlayerFlag();
	CContinuity *pContinuity = CGame::GetContinuity();
	bool bFlag = pContinuity->GetContinuityFlag();
	CPause *pPause = CGame::GetPause();
	int nUse = pPause->GetPauseMode();

	//! =============================================================================
	//! ポーズに関する処理
	//! =============================================================================

	if (pFade == CFade::FADE_NONE)
	{
		if (bPlayerFlag == true)
		{
			if (pInputKeyboard->GetTrigger(DIK_R) == true)
			{
				CManager::GetFade()->SetFade(CManager::MODE_RESULT);
			}

			if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_START, 0) == true || pInputKeyboard->GetTrigger(DIK_P) == true)
			{
				if (bFlag == false)
				{
					{
						m_bPause = m_bPause ? false : true;
					}
				}
			}
		}
	}

	
	if (nUse == CPause::MENU::PAUSE00)//ポーズの解除
	{
		if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			{
				m_bPause = false;
			}

		}
	}

	//! =============================================================================
	//! コンティニューに関する処理
	//! =============================================================================
	
	//↓obj総数の獲得&&使えるようにローカルに情報を与える
	int NumAll = CScene::GetNumAll();

	for (int nCntP = 0; nCntP < CScene::OBJ_DRAW::DRAW_ALL; nCntP++)//用意されたobj分forを回す
	{
		for (int nCnt = 0; nCnt < NumAll; nCnt++)//用意されたobj分forを回す
		{
			CScene *pScene;
			pScene = CScene::GetScene(nCntP, nCnt);

			if (pScene != NULL)
			{
				CScene::OBJ_TYPE ObjType;
				ObjType = pScene->GetObjType();//タイプの確認

				if (ObjType == CScene::OBJ_TYPE::OBJTYPE_PLAYER)//プレイヤーobjなら
				{
					CScene2D *pPlayer = (CScene2D*)pScene;//CScene2DのGetPosを使えるようにキャスト(変換)する
					
					int nLife = pPlayer->GetLife();//プレイヤーの体力を取得

					
					if (nLife <= 0||TimeNow <= 0)//Pの体力もしくは時間が0の場合...
					{
						m_bContinuity = true;
						
						int nUse = pContinuity->GetContinuityMode();
						if (nUse == CContinuity::MENU::CONTINUITY00)
						{
							if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
							{
								
								{
									m_bContinuity = false;


									if (nLife <= 0)//体力が0の場合に...
									{
										nLife = 10;
										CLife *pLife = CGame::GetLife();
										pLife->SetLife(nLife);
										pPlayer->SetLife(nLife);
									}


									TimeNow += (10 * 100);//時間の加算
									pTime->SetLife(TimeNow);

									pScore->SetScore(nNowScore / 2);//現スコアを半減

									pPlayer->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//プレイヤー表示

									m_nCCC = 1;//時間回転アイコン関係
									break;
								}
								
							}
						}
					}
				}
			}
		}
	}

	//! =============================================================================
	//! 敵自動生成に関する処理
	//! =============================================================================
	srand((unsigned)time(NULL));
	//CTime::GetEnemyCreateTime();
	if (m_bContinuity == false)
	{
			int ECT = pTime->GetEnemyCreateTime();
		if (m_nCheck == 0)
		{
			if (ECT < 12 * 100)//12秒内
			{
				if (ECT % (3 * 100) == 0)//3秒間隔
				{
					CEnemy::Create(CEnemy::ENEMY01, SCREEN_WIDTH + (100 + rand() % 200), 110 + (rand() % 300), 3);
					CEnemy::Create(CEnemy::ENEMY01, SCREEN_WIDTH + (100 + rand() % 200), 660 - (rand() % 200), 3);
					CEnemy::Create(CEnemy::ENEMY02, SCREEN_WIDTH + (100 + rand() % 200), SCREEN_HEIGHT / 2 - 80, 5);
				}
			}
			if (ECT > 7 * 100)//7秒後
			{
				if (ECT % (5 * 100) == 0)//5秒間隔
				{
					CEnemy::Create(CEnemy::ENEMY01, SCREEN_WIDTH + (100 + rand() % 200), 140 + (rand() % 380), 3);
					CEnemy::Create(CEnemy::ENEMY01, SCREEN_WIDTH + (100 + rand() % 200), 590 - (rand() % 210), 3);
					CEnemy::Create(CEnemy::ENEMY02, SCREEN_WIDTH + (100 + rand() % 200), SCREEN_HEIGHT / 2 + 95, 5);
				}
			}
			if (ECT > 10 * 100)//10秒後
			{
				if (ECT % (4 * 100) == 0)//5秒間隔
				{
					CEnemy::Create(CEnemy::ENEMY03, SCREEN_WIDTH + (100 + rand() % 200), 60, 3);
				}
			}
			if (ECT > 18 * 100)//18秒後
			{
				if (ECT % (4 * 100) == 0)//5秒間隔
				{
					CEnemy::Create(CEnemy::ENEMY04, 150 + (rand() % 530), SCREEN_HEIGHT + 50, 3);
				}
			}
			if (ECT > 25 * 100)//25秒後
			{
				if (ECT % (7 * 100) == 0)//5秒間隔
				{
					CEnemy::Create(CEnemy::ENEMY05, SCREEN_WIDTH + (100 + rand() % 200), 100 + (rand() % 190), 3);
					CEnemy::Create(CEnemy::ENEMY05, SCREEN_WIDTH + (100 + rand() % 200), SCREEN_HEIGHT / 2 + 95, 5);
					CEnemy::Create(CEnemy::ENEMY05, SCREEN_WIDTH + (100 + rand() % 200), 560 - (rand() % 140), 3);
				}
			}
		}
		if (ECT > 35 * 100&& ECT < 36 * 100)//35秒後
		{
			m_bBossFlag = true;
			m_nCheck++;
			if (m_bBossFlag == true && m_nCheck == 1)
			{
				m_bBossFlag = false;
				m_pEnemy = CEnemy::Create(CEnemy::ENEMY_BOSS, SCREEN_WIDTH, SCREEN_HEIGHT / 2, 10);
			}
		}
	}
	
	CEnemy*pEnemy = CGame::GetEnemy();
	if (pEnemy != NULL)
	{
		int Life = pEnemy->GetLife();
		if (Life <= 0)
		{
			CFade::FADE pFade;
			pFade = CFade::GetFade();
			if (pFade == CFade::FADE_NONE)
			{
				{
					pEnemy = NULL;
					CManager::GetFade()->SetFade(CManager::MODE_RESULT);
				}
			}
		}
	}
}

//? =============================================================================
//? ゲームの描画処理
//? =============================================================================
void CGame::Draw(void)
{

}

//時間表現アイコンに関する処理
void CGame::SetCCC(int nCCC)
{
	m_nCCC = nCCC;
}

