//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//3Dポリゴン処理処理 [scene3D.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "scene.h"

//==============================================
//シーンの派生 → 3Dポリゴン
//==============================================
class CScene3D : public CScene
{
public:
	//コンストラクタ / デストラクタ
	CScene3D(int nPriority = DRAW_3D, DATA_TYPE dataType = DATA_TYPE_3D);
	~CScene3D();

	//生成
	static CScene3D *Create();

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//Set関数(他処理の数値、データをもらい適応 / 主に派生(子)クラスで使用)
	void BindTexture(LPDIRECT3DTEXTURE9 textureInfo);	//! 画像情報をもらい、それを描画
	void SetPos(D3DXVECTOR3 pos);						//! 位置
	void SetSize(float fSizeX, float fSizeY, float fSizeZ);			//! サイズ
	void SetCol(D3DXCOLOR col);							//! 色
	void FlashTex(void);								//! 点滅
	void SetTexAnim(int nAnimSpeed, int nWidth,			//! 分割アニメーション
		int nHeight, int nPattern);						//! (アニメーションの速さ、横の分割数、縦の分割数、計算で割り出される)


private:
	LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_rot;						//向き
	D3DXCOLOR m_col;						//色
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス
	float m_fSizeX;							//Xサイズ
	float m_fSizeY;							//Yサイズ
	float m_fSizeZ;							//Zサイズ

	//点滅に関する処理
	bool m_bFlash;							//透明率の切り替え
	float fFlashCnt;						//点滅する速度


};




#endif