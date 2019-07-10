//=============================================================================
// ライト処理 [light.cpp]
// Author : Kobayashi/小林将兵
//=============================================================================
#include "light.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LIGHT (3)//ライトの数
#define LIGHT_1 D3DXVECTOR3(0.2f, -0.8f, 0.4f)
#define LIGHT_2 D3DXVECTOR3(10.2f, -0.8f, -1.4f)
#define LIGHT_3 D3DXVECTOR3(-10.2f, -0.8f, -1.4f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DLIGHT9 g_light[MAX_LIGHT];

//=============================================================================
// ライトの初期化処理
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXVECTOR3 vecDir[MAX_LIGHT];

//ライト1
#if 1
	// ライトをクリアする
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	// ライトの種類を設定
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;

	// ライトの拡散光を設定
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	// ライトの方向の設定
	vecDir[0] = LIGHT_1;
	D3DXVec3Normalize(&vecDir[0], &vecDir[0]);
	g_light[0].Direction = vecDir[0];

	// ライトを設定する
	pDevice->SetLight(0, &g_light[0]);//ライトのタイプ0

	// ライトを有効にする
	pDevice->LightEnable(0, TRUE);
#endif

//ライト2
#if 1
	// ライトをクリアする
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	// ライトの種類を設定
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;

	// ライトの拡散光を設定
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライトの方向の設定
	vecDir[1] = LIGHT_2;
	D3DXVec3Normalize(&vecDir[1], &vecDir[1]);
	g_light[1].Direction = vecDir[1];

	// ライトを設定する
	pDevice->SetLight(1, &g_light[1]);//ライトのタイプ1

	// ライトを有効にする
	pDevice->LightEnable(1, TRUE);
#endif

//ライト3
#if 1
	// ライトをクリアする
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	// ライトの種類を設定
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;

	// ライトの拡散光を設定
	g_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライトの方向の設定
	vecDir[2] = LIGHT_3;
	D3DXVec3Normalize(&vecDir[2], &vecDir[2]);
	g_light[2].Direction = vecDir[2];

	// ライトを設定する
	pDevice->SetLight(2, &g_light[2]);//ライトのタイプ2

	// ライトを有効にする
	pDevice->LightEnable(2, TRUE);
#endif
	

}

//=============================================================================
// ライトの終了処理
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void UpdateLight(void)
{
	
}

