//=========================================================================
// チュートリアル処理 [tutorial.cpp]
// Author:Kobayashi/小林 将兵
//=========================================================================
#include "main.h"	//メイン処理
#include "tutorial.h"
#include "input.h"	//入力処理
#include "fade.h"	//フェード画面切り替え処理
#include "sound.h"

//=========================================================================
//マクロ
//=========================================================================
#define TH_TYPE (9)//背景の枚数
#define Tutorial_TEXTURENAME "DATA\\TEXTURE\\背景P_.jpg"//読み込むテクスチャ
#define Tutorial_TEXTURENAME2 "DATA\\TEXTURE\\チュートリアル_.png"//読み込むテクスチャ
#define Tutorial_TEXTURENAME3 "DATA\\TEXTURE\\W.jpg"
#define Tutorial_TEXTURENAME4 "DATA\\TEXTURE\\S.jpg"
#define Tutorial_TEXTURENAME5 "DATA\\TEXTURE\\A.jpg"
#define Tutorial_TEXTURENAME6 "DATA\\TEXTURE\\D.jpg"
#define Tutorial_TEXTURENAME7 "DATA\\TEXTURE\\スペース.jpg"
#define Tutorial_TEXTURENAME8 "DATA\\TEXTURE\\菌B.png"
#define Tutorial_TEXTURENAME9 "DATA\\TEXTURE\\吹き出し.png"

#define Tutorial_POS_X (0)							//背景の左上X座標
#define Tutorial_POS_Y (0)						    //背景の左上Y座標
#define Tutorial_WIDTH (SCREEN_WIDTH)				//背景の幅
#define Tutorial_HEIGHT (SCREEN_HEIGHT)			//背景の高さ

//=========================================================================
//グローバル
//=========================================================================
LPDIRECT3DTEXTURE9 g_pTextureTutorial[TH_TYPE] = {};				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;			//頂点バッファへのポインタ

