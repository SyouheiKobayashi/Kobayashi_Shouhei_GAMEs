//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// アクション処理 [action.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "manager.h"
#include "input.h"
#include "game.h"
#include "player.h"
#include "action.h"
#include "bullet.h"
#include "effect.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "bloodGauge.h"

//マクロ
//読み込むテクスチャ↓
#define TEXTURE_NAME01	("DATA\\鎌02.png")
//アクションのサイズ↓
#define B_SIZE_H	(10.0f)
#define B_SIZE_W	(10.0f)
//アクションの速度↓
#define PB_SPEED	(10.0f)
#define EB_SPEED	(-10.0f)

//静的メンバ変数
LPDIRECT3DTEXTURE9 CAction::m_pTexture[ACTION_TEX] = {};
//! =============================================================================
//! コンストラクタ
//! =============================================================================
CAction::CAction() :CScene2D(OBJ_DRAW::DRAW_BULLET)
{
	m_ActionType = OBJTYPE_NONE;

	m_nActionTime = 0;

	 m_fAngle = (D3DX_PI);//角度
	 m_fActionAngle = 0.0f;//鎌が自機に対して動く角度
}
//! =============================================================================
//! デストラクタ
//! =============================================================================
CAction::~CAction()
{

}

//! =============================================================================
//! Tex読み込み
//! =============================================================================
HRESULT CAction::Load(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture[0]);

	return S_OK;
}
//! =============================================================================
//! 使用Texの破棄
//! =============================================================================
void CAction::UnLoad(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < ACTION_TEX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//! =============================================================================
//! 生成処理
//! =============================================================================
#if 1
CAction *CAction::Create(D3DXVECTOR3 pos,OBJ_TYPE ObjType)
{

	CAction *pAction = NULL;
	if (pAction == NULL)
	{
		pAction = new CAction;
		pAction->Init();
		pAction->SetBulletType(ObjType);//弾のタイプ分け
		pAction->SetSize(B_SIZE_H+500, B_SIZE_W+500 );//弾のサイズ
		pAction->SetPos(pos);////プレイヤーの移動情報(変更・更新)が入る
		pAction->BindTexture(m_pTexture[0]);
		pAction->m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pAction->m_fRange = 300;//円の大きさ
		pAction->m_fActionAngle = 10.01f;
	}
	
	return pAction;
}
#endif

//! =============================================================================
//! 初期化
//! =============================================================================
HRESULT CAction::Init(void)
{
	CScene2D::Init();
	//SetObjType(CScene::OBJTYPE_BULLET);//タイプを当てはめる

	m_nActionTime = 0;

	return S_OK;
}
//! =============================================================================
//! 終了
//! =============================================================================
void CAction::Uninit(void)
{
	CScene2D::Uninit();

}
//! =============================================================================
//! 更新
//! =============================================================================
void CAction::Update(void)
{
	CScene2D::Update();
	int nLife = 0;
	int nBloodLife = 0;


	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();//プレイヤーの位置を取得
	D3DXVECTOR3 SicklePos = CAction::GetPos();//鎌の位置を取得

	//D3DXVECTOR3 EnemyBulletPos = CEnemy::GetBullet()->GetPos();

	m_nActionTime += 1;//表示時間の加算
	m_fActionAngle += 0.18f;//弧を描く(円移動)速さ

	SicklePos.x = m_fRange*(float)sin(m_fAngle - m_fActionAngle) + (PlayerPos.x);
	SicklePos.y = m_fRange*(float)cos(m_fAngle - m_fActionAngle) + (PlayerPos.y);

	//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
	// プレイヤーの弾であるなら↓
	//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
	if (m_ActionType == CScene::OBJTYPE_PLAYER)
	{

		SicklePos += m_move;//取得した位置に移動量を加算する
		CScene2D::SetPos(SicklePos);//弾の移動を反映する
		CScene2D::SetRot(-0.2f);
		/*CEffect::Create(SicklePos + D3DXVECTOR3(0.0f, 30.0f, 0.0f), D3DXCOLOR(0.5f, 0.0f, 0.7f, 1.0f));
		CEffect::Create(SicklePos + D3DXVECTOR3(0.0f, -30.0f, 0.0f), D3DXCOLOR(0.5f, 0.0f, 0.7f, 1.0f));*/


		//! 弾の画面外処理↓
		if (SCREEN_WIDTH < PlayerPos.x)
		{
			//CExplosion::Create(pos);
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

				//! 敵とのあたり判定
				if (ObjType == OBJ_TYPE::OBJTYPE_ENEMY)//敵objなら
				{
					CScene2D *pEnemy = (CScene2D*)pScene;//CScene2DのGetPosを使えるようにキャスト(変換)する
					D3DXVECTOR3 EnemyPos = pEnemy->GetPos();//敵の位置を取得
					nLife = pEnemy->GetLife();//敵の体力を取得

					CPlayer *pPlayer = CGame::GetPlayer();
					nBloodLife = pPlayer->GetBloodLife();

					//! 技の範囲内に入ったら...
					if (EnemyPos.x - B_SIZE_W*25.0f < SicklePos.x && SicklePos.x < EnemyPos.x + B_SIZE_W*10.0f
						&& EnemyPos.y - B_SIZE_H*10.0f < SicklePos.y&& SicklePos.y < EnemyPos.y + B_SIZE_H*10.0f)
					{
						if (m_ActionType == OBJ_TYPE::OBJTYPE_PLAYER)//! 自機の技であれば
						{
							nLife -= 100;//減らす

							if (nLife <= 0)
							{
								CScore *pScore = CGame::GetScore();
								pScore->AddScore(100);
								nBloodLife += 1;
								CExplosion::Create(EnemyPos);//敵の位置で爆発アニメーション
								pScene->Uninit();//そして消す
							}

							pEnemy->SetLife(nLife);
							pPlayer->SetBloodLife(nBloodLife);
						}
					}
				}

				//! 弾とのあたり判定
				CScene2D *pScene2D = (CScene2D*)pScene;//Scene2Dにキャスト
				CBullet *pBullet = (CBullet*)pScene2D;//Bulletにキャスト
				int nB = pBullet->GetType();
				if (ObjType == OBJ_TYPE::OBJTYPE_BULLET)//敵objなら
				{
					CScene2D *pBullet = (CScene2D*)pScene;//CScene2DのGetPosを使えるようにキャスト(変換)する
					D3DXVECTOR3 BulletPos = pBullet->GetPos();//弾の位置を取得


					//! 技の範囲内に入ったら...
					if (BulletPos.x - B_SIZE_W*25.0f < SicklePos.x && SicklePos.x < BulletPos.x + B_SIZE_W*10.0f
						&& BulletPos.y - B_SIZE_H*10.0f < SicklePos.y&& SicklePos.y < BulletPos.y + B_SIZE_H*10.0f)
					{
						if (nB == CBullet::TYPE::ENEMY)
						{
							if (m_ActionType == OBJ_TYPE::OBJTYPE_PLAYER)//! 自機の技であれば
							{
								CScore *pScore = CGame::GetScore();
								pScore->AddScore(234);
								pBullet->Uninit();
							}
						}

					}

				}

			}
		}
	}

	if (45 <= m_nActionTime)
	{
		this->Uninit();//自分自身(弾)を消す(↑のif分に入れると貫通弾もどき)
	}
}

//! =============================================================================
//! 描画
//! =============================================================================
void CAction::Draw(void)
{
	CScene2D::Draw();
}

//! =============================================================================
//! 弾の種類判別処理
//! =============================================================================
void CAction::SetBulletType(OBJ_TYPE ObjType)
{
	m_ActionType = ObjType;
}
