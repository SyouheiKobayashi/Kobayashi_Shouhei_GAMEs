//=============================================================================
// 障害物用モデル処理 [collisionModle.cpp]
// Author : Kobayashi/小林将兵
//=============================================================================
#include "collisionModel.h"
#include "camera.h"
#include "fade.h"
#include "bullet.h"
#include "player.h"
#include "shadow.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME ("DATA\\MODEL\\STONE00.x")
#define TEXTURE_NAME ("DATA\\TEXTURE\\洞窟天上.jpg")

#define C_X_SIZE (10)	//あたり判定の大きさ補正
#define C_Z_SIZE (10)	//あたり判定の大きさ補正

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshCollisionModle = NULL;
LPD3DXBUFFER g_pBuffMatCollisionModle = NULL;
LPDIRECT3DTEXTURE9 g_pTextureCollisionModle = NULL;

DWORD g_nNumMatCollisionModle = 0;

COLLISIONMODEL g_Collision;

D3DXVECTOR3 g_SabunCM;//滑らかな方向転換のために使う

int g_nIdxShadowCM;

//=============================================================================
// 初期化処理
//=============================================================================
void InitCollisionModle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 位置・向きの初期設定
	g_Collision.pos = D3DXVECTOR3(200, 200, -210);//位置
	g_Collision.rot = D3DXVECTOR3(0, 0, 0);//向き
	g_Collision.bUse = true;
	g_SabunCM = D3DXVECTOR3(0, 0, 0);//差分
	g_nIdxShadowCM = SetShadow(D3DXVECTOR3(g_Collision.pos.x, 0.0f, g_Collision.pos.z), g_Collision.rot);
	g_Collision.VtxMin = D3DXVECTOR3(10000, 10000, 10000);
	g_Collision.VtxMax = D3DXVECTOR3(-10000, -10000, -10000);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureCollisionModle);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatCollisionModle,
		NULL,
		&g_nNumMatCollisionModle,
		&g_pMeshCollisionModle);


	int nNumVtx;										//頂点数
	DWORD sizeFVF;										//頂点フォーマットのサイズ
	BYTE *pVtxBuff;										//頂点バッファへのポインタ

	//頂点数を取得
	nNumVtx = g_pMeshCollisionModle->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshCollisionModle->GetFVF());

	//頂点バッファをロック
	g_pMeshCollisionModle->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVer = 0; nCntVer < nNumVtx; nCntVer++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//頂点座標の代入

		if (g_Collision.VtxMin.x >= vtx.x)
		{
			g_Collision.VtxMin.x = vtx.x;
		}
		if (g_Collision.VtxMin.y >= vtx.y)
		{
			g_Collision.VtxMin.y = vtx.y;
		}
		if (g_Collision.VtxMin.z >= vtx.z)
		{
			g_Collision.VtxMin.z = vtx.z;
		}

		if (g_Collision.VtxMax.x <= vtx.x)
		{
			g_Collision.VtxMax.x = vtx.x;
		}
		if (g_Collision.VtxMax.y <= vtx.y)
		{
			g_Collision.VtxMax.y = vtx.y;
		}
		if (g_Collision.VtxMax.z <= vtx.z)
		{
			g_Collision.VtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;//サイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	g_pMeshCollisionModle->UnlockVertexBuffer();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCollisionModle(void)
{
	// メッシュの開放
	if (g_pMeshCollisionModle != NULL)
	{
		g_pMeshCollisionModle->Release();
		g_pMeshCollisionModle = NULL;
	}

	// マテリアルの開放
	if (g_pBuffMatCollisionModle != NULL)
	{
		g_pBuffMatCollisionModle->Release();
		g_pBuffMatCollisionModle = NULL;
	}

	// テクスチャの破棄
	if (g_pTextureCollisionModle != NULL)
	{
		g_pTextureCollisionModle->Release();
		g_pTextureCollisionModle = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCollisionModle(void)
{
	if (g_Collision.bUse == true)
	{
		//SetPositionShadow(g_nIdxShadowCM, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCollisionModle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Collision.mtxWorldCollision);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Collision.rot.y, g_Collision.rot.x, g_Collision.rot.z);
	D3DXMatrixMultiply(&g_Collision.mtxWorldCollision, &g_Collision.mtxWorldCollision, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, g_Collision.pos.x, g_Collision.pos.y, g_Collision.pos.z);
	D3DXMatrixMultiply(&g_Collision.mtxWorldCollision, &g_Collision.mtxWorldCollision, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Collision.mtxWorldCollision);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatCollisionModle->GetBufferPointer();

	for (int nCntMat = 0; nCntMat<(int)g_nNumMatCollisionModle; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureCollisionModle);

		// モデル(パーツ)の描画
		g_pMeshCollisionModle->DrawSubset(nCntMat);

	}
	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 障害物用モデル情報の取得
//=============================================================================
COLLISIONMODEL *GetCollision(void)
{
	return &g_Collision;
}
//=============================================================================
// 当たり判定処理
//=============================================================================
void CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMax,D3DXVECTOR3 *pVtxMin)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	if (g_Collision.bUse == true)
	{
		if (pPos->x + C_X_SIZE >= g_Collision.pos.x + (g_Collision.VtxMin.x) &&
			pPos->x - C_X_SIZE <= g_Collision.pos.x + (g_Collision.VtxMax.x))
		{
			if (pPos->z + C_Z_SIZE >= g_Collision.pos.z + (g_Collision.VtxMin.z) &&
				pPos->z - C_Z_SIZE <= g_Collision.pos.z + (g_Collision.VtxMax.z))
			{
				//FADE pFade;

				//pFade = *GetFade();

				////モード設定
				//SetFade(MODE_RESULT);
				//
				//pPlayer->move = D3DXVECTOR3(0, 0, 0);//移動量を0にする

				//if (pPosOld->z + C_Z_SIZE <= g_Collision.pos.z + (g_Collision.VtxMin.z) &&
				//	pPos->z + C_Z_SIZE >= g_Collision.pos.z + (g_Collision.VtxMin.z))
				//{//手前の判定
				//	pPos->z = g_Collision.pos.z + (g_Collision.VtxMin.z) - C_Z_SIZE;
				//}
				//else if (pPosOld->z - C_Z_SIZE >= g_Collision.pos.z + (g_Collision.VtxMax.z ) &&
				//	pPos->z - C_Z_SIZE <= g_Collision.pos.z + (g_Collision.VtxMax.z))
				//{//奥の判定
				//	pPos->z = g_Collision.pos.z + (g_Collision.VtxMax.z) + C_Z_SIZE;
				//}


				//if (pPosOld->x - C_X_SIZE >= g_Collision.pos.x + (g_Collision.VtxMax.x) &&
				//	pPos->x - C_X_SIZE <= g_Collision.pos.x + (g_Collision.VtxMax.x))
				//{//右の判定
				//	pPos->x = g_Collision.pos.x + (g_Collision.VtxMax.x)+ C_X_SIZE;
				//}
				//else if (pPosOld->x + C_X_SIZE <= g_Collision.pos.x+ (g_Collision.VtxMin.x) &&
				//	pPos->x + C_X_SIZE >= g_Collision.pos.x + (g_Collision.VtxMin.x))
				//{//左の判定
				//	pPos->x = g_Collision.pos.x + (g_Collision.VtxMin.x)- C_X_SIZE;
				//}
			}
		}
	}
}

