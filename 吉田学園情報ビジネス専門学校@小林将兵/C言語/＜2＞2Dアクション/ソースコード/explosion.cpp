//=============================================================================
//
// 弾処理 [explosion.cpp]
// Author :小林 / Kobayashi
//
//=============================================================================
#include "main.h"
#include "explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_EXPLOSION		(128)		// 爆発の最大数

//*****************************************************************************
// 爆発の構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	int nCounterAnim;		//アニメーションカウンター
	int nPatternAnim;		//アニメーションパターンNo.
	bool bUse;
} Explosion;

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// 頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];				//爆発の情報

//D3DXVECTOR3 g_posBullet; //ポリゴンの位置
//D3DXVECTOR3 g_moveBullet; //ポリゴンの移動量

//=============================================================================
// 初期化処理
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// デバイスの取得
	pDevice = GetDevice();

	// 弾の情報の初期化
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
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		//テクスチャ座標の設定
		/*pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.2f, 1.0f);*/

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.166f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.166f);
		pVtx[3].tex = D3DXVECTOR2(0.166f, 0.166f);

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
	
	VERTEX_2D*pVtx;
	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
		{
			if (g_aExplosion[nCntExplosion].bUse == true)	//爆発が使用されている
			{
#if 1
				g_aExplosion[nCntExplosion].nCounterAnim++; //カウンターの加算 爆発の速度
				if (g_aExplosion[nCntExplosion].nCounterAnim % 1 == 0)
				{
					g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 30;//パターンNo.更新
				}

					pVtx[nCntExplosion * 4].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 40, g_aExplosion[nCntExplosion].pos.y - 20, 0.0f);
					pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 40, g_aExplosion[nCntExplosion].pos.y - 20, 0.0f);
					pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 40, g_aExplosion[nCntExplosion].pos.y + 60, 0.0f);
					pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 40, g_aExplosion[nCntExplosion].pos.y+ 60, 0.0f);

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
#endif
#if 0
				g_aExplosion[nCntExplosion].nCounterAnim++; //カウンターの加算 爆発の速度
				if (g_aExplosion[nCntExplosion].nCounterAnim % 5 == 0)
				{
					g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 8;//パターンNo.更新
				}

				pVtx[nCntExplosion * 4].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y - 20, 0.0f);
				pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 40, g_aExplosion[nCntExplosion].pos.y - 20, 0.0f);
				pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y + 20, 0.0f);
				pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 40, g_aExplosion[nCntExplosion].pos.y + 20, 0.0f);

				pVtx[nCntExplosion * 4].tex = D3DXVECTOR2(0.125f*g_aExplosion[nCntExplosion].nPatternAnim, 0.0f);
				pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2(0.125f*g_aExplosion[nCntExplosion].nPatternAnim + 0.125f, 0.0f);
				pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2(0.125f*g_aExplosion[nCntExplosion].nPatternAnim, 1.0f);
				pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2(0.125f*g_aExplosion[nCntExplosion].nPatternAnim + 0.125f, 1.0f);

				if (g_aExplosion[nCntExplosion].nPatternAnim >= 7)
				{
					g_aExplosion[nCntExplosion].nPatternAnim = 0;
					g_aExplosion[nCntExplosion].bUse = false;
				}
#endif
				//g_aExplosion[nCntExplosion].pos.y += 5.0f;

#if 0
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(100 + g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(300 + g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(100 + g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y + 300, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(300 + g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y + 300, 0.0f);
				//テクスチャの設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(0.2f, 0.5f);
#endif
				if (g_aExplosion[nCntExplosion].pos.y < -10)		//球の位置が画面外になったら
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}

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
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	// ポリゴンの描画
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{

		if (g_aExplosion[nCntExplosion].bUse == true)		//球が使用されている
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion *4, 2);
		}
	}
}

//=============================================================================
// 爆弾の設定処理
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DCOLOR col)
{
	int nCntExplosion;

	//頂点情報の設定
	VERTEX_2D*pVtx;
	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)	//球が使用されていない
		{
			
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			g_aExplosion[nCntExplosion].bUse = true;//使用している状態にする

		break;
		}
		//pVtx += (nCntBullet * 4); //該当の位置まで進める
		pVtx += 4; //ポインタを進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();
}

