//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//				3Dポリゴン処理 [polygon3D.h]
//			Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _POLYGON3D_H_
#define _POLYGON3D_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "billboard.h"

#define POLYGON3D_MAX	(11)

//==============================================
//			ビルボードの派生 → 3Dポリゴン
//==============================================
class CPolygon3D : public CBillboard
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CPolygon3D(int nPriority = DRAW_BILLBOARD, DATA_TYPE nObjType = DATA_TYPE_BILLBOARD);
	~CPolygon3D();
	static CPolygon3D *Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nAnimSpeed, int nWidth, int nHight, bool bLoop);

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


private:
	//キーボード・コントローラーの取得処理
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	static const char *m_apTexName[];//使用するテクスチャ
	static LPDIRECT3DTEXTURE9 m_apTexture[POLYGON3D_MAX];//共有テクスチャへのポインタ
	
	int m_nType;
	 
	float m_fRadius;//半径(大きさ)
	int m_nLife;//表示時間(寿命)

	//アニメーションに関する変数
	int m_nAnimSpeed;
	int m_nWidth;
	int m_nHight;
	bool m_bLoop;
	int m_nCnt;
};

#endif