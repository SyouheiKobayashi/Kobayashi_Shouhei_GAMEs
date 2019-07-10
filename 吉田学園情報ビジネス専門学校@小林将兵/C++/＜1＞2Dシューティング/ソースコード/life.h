//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// ライフ処理 [life.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _LIFE_H_
#define _LIFE_H_
#include "main.h"
#include "scene.h"

#define MAX_LIFE	(15)
class CGauge;
//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ ライフCLASS(<Scene>の派生クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CLife : public CScene
{
public:
	CLife();
	~CLife();

	static HRESULT Load(void);//テクスチャを必要分読み込む
	static void UnLoad(void);//使用しているテクスチャを他の処理で消させないようにする

	static CLife *Create(void);//スコアの生成処理

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos);//得た情報を反映させる

	void SetLife(int nLife);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;			// ポリゴンの位置

	CGauge *m_apGauge[MAX_LIFE];//number処理を扱いため
	static int m_nLife;
	static int m_nLifeGauge[MAX_LIFE];

};




#endif