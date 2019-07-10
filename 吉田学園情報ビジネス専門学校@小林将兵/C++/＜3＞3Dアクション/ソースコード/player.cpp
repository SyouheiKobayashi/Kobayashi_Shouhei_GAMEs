//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					プレイヤー処理 [player.h]
//			Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "manager.h"
#include "debugLog.h"
#include "sound.h"
#include "camera.h"
#include "input.h"
#include "title.h"
#include "timeCharge.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "model.h"
#include "player.h"
#include "enemy.h"
#include "object.h"
#include "scene3D.h"
#include "polygon2D.h"
#include "polygon3D.h"


//==============================================
//				静的メンバ変数
//==============================================
CSound *CPlayer::m_pSound = NULL;
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = {};
LPD3DXMESH CPlayer::m_pMesh[PLAYER_PARTS] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat[PLAYER_PARTS] = {};
DWORD CPlayer::m_pNumMat[PLAYER_PARTS] = {};
int CPlayer::m_nNumParts = NULL;
int CPlayer::m_aIndexParent[PLAYER_PARTS] = {};
CPlayer::KEY CPlayer::m_aKeyOffseet[PLAYER_PARTS] = {};
int CPlayer::m_nNumModel = NULL;
char CPlayer::m_aFileNameModel[PLAYER_PARTS][256] = {};

//==============================================
//					コンストラクタ
//==============================================
CPlayer::CPlayer(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	NULLCheck();//NULLチェック

}
//==============================================
//					デストラクタ
//==============================================
CPlayer::~CPlayer()
{
}

//==============================================
//					生成
//==============================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = NULL;
	CModel *pModel = NULL;

	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
		pPlayer->m_pos = pos;
		pPlayer->m_rot = rot;
		pPlayer->Init();

	}
	return pPlayer;
}
//==============================================
//					初期化処理
//==============================================
HRESULT CPlayer::Init(void)
{
	NULLCheck();//NULLチェック

	ModelLode();//使用するモデルの読み込み
	m_pSound = CManager::GetSound();

	return S_OK;
} 

//==============================================
//					終了処理
//==============================================
void CPlayer::Uninit(void)
{
	if (m_pSound != NULL)
	{
		m_pSound->StopSound();
	}

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		if (m_pModel[nCnt] != NULL)
		{
			m_pModel[nCnt]->Uninit();
			delete m_pModel[nCnt];
			m_pModel[nCnt] = NULL;
		}
	}

	Release();
}

//==============================================
//					更新処理
//==============================================
void CPlayer::Update(void)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)//使用モデル分更新
	{
		m_pModel[nCnt]->Update();
	}
	//キーボード・コントローラーの取得処理
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	m_pInputMouse = CManager::GetInputMouse();

	m_posOld = m_pos;//過去の位置情報を記憶

	CurrentMode();//現在のモードによって情報を変える
	Gravity();	//重力
	MOVE();		//移動
	JUMP();		//ジャンプ
	Polygon3D();
	CollObj();		//オブジェクトの当たり判定
	CollEnemy();	//オブジェクトの当たり判定
	LadderEvent();	//梯子のイベント

	if (m_pos.z <= -230.0f)//ステージ外に出たら
	{
		m_bOutStage = true;
	}
	if (m_bOutStage == true)
	{
		m_nReTime++;
		if (m_nReTime >= 60)
		{
			SetPos(D3DXVECTOR3(1150.0f, 100.0f, 0.0f));
			m_bOutStage = false;
			m_nReTime = 0;
		}
	}

	if (m_pos.z >= 220.0f)
	{
		if (m_pInputKeyboard->GetPress(DIK_D) == false && m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == false &&
			m_pInputKeyboard->GetPress(DIK_A) == false && m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == false&&
			 m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_RIGHT, 0) == false && m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_LEFT, 0) == false)
		{
			motionType = WINDOW_WAIT;
		}
		m_pos.x += -1.0f;
	}

	TitleEvent();

	if (CManager::GetMode() == CManager::MODE_RANKING)//RANKINGのみのモーション
	{
		motionType = RANKING;

	}

	UpdateMotion();//モーションの更新(処理の順番によりほかの処理よりも下に!!)


#ifdef _DEBUG
	Debug();					//デバック操作用
#endif

}

//==============================================
//					描画処理
//==============================================
void CPlayer::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;


	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	if (CGame::GetDeath() == false)
	{
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			m_pModel[nCnt]->Draw();//使用するモデルの描画
		}
	}
}

