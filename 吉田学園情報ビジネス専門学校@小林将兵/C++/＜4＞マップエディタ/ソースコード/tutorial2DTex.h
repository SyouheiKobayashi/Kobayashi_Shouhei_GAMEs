//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//チュートリアル用画像処理処理 [tutorial2DTex.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _TUTORIAL2DTEX_H_
#define _TUTORIAL2DTEX_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "scene2D.h"

//==============================================
//マクロ定義
//==============================================
#define TEX_MAX	(20)

//==============================================
//scene2Dの派生 → チュートリアル用画像
//==============================================
class CTutorial2DTex : public CScene2D
{
public:

	//コンストラクタ / デストラクタ
	CTutorial2DTex(int nPriority = DRAW_2D, DATA_TYPE nObjType = DATA_TYPE_2D);
	~CTutorial2DTex();

	//生成
	static CTutorial2DTex *Create(int nTexType,D3DXVECTOR3 pos , float nSizeX, float nSizeY);

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//オブジェクトに『使用する画像』の読み込み
	static HRESULT TextureLoad(void);
	static void TextureUnLoad(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_MAX];	//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//頂点バッファへのポインタ
	D3DXVECTOR3	m_pos;								//ポリゴンの位置


};




#endif