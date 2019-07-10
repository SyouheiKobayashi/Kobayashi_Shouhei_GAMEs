//=========================================================================
// リザルト画面の処理 [result.cpp]
// Kobayashi Syouhei / 小林将兵
//=========================================================================
#include "main.h"	//メイン処理
#include "result.h"	//リザルト処理
#include "input.h"	//入力処理
#include "fade.h"	//フェード画面切り替え処理

//=========================================================================
//マクロ
//=========================================================================
#define Result_TEXTURENAME "DATA\\TEXTURE\\血しぶき.png"		//読み込むテクスチャ
#define Result_POS_X (0)							//背景の左上X座標
#define Result_POS_Y (0)						    //背景の左上Y座標
#define Result_WIDTH (SCREEN_WIDTH)					//背景の幅
#define Result_HEIGHT (SCREEN_HEIGHT)				//背景の高さ

//=========================================================================
//グローバル
//=========================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;			//頂点バッファへのポインタ

//=========================================================================
//リザルト / 初期化
//=========================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの所得


	//◆テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, Result_TEXTURENAME, &g_pTextureResult);

	//◆頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

						//◆頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//◇頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(Result_POS_X, Result_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Result_POS_X + Result_WIDTH, Result_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Result_POS_X, Result_POS_Y + Result_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Result_POS_X + Result_WIDTH, Result_POS_Y + Result_HEIGHT, 0.0f);

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

	//◆頂点バッファをアンロック
	g_pVtxBuffResult->Unlock();
}

//=========================================================================
//タイトル / 終了
//=========================================================================
void UninitResult(void)
{
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//=========================================================================
//リザルト / 更新
//=========================================================================
void UpdateResult(void)
{
	FADE pFade;
	pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//モードの設定
			SetFade(MODE_TITLE);
		}
	}
}

//=========================================================================
//リザルト / 描画
//=========================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//◆デバイスを所得する
	pDevice = GetDevice();
	pDevice->SetFVF(FVF_VERTEX_2D);

	//◆頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//◆テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult);

	//◆頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//◆ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
