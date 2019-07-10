//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// UI処理 [UI.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _UI_H_
#define _UI_H_
#include "main.h"
#include "scene2D.h"

#define MAX_UI	(21)
//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ UICLASS(<scene2D>の派生クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CUI : public CScene2D
{
public:
	CUI();
	~CUI();
	static HRESULT Load(void);//テクスチャを必要分読み込む
	static void UnLoad(void);//使用しているテクスチャを他の処理で消させないようにする
	static CUI *Create(int nUI_NUM,int nPOS_X, int nPOS_Y,int nSIZE_X, int nSIZE_Y);

	HRESULT Init(int nUI_NUM);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetActionUI(int nSelectActionNo,int nMode,int UI_TEX);//アクション選択時の処理
	

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_UI];//共有テクスチャへのポインタ
	

	//! <ポリゴンのアニメーションに関する変数>
	int m_nType;
	int m_CntAnim;//アニメーションの速さ
	int m_PatternAnim;//アニメーションの分割数

	bool m_bTimeCheck;

	float m_fCnt;//ゲームオーバーUIの不透明率を扱う
};




#endif