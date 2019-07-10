//=========================================================================
// ゲーム処理 [game.cpp]
// Author:Kobayashi/小林 将兵
//=========================================================================
#include "main.h"
#include "sound.h"
#include "fade.h"
#include "game.h"
#include "stage.h"//ステージ（フィールド）
#include "layout.h"
#include "timer.h"
#include "score.h"
#include "camera.h"
#include "light.h"
#include "polygon.h"
#include "meshField.h"
#include "wall.h"
#include "meshWall.h"
#include "shadow.h"
#include "player.h"
#include "dummymodel.h"
#include "collisionModel.h"
#include "fallingRocks.h"
#include "item.h"
#include "badItem.h"
#include "billboard.h"
#include "bullet.h"
#include "effect.h"
#include "explosion.h"

//=============================================================================
//マクロ定義
//=============================================================================

//=========================================================================
//ゲーム / グローバル変数
//=========================================================================
GAMESTATE g_gameState = GAMESTATE_NONE;	//ゲームの状態
int g_nCounterGameState;				//状態管理カウンター

//=========================================================================
//ゲーム / 初期化
//=========================================================================
void InitGame(void)
{
	int nCnt;

	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	// ステージの初期化処理
	InitStage();


	// スコアの初期化処理
	InitScore();

	// ポリゴンの初期化処理
	InitPolygon();

	//メッシュフィールドの初期化処理
	InitMeshField();

	// 壁の初期化処理
	InitWall();

	//メッシュ壁の初期化処理
	InitMeshWall();

	// 影の初期化処理
	InitShadow();

	// モデルの初期化処理
	InitPlayer();

	// ダミーの初期化処理
	InitDummyModel();

	// 衝突用モデルの初期化処理
	InitCollisionModle();

	//落石の初期化処理
	InitFallingRocks();

	// アイテムの初期化処理
	InitItem();

	// 減点アイテムの初期化処理
	InitBadItem();

	// ビルボードの初期化処理
	InitBillboard();

	// 弾の初期化処理
	InitBullet();

	// エフェクトの初期化処理
	InitEffect();

	//紅魔式初期化処理
	InitExplosion();

	// 制限時間の初期化処理
	InitTimer();

	//レイアウトの初期化
	InitLayout();

	PlaySound(SOUND_LABEL_GAME);

	//+ 壁の配置
	//SetWall(D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0));
	//SetWall(D3DXVECTOR3(0, 0, -100), D3DXVECTOR3(0, D3DX_PI, 0));
	//SetWall(D3DXVECTOR3(100, 0, 0), D3DXVECTOR3(0, D3DX_PI/2, 0));
	//SetWall(D3DXVECTOR3(-100, 0, 0), D3DXVECTOR3(0, -D3DX_PI/2, 0));

	SetMeshWall(D3DXVECTOR3(0, 0, 100), D3DXVECTOR3(0, 0, 0));
	SetMeshWall(D3DXVECTOR3(500, 0, -600), D3DXVECTOR3(0, D3DX_PI, 0));
	SetMeshWall(D3DXVECTOR3(600, 0, 0), D3DXVECTOR3(0, D3DX_PI / 2, 0));
	SetMeshWall(D3DXVECTOR3(-100, 0, -500), D3DXVECTOR3(0, -D3DX_PI / 2, 0));

//◆ビルボード配置
	SetBillboard(D3DXVECTOR3(0, 10, 0), D3DXVECTOR3(0, 0, 0), 0);
	SetBillboard(D3DXVECTOR3(-2000, 0, 420), D3DXVECTOR3(0, -D3DX_PI / 2, 0), 2);//左側矢印
	SetBillboard(D3DXVECTOR3(1000, 0, 420), D3DXVECTOR3(0, -D3DX_PI / 2, 0), 2);//左側矢印

// ◆アイテム配置	
	for (nCnt = 0; nCnt < 5; nCnt++)
	{ 
		SetItem(D3DXVECTOR3(-400.0f + (nCnt * 170), 15.0f, -2100 + (nCnt * 700)), D3DXVECTOR3(0.4f,0.0f,0.0f));
	}

// ◆<デメリット>アイテム配置	
	for (nCnt = 0; nCnt < 5; nCnt++)
	{
		SetBadItem(D3DXVECTOR3(-450.0f + (nCnt * 170), 15.0f, -2300 + (nCnt * 700)), D3DXVECTOR3(3.0f, 0.0f, 0.0f));
	}

// ◆落石配置	
	SetFallingRocks(D3DXVECTOR3(-300.0f, 800.0f, -2000), D3DXVECTOR3(10.0f, 0.0f, 0.0f),0);
	SetFallingRocks(D3DXVECTOR3(-200.0f, 800.0f, -1200), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 1);
	SetFallingRocks(D3DXVECTOR3(-100.0f, 800.0f, -400), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 2);
	SetFallingRocks(D3DXVECTOR3(0.0f, 800.0f, 400), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 3);
	SetFallingRocks(D3DXVECTOR3(100.0f, 800.0f, 1200), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 4);
	SetFallingRocks(D3DXVECTOR3(200.0f, 800.0f, 2000), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 5);
	SetFallingRocks(D3DXVECTOR3(300.0f, 800.0f, 2200), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 6);

// ◆クリア地点目安線	
	for (nCnt = 0; nCnt < 39; nCnt++)
	{
		SetEffect(D3DXVECTOR3(-430.0f+(nCnt*25), 20.0f, 2800.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5.0f, 1.0f);
	}

	g_gameState = GAMESTATE_NORMAL;	//通常状態に設定
	g_nCounterGameState = 0;
}
//=========================================================================
//ゲーム / 終了
//=========================================================================
void UninitGame(void)
{
	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	// ステージの終了処理
	UninitStage();

	

	// スコアの終了処理
	UninitScore();

	// ポリゴンの終了処理
	UninitPolygon();

	//メッシュフィールドの終了処理
	UninitMeshField();

	// 壁の終了処理
	UninitWall();

	//メッシュ壁の終了処理
	UninitMeshWall();

	// 影の終了処理
	UninitShadow();

	// モデルの終了処理
	UninitPlayer();

	// ダミーの終了処理
	UninitDummyModel();

	// 衝突用モデルの終了処理
	UninitCollisionModle();

	//落石の終了処理
	UninitFallingRocks();

	// アイテムの終了処理
	UninitItem();

	// 減点アイテムの終了処理
	UninitBadItem();

	// ビルボードの終了処理
	UninitBillboard();

	// 弾の終了処理
	UninitBullet();

	// エフェクトの終了処理
	UninitEffect();

	//紅魔式終了処理
	UninitExplosion();

	// 制限時間の終了処理
	UninitTimer();

	//レイアウトの終了処理
	InitLayout();

	StopSound();
}
//=========================================================================
//ゲーム / 更新
//=========================================================================
void UpdateGame(void)
{
	// ライトの更新処理
	UpdateLight();

	// ステージの更新処理
	UpdateStage();

	
	// スコアの更新処理
	UpdateScore();

	// ポリゴンの更新処理
	UpdatePolygon();

	//メッシュフィールドの更新処理
	UpdateMeshField();

	// 壁の更新処理
	UpdateWall();

	//メッシュ壁の更新処理
	UpdateMeshWall();

	// 影の更新処理
	UpdateShadow();

	// モデルの更新処理
	UpdatePlayer();

	// カメラの更新処理
	UpdateCamera();

	// ダミーの更新処理
	UpdateDummyModel();

	// 衝突用モデルの更新処理
	UpdateCollisionModle();

	//落石の更新処理
	UpdateFallingRocks();

	// アイテムの更新処理
	UpdateItem();

	// 減点アイテムの更新処理
	UpdateBadItem();

	// ビルボードの更新処理
	UpdateBillboard();

	// 弾の更新処理
	UpdateBullet();

	// エフェクトの更新処理
	UpdateEffect();

	//紅魔式更新処理
	UpdateExplosion();

	// 制限時間の更新処理
	UpdateTimer();

	//レイアウトの更新処理
	UpdateLayout();

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;

	case GAMESTATE_CLEAR:
		g_nCounterGameState++;

		if (g_nCounterGameState >= 50)//画面切り替えの余韻 / 時間
		{
			g_gameState = GAMESTATE_NONE;
			SetFade(MODE_CLEAR);
		}
		break;

		case GAMESTATE_END:
			g_nCounterGameState++;

			if (g_nCounterGameState >= 50)//画面切り替えの余韻 / 時間
			{
				g_gameState = GAMESTATE_NONE;
				SetFade(MODE_RESULT);
			}
			break;
	}
}

