//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//3Dポリゴン処理処理 [scene3D.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "scene3D.h"
#include "manager.h"
#include "debugLog.h"
#include "input.h"
#include "game.h"
//==============================================
//3Dポリゴンのコンストラクタ
//==============================================
CScene3D::CScene3D(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	m_pTexture = NULL;								//テクスチャへのポインタ
	m_pVtxBuff = NULL;								//頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fSizeX = 100.0f;								//Xサイズ
	m_fSizeY = 0.0f;								//Yサイズ
	m_fSizeZ = 100.0f;								//Zサイズ
		
}
//==============================================
//3D3Dポリゴンののデストラクタ
//==============================================
CScene3D::~CScene3D()
{

}

//==============================================
//3Dポリゴンの生成
//==============================================

CScene3D *CScene3D::Create()
{
	CScene3D *pScene3D = NULL;

	if (pScene3D == NULL)
	{
		pScene3D = new CScene3D;
		pScene3D->Init();

	}
	return pScene3D;
}
//==============================================
//3Dポリゴンの初期化処理
//==============================================
HRESULT CScene3D::Init(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点情報の作成
	VERTEX_3D *pVtx;

	//頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, NULL, &m_pTexture);


	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//3Dポリゴンのの位置を設定
	pVtx[0].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, m_fSizeY, m_fSizeZ + m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, m_fSizeY, m_fSizeZ + m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, m_fSizeY, -m_fSizeZ + m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, m_fSizeY, -m_fSizeZ + m_pos.z);

	//テクスチャの生成
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);

	//カラー情報
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================
//3Dポリゴンの終了処理
//==============================================
void CScene3D::Uninit(void)
{
	Release();
}

//==============================================
//3Dポリゴンの更新処理
//==============================================
void CScene3D::Update(void)
{

}

//==============================================
//3Dポリゴンの描画処理
//==============================================
void CScene3D::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));


	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//3Dポリゴンのの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//==============================================
//画像情報の取得・反映
//==============================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 textureInfo)
{
	m_pTexture = textureInfo;
}


//==============================================
//位置情報の取得・反映
//==============================================
void CScene3D::SetPos(D3DXVECTOR3 pos)
{

}

//==============================================
//サイズ情報の取得・反映
//==============================================
void CScene3D::SetSize(float fSizeX, float fSizeY, float fSizeZ)
{
	m_fSizeX = fSizeX;
	m_fSizeY = fSizeY;
	m_fSizeZ = fSizeZ;
}

//==============================================
//色情報の取得・反映
//==============================================
void CScene3D::SetCol(D3DXCOLOR col)
{
	m_col = col;
}


//==============================================
//点滅情報の取得・反映
//==============================================
void CScene3D::FlashTex(void)
{
	switch (m_bFlash)
	{
	case true:
		fFlashCnt += 0.03f;
		m_col = D3DXCOLOR(fFlashCnt, fFlashCnt, fFlashCnt, fFlashCnt);
		if (fFlashCnt >= 1.0f)
		{
			m_bFlash = false;
		}
		break;

	case false:
		fFlashCnt -= 0.03f;
		m_col = D3DXCOLOR(fFlashCnt, fFlashCnt, fFlashCnt, fFlashCnt);
		if (fFlashCnt <= 0.0f)
		{
			m_bFlash = true;
		}
		break;
	}
}

//=============================================================================
//アニメーションSet処理
//=============================================================================
void CScene3D::SetTexAnim(int nCntAnim, int nWidth, int nHeight, int nPattern)
{
	//頂点情報の作成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight));
	pVtx[1].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth) + (1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight));
	pVtx[2].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight) + (1.0f / nHeight));
	pVtx[3].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth) + (1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight) + (1.0f / nHeight));

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
