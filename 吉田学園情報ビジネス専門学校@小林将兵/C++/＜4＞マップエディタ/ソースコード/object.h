//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//オブジェクト処理処理 [object.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _OBJECT_H_
#define _OBJECT_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "sceneX.h"

//==============================================
//マクロ定義
//==============================================
#define OBJ_TEXT ("DATA\\TEXT\\OBJ_LODE.txt")
#define OBJ_TEXTURE_NUM	(64)

//オブジェクトの当たり判定補正数値
#define OBJ_X	(0.0f)
#define OBJ_Y	(0.0f)
#define OBJ_Z	(0.0f)
#define OBJ_UNDER	(28)

//オブジェクト使用数
#define MAX_OBJECT	(256)

//==============================================
//シーンXの派生 → オブジェクト
//==============================================
class CObject : public CSceneX
{
public:
	/*typedef enum
	{
		OBJ_TYPE00 = 0,
		OBJ_TYPE01,
		OBJ_TYPE_MAX
	}OBJ_TYPE;*/

	//コンストラクタ / デストラクタ
	CObject(int nPriority = DRAW_OBJECT, DATA_TYPE dataType = DATA_TYPE_OBJECT);
	~CObject();
	
	//生成
	static CObject *Create(int nObjType, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Debug(void);

	//当たり判定に関する処理↓
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,
		D3DXVECTOR3 *pMove);

	//使用する『オブジェクト』の読み込み
	static HRESULT ObjectLoad(void);
	static void ObjectUnLoad(void);

	//オブジェクトに『使用する画像』の読み込み
	static HRESULT TextureLoad(void);
	static void TextureUnLoad(void);

	//Get関数(自身で扱った情報を他のプログラムで使用する処理)
	static int GetCreateNum(void) { return m_nCreateNum; }
	//static OBJ_TYPE GetObjType(void) { return m_objType; }


private:
	static LPDIRECT3DTEXTURE9 m_pTexture[OBJ_TEXTURE_NUM];				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;									//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;													//位置
	D3DXVECTOR3 m_move;													//移動
	D3DXVECTOR3 m_rot;													//向き

	//外部データからの読み込みに使用する変数
	static int m_nNumObject;							//読み込むオブジェクトの種類数
	static int m_nNumTexture;							//読み込む画像の数
	static char m_aFileNameObject[MAX_OBJECT][256];		//オブジェクトの名前
	static char m_aFileNameTexture[MAX_OBJECT][256];	//オブジェクトに使用する画像・UVの名前

	//オブジェクト情報
	static int m_objType;							//使用するオブジェクトのデータ番号
	static LPD3DXMESH m_pMesh[MAX_OBJECT];
	static LPD3DXBUFFER m_pBuffMat[MAX_OBJECT];
	static DWORD m_pNumMat[MAX_OBJECT];

	//当たり判定に必要な処理
	D3DXVECTOR3 m_VtxMin;
	D3DXVECTOR3 m_VtxMax;

	//キーボード・コントローラーの取得処理
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;

	//生成された数の記憶
	static int m_nCreateNum;
};




#endif