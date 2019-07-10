//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//UI処理 [UI.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "manager.h"
#include "game.h"
#include "UI.h"
#include"player.h"
#include "time.h"
#include "continuity.h"

//マクロ
//読み込むテクスチャ↓
#define UI_01	("DATA\\TEX\\UI\\UI_title.png")//タイトルロゴ
#define UI_02	("DATA\\GAME_UI00.png")//下枠
#define UI_03	("DATA\\LIFE_ANIM03.png")//ライフ
#define UI_04	("DATA\\BLOOD_ANIM01.png")//血液ゲージ
#define UI_05	("DATA\\ActionIcon01.png")//アクション(回復)
#define UI_06	("DATA\\ActionIcon02.png")//アクション(時間増加)
#define UI_07	("DATA\\GAME_UI01.png")//アクション(必殺技)
#define UI_08	("DATA\\No_Use_Icon.png")//使用不可
#define UI_09	("DATA\\No_Use_Icon.png")//使用不可
#define UI_010	("DATA\\No_Use_Icon.png")//使用不可
#define UI_011	("DATA\\TEX\\UI\\UI_ranking.png")//リザルトロゴ
#define UI_012	("DATA\\TEX\\UI\\UI_TimeIcon00.png")//時間表記UI(回転あり)
#define UI_013	("DATA\\TEX\\UI\\UI_LifeFrame.png")//ライフゲージ枠
#define UI_014	("DATA\\TEX\\UI\\UI_BloodFrame.png")//血液ゲージ枠
#define UI_015	("DATA\\TEX\\UI\\UI_TimeFrame.png")//時計枠
#define UI_016	("DATA\\TEX\\UI\\UI_TimeParts.png")//時計針
#define UI_017	("DATA\\TEX\\UI\\UI_TimeParts.png")//時計針
#define UI_018	("DATA\\TEX\\pause\\pause_retry.png")//ゲームオーバー
#define UI_019	("DATA\\TEX\\UI\\UI_Score.png")
#define UI_020	("DATA\\TEX\\UI\\UI_Time.png")
#define UI_021	("DATA\\TEX\\UI\\UI_tutorial.png")
//UIのサイズ↓
#define E_SIZE_H	(30)
#define E_SIZE_W	(30)
//UIの攻撃間隔↓
#define E_INTERVAL	(70)
//静的メンバ変数
LPDIRECT3DTEXTURE9 CUI::m_pTexture[MAX_UI] = {};

//=============================================================================
//+UIのコンストラクタ
//=============================================================================
CUI::CUI() :CScene2D(OBJ_DRAW::DRAW_UI)
{
	m_nType = 0;
	m_CntAnim = 0;//アニメーションの速さ
	m_PatternAnim = 0;//アニメーションの分割数
	m_bTimeCheck = false;
	m_fCnt = 0.0f;
}

//=============================================================================
//+UIのデストラクタ
//=============================================================================
CUI::~CUI()
{

}

