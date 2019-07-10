//=========================================================================
// リザルト画面の処理 [result.cpp]
// Kobayashi Syouhei / 小林将兵
//=========================================================================
#include "main.h"	//メイン処理
#include "sound.h"
#include "result.h"	//リザルト処理
#include "camera.h"	//カメラ処理
#include "light.h"	//ライト処理
#include "stage.h"
#include "fade.h"	//フェード処理
#include "input.h"	//入力処理

//=========================================================================
//マクロ
//=========================================================================
#define Result_TEXTURENAME "DATA\\TEXTURE\\result00.png"		//読み込むテクスチャ
#define Result_POS_X (0)							//背景の左上X座標
#define Result_POS_Y (0)						    //背景の左上Y座標
#define Result_WIDTH (SCREEN_WIDTH)					//背景の幅
#define Result_HEIGHT (SCREEN_HEIGHT)				//背景の高さ

//=========================================================================
//グローバル
//=========================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;			//頂点バッファへのポインタ
camera *pCameraResult;
//=========================================================================
//リザルト / 初期化
//=========================================================================
void InitResult(void)
{
	InitCamera();
	InitLight();
	InitStage();
	PlaySound(SOUND_LABEL_RESULT);

	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの所得
	camera *pCamera = GetCamera();//カメラの読み込み
	pCamera[0].Radian = 45.0f;


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
	UninitCamera();
	UninitLight();
	UninitStage();
	StopSound();

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

	UpdateCamera();
	UpdateLight();
	UpdateStage();

	pCameraResult = GetCamera();

	pCameraResult->posV.x = sinf(pCameraResult->fKaiten) * 5;
	pCameraResult->posV.z = cosf(pCameraResult->fKaiten) * 5;

	pCameraResult->posR.x = pCameraResult->posV.x + sinf(pCameraResult->fKaiten) * 200;
	pCameraResult->posR.z = pCameraResult->posV.z + cosf(pCameraResult->fKaiten) * 200;

	pCameraResult->vecU = D3DXVECTOR3(D3DX_PI, 1.0f, 0.0f);


	FADE pFade;
	pFade = *GetFade();
	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//モードの設定
			SetFade(MODE_RANKING);
		}
	}
}

//=========================================================================
//リザルト / 描画
//=========================================================================
void DrawResult(void)
{
	DrawStage();
	camera *pCamera = GetCamera();
	SetCamera();

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
