//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 数字・ナンバー処理 [number.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include "main.h"

//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ 数字・ナンバーCLASS(基本クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CNumber
{
public:
	CNumber();
	~CNumber();

	static HRESULT Load(void);//テクスチャを必要分読み込む
	static void UnLoad(void);//使用しているテクスチャを他の処理で消させないようにする
	static CNumber *Create(void);//数字・ナンバーの生成処理

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(int nNumber);
	void SetPos(D3DXVECTOR3 pos, int nSpace,int nCnt);//(位置情報,間隔,桁分間隔をあける)
	void SetSize(float X, float Y);//ポリゴンのサイズ変更


	//D3DXVECTOR3 GetPos(void);//生成した数字・ナンバーの位置を取得する
	//void SetSize(float fWIDTH, float fHEIGHT);//数字・ナンバーのサイズ変更

	//void BindTexture(LPDIRECT3DTEXTURE9 m_pShareTexture);

private:
	//! メンバ変数↓
	static LPDIRECT3DTEXTURE9	m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ

	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	float					m_SizeX;
	float					m_SizeY;


};




#endif