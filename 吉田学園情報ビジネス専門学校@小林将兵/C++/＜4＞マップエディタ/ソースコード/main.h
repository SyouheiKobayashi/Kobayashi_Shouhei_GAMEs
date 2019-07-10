//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//メイン処理 [main.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _MAIN_H_
#define _MAIN_H_
#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION (0x0800) //ビルド時の警告対処

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include <windows.h>
#include "d3dx9.h"		//描画に必要な処理
#include"dinput.h"		//入力処理に必要
#include "xaudio2.h"	//サウンド処理に必要
#include <Xinput.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>

//==============================================
//ライブラリファイルへのリンク
//==============================================
#pragma comment(lib,"d3d9.lib")			//描画に必要な処理
#pragma comment(lib,"d3dx9.lib")		//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")		//DirectXコンポーネント(部品)に必要
#pragma comment(lib,"winmm.lib")		//システム時刻所得に必要
#pragma comment(lib,"dinput8.lib")		//入力処理に必要
#pragma comment(lib, "xinput.lib")	

//==============================================
//マクロの定義
//==============================================
#define SCREEN_WIDTH	(1280)		//ウインドウの幅
#define SCREEN_HEIGHT	(720)		//ウインドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//3Ｄポリゴン頂点フォーマット(頂点座標[3D] / 頂点カラー / テクスチャ座標)
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//#define MAX_SCENE	(4444)//Scene(ポリゴン)の最大数

//==============================================
//構造体の宣言
//==============================================
//2Dに関する処理
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_2D;

//3Dに関する処理
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_3D;

//==============================================
//前方宣言
//==============================================
class cRenderer;
class cScene;

int GetFPS(void);

#endif