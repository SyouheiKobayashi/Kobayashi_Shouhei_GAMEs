//=========================================================================
// タイトル画面の処理 [title.cpp]
// Author:Kobayashi/小林 将兵
//=========================================================================
#include "main.h"	//メイン処理
#include "title.h"	//タイトル処理
#include "input.h"	//入力処理
#include "fade.h"	//フェード画面切り替え処理

//=========================================================================
//マクロ
//=========================================================================
#define T_TYPE (2)//背景の枚数
#define Title_TEXTURENAME "DATA\\TEXTURE\\背景P_.jpg"//読み込むテクスチャ
#define Title_TEXTURENAME2 "DATA\\TEXTURE\\タイトル文字.png"//読み込むテクスチャ

#define Title_POS_X (0)							//背景の左上X座標
#define Title_POS_Y (0)						    //背景の左上Y座標
#define Title_WIDTH (SCREEN_WIDTH)				//背景の幅
#define Title_HEIGHT (SCREEN_HEIGHT)			//背景の高さ

//=========================================================================
//グローバル
//=========================================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle[T_TYPE] = {};				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;			//頂点バッファへのポインタ

int g_ScrollAnim;
//=========================================================================
//タイトル / 初期化
//=========================================================================
void InitTitle(void)
{
	g_ScrollAnim = 0;

	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの所得
	
	//◆テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, Title_TEXTURENAME, &g_pTextureTitle[0]);//動く背景用
	D3DXCreateTextureFromFile(pDevice, Title_TEXTURENAME2, &g_pTextureTitle[1]);//タイトル文字

	//◆頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * T_TYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//◆頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntT = 0; nCntT < T_TYPE; nCntT++)
	{
		//◇頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(Title_POS_X, Title_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Title_POS_X + Title_WIDTH, Title_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(Title_POS_X, Title_POS_Y + Title_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Title_POS_X + Title_WIDTH, Title_POS_Y + Title_HEIGHT, 0.0f);

		//◇rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//◇頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//◇テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//--------------------
//タイトル文字
//--------------------
		//頂点座標の設定
		pVtx[4].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(Title_WIDTH, 0, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(0, Title_HEIGHT, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(Title_WIDTH, Title_HEIGHT, 0.0f);

		//rhwの設定
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//◆頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();
}

//=========================================================================
//タイトル / 終了
//=========================================================================
void UninitTitle(void)
{
	for (int nCnt = 0; nCnt < T_TYPE; nCnt++)
	{
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//=========================================================================
//タイトル / 更新
//=========================================================================
void UpdateTitle(void)
{
	g_ScrollAnim++;

	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.0005f * g_ScrollAnim), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + (0.0005f * g_ScrollAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (0.0005f * g_ScrollAnim), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + (0.0005f * g_ScrollAnim), 1.0f);

	if (pVtx[0].tex.x < 0.0f)
	{
		pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	if (pVtx[2].tex.x < 0.0f)
	{
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	}

	pVtx += 4;
	//頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();

	FADE pFade;
	pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//モードの設定
			SetFade(MODE_TUTORIAL);
		}
	}
}

//=========================================================================
//タイトル / 描画
//=========================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//◆デバイスを所得する
	pDevice = GetDevice();

	//◆頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//◆頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBG = 0; nCntBG < T_TYPE; nCntBG++)
	{
		//◆テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCntBG]);


		//◆ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG*4, 2);
	}
}
