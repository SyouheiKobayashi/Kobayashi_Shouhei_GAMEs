//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// レンダリング処理 [renderer.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"

//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ レンダリングCLASS(基本クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//デバイス情報の所得↓(ポインタを返すだけの場合/メリット:ソースに書かなくても言いこと)
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

private:
	

#ifdef _DEBUG
	void DrawFPS(void);//FPS表記
#endif

	//! メンバ変数↓
	LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)

	


#ifdef _DEBUG
	LPD3DXFONT				m_pFont;			// フォントへのポインタ
#endif


};

#endif