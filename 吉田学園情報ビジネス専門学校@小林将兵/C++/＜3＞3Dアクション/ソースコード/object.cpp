//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					オブジェクト処理処理 [object.cpp]
//			Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "manager.h"
#include "debugLog.h"
#include "sound.h"
#include "input.h"
#include "sceneX.h"
#include "object.h"
#include "game.h"
#include "player.h"
#include "particle.h"
#include "time.h"
#include "polygon2D.h"
#include "polygon3D.h"
//==============================================
//				静的メンバ変数
//==============================================
CSound *CObject::m_pSound = NULL;
//テキスト読み込み関連
int CObject::m_nNumObject = NULL;
int CObject::m_nNumTexture = NULL;
char CObject::m_aFileNameObject[MAX_OBJECT][256] = {};
char CObject::m_aFileNameTexture[MAX_OBJECT][256] = {};
//モデル情報
LPD3DXMESH CObject::m_pMesh[MAX_OBJECT] = {};
LPD3DXBUFFER CObject::m_pBuffMat[MAX_OBJECT] = {};
DWORD CObject::m_pNumMat[MAX_OBJECT] = {};
//画像関連
LPDIRECT3DTEXTURE9 CObject::m_pTexture[OBJ_TEXTURE_NUM] = {};

int CObject::m_nCreateNum = 0;//生成された数の記憶
int CObject::m_nSwitchNum = 0;

//==============================================
//					コンストラクタ
//==============================================
CObject::CObject(int nPriority, DATA_TYPE dataType) :CSceneX(nPriority, dataType)
{
	//m_pTexture = NULL;		//テクスチャへのポインタ
	m_pVtxBuff = NULL;		//頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);
	m_VtxMin = GetVtxMin();
	m_VtxMax = GetVtxMax();
	m_bRide = false;
	m_bSide = false;
	m_bGimmickFlag = false;
	m_bLadderFlag = false;
	m_nFlagTimeCnt = 0;
	m_bBlockUP = false;
	m_nUPCnt = 0;
	m_bRotGimmick = false;
	m_bDrillGimmick = false;
	m_nDrillCnt = 0;
}
//==============================================
//					デストラクタ
//==============================================
CObject::~CObject()
{

}

//==============================================
//					生成
//==============================================
CObject *CObject::Create(int nObjType, int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_nCreateNum += 1;
	CObject *pObject = NULL;
	if (pObject == NULL)
	{
		pObject = new CObject;
		pObject->m_objType = nObjType;
		if (nObjType == 1)
		{
			m_nSwitchNum += 1;
		}
		pObject->BindObject(m_pBuffMat[nObjType], m_pNumMat[nObjType], m_pMesh[nObjType]);
		pObject->BindTexture(m_pTexture[nTexType]);	
		pObject->Init();
		pObject->SetPos(pos);
		pObject->SetRot(rot);
	}
	return pObject;
}
//==============================================
//					初期化処理
//==============================================
HRESULT CObject::Init(void)
{
	CSceneX::Init();

	m_VtxMin = GetVtxMin();
	m_VtxMax = GetVtxMax();
	m_bRide = false;
	m_bSide = false;
	m_bGimmickFlag = false;
	m_bLadderFlag = false;
	m_nFlagTimeCnt = 0;
	m_bBlockUP = false;
	m_nUPCnt = 0;
	m_bRotGimmick = false;
	m_bDrillGimmick = false;
	m_nDrillCnt = 0;
	m_pSound = CManager::GetSound();

	return S_OK;
}

//==============================================
//					終了処理
//==============================================
void CObject::Uninit(void)
{
	//次のモードのためにここで数値を0に
	m_nCreateNum = 0;
	m_nSwitchNum = 0;

	if (m_pSound != NULL)
	{
		m_pSound->StopSound();
	}

	CSceneX::Uninit();
}

