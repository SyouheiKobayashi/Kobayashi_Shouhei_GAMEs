//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// スコア処理 [score.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "score.h"
#include "number.h"
#include "result.h"
#include "manager.h"

//マクロ
#define SCORE_SIZE_X	(18)
#define SCORE_SIZE_Y	(18)
#define SCORE_SPACE		(30)
#define SCORE_SIZE_posX	(SCREEN_WIDTH-510)
#define SCORE_SIZE_posY	(100)

//静的メンバ変数

//=============================================================================
//+ スコアのコンストラクタ
//=============================================================================
CScore::CScore():CScene(OBJ_DRAW::DRAW_INFO)
{
	m_nScore = 0;
	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		m_nScoreNo[nCnt] = 0;
		
	}

}
//=============================================================================
//+ スコアのデストラクタ
//=============================================================================
CScore::~CScore()
{

}
//=============================================================================
//+ スコアの生成処理
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos,SCORE_TYPE type)
{
	CScore *pScore = NULL;

	if (pScore == NULL)
	{
		switch (type)
		{
		case GAME_SCORE:
			pScore = new CGameScore;
			pScore->Init(pos);

			break;

		case RANKING_SCORE:
			pScore = new CRankingScore;
			pScore->Init(pos);

			break;
		}

	}

	return pScore;
}

void CScore::SetPos(D3DXVECTOR3 pos)
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

void CScore::SetScore(int nNowScore)
{
	m_nScore = nNowScore;
	
	
}

void CScore::AddScore(int nValue)
{
	m_nScore += nValue;

	float digit = 10;//初期桁
	float newdigit01 = powf(digit, MAX-1);//桁数を変える
	float newdigit02 = powf(digit, MAX);//桁数を変える

	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		m_nScoreNo[nCnt] = (m_nScore % (int)newdigit02) / (int)newdigit01;
		newdigit01 = newdigit01 / 10;
		newdigit02 = newdigit02 / 10;
	}
}

void CScore::SaveScore(int nValue)
{
	m_nScore = nValue;

	float digit = 10;//初期桁
	float newdigit01 = powf(digit, MAX - 1);//桁数を変える
	float newdigit02 = powf(digit, MAX);//桁数を変える

	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		m_nScoreNo[nCnt] = (m_nScore % (int)newdigit02) / (int)newdigit01;
		newdigit01 = newdigit01 / 10;
		newdigit02 = newdigit02 / 10;
	}
}

//!+ ゲーム用
//=============================================================================
//+ スコアのコンストラクタ
//=============================================================================
CGameScore::CGameScore()
{
	
	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

}
//=============================================================================
//+ スコアのデストラクタ
//=============================================================================
CGameScore::~CGameScore()
{

}

//=============================================================================
//+ スコアの初期化処理
//=============================================================================
HRESULT CGameScore::Init(void)
{
	return S_OK;
}
HRESULT CGameScore::Init(D3DXVECTOR3 pos)
{
	
	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apNumber[nCnt] = new CNumber;
		m_apNumber[nCnt]->Init();
		m_apNumber[nCnt]->SetSize(SCORE_SIZE_X, SCORE_SIZE_Y);
		m_apNumber[nCnt]->SetPos(pos, SCORE_SPACE, nCnt);
	}
	return S_OK;
}
//=============================================================================
//+ スコアの終了処理
//=============================================================================
void CGameScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apNumber[nCnt]->Uninit();
		m_apNumber[nCnt] = NULL;
	}
	CManager::SetLastScore(m_nScore);//マネージャに最終スコア保管
	//自分自身をdelete	<Scene>のdelete処理を使用
	Release();
}
//=============================================================================
//+ スコアの更新処理
//=============================================================================
void CGameScore::Update(void)
{
	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apNumber[nCnt]->Update();
		m_apNumber[nCnt]->SetNumber(m_nScoreNo[nCnt]);//カウント分間隔をあける
	}

	//CResult::SetLastScore(m_nScore);
}
//=============================================================================
//+ スコアの描画処理
//=============================================================================
void CGameScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apNumber[nCnt]->Draw();
	}
}

