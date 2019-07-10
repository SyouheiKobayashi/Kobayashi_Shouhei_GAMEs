//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// スコア処理 [time.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "time.h"
#include "number.h"
#include "fade.h"
#include "UI.h"
#include "game.h"
#include "continuity.h"

//マクロ
#define SCORE_SIZE_X	(18)
#define SCORE_SIZE_Y	(18)
#define SCORE_SPACE		(30)
#define SCORE_SIZE_posX	(SCREEN_WIDTH-320)
#define SCORE_SIZE_posY	(650)

#define INITIAL_TIME (30)//初期開始時間
#define END_TIME (0)//ゲーム終了時間
#define ENEMY_CREATE_TIME	(90)

//静的メンバ変数

//=============================================================================
//+ スコアのコンストラクタ
//=============================================================================
CTime::CTime() :CScene(OBJ_DRAW::DRAW_INFO)
{
	m_nTimeNow = INITIAL_TIME *100;
	m_nEnemyCreateTime = 0;
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_nTimeDigit[nCnt] = 0;
		m_apNumber[nCnt] = NULL;
	}

}
//=============================================================================
//+ スコアのデストラクタ
//=============================================================================
CTime::~CTime()
{

}
//=============================================================================
//+ スコアの生成処理
//=============================================================================
CTime *CTime::Create(void)
{
	CTime *pTime = NULL;

	if (pTime == NULL)
	{
		pTime = new CTime;
		pTime->Init();
	}

	return pTime;
}
//=============================================================================
//+ スコアの初期化処理
//=============================================================================
HRESULT CTime::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apNumber[nCnt] = new CNumber;
		m_apNumber[nCnt]->Init();
		m_apNumber[nCnt]->SetSize(SCORE_SIZE_X, SCORE_SIZE_Y);
		m_apNumber[nCnt]->SetPos(D3DXVECTOR3(SCORE_SIZE_posX, SCORE_SIZE_posY, 0.0f), SCORE_SPACE, nCnt);
	}

	m_nTimeNow = INITIAL_TIME *100;
	m_nUnintTime = 0;
	m_nCheck = false;
	m_bPlayerFlag = true;
	m_nEnemyCreateTime = 0;
	return S_OK;
}
//=============================================================================
//+ スコアの終了処理
//=============================================================================
void CTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apNumber[nCnt]->Uninit();
		m_apNumber[nCnt] = NULL;
	}
	//自分自身をdelete	<Scene>のdelete処理を使用
	Release();
}
//=============================================================================
//+ スコアの更新処理
//=============================================================================
void CTime::Update(void)
{
	
	
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apNumber[nCnt]->Update();
		m_apNumber[nCnt]->SetNumber(m_nTimeDigit[nCnt]);//カウント分間隔をあける
	}

	m_nTimeNow--;
	m_nEnemyCreateTime++;
	CContinuity *pContinuity = CGame::GetContinuity();
	bool Flag = pContinuity->GetGiveUpFlag();
	if (Flag == true)
	{
	
		m_nUnintTime++;//フェード処理を行うまでの時間
		m_nCheck = true;//UIの複数生成を阻止
		m_bPlayerFlag = false;//プレイヤー操作不可

		if (m_nCheck == true && m_nUnintTime == 1)
		{
			CUI::Create(17, SCREEN_WIDTH / 2, 350, 115, 115);//ゲームオーバーアイコン
			m_nCheck = false;
		}

		if (m_nUnintTime > (3 * 100))//ある一定の時間経過で...
		{

			//ゲームの遷移
			CFade::FADE pFade;
			pFade = CFade::GetFade();
			if (pFade == CFade::FADE_NONE)
			{
				CManager::GetFade()->SetFade(CManager::MODE_RESULT);
				
			}
		}
	}
		m_nTimeDigit[0] = m_nTimeNow % 100000 / 10000;
		m_nTimeDigit[1] = m_nTimeNow % 10000 / 1000;
		m_nTimeDigit[2] = m_nTimeNow % 1000 / 100;

}
//=============================================================================
//+ スコアの描画処理
//=============================================================================
void CTime::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apNumber[nCnt]->Draw();
	}
}

void CTime::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//通常表示背景(サイズ変化、回転なし,各.cppでサイズの書き換え可)
	pVtx[0].pos = D3DXVECTOR3(-100, -100, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+100, -100, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-100, +100, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(+100, +100, 0.0f) + m_pos;


	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

void CTime::AddScore(int nValue)
{
	m_nTimeNow += nValue;
}

void CTime::SetLife(int nAddLife)
{
	m_nTimeNow = nAddLife;
}
