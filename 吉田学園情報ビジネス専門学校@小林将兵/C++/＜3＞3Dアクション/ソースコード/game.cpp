//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//							ゲーム処理 [game.h]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "game.h"
#include "fade.h"
#include "debugLog.h"
#include "sound.h"
#include "light.h"
#include "camera.h"
#include "scene2D.h"
#include "polygon2D.h"
#include "scene3D.h"
#include "polygon3D.h"
#include "bullet.h"
#include "particle.h"
#include "number.h"
#include "score.h"
#include "time.h"
#include "stencilShadow.h"
#include "object.h"
#include "player.h"
#include "enemy.h"

//=====================================================================
//							静的メンバ変数
//=====================================================================
CDebug *CGame::m_pDebug = NULL;
CSound *CGame::m_pSound = NULL;
CLight *CGame::m_pLight = NULL;
CCamera *CGame::m_pCamera = NULL;
CScene2D *CGame::m_pScene2D = NULL;
CPolygon2D *CGame::m_pPolygon2D[POLYGON2D_TEX_GAME] = {};
CScene3D *CGame::m_pScene3D[SCENE3D_CREATE] = {};
CPolygon3D *CGame::m_pPolygon3D[POLYGON3D_CREATE] = {};
CBullet *CGame::m_pBullet = NULL;
CParticle3D *CGame::m_pParticle3D = NULL;
CNumber *CGame::m_pNumber = NULL;
CScore *CGame::m_pScore = NULL;
CTime *CGame::m_pTime = NULL;
CStencilShadow *CGame::m_pStencilShadow = NULL;
CObject *CGame::m_pObject[OBJ_CREATE] = {};
CPlayer *CGame::m_pPlayer = NULL;
CEnemy *CGame::m_pEnemy[ENEMY_CREATE] = {};
int CGame::m_nStageCnt = STAGE_01;
int CGame::m_nSwitchFlagNum = 0;
bool CGame::m_bDivided = false;
bool CGame::m_bDivided02 = false;
bool CGame::m_bPageStop = false;
bool CGame::m_bDeath = false;
//==============================================
//					コンストラクタ
//==============================================
CGame::CGame()
{

}

//==============================================
//					デストラクタ
//==============================================
CGame::~CGame()
{

}

