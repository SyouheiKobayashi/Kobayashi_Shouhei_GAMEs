//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					エネミー処理 [enemy.h]
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
#include "time.h"
#include "particle.h"

//==============================================
//				静的メンバ変数
//==============================================
CSound *CEnemy::m_pSound = NULL;
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = {};
LPD3DXMESH CEnemy::m_pMesh[ENEMY_PARTS] = {};
LPD3DXBUFFER CEnemy::m_pBuffMat[ENEMY_PARTS] = {};
DWORD CEnemy::m_pNumMat[ENEMY_PARTS] = {};
int CEnemy::m_nNumParts = NULL;
int CEnemy::m_aIndexParent[ENEMY_PARTS] = {};
CEnemy::KEY CEnemy::m_aKeyOffseet[ENEMY_PARTS] = {};
int CEnemy::m_nNumModel = NULL;
char CEnemy::m_aFileNameModel[ENEMY_PARTS][256] = {};
int CEnemy::m_nCreateNum = 0;//生成された数の記憶

//==============================================
//					コンストラクタ
//==============================================
CEnemy::CEnemy(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	NULLCheck();

}
//==============================================
//					デストラクタ
//==============================================
CEnemy::~CEnemy()
{
}

//==============================================
//					生成
//==============================================
CEnemy *CEnemy::Create(int nAIType, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_nCreateNum += 1;

	CEnemy *pEnemy = NULL;
	CModel *pModel = NULL;

	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;
		pEnemy->m_nAIType = nAIType;
		pEnemy->m_pos = pos;
		pEnemy->m_rot = rot;
		pEnemy->Init();

	}
	return pEnemy;
}
//==============================================
//					初期化処理
//==============================================
HRESULT CEnemy::Init(void)
{
	m_OriginPos = m_pos;//所定地の記憶

	NULLCheck();

	ModelLode();
	m_pSound = CManager::GetSound();

	Vtx();
	return S_OK;
} 

//==============================================
//					終了処理
//==============================================
void CEnemy::Uninit(void)
{
	m_nCreateNum = 0;

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
void CEnemy::Update(void)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)//使用モデル分更新
	{
		m_pModel[nCnt]->Update();
	}
	m_posOld = m_pos;//過去の位置情報を記憶

	//キーボード・コントローラーの取得処理
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	m_pInputMouse = CManager::GetInputMouse();

	CurrentMode();//現在のモードによって情報を変える
	Gravity();	//重力
	MOVE();		//移動
	JUMP();		//ジャンプ
	CollObj();	//オブジェクトの当たり判定
	if (m_pPlayer != NULL)
	{
		if (m_bRide == true)//プレイヤーに踏まれたなら
		{
			m_bMoveStop = true;
		}
		
		if (m_bMoveStop == true)
		{
			CParticle3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y+50.0f, m_pos.z),//位置
				D3DXVECTOR3((rand() % 40 - 20)*0.05f, (rand() % 20 + 1)*0.05f, (rand() % 40 - 20)*0.05f),//移動量
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),false, 20, 0.4f, 0);//回転 カラー 生存時間 大きさ

			motionType = STOP;
			m_MoveStopTime++;
			if (m_MoveStopTime >= 100)
			{
				m_bMoveStop = false;
				m_MoveStopTime = 0;
			}
		}
		
	}
	TitleEvent();//タイトル時の演出

	UpdateMotion();//モーションの更新(処理の順番によりほかの処理よりも下に!!)

	Debug();//デバック
}

//==============================================
//					描画処理
//==============================================
void CEnemy::Draw(void)
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

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_pModel[nCnt]->Draw();//使用するモデルの描画
	}
}

//==============================================
//			現在のモードによって情報を変える
//==============================================
void CEnemy::CurrentMode(void)
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
void CEnemy::Gravity(void)
{
	if (m_bMeshcheck == false || m_bObjRide[m_nCurrentObj] == false)//乗っていなかった場合
	{
		if (m_pos.y <= 0)
		{
			m_pos.y = 0;
			m_move.y = 0;
		}
		else
		{
			m_move.y -= ENEMY_GRAVITY;//重力加算

		}
	}
}

