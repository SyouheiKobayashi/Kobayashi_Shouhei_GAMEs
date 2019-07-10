//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//デバックログ処理 [debugLog.cpp]
//Author : Kobayashi_Sho-hei/小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "debugLog.h"
#include "manager.h"

//=====================================================================
//静的メンバ変数
//=====================================================================
char CDebug::m_aStr[MAX_WORD] = {};
LPD3DXFONT CDebug::m_pFont = NULL;

//==============================================
//コンストラクタ
//==============================================
CDebug::CDebug()
{
	
}

//==============================================
//デストラクタ
//==============================================
CDebug::~CDebug()
{

}

//==============================================
//生成
//==============================================
CDebug*CDebug::Create(void)
{
	CDebug *pDebug = NULL;

	if (pDebug == NULL)
	{
		pDebug = new CDebug;
		pDebug->Init();
	}
	return pDebug;
}

//==============================================
//初期化
//==============================================
void CDebug::Init(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
}

//==============================================
//終了
//==============================================
void CDebug::Uninit(void)
{
	if (m_pFont != NULL)
	{
		delete this;
	}
}

//==============================================
//入力された文字数の表記
//==============================================
void CDebug::DebugLog(char * fmt, ...)
{
	//デバック用
#ifdef _DEBUG
		char CharData[MAX_WORD];
		va_list ap;
		va_start(ap, fmt);

		vsprintf(CharData, fmt, ap);

		va_end(ap);

		strcat(m_aStr, CharData);
#endif
}

//==============================================
//描画表示
//==============================================
void CDebug::Draw(void)
{
	//デバック用
#ifdef _DEBUG
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	strcpy(m_aStr, "");
#endif
}