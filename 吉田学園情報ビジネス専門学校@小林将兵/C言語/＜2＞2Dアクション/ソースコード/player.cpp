//==============================================================================
// 自機・操作キャラの処理[player.cpp]
// Author:Kobayashi/小林 将兵
//=============================================================================
#include "main.h"
#include "sound.h"
#include "game.h"
#include "input.h"
#include "player.h"
#include "block.h"
#include "item.h"
#include "fade.h"
#include "score.h"

//==============================================================================
// マクロ定義
//==============================================================================
#define PLAYER_SIZE (25)//自機の大きさ
#define PLAYER_SPEED (0.8f)//自機の速さ
#define PLAYER_MAX_JUMP (2)//最大ジャンプ回数
#define PLAYER_JUMP_POWER (14)//ジャンプの高さ / パワー
#define GRAVITY (1.0f)//重力

//==============================================================================
//グローバル変数
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;
//D3DXVECTOR3 g_player.pos.x; //ポリゴンの位置情報
//D3DXVECTOR3 g_movePlayer; //ポリゴンの移動量情報
int g_jumpPlayer;//複数回ジャンプ変数

int SpeedAnimation;//アニメーション速度
int PatternAnimation;//アニメーションのパターン数
int TextureAnimation;//左右反転表示するための変数
int JumpAnimation;//ジャンプ時のテクスチャ

Player g_player;
Player *GetPlayer(void)
{
	return &g_player;
}

//==============================================================================
// プレイヤーの初期化
//==============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの所得
	pDevice = GetDevice();

	// プレイヤーの情報の初期化
	g_player.pos = D3DXVECTOR3(50.0f, 630.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.state = PLAYERSTATE_NORMAL;//プレイヤー状態
	g_player.nCounterState = 0;//プレイヤーの状態管理
	g_jumpPlayer = 0;
	SpeedAnimation = 0;
	PatternAnimation = 0;
	TextureAnimation = 0;
	JumpAnimation = 0;
	g_player.bwait = true;//待機 / 動いているか否か
	g_player.bJump = false;//ジャンプ / 空中いるか否か
	g_player.bUse = true; //true=使用している / false=使用していない

	//[ポリゴンの位置情報]
	//g_player.pos.x = D3DXVECTOR3(290, 300, 0.0f); //初期位置
	//g_movePlayer = D3DXVECTOR3(0, 0, 0.0f);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\player000.png", &g_pTexturePlayer);

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

//位置　画像　rhw　色の設定
#if 1
	//位置
	/*pVtx[0].pos = D3DXVECTOR3(g_player.pos.x.x- PLAYER_SIZE, g_player.pos.x.y - PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x.x+ PLAYER_SIZE, g_player.pos.x.y - PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x.x- PLAYER_SIZE, g_player.pos.x.y + PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x.x+ PLAYER_SIZE, g_player.pos.x.y + PLAYER_SIZE, 0.0f);*/

	//めり込んだ時のブロックの基準となる / ブロックに対する判定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE, g_player.pos.y - PLAYER_SIZE*2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE, g_player.pos.y - PLAYER_SIZE*2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x+ PLAYER_SIZE, g_player.pos.y, 0.0f);

	//画像
	//ユルエ
	/*pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);*/
	//配布キャラ
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//色
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
#endif

	//頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();
}

