//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// フェード処理 [fade.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

#include "fade.h"
#include "manager.h"
#include "scene.h"
#include "input.h"


//静的メンバ変数
CFade::FADE CFade::m_fade = FADE_IN;
//! =============================================================================
//! コンストラクタ
//! =============================================================================
CFade::CFade()
{
	//! <値をクリアな状態にする>
	m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
}
//! =============================================================================
//! デストラクタ
//! =============================================================================
CFade::~CFade()
{

}
//! =============================================================================
//! 生成
//! =============================================================================
CFade *CFade::Create(void)
{
	CFade *pNumber = NULL;

	if (pNumber == NULL)
	{
		pNumber = new CFade;
		pNumber->Init();
	}
	return pNumber;
}
//! =============================================================================
//! 初期化
//! =============================================================================
HRESULT CFade::Init(void)
{
	//! <初期値の設定>
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
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
//! =============================================================================
//! 終了
//! =============================================================================
void CFade::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}
//! =============================================================================
//! 更新
//! =============================================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)//? フェードイン状態なら
		{
			m_colorFade.a -= 0.02f;//フェードを薄くしていく

			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;//! 0.0f以上にさせない
				m_fade = FADE_NONE;//使用してない状態へ
			}
		}
		
		else if (m_fade == FADE_OUT)//? フェードアウト状態なら
		{
			m_colorFade.a += 0.02f;//フェードを濃くする

			if (m_colorFade.a >= 1.0f)//一定数値以上なら
			{
				m_colorFade.a = 1.0f;//! 1.0f以上にさせない
				m_fade = FADE_IN;//フェードイン状態へ

				SetMode(m_modeNext);//フェードアウトを終えた後、次のモードに変わる
			}
		}
	}

	VERTEX_2D*pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点データへのポインタを所得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点情報(カラー)の更新
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;
	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

}
//! =============================================================================
//!　描画
//! =============================================================================
void CFade::Draw(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//! =============================================================================
//! フェードの設定処理
//! =============================================================================
void CFade::SetFade(MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

}

