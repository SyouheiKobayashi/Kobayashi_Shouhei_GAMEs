//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//レンダリング処理 [renderer.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _RENDERER_H_
#define _RENDERER_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"

//==============================================
//レンダリング
//==============================================
class CRenderer
{
public:
	//コンストラクタ / デストラクタ
	CRenderer();
	~CRenderer();

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//Get関数(使用した変数などの情報を他のプログラムで使用する処理)
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

private:
	LPDIRECT3D9				m_pD3D;			//Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;	//Deviceオブジェクト(描画に必要)

	//デバック用
#ifdef _DEBUG
	LPD3DXFONT				m_pFont;		//フォントへのポインタ
#endif
};

#endif