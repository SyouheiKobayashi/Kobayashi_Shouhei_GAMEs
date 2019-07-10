//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					mesh処理 [mesh.h]
//			Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "scene.h"

//==============================================
//					マクロ定義
//==============================================
#define MESH_TEX01	("DATA/TEXTURE/mesh01.png")
#define MESH_TEX02	("DATA/TEXTURE/mesh02.png")

class CPlayer;
//==============================================
//		sceneの派生 → メッシュ
//==============================================
class CMeshField : public CScene
{
public:
	typedef enum
	{
		XZ = 0,
		XY,
		MAX
	}MESH_TYPE;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CMeshField(int nPriority = DRAW_3D, DATA_TYPE nObjType = DATA_TYPE_3D);
	~CMeshField();
	static CMeshField *Create(int nTexType,MESH_TYPE type ,D3DXVECTOR3 startPos ,int nSize,int nNumX, int nNumZ);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					基盤関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					その他関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	void MeshNormaVector(void);//法線情報による明暗表現


	float GetHight(D3DXVECTOR3 pos);				//メッシュの高さを反映させるための情報を得る
	float GetDotPosY(void) { return m_DotPosY; }
	bool GetCheck(void) { return m_bCheck; }		//メッシュに触れているか / 乗っているか

	//起伏表現
	void SetHight(D3DXVECTOR3 pos, float fValue, float fRange);

private:
	LPDIRECT3DTEXTURE9		m_pTexture[2];	//テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//インデックスのポインタ

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_rot;		//向き
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス

	//法線に関する変数
	D3DXVECTOR3 m_nor[6];
	D3DXVECTOR3 m_vec0;
	D3DXVECTOR3 m_vec1;
	D3DXVECTOR3 m_vec2;
	D3DXVECTOR3 m_vec3;

	int m_nNumIndxMeshField;	//インデックス数
	int m_nNumPolygonMeshField;	//ポリゴン数
	int m_nNumVertexMeshField;	//頂点数

	CPlayer *m_pPlayer;

	bool m_bCheck;	//乗っているのか?

	float m_DotPosY;//プレイヤーの位置加算用

	int m_nSelectTex;			//使用する画像
	int m_nMeshType;			//縦か横か
	D3DXVECTOR3 m_startPos;		//生成地点
	int m_nSize;				//一つ分のサイズ
	int m_nNumX;				//横の個数
	int m_nNumZ;				//縦の個数

};




#endif