//==============================================
//			現在のモードによって情報を変える
//==============================================
void CPlayer::CurrentMode(void)
{
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{
		m_pCamera = CTitle::GetCamera();//カメラ情報の取得

	}
	if (CManager::GetMode() == CManager::MODE_CHARGETIME)
	{
		m_pCamera = CTimeCharge::GetCamera();//カメラ情報の取得

	}
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		m_pCamera = CGame::GetCamera();//カメラ情報の取得
	}
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{
		m_pCamera = CResult::GetCamera();//カメラ情報の取得

	}
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{
		m_pCamera = CRanking::GetCamera();//カメラ情報の取得
	}
}
//==============================================
//					重力
//==============================================
void CPlayer::Gravity(void)
{
	if (m_bMeshcheck == false || m_bObjRide[m_nCurrentObj] == false || m_bEnemyRide[m_nCurrentEnemy] == false)//乗っていなかった場合
	{
		if (m_pos.y <= 0)
		{
			m_pos.y = 0;
			m_move.y = 0;
		}
		else
		{
			m_move.y -= PLAYER_GRAVITY;//重力加算
		}
	}

}

//==============================================
//					移動
//==============================================
void CPlayer::MOVE(void)
{
	CGame *pGame = CManager::GetGame();
	CPolygon3D *pPolygon3D = CGame::GetPolygon3D(0);//0にゲート情報がはいっている
	float fRotation = m_pCamera->GetRotation();

	if (CGame::GetDeath() == false)
	{
		if (m_bLadderFlag == true)
		{

			if (m_pInputKeyboard->GetPress(DIK_W) == true ||
				m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 0) == true)
			{
				motionType = WALK;
				m_pos.x += sinf(fRotation) * 0.0f;
				m_pos.z += cosf(fRotation) * 0.0f;
				m_Sabun.y = D3DX_PI + fRotation - m_rot.y;
			}
		}

		//イベントが起きたなら
		if (pGame != NULL&&pPolygon3D != NULL)
		{//範囲内であり次のステージに行ける状態
			CDebug::DebugLog("\npPolygon3D->GetPos().x %.1f,", pPolygon3D->GetPos().x);
			if (pGame->GetNextStage() == true && (pPolygon3D->GetPos().x*2.0f) + 60 > m_pos.x && (pPolygon3D->GetPos().x*2.0f) - 60 < m_pos.x)
			{
				CPolygon2D *pPolygon2D = CGame::GetPolygon2D(3);//「操作」アイコンの表示
				if (pPolygon2D != NULL)
				{
					pPolygon2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				CDebug::DebugLog("\n範囲内");
				if (m_pInputKeyboard->GetPress(DIK_W) == true ||
					m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 0) == true)
				{
					m_bAutoMove = true;//自動でZ軸へ
				}
			}
			else
			{
				CPolygon2D *pPolygon2D = CGame::GetPolygon2D(3);//「操作」アイコンの非表示
				if (pPolygon2D != NULL)
				{
					pPolygon2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				}
			}
		}
		//分かれ道
		if (m_bAutoMove == true || CGame::GetDivided() == true)//次のステージに行く際 / 分かれ道を進むとき
		{
			motionType = WALK;
			m_pos.x += sinf(fRotation) * 1.2f;
			m_pos.z += cosf(fRotation) * 1.2f;
			m_Sabun.y = D3DX_PI + fRotation - m_rot.y;
		}
		if (CGame::GetDivided02() == true)//元の道に戻るとき
		{
			motionType = WALK;
			m_pos.x += sinf(D3DX_PI + fRotation) * PLAYER_SPEED;
			m_pos.z += cosf(D3DX_PI + fRotation) * PLAYER_SPEED;
			m_Sabun.y = fRotation - m_rot.y;
		}

		//イベントでなければ
		if (m_bAutoMove == false && m_bLadderFlag == false && CGame::GetDivided() == false && CGame::GetDivided02() == false)
		{
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				if (CGame::GetPageStop() == true)
				{
					if (m_pInputKeyboard->GetPress(DIK_D) == true ||
						m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true || m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_RIGHT, 0) == true)
					{
						if (m_pos.z >= 220.0f)
						{
							motionType = WINDOW;
						}
						else
						{
							motionType = WALK;
						}
						m_pos.x += sinf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_pos.z += cosf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_Sabun.y = (-D3DX_PI / 2 + fRotation) - m_rot.y;
					}

					if (m_pInputKeyboard->GetPress(DIK_A) == true ||
						m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == true || m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_LEFT, 0) == true)
					{
						motionType = WALK;
						m_pos.x -= sinf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_pos.z -= cosf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_Sabun.y = ((D3DX_PI / 2) + fRotation) - m_rot.y;
					}
				}
			}
		}
	}
	if (m_Sabun.y > D3DX_PI)
	{
		m_Sabun.y -= D3DX_PI * 2;
	}
	else if (m_Sabun.y < -D3DX_PI)
	{
		m_Sabun.y += D3DX_PI * 2;
	}

	m_rot.y += m_Sabun.y * 0.25f;//方向転換の速さ

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}

	m_Sabun.y = 0;

	m_bLoopCheck = false;//モーションループの解除

}