//==============================================
//					更新処理
//==============================================
void CObject::Update(void)
{
	CSceneX::Update();
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	m_pPlayer = CGame::GetPlayer();

	SwitchFlag();

	if (m_objType == 18)//梯子
	{
		CDebug::DebugLog("\nイベント %d", m_bLadderFlag);

		if (m_pPlayer != NULL)
		{
			D3DXVECTOR3 pos = m_pPlayer->GetPos();
			CPolygon2D *pPolygon2D = CGame::GetPolygon2D(4);//アイコンの表示
			if (GetPos().x + 12 > pos.x && GetPos().x - 15 < pos.x)
			{
				
				if (pPolygon2D != NULL)
				{
					pPolygon2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				CDebug::DebugLog("\n梯子範囲内");
				if (m_pInputKeyboard->GetTrigger(DIK_W) == true || 
					m_pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || m_pInputXPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 0) == true)
				{
					m_bLadderFlag = true;
				}
			}
			else
			{
				if (pPolygon2D != NULL)
				{
					pPolygon2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				}
			}
		}
	}

	Gimmick();//ギミック処理のまとめ
	
	
	Debug();
	//CDebug::DebugLog("\n乗っている　%d", m_bRide);
	//CDebug::DebugLog("\n横に触れている　%d", m_bSide);

}

//==============================================
//					描画処理
//==============================================
void CObject::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	if (m_objType == 20)
	{
		CSceneX::DrawShadow();
	}
	else
	{
		CSceneX::Draw();
	}
}

//==============================================
//	オブジェクトに乗っているかを確認(主に敵ダメージによるふっとばしなどで使用する)
//==============================================
void CObject::SetRide(bool bRide)
{
	m_bRide = bRide;
}

//==============================================
//				ギミックフラグ
//==============================================
void CObject::SetGimmickFlag(bool bFlag)
{
	m_bGimmickFlag = bFlag;
}
void CObject::SetLadderFlag(bool bFlag)
{
	m_bLadderFlag = bFlag;
}
void CObject::Gimmick(void)
{
	if (m_objType == 21)//+ 上下ブロック
	{
		D3DXVECTOR3 pos = GetPos();

		switch (m_bBlockUP)
		{
		case true:
			m_nUPCnt++;
			pos.y += 1.0f;
			SetPos(pos);
			if (m_nUPCnt >= 40)
			{
				m_bBlockUP = false;
				m_nUPCnt = 0;
			}
			break;

		case false:
			m_nUPCnt++;
			pos.y -= 1.0f;
			SetPos(pos);
			if (m_nUPCnt >= 40)
			{
				m_bBlockUP = true;
				m_nUPCnt = 0;
			}
			break;
		}
	}

	if (m_objType == 19)//+ 回転刃ギミックの回転
	{
		D3DXVECTOR3 rot = GetRot();
		rot.z++;
		SetRot(rot);
		if (m_pPlayer != NULL)
		{
			if (m_pPlayer->GetCurrentObj() == 11)
			{
				m_bRotGimmick = true;
			}
		}
	}
	if (m_bRotGimmick == true)
	{
		D3DXVECTOR3 pos = GetPos();//170

		if (pos.y >= 170.0f&&pos.x <= 650.0f)
		{
			pos.y -= 10.0f;
		}
		else if (pos.y <= 170.0f)
		{
			if (pos.x <= 550.0f)
			{
				CPolygon3D::Create(0, D3DXVECTOR3(pos.x / 2.0f + 20.0f, pos.y / 2.0f - 20.0f, pos.z - 10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 1, 4, 3, false);
			}
			pos.x += 3.0f;
		}
		if (pos.x >= 650.0f)
		{
			pos.y += 3.0f;
		}
		SetPos(pos);
	}
	if (m_objType == 20)//+ ドリルギミックの回転
	{
		D3DXVECTOR3 rot = GetRot();
		rot.z += 0.5f;
		SetRot(rot);
		D3DXVECTOR3 pos = GetPos();

		switch (m_bDrillGimmick)
		{
		case true:
			m_nDrillCnt++;
			pos.z -= 5.0f;
			SetPos(pos);
			if (m_nDrillCnt >= 70)
			{
				m_bDrillGimmick = false;
				m_nDrillCnt = 0;
			}
			break;

		case false:
			m_nDrillCnt++;
			pos.z += 5.0f;
			SetPos(pos);
			if (m_nDrillCnt >= 70)
			{
				m_bDrillGimmick = true;
				m_nDrillCnt = 0;
			}
			break;
		}
	}
}
//==============================================
//				スイッチ系ギミック
//==============================================
void CObject::SwitchFlag(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer != NULL)
	{
		if (m_objType == 1)//スイッチ系ギミックであれば
		{
			D3DXVECTOR3 pos = GetPos();
			CPolygon2D *pPolygon2D = CGame::GetPolygon2D(2);//「操作」アイコンの表示

			if (pos.x + 50 > pPlayer->GetPos().x && pos.x - 50 < pPlayer->GetPos().x&&pos.y - 15.0f <= pPlayer->GetPos().y &&
				pos.z >= pPlayer->GetPos().z&& pos.y+10.0f >= pPlayer->GetPos().y)
			{
				CDebug::DebugLog("\nGimmick範囲内");
				if (m_bGimmickFlag == false)
				{
					if (pPolygon2D != NULL)
					{
						pPolygon2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					}
					if (m_pInputKeyboard->GetTrigger(DIK_RETURN) == true || m_pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
					{
						if (m_pSound != NULL)
						{
							m_pSound->PlaySound(CSound::SE_SWITCH);
						}
						m_bGimmickFlag = true;
						CGame::SetSwitchFlagNum();//加算
					}
				}
				else if (m_bGimmickFlag == true)
				{
					if (pPolygon2D != NULL)
					{
						pPolygon2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
					}
				}
			}
			else if (pos.x - 50 > pPlayer->GetPos().x && pos.x - 150 < pPlayer->GetPos().x||
						pos.x + 50 < pPlayer->GetPos().x && pos.x + 150 > pPlayer->GetPos().x)
			{
				if (pPolygon2D != NULL)
				{
					pPolygon2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				}
			}

			if (m_bGimmickFlag == true)
			{
				D3DXVECTOR3 pos = GetPos();
				m_nFlagTimeCnt++;
				D3DXVECTOR3 rot = GetRot();
				if (m_nFlagTimeCnt <= 8)
				{
					rot.z -= 0.2f;
				}
				SetRot(rot);
			}
			else
			{
				CParticle3D::Create(D3DXVECTOR3(pos.x, pos.y, pos.z - 20),//位置
					D3DXVECTOR3((float)(rand() % 50)*0.05f, (float)(rand() % 3) * 0.5f, (float)(rand() % 50)*0.05f),//移動量
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),//回転 
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), true,50, 0.2f, 0);//カラー 生存時間 拡大率

			}
		}
	}
}

