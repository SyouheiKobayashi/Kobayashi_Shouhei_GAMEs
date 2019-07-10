//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					ナンバー処理 [number.cpp]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"

//==============================================
//				静的メンバ変数
//==============================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//==============================================
//					コンストラクタ
//==============================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
}

//==============================================
//					デストラクタ
//==============================================
CNumber::~CNumber()
{

}

//==============================================
//						生成
//==============================================
CNumber *CNumber::Create(void)
{
	CNumber *pNumber = NULL;

	if (pNumber == NULL)
	{
		pNumber = new CNumber;
		pNumber->Init();
	}
	return pNumber;
}
//==============================================
//				初期化処理
//==============================================
HRESULT CNumber::Init(void)
{
	m_SizeX = 0;
	m_SizeY = 0;
	m_nChangeCnt = 0;
	bChange = true;

	//デバイス情報の取得↓
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

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの位置を設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}
//==============================================
//				終了処理
//==============================================
void CNumber::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	delete this;
}
//==============================================
//				更新処理
//==============================================
void CNumber::Update(void)
{
	
}

//==============================================
//					描画処理
//==============================================
void CNumber::Draw(void)
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
//　　　　　		数値の反映
//==============================================
void CNumber::SetNumber(int nNumber)
{
	//頂点情報の作成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	//テクスチャの生成
	pVtx[0].tex = D3DXVECTOR2(0.0f + nNumber * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + nNumber * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + nNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + nNumber * 0.1f, 1.0f);


	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}


//==============================================
//				表示位置・間隔・桁数
//==============================================
void CNumber::SetPos(D3DXVECTOR3 pos, float fSpace, int nDigitNum)
{
	m_pos = pos;
	m_fSpace = fSpace;
	m_nDigitNum = nDigitNum;
	//頂点情報の作成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの位置を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y - m_SizeY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y - m_SizeY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y + m_SizeY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y + m_SizeY, 0.0f);


	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================
//					サイズの調整
//==============================================
void CNumber::SetSize(float X, float Y)
{
	m_SizeX = X;
	m_SizeY = Y;
}

//==============================================
//				拡大縮小演出
//==============================================
void CNumber::SetScale(int nChangeTime,float fSpeed)
{

	if (bChange == true)
	{
		m_nChangeCnt++;
		m_fSpace += fSpeed;
		m_pos.x -= fSpeed;
		m_SizeX += fSpeed;
		m_SizeY += fSpeed;
		if (m_nChangeCnt > nChangeTime)
		{
			bChange = false;
			m_nChangeCnt = 0;
		}
	}
	if (bChange == false)
	{
		m_nChangeCnt++;
		m_fSpace -= fSpeed;
		m_pos.x += fSpeed;
		m_SizeX -= fSpeed;
		m_SizeY -= fSpeed;
		if (m_nChangeCnt > nChangeTime)
		{
			bChange = true;
			m_nChangeCnt = 0;

		}
	}

	//頂点情報の作成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの位置を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y - m_SizeY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y - m_SizeY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y + m_SizeY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y + m_SizeY, 0.0f);


	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//==============================================
//					カラーの調整
//==============================================
void CNumber::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;
						
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	m_pVtxBuff->Unlock();
}

//==============================================
//					画像の読み込み
//==============================================
HRESULT CNumber::TextureLoad(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TIME_TEX_NAME01, &m_pTexture);

	return S_OK;
}
//==============================================
//			　　画像の解放
//==============================================
void CNumber::TextureUnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