//==============================================
//					ジャンプ
//==============================================
void CPlayer::JUMP(void)
{
	if (CGame::GetDeath() == false)
	{
		if (m_bObjRide[m_nCurrentObj] == true || m_bEnemyRide[m_nCurrentEnemy] == true || /*m_bBlockUpCheck == true|| */m_pos.y <= 0)//地面に触れていたらジャンプ可能
		{
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				if (CGame::GetPageStop() == true)
				{
					if (m_pInputKeyboard->GetTrigger(DIK_SPACE) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
					{
						if (m_pSound != NULL)
						{
							m_pSound->PlaySound(CSound::SE_JUMP);
						}
						m_move.y = PLAYER_JUMP;//ジャンプ加算
					}
					if (m_bAutoJump == true)//敵の上に乗ったら
					{
						m_move.y = PLAYER_JUMP;//ジャンプ加算
						m_bAutoJump = false;
					}
				}
			}
		}
		else if (m_pScene3D != NULL)
		{
			if (m_bScene3DRide == false)
			{
				if (CManager::GetMode() == CManager::MODE_GAME)
				{
					if (m_bPolygon3DCheck[m_nCurrent3DPolygon] == true)
					{
						if (m_pInputKeyboard->GetTrigger(DIK_SPACE) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
						{
							m_bScene3DRide = true;
							if (m_pSound != NULL)
							{
								m_pSound->PlaySound(CSound::SE_JUMP);
							}
							m_move.y = PLAYER_JUMP;//ジャンプ加算
						}
					}


				}
			}
		}
	}
	m_pos.y += m_move.y;
}

//==============================================
//				3Dポリゴンに関する処理
//==============================================
void CPlayer::Polygon3D(void)
{
	for (int nCnt = 0; nCnt < SCENE3D_CREATE; nCnt++)
	{
		m_pScene3D[nCnt] = CGame::GetScene3D(nCnt);
		if (m_pScene3D[nCnt] != NULL)
		{
			m_bPolygon3DCheck[nCnt] = m_pScene3D[nCnt]->GetCheck();
			if (m_bPolygon3DCheck[nCnt] == true)
			{
				m_nCurrent3DPolygon = nCnt;
				if (m_pos.y <= m_pScene3D[m_nCurrent3DPolygon]->GetDotPosY())
				{
					CDebug::DebugLog("\n上上上");
					m_bScene3DRide = false;
					m_pos.y = m_pScene3D[m_nCurrent3DPolygon]->GetDotPosY();//位置の反映
					m_move.y = 0;
				}
			}
		}
	}
}

//==============================================
//				objとの当たり判定
//==============================================
void CPlayer::CollObj(void)
{
	for (int nCnt = 0; nCnt < CObject::GetCreateNum(); nCnt++)
	{
		if (CManager::GetMode() == CManager::MODE_TITLE)
		{
			m_pObj = CTitle::GetObj(nCnt);
		}
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			m_pObj = CGame::GetObj(nCnt);
		}
		if (CManager::GetMode() == CManager::MODE_RANKING)
		{
			m_pObj = CRanking::GetObj(nCnt);
		}
		if (m_pObj != NULL)
		{
			//objの上に乗った場合
			if (m_pObj->Collision(&m_pos, &m_posOld, &m_move, GetDataType()) == true)
			{
				//m_move.y = 0;
				m_bObjRide[nCnt] = true;
				m_nCurrentObj = nCnt;
				m_move.y = 0;
			}
			else
			{
				m_bObjRide[nCnt] = false;
				if (CGame::GetStageCnt() == 2&&nCnt == 12)//例外で上下ブロックのみ常に乗っている状態にしておく
				{
					m_bObjRide[nCnt] = true;
				}

			}

			//objの横の場合
			if (m_pObj->CollSide(&m_pos, &m_posOld, &m_move, GetDataType()) == true)
			{
				m_bObjSide[nCnt] = true;
				m_nCurrentSideObj = nCnt;
			}
			else
			{
				m_bObjSide[nCnt] = false;
			}

			if (m_bDamageState[OBJ] == true)//ダメージを受けたら
			{
				SetDamageAction(0.4f, 0.2f,OBJ);//ダメージ演出処理(どれくらい吹っ飛ぶか)

			}

		}
	}
}