int SpeedAnimationTH;
int PatternAnimationTH;
int nCC;
//=========================================================================
//タイトル / 初期化
//=========================================================================
void InitTutorial(void)
{
	SpeedAnimationTH = 0;
	PatternAnimationTH = 0;
	nCC = 0;

	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの所得

								//PlaySound(SOUND_LABEL_BGM000);

								//◆テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME, &g_pTextureTutorial[0]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME2, &g_pTextureTutorial[1]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME3, &g_pTextureTutorial[2]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME4, &g_pTextureTutorial[3]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME5, &g_pTextureTutorial[4]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME6, &g_pTextureTutorial[5]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME7, &g_pTextureTutorial[6]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME8, &g_pTextureTutorial[7]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME9, &g_pTextureTutorial[8]);

	//◆頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4* TH_TYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//◆頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntT = 0; nCntT < TH_TYPE; nCntT++)
	{
		//◇頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Tutorial_WIDTH, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, Tutorial_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Tutorial_WIDTH, Tutorial_HEIGHT, 0.0f);

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
//--------
//文字表記
//--------
		//◇頂点座標の設定
		pVtx[4].pos = D3DXVECTOR3(50,50, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(350, 50, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(50, 150, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(350, 150, 0.0f);

		//◇rhwの設定
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//◇頂点カラーの設定
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//◇テクスチャ座標の設定
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

//--------
//	W
//--------
		//◇頂点座標の設定
		pVtx[8].pos = D3DXVECTOR3(250, 300, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(350, 300, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(250, 400, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(350, 400, 0.0f);

		//◇rhwの設定
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//◇頂点カラーの設定
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//◇テクスチャ座標の設定
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);
//--------
//	S
//--------
	//◇頂点座標の設定
	pVtx[12].pos = D3DXVECTOR3(250, 410, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(350, 410, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(250, 510, 0.0f);
	pVtx[15].pos = D3DXVECTOR3(350, 510, 0.0f);

	//◇rhwの設定
	pVtx[12].rhw = 1.0f;
	pVtx[13].rhw = 1.0f;
	pVtx[14].rhw = 1.0f;
	pVtx[15].rhw = 1.0f;

	//◇頂点カラーの設定
	pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//◇テクスチャ座標の設定
	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);

//--------
//	A
//--------
	//◇頂点座標の設定
	pVtx[16].pos = D3DXVECTOR3(140, 410, 0.0f);
	pVtx[17].pos = D3DXVECTOR3(240, 410, 0.0f);
	pVtx[18].pos = D3DXVECTOR3(140, 510, 0.0f);
	pVtx[19].pos = D3DXVECTOR3(240, 510, 0.0f);

	//◇rhwの設定
	pVtx[16].rhw = 1.0f;
	pVtx[17].rhw = 1.0f;
	pVtx[18].rhw = 1.0f;
	pVtx[19].rhw = 1.0f;

	//◇頂点カラーの設定
	pVtx[16].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[17].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[18].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[19].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//◇テクスチャ座標の設定
	pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[17].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[19].tex = D3DXVECTOR2(1.0f, 1.0f);

//--------
//	D
//--------
	//◇頂点座標の設定
	pVtx[20].pos = D3DXVECTOR3(360, 410, 0.0f);
	pVtx[21].pos = D3DXVECTOR3(460, 410, 0.0f);
	pVtx[22].pos = D3DXVECTOR3(360, 510, 0.0f);
	pVtx[23].pos = D3DXVECTOR3(460, 510, 0.0f);

	//◇rhwの設定
	pVtx[20].rhw = 1.0f;
	pVtx[21].rhw = 1.0f;
	pVtx[22].rhw = 1.0f;
	pVtx[23].rhw = 1.0f;

	//◇頂点カラーの設定
	pVtx[20].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[21].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[22].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[23].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//◇テクスチャ座標の設定
	pVtx[20].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[21].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[22].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[23].tex = D3DXVECTOR2(1.0f, 1.0f);

//--------
//	SPACE
//--------
	//◇頂点座標の設定
	pVtx[24].pos = D3DXVECTOR3(580, 420, 0.0f);
	pVtx[25].pos = D3DXVECTOR3(800, 420, 0.0f);
	pVtx[26].pos = D3DXVECTOR3(580, 510, 0.0f);
	pVtx[27].pos = D3DXVECTOR3(800, 510, 0.0f);

	//◇rhwの設定
	pVtx[24].rhw = 1.0f;
	pVtx[25].rhw = 1.0f;
	pVtx[26].rhw = 1.0f;
	pVtx[27].rhw = 1.0f;

	//◇頂点カラーの設定
	pVtx[24].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[25].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[26].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[27].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//◇テクスチャ座標の設定
	pVtx[24].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[25].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[26].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[27].tex = D3DXVECTOR2(1.0f, 1.0f);

//--------
//	菌
//--------
	//◇頂点座標の設定
	pVtx[28].pos = D3DXVECTOR3(880, 570, 0.0f);
	pVtx[29].pos = D3DXVECTOR3(1000, 570, 0.0f);
	pVtx[30].pos = D3DXVECTOR3(880, 670, 0.0f);
	pVtx[31].pos = D3DXVECTOR3(1000, 670, 0.0f);

	//◇rhwの設定
	pVtx[28].rhw = 1.0f;
	pVtx[29].rhw = 1.0f;
	pVtx[30].rhw = 1.0f;
	pVtx[31].rhw = 1.0f;

	//◇頂点カラーの設定
	pVtx[28].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[29].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[30].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[31].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//◇テクスチャ座標の設定
	pVtx[28].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[29].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[30].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[31].tex = D3DXVECTOR2(0.25f, 1.0f);

	//--------
	//	吹き出し
	//--------
	//◇頂点座標の設定
	pVtx[32].pos = D3DXVECTOR3(880, 370, 0.0f);
	pVtx[33].pos = D3DXVECTOR3(1200, 370, 0.0f);
	pVtx[34].pos = D3DXVECTOR3(880, 570, 0.0f);
	pVtx[35].pos = D3DXVECTOR3(1200, 570, 0.0f);

	//◇rhwの設定
	pVtx[32].rhw = 1.0f;
	pVtx[33].rhw = 1.0f;
	pVtx[34].rhw = 1.0f;
	pVtx[35].rhw = 1.0f;

	//◇頂点カラーの設定
	pVtx[32].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[33].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[34].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[35].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//◇テクスチャ座標の設定
	pVtx[32].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[33].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[34].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[35].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//◆頂点バッファをアンロック
	g_pVtxBuffTutorial->Unlock();
}

//=========================================================================
//タイトル / 終了
//=========================================================================
void UninitTutorial(void)
{
	for (int nCnt = 0; nCnt < TH_TYPE; nCnt++)
	{
		if (g_pTextureTutorial[nCnt] != NULL)
		{
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
	//StopSound();
}

//=========================================================================
//タイトル / 更新
//=========================================================================
void UpdateTutorial(void)
{
	

	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	nCC++;
	pVtx[4].col = D3DCOLOR_RGBA(255 - nCC, 255 - nCC, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255 - nCC, 255 - nCC, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);

	pVtx[16].col = D3DCOLOR_RGBA(255, 255, 255 - nCC, 255);
	pVtx[17].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);
	pVtx[18].col = D3DCOLOR_RGBA(255, 255, 255 - nCC, 255);
	pVtx[19].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);

	pVtx[20].col = D3DCOLOR_RGBA(255, 255, 255 - nCC, 255);
	pVtx[21].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);
	pVtx[22].col = D3DCOLOR_RGBA(255, 255, 255 - nCC, 255);
	pVtx[23].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);

	pVtx[24].col = D3DCOLOR_RGBA(255, 255, 255 - nCC, 255);
	pVtx[25].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);
	pVtx[26].col = D3DCOLOR_RGBA(255, 255, 255 - nCC, 255);
	pVtx[27].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);

#if 0
	if (GetKeyboardPress(DIK_W) == true)
	{
		pVtx[8].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	if (GetKeyboardPress(DIK_W) == false)
	{
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	if (GetKeyboardPress(DIK_S) == true)
	{
		pVtx[12].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[13].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[14].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[15].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	if (GetKeyboardPress(DIK_S) == false)
	{
		pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	if (GetKeyboardPress(DIK_A) == true)
	{
		pVtx[16].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[17].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[18].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[19].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	if (GetKeyboardPress(DIK_A) == false)
	{
		pVtx[16].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[17].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[18].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[19].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	if (GetKeyboardPress(DIK_D) == true)
	{
		pVtx[20].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[21].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[22].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[23].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	if (GetKeyboardPress(DIK_D) == false)
	{
		pVtx[20].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[21].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[22].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[23].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		pVtx[24].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[25].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[26].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[27].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	if (GetKeyboardPress(DIK_SPACE) == false)
	{
		pVtx[24].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[25].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[26].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[27].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
#endif
		SpeedAnimationTH++; //カウンターの加算
		if ((SpeedAnimationTH % 8) == 0)
		{
			PatternAnimationTH = (PatternAnimationTH + 1) % 4;//パターンNo.更新

			pVtx[28].tex = D3DXVECTOR2((PatternAnimationTH*0.25f), 0.0f);
			pVtx[29].tex = D3DXVECTOR2((PatternAnimationTH*0.25f) + 0.25f, 0.0f);
			pVtx[30].tex = D3DXVECTOR2((PatternAnimationTH*0.25f), 1.0f);
			pVtx[31].tex = D3DXVECTOR2((PatternAnimationTH*0.25f) + 0.25f, 1.0f);
		}
		pVtx += 4;

	// 頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();

	FADE pFade;
	pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//モードの設定
			SetFade(MODE_GAME);
		}

	}
}

//=========================================================================
//タイトル / 描画
//=========================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//◆デバイスを所得する
	pDevice = GetDevice();

	//◆頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//◆頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTH = 0; nCntTH < TH_TYPE; nCntTH++)
	{
		//◆テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTutorial[nCntTH]);


		//◆ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTH*4, 2);
	}
}
