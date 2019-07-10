//? ◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//? 敵処理 [enemy.cpp]
//? Author :小林 / Kobayshi
//? ◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "enemy.h"
#include "explosion.h"
#include "bullet.h"
#include "game.h"
#include "score.h"
#include "player.h"
#include "sound.h"
//? ==================================================
//? グローバル変数宣言
//? ==================================================
LPDIRECT3DTEXTURE9		g_apTextureEnemy[ENEMY_TYPE] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// 頂点バッファへのポインタ
ENEMY g_aEnemy[ENEMY_MAX];										//敵の情報
MOVE g_move;
int g_nNumEnemy;//敵の総数
int g_nCountAnimE; //アニメーションカウンター
int g_nPatternAnimE;//アニメーションパターンNo.
//? ==================================================
//? 初期化処理
//? ==================================================
void InitEnemy(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	g_nCountAnimE = 0;
	g_nPatternAnimE = 0;
	g_nNumEnemy = 0;
	g_move = MOVE_R;
	// 敵の情報の初期化
	for(int nCntEnemy = 0; nCntEnemy < ENEMY_MAX; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 1;
		g_aEnemy[nCntEnemy].bUse = false;
		
	}

	// テクスチャの読み込み(４体分)
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\ENEMY\\enemy100.png", &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\ENEMY\\enemy101.png", &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\ENEMY\\enemy102.png", &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\ENEMY\\enemy103.png", &g_apTextureEnemy[3]);

	// 頂点情報の作成
	VERTEX_2D *pVtx;
	// 頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * ENEMY_MAX,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(int nCntEnemy = 0; nCntEnemy < ENEMY_MAX; nCntEnemy++)
	{
		////頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);


		pVtx += 4;//頂点データの情報を４つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
	//g_nNumEnemy = 0;//敵の総数をクリア
}

//? ==================================================
//? 終了処理
//? ==================================================
void UninitEnemy(void)
{
	// テクスチャの開放
	for(int nCntTex = 0; nCntTex < ENEMY_TYPE; nCntTex++)
	{
		// テクスチャの開放
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//? ==================================================
//? 更新処理
//? ==================================================
void UpdateEnemy(void)
{
	float nKakudo;//角度の変数
	PLAYER *pPlayer;
	pPlayer = GetPlayer();//プレイヤー情報の取得

	

	// 頂点情報の作成
	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL://通常時の処理
				g_aEnemy[nCntEnemy].nCounterState++;
				if (g_aEnemy[nCntEnemy].nCounterState % ENEMY_INTERVAL == 0)
				{
					//プレイヤーの位置に向けて発射
					nKakudo = atan2f(pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(nKakudo)*6.0f, cosf(nKakudo)*6.0f, 0.0f), BULLETTYPE_ENEMY);
				}
				break;

			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;//通常の状態に戻す

					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				break;
			}
		}
			switch (g_move)
			{
			case MOVE_R:
				g_aEnemy[nCntEnemy].move.x = 5.0f;
				g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
				if (g_aEnemy[nCntEnemy].pos.x == SCREEN_WIDTH-60)
				{
					g_move = MOVE_L;
				}
				break;

			case MOVE_L:

				g_aEnemy[nCntEnemy].move.x = 5.0f;
				g_aEnemy[nCntEnemy].pos.x -= g_aEnemy[nCntEnemy].move.x;
				if (-160 == g_aEnemy[nCntEnemy].pos.x)
				{
					g_move = MOVE_R;
				}

				break;
			}

		pVtx[0].pos = D3DXVECTOR3(-ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.x, -ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.x, -ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.x, +ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.x, +ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.y, 0.0f);

		//!+ <エネミーのアニメーション>
		g_aEnemy[nCntEnemy].nCountAnimE++; 
		if ((g_aEnemy[nCntEnemy].nCountAnimE % 20) == 0)
		{
			g_aEnemy[nCntEnemy].nPatternAnimE = (g_aEnemy[nCntEnemy].nPatternAnimE + 1) % 2;

			pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aEnemy[nCntEnemy].nPatternAnimE*0.5f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f + (g_aEnemy[nCntEnemy].nPatternAnimE*0.5f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aEnemy[nCntEnemy].nPatternAnimE*0.5f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f + (g_aEnemy[nCntEnemy].nPatternAnimE*0.5f), 1.0f);
		}


		pVtx += 4;

	}
	g_pVtxBuffEnemy->Unlock();
}

//? ==================================================
//? 描画処理
//? ==================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(int nCntEnemy = 0; nCntEnemy < ENEMY_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//? ==================================================
//? 敵の設定
//? ==================================================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < ENEMY_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)	//敵が使用されていない
		{
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nLife = 5;
			g_aEnemy[nCntEnemy].bUse = true;


			//頂点座標の設定 / 大きさ
			pVtx[0].pos = D3DXVECTOR3(-ENEMY_SIZE+ g_aEnemy[nCntEnemy].pos.x,  - ENEMY_SIZE+ g_aEnemy[nCntEnemy].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.x,  - ENEMY_SIZE+ g_aEnemy[nCntEnemy].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.x,  + ENEMY_SIZE+ g_aEnemy[nCntEnemy].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.x,  + ENEMY_SIZE+ g_aEnemy[nCntEnemy].pos.y, 0.0f);

			g_nNumEnemy++;//敵の総数を加算

			break;
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//? ==================================================
//? 敵の通常、ダメージ時の表示処理
//? ==================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)	//体力が0以下になった場合
	{
		//[敵を撃破した時の爆発の生成]
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_aEnemy[nCntEnemy].bUse = false;

		PlaySound(SOUND_EXPLOSION);
 		AddScore(1000);//スコア
		g_nNumEnemy--;//敵の総数減らす

		if (g_nNumEnemy <= 0)//クリア条件
		{
			SetGameState(GAMESTATE_END);
		}
	}
	else//体力が余ってる場合の処理
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;//被弾時
		g_aEnemy[nCntEnemy].nCounterState = 5;//ダメージ表現の時間

		//頂点カラーの設定
		VERTEX_2D *pVtx;
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += (nCntEnemy * 4);
		//被弾時のカラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		g_pVtxBuffEnemy->Unlock();
	}
}
//? ==================================================
//? 敵の取得
//? ==================================================
ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}
