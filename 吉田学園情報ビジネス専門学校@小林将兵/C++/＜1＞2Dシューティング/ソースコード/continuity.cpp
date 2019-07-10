//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//一時停止処理 [Continuity.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "manager.h"
#include "continuity.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "enemy.h"
#include "explosion.h"

//マクロ
//読み込むテクスチャ↓
#define CONTINUITY_TEX01	("DATA\\TEX\\pause\\pause_BG.png")//ポーズ時の背景
#define CONTINUITY_TEX02	("DATA\\TEX\\pause\\pause_BG02.png")//ポーズ時の背景
#define CONTINUITY_TEX03	("DATA\\TEX\\pause\\pause_BG03.jpg")//ポーズ時の背景
#define CONTINUITY_TEX04	("DATA\\TEX\\pause\\pause_Continue.png")//下枠
#define CONTINUITY_TEX05	("DATA\\TEX\\pause\\pause_giveup.png")//下枠
//UIのサイズ↓
#define E_SIZE_H	(30)
#define E_SIZE_W	(30)
//UIの攻撃間隔↓
#define E_INTERVAL	(70)
//静的メンバ変数
LPDIRECT3DTEXTURE9 CContinuity::m_pTexture[CONTINUITY_TEX] = {};
//! =============================================================================
//! コンストラクタ
//! =============================================================================
CContinuity::CContinuity() :CScene2D(OBJ_DRAW::DRAW_PAUSE)
{
	m_nType = 0;

	m_nContinuityMode = CONTINUITY00;
	m_GiveUpFlag = false;
}

//! =============================================================================
//! デストラクタ
//! =============================================================================
CContinuity::~CContinuity()
{

}

//! =============================================================================
//! Tex読み込み
//! =============================================================================
HRESULT CContinuity::Load(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, CONTINUITY_TEX01, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, CONTINUITY_TEX02, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, CONTINUITY_TEX03, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, CONTINUITY_TEX04, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, CONTINUITY_TEX05, &m_pTexture[4]);

	return S_OK;
}
//! =============================================================================
//! Tex破棄
//! =============================================================================
void CContinuity::UnLoad(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < CONTINUITY_TEX; nCnt++)
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
CContinuity *CContinuity::Create(int nUI_NUM, int nPOS_X, int nPOS_Y, int nSIZE_X, int nSIZE_Y)
{
	CContinuity *pUI = NULL;
	if (pUI == NULL)
	{
		pUI = new CContinuity;
		pUI->Init(nUI_NUM);
		pUI->BindTexture(m_pTexture[nUI_NUM]);
		pUI->SetSize((float)nSIZE_X, (float)nSIZE_Y);//UIのサイズ
		pUI->SetPos(D3DXVECTOR3((float)nPOS_X, (float)nPOS_Y, 0.0f));//UI初期位置
	}
	return pUI;
}
#endif

//! =============================================================================
//! 初期化
//! =============================================================================
HRESULT CContinuity::Init(int nUI_NUM)
{
	CScene2D::Init();

	m_nType = nUI_NUM;
	m_nContinuityMode = CONTINUITY00;
	m_GiveUpFlag = false;
	return S_OK;
}

//! =============================================================================
//! 終了
//! =============================================================================
void CContinuity::Uninit(void)
{
	CScene2D::Uninit();
}

//! =============================================================================
//! 更新
//! =============================================================================
void CContinuity::Update(void)
{
	CScene2D::Update();
	//キーボードを使用するための処理↓
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//ゲームパッド呼び
	CInputXPad *pInputXPad = CManager::GetInputXPad();
	CGame *pGame = CManager::GetGame();

	int nUnintTime = 0;
	//nUnintTime++;

	//ポーズ使用、不使用時の処理
	m_ContinuityFlag = pGame->GetContinuityFlag();
	if (m_ContinuityFlag == false|| m_GiveUpFlag == true)
	{
		
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));//表示しない状態
		
	}
	else
	{
		
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//表示している状態
			//キー選択処理
			//if (state.Gamepad.sThumbLY <= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
			if (pInputXPad->GetTrigger(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || pInputKeyboard->GetTrigger(DIK_W) == true)
			{
				m_nContinuityMode -= 1;
				if (m_nContinuityMode < CONTINUITY00)
				{
					m_nContinuityMode = CONTINUITY01;
				}
				
			}
			//if (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
			if (pInputXPad->GetTrigger(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true || pInputKeyboard->GetTrigger(DIK_S) == true)
			{
				
				m_nContinuityMode += 1;
				if (m_nContinuityMode > CONTINUITY01)
				{
					m_nContinuityMode = CONTINUITY00;
				}
			}
			//状態の反映
			if (m_nType == m_nContinuityMode)
			{
				CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			if (m_nType != m_nContinuityMode)
			{
				CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}

			if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				{
					if (m_nContinuityMode == CONTINUITY01)
					{
						m_GiveUpFlag = true;
					}
				}
			}
		
	}

	//UIの位置情報の所得を行うための処理↓
	D3DXVECTOR3 pos = CScene2D::GetPos();


	//UIの移動情報(変更・更新)の処理↓
	CScene2D::SetPos(pos);

}

//! =============================================================================
//! 描画
//! =============================================================================
void CContinuity::Draw(void)
{
	CScene2D::Draw();
}

