//=============================================================================
// 床・壁、障害物等の処理 [block.cpp]
// Author:Kobayashi/小林 将兵
//=============================================================================
#include "main.h"
#include "sound.h"
#include "game.h"
#include "input.h"
#include "block.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SIZE (50)//自機の大きさ
#define	BLOCK_TYPE (7)//ブロックの種類
#define UPYUKA_SPEED (-2.0f)//↑スピード
#define HIDARI_SPEED (-2.0f)//←スピード

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureBlock[BLOCK_TYPE] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	// 頂点バッファへのポインタ

Block g_Block[MAX_BLOCK];//ブロック構造体

int g_nCntBlock;

//=============================================================================
// ブロックの初期化
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// ブロックの情報の初期化
	for (g_nCntBlock = 0; g_nCntBlock < MAX_BLOCK; g_nCntBlock++)
	{
		g_Block[g_nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[g_nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[g_nCntBlock].fWidth = 0.0f;
		g_Block[g_nCntBlock].fHeight = 0.0f;
		g_Block[g_nCntBlock].nBlockType = 0;
		g_Block[g_nCntBlock].bUse = false; //true=使用している / false=使用していない
		g_Block[g_nCntBlock].Determine = false;//着地していない


	// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\黒床.jpg", &g_pTextureBlock[0]);//床用ブロック
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\Block03横.jpg", &g_pTextureBlock[1]);//床用ブロック
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\Block03縦太.jpg", &g_pTextureBlock[2]);//床用ブロック
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\黒床.jpg", &g_pTextureBlock[3]);//床用ブロック
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\黒床.jpg", &g_pTextureBlock[4]);//上下壁
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\黒床.jpg", &g_pTextureBlock[5]);//沈むブロック
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\黒床.jpg", &g_pTextureBlock[6]);//左右移動ブロック

		// 頂点情報の作成
		VERTEX_2D *pVtx;

		// 頂点バッファを生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffBlock,
			NULL);

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

		for (g_nCntBlock = 0; g_nCntBlock < MAX_BLOCK; g_nCntBlock++)
		{

			//ブロックの位置
			pVtx[0].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x, g_Block[g_nCntBlock].pos.y, 0.0f);

			pVtx[1].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth, g_Block[g_nCntBlock].pos.y, 0.0f);

			pVtx[2].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x, g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight, 0.0f);

			pVtx[3].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth, g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight, 0.0f);

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//テクスチャ
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;//頂点データの情報を４つ分進める
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// ブロックの終了
//=============================================================================
void UninitBlock(void)
{
	for (g_nCntBlock = 0; g_nCntBlock < BLOCK_TYPE; g_nCntBlock++)
	{
		// テクスチャの開放
		if (g_pTextureBlock[g_nCntBlock] != NULL)
		{
			g_pTextureBlock[g_nCntBlock]->Release();
			g_pTextureBlock[g_nCntBlock] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//=============================================================================
// ブロックの更新
//=============================================================================
void UpdateBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();
																						   
	// 頂点情報の作成
	VERTEX_2D *pVtx;


	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
   	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (g_nCntBlock = 0; g_nCntBlock < MAX_BLOCK; g_nCntBlock++)
	{
		g_Block[g_nCntBlock].bUse = true;
		if (g_Block[g_nCntBlock].bUse == true)
		{
			g_Block[g_nCntBlock].pos += g_Block[g_nCntBlock].move;//ブロックの移動

			if (g_Block[g_nCntBlock].pos.y < -50)//スクリーン外に出た場合の処理
			{
				g_Block[g_nCntBlock].pos.y = SCREEN_HEIGHT;
			}
			//if (g_Block[g_nCntBlock].pos.y > SCREEN_HEIGHT)//スクリーン外に出た場合の処理
			//{
			//	g_Block[g_nCntBlock].pos.y = 0;
			//}
			if (g_Block[g_nCntBlock].pos.x < -150)//スクリーン外に出た場合の処理
			{
				g_Block[g_nCntBlock].pos.x = SCREEN_WIDTH;
			}
			if (g_Block[g_nCntBlock].nBlockType == 3)//ブロックの上下運動
			{
				if (488 == g_Block[g_nCntBlock].pos.y)//止める
				{
					g_Block[g_nCntBlock].move.y = 0.0f;
				}
				if (500 < g_Block[g_nCntBlock].pos.y)//上昇
				{
					g_Block[g_nCntBlock].move.y = UPYUKA_SPEED;
				}
			}
			if (g_Block[g_nCntBlock].nBlockType == 4)//ブロックの上下運動
			{
				if (170 > g_Block[g_nCntBlock].pos.y)//下降
				{
					g_Block[g_nCntBlock].move.y = 2.0f;
				}
				if (340 < g_Block[g_nCntBlock].pos.y)//上昇
				{
					g_Block[g_nCntBlock].move.y = UPYUKA_SPEED - 1.0f;
				}
			}
			if (g_Block[g_nCntBlock].nBlockType == 5)//ブロックの上下運動
			{
				if (670 == g_Block[g_nCntBlock].pos.y)//止める
				{
					g_Block[g_nCntBlock].move.y = 0.0f;
				}
				if (800 < g_Block[g_nCntBlock].pos.y)//上昇
				{
					g_Block[g_nCntBlock].move.y = UPYUKA_SPEED;
				}
			}

			if (g_Block[g_nCntBlock].nBlockType == 6)//ブロックの左右運動
			{
				if (850 > g_Block[g_nCntBlock].pos.x)//左
				{
					g_Block[g_nCntBlock].move.x = -HIDARI_SPEED;
				}
				if (950 < g_Block[g_nCntBlock].pos.x)//右
				{
					g_Block[g_nCntBlock].move.x = HIDARI_SPEED;
				}
			}

			//ブロックの位置
			pVtx[0].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x, g_Block[g_nCntBlock].pos.y, 0.0f);

			pVtx[1].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth, g_Block[g_nCntBlock].pos.y, 0.0f);

			pVtx[2].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x, g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight, 0.0f);

			pVtx[3].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth, g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight, 0.0f);

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//テクスチャ
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		}
		pVtx += 4;//頂点データの情報を４つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// ブロックの描画
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(int g_nCntBlock = 0; g_nCntBlock < MAX_BLOCK; g_nCntBlock++)
	{
		if (g_Block[g_nCntBlock].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBlock[g_Block[g_nCntBlock].nBlockType]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, g_nCntBlock*4, 2);
		}
	}
}