//==============================================
//				当たり判定処理
//==============================================
bool CObject::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, int nType)
{
	D3DXVECTOR3 pos = GetPos();
	if (m_objType != 10 && m_objType != 17)
	{
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
				pPos->y = (pos.y + m_VtxMax.y) + OBJ_Y;
			}
			//OBJ上でジャンプした際の処理
			if (pos.y + m_VtxMax.y < pPos->y + OBJ_Y)
			{
				m_bRide = false;
			}
		}
		else
		{
			m_bRide = false;
		}

		//下判定
		if (m_objType == 16|| m_objType == 24)
		{
			if (pos.x + m_VtxMin.x < pPos->x + 0.0f &&
				pos.x + m_VtxMax.x > pPos->x - 0.0f &&
				pos.z + m_VtxMin.z < pPos->z + 0.0f &&
				pos.z + m_VtxMax.z > pPos->z - 0.0f)
			{
				if (pos.y + m_VtxMin.y > pPosOld->y - 0 &&
					pos.y + m_VtxMin.y < pPos->y + 40)
				{

					pPos->y = (pos.y + m_VtxMin.y) - 40;
				}
			}
		}
	}
	return m_bRide;
}

bool CObject::CollSide(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,
	D3DXVECTOR3 *pMove, int nType)
{
	D3DXVECTOR3 pos = GetPos();
	CTime *pTime = CGame::GetTime();

	if (m_objType != 10 && m_objType != 17)
	{
		if (m_VtxMax.y + pos.y - 0.5f > pPos->y + OBJ_Y&&
			m_VtxMin.y + pos.y - 40.0f <= pPos->y + OBJ_Y)
		{
			//前後判定
			if (m_objType == 20)
			{
				if (pos.x + m_VtxMin.x < pPos->x + 0.0f &&
					pos.x + m_VtxMax.x > pPos->x - 0.0f)
				{
					//手前の判定
					if (pos.z + m_VtxMin.z >= pPosOld->z - OBJ_Z&&
						pos.z + m_VtxMin.z < pPos->z + OBJ_Z)
					{
						pPos->z = pos.z + m_VtxMin.z - OBJ_Z;
						if (nType == DATA_TYPE_PLAYER)
						{
							if (m_pSound != NULL)
							{
								m_pSound->PlaySound(CSound::SE_CRASH);
								m_pSound->PlaySound(CSound::SE_DAMAGE);
							}
							m_pPlayer->SetDamageState(CPlayer::OBJ,true);
							m_pPlayer->SetKnockBack(2);
							pTime->SetDemeritTime(10);

						}
					}
					//奥の判定
					else if (pos.z + m_VtxMax.z <= pPosOld->z + OBJ_Z&&
						pos.z + m_VtxMax.z > pPos->z - OBJ_Z)
					{
						pPos->z = pos.z + m_VtxMax.z + OBJ_Z;
						if (nType == DATA_TYPE_PLAYER)
						{
							if (m_objType == 20)
							{
								m_pPlayer->SetDamageState(CPlayer::OBJ, true);
								m_pPlayer->SetKnockBack(3);
								pTime->SetDemeritTime(10);

							}
						}
					}
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
					pPos->x = pos.x + m_VtxMin.x - OBJ_X;
					if (nType == DATA_TYPE_PLAYER)
					{
						m_bSide = true;
						if (m_objType == 19)
						{
							if (m_pSound != NULL)
							{
								m_pSound->PlaySound(CSound::SE_DAMAGE);
							}
							m_pPlayer->SetDamageState(CPlayer::OBJ, true);
							m_pPlayer->SetKnockBack(0);//右か
							pTime->SetDemeritTime(10);

						}
					}

				}
				//右の判定
				else if (pos.x + m_VtxMax.x <= pPosOld->x + OBJ_X&&
					pos.x + m_VtxMax.x > pPos->x - OBJ_X)
				{
					pPos->x = pos.x + m_VtxMax.x + OBJ_X;
					if (nType == DATA_TYPE_PLAYER)
					{
						m_bSide = true;
						if (m_objType == 19)
						{
							if (m_pSound != NULL)
							{
								m_pSound->PlaySound(CSound::SE_DAMAGE);
							}
							m_pPlayer->SetDamageState(CPlayer::OBJ, true);
							m_pPlayer->SetKnockBack(1);//左か
							pTime->SetDemeritTime(10);

						}
					}
				}
				//横に触れてない場合
				if (pos.x + m_VtxMin.x > pPos->x + OBJ_X ||
					pos.x + m_VtxMax.x < pPos->x - OBJ_X)
				{
					if (nType == DATA_TYPE_PLAYER)
					{
						m_bSide = false;
					}
				}
			}

		}
		else
		{
			if (nType == DATA_TYPE_PLAYER)
			{
				m_bSide = false;
			}
		}
	}
	return m_bSide;
}


