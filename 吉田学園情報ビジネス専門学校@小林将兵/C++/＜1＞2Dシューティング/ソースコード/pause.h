//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 一時停止処理 [pause.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "main.h"
#include "scene2D.h"

#define PAUSE_TEX	(6)
//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ UICLASS(<scene2D>の派生クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CPause : public CScene2D
{
public:
	typedef enum
	{
		PAUSE_BG = 0,
		PAUSE_BG02,
		PAUSE_BG03,
		PAUSE00,//ゲームの再開
		PAUSE01,//１から
		PAUSE02,//タイトルへ
	}MENU;

	CPause();
	~CPause();
	static HRESULT Load(void);//テクスチャを必要分読み込む
	static void UnLoad(void);//使用しているテクスチャを他の処理で消させないようにする
	static CPause *Create(int nUI_NUM, int nPOS_X, int nPOS_Y, int nSIZE_X, int nSIZE_Y);

	HRESULT Init(int nUI_NUM);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetPauseMode(void) { return m_nPauseMode; }
	
		
	//void SetActionUI(int nSelectActionNo, int nMode, int UI_TEX);//アクション選択時の処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[PAUSE_TEX];//共有テクスチャへのポインタ

												 //! <ポリゴンのアニメーションに関する変数>
	int m_nType;
	int m_nPauseMode;
	bool m_PauseFlag;
	//int m_CntAnim;//アニメーションの速さ
	//int m_PatternAnim;//アニメーションの分割数
};




#endif