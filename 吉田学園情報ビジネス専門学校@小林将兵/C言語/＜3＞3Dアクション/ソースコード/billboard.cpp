//=============================================================================
// ポリゴン処理 [billboard.cpp]
// Author : Kobayashi/小林将兵
//=============================================================================
#include "billboard.h"
#include "player.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME ("DATA\\TEXTURE\\error00.png")
#define TEXTURE_NAME02 ("DATA\\TEXTURE\\メルクちゃん.png")
#define TEXTURE_NAME03 ("DATA\\TEXTURE\\arrow.png")
#define MAX_BILLBOARD (50)
#define MAX_TYPE (3)

PLAYER *pPlayer_BillBoard;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureBillboard[MAX_TYPE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;

BILLBOARD g_Billboard[MAX_BILLBOARD];

//int g_nIdxShadowB[MAX_BILLBOARD];

//=============================================================================
// 初期化処理
//=============================================================================
void InitBillboard(void)
{
	int nCntBillboard;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_Billboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCntBillboard].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCntBillboard].nType = 0;
		g_Billboard[nCntBillboard].bUse = false;
	}
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureBillboard[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME02, &g_pTextureBillboard[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME03, &g_pTextureBillboard[2]);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	VERTEX_3D*pVtx;//頂点情報へのポインタ

				   //頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		//頂点座標の設定
		//g_posBillboard = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//法線の設定
		pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
		pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
		pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
		pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);

		pVtx += 4;//頂点データの情報を４つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffBillboard->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBillboard(void)
{
	for (int nCnt = 0; nCnt < MAX_TYPE; nCnt++)
	{
		// テクスチャの破棄
		if (g_pTextureBillboard[nCnt] != NULL)
		{
			g_pTextureBillboard[nCnt]->Release();
			g_pTextureBillboard[nCnt] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBillboard(void)
{
	pPlayer_BillBoard = GetPlayer();

	VERTEX_3D*pVtx;//頂点情報へのポインタ

				   //頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == true)
		{
			if (g_Billboard[nCntBillboard].nType == 2)
			{
				//g_Billboard[nCntBillboard].pos.x++;
			}
			
			//SetPositionShadow(g_nIdxShadowB[nCntBillboard], D3DXVECTOR3(g_Billboard[nCntBillboard].pos.x, 0.0f, g_Billboard[nCntBillboard].pos.z));
			if (g_Billboard[nCntBillboard].pos.x > 300)
			{
				//g_Billboard[nCntBillboard].pos.x = 0;
			}
		}
		if (g_Billboard[nCntBillboard].nType == 0)
		{//◆プレイヤー頭上に表示
			g_Billboard[nCntBillboard].pos.x = pPlayer_BillBoard->pos.x;
			g_Billboard[nCntBillboard].pos.z = pPlayer_BillBoard->pos.z;
			//◆指定範囲の場合危険を示すマークを表示
			if (pPlayer_BillBoard->pos.z > -2400&& pPlayer_BillBoard->pos.z < -2300||
				pPlayer_BillBoard->pos.z > -1600 && pPlayer_BillBoard->pos.z < -1500||
				pPlayer_BillBoard->pos.z > -800 && pPlayer_BillBoard->pos.z < -700||
				pPlayer_BillBoard->pos.z > 0 && pPlayer_BillBoard->pos.z < 100||
				pPlayer_BillBoard->pos.z > 800 && pPlayer_BillBoard->pos.z < 900||
				pPlayer_BillBoard->pos.z > 1600 && pPlayer_BillBoard->pos.z < 1700||
				pPlayer_BillBoard->pos.z > 1800 && pPlayer_BillBoard->pos.z < 1900)
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else//◆指定範囲外の場合は非表示
			{
				
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);
			}
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffBillboard->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBillboard(void)
{
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	D3DXMATRIX mtxView, mtxTrans, mtxRot;//計算用マトリックス

	 //アルファテスト処理(透明化による画像の切り取り現象を無効にする)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);//REF = Reference:参照
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//FUNC = Function:機能 //GREATER = ～より大きい

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Billboard[nCntBillboard].mtxWorldBillboard);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			if (g_Billboard[nCntBillboard].nType == 0 || g_Billboard[nCntBillboard].nType == 1)
			{
				g_Billboard[nCntBillboard].mtxWorldBillboard._11 = mtxView._11;
				g_Billboard[nCntBillboard].mtxWorldBillboard._12 = mtxView._21;
				g_Billboard[nCntBillboard].mtxWorldBillboard._13 = mtxView._31;
				g_Billboard[nCntBillboard].mtxWorldBillboard._21 = mtxView._12;
				g_Billboard[nCntBillboard].mtxWorldBillboard._22 = mtxView._22;
				g_Billboard[nCntBillboard].mtxWorldBillboard._23 = mtxView._32;
				g_Billboard[nCntBillboard].mtxWorldBillboard._31 = mtxView._13;
				g_Billboard[nCntBillboard].mtxWorldBillboard._32 = mtxView._23;
				g_Billboard[nCntBillboard].mtxWorldBillboard._33 = mtxView._33;
			}

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Billboard[nCntBillboard].pos.x, g_Billboard[nCntBillboard].pos.y, g_Billboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_Billboard[nCntBillboard].mtxWorldBillboard, &g_Billboard[nCntBillboard].mtxWorldBillboard, &mtxTrans);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Billboard[nCntBillboard].rot.y, g_Billboard[nCntBillboard].rot.x, g_Billboard[nCntBillboard].rot.z);
			D3DXMatrixMultiply(&g_Billboard[nCntBillboard].mtxWorldBillboard, &g_Billboard[nCntBillboard].mtxWorldBillboard, &mtxRot);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Billboard[nCntBillboard].mtxWorldBillboard);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
			{
				if (g_Billboard[nCntBillboard].bUse == true)
				{
					// テクスチャの設定
					pDevice->SetTexture(0, g_pTextureBillboard[g_Billboard[nCntBillboard].nType]);
					// ポリゴンの描画
					pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillboard * 4, 2);
				}
			}
		}
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// ビルボードの設定
//=============================================================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{

	int nSize = 0;
	// 頂点情報の作成
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == false)
		{
			g_Billboard[nCntBillboard].pos = pos;
			g_Billboard[nCntBillboard].rot = rot;
			g_Billboard[nCntBillboard].nType = nType;
			g_Billboard[nCntBillboard].bUse = true;
			//g_nIdxShadowB[nCntBillboard] = SetShadow(D3DXVECTOR3(g_Billboard[nCntBillboard].pos.x, 0.0f, g_Billboard[nCntBillboard].pos.z), D3DXVECTOR3(0, 0, 0));

			if (nType == 0|| nType == 1)
			{
				nSize = 10;
			}

			if (nType == 2)
			{
				nSize = 50;
			}

			pVtx[0].pos = D3DXVECTOR3(-10.0f- nSize, 20.0f + (nSize*2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(10.0f + nSize, 20.0f + (nSize*2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-10.0f - nSize, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(10.0f + nSize, 0.0f, 0.0f);


			break;
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffBillboard->Unlock();
}