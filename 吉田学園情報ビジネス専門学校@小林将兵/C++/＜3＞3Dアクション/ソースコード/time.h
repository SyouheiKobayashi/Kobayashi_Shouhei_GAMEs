//@@@@@@@@@@@@@@@@@
//					Τ [time.h]
//				Author : Kobayashi_Sho-hei / ¬Ρ «Ί
//@@@@@@@@@@@@@@@@@
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#include "scene.h"

#define MAX_DIGIT	(3)
class CNumber;

//==============================================
//				V[ΜhΆ ¨ 2D|S
//==============================================
class CTime : public CScene
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			RXgN^EfXgN^EΆ¬
	// @   @   @   @   @   @   @   @   @   @   @   @
	CTime(int nPriority = DRAW_2D, DATA_TYPE nObjType = DATA_TYPE_2D);
	~CTime();
	static CTime *Create(int fTime,D3DXVECTOR2 size, D3DXVECTOR2 pos);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					ξΥΦ
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetTime(void) { return m_nTime; }//»έΜΤπζΎ
	void SetDemeritTime(int nTime);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//Έ_obt@ΦΜ|C^

	CNumber *m_apNumber[MAX_DIGIT];			//numberπ΅’½ί

	int m_nTime;		//»έΜΤ
	int m_nTimeSet;	//ΤΜέθ
	D3DXVECTOR2 m_size; //TCY
	D3DXVECTOR2 m_pos;	//Κu

	int m_nTimeDigit[MAX_DIGIT];//
};




#endif