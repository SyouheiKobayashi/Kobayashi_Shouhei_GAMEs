//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// タイトル処理 [tutorial.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "main.h"
#include "manager.h"

class CBG;
class CUI;

//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ ゲームCLASS(基本クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CTutorial
{
public:
	CTutorial();
	~CTutorial();
	static CTutorial *Create(void);
	static CBG *GetBG(void) { return m_pBG; }
	static CUI *GetUI(void) { return m_pUI; }
	

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	

private:
	static CTutorial *m_pGame;
	static  CBG *m_pBG;
	static CUI *m_pUI;
};

#endif

