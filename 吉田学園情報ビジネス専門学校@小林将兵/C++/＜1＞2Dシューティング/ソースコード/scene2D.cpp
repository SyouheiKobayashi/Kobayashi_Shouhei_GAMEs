//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 2Dポリゴン処理 [scene2D.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "scene2D.h"
#include "manager.h"
#include "input.h"

//マクロ
//#define TEXTURE_NAME01	("DATA\\akira000.png")

//グローバル
//=============================================================================
//+ 2Dポリゴンのコンストラクタ
//=============================================================================
#if 1
CScene2D::CScene2D(int nPriority = 3):CScene(nPriority)
{
	//! <値をクリアな状態にする>
	m_pTexture = NULL;		// テクスチャへのポインタ
	m_pVtxBuff = NULL;		// 頂点バッファへのポインタ

	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);//表示するポリゴンの位

	//m_fAngle = 0;//角度
	//m_fLengs = 0;//距離
	//m_fSpin = 0;//回転の速度
	//m_fSize = 0.0f;
	
	m_nLife = 0;
}
#endif
//=============================================================================
//+ 2Dポリゴンのデストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
//+ ポリゴンの初期化処理
//=============================================================================
HRESULT CScene2D::Init(void)
{
	//! <初期値の設定>
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);//表示するポリゴンの位置

	//m_fSpin = 0;//回転の速度
	//m_fSize = 0.0f;//拡大・縮小
	
	m_nLife = 0;

	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();//NULLじゃなかったらGetDevice

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture);


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ポリゴンの位置を設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	/*pVtx[0].pos = D3DXVECTOR3(-m_fWIDTH, -m_fHEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_fWIDTH, -m_fHEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWIDTH, +m_fHEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_fWIDTH, +m_fHEIGHT, 0.0f);*/


	// テクスチャの生成
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//カラー情報
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//+ ポリゴンの終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	// テクスチャの破棄
	//! 各テクスチャを扱う.cppに書き込んでいる

	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//自分自身をdelete	<Scene>のdelete処理を使用
	Release();
}

//=============================================================================
//+ ポリゴンの更新処理
//=============================================================================
void CScene2D::Update(void)
{
	//! <ポリゴンの回転に関する変数>
	//m_fAngle = atan2f(100, 100);//理解不能
	//m_fLengs = 100;//全体的なサイズが変わる

	//m_fAngle = atan2f(m_fWIDTH, m_fHEIGHT);//理解不能
	//m_fLengs = sqrtf((m_fWIDTH/2)*(m_fWIDTH/2)+ (m_fHEIGHT / 2)*(m_fHEIGHT / 2));//全体的なサイズが変わる
	//m_fSpin += 0.01f;//回転の速度
#if 0
	 //! <ポリゴンの拡大・縮小に関する変数>
	switch (m_size)
	{
	case Big:
		m_fSize += 1.5f;//拡大する値
		
		if (80.0f <= m_fSize)
		{
			m_size = Small;
		}
		break;

	case Small:
		m_fSize -= 1.5f;//縮小する値
		if (m_fSize <= 0.0f)
		{
			m_size = Big;
		}
		break;
	}
#endif
	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ポリゴンのサイズ、回転らの処理
	//pVtx[0].pos = D3DXVECTOR3(sinf(m_fAngle - D3DX_PI + m_fSpin), cosf(m_fAngle - D3DX_PI + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	//pVtx[1].pos = D3DXVECTOR3(sinf(-m_fAngle + D3DX_PI + m_fSpin), cosf(-m_fAngle + D3DX_PI + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	//pVtx[2].pos = D3DXVECTOR3(sinf(-m_fAngle + m_fSpin), cosf(-m_fAngle + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	//pVtx[3].pos = D3DXVECTOR3(sinf(m_fAngle + m_fSpin), cosf(m_fAngle + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	
	//通常表示ポリゴン(サイズ変化、回転なし,各.cppでサイズの書き換え可)
	/*pVtx[0].pos = D3DXVECTOR3(-m_fWIDTH, - m_fHEIGHT, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+ m_fWIDTH, - m_fHEIGHT, 0.0f)+ m_pos;
	pVtx[2].pos = D3DXVECTOR3(- m_fWIDTH, + m_fHEIGHT, 0.0f)+ m_pos;
	pVtx[3].pos = D3DXVECTOR3(+ m_fWIDTH, + m_fHEIGHT, 0.0f)+ m_pos;*/



	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	
}

//=============================================================================
//+ ポリゴンの描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
 	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=============================================================================
//+ ポリゴンのSet処理
//=============================================================================
void CScene2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//通常表示ポリゴン(サイズ変化、回転なし,各.cppでサイズの書き換え可)
	pVtx[0].pos = D3DXVECTOR3(-m_fWIDTH, -m_fHEIGHT, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+m_fWIDTH, -m_fHEIGHT, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-m_fWIDTH, +m_fHEIGHT, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(+m_fWIDTH, +m_fHEIGHT, 0.0f) + m_pos;


	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//=============================================================================
//+ ポリゴンのカラーSet処理
//=============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) + col;
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) + col;
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) + col;
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) + col;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}


