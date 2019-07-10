//=============================================================================
// スコア処理 [score.cpp]
// Author:Kobayashi/小林 将兵
//=============================================================================
#include "score.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_SCORE		"DATA\\TEXTURE\\number000.png"	// 読み込むテクスチャファイル名
#define TATE_POS (35)
#define YOKO_POS (925)
#define TATE_SIZE (25)
#define YOKO_SIZE (25)
//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// 頂点バッファへのポインタ
int						g_nScore;					// スコア
D3DXVECTOR3				g_posScore;					// 位置

//=============================================================================
// 初期化処理
//=============================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スコアの初期化
	g_nScore = 0;

	g_posScore = D3DXVECTOR3(YOKO_POS, TATE_POS, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_SCORE,		// ファイルの名前
								&g_pTextureScore);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexScore(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	// テクスチャの開放
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	// 頂点バッファの開放
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	int nCount;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	
	// ポリゴンの描画
	for (nCount = 0; nCount < 8; nCount++)
	{
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCount,2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntScore;

	// [頂点バッファを生成]
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// [頂点情報を設定]
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - YOKO_SIZE, g_posScore.y - TATE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + YOKO_SIZE, g_posScore.y - TATE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - YOKO_SIZE, g_posScore.y + TATE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + YOKO_SIZE, g_posScore.y + TATE_SIZE, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
		g_posScore.x += 40;//間隔
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// スコアの加算
//=============================================================================
void AddScore(int nValue)
{
	int nScoreNo[8];
	int nCntScoreNo;

	g_nScore += nValue;

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	nScoreNo[0] = g_nScore / 10000000;
	nScoreNo[1] = g_nScore % 10000000 / 1000000;
	nScoreNo[2] = g_nScore % 1000000 / 100000;
	nScoreNo[3] = g_nScore % 100000 / 10000;
	nScoreNo[4] = g_nScore % 10000 / 1000;
	nScoreNo[5] = g_nScore % 1000 / 100;
	nScoreNo[6] = g_nScore % 100 / 10;
	nScoreNo[7] = g_nScore % 10;

	for (nCntScoreNo = 0; nCntScoreNo < 8; nCntScoreNo++)
	{
	pVtx[0].tex = D3DXVECTOR2(0.0f + nScoreNo[nCntScoreNo] * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + nScoreNo[nCntScoreNo] * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + nScoreNo[nCntScoreNo] * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + nScoreNo[nCntScoreNo] * 0.1f, 1.0f);

	pVtx += 4;

	}
	
	// 頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
 }
