//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 敵・エネミー処理 [enemy.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "manager.h"
#include "input.h"
#include "enemy.h"
#include "bullet.h"

//マクロ
//読み込むテクスチャ↓
#define ENEMY_TEX01	("DATA\\runningman000.png")
#define ENEMY_TEX02	("DATA\\IMG_0011.png")
#define ENEMY_TEX03	("DATA\\TEX\\enemy\\enemy003.png")
#define ENEMY_TEX04	("DATA\\TEX\\enemy\\enemy000.png")
#define ENEMY_TEX05	("DATA\\TEX\\enemy\\enemy001.png")
#define ENEMY_TEX06	("DATA\\TEX\\enemy\\enemy004.png")
//敵・エネミーのサイズ↓
#define E_SIZE_H	(30)
#define E_SIZE_W	(30)
//弾・バレットのアニメーション設定↓
#define	E_ANIM_SPEED	(5)//アニメーション速さ
#define	E_ANIM_W	(8)//横分割
#define	E_ANIM_H	(1)//縦分割
//敵・エネミーの攻撃間隔↓
#define E_INTERVAL	(70)
//静的メンバ変数
CBullet *CEnemy::m_pBullet = NULL;
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[ENEMY_ALL] = {};

//! =============================================================================
//! コンストラクタ
//! =============================================================================
CEnemy::CEnemy() :CScene2D(OBJ_DRAW::DRAW_ENEMY)
{
	m_CntAnim = 0;//アニメーションの速さ
	m_PatternAnim = 0;//アニメーションの分割数

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	m_nIntervalAttack = 0;

	m_nEnemyType = 0;

	m_nRndPattern = rand() % 3;

	
}

//! =============================================================================
//! デストラクタ
//! =============================================================================
CEnemy::~CEnemy()
{

}

//! =============================================================================
//! Tex読み込み
//! =============================================================================
HRESULT CEnemy::Load(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX01, &m_pTexture[ENEMY01]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX02, &m_pTexture[ENEMY02]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX03, &m_pTexture[ENEMY03]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX04, &m_pTexture[ENEMY04]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX05, &m_pTexture[ENEMY05]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX06, &m_pTexture[ENEMY_BOSS]);

	return S_OK;
}
//! =============================================================================
//!　Tex破棄　
//! =============================================================================
void CEnemy::UnLoad(void)
{
	// テクスチャの破棄
	for (int nCnt = 0;nCnt <ENEMY_ALL;nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

}

//! =============================================================================
//! 生成
//! =============================================================================
#if 1
CEnemy *CEnemy::Create(int nType,int X_pos, int Y_pos, int Life)
{
	CEnemy *pEnemy = NULL;
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;
		pEnemy->Init(nType);
		pEnemy->BindTexture(m_pTexture[nType]);
		pEnemy->SetSize(E_SIZE_H, E_SIZE_W);//敵・エネミーのサイズ
		pEnemy->SetPos(D3DXVECTOR3((float)X_pos, (float)Y_pos, 0.0f));//敵・エネミー初期位置
		pEnemy->SetLife(Life);
	}
	return pEnemy;
}
#endif

//! =============================================================================
//!　初期化
//! =============================================================================
HRESULT CEnemy::Init(int nType)
{
	CScene2D::Init();

	CScene::SetObjType(OBJ_TYPE::OBJTYPE_ENEMY);//タイプを当てはめる
	
	m_CntAnim = 0;//アニメーションの速さ
	m_PatternAnim = 0;//アニメーションの分割数

	//m_move = D3DXVECTOR3(0.0f, -5.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	m_nIntervalAttack = 0;

	m_nEnemyType = nType;

	m_nRndPattern = rand() % 3;

	

	return S_OK;
}

//! =============================================================================
//! 終了
//! =============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//! =============================================================================
//! 更新
//! =============================================================================
void CEnemy::Update(void)
{
	CScene2D::Update();
	EnemyPattern();
	//キーボードを使用するための処理↓
	//cInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//敵・エネミーの位置情報の所得を行うための処理↓
	D3DXVECTOR3 pos = CScene2D::GetPos();

	//! <敵・エネミーのアニメーション処理>
	m_CntAnim++; //カウンターの加算 爆発の速度
	if (m_nEnemyType == 0)
	{
		if (m_CntAnim % E_ANIM_SPEED == 0)
		{
			m_PatternAnim = (m_PatternAnim + 1) % (E_ANIM_W * E_ANIM_H);//パターンNo.更新
		}

		CScene2D::SetTexAnim(E_ANIM_SPEED, E_ANIM_W, E_ANIM_H, m_PatternAnim);

		if (m_PatternAnim >= (E_ANIM_W * E_ANIM_H) - 1)
		{
			m_PatternAnim = 0;
		}
	}
	//! <敵・エネミーの左右移動するだけの処理>
	//pos.y += m_move.y;
	/*if (pos.y <= 0)
	{
		m_move.y = 5.0f;
		pos.y += m_move.y;
	}
	if (SCREEN_HEIGHT <= pos.y)
	{
		m_move.y = -5.0f;
		pos.y += m_move.y;
	}*/


	//倒されず画面外に出た場合...
	if (pos.x < -5)
	{
		
		CScene2D::Uninit();
	}
	else if (pos.y < -90)
	{

		CScene2D::Uninit();
	}
	else if (pos.y > SCREEN_HEIGHT+90)
	{

		CScene2D::Uninit();
	}

#if 1

	//! <敵・エネミーの弾の発射処理>
	
	//if (m_nEnemyType == 0)
	//{
	//	if (m_nIntervalAttack % E_INTERVAL == 0)
	//	{
	//		//弾の生成(bullet処理の呼び出し)//(生成位置,弾のサイズ,タイプの判別,使用Texの番号)
	//		m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1);
	//		//cBullet::Create(pos + D3DXVECTOR3(-20.0f, -15.0f, 0.0f), CScene::OBJTYPE_ENEMY);
	//	}
	//}

	//if (m_nEnemyType == 1)
	//{
	//	if (m_nIntervalAttack % E_INTERVAL-10 == 0)
	//	{
	//		//弾の生成(bullet処理の呼び出し)//(生成位置,弾のサイズ,タイプの判別,使用Texの番号)
	//		m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 7.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1);
	//		m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, -7.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1);
	//	}
	//}
#endif

	
}

