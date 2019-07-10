//=============================================================================
// 紅魔式処理 [explosion.cpp]
// Author : Kobayashi/小林将兵
//=============================================================================
#include "main.h"
#include "explosion.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_EXPLOSION		(128)		// 紅魔式最大保管数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// 爆発の構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	int nCounterAnim;		//アニメーションカウンター
	int nPatternAnim;		//アニメーションパターンNo.
	D3DXMATRIX mtxWorldExplosion;	//ワールドマトリックス
	bool bUse;
} Explosion;

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// 頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];				//紅魔式情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitExplosion(void)
{
	int nCntExplosion;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 紅魔式情報の初期化
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\爆破エフェクト.png", &g_pTextureExplosion);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-25, 25, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(25, 25, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-25, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(25, 0.0f, 0.0f);
		//pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//テクスチャの設定
		/*pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);*/
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.166f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.166f);
		pVtx[3].tex = D3DXVECTOR2(0.166f, 0.166f);

		//法線の設定
		pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
		pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
		pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
		pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		pVtx += 4;			//頂点データの情報を４つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplosion(void)
{
	// テクスチャの開放
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	
	VERTEX_3D*pVtx;
	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
		{
			if (g_aExplosion[nCntExplosion].bUse == true)	//紅魔式使用可状態
			{
				g_aExplosion[nCntExplosion].nCounterAnim++; //カウンターの加算 爆発の速度
				if (g_aExplosion[nCntExplosion].nCounterAnim % 3 == 0)
				{
					g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 30;//パターンNo.更新
				}

				//	pVtx[nCntExplosion * 4].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 80, g_aExplosion[nCntExplosion].pos.y - 80, 0.0f);
				//	pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 80, g_aExplosion[nCntExplosion].pos.y - 80, 0.0f);
				//	pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 80, g_aExplosion[nCntExplosion].pos.y + 80, 0.0f);
				//	pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 80, g_aExplosion[nCntExplosion].pos.y+ 80, 0.0f);

					//横５分割　縦６分割
					pVtx[nCntExplosion*4].tex = D3DXVECTOR2(0.2f*g_aExplosion[nCntExplosion].nPatternAnim, 0.166f*(g_aExplosion[nCntExplosion].nPatternAnim / 5));
					pVtx[nCntExplosion*4+1].tex = D3DXVECTOR2(0.2f*g_aExplosion[nCntExplosion].nPatternAnim+0.2f, 0.166f*(g_aExplosion[nCntExplosion].nPatternAnim / 5));
					pVtx[nCntExplosion*4+2].tex = D3DXVECTOR2(0.2f*g_aExplosion[nCntExplosion].nPatternAnim, 0.166f*(g_aExplosion[nCntExplosion].nPatternAnim / 5)+0.166f);
					pVtx[nCntExplosion*4+3].tex = D3DXVECTOR2(0.2f*g_aExplosion[nCntExplosion].nPatternAnim+0.2f, 0.166f*(g_aExplosion[nCntExplosion].nPatternAnim / 5)+0.166f);

				if (g_aExplosion[nCntExplosion].nPatternAnim >= 29)
				{
					g_aExplosion[nCntExplosion].nPatternAnim = 0;
					g_aExplosion[nCntExplosion].bUse = false;
				}


				/*pVtx[nCntExplosion * 4].tex = D3DXVECTOR2(0.125f*g_aExplosion[nCntExplosion].nPatternAnim, 0.0f);
				pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2(0.125f*g_aExplosion[nCntExplosion].nPatternAnim + 0.125f, 0.0f);
				pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2(0.125f*g_aExplosion[nCntExplosion].nPatternAnim, 1.0f);
				pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2(0.125f*g_aExplosion[nCntExplosion].nPatternAnim + 0.125f, 1.0f);

				if (g_aExplosion[nCntExplosion].nPatternAnim >= 7)
				{
					g_aExplosion[nCntExplosion].nPatternAnim = 0;
					g_aExplosion[nCntExplosion].bUse = false;
				}*/


				//if (g_aExplosion[nCntExplosion].pos.y < -10)		//球の位置が画面外になったら
				//{
				//	g_aExplosion[nCntExplosion].bUse = false;
				//}

			}
		}
				//頂点バッファをアンロック
				g_pVtxBuffExplosion->Unlock();
}


//=============================================================================
// 描画処理
//=============================================================================
void DrawExplosion(void)
{
	int nCntExplosion;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxView, mtxTrans;//計算用マトリックス


	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtxWorldExplosion);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_aExplosion[nCntExplosion].mtxWorldExplosion._11 = mtxView._11;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._12 = mtxView._21;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._13 = mtxView._31;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._21 = mtxView._12;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._22 = mtxView._22;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._23 = mtxView._32;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._31 = mtxView._13;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._32 = mtxView._23;
			g_aExplosion[nCntExplosion].mtxWorldExplosion._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, g_aExplosion[nCntExplosion].pos.z);
			D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorldExplosion, &g_aExplosion[nCntExplosion].mtxWorldExplosion, &mtxTrans);


			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtxWorldExplosion);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureExplosion);

			// ポリゴンの描画
			if (g_aExplosion[nCntExplosion].bUse == true)		//紅魔式使用可状態
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
			}
		}
	}
}

//=============================================================================
// 爆弾の設定処理
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DCOLOR col)
{
	int nCntExplosion;

	////頂点情報の設定
	//VERTEX_3D*pVtx;
	////頂点バッファをロックし、頂点データへのポインタを所得
	//g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)	//紅魔式使用可状態
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			g_aExplosion[nCntExplosion].bUse = true;//使用している状態にする
			break;
		}
		//pVtx += 4; //ポインタを進める
	}
	////頂点バッファをアンロック
	//g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成


	// 頂点情報の設定

}


