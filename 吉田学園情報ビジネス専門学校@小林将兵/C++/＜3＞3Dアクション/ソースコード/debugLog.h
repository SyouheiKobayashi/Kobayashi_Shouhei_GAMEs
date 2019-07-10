//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//デバックログ処理 [debugLog.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _DEBUG_H_
#define _DEBUG_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"

//==============================================
//マクロ定義
//==============================================
#define MAX_WORD	(1024)//最大文字数

//==============================================
//派生なし → デバックログ
//==============================================
class CDebug
{
public:
	//コンストラクタ / デストラクタ
	CDebug();
	~CDebug();

	//生成
	static CDebug *Create(void);

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	void Init(void);
	void Uninit(void);
	static void DebugLog(char * fmt,...);//この関数を使用して画面上にデバック表示を行う
	static void Draw(void);

	
private:
	static LPD3DXFONT m_pFont;
	static char m_aStr[MAX_WORD];//文字列の保管
	
};

#endif