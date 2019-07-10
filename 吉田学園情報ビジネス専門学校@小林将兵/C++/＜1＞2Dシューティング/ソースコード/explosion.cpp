//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 爆発エフェクト処理 [explosion.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"

//マクロ
//読み込むテクスチャ↓
#define TEXTURE_NAME01	("DATA\\explosion000.png")
//爆発のサイズ↓
#define B_SIZE_H	(50.0f)//縦サイズ
#define B_SIZE_W	(50.0f)//横サイズ
//爆発のアニメーション設定↓
#define	EX_ANIM_SPEED	(5)//アニメーション速さ
#define	EX_ANIM_W	(8)//横分割
#define	EX_ANIM_H	(1)//縦分割

//静的メンバ変数
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;
//! =============================================================================
//! コンストラクタ
//! =============================================================================
CExplosion::CExplosion():CScene2D(OBJ_DRAW::DRAW_EXPLOSION)
{
	m_CntAnim = 0;//アニメーションの速さ
	m_PatternAnim = 0;//アニメーションの分割数
}

//! =============================================================================
//! デストラクタ
//! =============================================================================
CExplosion::~CExplosion()
{

}

//! =============================================================================
//! Tex読み込み
//! =============================================================================
HRESULT CExplosion::Load(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture);

	return S_OK;
}
//! =============================================================================
//!　Tex破棄
//! =============================================================================
void CExplosion::UnLoad(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//! =============================================================================
//!　生成
//! =============================================================================
#if 1
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{

	CExplosion *pExplosion = NULL;
	if (pExplosion == NULL)
	{
		pExplosion = new CExplosion;
		pExplosion->Init();
		pExplosion->SetSize(B_SIZE_H, B_SIZE_W);//弾のサイズ
		pExplosion->SetPos(pos);////プレイヤーの移動情報(変更・更新)が入る
		pExplosion->BindTexture(m_pTexture);
	}
	return pExplosion;
}
#endif

//! =============================================================================
//! 初期化
//! =============================================================================
HRESULT CExplosion::Init(void)
{
	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_EXPLOSION);//タイプを当てはめる
	m_CntAnim = 0;//アニメーションの速さ
	m_PatternAnim = 0;//アニメーションの分割数
	return S_OK;
}

//! =============================================================================
//! 終了
//! =============================================================================
void CExplosion::Uninit(void)
{

	CScene2D::Uninit();
}

//! =============================================================================
//! 更新
//! =============================================================================
void CExplosion::Update(void)
{
	m_CntAnim++; //カウンターの加算 爆発の速度
	if (m_CntAnim % EX_ANIM_SPEED == 0)
	{
		m_PatternAnim = (m_PatternAnim + 1) % (EX_ANIM_W * EX_ANIM_H);//パターンNo.更新
	}

	CScene2D::SetTexAnim(EX_ANIM_SPEED, EX_ANIM_W, EX_ANIM_H, m_PatternAnim);

	if (m_PatternAnim >= (EX_ANIM_W * EX_ANIM_H) - 1)
	{
		//使用した弾を消す
		CScene2D::Uninit();
	}
	
}

//! =============================================================================
//! 描画
//! =============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}