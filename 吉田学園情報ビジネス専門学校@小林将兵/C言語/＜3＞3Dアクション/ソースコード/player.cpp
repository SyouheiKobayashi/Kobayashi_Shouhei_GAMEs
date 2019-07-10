//=============================================================================
// モデル処理 [player.cpp]
// Author : Kobayashi/小林将兵
//=============================================================================
#include "player.h"
#include "input.h"
#include "game.h"
#include "camera.h"
#include "collisionModel.h"
#include "item.h"
#include "badItem.h"
#include "fallingRocks.h"
#include "bullet.h"
#include "shadow.h" 
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME ("DATA\\MODEL\\car000.x")
#define MODEL_NAME2 ("DATA\\MODEL\\PLAYER_head00.x")


#define TEXTURE_NAME ("DATA\\TEXTURE\\メルクちゃん.jpg")
#define TEXTURE_NAME2 ("DATA\\TEXTURE\\企画書 代キャラ03.jpg")

//*****************************************************************************
// グローバル変数
//*****************************************************************************
PLAYER g_Player;

D3DXVECTOR3 g_Sabun;//滑らかな方向転換のために使う

camera *pCamera;

int g_nIdxShadow;

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_Player.aModel[1].pTexture);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME2, &g_Player.aModel[2].pTexture);