//==============================================
//					移動
//==============================================
void CEnemy::MOVE(void)
{
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		float fRotation = m_pCamera->GetRotation();
		m_pPlayer = CGame::GetPlayer();
		if (m_pPlayer != NULL && m_nAIType == 0)
		{
			if (m_pPlayer->GetSide(m_pPlayer->GetSideObjNum()) == false && m_bMoveStop == false)//プレイヤーが壁に触れていない場合
			{
				if (m_pos.x + 100 > m_pPlayer->GetPos().x && m_pos.x - 100 < m_pPlayer->GetPos().x)
				{
					m_bSearchCheck = true;
					
					if (m_pos.x < m_pPlayer->GetPos().x && m_pos.y >= m_pPlayer->GetPos().y)//プレイヤーが右側にいるとき
					{
						motionType = WALK;
						m_pos.x += sinf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_pos.z += cosf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_Sabun.y = (-D3DX_PI / 2 + fRotation) - m_rot.y;
					}
					if (m_pos.x > m_pPlayer->GetPos().x && m_pos.y >= m_pPlayer->GetPos().y)//プレイヤーが左側にいるとき
					{
						motionType = WALK;
						m_pos.x -= sinf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_pos.z -= cosf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_Sabun.y = ((D3DX_PI / 2) + fRotation) - m_rot.y;
					}
				}
				else//プレイヤーが範囲外なら特定の位置に戻る
				{
					m_bSearchCheck = false;
					if (m_pos.x < m_OriginPos.x)//特定の位置から左にいるとき
					{
						motionType = WALK;
						m_pos.x += sinf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_pos.z += cosf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_Sabun.y = (-D3DX_PI / 2 + fRotation) - m_rot.y;
					}
					if (m_pos.x > m_OriginPos.x)//特定の位置から右にいるとき
					{
						motionType = WALK;
						m_pos.x -= sinf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_pos.z -= cosf(D3DX_PI / 2 + fRotation) * m_move.x;
						m_Sabun.y = ((D3DX_PI / 2) + fRotation) - m_rot.y;
					}
				}
			}
		}
		if (m_pPlayer != NULL && m_nAIType == 1)
		{
			if (m_pos.x+100.0f > m_pPlayer->GetPos().x && m_pos.x -130 < m_pPlayer->GetPos().x)
			{
				CDebug::DebugLog("\nエネミーの射程範囲内です,");
				motionType = WALK;
				if (m_pos.z >= -50.0f)
				{
					CParticle3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z),//位置
						D3DXVECTOR3((rand() % 40 - 20)*0.05f, (rand() % 20 + 1)*0.1f, (rand() % 40 - 20)*0.05f),//移動量
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, 30, 0.2f, 1);//カラー 回転 生存時間 大きさ
				}
				m_pos.x += sinf(D3DX_PI + fRotation) * m_move.z;
				m_pos.z += cosf(D3DX_PI + fRotation) * m_move.z;
				m_Sabun.y = fRotation - m_rot.y;
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
}

//==============================================
//					ジャンプ
//==============================================
void CEnemy::JUMP(void)
{
	//if (m_bObjRide[m_nCurrentObj] == true|| m_pos.y <= 0)//地面に触れていたらジャンプ可能
	//{
	//	if (m_pInputKeyboard->GetTrigger(DIK_J) == true)
	//	{
	//		m_move.y = ENEMY_JUMP;//ジャンプ加算
	//	}
	//}
	m_pos.y += m_move.y;
}


