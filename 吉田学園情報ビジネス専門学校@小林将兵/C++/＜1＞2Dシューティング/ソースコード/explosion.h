//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 爆発エフェクト処理 [explosion.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"
#include "scene2D.h"

//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ 爆発エフェクトCLASS(<scene2D>の派生クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CExplosion : public CScene2D
{
public:
	CExplosion();
	~CExplosion();
	static HRESULT Load(void);//テクスチャを必要分読み込む
	static void UnLoad(void);//使用しているテクスチャを他の処理で消させないようにする
	static CExplosion *Create(D3DXVECTOR3 pos);//弾の生成(位置情報)

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//共有テクスチャへのポインタ
	D3DXVECTOR3 m_move;//移動処理

	 //! <ポリゴンのアニメーションに関する変数>
	int m_CntAnim;//アニメーションの速さ
	int m_PatternAnim;//アニメーションの分割数

};

#endif