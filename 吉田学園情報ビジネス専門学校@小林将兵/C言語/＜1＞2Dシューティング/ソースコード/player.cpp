//? ◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//? [Player.cpp]
//? Author : Kobayashi / 小林
//? ◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "game.h"
#include "sound.h"
//? ==================================================
//? グローバル変数
//? ==================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;

int g_nCountAnim; //アニメーションカウンター
int g_nPatternAnim;//アニメーションパターンNo.
PLAYER g_player;

//? ==================================================
//? 初期化
//? ==================================================
void InitPlayer(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// プレイヤーの情報の初期化	
	g_player.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.state = PLAYERSTATE_NORMAL;
	g_player.nCounterState = 0;
	g_player.nLife = PLAYER_LIFE;
	g_player.bDisp = true;

	//アニメーション
	g_nCountAnim = 0;
	g_nPatternAnim = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\PLAYER\\player000.png", &g_pTexturePlayer);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-PLAYER_SIZE + g_player.pos.x, g_player.pos.y - PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PLAYER_SIZE + g_player.pos.x, g_player.pos.y - PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-PLAYER_SIZE + g_player.pos.x, g_player.pos.y + PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PLAYER_SIZE + g_player.pos.x, g_player.pos.y + PLAYER_SIZE, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();
}

//? ==================================================
//? 終了
//? ==================================================
void UninitPlayer(void)
{
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//? ==================================================
//? 更新
//? ==================================================
void UpdatePlayer(void)
{
	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL://通常時の処理
		break;

	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;//通常状態時

		//[頂点カラーの設定]
			VERTEX_2D *pVtx;
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_pVtxBuffPlayer->Unlock();
		}
		break;

	case PLAYERSTATE_DEATH:
		SetGameState(GAMESTATE_END);
		g_player.state = PLAYERSTATE_END;
		break;
	}

	//アニメーション
#if 0
	g_nCountAnim++; //カウンターの加算
	if ((g_nCountAnim % 8) == 0)
	{
		g_nPatternAnim++;
		g_nPatternAnim = (g_nPatternAnim + 1) % 10;//パターンNo.更新
	}
#endif
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//!+ <弾の発射処理>
	if (g_player.bDisp == true)
	{
		if (GetKeyboardTrigger(DIK_SPACE) == true)//スペース押しての弾の射出
		{
			PlaySound(SOUND_BULLET);
			SetBullet(g_player.pos, D3DXVECTOR3(0.0f, -11.0f, 0.0f), BULLETTYPE_PLAYER);//上
			SetBullet(g_player.pos, D3DXVECTOR3(-7.0f, -11.0f, 0.0f), BULLETTYPE_PLAYER);
			SetBullet(g_player.pos, D3DXVECTOR3(7.0f, -11.0f, 0.0f), BULLETTYPE_PLAYER);
		}
	}

	//!+ <移動に関する処理>
	//左
	if (GetKeyboardPress(DIK_A) == true)
	{
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_player.move.x += sinf(-3.14f * 0.75f)*Player_Speed;
			g_player.move.y += cosf(-3.14f * 0.75f)*Player_Speed;
			if (g_player.pos.y < 20)
			{
				g_player.move.y = 0;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_player.move.x += sinf(-3.14f * 0.25f)*Player_Speed;
			g_player.move.y += cosf(-3.14f * 0.25f)*Player_Speed;
			if (g_player.pos.y > 670)//ウィンドウの高さ - 自機の高さ = 680
			{
				g_player.move.y = 0;
			}
		}
		else
		{
			g_player.move.x -= Player_Speed; //ポリゴンの位置を左に移動(速さ)
		}
		if (g_player.pos.x < 25)
		{
			g_player.move.x = 0;
		}
	}
	//右
	else if (GetKeyboardPress(DIK_D) == true)
	{
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_player.move.x += sinf(3.14f * 0.75f)*Player_Speed;
			g_player.move.y += cosf(3.14f * 0.75f)*Player_Speed;
			if (g_player.pos.y < 20)
			{
				g_player.move.y = 0;
			}

		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_player.move.x += sinf(3.14f * 0.25f)*Player_Speed;
			g_player.move.y += cosf(3.14f * 0.25f)*Player_Speed;
			if (g_player.pos.y > 670)//ウィンドウの高さ - 自機の高さ = 680
			{
				g_player.move.y = 0;
			}
		}
		else
		{
			g_player.move.x += Player_Speed; //ポリゴンの位置を右に移動
		}
		if (g_player.pos.x > 1255)
		{
			g_player.move.x = 0;
		}
	}

	//上
	else if (GetKeyboardPress(DIK_W) == true)
	{
		g_player.move.y -= Player_Speed; //ポリゴンの位置を上に移動
		if (g_player.pos.y < 20)
		{
			g_player.move.y = 0;
		}
	}

	//下
	else if (GetKeyboardPress(DIK_S) == true)
	{
		g_player.move.y += Player_Speed; //ポリゴンの位置を下に移動
		if (g_player.pos.y > 670)//ウィンドウの高さ - 自機の高さ = 680
		{
			g_player.move.y = 0;
		}
	}

	//位置更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;
	//斜め移動更新
	g_player.move.x += (0.0f - g_player.move.x)*0.2f;
	g_player.move.y += (0.0f - g_player.move.y)*0.2f;

