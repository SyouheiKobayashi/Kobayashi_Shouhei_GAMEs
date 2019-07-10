//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// ゲージ処理 [gauge.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _GAUGE_H_
#define _GAUGE_H_
#include "main.h"

//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ ゲージCLASS(基本クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CGauge
{
public:
	CGauge();
	~CGauge();

	static CGauge *Create(void);//数字・ナンバーの生成処理

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(int nNumber);
	void SetPos(D3DXVECTOR3 pos, int nSpace, int nCnt);//(位置情報,間隔,桁分間隔をあける)
	void SetSize(float X, float Y);//ポリゴンのサイズ変更

	
private:
	//! メンバ変数↓
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ

	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	float					m_SizeX;
	float					m_SizeY;


};




#endif