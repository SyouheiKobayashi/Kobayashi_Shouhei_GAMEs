//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//						ランキング処理 [ranking.cpp]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "score.h"
#include "number.h"
#include "ranking.h"
#include "manager.h"
#include "game.h"
#include "time.h"
//==============================================
//					コンストラクタ
//==============================================
CScore::CScore(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
	{
		m_nScoreNo[nCnt] = 0;
	}
}
//==============================================
//					デストラクタ
//==============================================
CScore::~CScore()
{

}
//==============================================
//					生成
//==============================================
CScore *CScore::Create(D3DXVECTOR3 pos,SCORE_TYPE type)
{
	CScore *pScore = NULL;

	if (pScore == NULL)
	{
		switch (type)
		{
		case GAME_SCORE:
			pScore = new CGameScore;
			pScore->AddScore(0);//モードが変わっても常に初期で(引き継いだ数値)スコアの表示を行う
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

//==============================================
//				表示位置
//==============================================
void CScore::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-100, -100, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+100, -100, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-100, +100, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(+100, +100, 0.0f) + m_pos;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================
//				スコアの加算
//==============================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
	m_nTotalScore = CManager::GetTotalScore();//前のステージのスコアを引き継ぎ表示する
											 
	float digit = 10.0f;
	float newdigit01 = powf(digit, (float)MAX_SCOREDIGIT-1.0f);
	float newdigit02 = powf(digit, (float)MAX_SCOREDIGIT);

	for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
	{
		m_nScoreNo[nCnt] = ((m_nScore +m_nTotalScore) % (int)newdigit02) / (int)newdigit01;//[m_nTotalScore]前のステージのスコアも加える
		newdigit01 = newdigit01 / 10;
		newdigit02 = newdigit02 / 10;
	}
}


// @   @   @   @   @   @   @   @   @   @   @   @
//!++			  ゲームスコア
// @   @   @   @   @   @   @   @   @   @   @   @
//==============================================
//					コンストラクタ
//==============================================
CGameScore::CGameScore()
{
	
	for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

}
//==============================================
//					デストラクタ
//==============================================
CGameScore::~CGameScore()
{

}

//==============================================
//					初期化
//==============================================
HRESULT CGameScore::Init(void)
{
	return S_OK;
}
HRESULT CGameScore::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
	{
		m_apNumber[nCnt] = new CNumber;
		m_apNumber[nCnt]->Init();
		m_apNumber[nCnt]->SetSize(SCORE_SIZE_X, SCORE_SIZE_Y);
		m_apNumber[nCnt]->SetPos(pos, SCORE_SPACE, nCnt);
	}
	return S_OK;
}

//==============================================
//						終了
//==============================================
void CGameScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = NULL;
		}
	}

	Release();
}

//==============================================
//					更新
//==============================================
void CGameScore::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
	{
		m_apNumber[nCnt]->Update();
		m_apNumber[nCnt]->SetNumber(m_nScoreNo[nCnt]);//カウント分桁数を増やす(横ずらし)
	}
}

//==============================================
//					描画
//==============================================
void CGameScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}

// @   @   @   @   @   @   @   @   @   @   @   @
//!++		   ランキングスコア
// @   @   @   @   @   @   @   @   @   @   @   @
//==============================================
//					コンストラクタ
//==============================================
CRankingScore::CRankingScore()
{
	for (int nRankNo = 0; nRankNo < MAX_RANK; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
		{
			m_apNumber[nRankNo][nCnt] = NULL;
			m_nDigt[nRankNo][nCnt] = 0;
		}
	}
	m_NewRecord = MAX_RANK;//最大順位分
}
//==============================================
//					デストラクタ
//==============================================
CRankingScore::~CRankingScore()
{

}

//==============================================
//					初期化
//==============================================
HRESULT CRankingScore::Init(void)
{
	return S_OK;
}
HRESULT CRankingScore::Init(D3DXVECTOR3 pos)
{

	for (int nRankNo = 0; nRankNo < MAX_RANK; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
		{
			m_apNumber[nRankNo][nCnt] = new CNumber;
			m_apNumber[nRankNo][nCnt]->Init();
			m_apNumber[nRankNo][nCnt]->SetSize(15.0f, 35.0f);
			m_apNumber[nRankNo][nCnt]->SetPos(pos + D3DXVECTOR3(0.0f,(110.0f* (float)nRankNo),0.0f), 75.0f, nCnt);
		}
	}

	int nScore = CManager::GetTotalScore();//今回のタイムを取得する
	SetRankingSort(nScore);

	return S_OK;
 }
//==============================================
//						終了
//==============================================
void CRankingScore::Uninit(void)
{
	for (int nRankNo = 0; nRankNo < MAX_RANK; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
		{
			m_apNumber[nRankNo][nCnt]->Uninit();
			m_apNumber[nRankNo][nCnt] = NULL;
		}
	}

	Release();
}
//==============================================
//					更新
//==============================================
void CRankingScore::Update(void)
{
	for (int nRankNo = 0; nRankNo < MAX_RANK; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
		{
			if(m_NewRecord < 5)
			{
				//m_apNumber[m_NewRecord][nCnt]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				m_apNumber[m_NewRecord][nCnt]->SetScale(100, 0.05f);
			}
			
		}
	}
}

//==============================================
//					描画
//==============================================
void CRankingScore::Draw(void)
{
	for (int nRankNo = 0; nRankNo < MAX_RANK; nRankNo++)
	{
		for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
		{
			m_apNumber[nRankNo][nCnt]->Draw();
		}
	}
}

//==============================================
//					ソート(昇順・降順等)
//==============================================
void CRankingScore::SetRankingSort(int nScore)
{
	int nRank = 0;
	int nSave = 0;
	nRank  = nScore;
	int nSave02 = 0;
	
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		if (nRank > CManager::m_nRank[nCnt])//記録更新したら...
		{
			nSave = CManager::m_nRank[nCnt];
			CManager::m_nRank[nCnt] = nRank;
			nRank = nSave;
			m_NewRecord = nCnt;
			for (int nSortCnt = nCnt + 1; nSortCnt < MAX_RANK; nSortCnt++)
			{
				
				nSave02 = CManager::m_nRank[nSortCnt];
				CManager::m_nRank[nSortCnt] = nRank;
				nRank = nSave02;
			}
			break;
		}
	}
	
	//桁に関する処理
	float digit = 10;//初期桁
	float newdigit01 = powf(digit, (float)MAX_SCOREDIGIT - 1.0f);//桁数を変える
	float newdigit02 = powf(digit, (float)MAX_SCOREDIGIT);//桁数を変える

	for (int Rank = 0; Rank < MAX_RANK; Rank++)
	{
		for (int nCnt = 0; nCnt < MAX_SCOREDIGIT; nCnt++)
		{
			m_nDigt[Rank][nCnt] = (CManager::m_nRank[Rank] % (int)newdigit02) / (int)newdigit01;
			
			m_apNumber[Rank][nCnt]->SetNumber(m_nDigt[Rank][nCnt]);
			newdigit01 = newdigit01 / 10;
			newdigit02 = newdigit02 / 10;
			if (nCnt == MAX_SCOREDIGIT - 1)
			{
				 newdigit01 = powf(digit, MAX_SCOREDIGIT - 1);//桁数を変える
				 newdigit02 = powf(digit, MAX_SCOREDIGIT);//桁数を変える
			}
		}
	}

	//CManager::SetLastScore(0);//次のスコアのために0を入れる
}