//! =============================================================================
//! 描画
//! =============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//! =============================================================================
//! 敵の攻撃 / 移動パターン
//! =============================================================================
void CEnemy::EnemyPattern(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPos();//敵位置取得
	m_nIntervalAttack++;
	

	switch (m_nEnemyType)//タイプの判別
	{
	case ENEMY01:

		pos += D3DXVECTOR3(-5.0f, 0.0f, 0.0f);//移動


		if (m_nIntervalAttack % 60 == 0)//攻撃間隔
		{
			//弾の生成(bullet処理の呼び出し)//(生成位置,弾のサイズ,タイプの判別,使用Texの番号)
			m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN01);
		}
		break;
		//! =============================================================================
	case ENEMY02:

		//移動パターン
		if (m_nRndPattern == 0)//真っすぐ
		{
			pos += D3DXVECTOR3(-8.0f, 0.0f, 0.0f);
			//攻撃間隔
			if (m_nIntervalAttack % 70 == 0)
			{
				//弾の生成(bullet処理の呼び出し)//(生成位置,弾のサイズ,タイプの判別,使用Texの番号)
				m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN02);
			}

		}
		if (m_nRndPattern == 1)//下へ
		{

			pos += D3DXVECTOR3(-8.0f, D3DX_PI, 0.0f);
			//攻撃間隔
			if (m_nIntervalAttack % 70 == 0)
			{
				//弾の生成(bullet処理の呼び出し)//(生成位置,弾のサイズ,タイプの判別,使用Texの番号)
				m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN04);
			}
		}
		if (m_nRndPattern == 2)//上へ
		{
			pos += D3DXVECTOR3(-8.0f, -D3DX_PI, 0.0f);
			//攻撃間隔
			if (m_nIntervalAttack % 70 == 0)
			{
				//弾の生成(bullet処理の呼び出し)//(生成位置,弾のサイズ,タイプの判別,使用Texの番号)
				m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN03);
			}
		}
		
		
		break;
		//! =============================================================================
	case ENEMY03:
		//移動パターン
		
			pos += D3DXVECTOR3(-6.0f, 0.0f, 0.0f);
		//攻撃間隔
		if (m_nIntervalAttack % 80 == 0)
		{
			//弾の生成(bullet処理の呼び出し)//(生成位置,弾のサイズ,タイプの判別,使用Texの番号)
			m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN05);
			//cBullet::Create(pos + D3DXVECTOR3(-20.0f, -15.0f, 0.0f), CScene::OBJTYPE_ENEMY);
		}
		break;

//! =============================================================================
	case ENEMY04:

		pos += D3DXVECTOR3(0.0f, -11.0f, 0.0f);
		//攻撃間隔
		if (m_nIntervalAttack % 10-(rand() % 4) == 0)
		{
			//弾の生成(bullet処理の呼び出し)//(生成位置,弾のサイズ,タイプの判別,使用Texの番号)
			if (210 < pos.x)
			{
				m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN06);
			}
			else
			{
				m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN07);

			}
			//cBullet::Create(pos + D3DXVECTOR3(-20.0f, -15.0f, 0.0f), CScene::OBJTYPE_ENEMY);
		}
		break;
		//! =============================================================================

	case ENEMY05:

		pos += D3DXVECTOR3(-8.0f, 0.0f, 0.0f);
		//攻撃間隔
		if (m_nIntervalAttack % 10 - (rand() % 4) == 0)
		{
			//弾の生成(bullet処理の呼び出し)//(生成位置,弾のサイズ,タイプの判別,使用Texの番号)

			CBullet::Create(pos + D3DXVECTOR3(0.0f, 3.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN08);
			CBullet::Create(pos + D3DXVECTOR3(0.0f, -3.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN09);

		}
		break;
		//! =============================================================================

	case ENEMY_BOSS:

		pos += D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		//攻撃間隔
		if (m_nIntervalAttack % 50 - (rand() % 4) == 0)
		{
			//弾の生成(bullet処理の呼び出し)//(生成位置,弾のサイズ,タイプの判別,使用Texの番号)
			for (int nCnt = 0; nCnt < 30; nCnt++)
			{
				CBullet::Create(pos + D3DXVECTOR3(0.0f, 7.0f - (rand() % 10), 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN08);
				CBullet::Create(pos + D3DXVECTOR3(0.0f, -7.0f + (rand() % 10), 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN09);

			}
			//CBullet::Create(pos + D3DXVECTOR3(0.0f, -3.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN09);

		}
		break;
	}
	

	CScene2D::SetPos(pos);//移動量反映
}
