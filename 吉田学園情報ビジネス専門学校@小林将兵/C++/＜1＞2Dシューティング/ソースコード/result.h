//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// タイトル処理 [result.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _RESULT_H_
#define _RESULT_H_
#include "main.h"
#include "manager.h"

class CBG;
class CUI;
class CNumber;
class CScore;

//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ ゲームCLASS(基本クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CResult
{
public:
	CResult();
	~CResult();
	static CResult *Create(void);
	static CBG *GetBG(void) { return m_pBG; }
	static CUI *GetUI(void) { return m_pUI; }
	static CNumber *GetNumber(void) { return m_pNumber; }
	static CScore *GetScore(void) { return m_pScore; }
	

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static CResult *m_pGame;
	static  CBG *m_pBG;
	static CUI *m_pUI;
	static CNumber *m_pNumber;
	static CScore * m_pScore;


	
};

#endif

