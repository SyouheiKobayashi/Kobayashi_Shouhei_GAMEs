//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//			オブジェクト処理処理 [object.h]
//		Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _OBJECT_H_
#define _OBJECT_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "sceneX.h"

class CInputKeyboard;
class CInputXPad;
class CInputMouse;
class CSound;
class CPlayer;
//==============================================
//					マクロ定義
//==============================================
#define OBJ_TEXT ("DATA\\TEXT\\OBJ_LODE.txt")
#define OBJ_TEXTURE_NUM	(64)

//オブジェクトの当たり判定補正数値
#define OBJ_X	(10.0f)
#define OBJ_Y	(0.0f)
#define OBJ_Z	(10.0f)
#define OBJ_UNDER	(28)

//オブジェクト使用数
#define MAX_OBJECT	(256)

//==============================================
//			シーンXの派生 → オブジェクト
//==============================================
class CObject : public CSceneX
{
public:

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CObject(int nPriority = DRAW_OBJECT, DATA_TYPE dataType = DATA_TYPE_OBJECT);
	~CObject();
	static CObject *Create(int nObjType, int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					基盤関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					追加関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	void SwitchFlag(void);	//スイッチ系ギミック
	void Gimmick(void);		//ギミック処理のまとめ
	void Debug(void);
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			オブジェクト・UVの読み込み  /解放
	// @   @   @   @   @   @   @   @   @   @   @   @
	static HRESULT ObjectLoad(void);
	static void ObjectUnLoad(void);

	static HRESULT TextureLoad(void);
	static void TextureUnLoad(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	//当たり判定に関する処理↓
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,//上判定
		D3DXVECTOR3 *pMove,int nType);

	bool CollSide(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,//横判定
		D3DXVECTOR3 *pMove, int nType);

	void SetRide(bool bRide);//乗っているか確認
	void SetGimmickFlag(bool bFlag);
	void SetLadderFlag(bool bFlag);
	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	static int GetCreateNum(void) { return m_nCreateNum; }
	bool GetSide(void) { return m_bSide; }
	static int GetSwitchNum(void) { return m_nSwitchNum; }
	bool GetLadderFlag(void) { return m_bLadderFlag; }
	bool GetBlockUP(void) { return m_bBlockUP; }
private:
	static CSound *m_pSound;
	CPlayer *m_pPlayer;

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
	int m_objType;							//使用するオブジェクトのデータ番号
	static LPD3DXMESH m_pMesh[MAX_OBJECT];
	static LPD3DXBUFFER m_pBuffMat[MAX_OBJECT];
	static DWORD m_pNumMat[MAX_OBJECT];

	//当たり判定に必要な処理
	D3DXVECTOR3 m_VtxMin;
	D3DXVECTOR3 m_VtxMax;

	//キーボード・コントローラーの取得処理
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//生成された数の記憶
	static int m_nCreateNum;

	//上に乗っているか？
	bool m_bRide;
	//横に触れているか？
	bool m_bSide;

	//ギミックのフラグ
	bool m_bGimmickFlag;
	int m_nFlagTimeCnt;
	static int m_nSwitchNum;//スイッチが何個生成されたか

	bool m_bLadderFlag;		//梯子のギミック

	bool m_bBlockUP;		//上下ギミック
	int m_nUPCnt;

	bool m_bRotGimmick;		//回転刃ギミックの起動Check
	bool m_bDrillGimmick;	//ドリルギミック
	int m_nDrillCnt;

};




#endif