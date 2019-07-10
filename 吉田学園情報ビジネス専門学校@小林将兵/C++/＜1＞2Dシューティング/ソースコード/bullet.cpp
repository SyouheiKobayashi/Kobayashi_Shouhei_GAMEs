//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 弾・バレット処理 [bullet.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "manager.h"
#include "input.h"
#include "game.h"
#include "sound.h"
#include "player.h"
#include "bullet.h"
#include "effect.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "bloodGauge.h"
#include "fade.h"
#include "pause.h"

//マクロ
//読み込むテクスチャ↓
#define TEXTURE_NAME01	("DATA\\bullet001.png")
#define TEXTURE_NAME02	("DATA\\star00.png")
//弾・バレットのサイズ↓
#define B_SIZE_H	(10.0f)
#define B_SIZE_W	(10.0f)
//弾・バレットの速度↓
#define PB_SPEED	(10.0f)
#define EB_SPEED	(-10.0f)

//静的メンバ変数
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_B_TEX] = {};
//! =============================================================================
//! コンストラクタ
//! =============================================================================
CBullet::CBullet() :CScene2D(OBJ_DRAW::DRAW_BULLET)
{
	m_BulletType = OBJTYPE_NONE;
	m_nRType = NONE;
	m_nBulletPattern = PATTERN01;

	m_PlayerPos = D3DXVECTOR3(0,0,0);
	m_EnemyPos = D3DXVECTOR3(0, 0, 0);
}

//! =============================================================================
//! デストラクタ
//! =============================================================================
CBullet::~CBullet()
{

}

//! =============================================================================
//! 読み込み
//! =============================================================================
HRESULT CBullet::Load(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME02, &m_pTexture[1]);

	return S_OK;
}
//! =============================================================================
//! Tex破棄
//! =============================================================================
void CBullet::UnLoad(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_B_TEX; nCnt++)
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
CBullet *CBullet::Create(D3DXVECTOR3 pos,int size, OBJ_TYPE ObjType, TYPE type,int nTexType, BULLET_PATTERN pattern)
{

	CBullet *pBullet = NULL;
	if (pBullet == NULL)
	{
		pBullet = new CBullet;
		pBullet->Init(pattern);
		pBullet->SetBulletType(ObjType, type);//弾のタイプ分け
		pBullet->SetSize(B_SIZE_H+ size, B_SIZE_W + size);//弾のサイズ
		pBullet->SetPos(pos);////プレイヤーの移動情報(変更・更新)が入る
		pBullet->BindTexture(m_pTexture[nTexType]);
		pBullet->m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	return pBullet;
}
#endif

//! =============================================================================
//! 初期化
//! =============================================================================
HRESULT CBullet::Init(BULLET_PATTERN pattern)
{
	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_BULLET);//タイプを当てはめる
	//m_nRType = NONE;
	m_bPause = false;

	/*CEnemy *pEnemyType = CGame::GetEnemy();
	m_nBulletPattern = pEnemyType->GetEnemyType();*/

	m_nBulletPattern = pattern;

	m_PlayerPos = D3DXVECTOR3(0, 0, 0);
	m_EnemyPos = D3DXVECTOR3(0, 0, 0);

	return S_OK;
}