//!+ RANKING用
//=============================================================================
//+ スコアのコンストラクタ
//=============================================================================
CRankingScore::CRankingScore()
{
	for (int nRankNo = 0; nRankNo < 5; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX; nCnt++)
		{
			m_apNumber[nRankNo][nCnt] = NULL;
			m_nDigt[nRankNo][nCnt] = 0;
		}
	}
}
//=============================================================================
//+ スコアのデストラクタ
//=============================================================================
CRankingScore::~CRankingScore()
{

}

//=============================================================================
//+ スコアの初期化処理
//=============================================================================
HRESULT CRankingScore::Init(void)
{
	return S_OK;
}
HRESULT CRankingScore::Init(D3DXVECTOR3 pos)
{

	for (int nRankNo = 0; nRankNo < 5; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX; nCnt++)
		{
			//↓呼び出したnumber処理を使う
			m_apNumber[nRankNo][nCnt] = new CNumber;
			m_apNumber[nRankNo][nCnt]->Init();
			m_apNumber[nRankNo][nCnt]->SetSize(35, 35);
			m_apNumber[nRankNo][nCnt]->SetPos(pos+D3DXVECTOR3(0.0f,(114.0f* nRankNo),0.0f), 55, nCnt);
		}
	}
	SetRankingSort(CManager::GetLastScore());

	return S_OK;
 }
//=============================================================================
//+ スコアの終了処理
//=============================================================================
void CRankingScore::Uninit(void)
{
	for (int nRankNo = 0; nRankNo < 5; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX; nCnt++)
		{
			//↓呼び出したnumber処理を使う
			m_apNumber[nRankNo][nCnt]->Uninit();
			m_apNumber[nRankNo][nCnt] = NULL;
		}
	}
	//自分自身をdelete	<Scene>のdelete処理を使用
	Release();
}
//=============================================================================
//+ スコアの更新処理
//=============================================================================
void CRankingScore::Update(void)
{
	for (int nRankNo = 0; nRankNo < 5; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX; nCnt++)
		{
			//↓呼び出したnumber処理を使う
			m_apNumber[nRankNo][nCnt]->Update();
		
		}
	}

	//CResult::SetLastScore(m_nScore);
}
//=============================================================================
//+ スコアの描画処理
//=============================================================================
void CRankingScore::Draw(void)
{
	for (int nRankNo = 0; nRankNo < 5; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX; nCnt++)
		{
			//↓呼び出したnumber処理を使う
			m_apNumber[nRankNo][nCnt]->Draw();
		}

	}
}

void CRankingScore::SetRankingSort(int nScore)
{
	int nRank = 0;
	int nSave = 0;
	nRank  = nScore;
	int nSave02 = 0;

	
	//スコアのソート処理
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		if (nRank > CManager::nRank[nCnt])
		{
			nSave = CManager::nRank[nCnt];
			CManager::nRank[nCnt] = nRank;
			nRank = nSave;
			for (int nSortCnt = nCnt + 1; nSortCnt < 5; nSortCnt++)
			{
				nSave02 = CManager::nRank[nSortCnt];
				CManager::nRank[nSortCnt] = nRank;
				nRank = nSave02;
			}
			break;
		}
	}
	//桁に関する処理
	float digit = 10;//初期桁
	float newdigit01 = powf(digit, MAX - 1);//桁数を変える
	float newdigit02 = powf(digit, MAX);//桁数を変える

	for (int Rank = 0; Rank < 5; Rank++)
	{
		for (int nCnt = 0; nCnt < MAX; nCnt++)
		{
			m_nDigt[Rank][nCnt] = (CManager::nRank[Rank] % (int)newdigit02) / (int)newdigit01;
			
			m_apNumber[Rank][nCnt]->SetNumber(m_nDigt[Rank][nCnt]);
			newdigit01 = newdigit01 / 10;
			newdigit02 = newdigit02 / 10;
			if (nCnt == MAX - 1)
			{
				 newdigit01 = powf(digit, MAX - 1);//桁数を変える
				 newdigit02 = powf(digit, MAX);//桁数を変える
			}

		}
	}
	CManager::SetLastScore(0);//初期化しなければ正しくないRankingになる
}