//==============================================
//						生成
//==============================================
CGame *CGame::Create()
{
	CGame *pGame = NULL;

	if (pGame == NULL)
	{
		pGame = new CGame;
		pGame->Init();
	}

	return pGame;
}
//==============================================
//					初期化
//==============================================
HRESULT CGame::Init(void)
{
	m_nDebugCnt = 0;
	m_bDeath = false;
	m_nFadeTime = 0;
	m_bPageStop = false;
	m_nPageCnt = 0;
	m_bDivided02 = false;
	m_bDivided = false;
	m_BulletTime = 0;;
	m_fBillCnt = 0.0f;
	m_nSwitchFlagNum = 0;
	bNextStage = false;

	//最大ステージ以上またはそれ以外であれば数値を0に(ステージ01にもどす)
	if (m_nStageCnt < STAGE_01 || STAGE_MAX <= m_nStageCnt)
	{
		m_nStageCnt = STAGE_01;
	}

	NullCheck();				//使用するデータを一度NULLにする
	BulkLoadData();				//使用したモデルとテクスチャの解放
	MAP_LOAD();					//マップ情報の読み込み
	CreateData();				//読み込んだ情報をもとにobjの生成

	//ステージによってBGMを変える
	m_pSound = CManager::GetSound();
	if (m_pSound != NULL)
	{
		if (m_nStageCnt == STAGE_01)
		{
			m_pSound->PlaySound(CSound::BGM_SOUND_GAME01);
		}
		if (m_nStageCnt == STAGE_02)
		{
			m_pSound->PlaySound(CSound::BGM_SOUND_GAME02);
		}
		if (m_nStageCnt == STAGE_03)
		{
			m_pSound->PlaySound(CSound::BGM_SOUND_GAME03);
		}
	}
	return S_OK;
}
//==============================================
//						終了
//==============================================
void CGame::Uninit(void)
{
	CManager::SetChargeTime(m_pTime->GetTime() / 100);

	if (m_pSound != NULL)
	{
		m_pSound->StopSound();
	}

	BulkUnLoadData();			//使用したモデルとテクスチャの解放

	if (m_pTime != NULL)//タイム
	{
		m_pTime = NULL;			
	}
	if (m_pScore != NULL)//スコア
	{
		m_pScore = NULL;		
	}

	if (m_pCamera != NULL)//カメラ
	{
		m_pCamera->Uninit();	
	}
	if (m_pLight != NULL)//ライト
	{
		m_pLight->Uninit();		
	}
	if (m_pDebug != NULL)//デバック
	{
		m_pDebug->Uninit();		
	}

	//使用したデータ・メモリをすべて開放
	CScene::ReleaseAll();
}
//==============================================
//					更新
//==============================================
void CGame::Update(void)
{
	//キーボード・コントローラーの取得処理
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	
	m_pFade = CFade::GetFade();	//フェード

	if (m_pLight != NULL)//ライト
	{
		m_pLight->Update();		
	}
	if (m_pCamera != NULL)//カメラ
	{
		m_pCamera->Update();	
	}

	SwitchFlag();		//スイッチを全て起動したら
	GameModeCheck();	//次のステージに進むか、それともリザルトか
	EventStage01();		//ステージ01用イベント
	EventStage02();		//ステージ02用イベント
	EventStage03();		//ステージ03用イベント

	if (m_pPolygon3D[1] != NULL)//敵のアイコン表示
	{
		if (m_pEnemy[0] != NULL)
		{
			m_pPolygon3D[1]->SetPos(D3DXVECTOR3(m_pEnemy[0]->GetPos().x / 2.0f, m_pEnemy[0]->GetPos().y + 40, m_pEnemy[0]->GetPos().z));
			if (m_pEnemy[0]->GetSearchCheck() == true && m_pEnemy[0]->GetMoveStop() == false)//見つかった状態なら
			{
				m_pPolygon3D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (m_pEnemy[0]->GetSearchCheck() == false || m_pEnemy[0]->GetMoveStop() == true)//見つかっていない状態 / 踏まれた状態
			{
				m_pPolygon3D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
		}
	}

	
	
#ifdef _DEBUG
	Debug();					//デバック操作用
	//DebugLoop();
#endif
}

//==============================================
//					描画
//==============================================
void CGame::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();//カメラ描画
	}

}

//==============================================
//				スイッチを何個押したのか
//==============================================
void CGame::SetSwitchFlagNum()
{
	m_nSwitchFlagNum += 1;
}

