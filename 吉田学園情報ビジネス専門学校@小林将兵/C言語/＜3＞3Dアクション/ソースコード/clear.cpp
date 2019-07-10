//=========================================================================
// クリア画面の処理 [clear.cpp]
// Kobayashi Syouhei / 小林将兵
//=========================================================================
#include "main.h"	//メイン処理
#include "sound.h"
#include "clear.h"	//クリア処理
#include "camera.h"	//カメラ処理
#include "light.h"	//ライト処理
#include "stage.h"
#include "player.h"
#include "fade.h"	//フェード処理
#include "input.h"	//入力処理

//=========================================================================
//マクロ
//=========================================================================
#define Clear_TEXTURENAME "DATA\\TEXTURE\\title00.png"		//読み込むテクスチャ
#define Clear_POS_X (0)							//背景の左上X座標
#define Clear_POS_Y (0)						    //背景の左上Y座標
#define Clear_WIDTH (SCREEN_WIDTH)					//背景の幅
#define Clear_HEIGHT (SCREEN_HEIGHT)				//背景の高さ

//=========================================================================
//グローバル
//=========================================================================
LPDIRECT3DTEXTURE9 g_pTextureClear = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffClear = NULL;			//頂点バッファへのポインタ
camera *pCameraClear;
//=========================================================================
//リザルト / 初期化
//=========================================================================
void InitClear(void)
{
	InitCamera();
	InitLight();
	InitStage();
	InitPlayer();
	PlaySound(SOUND_LABEL_TITLE);

	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの所得
	camera *pCamera = GetCamera();//カメラの読み込み
	pCamera[0].Radian = 45.0f;
	pCamera->posV = D3DXVECTOR3(sinf(pCamera->fKaiten)*3600, 40, cosf(pCamera->fKaiten)*3600);						//視点
	pCamera->posR = D3DXVECTOR3(0, 80, 0);				//注視点
	pCamera->vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);


	PLAYER *pPlayer = GetPlayer();//プレイヤーの読み込み
	pPlayer->pos = D3DXVECTOR3(0, 0, 3400);
	pPlayer->rot = D3DXVECTOR3(0, 60, 0);



	//◆テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, Clear_TEXTURENAME, &g_pTextureClear);

	//◆頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffClear,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

						//◆頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffClear->Lock(0, 0, (void**)&pVtx, 0);

	//◇頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(Clear_POS_X, Clear_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Clear_POS_X + Clear_WIDTH, Clear_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Clear_POS_X, Clear_POS_Y + Clear_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Clear_POS_X + Clear_WIDTH, Clear_POS_Y + Clear_HEIGHT, 0.0f);

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
	g_pVtxBuffClear->Unlock();
}

//=========================================================================
//タイトル / 終了
//=========================================================================
void UninitClear(void)
{
	UninitCamera();
	UninitLight();
	UninitStage();
	UninitPlayer();
	StopSound();

	if (g_pTextureClear != NULL)
	{
		g_pTextureClear->Release();
		g_pTextureClear = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffClear != NULL)
	{
		g_pVtxBuffClear->Release();
		g_pVtxBuffClear = NULL;
	}
}

//=========================================================================
//リザルト / 更新
//=========================================================================
void UpdateClear(void)
{
	
	UpdateLight();
	UpdateStage();
	

	/*pCameraClear = GetCamera();

	pCameraClear->posV.x = sinf(pCameraClear->fKaiten) * 5;
	pCameraClear->posV.z = cosf(pCameraClear->fKaiten) * 5;

	pCameraClear->posR.x = pCameraClear->posV.x + sinf(pCameraClear->fKaiten) * 200;
	pCameraClear->posR.z = pCameraClear->posV.z + cosf(pCameraClear->fKaiten) * 200;*/

	//pCameraClear->vecU = D3DXVECTOR3(D3DX_PI, 1.0f, 0.0f);

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
void DrawClear(void)
{
	DrawStage();
	DrawPlayer();
	//camera *pCamera = GetCamera();
	SetCamera();

	LPDIRECT3DDEVICE9 pDevice;

	//◆デバイスを所得する
	pDevice = GetDevice();
	pDevice->SetFVF(FVF_VERTEX_2D);

	//◆頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffClear, 0, sizeof(VERTEX_2D));

	//◆テクスチャの設定
	pDevice->SetTexture(0, g_pTextureClear);

	//◆頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//◆ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
