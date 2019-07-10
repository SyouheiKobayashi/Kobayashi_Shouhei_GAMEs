//=============================================================================
// 障害物用モデル処理 [fallingRocks.cpp]
// Author : Kobayashi/小林将兵
//=============================================================================
#include "fallingRocks.h"
#include "sound.h"
#include "game.h"
#include "fade.h"
#include "camera.h"
#include "timer.h"
#include "bullet.h"
#include "player.h"
#include "shadow.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME ("DATA\\MODEL\\STONE00.x")
#define TEXTURE_NAME ("DATA\\TEXTURE\\洞窟天上.jpg")
#define MAX_ITEM (1)	//使用するモデルの種類
#define MAX_ARRANGEMENT (7)	//配置するモデルの数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshFallingRocks[MAX_ARRANGEMENT] = {};
LPD3DXBUFFER g_pBuffMatFallingRocks[MAX_ARRANGEMENT] = {};
LPDIRECT3DTEXTURE9 g_pTextureFallingRocks[MAX_ARRANGEMENT]= {};

DWORD g_nNumMatFallingRocks[MAX_ARRANGEMENT] = {};

FALLINGROCKS g_FallingRocks[MAX_ARRANGEMENT];

D3DXVECTOR3 g_SabunFR[MAX_ARRANGEMENT];//滑らかな方向転換のために使う

//int g_nIdxShadowFR[MAX_ARRANGEMENT];

PLAYER *pPlayer;

