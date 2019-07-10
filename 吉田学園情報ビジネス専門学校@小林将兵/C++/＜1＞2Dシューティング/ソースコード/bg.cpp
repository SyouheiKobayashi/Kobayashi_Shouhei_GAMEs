//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 背景処理 [bg.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "bg.h"
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"
#include "time.h"
#include "game.h"

//マクロ
#define TEXTURE_NAME01	("DATA\\TEX\\bg\\bg_towards.jpg")//晴天
#define TEXTURE_NAME02	("DATA\\TEX\\bg\\BG00.png")//夜帳
#define TEXTURE_NAME03	("DATA\\TEX\\bg\\BG01.png")//キラキラ
#define TEXTURE_NAME04	("DATA\\TEX\\bg\\BG02.png")//山
#define TEXTURE_NAME05	("DATA\\TEX\\bg\\BG03.png")//地面
#define TEXTURE_NAME06	("DATA\\TEX\\bg\\BG04.png")//森

//静的変数
LPDIRECT3DTEXTURE9 CBG::m_aTexture[MAX_TEXTURE] = {};
//! =============================================================================
//! コンストラクタ
//! =============================================================================
#if 1
CBG::CBG() :CScene(OBJ_DRAW::DRAW_BG)
{
	//! <値をクリアな状態にする>
	
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
	}

	m_nScrollCnt = NULL;
}
#endif
//! =============================================================================
//! デストラクタ
//! =============================================================================
#if 1
CBG::~CBG()
{
	
}
#endif
//! =============================================================================
//! Tex読み込み
//! =============================================================================
HRESULT CBG::Load(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_aTexture[0]);//空
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME02, &m_aTexture[1]);//空
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME03, &m_aTexture[2]);//キラキラ
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME04, &m_aTexture[3]);//山
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME05, &m_aTexture[4]);//地面
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME06, &m_aTexture[5]);//森


	return S_OK;
}
//! =============================================================================
//! 使用Texの破棄
//! =============================================================================
void CBG::UnLoad(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (m_aTexture[nCnt] != NULL)
		{
			m_aTexture[nCnt]->Release();
			m_aTexture[nCnt] = NULL;
		}
	}
}

//! =============================================================================
//! 生成処理
//! =============================================================================
CBG *CBG::Create(void)
{
	CBG *pBG = NULL;
	if (pBG == NULL)
	{
		pBG = new CBG;
		pBG->Init();
	}
	return pBG;
}
//! =============================================================================
//! 初期化
//! =============================================================================
HRESULT CBG::Init(void)
{
	

	SetObjType(CScene::OBJTYPE_BG);//タイプを当てはめる

	m_nScrollCnt = NULL;

	/*cManager::MODE pMode = cManager::GetMode();
	if (pMode == cManager::MODE_TITLE)
	{
	}*/
		for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
		{
			m_apScene2D[nCnt] = new CScene2D(OBJ_DRAW::DRAW_BG);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_aTexture[nCnt]);
		}

	return S_OK;
}
//! =============================================================================
//! 終了
//! =============================================================================
void CBG::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
		m_apScene2D[nCnt] = NULL;
	}
	//自分自身をdelete	<Scene>のdelete処理を使用
	Release();
}
//! =============================================================================
//! 更新
//! =============================================================================
void CBG::Update(void)
{
	m_nScrollCnt--;
	m_apScene2D[0]->SetScroll(0.0005f, m_nScrollCnt,2);//(スクロール速度,加算or減算,1=縦 2=横)
	m_apScene2D[1]->SetScroll(0.0005f, m_nScrollCnt, 2);
	m_apScene2D[2]->SetScroll(0.00015f, m_nScrollCnt, 2);
	m_apScene2D[3]->SetScroll(0.0003f, m_nScrollCnt, 2);
	m_apScene2D[4]->SetScroll(0.0015f, m_nScrollCnt, 2);
	m_apScene2D[5]->SetScroll(0.0015f, m_nScrollCnt, 2);

	//m_apScene2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	CManager::MODE mode;
	mode = CManager::GetMode();
	if (mode == CManager::MODE_GAME)
	{
		CTime *pTime = CGame::GetTime();
		
		int nTimeNow = pTime->GetTimeNow();
		float nTime = nTimeNow*0.001f;
		m_apScene2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, nTime-0.5f));
		m_apScene2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, nTime-0.5f));
	}
}
//! =============================================================================
//! 描画
//! =============================================================================
void CBG::Draw(void)
{
	
}
//! =============================================================================
//! pos / 位置更新
//! =============================================================================
void CBG::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//通常表示背景(サイズ変化、回転なし,各.cppでサイズの書き換え可)
	pVtx[0].pos = D3DXVECTOR3(-100, -100, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+100, -100, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-100, +100, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(+100, +100, 0.0f) + m_pos;


	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}