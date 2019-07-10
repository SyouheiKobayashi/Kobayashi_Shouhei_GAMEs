//=============================================================================
// 障害物用モデル処理 [badItem.cpp]
// Author : Kobayashi/小林将兵
//=============================================================================
#include "badItem.h"
#include "sound.h"
#include "game.h"
#include "camera.h"
#include "score.h"
#include "timer.h"
#include "bullet.h"
#include "player.h"
#include "effect.h"
#include "shadow.h"
//#include "fade.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME ("DATA\\MODEL\\ITEM00.x")
#define TEXTURE_NAME ("DATA\\UV\\アイテム00_UV.jpg")
#define MAX_ITEM (1)	//使用するモデルの種類
#define MAX_ARRANGEMENT (5)	//配置するモデルの数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshBadItem[MAX_ARRANGEMENT] = {};
LPD3DXBUFFER g_pBuffMatBadItem[MAX_ARRANGEMENT] = {};
LPDIRECT3DTEXTURE9 g_pTextureBadItem[MAX_ARRANGEMENT]= {};

DWORD g_nNumMatBadItem[MAX_ARRANGEMENT] = {};

BADITEM g_BadItem[MAX_ARRANGEMENT];

D3DXVECTOR3 g_SabunBI[MAX_ARRANGEMENT];//滑らかな方向転換のために使う

int g_nIdxShadowBI[MAX_ARRANGEMENT];

int g_NumBadItem;//アイテムの総数

