//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//カメラ処理 [camera.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _CAMERA_H_
#define _CAMERA_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"

//==============================================
//マクロ定義
//==============================================
#define CAMERA_V D3DXVECTOR3(0.0f, 50.0f, -400.0f)//注視点からの距離(常に中視点を見続ける)
#define CAMERA_R D3DXVECTOR3(0.0f, 0.0f, 0.0f)//注視点の位置(常にカメラの中心である)
#define CAMERA_WIDTH (50.0f)//カメラ視野の広さ
#define CAMERA_INIT_V (400.0f)//注視点からの距離(常に中視点を見続ける)

class CGame;
class CInputKeyboard;
class CInputXPad;
class CInputMouse;

//==============================================
//カメラ
//==============================================
class CCamera
{
public:
	typedef enum        //モードの種類
	{
		MODE_XYZ = 0,	//キーボード操作のみ
		MODE_XZ,		//マウス操作も可能
		MODE_MAX		//最大数
	}CAMERA_MODE;

	//コンストラクタ / デストラクタ
	CCamera();
	~CCamera();

	//生成
	static CCamera *Create(void);

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	void Init(void);
	void Uninit(void);
	void Update(void);

	void MOVE(void);			//入力モードによるカメラ操作2種類
	void MOVE02(void);

	void PointViewRot(void);	//注視点を軸に視点の回転(常に注視点を見続ける)
	void NoteViewRot(void);		//視点の回転(注視点をコンパスのように一定回転)

	//Get関数(自身で扱った情報を他のプログラムで使用する処理)
	float GetRotation(void) { return m_fRotation; }
	D3DXMATRIX GetMtxProjection(void) { return m_mtxProjection; }
	D3DXMATRIX GetMtxViex(void) { return m_mtxViex; }
	int GetCameraMode(void) {return m_nCameraMode;}//現在のカメラの状態
	D3DXVECTOR3 GetPosR(void) { return m_posR; }
	D3DXVECTOR3 GetR(void) { return m_posR; }
	//Set関数(他処理の数値、データをもらい適応 / 主に派生(子)クラスで使用)
	void SetCamera(void);//カメラの基本情報

private:
	D3DXVECTOR3 m_posV;		//(現在の)視点
	D3DXVECTOR3 m_posR;		//(現在の)注視点
	D3DXVECTOR3 m_vecU;
	D3DXVECTOR3 m_posVDest;	//(目的の)視点
	D3DXVECTOR3 m_posRDest;	//(目的の)注視点
	D3DXVECTOR3 m_rot;		//(現在の)向き
	D3DXVECTOR3 m_rotDest;	//(目的の)向き
	D3DXMATRIX m_mtxProjection;
	D3DXMATRIX m_mtxViex;

	//キーボード・コントローラーの取得処理
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	float m_Radian;//カメラの距離
	float m_fRotation;//軸

	CGame *m_pGame;
	int m_nCameraMode;//モードの変更
};

#endif
