//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//フェード処理 [fade.cpp]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "fade.h"
#include "manager.h"
#include "scene.h"
#include "input.h"

//=====================================================================
//静的メンバ変数
//=====================================================================
CFade::FADE CFade::m_fade = FADE_NONE;

//=============================================================================
//コンストラクタ
//=============================================================================
CFade::CFade()
{
	m_pVtxBuff = NULL;//頂点バッファへのポインタ
}
//=============================================================================
//デストラクタ
//=============================================================================
CFade::~CFade()
{

}
//=============================================================================
//生成処理
//=============================================================================
CFade *CFade::Create(void)
{
	CFade *pFade = NULL;

	if (pFade == NULL)
	{
		pFade = new CFade;
		pFade->Init();
	}
	return pFade;
}
//=============================================================================
//初期化処理
//=============================================================================
HRESULT CFade::Init(void)
{
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

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの位置を設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
//=============================================================================
//終了処理
//=============================================================================
void CFade::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}


}
//=============================================================================
//更新処理
//=============================================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)//徐々に画面を表示する
	{
		if (m_fade == FADE_IN)
		{
			m_Color.a -= 0.02f;

			if (m_Color.a <= 0.0f)
			{
				m_Color.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}

		else if (m_fade == FADE_OUT)//徐々に画面を暗くする
		{
			m_Color.a += 0.02f;

			if (m_Color.a >= 1.0f)
			{
				m_Color.a = 1.0f;
				m_fade = FADE_IN;

				SetStateMode(m_NextMode);//次のモードの準備
			}
		}
	}

	VERTEX_2D*pVtx;

	 //頂点バッファをロックし、頂点データへのポインタを所得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報(カラー)の更新
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

}
//=============================================================================
//描画処理
//=============================================================================
void CFade::Draw(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
//設定
//=============================================================================
void CFade::SetFade(STATE_MODE nextMode)
{
	m_fade = FADE_OUT;
	m_NextMode = nextMode;
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

}