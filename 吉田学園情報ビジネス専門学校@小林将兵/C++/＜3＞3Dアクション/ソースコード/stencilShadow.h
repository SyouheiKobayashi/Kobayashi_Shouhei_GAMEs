//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//ステンシルシャドウ処理処理 [stencilShadow.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _STENCILSHADOW_H_
#define _STENCILSHADOW_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "sceneX.h"

//==============================================
//マクロ定義
//==============================================
#define STENCIL_TEXT ("DATA\\TEXT\\OBJ_LODE.txt")
#define STENCIL_TEXTURE_NUM	(1)

//オブジェクトの当たり判定補正数値
#define STENCIL_X	(0.0f)
#define STENCIL_Y	(0.0f)
#define STENCIL_Z	(0.0f)

//オブジェクト使用数
#define MAX_STENCIL	(1)

class CPolygon2D;

//==============================================
//シーンXの派生 → オブジェクト
//==============================================
class CStencilShadow : public CSceneX
{
public:

	//コンストラクタ / デストラクタ
	CStencilShadow(int nPriority = DRAW_SHADOW, DATA_TYPE dataType = DATA_TYPE_OBJECT);
	~CStencilShadow();
	
	//生成
	static CStencilShadow *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Debug(void);

	//使用する『オブジェクト』の読み込み
	static HRESULT ObjectLoad(void);
	static void ObjectUnLoad(void);

	//オブジェクトに『使用する画像』の読み込み
	static HRESULT TextureLoad(void);
	static void TextureUnLoad(void);

	//Get関数(自身で扱った情報を他のプログラムで使用する処理)
	static int GetCreateNum(void) { return m_nCreateNum; }

	static CPolygon2D *GetPolygon2D(void) { return m_pPolygon2D; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[STENCIL_TEXTURE_NUM];				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;									//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;													//位置
	D3DXVECTOR3 m_move;													//移動
	D3DXVECTOR3 m_rot;													//向き

	//外部データからの読み込みに使用する変数
	static int m_nNumObject;							//読み込むオブジェクトの種類数
	static int m_nNumTexture;							//読み込む画像の数
	static char m_aFileNameObject[MAX_STENCIL][256];		//オブジェクトの名前
	static char m_aFileNameTexture[MAX_STENCIL][256];	//オブジェクトに使用する画像・UVの名前

	//オブジェクト情報
	static int m_objType;							//使用するオブジェクトのデータ番号
	static LPD3DXMESH m_pMesh[MAX_STENCIL];
	static LPD3DXBUFFER m_pBuffMat[MAX_STENCIL];
	static DWORD m_pNumMat[MAX_STENCIL];

	//当たり判定に必要な処理
	D3DXVECTOR3 m_VtxMin;
	D3DXVECTOR3 m_VtxMax;

	//キーボード・コントローラーの取得処理
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//生成された数の記憶
	static int m_nCreateNum;

	static CPolygon2D *m_pPolygon2D;


};




#endif