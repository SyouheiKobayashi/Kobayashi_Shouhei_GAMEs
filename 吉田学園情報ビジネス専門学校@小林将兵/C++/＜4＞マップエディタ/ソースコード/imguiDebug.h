//@@@@@@@@@@@@@@@@@
//imgui [imguiDebug.h]
//Author : Kobayashi_Sho-hei / ¬Ñ «º
//@@@@@@@@@@@@@@@@@
#ifndef _IMGUI_H_
#define _IMGUI_H_

//=================================================
//include / ¼Ìf[^ER[hÌÄÑoµEp
//=================================================
#include "main.h"

//==============================================
//imgui
//==============================================
class CImguiDebug
{
public:
	
	//RXgN^ / fXgN^
	CImguiDebug();
	~CImguiDebug();

	//îÕÆÈéÖ(ú» / I¹ / XV / `æ)
	void Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Tutorial(void);	//L[{[hà¾«
	void Tutorial02(void);	//}EXà¾«

private:

};




#endif