//=============================================================================
// モデル処理 [player.h]
// Author :Kobayashi/小林将兵//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MODEL (1)

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	LPDIRECT3DTEXTURE9 pTexture;

	DWORD nNumMat;
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;			//回転
	int nIdxModelParent;//親モデルとのインデックス
	bool bUse;
}MODEL;

typedef struct
{
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 posOld;			//ひとつ前
	D3DXVECTOR3 move;			//移動
	D3DXVECTOR3 rot;			//回転
	D3DXVECTOR3 VtxMax;
	D3DXVECTOR3 VtxMin;
	MODEL aModel[MAX_MODEL];
	bool bUse;
}PLAYER;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(void);
#endif