//==============================================
//				エネミーとの当たり判定
//==============================================
void CPlayer::CollEnemy(void)
{
	for (int nCnt = 0; nCnt < CEnemy::GetCreateNum(); nCnt++)
	{
		if (CManager::GetMode() == CManager::MODE_TITLE)
		{
			//m_pEnemy = CTitle::GetEnemy(nCnt);
		}
		if (CManager::GetMode() == CManager::MODE_CHARGETIME)
		{
			//m_pEnemy = CTimeCharge::GetEnemy(nCnt);
		}
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			m_pEnemy = CGame::GetEnemy(nCnt);
		}
		if (CManager::GetMode() == CManager::MODE_RESULT)
		{
			//m_pEnemy = CResult::GetEnemy(nCnt);

		}
		if (CManager::GetMode() == CManager::MODE_RANKING)
		{
			//m_pEnemy = CRanking::GetEnemy(nCnt);
		}
		if (m_pEnemy != NULL)
		{
			if (m_bDamageState[ENEMY] == false)//ダメージを受けてなければ
			{
				//エネミーの上に乗った場合
				if (m_pEnemy->Collision(&m_pos, &m_posOld, &m_move) == true)
				{
					m_bEnemyRide[nCnt] = true;
					m_nCurrentEnemy = nCnt;
					m_bAutoJump = true;
				}
				else
				{
					m_bEnemyRide[nCnt] = false;

				}
			}
			else if (m_bDamageState[ENEMY] == true)//ダメージを受けたら
			{
				SetDamageAction(3.0f,3.0f,ENEMY);//ダメージ演出処理(どれくらい吹っ飛ぶか)
			}
		}
	}
}

//==============================================
//				梯子のイベント
//==============================================
void CPlayer::LadderEvent(void)
{
	if (m_pObj != NULL)
	{
		m_bLadderFlag = m_pObj->GetLadderFlag();
		if (m_bLadderFlag == true)
		{
			motionType = EVENT;
			m_move.y += PLAYER_GRAVITY + 0.05f;
			if (m_pos.y >= 120.0f)
			{
				m_bLoopCheck = false;//モーションループの解除
				m_pos.x += 5.0f;
				if (m_pos.x >= 950.0f)
				{
					m_rot.y = -D3DX_PI / 2;
					m_pObj->SetLadderFlag(false);
				}
			}
		}
	}
}

