//? ◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//? 弾処理 [bullet.cpp]
//? Author :小林 / Kobayashi
//? ◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "main.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "player.h"
#include "effect.h"
#include "sound.h"

//? ==================================================
//+ マクロ定義
//? ==================================================
#define	BULLET_MAX		(256)		// 弾の最大数
#define BULLET_SIZE	(15)
//? ==================================================
//+ 構造体
//? ==================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	int nLife;				//寿命
	BULLETTYPE type;		//弾の種類(誰の弾か/敵か味方か)
	bool bUse;				//使用しているかどうか
} Bullet;

//? ==================================================
//?+ グローバル変数宣言
//? ==================================================
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// 頂点バッファへのポインタ
Bullet g_aBullet[BULLET_MAX];						//球の情報

//? ==================================================
//?+ 初期化処理
//? ==================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// デバイスの取得
	pDevice = GetDevice();

	// 弾の情報の初期化
	for(nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\加工bullet.png", &g_pTextureBullet);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * BULLET_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//頂点情報の設定
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点カラーの設定 / 弾の色
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx += 4;//頂点データの情報を４つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//? ==================================================
//?+ 終了処理
//? ==================================================
void UninitBullet(void)
{
	// テクスチャの開放
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
	StopSound();
}

//? ==================================================
//?+ 更新処理
//? ==================================================
void UpdateBullet(void)
{
	//頂点情報の設定
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//!+ <プレイヤーの弾>
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				//弾の移動更新
				g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;

				//頂点座標の設定 / 弾の大きさ
				pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);
				pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);

				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 15.0f, 20);
			}

			//!+ <敵の弾>
			if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				//弾の移動更新
				g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;

				//頂点座標の設定 / 弾の大きさ
				pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);
				pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);

				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 15.0f, 20);

			}

			//!+ <弾の寿命>
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			//!+ <弾の画面外処理>
			if (g_aBullet[nCntBullet].pos.y < -10)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			else if (SCREEN_HEIGHT + 10 < g_aBullet[nCntBullet].pos.y)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

			//!+ <敵とのあたり判定>
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				ENEMY *pEnemy;
				pEnemy = GetEnemy();

				for (int nCountEnemy = 0; nCountEnemy < ENEMY_MAX; nCountEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (pEnemy->pos.x - 60 < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + 60 > g_aBullet[nCntBullet].pos.x
							&& pEnemy->pos.y - 60 < g_aBullet[nCntBullet].pos.y&& pEnemy->pos.y + 60 > g_aBullet[nCntBullet].pos.y)
						{
							HitEnemy(nCountEnemy, 1);//ダメージ処理
							g_aBullet[nCntBullet].bUse = false;
						}
					}
				}
			}
			//!+ <プレイヤーとのあたり判定>
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				PLAYER *pPlayer;
				pPlayer = GetPlayer();//プレイヤー位置の取得

				if (pPlayer->bDisp == true)
				{
					if (pPlayer->pos.x - 25 < g_aBullet[nCntBullet].pos.x && pPlayer->pos.x + 25 > g_aBullet[nCntBullet].pos.x
						&& pPlayer->pos.y - 25 < g_aBullet[nCntBullet].pos.y&& pPlayer->pos.y + 25 > g_aBullet[nCntBullet].pos.y)
					{
						HitPlayer(1);//ダメージ処理
						g_aBullet[nCntBullet].bUse = false;
					}
				}
			}
		}
	}
	pVtx += 4;
	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}


//? ==================================================
//?+ 描画処理
//? ==================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

	// ポリゴンの描画
	for(nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)		//球が使用されている
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet*4, 2);
		}
	}
}

//? ==================================================
//?+ 弾の設定処理
//? ==================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type)
{
	//頂点情報の設定
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(int nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)	//球が使用されていない
		{
			if (type == BULLETTYPE_PLAYER)
			{
				g_aBullet[nCntBullet].pos = pos;
				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].nLife = 80;//弾の生存時間/距離
				g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
				g_aBullet[nCntBullet].bUse = true;

				break;
			}

			if (type == BULLETTYPE_ENEMY)
			{
				g_aBullet[nCntBullet].pos = pos;
				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].nLife = 160;//弾の生存時間/距離160
				g_aBullet[nCntBullet].type = BULLETTYPE_ENEMY;
				g_aBullet[nCntBullet].bUse = true;

				break;
			}
		}
		
		pVtx += 4; //ポインタを進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