#if 0
	/*pVtx[0].tex = D3DXVECTOR2(g_nPatternAnim*0.2f,          0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_nPatternAnim*0.2f + 0.2f,	0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnim*0.2f,          1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_nPatternAnim*0.2f + 0.2f,	1.0f);*/


	/*pVtx[0].tex = D3DXVECTOR2(g_nPatternAnim*0.2f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_nPatternAnim*0.2f + 0.2f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnim*0.2f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(g_nPatternAnim*0.2f + 0.2f, 0.5f);*/

	//[2段]
	/*pVtx[0].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5),			0.5f*(g_nPatternAnim / 5));
	pVtx[1].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5) + 0.2f,		0.5f*(g_nPatternAnim / 5));
	pVtx[2].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5),			0.5f*(g_nPatternAnim / 5)+0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5) + 0.2f,		0.5f*(g_nPatternAnim / 5) + 0.5f);*/

	//[4段]
	//pVtx[0].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5),		0.25f*(g_nPatternAnim / 5));
	//pVtx[1].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5) + 0.2f, 0.25f*(g_nPatternAnim / 5));
	//pVtx[2].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5),		0.25f*(g_nPatternAnim / 5) + 0.25f);
	//pVtx[3].tex = D3DXVECTOR2(0.2f*(g_nPatternAnim % 5) + 0.2f, 0.25f*(g_nPatternAnim / 5) + 0.25f);
#endif

	//頂点座標の設定 / 大きさ
	pVtx[0].pos = D3DXVECTOR3(-PLAYER_SIZE + g_player.pos.x, g_player.pos.y - PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PLAYER_SIZE + g_player.pos.x, g_player.pos.y - PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-PLAYER_SIZE + g_player.pos.x, g_player.pos.y + PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PLAYER_SIZE + g_player.pos.x, g_player.pos.y + PLAYER_SIZE, 0.0f);

	//頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();
}

//? ==================================================
//? 描画
//? ==================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを所得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_player.bDisp == true)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//? ==================================================
//? プレイヤーの通常、ダメージ時の表示処理
//? ==================================================
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;
	if (g_player.nLife <= 0)//体力が0以下
	{
		PlaySound(SOUND_EXPLOSION);
		SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_player.bDisp = false;
		g_player.state = PLAYERSTATE_DEATH;
		g_player.nCounterState = 60;
	}
	else//ダメージの表現
	{
		PlaySound(SOUND_EXPLOSION);
		g_player.state = PLAYERSTATE_DAMAGE;//ダメージ状態時
		g_player.nCounterState = 5;//ダメージ継続の時間
	
		VERTEX_2D *pVtx;

		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		g_pVtxBuffPlayer->Unlock();
	}
}

//? ==================================================
//? プレイヤーの通常、ダメージ時の表示処理
//? ==================================================
PLAYER *GetPlayer(void)
{
	return &g_player;
}