//==============================================
//			オブジェクトの読み込み
//==============================================
HRESULT CObject::ObjectLoad(void)
{
	FILE *pFile;

	char * pStrCur;		//先頭文字列のポインタ
	char aLine[256];	//文字列の読み込み
	char aStr[256];		//文字列の抜き出し
	int nCnt = 0;

	//テキストの読み込み
	pFile = fopen(OBJ_TEXT, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "OBJECT_LOAD", strlen("OBJECT_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = GetLIneTop(&aLine[0]);

					//パーツ数の読み込み
					if (memcmp(pStrCur, "NUM_OBJECT = ", strlen("NUM_OBJECT = ")) == 0)
					{
						pStrCur += strlen("NUM_OBJECT = ");
						strcpy(aStr, pStrCur);
						m_nNumObject = atoi(aStr);
					}
					//使用する名前の確認
					if (memcmp(pStrCur, "OBJECT_NAME ", strlen("OBJECT_NAME ")) == 0)
					{
						pStrCur += strlen("OBJECT_NAME ");

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

							strcpy(&m_aFileNameObject[nCnt][0], pStrCur);
						}

						nCnt += 1;
					}

					//読み込みの終わり
					if (memcmp(pStrCur, "END_OBJECT_LOAD", strlen("END_OBJECT_LOAD")) == 0)
					{
						break;
					}
				}

			}
			//読み込みの終わり
			if (memcmp(pStrCur, "END_OBJECT_LOAD", strlen("END_OBJECT_LOAD")) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);

	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < m_nNumObject; nCnt++)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX(m_aFileNameObject[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCnt],
			NULL,
			&m_pNumMat[nCnt],
			&m_pMesh[nCnt]);
	}

	return S_OK;
}
//==============================================
//				オブジェクトの破棄
//==============================================
void CObject::ObjectUnLoad(void)
{
	for (int nCnt = 0; nCnt < m_nNumObject; nCnt++)
	{
		//メッシュの開放
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		//マテリアル関連の開放
		if (m_pNumMat[nCnt] != NULL)
		{
			m_pNumMat[nCnt] = NULL;
		}
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}
	}
}