//==============================================================================
// プレイヤーの終了
//==============================================================================
void UninitPlayer(void)
{
	//テクスチャの破棄
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

//==============================================================================
// プレイヤーの更新
//==============================================================================
void UpdatePlayer(void)
{
	if (g_player.pos.y > SCREEN_HEIGHT + 50)//自機がもし画面したに落ちた場合
	{
		GAMESTATE pGameState; //game.cppにある「ゲーム状態の取得」を入れるためにpGameState(変数)を用意する
		pGameState = GetGameState(); //pGameState(変数)にgame.cppの「ゲーム状態の取得」にあるg_gameStateを代入する

		if (pGameState != GAMESTATE_END && pGameState == GAMESTATE_NORMAL)//GAMESTATEがNORMALのとき
		{
			SetGameState(GAMESTATE_END);
		}
		g_player.bUse = false;//使えなくする
		g_player.state = PLAYERSTATE_DEATH;//死亡状態
	}

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL://通常時の処理
		break;

	case PLAYERSTATE_DEATH:
		break;
		
	}

	g_player.posOld = g_player.pos;//現在の自機位置情報をposOldに保存しとく

	VERTEX_2D*pVtx;//頂点情報へのポインタ

   //頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	SpeedAnimation++;
	if ((SpeedAnimation % 8) == 0)
	{
		PatternAnimation = (PatternAnimation + 1) % 4;//パターンNo.更新
	}
//-------------------
// 自機の操作設定
//-------------------
	//★任意のキー(Dキー)が押されたかどうか / 自機の右移動の処理★
	if (GetKeyboardPress(DIK_D) == true)
	{
		TextureAnimation = 0;//0にする
		g_player.bwait = false;//待機していない状態にする
			g_player.move.x += PLAYER_SPEED;

			if (g_player.pos.x > SCREEN_WIDTH)//スクリーン外に出た場合の処理
			{
				g_player.pos.x = 0;
			}

			//頂点バッファをロックし、頂点データへのポインタを所得
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			//画像
			//ユルエ
			/*pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);*/
			//配布キャラ
			/*pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);*/
			//配布キャラアニメーション
			pVtx[0].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 0.5f);
			pVtx[3].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 0.5f);
			//頂点バッファをアンロック
			g_pVtxBuffPlayer->Unlock();
	}

	//★任意のキー(Aキー)が押されたかどうか / 自機の左移動の処理★
	if (GetKeyboardPress(DIK_A) == true)
	{
		TextureAnimation = 1;//1にする
		g_player.bwait = false;//待機していない状態にする
		g_player.move.x -= PLAYER_SPEED;

		if (g_player.pos.x < 0)//スクリーン外に出た場合の処理
		{
			g_player.pos.x = SCREEN_WIDTH;
		}

		//if (g_player.pos.x < 25)//スクリーン外に出た場合の処理
		//{
		//	g_player.pos.x = 25;
		//}

		//頂点バッファをロックし、頂点データへのポインタを所得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		//画像
		//ユルエ
		/*pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);*/
		//配布キャラ
		/*pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);*/
		//配布キャラアニメーション(強制反転Dキーの0と1、2と3を逆にする)
		/*pVtx[0].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 0.5f);*/

		//頂点バッファをアンロック
		g_pVtxBuffPlayer->Unlock();
		
	}

	//★任意のキー(SPACEキー)が押されたかどうか / 自機のジャンプの処理★
	if (g_player.bJump == false)
	{
		if (GetKeyboardTrigger(DIK_SPACE) == true)//スペースを押して&&ジャンプは最大PLAYER_MAX_JUMP回まで
		{
			PlaySound(SOUND_LABEL_SE_JUMP);//ジャンプ音
			g_jumpPlayer++;
			g_player.move.y -= PLAYER_JUMP_POWER;//自機の飛ぶ力
			g_player.bJump = true;
		}
	}
	g_player.move.y += GRAVITY;//重力加算

		g_player.pos.x += g_player.move.x;//横移動
		g_player.pos.y += g_player.move.y;//落下

		
//---------------------------------------------------------------------
	//位置更新(移動)
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//慣性
	g_player.move.x += (0.0f - g_player.move.x)*0.2f;
	//g_movePlayer.y += (0.0f - g_movePlayer.y)*0.2f;

	/*g_player.pos = g_player.pos.x;
	g_player.move = g_movePlayer;*/

	if (CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, 0, 0) == true)
	{
		g_player.bJump = false;//ジャンプしていない
	}
	else
	{
		g_player.bJump = true;//ジャンプしている
	}

//-------------------------------------------------------------------
//						コイン加点処理
//-------------------------------------------------------------------
	if (CollisionItem(&g_player.pos, &g_player.posOld, &g_player.move, 0, 0) == true)
	{
		g_player.bTouch = false;//触れていない
	}
	else
	{
		g_player.bTouch = true;//触れている
	}

	//床の高さ // Sキー押した場合それ以上、下に行かせないため
	/*if (g_player.pos.y >= 650)
	{
		g_player.pos.y = 650;
		g_player.move.y = 0.0f;
		g_jumpPlayer = 0;
		g_player.bJump = false;
	}*/

	////配布キャラアニメーション
	//移動キーを押していないときの処理 / 待機処理
	if (GetKeyboardPress(DIK_D) == false&& GetKeyboardPress(DIK_A) == false)
	{
		g_player.bwait = true;
		if (TextureAnimation == 0 && g_player.bwait == true)//右
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);
		}
		if (TextureAnimation == 1 && g_player.bwait == true)//左
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.25f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);
		}

	}
	//右向きの時のテクスチャアニメーション表示の処理
	if (TextureAnimation == 0&& g_player.bwait == false)//右
	{
		pVtx[0].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 0.5f);
	}
	//左向きの時のテクスチャアニメーション表示の処理
	if (TextureAnimation == 1&& g_player.bwait == false)//左
	{
		pVtx[0].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 0.5f);
		pVtx[1].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.25f*(PatternAnimation), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f*(PatternAnimation)+0.25f, 1.0f);
	}

	//頂点座標の設定 / 自機の大きさ
	/*pVtx[0].pos = D3DXVECTOR3(g_player.pos.x.x - PLAYER_SIZE, g_player.pos.x.y - PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x.x + PLAYER_SIZE, g_player.pos.x.y - PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x.x - PLAYER_SIZE, g_player.pos.x.y + PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x.x + PLAYER_SIZE, g_player.pos.x.y + PLAYER_SIZE, 0.0f);*/

	//めり込んだ時のブロックの基準となる / ブロックに対する判定(更新版)
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE, g_player.pos.y - PLAYER_SIZE * 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE, g_player.pos.y - PLAYER_SIZE * 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE, g_player.pos.y, 0.0f);

	//頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();
}

//==============================================================================
// プレイヤーの描画
//==============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを所得する
	pDevice = GetDevice();
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	if (g_player.bUse == true)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
