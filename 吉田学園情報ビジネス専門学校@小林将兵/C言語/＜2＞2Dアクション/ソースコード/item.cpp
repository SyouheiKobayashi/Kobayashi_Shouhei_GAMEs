//=============================================================================
// アイテム処理 [item.cpp]
// Author:Kobayashi/小林 将兵
//=============================================================================
#include "main.h"
#include "sound.h"
#include "game.h"
#include "input.h"
#include "player.h"
#include "item.h"
#include "explosion.h"
#include "score.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	ITEM_TYPE (3)//ブロックの種類
#define ITEM_SIZE (50)//アイテムのサイズ

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureItem[ITEM_TYPE] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	// 頂点バッファへのポインタ

Item g_Item[MAX_ITEM];//ブロック構造体

int g_nCntItem;
int g_NumItem;//アイテムの総数

//=============================================================================
// ブロックの初期化
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// アイテムの情報の初期化
	for (g_nCntItem = 0; g_nCntItem < MAX_ITEM; g_nCntItem++)
	{
		g_Item[g_nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[g_nCntItem].nItemType = 0;
		g_Item[g_nCntItem].bUse = false; //true=使用している / false=使用していない
		g_Item[g_nCntItem].bTouch = false;//触れていない

		//アニメーション初期
		g_Item[g_nCntItem].SpeedAnimation = 0;
		g_Item[g_nCntItem].PatternAnimation = 0;

		g_NumItem = 0;

		 // テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\coin000.png", &g_pTextureItem[0]);	//コインテクスチャ
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\coin000.png", &g_pTextureItem[1]);	//コインテクスチャ
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\菌B.png", &g_pTextureItem[2]);	//コインテクスチャ

		 // 頂点情報の作成
		VERTEX_2D *pVtx;


		// 頂点バッファを生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffItem,
			NULL);

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCB = 0; nCB < MAX_ITEM; nCB++)
		{

			//アイテムの位置
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

			pVtx += 4;//頂点データの情報を４つ分進める
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
	g_NumItem = 0;
}

