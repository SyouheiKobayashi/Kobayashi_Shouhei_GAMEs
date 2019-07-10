//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// プレイヤー処理 [player.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "manager.h"
#include "input.h"
#include "game.h"
#include "sound.h"
#include "UI.h"
#include "life.h"
#include "bloodGauge.h"
#include "player.h"
#include "bullet.h"
#include "action.h"
#include "time.h"
#include "explosion.h"

//マクロ
//読み込むテクスチャ↓
#define TEXTURE_NAME01	("DATA\\TEX\\player_Anim01.png")
//プレイヤーのサイズ↓
#define P_SIZE_H	(45)//縦サイズ
#define P_SIZE_W	(45)//横サイズ
//弾・バレットのアニメーション設定↓
#define	P_ANIM_SPEED	(12)//アニメーション速さ
#define	P_ANIM_W	(4)//横分割
#define	P_ANIM_H	(1)//縦分割

//静的メンバ変数
CAction *CPlayer::m_pAction = NULL;
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
//=============================================================================
//+ プレイヤーのコンストラクタ
//=============================================================================
CPlayer::CPlayer() :CScene2D(OBJ_DRAW::DRAW_PLAYER)
{
	m_Move = D3DXVECTOR3(8.0f,8.0f,0.0f);
	m_CntAnim = 0;//アニメーションの速さ
	m_PatternAnim = 0;//アニメーションの分割数
	m_nBloodLife = 0;
	m_nActionPos = 0;

	m_nActionMode = CURE;
	m_bUse01 = false;
	m_bUse02 = false;
	m_bUse03 = false;
	m_bTimeCheck = false;
}

//=============================================================================
//+ プレイヤーのデストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}
//=============================================================================
//+ プレイヤーの必要分読み込み
//=============================================================================
HRESULT CPlayer::Load(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture);

	return S_OK;
}
//=============================================================================
//+ プレイヤーを他の処理による削除をさせない
//=============================================================================
void CPlayer::UnLoad(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//+ プレイヤーの生成処理
//=============================================================================
#if 1
CPlayer *CPlayer::Create(float fWIDTH, float fHEIGHT, int nLife)
{
	CPlayer *pPlayer = NULL;
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
		pPlayer->Init();
		pPlayer->BindTexture(m_pTexture);
		pPlayer->SetSize(P_SIZE_H, P_SIZE_W);//プレイヤーのサイズ
		pPlayer->SetPos(D3DXVECTOR3(150.0f, 250.0f, 0.0f));//プレイヤー初期位置
		pPlayer->SetLife(nLife);

	
		//cLifeのライフ設定処理
		CLife * pLife = CGame::GetLife();
		pLife->SetLife(nLife);

	}
	return pPlayer;
}
#endif

//=============================================================================
//+ プレイヤーの初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	CScene2D::Init();
	m_Move = D3DXVECTOR3(8.0f, 8.0f, 0.0f);
	SetObjType(CScene::OBJTYPE_PLAYER);//タイプを当てはめる
	m_CntAnim = 0;//アニメーションの速さ
	m_PatternAnim = 0;//アニメーションの分割数
	m_nActionPos = 0;
	return S_OK;
}

//=============================================================================
//+ プレイヤーの終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
	
}