//==============================================
//		用意されたスイッチが全て起動されたら
//==============================================
void CGame::SwitchFlag()
{
	if (m_nSwitchFlagNum == CObject::GetSwitchNum())
	{
		if (m_pPolygon2D[1] != NULL)
		{
			m_pPolygon2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		bNextStage = true;//次のステージへ行ける
		if (m_pPolygon3D[0] == NULL)//3Dテクスチャ
		{
			if (m_pSound != NULL)
			{
				m_pSound->PlaySound(CSound::SE_GATE);//ゲートが開かれた音
			}
			//ゲート
			if (m_nStageCnt == STAGE_01)
			{
				m_pPolygon3D[0] = CPolygon3D::Create(1, D3DXVECTOR3(180.0f, 50.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, 4, 4, true);
			}
			if (m_nStageCnt == STAGE_02)
			{
				m_pPolygon3D[0] = CPolygon3D::Create(1, D3DXVECTOR3(940.0f, 50.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, 4, 4, true);
			}
			if (m_nStageCnt == STAGE_03)
			{
				m_pPolygon3D[0] = CPolygon3D::Create(1, D3DXVECTOR3(395.0f, 50.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, 4, 4, true);
			}

		}
	}
}

//==============================================
//		次のステージに進むか、それともリザルトか
//==============================================
void CGame::GameModeCheck(void)
{
	if (m_pTime->GetTime() <= 0)//ライフ兼制限時間が0になったら
	{
		m_bDeath = true;//死亡状態
		m_nFadeTime++;

		if (m_pPolygon3D[5] == NULL)//爆発ポリゴン
		{
			m_pPolygon3D[5] = CPolygon3D::Create(10, D3DXVECTOR3(m_pPlayer->GetPos().x/2, m_pPlayer->GetPos().y/2+20.0f, -30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(120.0f, 120.0f, 0.0f), 6, 3, 2, false);
		}

		if (m_nFadeTime >= 80)
		{
			if (m_pFade == CFade::FADE_NONE)
			{
				m_nStageCnt = STAGE_01;
				CManager::SetResult(false);
				CManager::GetFade()->SetFade(CManager::MODE_RESULT);
			}
		}
	}

	if (bNextStage == true && m_pPlayer->GetPos().z >= 30)//次のステージに行ける状態 / プレイヤーがある一定の位置に来たら
	{
		if (m_pFade == CFade::FADE_NONE)
		{
			m_nStageCnt += 1;//終わるたびに加算、読み込むステージを変えていく

			if (m_nStageCnt <= STAGE_MAX - 1)
			{
				CManager::SetChargeTime(m_pTime->GetTime() / 100);//次のステージへ時間を引継ぐ
				CManager::GetFade()->SetFade(CManager::MODE_GAME);
			}
			else//最後のステージなら
			{
				m_nStageCnt = STAGE_01;
				CManager::SetResult(true);
				CManager::GetFade()->SetFade(CManager::MODE_RESULT);

			}
		}
	}
}

//==============================================
//					01イベント
//==============================================
void CGame::EventStage01()
{
	if (m_nStageCnt == STAGE_01)
	{
		//チュートリアル画面の表示
		if (m_pInputKeyboard->GetPress(DIK_SPACE) == true || m_pInputKeyboard->GetPress(DIK_RETURN) == true ||
			m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
		{
			m_nPageCnt += 1;
			if (m_nPageCnt == 1)
			{
				m_pPolygon2D[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_pPolygon2D[6]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			if (m_nPageCnt == 2)
			{
				m_pPolygon2D[6]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_bPageStop = true;
			}
		}
	}
	else
	{
		m_bPageStop = true;

	}

}

//==============================================
//					02イベント
//==============================================
void CGame::EventStage02()
{
	// @   @   @   @   @   @   @   @   @   @   @   @
	//					バレット類の生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_nStageCnt == STAGE_02)
	{
		if (m_pEnemy[1] != NULL)
		{
			m_BulletTime++;
			if (m_BulletTime % 60 == 0 && m_pEnemy[1]->GetPos().z >= 0.0f)//生成時間 / 指定場所以外では生成しない
			{
				CBullet::Create(80,D3DXVECTOR3(m_pEnemy[1]->GetPos().x / 2.0f, (m_pEnemy[1]->GetPos().y - m_pEnemy[1]->GetPos().y / 2.0f) + 15.0f, m_pEnemy[1]->GetPos().z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), 0, 5, 4, 3, true);
			}
			//横風
			if (m_BulletTime % 80 == 0 && m_pPlayer->GetPos().z >= 200.0f)//生成時間 / 指定場所以外では生成しない
			{
				CBullet::Create(120,D3DXVECTOR3(400.0f, (rand() % 20) + 30.0f, 120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 1, 1, 1, 1, true);
			}
		}
	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					煙突の煙の生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_nStageCnt == STAGE_02)
	{
		CParticle3D::Create(D3DXVECTOR3(940.0f, 320.0f, 100.0f),//位置
			D3DXVECTOR3((rand() % 20 - 10)*0.08f, (rand() % 20 + 1)*0.1f, (rand() % 20 - 10)*0.08f),//移動量
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, 30, 0.5f, 2);//カラー 回転 生存時間 大きさ
	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				Z軸移動の風ポリゴン
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_nStageCnt == STAGE_02)
	{
		if (m_pPolygon3D[4] != NULL)
		{
			D3DXVECTOR3 pos = m_pPolygon3D[4]->GetPos();
			pos.x = 45.0f;
			pos.y += 0.7f;
			pos.z += 1.0f;
			m_pPolygon3D[4]->SetPos(pos);
			if (m_pPolygon3D[4]->GetPos().z >= 100.0f)
			{
				D3DXCOLOR col = m_pPolygon3D[4]->GetCol();
				col.a -= 0.03f;
				m_pPolygon3D[4]->SetCol(col);
				if (m_pPolygon3D[4]->GetPos().z >= 200.0f)
				{
					m_pPolygon3D[4]->SetPos(D3DXVECTOR3(45.0f, 20.0f, -30.0f));
				}
			}
			else
			{
				m_pPolygon3D[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
			}
		}
	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					分かれ道
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_nStageCnt == STAGE_02)//分かれ道処理
	{
		if (m_pPlayer->GetPos().x >= 80.0f && m_pPlayer->GetPos().x <= 150.0f)//この範囲にプレイヤーが入ったら
		{
			if (m_bDivided == false && m_pPlayer->GetPos().z <= 0)
			{//アイコンの表示
				m_pPolygon3D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (m_bDivided == true)
			{//アイコンの非表示
				m_pPolygon3D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
			if (m_pInputKeyboard->GetPress(DIK_W) == true ||
				m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 0) == true)
			{
				m_bDivided = true;//Z軸の道を選ばれた

			}
			if (m_bDivided == true && m_pPlayer->GetPos().z >= 220.0f)//どこまで進めるのか
			{
				m_bDivided = false;
			}
		}
		else//アイコンの非表示
		{
			m_pPolygon3D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}

		//戻り道
		if (m_pPlayer->GetPos().x >= 730 && m_pPlayer->GetPos().x <= 800)//この範囲に入ったら
		{
			if (m_bDivided02 == false && m_pPlayer->GetPos().z >= 200.0f)
			{//アイコンの表示
				m_pPolygon3D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			if (m_bDivided02 == true)
			{//アイコンの非表示
				m_pPolygon3D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
			if (m_pInputKeyboard->GetPress(DIK_S) == true ||
				m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true || m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true)
			{
				m_bDivided02 = true;//Z軸の道を選ばれた
			}
			if (m_bDivided02 == true && m_pPlayer->GetPos().z <= 0.0f)//どこまで進めるのか
			{
				m_bDivided02 = false;
			}
		}
		else
		{//アイコンの非表示
			m_pPolygon3D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
}

//==============================================
//					03イベント
//==============================================
void CGame::EventStage03()
{
	// @   @   @   @   @   @   @   @   @   @   @   @
	//				ステージ外にでたら
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_pPlayer != NULL)
	{
		if (m_pPlayer->GetOutStage() == true)
		{//割れガラスの2Dポリを表示
			m_pPolygon2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{//表示後徐々に薄く
			D3DXCOLOR col = m_pPolygon2D[0]->GetCol();
			col.a -= 0.05f;
			m_pPolygon2D[0]->SetCol(col);
		}
	}
}
//==============================================
//				NULLチェック
//==============================================
void CGame::NullCheck(void)
{
	if (m_pDebug != NULL)
	{
		m_pDebug = NULL;		//デバック
	}
	if (m_pLight != NULL)
	{
		m_pLight = NULL;		//ライト
	}
	if (m_pCamera != NULL)
	{
		m_pCamera = NULL;		//カメラ
	}

	if (m_pScene2D != NULL)
	{
		m_pScene2D = NULL;		//シーン2D
	}
	for (int nCnt = 0; nCnt < POLYGON2D_TEX_GAME; nCnt++)
	{
		if (m_pPolygon2D[nCnt] != NULL)
		{
			m_pPolygon2D[nCnt] = NULL;	//ポリゴン2D
		}
	}
	for (int nCnt = 0; nCnt < SCENE3D_CREATE; nCnt++)
	{
		if (m_pScene3D[nCnt] != NULL)
		{
			m_pScene3D[nCnt] = NULL;		//シーン3D
		}
	}
	
	for (int nCnt = 0; nCnt < POLYGON3D_CREATE; nCnt++)
	{
		if (m_pPolygon3D[nCnt] != NULL)
		{
			m_pPolygon3D[nCnt] = NULL;	//ポリゴン3D
		}
	}
	if (m_pBullet != NULL)
	{
		m_pBullet = NULL;
	}
	if (m_pStencilShadow != NULL)
	{
		m_pStencilShadow = NULL;	//ステンシルシャドウ
	}

	for (int nCnt = 0; nCnt < m_nMaxObjCreateNum; nCnt++)
	{
		if (m_pObject[nCnt] != NULL)
		{
			m_pObject[nCnt] = NULL;	//オブジェクト
		}
	}

	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;		//プレイヤー
	}
	for (int nCnt = 0; nCnt < ENEMY_CREATE; nCnt++)
	{
		if (m_pEnemy[nCnt] != NULL)
		{
			m_pEnemy[nCnt] = NULL;		//エネミー
		}
	}
}

//==============================================
//				　Load処理(読み込み)
//==============================================
void CGame::BulkLoadData(void)
{
	CPolygon2D::TextureLoad();
	CPolygon3D::TextureLoad();
	CBullet::TextureLoad();
	CParticle3D::TextureLoad();
	CNumber::TextureLoad();
	CStencilShadow::ObjectLoad();
	CObject::ObjectLoad();
	CObject::TextureLoad();
	CPlayer::ModelLoad();
	CPlayer::TextureLoad();
	CEnemy::ModelLoad();
	CEnemy::TextureLoad();

}

//==============================================
//				　UnLoad処理(解放)
//==============================================
void CGame::BulkUnLoadData(void)
{
	CEnemy::TextureUnLoad();
	CEnemy::ModelUnLoad();
	CPlayer::TextureUnLoad();
	CPlayer::ModelUnLoad();
	CObject::TextureUnLoad();
	CObject::ObjectUnLoad();
	CStencilShadow::ObjectUnLoad();
	CNumber::TextureUnLoad();
	CParticle3D::TextureUnLoad();
	CBullet::TextureUnLoad();
	CPolygon3D::TextureUnLoad();
	CPolygon2D::TextureUnLoad();
}

//==============================================
//					生成処理
//==============================================
void CGame::CreateData(void)
{
	if (m_pDebug == NULL)//デバック
	{
		m_pDebug = CDebug::Create();
	}
	if (m_pLight == NULL)//ライト
	{
		m_pLight = CLight::Create();
	}
	if (m_pCamera == NULL)//カメラ
	{
		m_pCamera = CCamera::Create();
	}

	if (m_pScene2D == NULL)//シーン2D
	{
		m_pScene2D = CScene2D::Create();
	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					2Dテクスチャ
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_pPolygon2D[0] == NULL)
	{
		m_pPolygon2D[7] = CPolygon2D::Create(16, false, D3DXVECTOR3(640.0f, 650.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 640.0f, 45.0f, 1, 1, 1, true);
		m_pPolygon2D[0] = CPolygon2D::Create(11, false, D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 640.0f, 360.0f, 1, 1, 1, true);
		m_pPolygon2D[1] = CPolygon2D::Create(17, false, D3DXVECTOR3(640.0f, 650.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 640.0f, 45.0f, 1, 1, 1, true);
		m_pPolygon2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		//操作アイコン
		m_pPolygon2D[2] = CPolygon2D::Create(18, false, D3DXVECTOR3(1000.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150.0f, 70.0f, 6, 2, 1, true);
		m_pPolygon2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pPolygon2D[3] = CPolygon2D::Create(19, false, D3DXVECTOR3(1000.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150.0f, 70.0f, 6, 2, 1, true);
		m_pPolygon2D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pPolygon2D[4] = CPolygon2D::Create(20, false, D3DXVECTOR3(1000.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150.0f, 70.0f, 6, 2, 1, true);
		m_pPolygon2D[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		CPolygon2D::Create(21, false, D3DXVECTOR3(220.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200.0f, 80.0f, 1, 1, 1, true);

	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					斜め判定
	// @   @   @   @   @   @   @   @   @   @   @   @

	if (m_nStageCnt == STAGE_02)
	{
		if (m_pScene3D[0] == NULL)
		{
			m_pScene3D[0] = CScene3D::Create(D3DXVECTOR3(350.0f, 14.0, 0.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f), 75.0f, -100.0f, 75.0f, -100.0f);

		}
		if (m_pScene3D[1] == NULL)
		{
			m_pScene3D[1] = CScene3D::Create(D3DXVECTOR3(570.0f, 125.0, 0.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f), 0.0f, 85.0f, 0.0f, 85.0f);
		}

		if (m_pScene3D[2] == NULL)
		{
			m_pScene3D[2] = CScene3D::Create(D3DXVECTOR3(765.0f, 35.0, 0.0f), D3DXVECTOR3(110.0f, 0.0f, 100.0f), 165.0f, -40.0f, 165.0f, -40.0f);
		}
	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					3Dポリゴン
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_pPolygon3D[1] == NULL)
	{
		m_pPolygon3D[1] = CPolygon3D::Create(6, D3DXVECTOR3(70.0f, 40.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 1, 1, 1, true);
		m_pPolygon3D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pPolygon3D[2] = CPolygon3D::Create(7, D3DXVECTOR3(50.0f, 40.0f, 0.0f), D3DXVECTOR3(0.5f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 1, 1, 1, true);
		m_pPolygon3D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pPolygon3D[3] = CPolygon3D::Create(8, D3DXVECTOR3(380.0f, 80.0f, 100.0f), D3DXVECTOR3(0.5f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 1, 1, 1, true);
		m_pPolygon3D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		if (m_nStageCnt == STAGE_02)
		{
			m_pPolygon3D[4] = CPolygon3D::Create(9, D3DXVECTOR3(45.0f, 20.0f, -30.0f), D3DXVECTOR3(1.5f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 1, 1, 1, true);
			m_pPolygon3D[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
		}

	}

	//背景用
	if (m_nStageCnt == STAGE_01)
	{
		CPolygon3D::Create(2, D3DXVECTOR3(50.0f, 50.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(2, D3DXVECTOR3(450.0f, 50.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(2, D3DXVECTOR3(-100.0f, 50.0f, 150.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(200.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(2, D3DXVECTOR3(620.0f, 50.0f, 620.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(200.0f, 300.0f, 0.0f), 1, 1, 1, true);
	}
	if (m_nStageCnt == STAGE_02)
	{
		CPolygon3D::Create(3, D3DXVECTOR3(50.0f, 140.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(3, D3DXVECTOR3(450.0f, 140.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(3, D3DXVECTOR3(850.0f, 140.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(3, D3DXVECTOR3(1250.0f, 140.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(3, D3DXVECTOR3(-100.0f, 140.0f, 150.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(3, D3DXVECTOR3(1160.0f, 140.0f, 1160.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
	}
	if (m_nStageCnt == STAGE_03)
	{
		CPolygon3D::Create(4, D3DXVECTOR3(50.0f, 140.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(4, D3DXVECTOR3(450.0f, 140.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(4, D3DXVECTOR3(850.0f, 140.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(4, D3DXVECTOR3(1250.0f, 140.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(4, D3DXVECTOR3(1650.0f, 140.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
		CPolygon3D::Create(4, D3DXVECTOR3(-100.0f, 140.0f, 150.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 1, 1, 1, true);
	}

	if (m_pTime == NULL)//タイム
	{	//マネージャが時間を管理している
		int nTime = CManager::GetChargeTime();
		if (nTime <= 0 && m_nStageCnt == STAGE_01)//時間の加算行為がされなければ...
		{
			nTime = DEFAULT_TIME;
		}
		m_pTime = CTime::Create(nTime, D3DXVECTOR2(40.0f, 40.0f), D3DXVECTOR2(147.0f, 92.0f));
	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				2Dテクスチャ(優先描画)
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_pPolygon2D[5] == NULL)//2Dテクスチャ
	{
		if (m_nStageCnt == STAGE_01)
		{
			m_pPolygon2D[5] = CPolygon2D::Create(25, false, D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 600.0f, 300.0f, 6, 2, 1, true);
			m_pPolygon2D[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pPolygon2D[6] = CPolygon2D::Create(26, false, D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 600.0f, 300.0f, 6, 2, 1, true);
			m_pPolygon2D[6]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}

	//ステンシルシャドウ
	if (m_pStencilShadow == NULL)
	{
		m_pStencilShadow = CStencilShadow::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}


	//外部から読み込んだオブジェクト情報をもとに生成
	for (int nCnt = 0; nCnt < m_nMaxObjCreateNum; nCnt++)
	{
		m_pObject[nCnt] = CObject::Create(m_nObjType[nCnt], m_nTexType[nCnt],
			D3DXVECTOR3(m_ObjOffseet[nCnt].fPosX, m_ObjOffseet[nCnt].fPosY, m_ObjOffseet[nCnt].fPosZ),
			D3DXVECTOR3(m_ObjOffseet[nCnt].fRotX, m_ObjOffseet[nCnt].fRotY, m_ObjOffseet[nCnt].fRotZ));
	}

	if (m_pPlayer == NULL)//プレイヤー
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(-100.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					敵の配置
	// @   @   @   @   @   @   @   @   @   @   @   @
	if (m_nStageCnt == STAGE_01)
	{
		if (m_pEnemy[0] == NULL)
		{
			m_pEnemy[0] = CEnemy::Create(0, D3DXVECTOR3(80.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}
	if (m_nStageCnt == STAGE_02)
	{
		if (m_pEnemy[0] == NULL)
		{
			//m_pEnemy[0] = CEnemy::Create(0, D3DXVECTOR3(80.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		if (m_pEnemy[1] == NULL)
		{
			m_pEnemy[1] = CEnemy::Create(1, D3DXVECTOR3(550.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/2, 0.0f));
		}
	}
	if (m_nStageCnt == STAGE_03)
	{
		if (m_pEnemy[0] == NULL)
		{
			m_pEnemy[0] = CEnemy::Create(0,D3DXVECTOR3(140.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}
}

//==============================================
//				デバック用処理
//==============================================
void  CGame::Debug(void)
{
	CDebug::DebugLog("STAGEナンバー %d", m_nStageCnt);
	CDebug::DebugLog("\nGimmickフラグ数 %d", m_nSwitchFlagNum);
	CDebug::DebugLog("\nGimmick生成フラグ数 %d", CObject::GetSwitchNum());

}

void  CGame::DebugLoop(void)
{
	m_nDebugCnt++;
	if (m_nDebugCnt >= 50)
	{
		if (m_pFade == CFade::FADE_NONE)
		{
			m_nStageCnt += 1;//終わるたびに加算、読み込むステージを変えていく

			if (m_nStageCnt <= STAGE_MAX - 1)
			{
				CManager::SetChargeTime(m_pTime->GetTime() / 100);//前回のステージの時間を引き継ぐ
				CManager::GetFade()->SetFade(CManager::MODE_GAME);
			}
			else
			{
				m_nStageCnt = STAGE_01;
				CManager::GetFade()->SetFade(CManager::MODE_RESULT);

			}
		}
	}

}
//==============================================
//		外部データからマップ情報の読み込み
//==============================================
void CGame::MAP_LOAD(void)
{
	char * pStrCur;	//先頭文字列のポインタ
	char aLine[256];//文字列の読み込み
	char aStr[256];	//文字列の抜き出し
	int nCnt = 0;
	int nWord;

	//外部テキストの読み込み
	if (m_nStageCnt == STAGE_01)
	{
		m_pFile = fopen("DATA\\TEXT\\STAGE01.txt", "r");
	}
	if (m_nStageCnt == STAGE_02)
	{
		m_pFile = fopen("DATA\\TEXT\\STAGE02.txt", "r");
	}
	if (m_nStageCnt == STAGE_03)
	{
		m_pFile = fopen("DATA\\TEXT\\STAGE03.txt", "r");
	}


	if (m_pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(m_pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "OBJ_CREATE_LOAD", strlen("OBJ_CREATE_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, m_pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					//オブジェクトを何個読み込むか
					if (memcmp(pStrCur, "MAX_OBJ_CREATE = ", strlen("MAX_OBJ_CREATE = ")) == 0)
					{
						pStrCur += strlen("MAX_OBJ_CREATE = ");
						strcpy(aStr, pStrCur);
						m_nMaxObjCreateNum = atoi(aStr);
					}
					if (memcmp(pStrCur, "OBJ_SET", strlen("OBJ_SET")) == 0)
					{
						while (1)
						{
							fgets(&aLine[0], 256, m_pFile);
							pStrCur = CSceneX::GetLIneTop(&aLine[0]);

							//使用するオブジェクト番号
							if (memcmp(pStrCur, "OBJ_TYPE = ", strlen("OBJ_TYPE = ")) == 0)
							{
								pStrCur += strlen("OBJ_TYPE = ");
								strcpy(aStr, pStrCur);
								m_nObjType[nCnt] = atoi(aStr);
							}
							//オブジェクトに張り付けるUV番号
							if (memcmp(pStrCur, "TEX_TYPE = ", strlen("TEX_TYPE = ")) == 0)
							{
								pStrCur += strlen("TEX_TYPE = ");

								strcpy(aStr, pStrCur);

								m_nTexType[nCnt] = atoi(aStr);
							}
							//配置する位置
							if (memcmp(pStrCur, "POS =", strlen("POS =")) == 0)
							{

								pStrCur += strlen("POS =");
								strcpy(aStr, pStrCur);

								for (int nCntWord = 0; nCntWord < 3; nCntWord++)
								{
									nWord = CSceneX::PopString(pStrCur, aStr);
									pStrCur += nWord;//読み込み文字位置をずらす
									strcpy(aStr, pStrCur);

									if (nCntWord == 0)//x
									{
										m_ObjOffseet[nCnt].fPosX = (float)atof(aStr);

									}
									else if (nCntWord == 1)//y
									{
										m_ObjOffseet[nCnt].fPosY = (float)atof(aStr);
									}
									else//z
									{
										m_ObjOffseet[nCnt].fPosZ = (float)atof(aStr);
									}
								}
							}
							//向き
							if (memcmp(pStrCur, "ROT =", strlen("ROT =")) == 0)
							{
								pStrCur += strlen("ROT =");
								strcpy(aStr, pStrCur);

								//x,y,z分回す
								for (int nCntWord = 0; nCntWord < 3; nCntWord++)
								{
									nWord = CSceneX::PopString(pStrCur, aStr);
									pStrCur += nWord;//読み込み文字位置をずらす
									strcpy(aStr, pStrCur);

									if (nCntWord == 0)//x
									{
										m_ObjOffseet[nCnt].fRotX = (float)atof(aStr);

									}
									else if (nCntWord == 1)//y
									{
										m_ObjOffseet[nCnt].fRotY = (float)atof(aStr);
									}
									else//z
									{
										m_ObjOffseet[nCnt].fRotZ = (float)atof(aStr);
									}
								}
							}

							//読み込み終了
							if (memcmp(pStrCur, "OBJ_SET_END", strlen("OBJ_SET_END")) == 0)
							{
								nCnt++;
								break;
							}
						}
					}
					//読み込み終了
					if (memcmp(pStrCur, "OBJ_CREATE_LOAD_END", strlen("OBJ_CREATE_LOAD_END")) == 0)
					{
						break;
					}
				}
			}

			//読み込み終了
			if (memcmp(pStrCur, "OBJ_CREATE_LOAD_END", strlen("OBJ_CREATE_LOAD_END")) == 0)
			{
				break;
			}
		}
	}
	fclose(m_pFile);
}




