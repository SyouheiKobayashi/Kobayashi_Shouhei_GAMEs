//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//2Dポリゴン処理処理 [scene2D.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "scene.h"

//==============================================
//シーンの派生 → 2Dポリゴン
//==============================================
class CScene2D : public CScene
{
public:
	//コンストラクタ / デストラクタ
	CScene2D(int nPriority = DRAW_2D, DATA_TYPE dataType = DATA_TYPE_2D);
	~CScene2D();

	//生成
	static CScene2D *Create(void);

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//Set関数(他処理の数値、データをもらい適応 / 主に派生(子)クラスで使用)
	void BindTexture(LPDIRECT3DTEXTURE9 textureInfo);	//! 画像情報をもらい、それを描画
	void SetPos(D3DXVECTOR3 pos);						//! 位置
	void SetSpin(float fSpinSpeed);						//! 回転
	void SetSize(float fSizeX, float fSizeY);			//! サイズ
	void SetCol(D3DXCOLOR col);							//! 色
	void FlashTex(void);								//! 点滅
	void SetTexAnim(int nAnimSpeed, int nWidth,			//! 分割アニメーション
					int nHeight, int nPattern);			//! (アニメーションの速さ、横の分割数、縦の分割数、計算で割り出される)

	//Get関数(自身で扱った情報を他のプログラムで使用する処理)
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
	float fFlashCnt;						//点滅する速度

	//回転
	float m_fAngle;							//角度
	float m_fLengs;							//距離
	float m_fSpinSpeed;						//回転速度

};




#endif