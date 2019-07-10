//=============================================================================
// モデル処理 [stage.cpp]
// Author : Kobayashi/小林将兵
//=============================================================================
#include "stage.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME ("DATA\\MODEL\\STAGE00.x")
#define TEXTURE_NAME ("DATA\\UV\\STAGE_UV編集.png")

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshStage = NULL;
LPD3DXBUFFER g_pBuffMatStage = NULL;
LPDIRECT3DTEXTURE9 g_pTextureStage = NULL;

DWORD g_nNumMatStage = 0;
D3DXVECTOR3 g_posStage;
D3DXVECTOR3 g_rotStage;
D3DXMATRIX g_mtxWorldStage;

//=============================================================================
// 初期化処理
//=============================================================================
void InitStage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureStage);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatStage,
		NULL,
		&g_nNumMatStage,
		&g_pMeshStage);

	// 位置・向きの初期設定
	g_posStage = D3DXVECTOR3(50, 0, 50);//位置
	g_rotStage = D3DXVECTOR3(0, D3DX_PI, 0);//向き
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStage(void)
{
	// メッシュの開放
	if (g_pMeshStage != NULL)
	{
		g_pMeshStage->Release();
		g_pMeshStage = NULL;
	}

	// マテリアルの開放
	if (g_pBuffMatStage != NULL)
	{
		g_pBuffMatStage->Release();
		g_pBuffMatStage = NULL;
	}

	// テクスチャの破棄
	if (g_pTextureStage != NULL)
	{
		g_pTextureStage->Release();
		g_pTextureStage = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStage(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldStage);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotStage.y, g_rotStage.x, g_rotStage.z);
	D3DXMatrixMultiply(&g_mtxWorldStage, &g_mtxWorldStage, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, g_posStage.x, g_posStage.y, g_posStage.z);
	D3DXMatrixMultiply(&g_mtxWorldStage, &g_mtxWorldStage, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldStage);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatStage->GetBufferPointer();

	for(int nCntMat = 0; nCntMat<(int)g_nNumMatStage;nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);
		pDevice->SetTexture(0, g_pTextureStage);


		// モデル(パーツ)の描画
		g_pMeshStage->DrawSubset(nCntMat);

	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}
