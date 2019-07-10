//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//ゲーム処理 [game.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _GAME_H_
#define _GAME_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "manager.h"
#include "fade.h"

//==============================================
//マクロ定義
//==============================================
#define OBJ_CREATE	(100)


//==============================================
//前方宣言
//==============================================
class CDebug;
class CLight;
class CCamera;
class CScene2D;
class CScene3D;
class CMeshField;
class CSceneX;
class CObject;
class CPlayer;

//==============================================
//ゲーム
//==============================================
class CGame
{
public:
	//コンストラクタ / デストラクタ
	CGame();
	~CGame();

	//生成
	static CGame *Create();

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void NullCheck(void);
	void CreateData(void);
	void ObjCreate();
	void ObjDelete();
	void Save(void);
	void Debug(void);


	//Get関数(自身で扱った情報を他のプログラムで使用する処理)
	static CDebug *GetDebug(void) { return m_pDebug; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CScene3D *GetScene3D(void) { return m_pScene3D; }
	static CMeshField *GetMeshField(void) { return m_pMeshField; }
	static CObject *GetObj(int nCnt) { return m_pObject[nCnt]; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }

	int GetInputMode(void) { return m_nInputMode; }

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			スクリーン座標をワールド座標に変換
	// @   @   @   @   @   @   @   @   @   @   @   @
	static D3DXVECTOR3* ScreenToWorld
	(D3DXVECTOR3* pout,
		int nScreenPosX,
		int nScreenPosY,
		float fProjectionSpace_Z,//射影空間のZを求める
		int ScreenWide,
		int ScreenHeight,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj);

	static D3DXVECTOR3* CalculationPoint
	(D3DXVECTOR3* pout,
		int nScreenPosX,
		int nScreenPosY,
		int ScreenWide,
		int ScreenHeight,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj);

private:
	static CDebug *m_pDebug;
	static CLight *m_pLight;
	static CCamera *m_pCamera;
	static CScene2D *m_pScene2D;
	static CScene3D *m_pScene3D;
	static CMeshField *m_pMeshField;
	static CSceneX *m_pSceneX;
	static CObject *m_pObject[OBJ_CREATE];
	static CPlayer *m_pPlayer;

	//キーボード・コントローラーの取得処理
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//画面遷移処理
	CFade::FADE m_pFade;

	int m_nInputMode;//現在の入力状態

	//デバック用
	int m_nCreateCnt;

};

#endif