//=========================================================================
//ゲーム / 描画
//=========================================================================
void DrawGame(void)
{
	// カメラの設定
	SetCamera();

	// ステージの描画処理
	DrawStage();

	

	// スコアの描画処理
	//DrawScore();

	//メッシュフィールドの描画処理
	//DrawMeshField();

	// ポリゴンの描画処理
	//DrawPolygon();

	// 壁の描画処理
	DrawWall();

	// 影の描画処理
	DrawShadow();

	//メッシュ壁の描画処理
	//DrawMeshWall();

	// モデルの描画処理
	DrawPlayer();

	// ダミーの描画処理
	//DrawDummyModel();

	// 衝突用モデルの描画処理
	//DrawCollisionModle();

	//落石の描画処理
	DrawFallingRocks();

	// アイテムの描画処理
	DrawItem();

	// 減点アイテムの描画処理
	DrawBadItem();

	//ビルボードの描画処理
	DrawBillboard();

	// 弾の描画処理
	DrawBullet();

	// エフェクトの初期化処理
	DrawEffect();

	//紅魔式描画処理
	DrawExplosion();

	//レイアウトの描画処理
	DrawLayout();

	// 制限時間の描画処理
	DrawTimer();
}
//=========================================================================
//ゲーム状態の設定
//=========================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//=========================================================================
//ゲーム状態の取得
//=========================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}