//==============================================
//				ダメージを受けた際の演出処理
//==============================================
void CPlayer::SetDamageAction(float fX, float fY, int nType)
{
	m_nStateCnt++;

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_pModel[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	}

	if (m_bObjSide[m_nCurrentSideObj] == false&& nType == ENEMY)//壁に触れていないなら&&タイプは敵
	{
		if (m_nKnockBack == LEFT)
		{
			m_pos.x -= fX;
			m_pos.y += fY;
		}
		else if (m_nKnockBack == RIGHT)
		{

			m_pos.x += fX;
			m_pos.y += fY;
		}
	}
	else if(nType == OBJ)//タイプはギミックobj
	{
		if (m_nKnockBack == FRONT)//手前判定
		{

			m_pos.z -= 1.2f;
			m_pos.y += 0.5f;
		}
		if (m_nKnockBack == LEFT)
		{
			m_pos.x -= fX;
			m_pos.y += fY;
		}
		else if (m_nKnockBack == RIGHT)
		{

			m_pos.x += fX;
			m_pos.y += fY;
		}
	}

	//ダメージ表記時間
	if (nType == OBJ)
	{
		if (m_nKnockBack == FRONT)
		{
			if (m_nStateCnt >= 200)
			{
				for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
				{
					m_pModel[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				m_nStateCnt = 0;
				m_bDamageState[OBJ] = false;
			}
		}
		else
		{
			if (m_nStateCnt >= 150)
			{
				for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
				{
					m_pModel[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				m_nStateCnt = 0;
				m_bDamageState[OBJ] = false;
			}
		}
	}
	if(nType == ENEMY)
	{
		if (m_nStateCnt >= 13)
		{
			for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
			{
				m_pModel[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			m_nStateCnt = 0;
			m_bDamageState[ENEMY] = false;
		}
	}
}

//==============================================
//				タイトル時の演出
//==============================================
void CPlayer::TitleEvent(void)
{
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{
		if (m_pInputKeyboard->GetTrigger(DIK_RETURN) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_START, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
		{
			m_bStop = true;
		}
			float fRotation = m_pCamera->GetRotation();
			if (m_bStop == false)
			{
				m_nTitleEventCnt++;//方向の切り替え

				if (m_bTitleEvent == false)//右へ
				{
					motionType = WALK;
					m_pos.x += sinf(D3DX_PI / 2 + fRotation) * m_move.x;
					m_pos.z += cosf(D3DX_PI / 2 + fRotation) * m_move.x;
					m_Sabun.y = (-D3DX_PI / 2 + fRotation) - m_rot.y;

					if (m_nTitleEventCnt >= 320)
					{
						m_bTitleEvent = true;
						m_nTitleEventCnt = 0;
					}
				}

				if (m_bTitleEvent == true)//左へ
				{
					motionType = WALK;
					m_pos.x -= sinf(D3DX_PI / 2 + fRotation) * m_move.x;
					m_pos.z -= cosf(D3DX_PI / 2 + fRotation) * m_move.x;
					m_Sabun.y = ((D3DX_PI / 2) + fRotation) - m_rot.y;
					if (m_nTitleEventCnt % 60 == 0)
					{
						m_move.y = PLAYER_JUMP;//ジャンプ加算
					}
					if (m_nTitleEventCnt >= 320)
					{
						m_bTitleEvent = false;
						m_nTitleEventCnt = 0;
					}
				}
			}
			else if (m_bStop == true)
			{
				motionType = RANKING;
				m_pos.x += sinf(D3DX_PI + fRotation) * 0.0f;
				m_pos.z += cosf(D3DX_PI + fRotation) * 0.0f;
				m_Sabun.y = fRotation - m_rot.y;

			}

			if (m_Sabun.y > D3DX_PI)
			{
				m_Sabun.y -= D3DX_PI * 2;
			}
			else if (m_Sabun.y < -D3DX_PI)
			{
				m_Sabun.y += D3DX_PI * 2;
			}

			m_rot.y += m_Sabun.y * 0.25f;//方向転換の速さ

			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2;
			}
			else if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2;
			}

			m_Sabun.y = 0;

			m_bLoopCheck = false;//モーションループの解除
		
	}
}

//==============================================
//				位置の反映
//==============================================
void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==============================================
//				現在の状態
//==============================================
void CPlayer::SetDamageState(int nType, bool bState)
{
	m_bDamageState[nType] = bState;
}
void CPlayer::SetKnockBack(int nState)
{
	m_nKnockBack = nState;
}

//==============================================
//				一括NULL化 / 初期化
//==============================================
void CPlayer::NULLCheck(void)
{
	m_pCamera = NULL;
	for (int nCnt = 0; nCnt < PLAYER_PARTS; nCnt++)
	{
		m_pModel[nCnt] = NULL;
	}
	m_move = D3DXVECTOR3(PLAYER_SPEED, PLAYER_SPEED, 1.2f);
	m_nKey = 0;
	motionType = NEUTRAL;
	m_nUseMotionType = NEUTRAL;
	m_bLoopCheck = false;
	for (int nCnt = 0; nCnt < SCENE3D_CREATE; nCnt++)
	{
		m_bPolygon3DCheck[nCnt] = false;
	}
	m_bMeshcheck = false;
	for (int nCnt = 0; nCnt < OBJ_CREATE; nCnt++)
	{
		m_bObjRide[nCnt] = false;
	}
	for (int nCnt = 0; nCnt < OBJ_CREATE; nCnt++)
	{
		m_bObjSide[nCnt] = false;
	}

	for (int nCnt = 0; nCnt < ENEMY_CREATE; nCnt++)
	{
		m_bEnemyRide[nCnt] = false;
	}
	m_nCurrent3DPolygon = 0;
	m_nCurrentObj = 0;
	m_nCurrentSideObj = 0;
	m_bScene3DRide = false;
	m_bDamageState[TYPE_MAX] = {};
	m_nStateCnt = 0;
	m_bLadderFlag = false;
	m_bBlockUpCheck = true;
	m_bOutStage = false;
	m_nReTime = 0;
	m_nTitleEventCnt = 0;
	m_bTitleEvent = false;
	m_bStop = false;
	m_bAutoJump = false;
}


//==============================================
//				モデルの読み込み
//==============================================
HRESULT CPlayer::ModelLoad(void)
{
	FILE *pFile;

	char * pStrCur;//先頭文字列のポインタ
	char aLine[256];//文字列の読み込み
	char aStr[256];//文字列の抜き出し
	int nCnt = 0;

	//テキストの読み込み↓
	pFile = fopen("DATA\\TEXT\\PLAYER_LODE.txt", "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "MODEL_LOAD", strlen("MODEL_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					//パーツ数の読み込み
					if (memcmp(pStrCur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
					{
						pStrCur += strlen("NUM_MODEL = ");
						strcpy(aStr, pStrCur);
						m_nNumModel = atoi(aStr);
					}

					if (memcmp(pStrCur, "MODEL_NAME ", strlen("MODEL_NAME ")) == 0)
					{
						pStrCur += strlen("MODEL_NAME ");

						strcpy(aStr, pStrCur);
						while (1)
						{
							if (pStrCur[strlen(pStrCur) - 1] != 'x')
							{
								pStrCur[strlen(pStrCur) - 1] = '\0';//改行文字をNULL文字に変換(参考サイト::http://hisashi.me/blog/?p=714)
							}

							else
							{
								break;
							}

							strcpy(&m_aFileNameModel[nCnt][0], pStrCur);
						}

						nCnt += 1;
					}

					//読み込みの終わり
					if (memcmp(pStrCur, "END_MODEL_LOAD", strlen("END_MODEL_LOAD")) == 0)
					{
						break;
					}
				}

			}
			//読み込みの終わり
			if (memcmp(pStrCur, "END_MODEL_LOAD", strlen("END_MODEL_LOAD")) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);

	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// Xファイルの読み込み
	for (int nCntLoad = 0; nCntLoad < m_nNumModel; nCntLoad++)
	{
		D3DXLoadMeshFromX(m_aFileNameModel[nCntLoad],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCntLoad],
			NULL,
			&m_pNumMat[nCntLoad],
			&m_pMesh[nCntLoad]);
	}

	return S_OK;
}

//==============================================
//					モデルの破棄
//==============================================
void CPlayer::ModelUnLoad(void)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		//マテリアルの数の解放
		if (m_pNumMat[nCnt] != NULL)
		{
			m_pNumMat[nCnt] = NULL;
		}
		//マテリアルの情報の開放
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}
		//メッシュの開放
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
	}
}

//==============================================
//					UV読み込み
//==============================================
HRESULT CPlayer::TextureLoad(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MODEL_UV, &m_pTexture);

	return S_OK;
}

//==============================================
//					UVの破棄
//==============================================
void CPlayer::TextureUnLoad(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//===================================================
//			各モデルの位置、向き、親を決める
//===================================================
void CPlayer::ModelLode(void)
{
	FILE *pFile;
	char * pStrCur;//先頭文字列のポインタ
	char aLine[256];//文字列の読み込み
	char aStr[256];//文字列の抜き出し
	int nCnt = 0;
	int nWord;
	int nParent[PLAYER_PARTS];

	//テキストの読み込み↓
	pFile = fopen("DATA\\TEXT\\PLAYER_LODE.txt", "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "CHARACTERSET", strlen("CHARACTERSET")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					if (memcmp(pStrCur, "PARTSSET", strlen("PARTSSET")) == 0)
					{
						while (1)
						{
							fgets(&aLine[0], 256, pFile);
							pStrCur = CSceneX::GetLIneTop(&aLine[0]);

							//パーツのインデックス(体なら0,頭なら1など)
							if (memcmp(pStrCur, "INDEX = ", strlen("INDEX = ")) == 0)
							{
								pStrCur += strlen("INDEX = ");
								strcpy(aStr, pStrCur);
								m_aIndexParent[nCnt] = atoi(aStr);
							}
							//各パーツの親を決める、知る
							if (memcmp(pStrCur, "PARENT = ", strlen("PARENT = ")) == 0)
							{
								pStrCur += strlen("PARENT = ");

								strcpy(aStr, pStrCur);

								nParent[nCnt] = atoi(aStr);
							}
							//各パーツのPOSの読み込み↓
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
										m_aKeyOffseet[nCnt].fPosX = (float)atof(aStr);

									}
									else if (nCntWord == 1)//y
									{
										m_aKeyOffseet[nCnt].fPosY = (float)atof(aStr);
									}
									else//z
									{
										m_aKeyOffseet[nCnt].fPosZ = (float)atof(aStr);
									}
								}
							}
							//各パーツのROTの読み込み↓
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
										m_aKeyOffseet[nCnt].fRotX = (float)atof(aStr);

									}
									else if (nCntWord == 1)//y
									{
										m_aKeyOffseet[nCnt].fRotY = (float)atof(aStr);
									}
									else//z
									{
										m_aKeyOffseet[nCnt].fRotZ = (float)atof(aStr);
									}
								}
							}

							//パーツ読み込みの終わり
							if (memcmp(pStrCur, "END_PARTSSET", strlen("END_PARTSSET")) == 0)
							{
								nCnt++;
								break;
							}
						}
					}
					//読み込みの終わり
					if (memcmp(pStrCur, "END_CHARACTERSET", strlen("END_CHARACTERSET")) == 0)
					{
						break;
					}
				}
			}

			//読み込みの終わり
			if (memcmp(pStrCur, "END_CHARACTERSET", strlen("END_CHARACTERSET")) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);

	//読み込んだモデル情報をモデルの数、反映させる
	for (int nCntLoad = 0; nCntLoad < m_nNumModel; nCntLoad++)
	{
		//各パーツの初期位置を決める↓
		m_pModel[nCntLoad] = CModel::Create(D3DXVECTOR3(m_aKeyOffseet[nCntLoad].fPosX, m_aKeyOffseet[nCntLoad].fPosY, m_aKeyOffseet[nCntLoad].fPosZ));
		//各パーツのモデルを決める↓
		m_pModel[nCntLoad]->BindModel(m_pBuffMat[nCntLoad], m_pNumMat[nCntLoad], m_pMesh[nCntLoad]);
		//各パーツのモデルを決める↓
		m_pModel[nCntLoad]->BindTexture(m_pTexture);
		//各パーツの親を決める↓
		m_pModel[nCntLoad]->SetParent(m_pModel[nParent[nCntLoad]]);
	}
}

