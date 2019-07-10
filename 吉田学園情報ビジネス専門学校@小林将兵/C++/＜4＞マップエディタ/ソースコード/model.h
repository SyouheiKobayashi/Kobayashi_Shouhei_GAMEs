//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//モデル処理 [model.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _MODEL_H_
#define _MODEL_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "scene.h"

//==============================================
//マクロ定義
//==============================================
#define MODEL_NAME	("DATA/MODEL/car000.x")


//==============================================
//モデル
//==============================================
class CModel
{
public:
	//コンストラクタ / デストラクタ
	CModel();
	~CModel();

	//生成
	static CModel *Create(D3DXVECTOR3 pos);

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	void InitDraw(void);

	//使用するモデル・画像の読み込み
	void BindModel(LPD3DXBUFFER buffMat, DWORD numMat, LPD3DXMESH mesh);
	void BindTexture(LPDIRECT3DTEXTURE9 textureInfo);

	void SetParent(CModel *pModel);//パーツごとの親を決める


	void SetPos(D3DXVECTOR3 pos);//位置
	void SetRot(D3DXVECTOR3 rot);//向き

	//Get関数(自身で扱った情報を他のプログラムで使用する処理)
	static int GetMaxCreateNum(void) { return m_nMaxCreateNum;}
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_move;						//移動
	D3DXVECTOR3 m_rot;						//向き
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	//モデル情報
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_pNumMat;

	CModel *m_pParent;//親モデルのポインタ

	static int m_nMaxCreateNum;

	int m_nInitDrawCheck;//一回しか通さないようにチェックするための変数
};




#endif