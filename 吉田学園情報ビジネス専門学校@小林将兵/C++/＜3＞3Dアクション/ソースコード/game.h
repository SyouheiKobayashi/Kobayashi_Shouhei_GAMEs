//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//						ゲーム処理 [game.h]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _GAME_H_
#define _GAME_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "manager.h"
#include "fade.h"

//==============================================
//					マクロ定義
//==============================================
#define ENEMY_CREATE	(5)
#define POLYGON3D_CREATE	(6)
#define SCENE3D_CREATE	(5)
#define POLYGON2D_TEX_GAME	(8)
#define DEFAULT_TIME	(50)

//==============================================
//					前方宣言
//==============================================
class CDebug;
class CSound;
class CLight;
class CCamera;
class CScene2D;
class CPolygon2D;
class CScene3D;
class CPolygon3D;
class CBullet;
class CParticle3D;
class CNumber;
class CScore;
class CTime;
class CStencilShadow;
class CObject;
class CPlayer;
class CEnemy;

//==============================================
//						ゲーム
//==============================================
class CGame
{
public:
	//読み込んだオブジェクトの向き、位置
	typedef struct
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	}OBJECT;

	typedef enum
	{
		STAGE_01 = 0,
		STAGE_02,
		STAGE_03,
		STAGE_MAX
	}STAGE_NUMBER;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CGame();
	~CGame();
	static CGame *Create();

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					基盤関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					追加関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	void NullCheck(void);
	void BulkLoadData(void);	//モデル、テクスチャの読み込み
	void BulkUnLoadData(void);	//モデル、テクスチャの解放
	void MAP_LOAD(void);		//マップ情報の読み込み
	void CreateData(void);		//(読み込まれた)モデル、オブジェクトの生成
	void Debug(void);			//デバック用
	void DebugLoop(void);
	void SwitchFlag();			//ステージ上のスイッチがすべて押されたか
	void GameModeCheck();		//ゲームの状態をチェック
	void EventStage01();		//ステージ01用イベント
	void EventStage02();		//ステージ02用イベント
	void EventStage03();		//ステージ03用イベント

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	static void SetSwitchFlagNum();//スイッチを何個押したのか

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	static CDebug *GetDebug(void) { return m_pDebug; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CPolygon2D *GetPolygon2D(int nCnt) { return m_pPolygon2D[nCnt]; }
	static CScene3D *GetScene3D(int nCnt) { return m_pScene3D[nCnt]; }
	static CPolygon3D *GetPolygon3D(int nCnt) { return m_pPolygon3D[nCnt]; }
	static CBullet *GetBullet(void) { return m_pBullet; }
	static CParticle3D *GetParticle3D(void) { return m_pParticle3D; }
	static CNumber *GetNumber(void) { return m_pNumber; }
	static CScore *GetScore(void) { return m_pScore; }
	static CTime *GetTime(void) { return m_pTime; }
	static CStencilShadow *GetStencilShadow(void) { return m_pStencilShadow; }
	static CObject *GetObj(int nCnt) { return m_pObject[nCnt]; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CEnemy *GetEnemy(int nCnt) { return m_pEnemy[nCnt];}

	bool GetNextStage(void) {return bNextStage;}
	static int GetStageCnt(void) { return m_nStageCnt; }
	static bool GetDivided(void) { return m_bDivided; }
	static bool GetDivided02(void) { return m_bDivided02; }
	static bool GetPageStop(void) { return m_bPageStop; }
	static bool GetDeath(void) { return m_bDeath; }

private:
	static CDebug *m_pDebug;
	static CSound *m_pSound;
	static CLight *m_pLight;
	static CCamera *m_pCamera;
	static CScene2D *m_pScene2D;
	static CPolygon2D *m_pPolygon2D[POLYGON2D_TEX_GAME];
	static CScene3D *m_pScene3D[SCENE3D_CREATE];
	static CPolygon3D * m_pPolygon3D[POLYGON3D_CREATE];
	static CBullet *m_pBullet;
	static CParticle3D *m_pParticle3D;
	static CNumber *m_pNumber;
	static CScore * m_pScore;
	static CTime * m_pTime;
	static CStencilShadow *m_pStencilShadow;
	static CObject *m_pObject[OBJ_CREATE];
	static CPlayer *m_pPlayer;
	static CEnemy *m_pEnemy[ENEMY_CREATE];


	//キーボード・コントローラーの取得処理
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//画面遷移処理
	CFade::FADE m_pFade;

	//外部データから読み込んだ情報を保管
	FILE *m_pFile;
	int m_nMaxObjCreateNum;
	int m_nObjType[50];
	int m_nTexType[50];
	OBJECT m_ObjOffseet[50];

	static int m_nStageCnt;//ステージを管理する変数

	static int m_nSwitchFlagNum;//スイッチを起動した数
	bool bNextStage;			//次のステージに移動可能かチェック

	//チュートリアル(STAGE1用)
	int m_nPageCnt;
	static bool m_bPageStop;

	//(STAGE2用)
	//弾の変数
	float m_fBillCnt;
	int m_BulletTime;
	//分かれ道
	static bool m_bDivided;		//行き
	static bool m_bDivided02;	//戻り道

	//ゲームオーバー演出
	int m_nFadeTime;
	static bool m_bDeath;//死亡状態の確認

	//デバック用
	int m_nCreateCnt;
	int m_nDebugCnt;

};

#endif