//=============================================================================
// ブロックの設定
//=============================================================================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, int nBlockType)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (g_nCntBlock = 0; g_nCntBlock < MAX_BLOCK; g_nCntBlock++)
	{
		if (g_Block[g_nCntBlock].bUse == false)	//ブロックを使用している
		{
			g_Block[g_nCntBlock].pos = pos;
			g_Block[g_nCntBlock].move = move;
			g_Block[g_nCntBlock].fWidth = fWidth;
			g_Block[g_nCntBlock].fHeight = fHeight;
			g_Block[g_nCntBlock].nBlockType = nBlockType;
			g_Block[g_nCntBlock].bUse = true;

			//ブロックの位置
			pVtx[0].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x, g_Block[g_nCntBlock].pos.y, 0.0f);

			pVtx[1].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth, g_Block[g_nCntBlock].pos.y, 0.0f);

			pVtx[2].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x, g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight, 0.0f);

			pVtx[3].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth, g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight, 0.0f);

			break;
		}
		pVtx += 4;
		
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// ブロックの衝突判定
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos,		//自機の現在の位置
					D3DXVECTOR3 *pPosOld,	//自機のひとつ前の位置
					D3DXVECTOR3 * pMove,	//自機の移動量
					float fWidth,
					float fHeight)	
{
	bool bLand = false; //着地していない

	/*if (g_Block[g_nCntBlock].nBlockType == 0)//もしタイプ０なら…すり抜け可能など
	{
	}*/

	for (g_nCntBlock = 0; g_nCntBlock < MAX_BLOCK; g_nCntBlock++)
	{
		if (g_Block[g_nCntBlock].bUse == true)//ブロックが使われている
		{
			g_Block[g_nCntBlock].Determine = false;//１つ一つのブロックの判定を元に戻す / 初期化する
			//ブロック / 地面判定処理 / 上と下
			if (pPos->x <= g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth && pPos->x >= g_Block[g_nCntBlock].pos.x)
			{
				//★上からの衝突判定
				if (pPosOld->y <= g_Block[g_nCntBlock].pos.y&&pPos->y >= g_Block[g_nCntBlock].pos.y)
				{	
					//*pPos->y += g_Block[g_nCntBlock].pos.y;
					
					g_Block[g_nCntBlock].Determine = true;
					bLand = true;//地面 / ブロックにめり込んだら
					pPos->y = g_Block[g_nCntBlock].pos.y; //立たせたい地面の上
					pMove->y = 0.0f;// 落下速度をなくす / マイナス数値にすると自動ジャンプ的な何か

					//床縦移動用
					if (g_Block[g_nCntBlock].nBlockType == 4&& g_Block[g_nCntBlock].move.y == UPYUKA_SPEED - 1.0f)//上昇時に適応
					{
						pPos->y = g_Block[g_nCntBlock].pos.y+ UPYUKA_SPEED - 1.0f;//立たせたい地面の上
					}

					if (g_Block[g_nCntBlock].nBlockType == 5 && g_Block[g_nCntBlock].move.y == UPYUKA_SPEED)//上昇時に適応
					{
						pPos->y = g_Block[g_nCntBlock].pos.y + UPYUKA_SPEED;//立たせたい地面の上
					}
					//if (g_Block[g_nCntBlock].nBlockType == 5 && g_Block[g_nCntBlock].move.y == 3.0f)//上昇時に適応
					//{
					//	pPos->y = g_Block[g_nCntBlock].pos.y +13.0f;//立たせたい地面の上
					//}
					//if (g_Block[g_nCntBlock].move.y = 0.7f)
					//{
					//	pPos->y = g_Block[g_nCntBlock].pos.y - 0.7f;//!!自機がブロックに乗ると重さで下がる
					//}
					//自機がブロックの上に乗ったらブロックが下がる
					if (g_Block[g_nCntBlock].nBlockType == 3)//ブロックの上下運動
					{
						g_Block[g_nCntBlock].move.y = 2.0f;
						pPos->y = g_Block[g_nCntBlock].pos.y;//!!自機がブロックに乗ると落ちる
					}
					if (g_Block[g_nCntBlock].nBlockType == 5)//ブロックの上下運動
					{
						g_Block[g_nCntBlock].move.y = 2.0f;
						pPos->y = g_Block[g_nCntBlock].pos.y;//!!自機がブロックに乗ると落ちる
					}
					
					//床横移動用
					if (g_Block[g_nCntBlock].nBlockType == 6)
					{
						pPos->x += g_Block[g_nCntBlock].move.x;//障害物が移動した分自機に代入
					}

				 //★任意のキー(Sキー)が押されたかどうか / 自機の下移動？の処理★
					//if (GetKeyboardPress(DIK_S) == true)
					//{
					//	//g_Block[g_nCntBlock].bUse = false;//下ドリル方式
					//	pPos->y = g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight * 2 + 10; //立たせたい地面の下
					//}
				}

				//★下からの衝突判定
				else if (pPosOld->y - PLAYER_SIZE >= g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight
					&& pPos->y - PLAYER_SIZE <= g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight)
				{
					g_Block[g_nCntBlock].Determine = true;
					//bLand = true;//地面 / ブロックにめり込んだら
					//ブロックの高さ*2+微調整数値
					pPos->y= g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight*3; //立たせたい地面の下
					pMove->y = 0.0f; // 落下速度をなくす
				}

				//ブロック / 横判定処理
				if (pPos->y <= g_Block[g_nCntBlock].pos.y+ PLAYER_SIZE * 1.5f + g_Block[g_nCntBlock].fHeight && pPos->y >= g_Block[g_nCntBlock].pos.y)
				{
					if (g_Block[g_nCntBlock].Determine == false)//ブロックに乗ってたら横判定
					{
							//★左からの衝突判定
							if (pPosOld->x <= g_Block[g_nCntBlock].pos.x && pPos->x >= g_Block[g_nCntBlock].pos.x)
							{
								bLand = true;//地面 / ブロックにめり込んだら
								pPos->x = pPosOld->x; //障害物にめり込んだ場合の処理
								pMove->x = -1.0f; // 速度をなくす
							}

							if (g_Block[g_nCntBlock].nBlockType == 6)//移動時の当たり判定
							{//移動するブロック分、過去の自機の居場所(復活場所)を足しておく
								if (pPosOld->x + HIDARI_SPEED <= g_Block[g_nCntBlock].pos.x && pPos->x >= g_Block[g_nCntBlock].pos.x)
								{
									bLand = true;//地面 / ブロックにめり込んだら
									pPos->x = pPosOld->x; //障害物にめり込んだ場合の処理
									pMove->x = -1.0f; // 速度をなくす
								}
							}

							//★右からの衝突判定 / 自機の大きさ２倍分	
							else if (pPosOld->x >= g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth && pPos->x <= g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth)
							{
								bLand = true;//地面 / ブロックにめり込んだら
								pPos->x = pPosOld->x; //障害物にめり込んだ場合の処理
								pMove->x = 1.0f; // 速度をなくす
							}
					}
				}

				//★ブロック / 横判定の処理
#if 0
				if (bLand == false)//着地していない / 空中にいる
				{
					if (pPos->y >= g_Block[g_nCntBlock].pos.y && pPos->y - PLAYER_SIZE * 2 <= g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight)
					{
						bLand = true;//地面 / ブロックにめり込んだら / 使うとロックマン仕様
						pPos->x = pPosOld->x; //障害物にめり込んだ場合の処理
						pMove->x = 0.0f; // 速度をなくす
					}
				}
#endif
			}
		}
	}
	return bLand;
}

//=============================================================================
// ブロックの取得
//=============================================================================
Block *GetBlock(void)
{
	return &g_Block[0];
}
