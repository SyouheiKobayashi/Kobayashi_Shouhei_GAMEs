//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					ナンバー処理 [number.h]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

#ifndef _NUMBER_H_
#define _NUMBER_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"

//==============================================
//マクロ定義
//==============================================
#define TIME_TEX_NAME01	("DATA/TEXTURE/number00.png")

//==============================================
//ナンバー
//==============================================
class CNumber
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CNumber();
	~CNumber();
	static CNumber *Create(void);

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

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	void SetNumber(int nNumber);
	void SetPos(D3DXVECTOR3 pos, float fSpace, int nDigitNum);//(位置情報,間隔,桁分間隔をあける)
	void SetSize(float X, float Y);//ポリゴンのサイズ変更
	void SetScale(int nChangeTime,float fSpeed);
	void SetCol(D3DXCOLOR col);
private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ

	D3DXVECTOR3 m_pos;		//位置
	float m_fSpace;			//桁間隔
	int m_nDigitNum;		//桁数
	float m_SizeX;
	float m_SizeY;
	D3DXCOLOR m_col;

	int m_nChangeCnt;		//拡大縮小の切り替え
	bool bChange;

};




#endif