//? ◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//? ポーズ処理
//? Kobayashi / 小林
//? ◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "pause.h"
#include "game.h"

//? ==================================================
//? マクロ定義
//? ==================================================
#define PAUSE_TEXTURENAME "DATA\\TEXTURE\\pause00.png" //読み込むテクスチャ
#define PAUSE_POS_X (0)						 //背景の左上X座標
#define PAUSE_POS_Y (0)						 //背景の左上Y座標
#define PAUSE_WIDTH (SCREEN_WIDTH)				 //背景の幅
#define PAUSE_HEIGHT (SCREEN_HEIGHT)			 //背景の高さ

//? ==================================================
//? グローバル変数
//? ==================================================
LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;


//? ==================================================
//? 初期化
//? ==================================================
#if 1
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの所得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURENAME, &g_pTexturePause);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	VERTEX_2D*pVtx;//頂点情報へのポインタ

				   //頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PAUSE_POS_X + PAUSE_WIDTH, PAUSE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y + PAUSE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PAUSE_POS_X + PAUSE_WIDTH, PAUSE_POS_Y + PAUSE_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffPause->Unlock();
}
#endif
//? ==================================================
//? 終了
//? ==================================================
#if 1
void UninitPause(void)
{
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}
#endif
//? ==================================================
//? 更新
//? ==================================================
#if 1
void UpdataPause(void)
{

}
#endif
//? ==================================================
//? 描画
//? ==================================================
#if 1
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを所得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePause);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
#endif