//==============================================
//					UVの読み込み
//==============================================
HRESULT CObject::TextureLoad(void)
{
	FILE *pFile;

	char * pStrCur;//先頭文字列のポインタ
	char aLine[256];//文字列の読み込み
	char aStr[256];//文字列の抜き出し
	int nCntTexture = 0;

	//テキストの読み込み↓
	pFile = fopen(OBJ_TEXT, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "TEXTURE_LOAD", strlen("TEXTURE_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					//オブジェクトに使用する画像の数
					if (memcmp(pStrCur, "NUM_TEXTURE = ", strlen("NUM_TEXTURE = ")) == 0)
					{
						pStrCur += strlen("NUM_TEXTURE = ");
						strcpy(aStr, pStrCur);
						m_nNumTexture = atoi(aStr);
					}

					//オブジェクトに使用する画像の名前
					if (memcmp(pStrCur, "TEXTURE_NAME ", strlen("TEXTURE_NAME ")) == 0)
					{
						pStrCur += strlen("TEXTURE_NAME ");

						strcpy(aStr, pStrCur);
						while (1)
						{
							if (pStrCur[strlen(pStrCur) - 1] != 'g')
							{
								pStrCur[strlen(pStrCur) - 1] = '\0';//改行文字をNULL文字に変換(参考サイト::http://hisashi.me/blog/?p=714)

							}

							else
							{
								break;
							}

							strcpy(&m_aFileNameTexture[nCntTexture][0], pStrCur);
						}

						nCntTexture += 1;
					}

					//読み込みの終わり
					if (memcmp(pStrCur, "END_TEXTURE_LOAD", strlen("END_TEXTURE_LOAD")) == 0)
					{
						break;
					}
				}

			}
			//読み込みの終わり
			if (memcmp(pStrCur, "END_TEXTURE_LOAD", strlen("END_TEXTURE_LOAD")) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);

	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	for (int nCnt = 0; nCnt < m_nNumTexture; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aFileNameTexture[nCnt], &m_pTexture[nCnt]);
	}

	return S_OK;
}
//==============================================
//					UVの破棄
//==============================================
void CObject::TextureUnLoad(void)
{
	for (int nCnt = 0; nCnt < m_nNumTexture; nCnt++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}


//==============================================
//					デバック
//==============================================
void CObject::Debug(void)
{
	D3DXVECTOR3 pos = GetPos();

	//キーボード・コントローラーの取得処理
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	if (m_objType == 20)
	{
		if (m_pInputKeyboard->GetPress(DIK_UP) == true)
		{
			pos.z -= 3.0f;
		}
		if (m_pInputKeyboard->GetPress(DIK_DOWN) == true)
		{
			pos.z += 3.0f;
		}

		if (m_pInputKeyboard->GetPress(DIK_LEFT) == true)
		{
			pos.x -= 1.0f;
		}
		if (m_pInputKeyboard->GetPress(DIK_RIGHT) == true)
		{
			pos.x += 1.0f;
		}
	}
	SetPos(pos);

	//CDebug::DebugLog("\nオブジェクト生成数　%d", m_nCreateNum);

}