//==============================================
//			当たり判定に関する処理
//==============================================
void CEnemy::Vtx(void)
{
	int nNumVtx;
	DWORD sizeFVF;
	BYTE *pVtxBuff;

	m_VtxMin = D3DXVECTOR3(10000, 10000, 10000);	//最大値
	m_VtxMax = D3DXVECTOR3(-10000, -10000, -10000);	//最小値

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{

		//頂点数の取得
		nNumVtx = m_pMesh[nCnt]->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(m_pMesh[nCnt]->GetFVF());

		//頂点バッファをロック
		m_pMesh[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVer = 0; nCntVer < nNumVtx; nCntVer++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (m_VtxMin.x >= vtx.x)
			{
				m_VtxMin.x = vtx.x;
			}
			if (m_VtxMin.y >= vtx.y)
			{
				m_VtxMin.y = vtx.y;
			}
			if (m_VtxMin.z >= vtx.z)
			{
				m_VtxMin.z = vtx.z;
			}

			if (m_VtxMax.x <= vtx.x)
			{
				m_VtxMax.x = vtx.x;
			}
			if (m_VtxMax.y <= vtx.y)
			{
				m_VtxMax.y = vtx.y;
			}
			if (m_VtxMax.z <= vtx.z)
			{
				m_VtxMax.z = vtx.z;
			}
			//サイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		//D3DXVECTOR3 size = GetModelSize();
		//m_VtxMin = D3DXVECTOR3(m_VtxMin.x * m_modelSize.x, m_VtxMin.y * m_modelSize.y, m_VtxMin.z * m_modelSize.z);
		//m_VtxMax = D3DXVECTOR3(m_VtxMax.x * m_modelSize.x, m_VtxMax.y * m_modelSize.y, m_VtxMax.z * m_modelSize.z);

		//m_VtxMin = D3DXVECTOR3(m_VtxMin.x, m_VtxMin.y, m_VtxMin.z);
		//m_VtxMax = D3DXVECTOR3(m_VtxMax.x, m_VtxMax.y, m_VtxMax.z);

		//頂点バッファをアンロック
		m_pMesh[nCnt]->UnlockVertexBuffer();
	}
}

//==============================================
//				当たり判定処理
//==============================================
bool CEnemy::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	D3DXVECTOR3 pos = GetPos();
	m_pObj = CGame::GetObj(m_nCurrentObj);
	CTime *pTime = CGame::GetTime();

	//上判定
	if (pos.x + m_VtxMin.x < pPos->x + 0.0f &&//数値を変えると判定部分が変わる
		pos.x + m_VtxMax.x > pPos->x - 0.0f &&

		pos.z + m_VtxMin.z < pPos->z + 0.0f &&
		pos.z + m_VtxMax.z > pPos->z - 0.0f)
	{
		if (pos.y - m_VtxMax.y <= pPosOld->y + OBJ_Y &&
			pos.y + m_VtxMax.y > pPos->y - OBJ_Y)
		{
  			m_bRide = true;
			m_pObj->SetRide(false);//乗っていない状態にしておく
			pPos->y = (pos.y + m_VtxMax.y) + OBJ_Y;
		}
		//OBJ上でジャンプした際の処理
		if (pos.y + m_VtxMax.y >= pPosOld->y + OBJ_Y &&
			pos.y + m_VtxMax.y < pPos->y - OBJ_Y)
		{
			m_bRide = false;
			//pPos->y = (pos.y + m_VtxMax.y) + OBJ_Y;
		}
	}
	else
	{
		m_bRide = false;
	}


	if (m_VtxMax.y + pos.y - 0.5f > pPos->y + OBJ_Y&&
		m_VtxMin.y + pos.y - 40.0f <= pPos->y + OBJ_Y)
	{
		//前後判定
		if (pos.x + m_VtxMin.x < pPos->x + 0.0f &&
			pos.x + m_VtxMax.x > pPos->x - 0.0f)
		{
			//手前の判定
			if (pos.z + m_VtxMin.z >= pPosOld->z - OBJ_Z&&
				pos.z + m_VtxMin.z < pPos->z + OBJ_Z)
			{
				pPos->z = pos.z + m_VtxMin.z - OBJ_Z;
			}
			//奥の判定
			else if (pos.z + m_VtxMax.z <= pPosOld->z + OBJ_Z&&
				pos.z + m_VtxMax.z > pPos->z - OBJ_Z)
			{
				pPos->z = pos.z + m_VtxMax.z + OBJ_Z;
			}
		}

		//左右判定
		if (pos.z + m_VtxMin.z < pPos->z + 0.0f &&
			pos.z + m_VtxMax.z > pPos->z - 0.0f)
		{
			//左の判定
			if (pos.x + m_VtxMin.x >= pPosOld->x - OBJ_X&&
				pos.x + m_VtxMin.x < pPos->x + OBJ_X)
			{
				if (m_pSound != NULL)
				{
					m_pSound->PlaySound(CSound::SE_DAMAGE);
				}
				pPos->x = pos.x + m_VtxMin.x - OBJ_X;
				m_pObj->SetRide(false);//乗っていない状態にしておく
				m_pPlayer->SetDamageState(CPlayer::ENEMY, true);
				m_pPlayer->SetKnockBack(0);//右か
				pTime->SetDemeritTime(3);
			}
			//右の判定
			else if (pos.x + m_VtxMax.x <= pPosOld->x + OBJ_X&&
				pos.x + m_VtxMax.x > pPos->x - OBJ_X)
			{
				if (m_pSound != NULL)
				{
					m_pSound->PlaySound(CSound::SE_DAMAGE);
				}
				pPos->x = pos.x + m_VtxMax.x + OBJ_X;
				m_pObj->SetRide(false);//乗っていない状態にしておく
				m_pPlayer->SetDamageState(CPlayer::ENEMY, true);
				m_pPlayer->SetKnockBack(1);//左か
				pTime->SetDemeritTime(3);
			}
		}
	}

	return m_bRide;
}

