//? ◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//? タイトル処理 [title.cpp]
//? Kobayashi Syouhei / 小林将兵
//? ◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "main.h"	//メイン処理
#include "title.h"	//タイトル処理
#include "input.h"	//入力処理
#include "fade.h"	//フェード画面切り替え処理
#include "sound.h"

//? ==================================================
//? マクロ
//? ==================================================
#define Title_TEXTURENAME "DATA\\TEXTURE\\TITLE00.jpg"		//読み込むテクスチャ
#define Title_POS_X (0)							//背景の左上X座標
#define Title_POS_Y (0)						    //背景の左上Y座標
#define Title_WIDTH (SCREEN_WIDTH)				//背景の幅
#define Title_HEIGHT (SCREEN_HEIGHT)			//背景の高さ

//? ==================================================
//? グローバル
//? ==================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;			//頂点バッファへのポインタ

//? ==================================================
//? タイトル / 初期化
//? ==================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの所得
	
	PlaySound(SOUND_TITLE);

	//◆テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, Title_TEXTURENAME, &g_pTextureTitle);

	//◆頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//◆頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//◇頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(Title_POS_X + Title_WIDTH, Title_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Title_POS_X + Title_WIDTH, Title_POS_Y + Title_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Title_POS_X, Title_POS_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Title_POS_X, Title_POS_Y + Title_HEIGHT, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);

	//◆頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();
}

//? ==================================================
//? タイトル / 終了
//? ==================================================
void UninitTitle(void)
{
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
	StopSound();
}

//? ==================================================
//? タイトル / 更新
//? ==================================================
void UpdateTitle(void)
{
	FADE pFade;
	pFade = *GetFade();
	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			PlaySound(SOUND_PUSH);
			//モードの設定
			SetFade(MODE_TUTORIAL);
		}

	}
}

//? ==================================================
//? タイトル / 描画
//? ==================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//◆デバイスを所得する
	pDevice = GetDevice();

	//◆頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//◆テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle);

	//◆頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//◆ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
