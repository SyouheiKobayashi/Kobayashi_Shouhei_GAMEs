//@@@@@@@@@@@@@@@@@
// Q[W [gauge.h]
// Author : Kobayashi_Sho-hei(¬Ρ «Ί)
//@@@@@@@@@@@@@@@@@
#ifndef _GAUGE_H_
#define _GAUGE_H_
#include "main.h"

//@@@@@@@@@@@@@@@@@
//+ Q[WCLASS(ξ{NX)
//@@@@@@@@@@@@@@@@@
class CGauge
{
public:
	CGauge();
	~CGauge();

	static CGauge *Create(void);//Eio[ΜΆ¬

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(int nNumber);
	void SetPos(D3DXVECTOR3 pos, int nSpace, int nCnt);//(Κuξρ,Τu,ͺΤuπ ―ι)
	void SetSize(float X, float Y);//|SΜTCYΟX

	
private:
	//! oΟ«
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// Έ_obt@ΦΜ|C^

	D3DXVECTOR3				m_pos;			// |SΜΚu
	float					m_SizeX;
	float					m_SizeY;


};




#endif