//=============================================================================
// 初期化処理
//=============================================================================
void InitFallingRocks(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// 位置・向きの初期設定
		g_FallingRocks[nCnt].pos = D3DXVECTOR3(0, 0, 0);//位置
		g_FallingRocks[nCnt].move = D3DXVECTOR3(0, 0, 0);//移動
		g_FallingRocks[nCnt].rot = D3DXVECTOR3(0, 0, 0);//向き
		g_FallingRocks[nCnt].nType = 0;
		g_FallingRocks[nCnt].bUse = false;
		g_FallingRocks[nCnt].bTouch = false;
		g_SabunFR[nCnt] = D3DXVECTOR3(0, 0, 0);//差分

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureFallingRocks[nCnt]);

		// Xファイルの読み込み
		D3DXLoadMeshFromX(MODEL_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatFallingRocks[nCnt],
			NULL,
			&g_nNumMatFallingRocks[nCnt],
			&g_pMeshFallingRocks[nCnt]);

		g_FallingRocks[nCnt].VtxMin = D3DXVECTOR3(10000, 10000, 10000);
		g_FallingRocks[nCnt].VtxMax = D3DXVECTOR3(-10000, -10000, -10000);

		int nNumVtx;										//頂点数
		DWORD sizeFVF;										//頂点フォーマットのサイズ
		BYTE *pVtxBuff;										//頂点バッファへのポインタ

		//頂点数を取得
		nNumVtx = g_pMeshFallingRocks[nCnt]->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshFallingRocks[nCnt]->GetFVF());

		//頂点バッファをロック
		g_pMeshFallingRocks[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVer = 0; nCntVer < nNumVtx; nCntVer++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//頂点座標の代入

			if (g_FallingRocks[nCnt].VtxMin.x >= vtx.x)
			{
				g_FallingRocks[nCnt].VtxMin.x = vtx.x;
			}
			if (g_FallingRocks[nCnt].VtxMin.y >= vtx.y)
			{
				g_FallingRocks[nCnt].VtxMin.y = vtx.y;
			}
			if (g_FallingRocks[nCnt].VtxMin.z >= vtx.z)
			{
				g_FallingRocks[nCnt].VtxMin.z = vtx.z;
			}

			if (g_FallingRocks[nCnt].VtxMax.x <= vtx.x)
			{
				g_FallingRocks[nCnt].VtxMax.x = vtx.x;
			}
			if (g_FallingRocks[nCnt].VtxMax.y <= vtx.y)
			{
				g_FallingRocks[nCnt].VtxMax.y = vtx.y;
			}
			if (g_FallingRocks[nCnt].VtxMax.z <= vtx.z)
			{
				g_FallingRocks[nCnt].VtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//サイズ分ポインタを進める
		}

		//頂点バッファをアンロック
		g_pMeshFallingRocks[nCnt]->UnlockVertexBuffer();

		//g_NumFallingRocks = 0;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFallingRocks(void)
{
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// メッシュの開放
		if (g_pMeshFallingRocks[nCnt] != NULL)
		{
			g_pMeshFallingRocks[nCnt]->Release();
			g_pMeshFallingRocks[nCnt] = NULL;
		}

		// マテリアルの開放
		if (g_pBuffMatFallingRocks[nCnt] != NULL)
		{
			g_pBuffMatFallingRocks[nCnt]->Release();
			g_pBuffMatFallingRocks[nCnt] = NULL;
		}

		// テクスチャの破棄
		if (g_pTextureFallingRocks[nCnt] != NULL)
		{
			g_pTextureFallingRocks[nCnt]->Release();
			g_pTextureFallingRocks[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFallingRocks(void)
{
	int nMove = 0;
	pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		if (g_FallingRocks[nCnt].bUse == true)
		{
			g_FallingRocks[nCnt].pos += g_FallingRocks[nCnt].move;

			if (g_FallingRocks[nCnt].pos.x > 300)
			{
				g_FallingRocks[nCnt].move.x = -2.0f;
			}
			if (g_FallingRocks[nCnt].pos.x < -300)
			{
				g_FallingRocks[nCnt].move.x = 2.0f;
			}

			if (g_FallingRocks[nCnt].nType == 0)
			{
				if (pPlayer->pos.z > -2400)//プレイヤー指定位置に到達した場合
				{
					
					g_FallingRocks[nCnt].move.y = -19.0f;
					
				}
			}
			if (g_FallingRocks[nCnt].nType == 1)
			{
				if (pPlayer->pos.z > -1600)//プレイヤー指定位置に到達した場合
				{
					g_FallingRocks[nCnt].move.y = -19.0f;
				}
			}
			if (g_FallingRocks[nCnt].nType == 2)
			{
				if (pPlayer->pos.z > -800)//プレイヤー指定位置に到達した場合
				{
					g_FallingRocks[nCnt].move.y = -19.0f;
				}
			}
			if (g_FallingRocks[nCnt].nType == 3)
			{
				if (pPlayer->pos.z > 0)//プレイヤー指定位置に到達した場合
				{
					g_FallingRocks[nCnt].move.y = -19.0f;
				}
			}
			if (g_FallingRocks[nCnt].nType == 4)
			{
				if (pPlayer->pos.z > 800)//プレイヤー指定位置に到達した場合
				{
					g_FallingRocks[nCnt].move.y = -19.0f;
				}
			}
			if (g_FallingRocks[nCnt].nType == 5)
			{
				if (pPlayer->pos.z > 1600)//プレイヤー指定位置に到達した場合
				{
					g_FallingRocks[nCnt].move.y = -19.0f;
				}
			}
			if (g_FallingRocks[nCnt].nType == 6)
			{
				if (pPlayer->pos.z > 1800)//プレイヤー指定位置に到達した場合
				{
					g_FallingRocks[nCnt].move.y = -19.0f;
				}
			}
			//◆落石指定pos到達時、moveを0(moveを0にした場合、↓あたり判定に書かれている処理を行う)
			if (g_FallingRocks[nCnt].pos.y <= 0)
			{
				g_FallingRocks[nCnt].move.y = 0;
				g_FallingRocks[nCnt].move.x = 0;
				
					
			}
			if (g_FallingRocks[nCnt].pos.y >= 650&& g_FallingRocks[nCnt].pos.y <= 700)
			{
				PlaySound(SOUND_LABEL_SE_FALL);//アイテム入手時の音
			}

			//SetPositionShadow(g_nIdxShadowFR[nCnt], D3DXVECTOR3(g_FallingRocks[nCnt].pos.x, 0.0f, g_FallingRocks[nCnt].pos.z));
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFallingRocks(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_FallingRocks[nCnt].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_FallingRocks[nCnt].rot.y, g_FallingRocks[nCnt].rot.x, g_FallingRocks[nCnt].rot.z);
		D3DXMatrixMultiply(&g_FallingRocks[nCnt].mtxWorld, &g_FallingRocks[nCnt].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, g_FallingRocks[nCnt].pos.x, g_FallingRocks[nCnt].pos.y, g_FallingRocks[nCnt].pos.z);
		D3DXMatrixMultiply(&g_FallingRocks[nCnt].mtxWorld, &g_FallingRocks[nCnt].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_FallingRocks[nCnt].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatFallingRocks[nCnt]->GetBufferPointer();

		if (g_FallingRocks[nCnt].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatFallingRocks[nCnt]; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, NULL);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureFallingRocks[nCnt]);

				// モデル(パーツ)の描画
				g_pMeshFallingRocks[nCnt]->DrawSubset(nCntMat);

			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}


//=============================================================================
// アイテムの設定
//=============================================================================

void SetFallingRocks(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType)
{
	// 頂点情報の作成
	//VERTEX_3D *pVtx;

	int nNumVtx;				//頂点数
	DWORD sizeFVF;				//頂点フォーマットのサイズ
	BYTE *pVtxBuff;				//頂点バッファへのポインタ
	
	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		//頂点数を取得
		nNumVtx = g_pMeshFallingRocks[nCnt]->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshFallingRocks[nCnt]->GetFVF());


		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pMeshFallingRocks[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		if (g_FallingRocks[nCnt].bUse == false)	//ブロックを使用している
		{
			g_FallingRocks[nCnt].pos = pos;
			g_FallingRocks[nCnt].move = move;
			g_FallingRocks[nCnt].nType = nType;
			g_FallingRocks[nCnt].bUse = true;
			//g_nIdxShadowFR[nCnt] = SetShadow(D3DXVECTOR3(g_FallingRocks[nCnt].pos.x, 0.0f, g_FallingRocks[nCnt].pos.z), D3DXVECTOR3(0, 0, 0));

			break;

		}

		// 頂点バッファをアンロックする
		g_pMeshFallingRocks[nCnt]->UnlockVertexBuffer();
	}
}

//=============================================================================
// 当たり判定処理
//=============================================================================
void CollisionFallingRocks(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMax,D3DXVECTOR3 *pVtxMin)
{
	
	pPlayer = GetPlayer();

	TIMER *pTimer;
	pTimer = GetTimer();
	
	

	for (int nCnt = 0; nCnt < MAX_ARRANGEMENT; nCnt++)
	{
		if (g_FallingRocks[nCnt].bUse == true)
		{
			if (pPos->x+10 >= g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMin.x) &&
				pPos->x-10 <= g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMax.x))
			{
				if (pPos->z+10 >= g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMin.z) &&
					pPos->z-10 <= g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMax.z))
				{
					if (pPos->y + 10 >= g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMin.y) &&
						pPos->y - 10 <= g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMax.y))
					{
						if (g_FallingRocks[nCnt].move.y != 0)
						{
							FADE pFade;

							pFade = *GetFade();

							//モード設定
							SetFade(MODE_RESULT);

							pPlayer->move = D3DXVECTOR3(0, 0, 0);//移動量を0にする
						}

						if (pPosOld->z + 10 <= g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMin.z) &&
							pPos->z + 10 >= g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMin.z))
						{//手前の判定
							pPos->z = g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMin.z) - 10;
						}
						else if (pPosOld->z - 10 >= g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMax.z) &&
							pPos->z - 10 <= g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMax.z))
						{//奥の判定
							pPos->z = g_FallingRocks[nCnt].pos.z + (g_FallingRocks[nCnt].VtxMax.z) + 10;
						}
						if (pPosOld->x - 10 >= g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMax.x) &&
							pPos->x - 10 <= g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMax.x))
						{//右の判定
							pPos->x = g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMax.x) + 10;
						}
						else if (pPosOld->x + 10 <= g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMin.x) &&
							pPos->x + 10 >= g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMin.x))
						{//左の判定
							pPos->x = g_FallingRocks[nCnt].pos.x + (g_FallingRocks[nCnt].VtxMin.x) - 10;
						}

						if (pPosOld->y + 10 <= g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMin.y) &&
							pPos->y - 10 >= g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMin.y))
						{//下の判定
							pPos->y = g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMin.y) - 10;

						

						}
						else if (pPosOld->y - 10 >= g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMax.y) &&
							pPos->y - 10 <= g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMax.y))
						{//上の判定
							pPos->y = g_FallingRocks[nCnt].pos.y + (g_FallingRocks[nCnt].VtxMax.y) + 10;

						}
					}
					
				}
			}

		}
	}
}

//=============================================================================
// 障害物用モデル情報の取得
//=============================================================================
FALLINGROCKS *GetFallingRocks(void)
{
		return &g_FallingRocks[MAX_ARRANGEMENT];
}