//=============================================================================
//+UIの必要分読み込み
//=============================================================================
HRESULT CUI::Load(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, UI_01, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, UI_02, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, UI_03, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, UI_04, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, UI_05, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, UI_06, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, UI_07, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, UI_08, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, UI_09, &m_pTexture[8]);
	D3DXCreateTextureFromFile(pDevice, UI_010, &m_pTexture[9]);
	D3DXCreateTextureFromFile(pDevice, UI_011, &m_pTexture[10]);
	D3DXCreateTextureFromFile(pDevice, UI_012, &m_pTexture[11]);
	D3DXCreateTextureFromFile(pDevice, UI_013, &m_pTexture[12]);
	D3DXCreateTextureFromFile(pDevice, UI_014, &m_pTexture[13]);
	D3DXCreateTextureFromFile(pDevice, UI_015, &m_pTexture[14]);
	D3DXCreateTextureFromFile(pDevice, UI_016, &m_pTexture[15]);
	D3DXCreateTextureFromFile(pDevice, UI_017, &m_pTexture[16]);
	D3DXCreateTextureFromFile(pDevice, UI_018, &m_pTexture[17]);
	D3DXCreateTextureFromFile(pDevice, UI_019, &m_pTexture[18]);
	D3DXCreateTextureFromFile(pDevice, UI_020, &m_pTexture[19]);
	D3DXCreateTextureFromFile(pDevice, UI_021, &m_pTexture[20]);


	return S_OK;
}
//=============================================================================
//+UIを他の処理による削除をさせない
//=============================================================================
void CUI::UnLoad(void)
{
	// テクスチャの破棄
	for (int nCnt = 0;nCnt < MAX_UI;nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
//+UIの生成処理
//=============================================================================
#if 1
CUI *CUI::Create(int nUI_NUM, int nPOS_X, int nPOS_Y, int nSIZE_X, int nSIZE_Y)
{
	CUI *pUI = NULL;
	if (pUI == NULL)
	{
		pUI = new CUI;
		pUI->Init(nUI_NUM);
		pUI->BindTexture(m_pTexture[nUI_NUM]);
		pUI->SetSize((float)nSIZE_X, (float)nSIZE_Y);//UIのサイズ
		pUI->SetPos(D3DXVECTOR3((float)nPOS_X, (float)nPOS_Y, 0.0f));//UI初期位置
	}
	return pUI;
}
#endif

//=============================================================================
//+UIの初期化処理
//=============================================================================
HRESULT CUI::Init(int nUI_NUM)
{
	CScene2D::Init();

	m_nType = nUI_NUM;
	m_CntAnim = 0;//アニメーションの速さ
	m_PatternAnim = 0;//アニメーションの分割数
	m_bTimeCheck = false;
	m_fCnt = 0.0f;
	if (m_nType == 17)
	{
		CScene2D::SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}

	return S_OK;
}

//=============================================================================
//+UIの終了処理
//=============================================================================
void CUI::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//+UIの更新処理
//=============================================================================
void CUI::Update(void)
{
	CScene2D::Update();
	//キーボードを使用するための処理↓
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//ゲームパッド呼び
	CInputXPad *pInputXPad = CManager::GetInputXPad();
	//UIの位置情報の所得を行うための処理↓
	D3DXVECTOR3 pos = CScene2D::GetPos();

	//UIの移動情報(変更・更新)の処理↓
	CScene2D::SetPos(pos);
	bool Check = false;

	

	//CPlayer *pPlayer = CPlayer::GetMode();
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

				if (ObjType == OBJ_TYPE::OBJTYPE_PLAYER)//敵objなら
				{
					CScene2D *pScene2D = (CScene2D*)pScene;//Scene2Dにキャスト
					CPlayer *pPlayer = (CPlayer*)pScene2D;//Bulletにキャスト
					int nActionMode = pPlayer->GetMode();//現在選択しているモードの情報を取得
					D3DXVECTOR3 PlayerPos = pPlayer->GetPos();//プレイヤーの位置情報
					//<タイム加算>が選ばれた場合...
					CUI::SetActionUI(nActionMode, CPlayer::MODE::CURE, 4);
					//<自己回復>が選ばれた場合...
					CUI::SetActionUI(nActionMode, CPlayer::MODE::ADD_TIME, 5);
					//<攻撃技>が選ばれた場合...
					CUI::SetActionUI(nActionMode, CPlayer::MODE::SICKLE, 6);

					int nBloodLife = pPlayer->GetBloodLife();//現在の血液情報を取得
					bool bUse01 = pPlayer->GetUse01();
					bool bUse02 = pPlayer->GetUse02();
					bool bUse03 = pPlayer->GetUse03();

					
					//! 技アイコン
					if (m_nType == 7)
					{
						if (bUse01 == true)
						{
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));//表示しない
						}
						else if (bUse01 == false)
						{
						
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//表示する

						}
					}
					if (m_nType == 8)
					{
						
						if (bUse02 == true)
						{
							
							
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));//表示しない
							
						}
						else if (bUse02 == false)
						{
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//表示する
							
						}
					}
					if (m_nType == 9)
					{
						if (bUse03 == true)
						{
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));//表示しない
						}
						else if (bUse03 == false)
						{
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//表示する
							
						}
					}
					
					CGame *pGame = CManager::GetGame();
					bool ContinuityFlag = pGame->GetContinuityFlag();
					int nCCC = pGame->GetCCC();

					//! 時間表記アイコン
					if (m_nType == 11)
					{
						CScene2D::SetRot(-0.0011f);
					}
					if (m_nType == 11)
					{
						if (nActionMode == CPlayer::MODE::ADD_TIME &&bUse02 == true && pInputXPad->GetTrigger(XINPUT_GAMEPAD_Y, 0) == true)
						{
							{
								CManager::MODE mode;
								mode = CManager::GetMode();
								if (mode == CManager::MODE_GAME)
								{
									CTime *pTime = CGame::GetTime();
									int nTimeNow = pTime->GetTimeNow();
									if (nTimeNow > (1 * 100))
									{
										CScene2D::SetRot(1.11f);
									}
								}
							}
						}
						if (nCCC == 1)
						{
							nCCC = 0;
							CScene2D::SetRot(1.11f);
							pGame->SetCCC(nCCC);
						}
					}
					//! 時計の針
					if (m_nType == 15)
					{
						CScene2D::SetRot(-0.015f);
					}
					if (m_nType == 16)
					{
						CScene2D::SetRot(-0.05f);
					}
					//! ゲームオーバー表示
					if (m_nType == 17)
					{
						m_fCnt+=0.005f;
						CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fCnt));
						if (m_fCnt > 1.0f)
						{
							m_fCnt = 1.0f;
						}
					}

					//! プレイヤー位置が時計と重なる位置になったら不透明にする
					if (PlayerPos.y <= 200)
					{
						if (m_nType == 11)
						{
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
						}
						if (m_nType == 14 || m_nType == 15 || m_nType == 16)
						{
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
						}
					}
					else
					{
						if (m_nType == 11 || m_nType == 14 || m_nType == 15 || m_nType == 16)
						{
							CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
						}
					}
				}
			}

		}
	}

	
	//! <プレイヤーのアニメーション処理>
		if (m_nType == 2||m_nType == 3)
		{
			m_CntAnim++; //カウンターの加算 爆発の速度
			if (m_CntAnim % 4 == 0)
			{
				m_PatternAnim = (m_PatternAnim + 1) % (5 * 3);//パターンNo.更新
			}

			CScene2D::SetTexAnim(4, 5, 3, m_PatternAnim);
			
			if (m_PatternAnim >= (5 * 3) - 1)
			{
				m_PatternAnim = 0;
			}
		}
	
}

//=============================================================================
//+ UIの描画処理
//=============================================================================
void CUI::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
//+ UIのアイコン表示処理
//=============================================================================

void CUI::SetActionUI(int nSelectActionNo, int nMode, int UI_TEX)
{
	
	if (nSelectActionNo == nMode)
	{
		if (m_nType == UI_TEX)
		{
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

	}
	else if (nSelectActionNo != nMode)
	{
		if (m_nType == UI_TEX)
		{
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
			
		}

	}
}
