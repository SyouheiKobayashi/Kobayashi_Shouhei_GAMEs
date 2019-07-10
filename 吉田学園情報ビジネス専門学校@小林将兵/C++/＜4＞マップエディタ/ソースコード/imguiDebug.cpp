//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//imgui処理 [imguiDebug.cpp]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "imguiDebug.h"
#include "imconfig.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"
#include "imstb_rectpack.h"
#include "imstb_textedit.h"
#include "imstb_truetype.h"

#include "game.h"
#include "player.h"
#include "model.h"
//=====================================================================
//静的メンバ変数
//=====================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CImguiDebug::CImguiDebug()
{
	
}
//=============================================================================
//デストラクタ
//=============================================================================
CImguiDebug::~CImguiDebug()
{

}

//=============================================================================
//初期化処理
//=============================================================================
void CImguiDebug::Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
{
	//ImGui用のテキストデータを生成する
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//AddFontFromFileTTF関数
	//第１引数 : フォントデータのファイルパス名
	//第２引数 : フォントのサイズ
	//第３引数 : NULLでOK
	//第４引数 : 日本語にしたければio.Fonts->GetGlyphRangesJapaneseで基本的にOK
	io.Fonts->AddFontFromFileTTF("c:/Windows/Fonts/meiryo.ttc", 20.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	//ImGuiを生成する
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);
	ImGui::StyleColorsClassic();
}
//=============================================================================
//終了処理
//=============================================================================
void CImguiDebug::Uninit(void)
{
	//ImGuiを終了させる
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

}
//=============================================================================
//更新処理
//=============================================================================
void CImguiDebug::Update(void)
{
	CGame * pGame = CManager::GetGame();
	CPlayer *pPlayer = CGame::GetPlayer();

	//新しいフレームを用意する
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//ウィンドウ生成開始
	ImGui::Begin(u8"Map_Editor Ver3.0", false);
	//ウィンドウ内にタグを増やす
	ImGui::CollapsingHeader(u8"Information");

	if (pPlayer != NULL)
	{
		int nNowSampleView = pPlayer->GetSampleObjType();
		ImGui::Text(u8"現在表示しているサンプル");
		ImGui::InputInt(u8"", &nNowSampleView);
		if (nNowSampleView > CModel::GetMaxCreateNum())
		{
			nNowSampleView = 0;
		}
		if (nNowSampleView < 0)
		{
			nNowSampleView = CModel::GetMaxCreateNum();
		}
		pPlayer->SetSampleObj(nNowSampleView);

		ImGui::Text(u8"サンプルの位置");
		D3DXVECTOR3 pos = pPlayer->GetPos();
		ImGui::InputFloat3(u8"", pos);
		pPlayer->SetPos(pos);

		ImGui::Text(u8"サンプルの回転軸");
		D3DXVECTOR3 rot = pPlayer->GetRot();
		ImGui::InputFloat3(u8" ", rot);//ひと枠開ける[u8"ここを開ける"]選択ができなくなる
		pPlayer->SetRot(rot);

	}
	//現在の情報を保存する
	//if (ImGui::Button(u8"保存する"))
	//{
	//	ImGui::SameLine();
	//}

	//if (ImGui::CollapsingHeader(u8"Information02"))
	//{
	//	ImGui::Text(u8"W,A,S,D [オブジェクトの移動]");
	//	ImGui::Text(u8"上,左,下,右 [カメラの移動]");
	//	if (ImGui::CollapsingHeader(u8"操作方法02"))
	//	{
	//		ImGui::Text(u8"上,左,下,右 [カメラの移動]02");
	//	}
	//}
	
	//ウィンドウ生成終了
	ImGui::End();

	if (pGame->GetInputMode() == 0)
	{
		Tutorial();//キーボード用説明
	}
	else if (pGame->GetInputMode() == 1)
	{
		Tutorial02();//マウス用説明
	}

	//フレームを終了させる
	ImGui::EndFrame();
	//u8…日本語

}
//=============================================================================
//描画処理
//=============================================================================
void CImguiDebug::Draw(void)
{
	//Updateで生成したImGuiを表示する
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void CImguiDebug::Tutorial(void)
{
	//ウィンドウ生成開始
	ImGui::Begin(u8"キーボードの操作説明", false);
	
	//記載内容
	ImGui::Text(u8"[F1] : 視点変更   [F2キー] : 操作の変更");
	ImGui::Text(u8"[WASDQEキー] : オブジェクトの移動   [矢印キー / 0キー] : カメラの移動 / 初期化	[位置の初期化] : ENTERキー");
	ImGui::Text(u8"[1・2キー] : オブジェクトの変更   [スペースキー] : 生成   [BackSpace] : ひとつ前に戻る   [F5キー] : 外部テキストに出力<OBJ_OUTPUT.txt>");

	//ウィンドウ生成終了
	ImGui::End();
}

void CImguiDebug::Tutorial02(void)
{
	//ウィンドウ生成開始
	ImGui::Begin(u8"マウスの操作説明", false);

	//記載内容
	ImGui::Text(u8"[F1] : 視点変更(マウス移動がXZ用・XY用に変更)   [F2キー] : 操作の変更");
	ImGui::Text(u8"[マウスに依存] : オブジェクトの移動   [WASDQEキー] : カメラの移動    [Xキー] : 初期化   [右クリック長押し] : 視点の回転");
	ImGui::Text(u8"[ホイールの回転] : オブジェクトの変更   [左クリック] : 生成   [BackSpace] : ひとつ前に戻る   [F5キー] : 外部テキストに出力<OBJ_OUTPUT.txt>");

	//ウィンドウ生成終了
	ImGui::End();
}


