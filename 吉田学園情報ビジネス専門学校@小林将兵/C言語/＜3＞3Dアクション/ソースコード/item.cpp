//=============================================================================
// 障害物用モデル処理 [item.cpp]
// Author : Kobayashi/小林将兵
//=============================================================================
#include "item.h"
#include "sound.h"
#include "game.h"
#include "camera.h"
#include "score.h"
#include "timer.h"
#include "bullet.h"
#include "player.h"
#include "shadow.h"
//#include "fade.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME ("DATA\\MODEL\\ITEM00.x")
#define TEXTURE_NAME ("DATA\\UV\\アイテム01_UV.jpg")
#define MAX_ITEM (1)	//使用するモデルの種類
#define MAX_ARRANGEMENT (5)	//配置するモデルの数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshItem[MAX_ARRANGEMENT] = {};
LPD3DXBUFFER g_pBuffMatItem[MAX_ARRANGEMENT] = {};
LPDIRECT3DTEXTURE9 g_pTextureItem[MAX_ARRANGEMENT]= {};

DWORD g_nNumMatItem[MAX_ARRANGEMENT] = {};

ITEM g_Item[MAX_ARRANGEMENT];

D3DXVECTOR3 g_SabunI[MAX_ARRANGEMENT];//滑らかな方向転換のために使う

int g_nIdxShadowI[MAX_ARRANGEMENT];

int g_NumItem;//アイテムの総数

