//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// ゲージ処理 [gaugecpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

#include "gauge.h"
#include "manager.h"
#include "scene.h"

//=============================================================================
//+ 数字・ナンバーのコンストラクタ
//=============================================================================
CGauge::CGauge()
{
	//! <値をクリアな状態にする>
	m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	m_SizeX = NULL;
	m_SizeY = NULL;


	//m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);//表示するポリゴンの位


}
//=============================================================================
//+ 数字・ナンバーのデストラクタ
//=============================================================================
CGauge::~CGauge()
{

}
//=============================================================================
//+ 数字・ナンバーの生成処理
//=============================================================================
CGauge *CGauge::Create(void)
{
	CGauge *pNumber = NULL;

	if (pNumber == NULL)
	{
		pNumber = new CGauge;
		pNumber->Init();
		//pNumber->SetPos(D3DXVECTOR3 (100.0f,100.0f,0.0f));

	}
	return pNumber;
}
//=============================================================================
//+ 数字・ナンバーの初期化処理
//=============================================================================
HRESULT CGauge::Init(void)
{
	//! <初期値の設定>
	//m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);//表示するポリゴンの位置

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

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ポリゴンの位置を設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

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
//+ 数字・ナンバーの終了処理
//=============================================================================
void CGauge::Uninit(void)
{

	// テクスチャの破棄
	//! 各テクスチャを扱う.cppに書き込んでいる

	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}
//=============================================================================
//+ 数字・ナンバーの更新処理
//=============================================================================
void CGauge::Update(void)
{

}
//=============================================================================
//+ 数字・ナンバーの描画処理
//=============================================================================
void CGauge::Draw(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//=============================================================================
//+ 個数分描画するための準備
//=============================================================================
void CGauge::SetNumber(int nNumber)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	// テクスチャの生成
	pVtx[0].tex = D3DXVECTOR2(0.0f + nNumber * 1.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + nNumber * 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + nNumber * 1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + nNumber * 1.0f, 1.0f);


	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//+ 表示位置,間隔,個数
//=============================================================================
void CGauge::SetPos(D3DXVECTOR3 pos, int nSpace, int nCnt)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ポリゴンの位置を設定
	pVtx[0].pos = D3DXVECTOR3(pos.x + (nSpace*nCnt), pos.y - m_SizeY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + m_SizeX + (nSpace * nCnt), pos.y - m_SizeY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x + (nSpace * nCnt), pos.y + m_SizeY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + m_SizeX + (nSpace * nCnt), pos.y + m_SizeY, 0.0f);


	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//+ サイズのSet処理
//=============================================================================
void CGauge::SetSize(float X, float Y)
{
	m_SizeX = X;
	m_SizeY = Y;
}