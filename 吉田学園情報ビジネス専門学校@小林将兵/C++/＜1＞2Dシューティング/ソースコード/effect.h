//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// エフェクト処理 [effect.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"
#include "scene2D.h"

//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ エフェクトCLASS(<scene2D>の派生クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CEffect : public CScene2D
{
public:
	CEffect();
	~CEffect();
	static HRESULT Load(void);//テクスチャを必要分読み込む
	static void UnLoad(void);//使用しているテクスチャを他の処理で消させないようにする
	static CEffect *Create(D3DXVECTOR3 pos, D3DXCOLOR col);//弾の生成(位置情報)

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//共有テクスチャへのポインタ
	//D3DXVECTOR3 m_move;//移動処理

	//! <ポリゴンのアニメーションに関する変数>
	//int m_CntAnim;//アニメーションの速さ
	//int m_PatternAnim;//アニメーションの分割数

	//D3DXVECTOR3 m_Pos;		// 位置
	//D3DXCOLOR m_col;			// 色
	float m_fRadius;			// 半径(大きさ)
	int m_nLife;				// 表示時間(寿命)

	
};

#endif