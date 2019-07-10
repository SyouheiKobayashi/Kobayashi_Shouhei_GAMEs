//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					2Dポリゴン処理 [polygon2D.h]
//			Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _POLYGON2D_H_
#define _POLYGON2D_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "scene2D.h"

//==============================================
//					マクロ定義
//==============================================
#define POLYGON2D_MAX	(27)

class CInputMouse;
//==============================================
//		scene2Dの派生 → 2Dポリゴン
//==============================================
class CPolygon2D : public CScene2D
{
public:

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CPolygon2D(int nPriority = DRAW_2D, DATA_TYPE nObjType = DATA_TYPE_2D);
	~CPolygon2D();
	static CPolygon2D *Create(int nTexType,bool bRotation , D3DXVECTOR3 pos , D3DXCOLOR col,float nSizeX, float nSizeY,
								int nAnimSpeed, int nWidth, int nHight, bool bLoop);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					基盤関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				画像の読み込み・解放
	// @   @   @   @   @   @   @   @   @   @   @   @
	static HRESULT TextureLoad(void);
	static void TextureUnLoad(void);

	void Debug(void);//デバック処理

private:
	static const char *m_apTexName[];//使用するテクスチャ
	static LPDIRECT3DTEXTURE9 m_apTexture[POLYGON2D_MAX];	//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//頂点バッファへのポインタ
	D3DXVECTOR3	m_pos;								//ポリゴンの位置
	CInputMouse *m_pInputMouse;

	int m_nPolygonType;	//2Dポリゴン番号の割り振り
	bool m_bRotation;	//回転させるか

	//アニメーションに関する変数
	int m_nAnimSpeed;
	int m_nWidth;
	int m_nHight;
	bool m_bLoop;
};




#endif