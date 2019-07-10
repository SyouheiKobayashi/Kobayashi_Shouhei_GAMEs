//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//チュートリアル用画像処理処理 [tutorial2DTex.cpp]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "tutorial2DTex.h"
#include "manager.h"
#include "input.h"
#include "debugLog.h"
#include "game.h"

LPDIRECT3DTEXTURE9 CTutorial2DTex::m_pTexture[TEX_MAX] = {};

//==============================================
//コンストラクタ
//==============================================
CTutorial2DTex::CTutorial2DTex(int nPriority, DATA_TYPE dataType) :CScene2D(nPriority, dataType)
{
	m_pVtxBuff = NULL;		//頂点バッファへのポインタ
}
//==============================================
//デストラクタ
//==============================================
CTutorial2DTex::~CTutorial2DTex()
{

}

//==============================================
//生成
//==============================================
CTutorial2DTex *CTutorial2DTex::Create(int nTexType,D3DXVECTOR3 pos, float nSizeX, float nSizeY)
{

	CTutorial2DTex *pTexture2D = NULL;

	if (pTexture2D == NULL)
	{
		pTexture2D = new CTutorial2DTex;
		pTexture2D->BindTexture(m_pTexture[nTexType]);
		pTexture2D->SetPos(pos);
		pTexture2D->SetSize(nSizeX, nSizeY);
		pTexture2D->Init();
	}
	return pTexture2D;
}
//==============================================
//初期化処理
//==============================================
HRESULT CTutorial2DTex::Init(void)
{
	CScene2D::Init();

	return S_OK;
}
//==============================================
//終了処理
//==============================================
void CTutorial2DTex::Uninit(void)
{
	CScene2D::Uninit();

}

//==============================================
//更新処理
//==============================================
void CTutorial2DTex::Update(void)
{
	CScene2D::Update();
}

//==============================================
//描画処理
//==============================================
void CTutorial2DTex::Draw(void)
{
	CScene2D::Draw();
}

//==============================================
//反映させる画像の読み込み
//==============================================
HRESULT CTutorial2DTex::TextureLoad(void)
{

	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "DATA/TEXTURE/T03.jpg", &m_pTexture[0]);

	return S_OK;
}

//==============================================
//反映させた画像の破棄
//==============================================
void CTutorial2DTex::TextureUnLoad(void)
{

	// テクスチャの破棄
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

}