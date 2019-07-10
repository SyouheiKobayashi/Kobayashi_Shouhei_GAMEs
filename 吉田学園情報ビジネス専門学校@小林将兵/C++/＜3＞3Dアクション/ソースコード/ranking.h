//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//						ランキング処理 [ranking.h]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _RANKING_H_
#define _RANKING_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "manager.h"
#include "fade.h"

//==============================================
//					マクロ定義
//==============================================
//#define OBJ_CREATE	(50)


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
class CParticle3D;
class CNumber;
class CScore;
class CObject;
class CPlayer;

//==============================================
//						ゲーム
//==============================================
class CRanking
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

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CRanking();
	~CRanking();
	static CRanking *Create();

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
	void BulkLoadData(void);
	void BulkUnLoadData(void);
	void MAP_LOAD(void);
	void CreateData(void);
	void DebugLoop(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	static CDebug *GetDebug(void) { return m_pDebug; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CPolygon2D *GetPolygon2D(void) { return m_pPolygon2D; }
	static CScene3D *GetScene3D(void) { return m_pScene3D; }
	static CPolygon3D *GetPolygon3D(void) { return m_pPolygon3D; }
	static CParticle3D *GetParticle3D(void) { return m_pParticle3D; }
	static CNumber *GetNumber(void) { return m_pNumber; }
	static CScore *GetScore(void) { return m_pScore; }
	static CObject *GetObj(int nCnt) { return m_pObject[nCnt]; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }

private:
	static CDebug *m_pDebug;
	static CSound *m_pSound;
	static CLight *m_pLight;
	static CCamera *m_pCamera;
	static CScene2D *m_pScene2D;
	static CPolygon2D *m_pPolygon2D;
	static CScene3D *m_pScene3D;
	static CPolygon3D * m_pPolygon3D;
	static CParticle3D *m_pParticle3D;
	static CNumber *m_pNumber;
	static CScore *m_pScore;
	static CObject *m_pObject[OBJ_CREATE];
	static CPlayer *m_pPlayer;

	//キーボード・コントローラーの取得処理
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//画面遷移処理
	CFade::FADE m_pFade;

	//外部データから読み込んだ情報を保管
	int m_nMaxObjCreateNum;
	int m_nObjType[50];
	int m_nTexType[50];
	OBJECT m_ObjOffseet[50];

	//デバック用
	int m_nCreateCnt;
	int m_nDebugCnt;

};

#endif

