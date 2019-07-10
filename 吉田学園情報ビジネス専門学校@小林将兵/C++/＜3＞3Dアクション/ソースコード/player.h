//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					プレイヤー処理 [player.h]
//			Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "sceneX.h"
#include "game.h"
//==============================================
//					マクロ定義
//==============================================
#define MODEL_UV	("DATA/TEXTURE/MODEL/player.png")

//プレイヤーステータス
#define PLAYER_SPEED	(2.2f)
#define PLAYER_GRAVITY	(0.5f)
#define PLAYER_PARTS		(11)
#define PLAYER_MAX_PATTERN		(10)
#define PLAYER_JUMP	(7.0f)

//==============================================
//					前方宣言
//==============================================
class CSound;
class CModel;
class CScene3D;
class CObject;
class CEnemy;
//==============================================
//			シーンXの派生 → プレイヤー
//==============================================
class CPlayer : public CScene
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
		KEY aKey[PLAYER_PARTS];//モデルのパーツ数
	}KEY_INFO;

	//モーション情報
	typedef struct
	{
		int nLoop;
		int nNumKey;
		KEY_INFO aKeyInfo[PLAYER_MAX_PATTERN];//モーションの数
	}MOTION_INFO;

	typedef enum
	{
		NEUTRAL = 0,
		WALK,
		RANKING,
		EVENT,
		WINDOW,
		WINDOW_WAIT,
		MOTION_MAX
	}MOTION_TYPE;

	typedef enum
	{
		LEFT = 0,
		RIGHT,
		FRONT,
		BACK,
		JUDGE_MAX
	}JUDGE_COLL;

	typedef enum
	{
		OBJ = 0,
		ENEMY,
		TYPE_MAX
	}COLL_TYPE;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CPlayer(int nPriority = DRAW_MODEL, DATA_TYPE nObjType = DATA_TYPE_PLAYER);
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

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
	void CurrentMode();		//現在のモードによって情報を変更する
	void Gravity(void);
	void MOVE(void);		//プレイヤーの移動操作
	void JUMP(void);		//プレイヤーのジャンプ処理
	void Polygon3D(void);
	void CollObj(void);		//オブジェクトとの当たり判定
	void CollEnemy(void);	//オブジェクトとの当たり判定
	void LadderEvent(void);	//梯子のイベント
	void SetDamageAction(float fX,float fY,int nType);	//ダメージを受けた際の演出(タイプは敵なのか、ギミックobjか)
	void TitleEvent(void);	//タイトル時の演出
	void NULLCheck(void);   //一括NULL化 / 初期化
	void Debug(void);		//デバック用

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
	void SetPos(D3DXVECTOR3 pos);
	void SetDamageState(int nType, bool bState);
	void SetKnockBack(int nState);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	D3DXVECTOR3 GetPos(void) {return m_pos; }		//位置
	D3DXVECTOR3 GetMove(void) { return m_move; }	//移動量
	D3DXVECTOR3 GetRot(void) { return m_rot; }		//向き
	int GetSideObjNum(void) { return m_nCurrentSideObj; }
	bool GetSide(int nCnt) { return m_bObjSide[nCnt]; }
	int GetCurrentObj(void) { return m_nCurrentObj; }
	bool GetOutStage(void) { return m_bOutStage; }
	bool GetAutoJump(void) { return m_bAutoJump; }

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
	CScene3D *m_pScene3D[SCENE3D_CREATE];
	CObject *m_pObj;
	CEnemy * m_pEnemy;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			モデルの読み込み・親子関係
	// @   @   @   @   @   @   @   @   @   @   @   @
	CModel *m_pModel[PLAYER_PARTS];
	static LPD3DXMESH m_pMesh[PLAYER_PARTS];
	static LPD3DXBUFFER m_pBuffMat[PLAYER_PARTS];
	static DWORD m_pNumMat[PLAYER_PARTS];
	static int m_nNumModel;//モデルパーツ数
	static char m_aFileNameModel[PLAYER_PARTS][256];//読み込むモデル名

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				モーションに関する情報
	// @   @   @   @   @   @   @   @   @   @   @   @
	int m_nNumKey;				//キーの総数
	KEY_INFO *m_pKeyInfo;		//キー情報のポインタ
	int m_nKey;					//現在のキー
	int m_nCntFrame;			//モーションカウンター
	static int m_nNumParts;		//パーツ数
	static int m_aIndexParent[PLAYER_PARTS];
	static KEY m_aKeyOffseet[PLAYER_PARTS];
	MOTION_INFO m_aMotionInfo[MOTION_MAX];		//モーション最大数
	KEY_INFO m_aKeyInfo000[PLAYER_MAX_PATTERN];	//モーションの種類
	MOTION_TYPE	motionType;						//初期のモーション
	int  m_nUseMotionType;						//使用するモーション(ここでは数値を次のモーションに変更させるために加算していく処理があるためint型で)
	bool m_bLoopCheck;							//ループするかしないかのチェック

	//キーボード・コントローラーの取得処理
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//プレイヤーが何に乗っているのか?
	bool m_bPolygon3DCheck[SCENE3D_CREATE];			//ポリゴンに乗っているか?
	int m_nCurrent3DPolygon;				//現在プレイヤーがどの3Dポリゴンに乗っているか
	bool m_bMeshcheck;				//メッシュに乗っているか?
	bool m_bObjRide[OBJ_CREATE];	//objに乗っているか?
	int m_nCurrentObj;				//現在プレイヤーがどのブロックに乗っているか
	bool m_bObjSide[OBJ_CREATE];	//objの横にいるか
	int m_nCurrentSideObj;			//現在プレイヤーがどのブロックの横にいるか
	bool m_bEnemyRide[ENEMY_CREATE];	//エネミーに乗っているか?
	int m_nCurrentEnemy;				//現在プレイヤーがどのブロックに乗っているか
	bool m_bScene3DRide;

	float m_fRotation;	//プレイヤーの軸回転
	D3DXVECTOR3 m_Sabun;//滑らかな方向転換のために使う

	bool m_bDamageState[TYPE_MAX];//ダメージを受けているか?

	int m_nKnockBack;//前後左右どちらでダメージを受けたか?
	int m_nStateCnt;//状態の継続

	bool m_bAutoMove;//イベントによって自動で移動させる

	bool m_bLadderFlag;//梯子イベント

	bool m_bBlockUpCheck;//上下させる

	bool m_bOutStage;//ステージ外になった場合
	int m_nReTime;//再起の時間
	
	//タイトル時の演出
	int m_nTitleEventCnt;
	bool m_bTitleEvent;
	bool m_bStop;

	bool m_bAutoJump;
};




#endif