//=============================================================================
// モデル処理 [DummyModel.cpp]
// Author : Kobayashi/小林将兵
//=============================================================================
#include "DummyModel.h"
#include "camera.h"
#include "bullet.h"
#include "shadow.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME ("DATA\\MODEL\\ダミーモデルちゃん.x")
#define TEXTURE_NAME ("DATA\\TEXTURE\\企画書 代キャラ03.jpg")

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshDummyModel = NULL;
LPD3DXBUFFER g_pBuffMatDummyModel = NULL;
LPDIRECT3DTEXTURE9 g_pTextureDummyModel = NULL;

DWORD g_nNumMatDummyModel = 0;
D3DXVECTOR3 g_posDummyModel;
D3DXVECTOR3 g_rotDummyModel;
D3DXMATRIX g_mtxWorldDummyModel;

D3DXVECTOR3 g_SabunD;//滑らかな方向転換のために使う

int g_nIdxShadowD;

//=============================================================================
// 初期化処理
//=============================================================================
void InitDummyModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureDummyModel);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatDummyModel,
		NULL,
		&g_nNumMatDummyModel,
		&g_pMeshDummyModel);

	// 位置・向きの初期設定
	g_posDummyModel = D3DXVECTOR3(50, 0, 50);//位置
	g_rotDummyModel = D3DXVECTOR3(0, 0, 0);//向き
	g_SabunD = D3DXVECTOR3(0, 0, 0);//差分

	g_nIdxShadowD = SetShadow(D3DXVECTOR3(g_posDummyModel.x,0.0f, g_posDummyModel.z), g_rotDummyModel);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitDummyModel(void)
{
	// メッシュの開放
	if (g_pMeshDummyModel != NULL)
	{
		g_pMeshDummyModel->Release();
		g_pMeshDummyModel = NULL;
	}

	// マテリアルの開放
	if (g_pBuffMatDummyModel != NULL)
	{
		g_pBuffMatDummyModel->Release();
		g_pBuffMatDummyModel = NULL;
	}

	// テクスチャの破棄
	if (g_pTextureDummyModel != NULL)
	{
		g_pTextureDummyModel->Release();
		g_pTextureDummyModel = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateDummyModel(void)
{
	g_rotDummyModel.y -= 0.01f;

//^^^^^^^^^^^^^^^^^^^^^^^^^^
//	弾の発射設定
//^^^^^^^^^^^^^^^^^^^^^^^^^^
	//SetBullet(g_posDummyModel, D3DXVECTOR3(sinf(g_rotDummyModel.y - D3DX_PI)*3.3f, 0.0f, cosf(g_rotDummyModel.y - D3DX_PI)*3.3f));

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawDummyModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldDummyModel);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotDummyModel.y, g_rotDummyModel.x, g_rotDummyModel.z);
	D3DXMatrixMultiply(&g_mtxWorldDummyModel, &g_mtxWorldDummyModel, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, g_posDummyModel.x, g_posDummyModel.y, g_posDummyModel.z);
	D3DXMatrixMultiply(&g_mtxWorldDummyModel, &g_mtxWorldDummyModel, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldDummyModel);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatDummyModel->GetBufferPointer();

	for(int nCntMat = 0; nCntMat<(int)g_nNumMatDummyModel;nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);
		pDevice->SetTexture(0, g_pTextureDummyModel);


		// モデル(パーツ)の描画
		g_pMeshDummyModel->DrawSubset(nCntMat);

	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}
