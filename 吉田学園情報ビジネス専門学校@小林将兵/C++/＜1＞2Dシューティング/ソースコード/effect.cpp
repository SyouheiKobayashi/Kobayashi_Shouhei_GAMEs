//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 爆発エフェクト処理 [effect.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "effect.h"

//マクロ
//読み込むテクスチャ↓
#define TEXTURE_NAME01	("DATA\\effect000.jpg")
//エフェクトのサイズ↓
#define B_SIZE_H	(40.0f)//縦サイズ
#define B_SIZE_W	(80.0f)//横サイズ
//エフェクトのアニメーション設定↓
#define	EX_ANIM_SPEED	(5)//アニメーション速さ
#define	EX_ANIM_W	(8)//横分割
#define	EX_ANIM_H	(1)//縦分割

//静的メンバ変数
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;
//! =============================================================================
//! コンストラクタ
//! =============================================================================
CEffect::CEffect():CScene2D(OBJ_DRAW::DRAW_EFFECT)
{
	
	m_fRadius = 0;			// 半径(大きさ)
	m_nLife = 0;				// 表示時間(寿命)
}

//! =============================================================================
//! デストラクタ
//! =============================================================================
CEffect::~CEffect()
{

}

//! =============================================================================
//! Tex読み込み
//! =============================================================================
HRESULT CEffect::Load(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture);

	return S_OK;
}
//! =============================================================================
//! Tex破棄
//! =============================================================================
void CEffect::UnLoad(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//! =============================================================================
//! 生成
//! =============================================================================
#if 1
CEffect *CEffect::Create(D3DXVECTOR3 pos,D3DXCOLOR col)
{

	CEffect *pEffect = NULL;
	if (pEffect == NULL)
	{
		pEffect = new CEffect;
		pEffect->Init();
		//pEffect->SetSize(B_SIZE_H, B_SIZE_W);//弾のサイズ
		pEffect->BindTexture(m_pTexture);
		pEffect->SetPos(pos);////プレイヤーの移動情報(変更・更新)が入る
		pEffect->SetCol(col);
		//pEffect->SetLife(20);
	}
	return pEffect;
}
#endif

//! =============================================================================
//! 初期化
//! =============================================================================
HRESULT CEffect::Init(void)
{
	CScene2D::Init();

	
	m_fRadius = 20;			// 半径(大きさ)
	SetSize(m_fRadius, m_fRadius);
	m_nLife = 10;				// 表示時間(寿命)

	return S_OK;
}

//! =============================================================================
//! 終了
//! =============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//! =============================================================================
//! 更新
//! =============================================================================
void CEffect::Update(void)
{


	m_fRadius--;
	if (m_fRadius <= 0)
	{
		m_fRadius = 0;
	}
	//頂点座標の設定 / エフェクトポリゴンの中心点を割り出す
	SetSize(m_fRadius, m_fRadius-10);
	m_nLife--;
	if (m_nLife <= 0)
	{
		this->Uninit();//自分自身を消す
	}
}

//! =============================================================================
//! 描画
//! =============================================================================
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		CScene2D::Draw();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}