//! =============================================================================
//! 終了
//! =============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();

}
//! =============================================================================
//! 更新
//! =============================================================================
void CBullet::Update(void)
{
	CScene2D::Update();
	int nLife = 0;
	int nBloodLife = 0;
	
	CSound *pSound = CManager::GetSound();
	D3DXVECTOR3 pos = CScene2D::GetPos();//プレイヤーの位置を取得
	

//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// プレイヤーの弾であるなら↓
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
	if(m_BulletType == CScene::OBJTYPE_PLAYER)
	{
	
		if (m_nBulletPattern == PATTERN_PLAYER)
		{
			m_move.x = 10.0f;
			pos += m_move;//取得した位置に移動量を加算する
			CScene2D::SetPos(pos);//弾の移動を反映する

			CEffect::Create(pos + D3DXVECTOR3(0.0f, 3.0f, 0.0f), D3DXCOLOR(0.5f, 0.0f, 0.7f, 1.0f));
			CEffect::Create(pos + D3DXVECTOR3(0.0f, -3.0f, 0.0f), D3DXCOLOR(0.5f, 0.0f, 0.7f, 1.0f));
		}
		//! 弾の画面外処理↓
		if (SCREEN_WIDTH < pos.x)
		{
			CScene2D::Uninit();
		}
	}

//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 敵の弾であるなら↓
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
	if (m_BulletType == CScene::OBJTYPE_ENEMY)
	{
		if (m_nBulletPattern == PATTERN01)//一直線
		{
			m_move.x = -12;
			pos += m_move;//取得した位置に移動量を加算する
		}
		if (m_nBulletPattern == PATTERN02)//ほぼ一直線
		{
			m_move.x = -12;
			m_move.y = -2 + (float)(rand() % 4);
			pos += m_move;//取得した位置に移動量を加算する
		}

		if (m_nBulletPattern == PATTERN03)
		{
			m_move.x = -10.0f;
			m_move.y = 7.0f;
			pos += m_move;//取得した位置に移動量を加算する
		}

		if (m_nBulletPattern == PATTERN04)
		{
			m_move.x = -10.0f;
			m_move.y = -7.0f;
			pos += m_move;//取得した位置に移動量を加算する
		}
		
		if (m_nBulletPattern == PATTERN05)//上からの攻撃
		{
			m_move.x = -2.0f;
			m_move.y = 10.0f;
			pos += m_move;//取得した位置に移動量を加算する
			CEffect::Create(pos + D3DXVECTOR3(2.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}

		if (m_nBulletPattern == PATTERN06)
		{
			m_move.x = (-15.0f+(rand() % -3));
			
			pos += m_move;//取得した位置に移動量を加算する
		}
		if (m_nBulletPattern == PATTERN07)
		{
			m_move.x = (+15.0f + (rand() % -3));

			pos += m_move;//取得した位置に移動量を加算する
		}

		if (m_nBulletPattern == PATTERN08)
		{
			m_move.x = -15;
			m_move.y = -1 + (float)(rand() % -6);

			pos += m_move;//取得した位置に移動量を加算する
		}
		if (m_nBulletPattern == PATTERN09)
		{
			m_move.x = -15;
			m_move.y = 1 + (float)(rand() % 6);

			pos += m_move;//取得した位置に移動量を加算する
		}
		CScene2D::SetPos(pos);//弾移動反映
							  //! *この処理より先に弾を消す処理をしない！！

		//画面外処理					  
		if (pos.x < 0)
		{
			
			CScene2D::Uninit();
		}
		else if (pos.y < 0|| SCREEN_HEIGHT < pos.y)
		{
			CScene2D::Uninit();
		}
		
	}

//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 当たり判定処理
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

	//↓obj総数の獲得&&使えるようにローカルに情報を与える
	int NumAll = CScene::GetNumAll();

	for (int nCntP = 0; nCntP < OBJ_DRAW::DRAW_ALL; nCntP++)//用意されたobj分forを回す
	{
		for (int nCnt = 0; nCnt < NumAll; nCnt++)//用意されたobj分forを回す
		{
			CScene *pScene;
			pScene = CScene::GetScene(nCntP, nCnt);

			if (pScene != NULL)
			{
				CScene::OBJ_TYPE ObjType;
				ObjType = pScene->GetObjType();//タイプの確認

				//! 自機とのあたり判定
				if (ObjType == OBJ_TYPE::OBJTYPE_PLAYER)//プレイヤーobjなら
				{
					CScene2D *pPlayer = (CScene2D*)pScene;//CScene2DのGetPosを使えるようにキャスト(変換)する
					D3DXVECTOR3 PlayerPos = pPlayer->GetPos();//敵の位置を取得
					nLife = pPlayer->GetLife();//プレイヤーの体力を取得


					if (PlayerPos.x - B_SIZE_W*2.0f < pos.x && pos.x < PlayerPos.x + B_SIZE_W*2.0f
						&& PlayerPos.y - B_SIZE_H*4.0f < pos.y&& pos.y < PlayerPos.y + B_SIZE_H*4.0f)
					{
						if (m_BulletType == OBJ_TYPE::OBJTYPE_ENEMY&&m_nRType == ENEMY)//! 敵の弾であれば
						{
							CExplosion::Create(PlayerPos);//自機の位置で爆発アニメーション
							pSound->PlaySound(CSound::SOUND_DAMAGE_SE);
							nLife -= 1;//減らす
							CLife *pLife = CGame::GetLife();//プレイヤーのライフ情報取得
							pLife->SetLife(nLife);



							if (nLife <= 0)
							{
								nLife = 0;
								//pScene->Uninit();//そして消す
								//pSound->PlaySound(CSound::SOUND_DELETE_SE);
								pPlayer->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

							}

							this->Release();//自分自身(弾)を消す
							pPlayer->SetLife(nLife);
						}
					}

				}

				//! 敵とのあたり判定
				if (ObjType == OBJ_TYPE::OBJTYPE_ENEMY)//敵objなら
				{
					CScene2D *pEnemy = (CScene2D*)pScene;//CScene2DのGetPosを使えるようにキャスト(変換)する
					D3DXVECTOR3 EnemyPos = pEnemy->GetPos();//敵の位置を取得
					nLife = pEnemy->GetLife();//敵の体力を取得


					CPlayer *pPlayer = CGame::GetPlayer();
					nBloodLife = pPlayer->GetBloodLife();


					//! 範囲
					if (EnemyPos.x - B_SIZE_W*3.0f < pos.x && pos.x < EnemyPos.x + B_SIZE_W*3.0f
						&& EnemyPos.y - B_SIZE_H*5.0f < pos.y&& pos.y < EnemyPos.y + B_SIZE_H*5.0f)
					{
						if (m_BulletType == OBJ_TYPE::OBJTYPE_PLAYER &&m_nRType == PLAYER)//! 自機の弾であれば
						{
							CExplosion::Create(EnemyPos);//敵の位置で爆発アニメーション

							pSound->PlaySound(CSound::SOUND_DAMAGE_SE);
							nLife -= 1;//減らす
							if (nLife <= 0)
							{
								CScore *pScore = CGame::GetScore();
								pScore->AddScore(800);
								nBloodLife += 2;
								pSound->PlaySound(CSound::SOUND_DELETE_SE);
								pEnemy->Uninit();
							}


							this->Release();//弾を消す

							pEnemy->SetLife(nLife);
							pPlayer->SetBloodLife(nBloodLife);
						}
					}

				}
			}
		}
	}

	
}

//! =============================================================================
//! 描画
//! =============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//! =============================================================================
//! 弾を打つキャラ / 使用Tex番号
//! =============================================================================
void CBullet::SetBulletType(OBJ_TYPE ObjType, TYPE type)
{
	m_BulletType = ObjType;
	m_nRType = type;
}
