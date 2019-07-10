//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 一時停止処理 [continuity.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _CONTINUITY_H_
#define _CONTINUITY_H_
#include "main.h"
#include "scene2D.h"

#define CONTINUITY_TEX	(5)
//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ UICLASS(<scene2D>の派生クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CContinuity : public CScene2D
{
public:
	typedef enum
	{
		CONTINUITY_BG01 = 0,
		CONTINUITY_BG02,
		CONTINUITY_BG03,
		CONTINUITY00,//復帰
		CONTINUITY01,//リザルトへ
		
	}MENU;

	CContinuity();
	~CContinuity();
	static HRESULT Load(void);//テクスチャを必要分読み込む
	static void UnLoad(void);//使用しているテクスチャを他の処理で消させないようにする
	static CContinuity *Create(int nUI_NUM, int nPOS_X, int nPOS_Y, int nSIZE_X, int nSIZE_Y);

	HRESULT Init(int nUI_NUM);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetContinuityMode(void) { return m_nContinuityMode; }
	bool GetContinuityFlag(void) { return m_ContinuityFlag; }

	bool GetGiveUpFlag(void) { return m_GiveUpFlag; }
		
	//void SetActionUI(int nSelectActionNo, int nMode, int UI_TEX);//アクション選択時の処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[CONTINUITY_TEX];//共有テクスチャへのポインタ


												 //! <ポリゴンのアニメーションに関する変数>
	int m_nType;
	int m_nContinuityMode;
	bool m_ContinuityFlag;
	bool m_GiveUpFlag;
	//int m_CntAnim;//アニメーションの速さ
	//int m_PatternAnim;//アニメーションの分割数
};




#endif