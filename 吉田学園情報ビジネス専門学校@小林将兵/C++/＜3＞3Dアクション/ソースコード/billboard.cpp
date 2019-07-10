//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//						ビルボード処理 [billboard.cpp]
//				Author : Kobayashi_Sho-hei/小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "billboard.h"
#include "manager.h"
#include "input.h"
#include "debugLog.h"

//==============================================
//					コンストラクタ
//==============================================
CBillboard::CBillboard(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	m_pVtxBuff = NULL;		//頂点バッファへのポインタ
}
//==============================================
//					デストラクタ
//==============================================
CBillboard::~CBillboard()
{

}

//==============================================
//			  テクスチャ情報の受け取り
//==============================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 textureInfo)
{
	m_pTexture = textureInfo;
}


//==============================================
//					生成
//==============================================
CBillboard *CBillboard::Create(void)
{
	CBillboard *pBillboard = NULL;

	if (pBillboard == NULL)
	{
		pBillboard = new CBillboard;
		pBillboard->Init();

	}
	return pBillboard;
}

//==============================================
//				初期化処理
//==============================================
HRESULT CBillboard::Init(void)
{
	m_nCnt = 0;
	m_PatternAnim = 0;

	//デバイス情報の取得↓
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
	//D3DXCreateTextureFromFile(pDevice, TEXBILLBOARD_NAME, &m_pTexture);


	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ビルボードの位置を設定
 	pVtx[0].pos = D3DXVECTOR3(-m_size.x+m_pos.x, m_size.y + m_pos.y, m_size.z + m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x + m_pos.x, m_size.y + m_pos.y, m_size.z + m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x + m_pos.x, -m_size.y + m_pos.y, m_size.z + m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_size.x + m_pos.x, -m_size.y + m_pos.y, m_size.z + m_pos.z);

	//テクスチャの生成
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);


	//カラー情報
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================
//					終了処理
//==============================================
void CBillboard::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//==============================================
//					更新処理
//==============================================
void CBillboard::Update(void)
{
}

//==============================================
//					描画処理
//==============================================
void CBillboard::Draw(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxView, mtxTrans, mtxRot;//計算用マトリックス

	//アルファテスト処理(透明化による画像の切り取り現象を無効にする)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);//REF = Reference:参照
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//FUNC = Function:機能 //GREATER = ～より大きい

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	if (CManager::GetMode() == CManager::MODE_RANKING)//RANKINGのときのみ常にカメラの方へ向かせる
	{
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		m_mtxWorld._11 = mtxView._11;
		m_mtxWorld._12 = mtxView._21;
		m_mtxWorld._13 = mtxView._31;
		m_mtxWorld._21 = mtxView._12;
		m_mtxWorld._22 = mtxView._22;
		m_mtxWorld._23 = mtxView._32;
		m_mtxWorld._31 = mtxView._13;
		m_mtxWorld._32 = mtxView._23;
		m_mtxWorld._33 = mtxView._33;
	}

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

	//ビルボードの描画
  	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//==============================================
//					サイズ
//==============================================
void CBillboard::SetSize(D3DXVECTOR3 size)
{
	m_size.x = size.x;
	m_size.y = size.y;
	m_size.z = size.z;

	
}
void CBillboard::SetChangeSize(float fsize)
{

	m_size.x += fsize;
	m_size.y += fsize;

	//頂点情報の作成
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ビルボードの位置を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x,  m_pos.y+ m_size.y , m_pos.z + m_size.z  );
	pVtx[1].pos = D3DXVECTOR3(m_pos.x+ m_size.x,  m_pos.y+ m_size.y, m_pos.z + m_size.z );
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x,m_pos.y - m_size.y , m_pos.z + m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y , m_pos.z + m_size.z );

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================
//					位置
//==============================================
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
 	m_pos = pos;
	
	//頂点情報の作成
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//ビルボードの位置を設定
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, m_pos.z + m_size.z);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, m_pos.z + m_size.z);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, m_pos.z + m_size.z);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, m_pos.z + m_size.z);

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}
//==============================================
//					回転
//==============================================
void CBillboard::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;

}
//==============================================
//					色
//==============================================
void CBillboard::SetCol(D3DXCOLOR col)
{
	m_col = col;

	VERTEX_3D*pVtx;
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラー設定
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//==============================================
//			アニメーション(コマ送り)
//==============================================
void CBillboard::SetTexAnim(int nCntAnim, int nWidth, int nHight, bool bLoop)
{
	m_nCnt++; //カウンターの加算 爆発の速度

	if (m_nCnt % nCntAnim == 0)
	{
		m_PatternAnim = (m_PatternAnim + 1) % (nWidth * nHight);//パターンNo.更新
	}

	//頂点情報の作成
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight));
	pVtx[1].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth) + (1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight));
	pVtx[2].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight) + (1.0f / nHight));
	pVtx[3].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth) + (1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight) + (1.0f / nHight));

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();


	if (bLoop == false)//ループしない場合
	{
		if (m_PatternAnim >= (nWidth * nHight) - 1)
		{
			CBillboard::Uninit();
		}
	}
}

//==============================================
//					パーティクル
//==============================================
void CBillboard::SetParticle(float fTransSize, D3DXCOLOR col)
{
	VERTEX_3D*pVtx;

	m_size.x += fTransSize;
	m_size.y += fTransSize;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報の設定 
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, -m_size.y, m_size.z);

	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR(col);
	pVtx[1].col = D3DXCOLOR(col);
	pVtx[2].col = D3DXCOLOR(col);
	pVtx[3].col = D3DXCOLOR(col);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================
//				回転情報の取得・反映
//==============================================
void CBillboard::SetSpin(float fSpinSpeed)
{
	m_fAngle = -atan2f(m_size.x, m_size.y);
	m_fLengs = -sqrtf((m_size.x)*(m_size.x)+(m_size.y)*(m_size.y));
	m_fSpinSpeed += fSpinSpeed;//回転速度

							   //頂点情報の作成
	VERTEX_3D *pVtx;

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
//			点滅情報の取得・反映
//==============================================
void CBillboard::FlashTex(void)
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
