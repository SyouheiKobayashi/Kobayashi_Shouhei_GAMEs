//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//imgui処理 [imguiDebug.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _IMGUI_H_
#define _IMGUI_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"

//==============================================
//imgui処理
//==============================================
class CImguiDebug
{
public:
	
	//コンストラクタ / デストラクタ
	CImguiDebug();
	~CImguiDebug();

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	void Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Tutorial(void);	//キーボード説明書き
	void Tutorial02(void);	//マウス説明書き

private:

};




#endif