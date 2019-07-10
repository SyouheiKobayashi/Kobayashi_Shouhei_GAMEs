//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//						ゲーム内制限時間を決める処理 [timeCharge.h]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _TIMECHARGE_H_
#define _TIMECHARGE_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "manager.h"
#include "fade.h"

//==============================================
//					マクロ定義
//==============================================
#define POLYGON2D_TEX_TC	(5)


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
class CMeshField;
class CBillboard;
class CPolygon3D;
class CParticle3D;
class CNumber;
class CTime;
class CObject;
class CPlayer;

//==============================================
//			 制限時間を決める処理
//==============================================
class CTimeCharge
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CTimeCharge();
	~CTimeCharge();
	static CTimeCharge *Create();

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
	void CreateData(void);
	void Event(void);
	void Debug(void);
	void DebugLoop(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	static CDebug *GetDebug(void) { return m_pDebug; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CPolygon2D *GetPolygon2D(int nCnt) { return m_pPolygon2D[nCnt]; }
	static CScene3D *GetScene3D(void) { return m_pScene3D; }
	static CMeshField *GetMeshField(void) { return m_pMeshField; }
	static CBillboard *GetBillboard(void) { return m_pBillboard; }
	static CPolygon3D *GetPolygon3D(void) { return m_pPolygon3D; }
	static CParticle3D *GetParticle3D(void) { return m_pParticle3D; }
	static CNumber *GetNumber(void) { return m_pNumber; }
	static CTime *GetTime(void) { return m_pTime; }
	static CObject *GetObj(int nCnt) { return m_pObject; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }

	int GetChargeTime(void) { return m_nChargeTime; }//チャージされた時間
	bool GetFlag(void) {return m_bFlag;}//チャージタイムの終了
private:
	static CDebug *m_pDebug;
	static CSound *m_pSound;
	static CLight *m_pLight;
	static CCamera *m_pCamera;
	static CScene2D *m_pScene2D;
	static CPolygon2D *m_pPolygon2D[POLYGON2D_TEX_TC];
	static CScene3D *m_pScene3D;
	static CMeshField *m_pMeshField;
	static CBillboard *m_pBillboard;
	static CPolygon3D * m_pPolygon3D;
	static CParticle3D *m_pParticle3D;
	static CNumber *m_pNumber;
	static CTime * m_pTime;
	static CObject *m_pObject;
	static CPlayer *m_pPlayer;

	//キーボード・コントローラーの取得処理
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//画面遷移処理
	CFade::FADE m_pFade;

	int m_nCntTime;
	bool m_bRotationSwitch;
	float m_fRotation;	//モデル回転用
	int m_nChargeTime;	//時間をいくら貯めたのか記録する

	int m_nCntChargeTime;//チャージ可能時間
	bool m_bFlag;//終了フラグ

	bool m_bStartFlag;
	int m_nStartCnt;
	bool m_ChargeStart;

	int m_nDebugCnt;

};

#endif

