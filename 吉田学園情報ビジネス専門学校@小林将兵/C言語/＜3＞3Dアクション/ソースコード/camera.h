//=============================================================================
// カメラ処理 [camera.h]
// Author : Kobayashi/小林将兵
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// カメラの構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posV;		//(現在の)視点
	D3DXVECTOR3 posR;		//(現在の)注視点
	D3DXVECTOR3 vecU;

	D3DXVECTOR3 posVDest;	//(目的の)視点
	D3DXVECTOR3 posRDest;	//(目的の)注視点

	//カメラの回り込み
	D3DXVECTOR3 rot;		//(現在の)向き
	D3DXVECTOR3 rotDest;	//(目的の)向き

	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxViex;
	float Radian;//カメラの距離
	float fKaiten;
}camera;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);

camera *GetCamera(void);

#endif