//=============================================================================
//+ ポリゴンに使用するテクスチャ情報の取得
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 m_pShareTexture)
{
	m_pTexture = m_pShareTexture;
}

//=============================================================================
//+ サイズ変更Set処理
//=============================================================================
void CScene2D::SetSize(float fWIDTH, float fHEIGHT)
{
	m_fWIDTH = fWIDTH;
	m_fHEIGHT = fHEIGHT;

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_fWIDTH, -m_fHEIGHT, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+m_fWIDTH, -m_fHEIGHT, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-m_fWIDTH, +m_fHEIGHT, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(+m_fWIDTH, +m_fHEIGHT, 0.0f) + m_pos;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}


//=============================================================================
//+ 回転Set処理
//=============================================================================
void CScene2D::SetRot(float fSpin)
{
	//! <ポリゴンの回転に関する変数>
	m_fAngle = atan2f(100, 100);//理解不能
	m_fLengs = 100;//全体的なサイズが変わる

	m_fAngle = atan2f(m_fWIDTH, m_fHEIGHT);//理解不能
	m_fLengs = sqrtf((m_fWIDTH/2)*(m_fWIDTH/2)+ (m_fHEIGHT / 2)*(m_fHEIGHT / 2));//全体的なサイズが変わる
	m_fSpin += fSpin;//回転の速度

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ポリゴンのサイズ、回転らの処理
	pVtx[0].pos = D3DXVECTOR3(sinf(m_fAngle - D3DX_PI + m_fSpin), cosf(m_fAngle - D3DX_PI + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(sinf(-m_fAngle + D3DX_PI + m_fSpin), cosf(-m_fAngle + D3DX_PI + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(sinf(-m_fAngle + m_fSpin), cosf(-m_fAngle + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(sinf(m_fAngle + m_fSpin), cosf(m_fAngle + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;


	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

void CScene2D::SetTimeRot(int nTime)
{
	//! <ポリゴンの回転に関する変数>
	m_fAngle = atan2f(100, 100);//理解不能
	m_fLengs = 100;//全体的なサイズが変わる

	m_fAngle = atan2f(m_fWIDTH, m_fHEIGHT);//理解不能
	m_fLengs = sqrtf((m_fWIDTH / 2)*(m_fWIDTH / 2) + (m_fHEIGHT / 2)*(m_fHEIGHT / 2));//全体的なサイズが変わる
	m_fSpin = (float)nTime;//回転の速度

					 // 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ポリゴンのサイズ、回転らの処理
	pVtx[0].pos = D3DXVECTOR3(sinf(m_fAngle - D3DX_PI + m_fSpin), cosf(m_fAngle - D3DX_PI + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(sinf(-m_fAngle + D3DX_PI + m_fSpin), cosf(-m_fAngle + D3DX_PI + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(sinf(-m_fAngle + m_fSpin), cosf(-m_fAngle + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(sinf(m_fAngle + m_fSpin), cosf(m_fAngle + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;


	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
//+ アニメーションSet処理
//=============================================================================
void CScene2D::SetTexAnim(int nCntAnim,int nWidth, int nHight, int nPattern)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth),				   (nPattern / nWidth)*(1.0f / nHight));
	pVtx[1].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth) + (1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHight));
	pVtx[2].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth),				   (nPattern / nWidth)*(1.0f / nHight) + (1.0f / nHight));
	pVtx[3].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth) + (1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHight) + (1.0f / nHight));

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//+ スクロールSet処理
//=============================================================================
void CScene2D::SetScroll(float fscrollSpeed, int nScrollCnt, int nScrollType)
{
	int nCnt = 0;
	

	VERTEX_2D*pVtx;//頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	nCnt++; //カウンターの加算


	if (nScrollType == 1)//縦スク
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (fscrollSpeed * nScrollCnt));
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (fscrollSpeed * nScrollCnt));
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (fscrollSpeed * nScrollCnt));
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (fscrollSpeed * nScrollCnt));
		if (pVtx[0].tex.y < 0.0f)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		}

		if (pVtx[1].tex.y < 0.0f)
		{
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}

	if (nScrollType == 2)//横スク
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f - (fscrollSpeed * nScrollCnt), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f - (fscrollSpeed * nScrollCnt), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f - (fscrollSpeed * nScrollCnt), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f - (fscrollSpeed * nScrollCnt), 1.0f);

		if (pVtx[0].tex.x < 0.0f)
		{
			pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		}

		if (pVtx[1].tex.x < 0.0f)
		{
			pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}


//=============================================================================
//+ 各ライフの設定(体力や時間経過等)処理
//=============================================================================
void CScene2D::SetLife(int nSetLife)
{
	m_nLife = nSetLife;
	/*if (m_nLife >= 15)
	{
		m_nLife =15;
	}*/
	this;//ブレイク時の値の確認に便利
}