//==============================================
//				objとの当たり判定
//==============================================
void CEnemy::CollObj(void)
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
		}
	}
}

//==============================================
//				タイトル時の演出
//==============================================
void CEnemy::TitleEvent(void)
{
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{
		if (m_pInputKeyboard->GetTrigger(DIK_RETURN) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_START, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
		{
			m_bStop = true;
			m_nTitleEventCnt = 0;
		}
		float fRotation = m_pCamera->GetRotation();

		if (m_bStop == false)
		{
			m_nTitleEventCnt++;//方向の切り替え / JUMP間隔

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
				if (m_nTitleEventCnt >= 320)
				{
					m_bTitleEvent = false;
					m_nTitleEventCnt = 0;
				}
			}
		}
		else if (m_bStop == true)
		{
			m_nTitleEventCnt++;
			m_pos.x += sinf(D3DX_PI + fRotation) * 0.0f;
			m_pos.z += cosf(D3DX_PI + fRotation) * 0.0f;
			m_Sabun.y = fRotation - m_rot.y;
			if (m_nTitleEventCnt % 40 == 0)
			{
				m_move.y = ENEMY_JUMP;//ジャンプ加算
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
}

//==============================================
//				一括NULL化 / 初期化
//==============================================
void CEnemy::NULLCheck(void)
{

	m_move = D3DXVECTOR3(ENEMY_SPEED, ENEMY_SPEED, ENEMY_SPEED);
	m_nKey = 0;
	motionType = NEUTRAL;
	m_nUseMotionType = NEUTRAL;
	m_pCamera = NULL;
	m_bLoopCheck = false;
	m_bMeshcheck = false;
	for (int nCnt = 0; nCnt < OBJ_CREATE; nCnt++)
	{
		m_bObjRide[nCnt] = false;

	}
	for (int nCnt = 0; nCnt < OBJ_CREATE; nCnt++)
	{
		m_bObjSide[nCnt] = false;
	}
	m_nCurrentObj = 0;
	m_nTitleEventCnt = 0;
	m_bTitleEvent = false;
	m_bStop = false;
	m_bSearchCheck = false;
	m_bMoveStop = false;
	m_MoveStopTime = 0;
}
//==============================================
//				位置の反映
//==============================================
void CEnemy::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==============================================
//				モデルの読み込み
//==============================================
HRESULT CEnemy::ModelLoad(void)
{
	FILE *pFile;

	char * pStrCur;//先頭文字列のポインタ
	char aLine[256];//文字列の読み込み
	char aStr[256];//文字列の抜き出し
	int nCnt = 0;

	//テキストの読み込み↓
	pFile = fopen("DATA\\TEXT\\ENEMY01.txt", "r");

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
void CEnemy::ModelUnLoad(void)
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
HRESULT CEnemy::TextureLoad(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, ENEMY01_UV, &m_pTexture);

	return S_OK;
}

//==============================================
//					UVの破棄
//==============================================
void CEnemy::TextureUnLoad(void)
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
void CEnemy::ModelLode(void)
{
	FILE *pFile;
	char * pStrCur;//先頭文字列のポインタ
	char aLine[256];//文字列の読み込み
	char aStr[256];//文字列の抜き出し
	int nCnt = 0;
	int nWord;
	int nParent[ENEMY_PARTS];

	//テキストの読み込み↓
	pFile = fopen("DATA\\TEXT\\ENEMY01.txt", "r");

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
void CEnemy::MotionLoad(void)
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
	pFile = fopen("DATA\\TEXT\\ENEMY01.txt", "r");

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
void CEnemy::UpdateMotion(void)
{
	CEnemy::MotionLoad();//外部テータからのモーションの読み込み

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
void CEnemy::Debug(void)
{
		CDebug::DebugLog("\n重力 %0.1f,", m_move.y);
	CDebug::DebugLog("\n乗っているか %d,", m_bObjRide[m_nCurrentObj]);
	CDebug::DebugLog("\n敵の位置 %.f,%.f,%.f", m_pos.x, m_pos.y,m_pos.z);

}
