//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//一時停止処理 [pause.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "manager.h"
#include "pause.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "enemy.h"
#include "explosion.h"

//マクロ
//読み込むテクスチャ↓
#define PAUSE_TEX01	("DATA\\TEX\\pause\\pause_BG.png")//ポーズ時の背景
#define PAUSE_TEX02	("DATA\\TEX\\pause\\pause_BG02.png")//ポーズ時の背景
#define PAUSE_TEX03	("DATA\\TEX\\pause\\pause_BG03.jpg")//ポーズ時の背景
#define PAUSE_TEX04	("DATA\\TEX\\pause\\pause_resumption.png")//選択1
#define PAUSE_TEX05	("DATA\\TEX\\pause\\pause_retry.png")//選択2
#define PAUSE_TEX06	("DATA\\TEX\\pause\\pause_Quit.png")//選択3
//UIのサイズ↓
#define E_SIZE_H	(30)
#define E_SIZE_W	(30)
//UIの攻撃間隔↓
#define E_INTERVAL	(70)
//静的メンバ変数
LPDIRECT3DTEXTURE9 CPause::m_pTexture[PAUSE_TEX] = {};
//=============================================================================
//+UIのコンストラクタ
//=============================================================================
CPause::CPause() :CScene2D(OBJ_DRAW::DRAW_PAUSE)
{
	m_nType = 0;

	m_nPauseMode = PAUSE00;

}

//=============================================================================
//+UIのデストラクタ
//=============================================================================
CPause::~CPause()
{

}

//=============================================================================
//+UIの必要分読み込み
//=============================================================================
HRESULT CPause::Load(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEX01, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEX02, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEX03, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEX04, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEX05, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEX06, &m_pTexture[5]);

	return S_OK;
}
//=============================================================================
//+UIを他の処理による削除をさせない
//=============================================================================
void CPause::UnLoad(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < PAUSE_TEX; nCnt++)
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
CPause *CPause::Create(int nUI_NUM, int nPOS_X, int nPOS_Y, int nSIZE_X, int nSIZE_Y)
{
	CPause *pUI = NULL;
	if (pUI == NULL)
	{
		pUI = new CPause;
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
HRESULT CPause::Init(int nUI_NUM)
{
	CScene2D::Init();

	m_nType = nUI_NUM;
	m_nPauseMode = PAUSE00;

	return S_OK;
}

//=============================================================================
//+UIの終了処理
//=============================================================================
void CPause::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//+UIの更新処理
//=============================================================================
void CPause::Update(void)
{
	CScene2D::Update();
	//キーボードを使用するための処理↓
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//ゲームパッド呼び
	CInputXPad *pInputXPad = CManager::GetInputXPad();
	CGame *pGame = CManager::GetGame();

	//ポーズ使用、不使用時の処理
	m_PauseFlag = pGame->GetPauseFlag();
	if (m_PauseFlag == false)
	{
		
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));//表示しない状態
	}
	else
	{
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//表示している状態
			//キー選択処理
			
			
			if (pInputXPad->GetTrigger(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || pInputKeyboard->GetTrigger(DIK_W) == true)
			//if (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
			{
				{
					m_nPauseMode -= 1;
					if (m_nPauseMode < PAUSE00)
					{
						m_nPauseMode = PAUSE02;
					}
					//apJoyState[0] = CInputXPad::INPUT_JOYSTATE_PUSH;
				}
			}

			if (pInputXPad->GetTrigger(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true || pInputKeyboard->GetTrigger(DIK_S) == true)
			//if (state.Gamepad.sThumbLY <= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
			{
				m_nPauseMode += 1;
				if (m_nPauseMode > PAUSE02)
				{
					m_nPauseMode = PAUSE00;
				}
			}
			//状態の反映
			if (m_nType == m_nPauseMode)
			{
				CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			if (m_nType != m_nPauseMode)
			{
				CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
			//モードの移行
			if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				{
					if (m_nPauseMode == PAUSE00)
					{
						m_PauseFlag = false;

					}
					if (m_nPauseMode == PAUSE01)//タイトルへ...
					{
						CFade::FADE pFade;
						pFade = CFade::GetFade();
						if (pFade == CFade::FADE_NONE)
						{
							CManager::GetFade()->SetFade(CManager::MODE_GAME);
						}
					}
					if (m_nPauseMode == PAUSE02)//タイトルへ...
					{
						CFade::FADE pFade;
						pFade = CFade::GetFade();
						if (pFade == CFade::FADE_NONE)
						{
							CManager::GetFade()->SetFade(CManager::MODE_TITLE);
						}
					}
				}
			}
	}

	//UIの位置情報の所得を行うための処理↓
	D3DXVECTOR3 pos = CScene2D::GetPos();


	//UIの移動情報(変更・更新)の処理↓
	CScene2D::SetPos(pos);
}

//=============================================================================
//+ UIの描画処理
//=============================================================================
void CPause::Draw(void)
{
	CScene2D::Draw();
}

