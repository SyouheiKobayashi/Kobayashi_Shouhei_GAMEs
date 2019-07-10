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
#include "input.h"

//==============================================
//マクロ定義
//==============================================
#define CAMERA_V D3DXVECTOR3(-150.0f, 140.0f, -220.0f)		//注視点からの距離(常に中視点を見続ける)
#define CAMERA_R D3DXVECTOR3(-150.0f, 120.0f, 0.0f)			//注視点の位置(常にカメラの中心である)
#define CAMERA_WIDTH (60.0f)//カメラ視野の広さ

//==============================================
//カメラ
//==============================================
class CCamera
{
public:
	//コンストラクタ / デストラクタ
	CCamera();
	~CCamera();

	//生成
	static CCamera *Create(void);

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	void Init(void);
	void Uninit(void);
	void Update(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					追加関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	void DebugCameraMove();
	void CameraView();

	//Get関数(自身で扱った情報を他のプログラムで使用する処理)
	float GetRotation(void) { return m_fRotation; }
	D3DXMATRIX GetMtxProjection(void) { return m_mtxProjection; }
	D3DXMATRIX GetMtxViex(void) { return m_mtxViex; }
	//Set関数(他処理の数値、データをもらい適応 / 主に派生(子)クラスで使用)
	void SetCamera(void);//カメラの基本情報
	void SetV(D3DXVECTOR3 posV);
	void SetR(D3DXVECTOR3 posR);

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

	float m_Radian;//カメラの距離
	float m_fRotation;//軸

	float m_fCameraPosZ;//プレイヤーの位置によるカメラの値の変更

	CInputKeyboard *m_pInputKeyboard;

	
};

#endif
