//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// スコア処理 [score.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"
#include "scene.h"

#define MAX	(7)
class CNumber;
//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ シーン2DCLASS(<Scene>の派生クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CScore : public CScene
{
public:
	typedef enum
	{
		GAME_SCORE = 0,
		RANKING_SCORE,
		MAX_SCORE

	}SCORE_TYPE;

	CScore();
	~CScore();

	static CScore *Create(D3DXVECTOR3 pos, SCORE_TYPE type);//スコアの生成処理

	virtual HRESULT Init(void) = 0;
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;
	
	
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	void SetPos(D3DXVECTOR3 pos);//得た情報を反映させる

	void AddScore(int nValue);//スコア加点

	void SaveScore(int nValue);//ゲームのスコア一時的セーブ

	int GetNowScore(void) { return m_nScore; }//現在スコアの取得
	void SetScore(int nNowScore);

	

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;			// ポリゴンの位置

protected:
	int m_nScore;//得点の記録
	int m_nScoreNo[MAX];//桁数

};

class CGameScore : public CScore
{
public:
	CGameScore();
	~CGameScore();

	//親がクリエイトをもつ

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos);


	void Uninit(void);
	void Update(void);
	void Draw(void);


private:
	
	CNumber *m_apNumber[MAX];//number処理を扱いため
	

};

class CRankingScore : public CScore
{
public:
	CRankingScore();
	~CRankingScore();

	//親がクリエイトをもつ

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos);


	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetRankingSort(int nScore);

private:

	CNumber *m_apNumber[5][MAX];//number処理を扱いため
	int m_nDigt[5][7];

};

#endif