//=============================================================================
//+ Xファイルの読み込み
//=============================================================================
	D3DXLoadMeshFromX(MODEL_NAME,//本体
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[0].pBuffMat,
		NULL,
		&g_Player.aModel[0].nNumMat,
		&g_Player.aModel[0].pMesh);

	D3DXLoadMeshFromX(MODEL_NAME2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[1].pBuffMat,
		NULL,
		&g_Player.aModel[1].nNumMat,
		&g_Player.aModel[1].pMesh);

	//D3DXLoadMeshFromX(MODEL_NAME2,//帽子
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_Player.aModel[2].pBuffMat,
	//	NULL,
	//	&g_Player.aModel[2].nNumMat,
	//	&g_Player.aModel[2].pMesh);
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	// 位置・向きの初期設定
	g_Player.pos = D3DXVECTOR3(0, 0, -2800);//位置
	g_Player.posOld = D3DXVECTOR3(0, 0, 0);//位置
	g_Player.move = D3DXVECTOR3(0, 0, 0);//移動
	g_Player.rot = D3DXVECTOR3(0, -D3DX_PI, 0);//向き
	g_Sabun = D3DXVECTOR3(0, 0, 0);//差分

	g_Player.aModel[0].pos = D3DXVECTOR3(0, 0, 0);
	g_Player.aModel[0].rot = D3DXVECTOR3(0, 0, 0);
	g_Player.aModel[0].nIdxModelParent = -1;

	g_Player.aModel[1].pos = D3DXVECTOR3(0, 0, -13);
	g_Player.aModel[1].rot = D3DXVECTOR3(0, 0, 0);
	g_Player.aModel[1].nIdxModelParent = 0;

	/*g_Player.aModel[2].pos = D3DXVECTOR3(20, 15, 0);
	g_Player.aModel[2].rot = D3DXVECTOR3(0, 0, 0);
	g_Player.aModel[2].nIdxModelParent = 0;*/

	g_nIdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z), g_Player.rot);

	int nNumVtx;										//頂点数
	DWORD sizeFVF;										//頂点フォーマットのサイズ
	BYTE *pVtxBuff;										//頂点バッファへのポインタ

														//頂点数を取得
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		nNumVtx = g_Player.aModel[nCnt].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCnt].pMesh->GetFVF());

		//頂点バッファをロック
		g_Player.aModel[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVer = 0; nCntVer < nNumVtx; nCntVer++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//頂点座標の代入

			if (g_Player.VtxMin.x >= vtx.x)
			{
				g_Player.VtxMin.x = vtx.x;
			}
			if (g_Player.VtxMin.y >= vtx.y)
			{
				g_Player.VtxMin.y = vtx.y;
			}
			if (g_Player.VtxMin.z >= vtx.z)
			{
				g_Player.VtxMin.z = vtx.z;
			}

			if (g_Player.VtxMax.x <= vtx.x)
			{
				g_Player.VtxMax.x = vtx.x;
			}
			if (g_Player.VtxMax.y <= vtx.y)
			{
				g_Player.VtxMax.y = vtx.y;
			}
			if (g_Player.VtxMax.z <= vtx.z)
			{
				g_Player.VtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//サイズ分ポインタを進める
		}

		//頂点バッファをアンロック
		g_Player.aModel[nCnt].pMesh->UnlockVertexBuffer();
	}

	
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
		// メッシュの開放
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_Player.aModel[nCnt].pMesh != NULL)
		{
			g_Player.aModel[nCnt].pMesh->Release();
			g_Player.aModel[nCnt].pMesh = NULL;
		}

		// マテリアルの開放
		if (g_Player.aModel[nCnt].pBuffMat != NULL)
		{
			g_Player.aModel[nCnt].pBuffMat->Release();
			g_Player.aModel[nCnt].pBuffMat = NULL;
		}

		// テクスチャの破棄
		if (g_Player.aModel[nCnt].pTexture != NULL)
		{
			g_Player.aModel[nCnt].pTexture ->Release();
			g_Player.aModel[nCnt].pTexture = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	pCamera = GetCamera();

	g_Player.posOld = g_Player.pos;

	//g_Player.aModel[2].rot.y++;

//^^^^^^^^^^^^^^^^^^^^^^^^^^
//			初期化
//^^^^^^^^^^^^^^^^^^^^^^^^^^
//	if (GetKeyboardPress(DIK_Q) == true)
//	{
//		g_Player.pos = D3DXVECTOR3(0, 0, 0);//位置
//		g_Player.rot = D3DXVECTOR3(0, 0, 0);//向き
//		g_Sabun = D3DXVECTOR3(0, 0, 0);//差分
//	}

//^^^^^^^^^^^^^^^^^^^^^^^^^^
//	弾の発射設定
//^^^^^^^^^^^^^^^^^^^^^^^^^^
	//if (GetKeyboardTrigger(DIK_SPACE) == true)//スペース押しての弾の射出
	//{//																	↓球の発射方向&&球の速度
	//	SetBullet(g_Player.pos, D3DXVECTOR3(sinf(g_Player.rot.y - D3DX_PI)*3.3f, 0.0f, cosf(g_Player.rot.y - D3DX_PI)*3.3f));
	//}

//^^^^^^^^^^^^^^^^^^^^^^^^^^
//	モデル移動[↑][↓][→][←]
//^^^^^^^^^^^^^^^^^^^^^^^^^^
	if (GetKeyboardPress(DIK_UP) == true)
	{
			g_Player.move.x += sinf(pCamera->rot.y) * 1.0f;
			g_Player.move.z += cosf(pCamera->rot.y) * 1.0f;
			g_Sabun.y = (D3DX_PI + pCamera->rot.y) - g_Player.rot.y;
			if (g_Player.pos.z > 3037)
			{
				g_Player.move.z = 0;
			}
		
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
			g_Player.move.x += sinf(D3DX_PI + pCamera->rot.y) * 1.0f;
			g_Player.move.z += cosf(D3DX_PI + pCamera->rot.y) * 1.0f;
			g_Sabun.y = (pCamera->rot.y) - g_Player.rot.y;
			//g_Player.rot.y = 3.14f + pCamera->rot.y; バック走法になるよ
			if (g_Player.pos.z < -2837)
			{
				g_Player.move.z = 0;
			}
		
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)//→
	{
		if (GetKeyboardPress(DIK_UP) == true)//斜め
		{
			g_Player.move.x += sinf(D3DX_PI * 0.5f + pCamera->rot.y) * 0.3f;
			g_Player.move.z += cosf(D3DX_PI * 0.5f + pCamera->rot.y) * 0.3f;
			g_Sabun.y = ((-D3DX_PI *0.75f) + pCamera->rot.y) - g_Player.rot.y;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)//斜め
		{
			g_Player.move.x += sinf(D3DX_PI * 0.5f + pCamera->rot.y) * 0.3f;
			g_Player.move.z += cosf(D3DX_PI * 0.5f + pCamera->rot.y) * 0.3f;
			g_Sabun.y = ((-D3DX_PI *0.25f) + pCamera->rot.y) - g_Player.rot.y;
		}
		else
		{
			g_Player.move.x += sinf(D3DX_PI / 2 + pCamera->rot.y) * 0.4f;
			g_Player.move.z += cosf(D3DX_PI / 2 + pCamera->rot.y) * 0.4f;
			g_Sabun.y = ((-D3DX_PI / 2) + pCamera->rot.y) - g_Player.rot.y;
		}
		if (g_Player.pos.x > 537)
		{
			g_Player.move.x = 0;
		}
	}
	if (GetKeyboardPress(DIK_LEFT) == true)//←
	{
		if (GetKeyboardPress(DIK_UP) == true)//斜め
		{
			g_Player.move.x -= sinf(D3DX_PI * 0.5f + pCamera->rot.y)*0.3f;
			g_Player.move.z -= cosf(D3DX_PI * 0.5f + pCamera->rot.y)*0.3f;
			g_Sabun.y = ((D3DX_PI *0.75f) + pCamera->rot.y) - g_Player.rot.y;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)//斜め
		{
			g_Player.move.x -= sinf(D3DX_PI * 0.5f + pCamera->rot.y) * 0.3f;
			g_Player.move.z -= cosf(D3DX_PI * 0.5f + pCamera->rot.y) * 0.3f;
			g_Sabun.y = ((D3DX_PI *0.25f) + pCamera->rot.y) - g_Player.rot.y;
		}
		else
		{
			g_Player.move.x -= sinf(D3DX_PI / 2 + pCamera->rot.y) * 0.4f;
			g_Player.move.z -= cosf(D3DX_PI / 2 + pCamera->rot.y) * 0.4f;
			g_Sabun.y = ((D3DX_PI / 2) + pCamera->rot.y) - g_Player.rot.y;
		
		}
		if (g_Player.pos.x < -437)
		{
			g_Player.move.x = 0;
		}
	}
	if (g_Sabun.y >  D3DX_PI)
	{
		g_Sabun.y -= D3DX_PI * 2;
	}
	if (g_Sabun.y <  -D3DX_PI)
	{
		g_Sabun.y += D3DX_PI * 2;
	}

	g_Player.rot.y += g_Sabun.y * 0.16f;

	if (g_Player.rot.y >  D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI * 2;
	}
	if (g_Player.rot.y <  -D3DX_PI)
	{
		g_Player.rot.y += D3DX_PI * 2;
	}

	g_Sabun.y = 0;

	g_Player.move += (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - g_Player.move)*0.1f;
	g_Player.pos += g_Player.move;

	//g_Player.aModel[1].rot.y -= 0.05f;
	//g_Player.aModel[2].rot.y += 0.05f;

	SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z));

//◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆
//+	プレイヤーに対するあたり判定の処理	
//◇ ◇	◇ ◇ ◇ ◇ ◇ ◇ ◇ ◇	◇ ◇ ◇ ◇ ◇ ◇ ◇ ◇	◇ ◇ ◇ ◇ ◇ ◇ ◇ ◇	◇ ◇ ◇ ◇ ◇ ◇
	CollisionModel(&g_Player.pos, &g_Player.posOld, &g_Player.move,&g_Player.VtxMax,&g_Player.VtxMin);
	CollisionItem(&g_Player.pos, &g_Player.posOld, &g_Player.move, &g_Player.VtxMax, &g_Player.VtxMin);
	CollisionBadItem(&g_Player.pos, &g_Player.posOld, &g_Player.move, &g_Player.VtxMax, &g_Player.VtxMin);
	CollisionFallingRocks(&g_Player.pos, &g_Player.posOld, &g_Player.move, &g_Player.VtxMax, &g_Player.VtxMin);


//◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆
//+	プレイヤーに対するカメラの追尾処理	
//◇ ◇	◇ ◇ ◇ ◇ ◇ ◇ ◇ ◇	◇ ◇ ◇ ◇ ◇ ◇ ◇ ◇	◇ ◇ ◇ ◇ ◇ ◇ ◇ ◇	◇ ◇ ◇ ◇ ◇ ◇
	pCamera->posRDest.x= (g_Player.pos.x) - sinf(pCamera->rot.y) * 80;
	pCamera->posRDest.y = (g_Player.pos.y);
	pCamera->posRDest.z = (g_Player.pos.z) - cosf(pCamera->rot.y) * 60;

	pCamera->posVDest.x = pCamera->posRDest.x - sinf(pCamera->rot.y) * 200;
	pCamera->posVDest.y = pCamera->posRDest.y;
	pCamera->posVDest.z = pCamera->posRDest.z - cosf(pCamera->rot.y) * 200;

	pCamera->posR.x += (pCamera->posRDest.x - pCamera->posR.x)*0.09f;
	pCamera->posR.y += (pCamera->posRDest.y - pCamera->posR.y)*0.05f;
	pCamera->posR.z += (pCamera->posRDest.z - pCamera->posR.z)*0.09f;

	pCamera->posV.x += (pCamera->posVDest.x - pCamera->posV.x)*0.09f;
	pCamera->posV.y += (pCamera->posVDest.y - pCamera->posV.y+50)*0.05f;
	pCamera->posV.z += (pCamera->posVDest.z - pCamera->posV.z)*0.09f;

//◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆
//+	プレイヤーが目的の値(pos)以上に到達し場合&&クリア条件	
//◇ ◇	◇ ◇ ◇ ◇ ◇ ◇ ◇ ◇	◇ ◇ ◇ ◇ ◇ ◇ ◇ ◇	◇ ◇ ◇ ◇ ◇ ◇ ◇ ◇	◇ ◇ ◇ ◇ ◇ ◇
	if (g_Player.pos.z < 2837)
	{
		SetGameState(GAMESTATE_CLEAR);
	}
}

//=============================================================================
//=============================================================================
//++ 描画処理
//=============================================================================
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	D3DXMATRIX mtxParent;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);
	
	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_Player.aModel[nCnt].nIdxModelParent == -1)
		{
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			mtxParent = g_Player.aModel[g_Player.aModel[nCnt].nIdxModelParent].mtxWorld;
		}

		//--------------------------------------------------------------------------------------
		//!+ Model(親)
		//--------------------------------------------------------------------------------------
			// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.aModel[nCnt].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCnt].rot.y, g_Player.aModel[nCnt].rot.x, g_Player.aModel[nCnt].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCnt].mtxWorld, &g_Player.aModel[nCnt].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[nCnt].pos.x, g_Player.aModel[nCnt].pos.y, g_Player.aModel[nCnt].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCnt].mtxWorld, &g_Player.aModel[nCnt].mtxWorld, &mtxTrans);

		D3DXMatrixMultiply(&g_Player.aModel[nCnt].mtxWorld, &g_Player.aModel[nCnt].mtxWorld, &mtxParent);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCnt].mtxWorld);

		//+ Xファイルの描画
		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCnt].nNumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);
			pDevice->SetTexture(0, g_Player.aModel[nCnt].pTexture);


			// モデル(パーツ)の描画
			g_Player.aModel[nCnt].pMesh->DrawSubset(nCntMat);

		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}

//=============================================================================
// プレイヤー情報の所得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}