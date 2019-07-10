//=============================================================================
// ポリゴン処理 [bullet.cpp]
// Author : Kobayashi/小林将兵
//=============================================================================
#include "bullet.h"
#include "shadow.h"
#include "effect.h"
#include "explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME ("DATA\\TEXTURE\\加工bullet.png")
#define MAX_BULLET (222)
#define BULLET_SIZE (5.0f)
#define BULLET_POS (5.0f)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;

BULLET g_Bullet[MAX_BULLET];

int g_nIdxShadowBullet[MAX_BULLET];

//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_Bullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//g_Bullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCntBullet].bUse = false;
	}
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureBullet);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet2 = 0; nCntBullet2 < MAX_BULLET; nCntBullet2++)
	{
		//頂点座標の設定
		//g_Bullet[nCntBullet2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE, BULLET_SIZE + BULLET_POS, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE + BULLET_POS, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE + BULLET_POS, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BULLET_SIZE, -BULLET_SIZE + BULLET_POS, 0.0f);

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
	g_pVtxBuffBullet->Unlock();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	// テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
//^^^^^^^^^^^^^^^^^^^^^^^^^^
//		弾の発射設定
//^^^^^^^^^^^^^^^^^^^^^^^^^^
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)	
	{
		if (g_Bullet[nCntBullet].bUse == true)	//球が使用されている
		{
			SetEffect(g_Bullet[nCntBullet].pos, D3DXCOLOR(15.0f, 15.0f, 15.0f, 15.0f), 15.0f, 20);

			//弾の射出方向関連
			g_Bullet[nCntBullet].pos += g_Bullet[nCntBullet].move;

			//一定時間経過
			g_Bullet[nCntBullet].nLife--;
			if (g_Bullet[nCntBullet].nLife <= 0)
			{
				SetExplosion(D3DXVECTOR3(g_Bullet[nCntBullet].pos.x, 0.0f, g_Bullet[nCntBullet].pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				g_Bullet[nCntBullet].bUse = false;
				DeleteShadow(g_nIdxShadowBullet[nCntBullet]);
			}
			SetPositionShadow(g_nIdxShadowBullet[nCntBullet], D3DXVECTOR3(g_Bullet[nCntBullet].pos.x, 0.0f, g_Bullet[nCntBullet].pos.z));

		}
		
	}
	
	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	D3DXMATRIX mtxView, mtxTrans;//計算用マトリックス

	 //アルファテスト処理(透明化による画像の切り取り現象を無効にする)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);//REF = Reference:参照
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//FUNC = Function:機能 //GREATER = ～より大きい


	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Bullet[nCntBullet].mtxWorldBullet);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_Bullet[nCntBullet].mtxWorldBullet._11 = mtxView._11;
			g_Bullet[nCntBullet].mtxWorldBullet._12 = mtxView._21;
			g_Bullet[nCntBullet].mtxWorldBullet._13 = mtxView._31;
			g_Bullet[nCntBullet].mtxWorldBullet._21 = mtxView._12;
			g_Bullet[nCntBullet].mtxWorldBullet._22 = mtxView._22;
			g_Bullet[nCntBullet].mtxWorldBullet._23 = mtxView._32;
			g_Bullet[nCntBullet].mtxWorldBullet._31 = mtxView._13;
			g_Bullet[nCntBullet].mtxWorldBullet._32 = mtxView._23;
			g_Bullet[nCntBullet].mtxWorldBullet._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Bullet[nCntBullet].pos.x, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_Bullet[nCntBullet].mtxWorldBullet, &g_Bullet[nCntBullet].mtxWorldBullet, &mtxTrans);


			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCntBullet].mtxWorldBullet);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));


			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 球の設定
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// 頂点情報の作成
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == false)
		{
			g_Bullet[nCntBullet].nLife = 100;//弾の生存時間/距離
			g_Bullet[nCntBullet].pos = pos;
			g_Bullet[nCntBullet].move = move;
			g_Bullet[nCntBullet].bUse = true;
			g_nIdxShadowBullet[nCntBullet] = SetShadow(D3DXVECTOR3(g_Bullet[nCntBullet].pos.x, 0.0f, g_Bullet[nCntBullet].pos.z), D3DXVECTOR3(0, 0, 0));
			break;
		}
		//pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成


	// 頂点情報の設定

}

