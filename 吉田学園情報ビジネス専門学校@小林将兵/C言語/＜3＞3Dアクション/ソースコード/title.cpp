//=========================================================================
// タイトル画面の処理 [title.cpp]
// Author:Kobayashi/小林 将兵
//=========================================================================
#include "main.h"			//メイン処理
#include "sound.h"
#include "game.h"			//ゲーム処理
#include "camera.h"			//カメラ処理
#include "light.h"			//ライト処理
#include "fade.h"			//フェード(切り替え)処理
#include "title.h"			//タイトル処理
#include "input.h"			//入力処理
#include "stage.h"

//=========================================================================
//マクロ
//=========================================================================
#define T_TYPE (2)//背景の枚数
//#define Title_TEXTURENAME "DATA\\TEXTURE\\title000.jpg"//読み込むテクスチャ
#define Title_TEXTURENAME2 "DATA\\TEXTURE\\TitleLogo00.png"//読み込むテクスチャ
#define Title_TEXTURENAME3 "DATA\\TEXTURE\\PUSH ENTER00.png"//読み込むテクスチャ

#define Title_POS_X (0)							//背景の左上X座標
#define Title_POS_Y (0)						    //背景の左上Y座標
#define Title_WIDTH (SCREEN_WIDTH)				//背景の幅
#define Title_HEIGHT (SCREEN_HEIGHT)			//背景の高さ

//=========================================================================
//グローバル
//=========================================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle[T_TYPE] = {};				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;			//頂点バッファへのポインタ

//int g_ScrollAnim;
int g_nCntFadeT; //自動フェード
int g_nCntFadeEnter; //ENTER押した後の余韻
camera *pCameraTitle;
TITLE_STATE state;
D3DXCOLOR Titlecol;
//=========================================================================
//タイトル / 初期化
//=========================================================================
void InitTitle(void)
{
	InitCamera();
	InitLight();
	InitStage();
	PlaySound(SOUND_LABEL_TITLE);
	//g_ScrollAnim = 0;
	g_nCntFadeT = 0;
	g_nCntFadeEnter = 0;
	state = TITLE_0;
	Titlecol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	pDevice = GetDevice();		//デバイスの所得
	camera *pCamera = GetCamera();//カメラの読み込み
	pCamera[0].Radian = 45.0f;

#if 1
	//◆テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice, Title_TEXTURENAME, &g_pTextureTitle[0]);//動く背景用
	D3DXCreateTextureFromFile(pDevice, Title_TEXTURENAME2, &g_pTextureTitle[0]);//タイトル文字
	D3DXCreateTextureFromFile(pDevice, Title_TEXTURENAME3, &g_pTextureTitle[1]);//タイトル文字

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
		pVtx[0].pos = D3DXVECTOR3(Title_POS_X+100, Title_POS_Y-100, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Title_POS_X + Title_WIDTH+100, Title_POS_Y - 100, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(Title_POS_X, Title_POS_Y + Title_HEIGHT - 100, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Title_POS_X + Title_WIDTH, Title_POS_Y + Title_HEIGHT - 100, 0.0f);

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

		//◇頂点座標の設定
		pVtx[4].pos = D3DXVECTOR3(400, 500, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(Title_WIDTH -370, 500, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(400, Title_HEIGHT + 100, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(Title_WIDTH - 370, Title_HEIGHT + 100, 0.0f);

		//◇rhwの設定
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//◇頂点カラーの設定
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//◇テクスチャ座標の設定
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	}
	//◆頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();
#endif
}

//=========================================================================
//タイトル / 終了
//=========================================================================
void UninitTitle(void)
{
	UninitCamera();
	UninitLight();
	UninitStage();
	StopSound();
#if 1
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
#endif
}

//=========================================================================
//タイトル / 更新
//=========================================================================
void UpdateTitle(void)
{
	UpdateCamera();
	UpdateLight();
	UpdateStage();

//◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆ ◆
//+	カメラ描画移動更新処理
//◇ ◇	◇ ◇ ◇ ◇ ◇ ◇ ◇ ◇	◇ ◇ ◇ ◇ ◇ ◇ ◇ ◇	◇ ◇ ◇ ◇ ◇ ◇ ◇ ◇	◇ ◇ ◇ ◇ ◇ ◇
	pCameraTitle = GetCamera();

	pCameraTitle->posV.x += sinf(pCameraTitle->fKaiten) * 5;
	pCameraTitle->posV.z += cosf(pCameraTitle->fKaiten) * 5;

	pCameraTitle->posR.x = pCameraTitle->posV.x + sinf(pCameraTitle->fKaiten) * 200;
	pCameraTitle->posR.z = pCameraTitle->posV.z + cosf(pCameraTitle->fKaiten) * 200;

#if 1
	//g_ScrollAnim++;

	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを所得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

		switch (state)
		{
		case TITLE_0:
			Titlecol.a += 0.03f;
			if (Titlecol.a >= 1.0f)
			{
				Titlecol.a = 1.0f;
				state = TITLE_1;
			}

			break;

		case TITLE_1:
			Titlecol.a -= 0.03f;
			if (Titlecol.a <= 0.0f)
			{
				Titlecol.a = 0.0f;
				state = TITLE_0;
			}

			break;

		}
	pVtx[4].col = Titlecol;
	pVtx[5].col = Titlecol;
	pVtx[6].col = Titlecol;
	pVtx[7].col = Titlecol;
	

	//pVtx += 4;
	//頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();
#endif

	

	FADE pFade;
	pFade = *GetFade();
	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
				//モードの設定
				SetFade(MODE_TUTORIAL);
		}
	}

	g_nCntFadeT++;
	if (g_nCntFadeT >= 400)
	{
		if (pFade == FADE_NONE)
		{
			
			//モード選択
			SetFade(MODE_RANKING);
		}
	}
}

//=========================================================================
//タイトル / 描画
//=========================================================================
void DrawTitle(void)
{
	DrawStage();
	camera *pCamera = GetCamera();
	SetCamera();
#if 1
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
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG * 4, 2);
	}
#endif
}