//=============================================================================
// 初期化処理
//=============================================================================
void InitBadItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// 位置・向きの初期設定
		g_BadItem[nCnt].pos = D3DXVECTOR3(0, 0, 0);//位置
		g_BadItem[nCnt].move = D3DXVECTOR3(0, 0, 0);//移動
		g_BadItem[nCnt].rot = D3DXVECTOR3(0, 0, 0);//向き
		g_BadItem[nCnt].bUse = false;
		g_BadItem[nCnt].bTouch = false;
		g_SabunBI[nCnt] = D3DXVECTOR3(0, 0, 0);//差分
		g_NumBadItem = 0;

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureBadItem[nCnt]);

		// Xファイルの読み込み
		D3DXLoadMeshFromX(MODEL_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatBadItem[nCnt],
			NULL,
			&g_nNumMatBadItem[nCnt],
			&g_pMeshBadItem[nCnt]);

		g_BadItem[nCnt].VtxMin = D3DXVECTOR3(10000, 10000, 10000);
		g_BadItem[nCnt].VtxMax = D3DXVECTOR3(-10000, -10000, -10000);

		int nNumVtx;										//頂点数
		DWORD sizeFVF;										//頂点フォーマットのサイズ
		BYTE *pVtxBuff;										//頂点バッファへのポインタ

		//頂点数を取得
		nNumVtx = g_pMeshBadItem[nCnt]->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshBadItem[nCnt]->GetFVF());

		//頂点バッファをロック
		g_pMeshBadItem[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVer = 0; nCntVer < nNumVtx; nCntVer++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//頂点座標の代入

			if (g_BadItem[nCnt].VtxMin.x >= vtx.x)
			{
				g_BadItem[nCnt].VtxMin.x = vtx.x;
			}
			if (g_BadItem[nCnt].VtxMin.y >= vtx.y)
			{
				g_BadItem[nCnt].VtxMin.y = vtx.y;
			}
			if (g_BadItem[nCnt].VtxMin.z >= vtx.z)
			{
				g_BadItem[nCnt].VtxMin.z = vtx.z;
			}

			if (g_BadItem[nCnt].VtxMax.x <= vtx.x)
			{
				g_BadItem[nCnt].VtxMax.x = vtx.x;
			}
			if (g_BadItem[nCnt].VtxMax.y <= vtx.y)
			{
				g_BadItem[nCnt].VtxMax.y = vtx.y;
			}
			if (g_BadItem[nCnt].VtxMax.z <= vtx.z)
			{
				g_BadItem[nCnt].VtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//サイズ分ポインタを進める
		}

		//頂点バッファをアンロック
		g_pMeshBadItem[nCnt]->UnlockVertexBuffer();

		//g_NumBadItem = 0;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBadItem(void)
{
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// メッシュの開放
		if (g_pMeshBadItem[nCnt] != NULL)
		{
			g_pMeshBadItem[nCnt]->Release();
			g_pMeshBadItem[nCnt] = NULL;
		}

		// マテリアルの開放
		if (g_pBuffMatBadItem[nCnt] != NULL)
		{
			g_pBuffMatBadItem[nCnt]->Release();
			g_pBuffMatBadItem[nCnt] = NULL;
		}

		// テクスチャの破棄
		if (g_pTextureBadItem[nCnt] != NULL)
		{
			g_pTextureBadItem[nCnt]->Release();
			g_pTextureBadItem[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBadItem(void)
{
	int nMove = 0;
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		if (g_BadItem[nCnt].bUse == true)
		{
			g_BadItem[nCnt].pos += g_BadItem[nCnt].move;

			//SetEffect(g_BadItem[nCnt].pos, D3DXCOLOR(15.0f, 15.0f, 15.0f, 15.0f), 15.0f, 20);

			if (g_BadItem[nCnt].pos.x > 300)
			{
				g_BadItem[nCnt].move.x = -3.0f;
			}
			if (g_BadItem[nCnt].pos.x < -300)
			{
				g_BadItem[nCnt].move.x = 3.0f;
			}

			g_BadItem[nCnt].rot.y -= 0.05f;

			SetPositionShadow(g_nIdxShadowBI[nCnt], D3DXVECTOR3(g_BadItem[nCnt].pos.x, 0.0f, g_BadItem[nCnt].pos.z));
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBadItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_BadItem[nCnt].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_BadItem[nCnt].rot.y, g_BadItem[nCnt].rot.x, g_BadItem[nCnt].rot.z);
		D3DXMatrixMultiply(&g_BadItem[nCnt].mtxWorld, &g_BadItem[nCnt].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, g_BadItem[nCnt].pos.x, g_BadItem[nCnt].pos.y, g_BadItem[nCnt].pos.z);
		D3DXMatrixMultiply(&g_BadItem[nCnt].mtxWorld, &g_BadItem[nCnt].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_BadItem[nCnt].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatBadItem[nCnt]->GetBufferPointer();

		if (g_BadItem[nCnt].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatBadItem[nCnt]; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, NULL);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBadItem[nCnt]);

				// モデル(パーツ)の描画
				g_pMeshBadItem[nCnt]->DrawSubset(nCntMat);

			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}


//=============================================================================
// アイテムの設定
//=============================================================================

void SetBadItem(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// 頂点情報の作成
	//VERTEX_3D *pVtx;

	int nNumVtx;				//頂点数
	DWORD sizeFVF;				//頂点フォーマットのサイズ
	BYTE *pVtxBuff;				//頂点バッファへのポインタ
	
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		//頂点数を取得
		nNumVtx = g_pMeshBadItem[nCnt]->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshBadItem[nCnt]->GetFVF());


		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pMeshBadItem[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		if (g_BadItem[nCnt].bUse == false)	//ブロックを使用している
		{
			g_BadItem[nCnt].pos = pos;
			g_BadItem[nCnt].move = move;
			g_BadItem[nCnt].bUse = true;
			g_nIdxShadowBI[nCnt] = SetShadow(D3DXVECTOR3(g_BadItem[nCnt].pos.x, 0.0f, g_BadItem[nCnt].pos.z), D3DXVECTOR3(0, 0, 0));

			g_NumBadItem++;//アイテムの総数を加算
			

			break;

		}

		// 頂点バッファをアンロックする
		g_pMeshBadItem[nCnt]->UnlockVertexBuffer();
	}
}

//=============================================================================
// 当たり判定処理
//=============================================================================
void CollisionBadItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMax,D3DXVECTOR3 *pVtxMin)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	TIMER *pTimer;
	pTimer = GetTimer();
	
	

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		if (g_BadItem[nCnt].bUse == true)
		{
			if (pPos->x+10 >= g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMin.x) &&
				pPos->x-10 <= g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMax.x))
			{
				if (pPos->z+10 >= g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMin.z) &&
					pPos->z-10 <= g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMax.z))
				{
					if (pPosOld->z+10 <= g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMin.z) &&
						pPos->z-10 >= g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMin.z))
					{//手前の判定
						pPos->z = g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMin.z) - 10;
					}
					else if (pPosOld->z-10 >= g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMax.z) &&
						pPos->z-10 <= g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMax.z))
					{//奥の判定
						pPos->z = g_BadItem[nCnt].pos.z + (g_BadItem[nCnt].VtxMax.z) + 10;
					}
					if (pPosOld->x-10 >= g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMax.x) &&
						pPos->x-10 <= g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMax.x))
					{//右の判定
						pPos->x = g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMax.x) + 10;
					}
					else if (pPosOld->x+10 <= g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMin.x) &&
						pPos->x+10 >= g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMin.x))
					{//左の判定
						pPos->x = g_BadItem[nCnt].pos.x + (g_BadItem[nCnt].VtxMin.x) - 10;
					}

					PlaySound(SOUND_LABEL_SE_HIT001);//アイテム入手時の音

					AddScore(10000);//アイテム入手時のポイント
					pTimer->nTime -= 2 * 100;//時間の増加

					g_BadItem[nCnt].bUse = false;//アイテムを表示しない
					DeleteShadow(g_nIdxShadowBI[nCnt]);

					g_NumBadItem--;

					//if (g_NumBadItem <= 0)
					//{//アイテムをすべて所得したら
					//	SetGameState(GAMESTATE_END);
					//}
				}
			}
		}
	}
}

//=============================================================================
// 障害物用モデル情報の取得
//=============================================================================
BADITEM *GetBadItem(void)
{
		return &g_BadItem[MAX_ARRANGEMENT];
}
