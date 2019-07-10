//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// ライフ処理 [life.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "life.h"
#include "Gauge.h"
#include "manager.h"

//マクロ
#define LIFE_SIZE_X	(30)
#define LIFE_SIZE_Y	(15)
#define LIFE_SPACE		(30)
#define LIFE_POS_X	(52)
#define LIFE_POS_Y	(SCREEN_HEIGHT-75)

//読み込むテクスチャ↓
#define TEXTURE_NAME01	("DATA\\PLAYER_LIFE.jpg")
//静的メンバ変数
int CLife::m_nLife = 0;
int CLife::m_nLifeGauge[MAX_LIFE] = {};
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;

//=============================================================================
//+ ライフのコンストラクタ
//=============================================================================
CLife::CLife() :CScene(OBJ_DRAW::DRAW_UI)
{
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		m_apGauge[nCnt] = NULL;
	}

}
//=============================================================================
//+ ライフのデストラクタ
//=============================================================================
CLife::~CLife()
{

}
//=============================================================================
//+ ライフの生成処理
//=============================================================================
CLife *CLife::Create(void)
{
	CLife *pLife = NULL;

	if (pLife == NULL)
	{
		pLife = new CLife;
		pLife->Init();
	}

	return pLife;
}

//=============================================================================
//+ 数字・ナンバーのTexの必要分読み込み
//=============================================================================
HRESULT CLife::Load(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture);

	return S_OK;
}
//=============================================================================
//+ ライフのTexを他の処理による削除をさせない
//=============================================================================
void CLife::UnLoad(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//+ ライフの初期化処理
//=============================================================================
HRESULT CLife::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apGauge[nCnt] = new CGauge;
		m_apGauge[nCnt]->Init();
		m_apGauge[nCnt]->SetSize(LIFE_SIZE_X, LIFE_SIZE_Y);
		m_apGauge[nCnt]->SetPos(D3DXVECTOR3(LIFE_POS_X, LIFE_POS_Y, 0.0f), LIFE_SPACE, nCnt);
		
	}
	return S_OK;
}
//=============================================================================
//+ ライフの終了処理
//=============================================================================
void CLife::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apGauge[nCnt]->Uninit();
		m_apGauge[nCnt] = NULL;
	}
	//自分自身をdelete	<Scene>のdelete処理を使用
	Release();
}
//=============================================================================
//+ ライフの更新処理
//=============================================================================
void CLife::Update(void)
{
	
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apGauge[nCnt]->Update();
		m_apGauge[nCnt]->SetNumber(m_nLifeGauge[nCnt]);//カウント分間隔をあける
	}
}
//=============================================================================
//+ ライフの描画処理
//=============================================================================
void CLife::Draw(void)
{
	
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	for (int nCnt = 0; nCnt < m_nLife; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apGauge[nCnt]->Draw();
	}
}

void CLife::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//通常表示背景(サイズ変化、回転なし,各.cppでサイズの書き換え可)
	pVtx[0].pos = D3DXVECTOR3(-100, -100, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+100, -100, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-100, +100, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(+100, +100, 0.0f) + m_pos;


	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

void CLife::SetLife(int nLife)
{
	m_nLife = nLife;
	
}