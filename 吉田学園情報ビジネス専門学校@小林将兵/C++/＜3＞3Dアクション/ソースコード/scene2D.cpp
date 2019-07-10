//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					2Dポリゴン処理 [scene2D.h]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "scene2D.h"
#include "manager.h"
#include "input.h"
#include "debugLog.h"

//==============================================
//					コンストラクタ
//==============================================
CScene2D::CScene2D(int nPriority, DATA_TYPE dataType):CScene(nPriority, dataType)
{

}
//==============================================
//					デストラクタ
//==============================================
CScene2D::~CScene2D()
{

}
//==============================================
//					生成
//==============================================
CScene2D *CScene2D::Create(void)
{
	CScene2D *pScene2D = NULL;
	
	if (pScene2D == NULL)
	{
		pScene2D = new CScene2D;
		pScene2D->Init();
	}
	return pScene2D;
}
//==============================================
//				初期化処理
//==============================================
HRESULT CScene2D::Init(void)
{
	m_bFlash = false;
	m_fFlashCnt = 0.0f;
	m_nSizeCnt = 0;
	m_bSizeChange = true;
	m_nScrollCnt = 0;
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点情報の作成
	VERTEX_2D *pVtx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, NULL, &m_pTexture);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの位置を設定
	pVtx[0].pos = D3DXVECTOR3(-m_fSizeX +m_pos.x, -m_fSizeY +m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, -m_fSizeY +m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fSizeX +m_pos.x, m_fSizeY + m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, m_fSizeY + m_pos.y, 0.0f);

	//テクスチャの生成
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
	pVtx[0].col = D3DXCOLOR(m_col);
	pVtx[1].col = D3DXCOLOR(m_col);
	pVtx[2].col = D3DXCOLOR(m_col);
	pVtx[3].col = D3DXCOLOR(m_col);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}
//==============================================
//					終了処理
//==============================================
void CScene2D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();//死亡フラグを立てる
}

//==============================================
//					更新処理
//==============================================
void CScene2D::Update(void)
{

}

//==============================================
//					描画処理
//==============================================
void CScene2D::Draw(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
 	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//==============================================
//				画像情報の取得・反映
//==============================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 textureInfo)
{
	m_pTexture = textureInfo;
}

//==============================================
//				位置情報の取得・反映
//==============================================
void CScene2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==============================================
//				回転情報の取得・反映
//==============================================
void CScene2D::SetSpin(float fSpinSpeed)
{
	m_fAngle = atan2f(m_fSizeX, m_fSizeY);
	m_fLengs = sqrtf((m_fSizeX )*(m_fSizeX ) + (m_fSizeY )*(m_fSizeY ));
	m_fSpinSpeed += fSpinSpeed;//回転速度

	//頂点情報の作成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンのサイズ、回転らの処理
	pVtx[0].pos = D3DXVECTOR3(sinf(m_fAngle + D3DX_PI + m_fSpinSpeed), cosf(m_fAngle + D3DX_PI + m_fSpinSpeed), 0.0f)*(m_fLengs + 0) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(sinf(-m_fAngle + D3DX_PI + m_fSpinSpeed), cosf(-m_fAngle + D3DX_PI + m_fSpinSpeed), 0.0f)*(m_fLengs + 0) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(sinf(-m_fAngle + m_fSpinSpeed), cosf(-m_fAngle + m_fSpinSpeed), 0.0f)*(m_fLengs + 0) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(sinf(m_fAngle + m_fSpinSpeed), cosf(m_fAngle + m_fSpinSpeed), 0.0f)*(m_fLengs + 0) + m_pos;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================
//				サイズ情報の取得・反映
//==============================================
void CScene2D::SetSize(float fSizeX, float fSizeY)
{
	m_fSizeX = fSizeX;
	m_fSizeY = fSizeY;
}

//==============================================
//					 色
//==============================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	m_col = col;
	//頂点情報の作成
	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//カラー情報
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//==============================================
//					点滅
//==============================================
void CScene2D::FlashTex(void)
{
	
	switch(m_bFlash)
	{
	case true:
		m_fFlashCnt+=0.03f;
		m_col = D3DXCOLOR(m_fFlashCnt, m_fFlashCnt, m_fFlashCnt, m_fFlashCnt);
		if (m_fFlashCnt >= 1.0f)
		{
			m_bFlash = false;
		}
		break;

	case false:
		m_fFlashCnt-=0.03f;
		m_col = D3DXCOLOR(m_fFlashCnt, m_fFlashCnt, m_fFlashCnt, m_fFlashCnt);
		if (m_fFlashCnt <= 0.0f)
		{
			m_bFlash = true;
		}
		break;
	}

	//頂点情報の作成
	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//カラー情報
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//								アニメーション
//=============================================================================
void CScene2D::SetTexAnim(int nCntAnim, int nWidth, int nHight, bool bLoop)
{
	m_nCnt++; //カウンターの加算 爆発の速度

	if (m_nCnt % nCntAnim == 0)
	{
		m_PatternAnim = (m_PatternAnim + 1) % (nWidth * nHight);//パターンNo.更新
	}

	//頂点情報の作成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight));
		pVtx[1].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth) + (1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight));
		pVtx[2].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight) + (1.0f / nHight));
		pVtx[3].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth) + (1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight) + (1.0f / nHight));

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}

	if (bLoop == false)//ループしない場合
	{
		if (m_PatternAnim >= (nWidth * nHight) - 1)
		{
			CScene2D::Uninit();
		}
	}
}

void CScene2D::SetAnimSize(float fCnt, int nSpeed)
{
	
	switch (m_bSizeChange)
	{
	case true:
		m_nSizeCnt++;
		m_fSizeX += fCnt;
		m_fSizeY += fCnt;
		if (m_nSizeCnt >= nSpeed)
		{
			m_nSizeCnt = 0;
			m_bSizeChange = false;
		}
			break;

	case false:
		m_nSizeCnt++;
		m_fSizeX += -fCnt;
		m_fSizeY += -fCnt;
		if (m_nSizeCnt >= nSpeed)
		{
			m_nSizeCnt = 0;
			m_bSizeChange = true;
		}
			break;


	}
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点情報の作成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//ポリゴンの位置を設定
		pVtx[0].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, -m_fSizeY + m_pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, -m_fSizeY + m_pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, m_fSizeY + m_pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, m_fSizeY + m_pos.y, 0.0f);

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//==============================================
//						移動
//==============================================
void CScene2D::SetMove(D3DXVECTOR3 move)
{
	m_pos += move;
	//頂点情報の作成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの位置を設定
	pVtx[0].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, -m_fSizeY + m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, -m_fSizeY + m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, m_fSizeY + m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, m_fSizeY + m_pos.y, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//==============================================
//					スクロール
//==============================================
void CScene2D::SetScroll(float fSpeed, bool bVector, int nType)
{
	//スクロール方向
	if (bVector == true)
	{
		m_nScrollCnt++;
	}
	else if (bVector == false)
	{
		m_nScrollCnt--;
	}

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (nType == 0)//横スクロール
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (fSpeed * m_nScrollCnt), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f + (fSpeed * m_nScrollCnt), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (fSpeed * m_nScrollCnt), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f + (fSpeed * m_nScrollCnt), 1.0f);
	}

	if (nType == 1)//縦スクロール
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + (fSpeed * m_nScrollCnt));
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + (fSpeed * m_nScrollCnt));
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + (fSpeed * m_nScrollCnt));
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + (fSpeed * m_nScrollCnt));
	}
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}


