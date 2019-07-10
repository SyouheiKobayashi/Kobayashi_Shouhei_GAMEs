//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 血液ゲージ処理 [bloodGauge.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _BLOODGAUGE_H_
#define _BLOODGAUGE_H_
#include "main.h"
#include "scene.h"

#define MAX_BLOOD	(16)
class CGauge;
//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ 血液CLASS(<Scene>の派生クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CBloodGauge : public CScene
{
public:
	CBloodGauge();
	~CBloodGauge();

	static HRESULT Load(void);//テクスチャを必要分読み込む
	static void UnLoad(void);//使用しているテクスチャを他の処理で消させないようにする

	static CBloodGauge *Create(void);//スコアの生成処理

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos);//得た情報を反映させる

	

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;			// ポリゴンの位置

	CGauge *m_apGauge[MAX_BLOOD];//number処理を扱いため
	static int m_nBlood;
	static int m_nBloodGauge[MAX_BLOOD];

};




#endif