//=============================================================================
// 初期化処理
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// 位置・向きの初期設定
		g_Item[nCnt].pos = D3DXVECTOR3(0, 0, 0);//位置
		g_Item[nCnt].move = D3DXVECTOR3(0, 0, 0);//移動
		g_Item[nCnt].rot = D3DXVECTOR3(0, 0, 0);//向き
		g_Item[nCnt].bUse = false;
		g_Item[nCnt].bTouch = false;
		g_SabunI[nCnt] = D3DXVECTOR3(0, 0, 0);//差分
		g_NumItem = 0;

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureItem[nCnt]);

		// Xファイルの読み込み
		D3DXLoadMeshFromX(MODEL_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatItem[nCnt],
			NULL,
			&g_nNumMatItem[nCnt],
			&g_pMeshItem[nCnt]);

		g_Item[nCnt].VtxMin = D3DXVECTOR3(10000, 10000, 10000);
		g_Item[nCnt].VtxMax = D3DXVECTOR3(-10000, -10000, -10000);

		int nNumVtx;										//頂点数
		DWORD sizeFVF;										//頂点フォーマットのサイズ
		BYTE *pVtxBuff;										//頂点バッファへのポインタ

		//頂点数を取得
		nNumVtx = g_pMeshItem[nCnt]->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshItem[nCnt]->GetFVF());

		//頂点バッファをロック
		g_pMeshItem[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVer = 0; nCntVer < nNumVtx; nCntVer++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//頂点座標の代入

			if (g_Item[nCnt].VtxMin.x >= vtx.x)
			{
				g_Item[nCnt].VtxMin.x = vtx.x;
			}
			if (g_Item[nCnt].VtxMin.y >= vtx.y)
			{
				g_Item[nCnt].VtxMin.y = vtx.y;
			}
			if (g_Item[nCnt].VtxMin.z >= vtx.z)
			{
				g_Item[nCnt].VtxMin.z = vtx.z;
			}

			if (g_Item[nCnt].VtxMax.x <= vtx.x)
			{
				g_Item[nCnt].VtxMax.x = vtx.x;
			}
			if (g_Item[nCnt].VtxMax.y <= vtx.y)
			{
				g_Item[nCnt].VtxMax.y = vtx.y;
			}
			if (g_Item[nCnt].VtxMax.z <= vtx.z)
			{
				g_Item[nCnt].VtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//サイズ分ポインタを進める
		}

		//頂点バッファをアンロック
		g_pMeshItem[nCnt]->UnlockVertexBuffer();

		//g_NumItem = 0;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem(void)
{
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// メッシュの開放
		if (g_pMeshItem[nCnt] != NULL)
		{
			g_pMeshItem[nCnt]->Release();
			g_pMeshItem[nCnt] = NULL;
		}

		// マテリアルの開放
		if (g_pBuffMatItem[nCnt] != NULL)
		{
			g_pBuffMatItem[nCnt]->Release();
			g_pBuffMatItem[nCnt] = NULL;
		}

		// テクスチャの破棄
		if (g_pTextureItem[nCnt] != NULL)
		{
			g_pTextureItem[nCnt]->Release();
			g_pTextureItem[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem(void)
{
	int nMove = 0;
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		if (g_Item[nCnt].bUse == true)
		{
			g_Item[nCnt].pos += g_Item[nCnt].move;

			if (g_Item[nCnt].pos.x > 300)
			{
				g_Item[nCnt].move.x = -2.0f;
			}
			if (g_Item[nCnt].pos.x < -300)
			{
				g_Item[nCnt].move.x = 2.0f;
			}

			g_Item[nCnt].rot.y += 0.05f;

			SetPositionShadow(g_nIdxShadowI[nCnt], D3DXVECTOR3(g_Item[nCnt].pos.x, 0.0f, g_Item[nCnt].pos.z));
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Item[nCnt].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Item[nCnt].rot.y, g_Item[nCnt].rot.x, g_Item[nCnt].rot.z);
		D3DXMatrixMultiply(&g_Item[nCnt].mtxWorld, &g_Item[nCnt].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, g_Item[nCnt].pos.x, g_Item[nCnt].pos.y, g_Item[nCnt].pos.z);
		D3DXMatrixMultiply(&g_Item[nCnt].mtxWorld, &g_Item[nCnt].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Item[nCnt].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatItem[nCnt]->GetBufferPointer();

		if (g_Item[nCnt].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatItem[nCnt]; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, NULL);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureItem[nCnt]);

				// モデル(パーツ)の描画
				g_pMeshItem[nCnt]->DrawSubset(nCntMat);

			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}


//=============================================================================
// アイテムの設定
//=============================================================================

void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// 頂点情報の作成
	//VERTEX_3D *pVtx;

	int nNumVtx;				//頂点数
	DWORD sizeFVF;				//頂点フォーマットのサイズ
	BYTE *pVtxBuff;				//頂点バッファへのポインタ
	
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		//頂点数を取得
		nNumVtx = g_pMeshItem[nCnt]->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshItem[nCnt]->GetFVF());


		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pMeshItem[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		if (g_Item[nCnt].bUse == false)	//ブロックを使用している
		{
			g_Item[nCnt].pos = pos;
			g_Item[nCnt].move = move;
			g_Item[nCnt].bUse = true;
			g_nIdxShadowI[nCnt] = SetShadow(D3DXVECTOR3(g_Item[nCnt].pos.x, 0.0f, g_Item[nCnt].pos.z), D3DXVECTOR3(0, 0, 0));

			g_NumItem++;//アイテムの総数を加算
			

			break;

		}

		// 頂点バッファをアンロックする
		g_pMeshItem[nCnt]->UnlockVertexBuffer();
	}
}

//=============================================================================
// 当たり判定処理
//=============================================================================
void CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMax,D3DXVECTOR3 *pVtxMin)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	TIMER *pTimer;
	pTimer = GetTimer();
	
	

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		if (g_Item[nCnt].bUse == true)
		{
			if (pPos->x+10 >= g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMin.x) &&
				pPos->x-10 <= g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMax.x))
			{
				if (pPos->z+10 >= g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMin.z) &&
					pPos->z-10 <= g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMax.z))
				{
					if (pPosOld->z+10 <= g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMin.z) &&
						pPos->z-10 >= g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMin.z))
					{//手前の判定
						pPos->z = g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMin.z) - 10;
					}
					else if (pPosOld->z-10 >= g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMax.z) &&
						pPos->z-10 <= g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMax.z))
					{//奥の判定
						pPos->z = g_Item[nCnt].pos.z + (g_Item[nCnt].VtxMax.z) + 10;
					}
					if (pPosOld->x-10 >= g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMax.x) &&
						pPos->x-10 <= g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMax.x))
					{//右の判定
						pPos->x = g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMax.x) + 10;
					}
					else if (pPosOld->x+10 <= g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMin.x) &&
						pPos->x+10 >= g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMin.x))
					{//左の判定
						pPos->x = g_Item[nCnt].pos.x + (g_Item[nCnt].VtxMin.x) - 10;
					}
					PlaySound(SOUND_LABEL_SE_HIT000);//アイテム入手時の音

					AddScore(10000);//アイテム入手時のポイント
					pTimer->nTime += 2 * 100;//時間の増加

					g_Item[nCnt].bUse = false;//アイテムを表示しない
					DeleteShadow(g_nIdxShadowI[nCnt]);

					g_NumItem--;

					//if (g_NumItem <= 0)
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
ITEM *GetItem(void)
{
		return &g_Item[MAX_ARRANGEMENT];
}
