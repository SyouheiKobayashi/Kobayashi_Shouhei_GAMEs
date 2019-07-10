//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					スコア処理 [score.h]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"
#include "scene.h"

//==============================================
//					マクロ定義
//==============================================
#define MAX_SCOREDIGIT	(3)//最大桁数
#define MAX_RANK	(5)//最大順位 / マネージャに手打ちで書いてるから気を付けて!!
#define SCORE_SIZE_X	(20)
#define SCORE_SIZE_Y	(26)
#define SCORE_SPACE		(45)

class CNumber;
//==============================================
//				シーンの派生 → スコア
//==============================================
class CScore : public CScene
{
public:
	typedef enum//スコアモード
	{
		GAME_SCORE = 0,	//ゲームスコア
		RANKING_SCORE,	//ランキングスコア
		MAX_SCORE
	}SCORE_TYPE;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CScore(int nPriority = DRAW_2D, DATA_TYPE nObjType = DATA_TYPE_2D);
	~CScore();
	static CScore *Create(D3DXVECTOR3 pos, SCORE_TYPE type);//スコアの生成処理

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					基盤関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	virtual HRESULT Init(void) = 0;
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	int GetNowScore(void) { return m_nScore; }//現在スコアの取得

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	void SetPos(D3DXVECTOR3 pos);
	void AddScore(int nValue);//スコア加点

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//頂点バッファへのポインタ
	D3DXVECTOR3	m_pos;//ポリゴンの位置


protected:
	int m_nScore;				//現在のスコア
	int m_nTotalScore;			//合計スコア
	int m_nScoreNo[MAX_SCOREDIGIT];	//スコアの桁数

};

//! ==============================================
//!			スコアの派生 → ゲームで使用するスコア
//! ==============================================
class CGameScore : public CScore
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CGameScore();
	~CGameScore();

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					基盤関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CNumber *m_apNumber[MAX_SCOREDIGIT];
};

//! ==============================================
//!			スコアの派生 → ランキングで使用するスコア
//! ==============================================
class CRankingScore : public CScore
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CRankingScore();
	~CRankingScore();

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					基盤関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetRankingSort(int nScore);			//スコアのソート

private:
	
	CNumber *m_apNumber[MAX_RANK][MAX_SCOREDIGIT];	//[最大順位][桁数]
	int m_nDigt[MAX_RANK][MAX_SCOREDIGIT];			//桁の更新で使用
	int m_NewRecord;								//記録が更新されたとき

};

#endif