//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// タイトル処理 [title.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _TITLE_H_
#define _TITLE_H_
#include "main.h"
#include "manager.h"

class CBG;
class CUI;

//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ ゲームCLASS(基本クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CTitle
{
public:
	CTitle();
	~CTitle();
	static CTitle *Create(void);
	static CBG *GetBG(void) { return m_pBG; }
	static CUI *GetUI(void) { return m_pUI; }
	

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	

private:
	static CTitle *m_pGame;
	static  CBG *m_pBG;
	static CUI *m_pUI;
};

#endif

