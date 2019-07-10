//=============================================================================
// 背景処理[bg.cpp]
// Author:Kobayashi/小林 将兵
//=============================================================================
#include "main.h"
#include "bg.h"

//=============================================================================
//マクロ
//=============================================================================
#define BG_TYPE (4)//背景の枚数
#define BG_TEXTURENAME "DATA\\TEXTURE\\背景P__.jpg" //大きな背景
#define BG_TEXTURENAME2 "DATA\\TEXTURE\\背景Z.png" //雲
#define BG_TEXTURENAME3 "DATA\\TEXTURE\\歯車B_.png" //歯車
#define BG_TEXTURENAME4 "DATA\\TEXTURE\\歯車B_.png" //歯車


#define BG_POS_X (0)						 //背景の左上X座標
#define BG_POS_Y (0)						 //背景の左上Y座標
#define BG_WIDTH (SCREEN_WIDTH)				 //背景の幅
#define BG_HEIGHT (SCREEN_HEIGHT)			 //背景の高さ
#define H_SIZE (200)


//=============================================================================
//グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBG[BG_TYPE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;

int g_nCountAnimBG; //アニメーションカウンター

int SpeedAnimationBG;//アニメーション速度
int PatternAnimationBG;//アニメーションのパターン数

//D3DXVECTOR2 g_BG[1];//
//=============================================================================
//背景の初期化処理
//=============================================================================
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

 //[アニメーション]
	g_nCountAnimBG = 0;

	SpeedAnimationBG=0;
	PatternAnimationBG=0;
	
	//デバイスの所得
	pDevice = GetDevice();

	/*for (int nCount = 0; nCount < BG_TYPE; nCount++)
	{
		g_BG[nCount] = D3DXVECTOR2(0.0f, 0.0f);
	}*/

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME, &g_pTextureBG[0]);//背景
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME2, &g_pTextureBG[1]);//雲
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME3, &g_pTextureBG[2]);//
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME3, &g_pTextureBG[3]);//歯車

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * BG_TYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBG = 0; nCntBG < BG_TYPE; nCntBG++)
	{
		//大きな背景テクスチャ
#if 1
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BG_POS_X + BG_WIDTH, BG_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y + BG_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BG_POS_X + BG_WIDTH, BG_POS_Y + BG_HEIGHT, 0.0f);

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

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
#endif
		//雲テクスチャ
#if 1
		//頂点座標の設定
		pVtx[4].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(BG_POS_X + BG_WIDTH, BG_POS_Y, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y + BG_HEIGHT, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(BG_POS_X + BG_WIDTH, BG_POS_Y + BG_HEIGHT, 0.0f);

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
#endif

#if 1
		//頂点座標の設定
		pVtx[8].pos = D3DXVECTOR3(H_SIZE, 0, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(H_SIZE *2, 0, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(H_SIZE, H_SIZE, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(H_SIZE *2, H_SIZE, 0.0f);

		//rhwの設定
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[8].col = D3DCOLOR_RGBA(255, 2055, 255, 0);
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 0);

		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(0.125f, 1.0f);
#endif

#if 1
		//頂点座標の設定
		pVtx[12].pos = D3DXVECTOR3(H_SIZE, 0, 0.0f);
		pVtx[13].pos = D3DXVECTOR3(H_SIZE * 2, 0, 0.0f);
		pVtx[14].pos = D3DXVECTOR3(H_SIZE, H_SIZE, 0.0f);
		pVtx[15].pos = D3DXVECTOR3(H_SIZE * 2, H_SIZE, 0.0f);

		//rhwの設定
		pVtx[12].rhw = 1.0f;
		pVtx[13].rhw = 1.0f;
		pVtx[14].rhw = 1.0f;
		pVtx[15].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[12].col = D3DCOLOR_RGBA(255, 2055, 255, 0);
		pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 0);

		pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[13].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[15].tex = D3DXVECTOR2(0.125f, 1.0f);
#endif
	}

	//頂点バッファをアンロック
	g_pVtxBuffBG->Unlock();
}

