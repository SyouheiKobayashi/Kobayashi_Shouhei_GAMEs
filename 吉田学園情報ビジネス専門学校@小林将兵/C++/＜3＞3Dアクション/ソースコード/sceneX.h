//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//						Xモデル処理処理 [sceneX.h]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _SCENEX_H_
#define _SCENEX_H_

//=================================================
//	include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "scene.h"

//==============================================
//					マクロ定義
//==============================================

//==============================================
//				シーンの派生 → Xモデル
//==============================================
class CSceneX : public CScene
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CSceneX(int nPriority = DRAW_MODEL, DATA_TYPE dataType = DATA_TYPE_MODEL);
	~CSceneX();
	static CSceneX *Create(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					基盤関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DrawShadow(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					追加関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	void Vtx(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	void BindObject(LPD3DXBUFFER buffMat, DWORD numMat, LPD3DXMESH mesh);		//! Xモデル・それに対して使用させる画像情報をもらいそれを適応・描画
	void BindTexture(LPDIRECT3DTEXTURE9 textureInfo);							//! 〃
	void SetPos(D3DXVECTOR3 pos);												//! 位置
	void SetMove(D3DXVECTOR3 move);												//! 移動
	void SetRot(D3DXVECTOR3 rot);												//! 回転
	void SetModelSize(float fModelSizeX, float fModelSizeY, float fModelSizeZ);	//! サイズ
	void SetCol(D3DXCOLOR col);													//! 色

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetModelSize(void) { return m_modelSize; }
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	D3DXMATRIX GetMtxRot(void) { return m_mtxRot; }
	D3DXMATRIX GetMtxTrans(void) { return m_mtxTrans; }

	//当たり判定に関する処理
	D3DXVECTOR3 GetVtxMin(void) { return m_VtxMin; }
	D3DXVECTOR3 GetVtxMax(void) { return m_VtxMax; }

	//外部データの読み込みに関する処理↓
	static char *ReadLine(FILE *pFile, char *pDst);
	static char *GetLIneTop(char *pSrc);
	static int PopString(char *pSrc, char *pDst);


private:
	LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_move;						//移動
	D3DXVECTOR3 m_rot;						//向き
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス
	D3DXMATRIX m_mtxRot, m_mtxTrans;		//計算用マトリックス
	D3DXVECTOR3 m_modelSize;				//モデル拡大縮小

	D3DXMATERIAL *m_pMat;
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_pNumMat;

	//当たり判定に必要な処理
	D3DXVECTOR3 m_VtxMin;	//最小値
	D3DXVECTOR3 m_VtxMax;	//最大値

};




#endif