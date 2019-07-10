//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					2Dポリゴン処理 [scene2D.h]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "scene.h"

//==============================================
//				シーンの派生 → 2Dポリゴン
//==============================================
class CScene2D : public CScene
{
public:

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CScene2D(int nPriority = DRAW_2D, DATA_TYPE dataType = DATA_TYPE_2D);
	~CScene2D();
	static CScene2D *Create(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					基盤関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	void BindTexture(LPDIRECT3DTEXTURE9 textureInfo);	//画像情報をもらい、それを描画
	void SetPos(D3DXVECTOR3 pos);						//位置
	void SetMove(D3DXVECTOR3 move);						//移動
	void SetSpin(float fSpinSpeed);						//回転
	void SetSize(float fSizeX, float fSizeY);			//サイズ
	void SetCol(D3DXCOLOR col);							//色
	void FlashTex(void);								//点滅
	void SetTexAnim(int nAnimSpeed, int nWidth,			//分割アニメーション
					int nHeight, bool bLoop);			//(アニメーションの速さ、横の分割数、縦の分割数、ループの可否)
	void SetAnimSize(float fCnt,int nSpeed);			//拡大・縮小アニメーション
	void SetScroll(float fSpeed, bool bVector, int nType);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXCOLOR GetCol(void) { return m_col; }

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;			//ポリゴンの位置
	D3DXCOLOR m_col;						//色
	float m_fSizeX;							//横サイズ
	float m_fSizeY;							//縦サイズ

	//点滅に関する処理
	bool m_bFlash;							//透明率の切り替え
	float m_fFlashCnt;						//点滅する速度

	//回転
	float m_fAngle;							//角度
	float m_fLengs;							//距離
	float m_fSpinSpeed;						//回転速度

	//アニメーション処理
	int m_nCnt;
	int m_PatternAnim;

	//サイズ変更カウント
	int m_nSizeCnt;
	bool m_bSizeChange;

	//スクロール
	int m_nScrollCnt;
};




#endif