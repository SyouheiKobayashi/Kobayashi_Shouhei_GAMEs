//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 背景処理 [bg.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "scene.h"

#define MAX_TEXTURE	(6)//画像最大数

//クラスの呼び出し
class CScene2D;
//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ 背景CLASS(<Scene>の派生クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CBG : public CScene
{
public:

	CBG();
	~CBG();

	static HRESULT Load(void);//テクスチャを必要分読み込む
	static void UnLoad(void);//使用しているテクスチャを他の処理で消させないようにする

	static CBG *Create(void);//ポリゴンの生成処理

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);//得た情報を反映させる


private:
	//! メンバ変数↓
	static LPDIRECT3DTEXTURE9 m_aTexture[MAX_TEXTURE];
	CScene2D *m_apScene2D[MAX_TEXTURE];

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ

	D3DXVECTOR3				m_pos;			// ポリゴンの位置

	int m_nScrollCnt;//スクロール加算用
};




#endif