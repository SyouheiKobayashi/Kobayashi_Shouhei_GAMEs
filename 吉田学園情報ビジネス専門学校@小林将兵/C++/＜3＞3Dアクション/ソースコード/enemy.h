//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					エネミー処理 [enemy.h]
//			Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "sceneX.h"

//==============================================
//					マクロ定義
//==============================================
#define ENEMY01_UV	("DATA/TEXTURE/MODEL/enemy01.png")

//プレイヤーステータス
#define ENEMY_SPEED	(1.5f)
#define ENEMY_GRAVITY	(0.5f)
#define ENEMY_PARTS		(11)
#define ENEMY_MAX_PATTERN		(10)
#define ENEMY_JUMP	(7.0f)

//==============================================
//					前方宣言
//==============================================
class CSound;
class CModel;
class CInputKeyboard;
class CInputXPad;
class CInputMouse;
class CPlayer;
//==============================================
//			シーンXの派生 → エネミー
//==============================================
class CEnemy : public CScene
{
public:
	//モデルごとの位置、回転
	typedef struct
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	}KEY;

	//キー情報
	typedef struct
	{
		int nFrame;
		KEY aKey[ENEMY_PARTS];//モデルのパーツ数
	}KEY_INFO;

	//モーション情報
	typedef struct
	{
		int nLoop;
		int nNumKey;
		KEY_INFO aKeyInfo[ENEMY_MAX_PATTERN];//モーションの数
	}MOTION_INFO;

	typedef enum
	{
		NEUTRAL = 0,
		WALK,
		STOP,
		MOTION_MAX
	}MOTION_TYPE;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CEnemy(int nPriority = DRAW_MODEL, DATA_TYPE nObjType = DATA_TYPE_ENEMY);
	~CEnemy();
	static CEnemy *Create(int nAIType,D3DXVECTOR3 pos, D3DXVECTOR3 rot);

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
	void CurrentMode();//現在のモードによって情報を変更する
	void Gravity(void);
	void MOVE(void);//プレイヤーの移動操作
	void JUMP(void);//プレイヤーのジャンプ処理
	void CollObj(void);//オブジェクトとの当たり判定
	void TitleEvent(void);	//タイトル時の演出
	void NULLCheck(void);   //一括NULL化 / 初期化
	void Debug(void);//デバック用

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			モデル・UVの読み込み  /解放
	// @   @   @   @   @   @   @   @   @   @   @   @
	static HRESULT ModelLoad(void);
	static void ModelUnLoad(void);
	static HRESULT TextureLoad(void);
	static void TextureUnLoad(void);
	
	// @   @   @   @   @   @   @   @   @   @   @   @
	//					モーション関連
	// @   @   @   @   @   @   @   @   @   @   @   @
	void ModelLode(void);							//モデルの読み込み
	void MotionLoad(void);							//モーションの読み込み
	void UpdateMotion(void);						//モーションの更新

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	//当たり判定に関する処理
	void Vtx(void);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,
		D3DXVECTOR3 *pMove);
	void SetPos(D3DXVECTOR3 pos);
	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	static int GetCreateNum(void) { return m_nCreateNum; }

	D3DXVECTOR3 GetPos(void) {return m_pos; }		//位置
	D3DXVECTOR3 GetMove(void) { return m_move; }	//移動量
	D3DXVECTOR3 GetRot(void) { return m_rot; }		//向き
	bool GetSearchCheck(void) { return m_bSearchCheck; }//エネミー範囲内か
	bool GetMoveStop(void) { return m_bMoveStop; }//敵がダメージを受けて止まっているか
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_posOld;					//過去の位置情報
	D3DXVECTOR3 m_move;						//移動
	D3DXVECTOR3 m_rot;						//向き
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	//他処理のポインタ
	static CSound *m_pSound;
	CCamera *m_pCamera;
	CObject *m_pObj;
	CPlayer * m_pPlayer;
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			モデルの読み込み・親子関係
	// @   @   @   @   @   @   @   @   @   @   @   @
	CModel *m_pModel[ENEMY_PARTS];
	static LPD3DXMESH m_pMesh[ENEMY_PARTS];
	static LPD3DXBUFFER m_pBuffMat[ENEMY_PARTS];
	static DWORD m_pNumMat[ENEMY_PARTS];
	static int m_nNumModel;//モデルパーツ数
	static char m_aFileNameModel[ENEMY_PARTS][256];//読み込むモデル名

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				モーションに関する情報
	// @   @   @   @   @   @   @   @   @   @   @   @
	int m_nNumKey;				//キーの総数
	KEY_INFO *m_pKeyInfo;		//キー情報のポインタ
	int m_nKey;					//現在のキー
	int m_nCntFrame;			//モーションカウンター
	static int m_nNumParts;		//パーツ数
	static int m_aIndexParent[ENEMY_PARTS];
	static KEY m_aKeyOffseet[ENEMY_PARTS];
	MOTION_INFO m_aMotionInfo[MOTION_MAX];		//モーション最大数
	KEY_INFO m_aKeyInfo000[ENEMY_MAX_PATTERN];	//モーションの種類
	MOTION_TYPE	motionType;						//初期のモーション
	int  m_nUseMotionType;						//使用するモーション(ここでは数値を次のモーションに変更させるために加算していく処理があるためint型で)
	bool m_bLoopCheck;							//ループするかしないかのチェック

	//キーボード・コントローラーの取得処理
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//生成された数の記憶
	static int m_nCreateNum;

	//プレイヤーが何に乗っているのか?
	bool m_bMeshcheck;				//メッシュに乗っているか?
	bool m_bObjRide[OBJ_CREATE];	//objに乗っているか?
	int m_nCurrentObj;				//現在プレイヤーがどのブロックに乗っているか
	bool m_bObjSide[OBJ_CREATE];	//objの横にいるか
	int m_nCurrentSideObj;			//現在プレイヤーがどのブロックの横にいるか

	float m_fRotation;	//プレイヤーの軸回転
	D3DXVECTOR3 m_Sabun;//滑らかな方向転換のために使う

	//当たり判定に必要な処理
	D3DXVECTOR3 m_VtxMin;	//最小値
	D3DXVECTOR3 m_VtxMax;	//最大値
	bool m_bRide;			//上に乗っているか？
	
	D3DXVECTOR3 m_OriginPos;//生成地

	int m_nTitleEventCnt;//タイトル時の演出
	bool m_bTitleEvent;
	bool m_bStop;

	bool m_bSearchCheck;//エネミーの範囲内に入っているか？
	
	//踏まれた際の処理
	bool	m_bMoveStop;
	int		m_MoveStopTime;

	int m_nAIType;//行動パターン
};




#endif