//=============================================================================
//背景の終了処理
//=============================================================================
void UninitBG(void)
{
	for (int nCnt = 0; nCnt < BG_TYPE; nCnt++)
	{
		if (g_pTextureBG[nCnt] != NULL)
		{
			g_pTextureBG[nCnt]->Release();
			g_pTextureBG[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//=============================================================================
//背景の更新処理
//=============================================================================
void UpdateBG(void)
{
#if 1
	g_nCountAnimBG++; //カウンターの加算
	
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	g_nCountAnimBG++; //カウンターの加算

	//テクスチャ座標の設定
	//縦スクロール↓
#if 0
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f - (0.001f * g_nCountAnimBG));
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f - (0.001f * g_nCountAnimBG));
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f - (0.001f * g_nCountAnimBG));
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f - (0.001f * g_nCountAnimBG));
#endif
	//横スクロール↓
#if 1
	pVtx[4].tex = D3DXVECTOR2(0.0f + (0.0005f * g_nCountAnimBG), 0.0f );
	pVtx[5].tex = D3DXVECTOR2(1.0f + (0.0005f * g_nCountAnimBG), 0.0f );
	pVtx[6].tex = D3DXVECTOR2(0.0f + (0.0005f * g_nCountAnimBG), 1.0f );
	pVtx[7].tex = D3DXVECTOR2(1.0f + (0.0005f * g_nCountAnimBG), 1.0f );
#endif

	if (pVtx[4].tex.x < 0.0f)
	{
		pVtx[4].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[7].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	if (pVtx[6].tex.x < 0.0f)
	{
		pVtx[5].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
//------------------------------------
// アニメーション処理
//------------------------------------
	SpeedAnimationBG++; //カウンターの加算
	if ((SpeedAnimationBG % 20) == 0)
	{
		PatternAnimationBG = (PatternAnimationBG+1) % 8;//パターンNo.更新

		pVtx[8].tex = D3DXVECTOR2(0.0f + (PatternAnimationBG*0.125f), 0.0f);
		pVtx[9].tex = D3DXVECTOR2(0.125f + (PatternAnimationBG*0.125f), 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f + (PatternAnimationBG*0.125f), 1.0f);
		pVtx[11].tex = D3DXVECTOR2(0.125f + (PatternAnimationBG*0.125f), 1.0f);

		pVtx[12].tex = D3DXVECTOR2(0.0f + (PatternAnimationBG*0.125f), 0.0f);
		pVtx[13].tex = D3DXVECTOR2(0.125f + (PatternAnimationBG*0.125f), 0.0f);
		pVtx[14].tex = D3DXVECTOR2(0.0f + (PatternAnimationBG*0.125f), 1.0f);
		pVtx[15].tex = D3DXVECTOR2(0.125f + (PatternAnimationBG*0.125f), 1.0f);
	}

	//頂点座標の設定
	pVtx[8].pos = D3DXVECTOR3(H_SIZE, 300, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(H_SIZE * 2, 300, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(H_SIZE, H_SIZE+300 , 0.0f);
	pVtx[11].pos = D3DXVECTOR3(H_SIZE * 2, H_SIZE+300, 0.0f);

	pVtx[12].pos = D3DXVECTOR3(H_SIZE+300, 100, 0.0f);
	pVtx[13].pos = D3DXVECTOR3((H_SIZE * 2) + 300, 100, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(H_SIZE + 300, H_SIZE + 100, 0.0f);
	pVtx[15].pos = D3DXVECTOR3((H_SIZE * 2) + 300, H_SIZE + 100, 0.0f);

	pVtx += 4;
	//頂点バッファをアンロック
	g_pVtxBuffBG->Unlock();
#endif
}

//=============================================================================
//背景の描画処理
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを所得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBG = 0; nCntBG < BG_TYPE; nCntBG++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBG[nCntBG]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG * 4, 2);
	}
}