//=============================================================================
// ブロックの終了
//=============================================================================
void UninitItem(void)
{
	int nCntText;

	for (nCntText = 0; nCntText < ITEM_TYPE; nCntText++)
	{
		// テクスチャの開放
		if (g_pTextureItem[nCntText] != NULL)
		{
			g_pTextureItem[nCntText]->Release();
			g_pTextureItem[nCntText] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// ブロックの更新
//=============================================================================
void UpdateItem(void)
{
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (g_nCntItem = 0; g_nCntItem < MAX_ITEM; g_nCntItem++)
	{
		if (g_Item[g_nCntItem].bUse == true)
		{
			g_Item[g_nCntItem].SpeedAnimation++; //カウンターの加算
			if ((g_Item[g_nCntItem].SpeedAnimation % 8) == 0)
			{
				g_Item[g_nCntItem].PatternAnimation = (g_Item[g_nCntItem].PatternAnimation + 1) % 4;//パターンNo.更新

				pVtx[0].tex = D3DXVECTOR2((g_Item[g_nCntItem].PatternAnimation*0.25f), 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_Item[g_nCntItem].PatternAnimation*0.25f) + 0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((g_Item[g_nCntItem].PatternAnimation*0.25f), 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_Item[g_nCntItem].PatternAnimation*0.25f) + 0.25f, 1.0f);
			}
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// ブロックの描画
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (g_nCntItem = 0; g_nCntItem < MAX_ITEM; g_nCntItem++)
	{
		if (g_Item[g_nCntItem].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItem[g_Item[g_nCntItem].nItemType]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, g_nCntItem * 4, 2);
		}
	}
}

//=============================================================================
// ブロックの設定
//=============================================================================
void SetItem(D3DXVECTOR3 pos, int nItemType)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (g_nCntItem = 0; g_nCntItem < MAX_ITEM; g_nCntItem++)
	{
		if (g_Item[g_nCntItem].bUse == false)	//ブロックを使用している
		{
			g_Item[g_nCntItem].pos = pos;
			g_Item[g_nCntItem].nItemType = nItemType;
			g_Item[g_nCntItem].bUse = true;

			//アイテムの位置
			pVtx[0].pos = D3DXVECTOR3(g_Item[g_nCntItem].pos.x, g_Item[g_nCntItem].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Item[g_nCntItem].pos.x + ITEM_SIZE, g_Item[g_nCntItem].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Item[g_nCntItem].pos.x, g_Item[g_nCntItem].pos.y + ITEM_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Item[g_nCntItem].pos.x + ITEM_SIZE, g_Item[g_nCntItem].pos.y + ITEM_SIZE, 0.0f);

			if (nItemType == 1)
			{
				//カラー
				pVtx[0].col = D3DCOLOR_RGBA(200, 0, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(200, 0, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(200, 0, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(200, 0, 0, 255);
			}
			if (nItemType == 2)
			{
				//カラー
				pVtx[0].col = D3DCOLOR_RGBA(200, 100, 50, 255);
				pVtx[1].col = D3DCOLOR_RGBA(200, 200, 50, 255);
				pVtx[2].col = D3DCOLOR_RGBA(200, 100, 50, 255);
				pVtx[3].col = D3DCOLOR_RGBA(200, 200, 50, 255);
			}

			if (nItemType == 0)
			{
				g_NumItem++;//アイテムの総数を加算

			}
			if (nItemType == 1)
			{
				g_NumItem++;//アイテムの総数を加算

			}
			break;
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
//						アイテムの当たり判定
//=============================================================================
bool CollisionItem(D3DXVECTOR3 *pPos,		//アイテムの現在の位置
	D3DXVECTOR3 *pPosOld,	//アイテムのひとつ前の位置
	D3DXVECTOR3 * pMove,	//アイテムの移動量
	float fWidth,
	float fHeight)
{
	int nCntTouch;

	for (nCntTouch = 0; nCntTouch < MAX_ITEM; nCntTouch++)
	{
		if (g_Item[nCntTouch].bUse == true)//アイテムががつかえる状態
		{	//あたり判定の範囲
			if (pPos->x <= g_Item[nCntTouch].pos.x + ITEM_SIZE && pPos->x >= g_Item[nCntTouch].pos.x&&
				pPos->y <= g_Item[nCntTouch].pos.y + ITEM_SIZE*2 && pPos->y >= g_Item[nCntTouch].pos.y)//*2あたり判定の拡大　
																										//プレイヤーのposが足元にあるため
			{
				
				if (g_Item[nCntTouch].nItemType == 2)
				{
					PlaySound(SOUND_LABEL_SE_HIT000);//アイテム入手時の音
				}
				else
				{
					PlaySound(SOUND_LABEL_SE_COIN);//アイテム入手時の音
				}

				if (g_Item[nCntTouch].nItemType == 2)
				{
					SetExplosion(g_Item[nCntTouch].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				AddScore(100);//アイテム入手時のポイント
				if (g_Item[nCntTouch].nItemType == 1)
				{
					AddScore(400);//+元ポイント
				}
				if (g_Item[nCntTouch].nItemType == 2)
				{
					AddScore(-600);
				}

				g_Item[nCntTouch].bUse = false;//アイテムを表示しない

				if (g_Item[nCntTouch].nItemType == 0)
				{
					g_NumItem--;//アイテムの総数を減らす
				}
				if (g_Item[nCntTouch].nItemType == 1)
				{
					g_NumItem--;//アイテムの総数を減らす
				}

				if (g_NumItem <= 0)
				{//アイテムをすべて所得したら
					SetGameState(GAMESTATE_CLEAR);
				}
			}
		}
	}
	return g_Item[nCntTouch].bTouch;
}

//=============================================================================
// アイテムの取得
//=============================================================================
Item *GetItem(void)
{
	return &g_Item[0];
}