//=============================================================================
//+ プレイヤーの更新処理
//=============================================================================
void CPlayer::Update(void)
{
	CScene2D::Update();
	
	
	int nLife = 0;

	CTime *pTime = CGame::GetTime();
	int nTimeNow = pTime->GetTimeNow();

	//キーボードを使用するための処理↓
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//ゲームパッド呼び
	CInputXPad *pInputXPad = CManager::GetInputXPad();

	CSound *pSound = CManager::GetSound();
	//プレイヤーの移動処理を行うための処理↓
	D3DXVECTOR3 pos = CScene2D::GetPos();

	
	
	bool bPlayerFlag = pTime->GetPlayerFlag();
	if (bPlayerFlag == true)
	{

		//! <プレイヤーの移動処理>
		if (pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || pInputKeyboard->GetPress(DIK_W) == true)
		{
			pos.y -= m_Move.y;
			if (pos.y < 25)
			{
				pos.y = 25;
			}
		}
		
		if (pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true || pInputKeyboard->GetPress(DIK_S) == true)
		{
			pos.y += m_Move.y;
			if (SCREEN_HEIGHT - 120 < pos.y)
			{
				pos.y = SCREEN_HEIGHT - 120;
			}

		}
		if (pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == true || pInputKeyboard->GetPress(DIK_A) == true)
		{
			pos.x -= m_Move.x;
			if (pos.x <= 25)
			{
				pos.x = 25;
			}
		}
		if (pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true || pInputKeyboard->GetPress(DIK_D) == true)
		{
			pos.x += m_Move.x;
			if (SCREEN_WIDTH-25< pos.x)
			{
				pos.x = SCREEN_WIDTH-25;
			}

		}

		//プレイヤーの移動情報(変更・更新)の処理↓
		CScene2D::SetPos(pos);

		//! <プレイヤーのアニメーション処理>
		m_CntAnim++; //カウンターの加算 爆発の速度
		if (m_CntAnim % P_ANIM_SPEED == 0)
		{
			m_PatternAnim = (m_PatternAnim + 1) % (P_ANIM_W * P_ANIM_H);//パターンNo.更新
		}

		CScene2D::SetTexAnim(P_ANIM_SPEED, P_ANIM_W, P_ANIM_H, m_PatternAnim);

		if (m_PatternAnim >= (P_ANIM_W * P_ANIM_H) - 1)
		{
			m_PatternAnim = 0;
		}

		//! <プレイヤーの弾の発射処理>
		if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true || pInputKeyboard->GetTrigger(DIK_SPACE) == true)
		{
				//弾の生成(bullet処理の呼び出し)//(生成位置,弾のサイズ,タイプの判別,使用Texの番号)
				CBullet::Create(pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), 10, CScene::OBJTYPE_PLAYER, CBullet::TYPE::PLAYER, 0, CBullet::PATTERN_PLAYER);
				CBullet::Create(pos + D3DXVECTOR3(0.0f, -20.0f, 0.0f), 10, CScene::OBJTYPE_PLAYER, CBullet::TYPE::PLAYER, 0, CBullet::PATTERN_PLAYER);
				pSound->PlaySound(CSound::SOUND_BULLET_SE);
			
		}

		//技の選択処理
		if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER, 0) == true || pInputKeyboard->GetTrigger(DIK_E) == true)
		{
			pSound->PlaySound(CSound::SOUND_SWITCH_SE);
				m_nActionMode += 1;
				if (m_nActionMode > SICKLE)
				{
					m_nActionMode = CURE;
				}
			
		}
		if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_LEFT_SHOULDER, 0) == true || pInputKeyboard->GetTrigger(DIK_Q) == true)
		{
			pSound->PlaySound(CSound::SOUND_SWITCH_SE);
				m_nActionMode -= 1;
				if (m_nActionMode < CURE)
				{
					m_nActionMode = SICKLE;
				}
		}

		//回復
		if (m_nBloodLife >= 3)//血液ゲージが3以上である...
		{
			m_bUse01 = true;//使える状態に
		}
		else if (m_nBloodLife < 3)
		{
			m_bUse01 = false;//使えない状態に
		}

		//時間
		if (m_nBloodLife >= 5)//血液ゲージが5以上である...
		{
			m_bUse02 = true;//使える状態に
		}
		else if (m_nBloodLife < 5)
		{
			m_bUse02 = false;//使えない状態に
		}

		//攻撃
		if (m_nBloodLife >= 10)//血液ゲージが10以上である...
		{
			m_bUse03 = true;//使える状態に

		}
		else if (m_nBloodLife < 10)
		{
			m_bUse03 = false;//使えない状態に
		}
		if (m_nBloodLife >= 15)//血液ゲージが10以上である...
		{
			m_nBloodLife = 15;//使える状態に
		}

		if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_Y, 0) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			{
				//<回復技>を使う条件...
				if (m_nActionMode == CURE)//条件の一致...
				{
					if (m_nBloodLife >= 3)//血液ゲージが3以上である...
					{
						if (m_bUse01 == true)
						{
							int NumAll = CScene::GetNumAll();//総数の獲得
							for (int nCntP = 0; nCntP < OBJ_DRAW::DRAW_ALL; nCntP++)//描画総数分回す
							{
								for (int nCnt = 0; nCnt < NumAll; nCnt++)//総数分回す
								{
									CScene *pScene;
									pScene = CScene::GetScene(nCntP, nCnt);//全シーン情報の取得

									if (pScene != NULL)
									{
										CScene::OBJ_TYPE ObjType;
										ObjType = pScene->GetObjType();//タイプ情報の取得


										if (ObjType == OBJ_TYPE::OBJTYPE_PLAYER)//タイプがプレイヤーなら...
										{
											CScene2D *pPlayer = (CScene2D*)pScene;//CScene2Dの持っている情報が欲しいのでキャスト
											nLife = pPlayer->GetLife();//プレイヤーのライフを取得

											nLife += 3;//プレイヤーのライフに値を加算する
											pSound->PlaySound(CSound::SOUND_ACTION_SE01);
											if (nLife >= 15)//もし最大ライフ以上の回復をした場合
											{
												nLife = 15;//上限越えを防ぐ
											}

											CLife *pLife = CGame::GetLife();//ライフゲージ(描画情報)に使用するための情報取得
											pLife->SetLife(nLife);//描画情報の反映
											pPlayer->SetLife(nLife);//プレイヤーのライフに反映
										}
									}
								}
							}

							m_nBloodLife -= 3;
						}
					}
				}

				//<時間増加>を使う条件...
				if (m_nActionMode == ADD_TIME)//条件の一致...
				{
					if (m_nBloodLife >= 5)//血液ゲージが3以上である...
					{
						if (m_bUse02 == true)
						{
							if (nTimeNow > (1 * 100))
							{
								nTimeNow += (10 * 100);
								pTime->SetLife(nTimeNow);
								pSound->PlaySound(CSound::SOUND_ACTION_SE02);
								m_nBloodLife -= 5;

							}
						}
					}
				}

				//<攻撃技>を使う条件...
				if (m_nActionMode == SICKLE)//数値が一致している
				{
					if (m_nBloodLife >= 10)//血液ゲージが10以上である...
					{
						if (m_bUse03 == true)
						{
							//アクションの生成(action処理の呼び出し)//(生成位置,弾のサイズ,タイプの判別,使用Texの番号)
							CAction::Create(pos + D3DXVECTOR3(0.0f, -250.0f, 0.0f), CScene::OBJTYPE_PLAYER);
							
							pSound->PlaySound(CSound::SOUND_ACTION_SE03);
							m_nBloodLife -= 10;
						}
					}
				}
			}
		}

	}
}

//=============================================================================
//+ プレイヤーの描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//血液情報の更新
void CPlayer::SetBloodLife(int nSetBloodLife)
{
	m_nBloodLife = nSetBloodLife;
	this;//ブレイク時の値の確認に便利
}
