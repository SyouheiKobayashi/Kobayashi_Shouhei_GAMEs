//=============================================================================
// アクションゲーム処理 [main.cpp]
// Author : Kobayashi / 小林
//=============================================================================
#include "main.h"
#include "sound.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "clear.h"
#include "result.h"
#include "fade.h"
#include "input.h"
#include "bg.h"
#include "player.h"
#include "block.h"
#include "item.h"
#include "score.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CLASS_NAME		"WindowClass"		// ウインドウクラスの名前
#define WINDOW_NAME		"アクションゲーム"	// ウインドウの名前(キャプション名)

//=============================================================================
// プロトタイプ宣言
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;

MODE g_mode = MODE_TITLE;//ゲームの始まりはタイトルから

Item g_Item2;

//=============================================================================
// メイン関数
//=============================================================================
#if 1
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};
	//RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;			//現在時刻
	DWORD dwExecLastTime;			//最後に処理した時刻
	dwCurrentTime = 0;				//初期化する
	dwExecLastTime = timeGetTime(); //現在時刻を所得
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	//AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの生成
	hWnd = CreateWindowEx(0,
							CLASS_NAME,
							WINDOW_NAME,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							/*(rect.right - rect.left),
							(rect.bottom - rect.top),*/
							SCREEN_WIDTH,
							SCREEN_HEIGHT,
							NULL,
							NULL,
							hInstance,
							NULL);

	// 初期化処理(ウィンドウを生成してから行う)
	if (FAILED(Init(hInstance, hWnd, TRUE))) //FALSE　→ 全画面
	{
		return -1;
	}
	timeBeginPeriod(1);				//分解能を設定

	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while(1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// メッセージを取得しなかった場合"0"を返す
		{// Windowsの処理
			if (msg.message == WM_QUIT)
			{// "WM_QUIT"メッセージが送られてきたらループを抜ける
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectXの処理

			dwCurrentTime = timeGetTime();		//現在時刻を取得

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// "60分の1秒"経過
				dwExecLastTime = dwCurrentTime;		//処理した時刻を保存
			// 更新処理
				Update();

				// 描画処理
				Draw();
			}
		}
	}

	// 終了処理
	Uninit();

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}
#endif
//=============================================================================
// ウインドウプロシージャ
//=============================================================================
#if 1
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		int nID;

	case WM_DESTROY:
		// "WM_QUIT"メッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
//[ESCキーを押した場合...]
			// ウィンドウを破棄する("WM_DESTROY"メッセージを送る)
			nID = MessageBox(hWnd, "ESCキーを押したね。終了する？(*´ω｀*)", "ESCキーを押した貴方に『終了メッセージ』", MB_YESNO);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;

		}
		break;

//[×ボタンの作成 / 押した場合...]
	case WM_CLOSE:
		nID = MessageBox(hWnd, "×を押したな。終了するか？(; ･`д･´)", "決別の時...", MB_YESNO);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// 既定の処理を返す
}
#endif
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;
	// Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			 = d3ddm.Format;				// バックバッファの形式
	d3dpp.BackBufferCount			 = 1;							// バックバッファの数
	d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;		// ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil	 = TRUE;						// デプスバッファ(Ｚバッファ)とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = false;// ウィンドウモード	
	//d3dpp.Windowed = false;// フルウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート(現在の速度に合わせる)
	d3dpp.PresentationInterval		 = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル(VSyncを待って描画)

	// Direct3Dデバイスの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,						// ディスプレイアダプタ
									D3DDEVTYPE_HAL,							// デバイスタイプ
									hWnd,									// フォーカスするウインドウへのハンドル
									D3DCREATE_HARDWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
									&d3dpp,									// デバイスのプレゼンテーションパラメータ
									&g_pD3DDevice)))						// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp,
										&g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp,
											&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); //カリングの設定 / D3DCULL_CCW 裏面をカリング
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//← TRUE / FALSE にしてみたり...
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);			//アルファブレンドの設定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);		//←

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//[各種オブジェクトの初期化処理]
	InitSound(hWnd);//サウンド
	InitKeyboard(hInstance,hWnd);//キーボード
	InitFade(MODE_TITLE);	//フェードの設定
	SetMode(g_mode);	//モードの設定

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	//[各種オブジェクトの終了処理]
	UninitSound();
	UninitKeyboard();
	UninitTitle();
	UninitTutorial();
	UninitGame();
	UninitClear();
	UninitResult();
	UninitFade();

	// Direct3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの開放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Update()
{
	//[各種オブジェクトの更新処理]
	UpdateKeyboard();
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;

	case MODE_TUTORIAL:
		UpdateTutorial();
		break;

	case MODE_GAME:
		UpdateGame();
		break;

	case MODE_CLEAR:
		UpdateClear();
		break;

	case MODE_RESULT:
		UpdateResult();
		break;
	}
	UpdateFade();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//[各種オブジェクトの描画処理]
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;

		case MODE_TUTORIAL:
			DrawTutorial();
			break;

		case MODE_GAME:
			DrawGame();
			break;

		case MODE_CLEAR:
			DrawClear();
			break;

		case MODE_RESULT:
			DrawResult();
			break;
		}

		DrawFade();

		// 描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
//デバイスの所得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=============================================================================
//モードの設定
//=============================================================================
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;

	case MODE_TUTORIAL:
		UninitTutorial();
		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_CLEAR:
		UninitClear();
		break;

	case MODE_RESULT:
		UninitResult();
		break;
	}
	//-------------------------
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_TUTORIAL:
		InitTutorial();
		break;

	case MODE_GAME:
		InitGame();
		break;

	case MODE_CLEAR:
		InitClear();
		break;

	case MODE_RESULT:
		InitResult();
		break;
	}
	g_mode = mode;
}

MODE GetMode(void)
{
	return g_mode;
}