//==============================================
//				モーションの読み込み
//==============================================
void CPlayer::MotionLoad(void)
{
	FILE *pFile;

	char * pStrCur;//先頭文字列のポインタ
	char aLine[256];//文字列の読み込み
	char aStr[256];//文字列の抜き出し
	int nMotionKeyCnt = 0;//一つのモーションに含まれるキーの数
	int nParts = 0;//パーツの個数分
	int nWord;
	m_nUseMotionType = NEUTRAL;

	//テキストの読み込み↓
	pFile = fopen("DATA\\TEXT\\PLAYER_LODE.txt", "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "MOTIONSET", strlen("MOTIONSET")) == 0 && motionType == m_nUseMotionType)
			{

				fgets(&aLine[0], 256, pFile);
				pStrCur = CSceneX::GetLIneTop(&aLine[0]);
				if (memcmp(pStrCur, "LOOP = ", strlen("LOOP = ")) == 0)
				{
					pStrCur += strlen("LOOP = ");
					strcpy(aStr, pStrCur);
					m_aMotionInfo[m_nUseMotionType].nLoop = atoi(aStr);
				}

				fgets(&aLine[0], 256, pFile);
				pStrCur = CSceneX::GetLIneTop(&aLine[0]);
				if (memcmp(pStrCur, "NUM_KEY = ", strlen("NUM_KEY = ")) == 0)
				{
					pStrCur += strlen("NUM_KEY = ");
					strcpy(aStr, pStrCur);
					m_aMotionInfo[m_nUseMotionType].nNumKey = atoi(aStr);
				}

				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					if (memcmp(pStrCur, "KEYSET", strlen("KEYSET")) == 0)
					{
						fgets(&aLine[0], 256, pFile);
						pStrCur = CSceneX::GetLIneTop(&aLine[0]);
						if (memcmp(pStrCur, "FRAME = ", strlen("FRAME = ")) == 0)
						{
							pStrCur += strlen("FRAME = ");
							strcpy(aStr, pStrCur);
							m_aKeyInfo000[nMotionKeyCnt].nFrame = atoi(aStr);
						}
						while (1)
						{
							fgets(&aLine[0], 256, pFile);
							pStrCur = CSceneX::GetLIneTop(&aLine[0]);

							if (memcmp(pStrCur, "KEY", strlen("KEY")) == 0)
							{
								while (1)
								{
									//各パーツのPOSの読み込み↓
									fgets(&aLine[0], 256, pFile);
									pStrCur = CSceneX::GetLIneTop(&aLine[0]);
									if (memcmp(pStrCur, "POS =", strlen("POS =")) == 0)
									{
										pStrCur += strlen("POS =");
										strcpy(aStr, pStrCur);

										for (int nCntWord = 0; nCntWord < 3; nCntWord++)//x,y,z分回す
										{
											nWord = CSceneX::PopString(pStrCur, aStr);
											pStrCur += nWord;//読み込む文字位置をずらす
											strcpy(aStr, pStrCur);

											if (nCntWord == 0)//x
											{
												m_aMotionInfo[m_nUseMotionType].aKeyInfo[nMotionKeyCnt].aKey[nParts].fPosX = (float)atof(aStr);

											}
											else if (nCntWord == 1)//y
											{
												m_aMotionInfo[m_nUseMotionType].aKeyInfo[nMotionKeyCnt].aKey[nParts].fPosY = (float)atof(aStr);
											}
											else//z
											{
												m_aMotionInfo[m_nUseMotionType].aKeyInfo[nMotionKeyCnt].aKey[nParts].fPosZ = (float)atof(aStr);
											}
										}
									}

									//各パーツのROTの読み込み↓
									fgets(&aLine[0], 256, pFile);
									pStrCur = CSceneX::GetLIneTop(&aLine[0]);
									if (memcmp(pStrCur, "ROT =", strlen("ROT =")) == 0)
									{
										pStrCur += strlen("ROT =");
										strcpy(aStr, pStrCur);

										for (int nCntWord = 0; nCntWord < 3; nCntWord++)//x,y,z分回す
										{
											nWord = CSceneX::PopString(pStrCur, aStr);
											pStrCur += nWord;//読み込む文字位置をずらす
											strcpy(aStr, pStrCur);

											if (nCntWord == 0)//x
											{
												m_aMotionInfo[m_nUseMotionType].aKeyInfo[nMotionKeyCnt].aKey[nParts].fRotX = (float)atof(aStr);

											}
											else if (nCntWord == 1)//y
											{
												m_aMotionInfo[m_nUseMotionType].aKeyInfo[nMotionKeyCnt].aKey[nParts].fRotY = (float)atof(aStr);
											}
											else//z
											{
												m_aMotionInfo[m_nUseMotionType].aKeyInfo[nMotionKeyCnt].aKey[nParts].fRotZ = (float)atof(aStr);
											}
										}
									}

									fgets(&aLine[0], 256, pFile);
									pStrCur = CSceneX::GetLIneTop(&aLine[0]);
									if (memcmp(pStrCur, "END_KEY", strlen("END_KEY")) == 0)
									{
										nParts++;
										break;
									}
								}
							}

							if (memcmp(pStrCur, "END_KEYSET", strlen("END_KEYSET")) == 0)
							{
								nParts = 0;
								nMotionKeyCnt++;
								break;
							}
						}
					}
					//読み込みの終わり
					if (memcmp(pStrCur, "END_MOTIONSET", strlen("END_MOTIONSET")) == 0)
					{
						nParts = 0;
						nMotionKeyCnt = 0;
						break;
					}
				}
			}

			//読み込みの終わり

			if (memcmp(pStrCur, "END_MOTIONSET", strlen("END_MOTIONSET")) == 0)
			{
				if (motionType == m_nUseMotionType)
				{
					nParts = 0;
					nMotionKeyCnt = 0;
					break;
				}
				else if (motionType != m_nUseMotionType)
				{
					m_nUseMotionType++;
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);
				}
			}
		}
	}
	fclose(pFile);
}

