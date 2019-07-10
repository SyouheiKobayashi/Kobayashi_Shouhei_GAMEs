//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �Q�[������ [game.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
#include "manager.h"

class CPause;
class CContinuity;
class CBG;
class CUI;
class CNumber;
class CScore;
class CTime;
class CGauge;
class CLife;
class CBloodGauge;
class CPlayer;
class CEnemy;
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �Q�[��CLASS(��{�N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CGame
{
public:
	CGame();
	~CGame();
	static CGame *Create(void);
	static CGame *GetGame(void) { return m_pGame; }
	static CPause *GetPause(void) { return m_pPause; }
	static CContinuity *GetContinuity(void) { return m_pContinuity; }
	static CBG *GetBG(void) { return m_pBG; }
	static CUI *GetUI(void) { return m_pUI; }
	static CNumber *GetNumber(void) { return m_pNumber; }
	static CScore *GetScore(void) { return m_pScore; }
	static CTime *GetTime(void) { return m_pTime; }
	static CGauge *GetGauge(void) { return m_pGauge; }
	static CLife * GetLife(void) { return m_pLife; }
	static CBloodGauge *GetBloodGauge(void) { return m_pBloodGauge; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CEnemy *GetEnemy(void) { return m_pEnemy; }
	bool GetPauseFlag(void) { return m_bPause; }//���݂̃t���O�̎擾
	bool GetContinuityFlag(void) { return m_bContinuity; }//���݂̃t���O�̎擾
	int GetCCC(void) { return m_nCCC; }
	void SetCCC(int nCCC);

	HRESULT Init(void);//��ʃT�C�Y
	void Uninit(void);
	void Update(void);
	void Draw(void);
	

private:
	static CPause *m_pPause;
	static CContinuity *m_pContinuity;
	static  CBG *m_pBG;
	static  CUI *m_pUI;
	static CNumber *m_pNumber;
	static CScore * m_pScore;
	static CTime * m_pTime;
	static CGauge *m_pGauge;
	static CLife *m_pLife;
	static CBloodGauge *m_pBloodGauge;
	static CPlayer *m_pPlayer;
	static CEnemy *m_pEnemy;

	static CGame *m_pGame;

	bool m_bPause;
	bool m_bContinuity;

	int m_nCCC;
	int m_nCheck;
	bool m_bBossFlag;
	
	
};

#endif

