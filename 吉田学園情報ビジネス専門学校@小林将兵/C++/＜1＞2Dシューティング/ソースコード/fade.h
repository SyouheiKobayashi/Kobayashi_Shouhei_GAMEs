//@@@@@@@@@@@@@@@@@
// tF[h [fade.h]
// Author : Kobayashi_Sho-hei(¬Ρ «Ί)
//@@@@@@@@@@@@@@@@@
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "manager.h"

//@@@@@@@@@@@@@@@@@
//+ tF[hCLASS(}l[WhΆ)
//@@@@@@@@@@@@@@@@@
class CFade : public CManager
{
public:
	typedef enum
	{
		FADE_NONE = 0,// gp΅ΔΘ’σΤ
		FADE_IN,// tF[hCσΤ
		FADE_OUT,// tF[hAEgσΤ
		FADE_MAX
	} FADE;

	CFade();
	~CFade();

	static CFade *Create(void);//tF[hΜΆ¬

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetFade(MODE modeNext);
	static FADE GetFade(void) { return m_fade; }


private:
	//! oΟ«
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// Έ_obt@ΦΜ|C^
	 static FADE m_fade;					// »έΜtF[hσΤπL―
	MODE m_modeNext;				// Μ[h
	D3DXCOLOR m_colorFade;			// tF[hΜF

};




#endif