//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// ライフ処理 [CBloodGauge.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "game.h"
#include "bloodGauge.h"
#include "gauge.h"
#include "manager.h"
#include "player.h"

//マクロ
#define BlOOD_SIZE_X	(40)
#define BlOOD_SIZE_Y	(20)
#define BlOOD_SPACE		(30)
#define BlOOD_POS_X	(45)
#define BlOOD_POS_Y	(SCREEN_HEIGHT-27)

//読み込むテクスチャ↓
#define TEXTURE_NAME01	("DATA\\PLAYER_BLOOD.png")
//静的メンバ変数
int CBloodGauge::m_nBlood = 0;
int CBloodGauge::m_nBloodGauge[MAX_BLOOD] = {};
LPDIRECT3DTEXTURE9 CBloodGauge::m_pTexture = NULL;

//! =============================================================================
//! コンストラクタ
//! =============================================================================
CBloodGauge::CBloodGauge() :CScene(OBJ_DRAW::DRAW_UI)
{
	for (int nCnt = 0; nCnt < MAX_BLOOD; nCnt++)
	{
		m_apGauge[nCnt] = NULL;
	}

}
//! =============================================================================
//! デストラクタ
//! =============================================================================
CBloodGauge::~CBloodGauge()
{

}
//! =============================================================================
//! 生成処理
//! =============================================================================
CBloodGauge *CBloodGauge::Create(void)
{
	CBloodGauge *pLife = NULL;

	if (pLife == NULL)
	{
		pLife = new CBloodGauge;
		pLife->Init();
	}

	return pLife;
}

//! =============================================================================
//! Tex読み混込み
//! =============================================================================
HRESULT CBloodGauge::Load(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture);

	return S_OK;
}
//! =============================================================================
//! Texの破棄
//! =============================================================================
void CBloodGauge::UnLoad(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//! =============================================================================
//!　初期化
//! =============================================================================
HRESULT CBloodGauge::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_BLOOD; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apGauge[nCnt] = new CGauge;
		m_apGauge[nCnt]->Init();
		m_apGauge[nCnt]->SetSize(BlOOD_SIZE_X, BlOOD_SIZE_Y);
		m_apGauge[nCnt]->SetPos(D3DXVECTOR3(BlOOD_POS_X, BlOOD_POS_Y, 0.0f), BlOOD_SPACE, nCnt);
		
	}
	return S_OK;
}
//! =============================================================================
//! 終了
//! =============================================================================
void CBloodGauge::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BLOOD; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apGauge[nCnt]->Uninit();
		m_apGauge[nCnt] = NULL;
	}
	//自分自身をdelete	<Scene>のdelete処理を使用
	Release();
}
//! =============================================================================
//! 更新
//! =============================================================================
void CBloodGauge::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_BLOOD; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apGauge[nCnt]->Update();
		m_apGauge[nCnt]->SetNumber(m_nBloodGauge[nCnt]);//カウント分間隔をあける
	}
}
//! =============================================================================
//! 描画
//! =============================================================================
void CBloodGauge::Draw(void)
{

	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	CPlayer *pPlayer = CGame::GetPlayer();
	m_nBlood = pPlayer->GetBloodLife();

	//血液ゲージ上限を超えない
	if (m_nBlood >= 16)
	{
		m_nBlood = 15;
	}
	

	for (int nCnt = 0; nCnt < m_nBlood; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apGauge[nCnt]->Draw();
	}
}

//! =============================================================================
//! pos / 位置更新
//! =============================================================================

void CBloodGauge::SetPos(D3DXVECTOR3 pos)
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