//==============================================
//				モーションの更新
//==============================================
void CPlayer::UpdateMotion(void)
{
	CPlayer::MotionLoad();//外部テータからのモーションの読み込み

	KEY *pKey, *pKeyNext;//現在、次のキー
	float fRateMotion;//モーションの相対値
	float fDiffMotion;//ひとつ前のモーションとの差分
	D3DXVECTOR3 posMotion;//モーションの軸の回転に使用
	D3DXVECTOR3 rotMotion;//モーションの軸の回転に使用

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		if (m_pModel[nCnt] != NULL)
		{
			//現在のキーを取得

			pKey = &m_aMotionInfo[m_nUseMotionType].aKeyInfo[m_nKey].aKey[nCnt];
			//次のキーを取得
			pKeyNext = &m_aMotionInfo[m_nUseMotionType].aKeyInfo[(m_nKey + 1) % m_aMotionInfo[m_nUseMotionType].nNumKey].aKey[nCnt];

			//相対値
			fRateMotion = (float)(m_nCntFrame + 1) / (float)m_aKeyInfo000[m_nKey].nFrame;//小数点の値を入れるため
																						 //差分をもとめて、モデルの向きを設定
			fDiffMotion = pKeyNext->fRotX - pKey->fRotX;
			rotMotion.x = pKey->fRotX + (fDiffMotion*fRateMotion);//現在キー+(差分*相対値)

			fDiffMotion = pKeyNext->fRotY - pKey->fRotY;
			rotMotion.y = pKey->fRotY + (fDiffMotion*fRateMotion);

			fDiffMotion = pKeyNext->fRotZ - pKey->fRotZ;
			rotMotion.z = pKey->fRotZ + (fDiffMotion*fRateMotion);

			m_pModel[nCnt]->SetRot(rotMotion);//モーションの反映
		}
	}

	if (m_aMotionInfo[m_nUseMotionType].nLoop == 1 && m_bLoopCheck == true)//ループするモーションであれば...
	{
		m_nCntFrame++;//フレームカウンターの加算
		if (m_nCntFrame > m_aKeyInfo000[m_nKey].nFrame)
		{
			m_nCntFrame = 0;//初期モーションにもどる
			m_nKey = (m_nKey + 1) % m_aMotionInfo[m_nUseMotionType].nNumKey;//パターン分キーを進める
		}

	}
	else//ループしない場合
	{
		m_nCntFrame++;//フレームカウンターの加算

		if (m_aKeyInfo000[m_nKey].nFrame < m_nCntFrame)
		{
			if (m_nKey == m_aMotionInfo[m_nUseMotionType].nNumKey - 1)//最後のキーの場合
			{
				if (m_aKeyInfo000[m_nKey].nFrame < m_nCntFrame)
				{
					m_nKey = 0;//キーを0に
					m_nCntFrame = 0;//初期フレームにもどす
					motionType = NEUTRAL;
				}
			}
			else
			{
				m_nCntFrame = 0;//初期フレームにもどす
				m_nKey = (m_nKey + 1) % m_aMotionInfo[m_nUseMotionType].nNumKey;//パターン分キーを進める
			}
		}
	}
}

//==============================================
//				デバック用処理
//==============================================
void CPlayer::Debug(void)
{
	CDebug::DebugLog("\nモデルフレーム %d/%d", m_nCntFrame, m_aKeyInfo000[m_nKey].nFrame);
	CDebug::DebugLog("\nプレイヤーの位置 %.f,%.f,%.f", m_pos.x,m_pos.y, m_pos.z);
	//CDebug::DebugLog("\n重力 %0.1f,", m_move.y);
	CDebug::DebugLog("\n乗っているか %d,%d", m_bObjRide[m_nCurrentObj], m_nCurrentObj);
	//CDebug::DebugLog("\nポリゴンに乗っている %d ,", m_bPolygon3DCheck[m_nCurrent3DPolygon]);
	CDebug::DebugLog("\nエネミーに乗っているか %d,", m_bEnemyRide[m_nCurrentEnemy]);
	//CDebug::DebugLog("\n現在のアクション %d,", m_nUseMotionType);

}
