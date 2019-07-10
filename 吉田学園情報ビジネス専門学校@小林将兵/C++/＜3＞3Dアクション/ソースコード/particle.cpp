//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//				3Dパーティクル処理 [particle3D.cpp]
//			Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "manager.h"
#include "input.h"
#include "particle.h"
#include "scene3D.h"

//==============================================
//				静的メンバ変数
//==============================================

LPDIRECT3DTEXTURE9 CParticle3D::m_pTexture[MAX_PARTICLE3D] = {};
int CParticle3D::m_nNumTexture = NULL;
char CParticle3D::m_aFileNameTexture[MAX_PARTICLE3D][256] = {};

//==============================================
//					コンストラクタ
//==============================================
CParticle3D::CParticle3D(int nPriority, DATA_TYPE dataType) :CBillboard(nPriority, dataType)
{

}

//==============================================
//					デストラクタ
//==============================================
CParticle3D::~CParticle3D()
{

}

//==============================================
//					生成
//==============================================
CParticle3D *CParticle3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, bool bAngle, int DeleteTime, float fTransSize, int nType)
{

	CParticle3D *pParticle3D = NULL;
	if (pParticle3D == NULL)
	{
		pParticle3D = new CParticle3D;
		pParticle3D->BindTexture(m_pTexture[nType]);
		pParticle3D->SetPos(pos);
		pParticle3D->m_move = move;
		pParticle3D->m_rot = rot;
		pParticle3D->SetCol(col);
		pParticle3D->m_bAngle = bAngle;
		pParticle3D->SetSize(D3DXVECTOR3(1.0f,1.0f,0.0f));
		pParticle3D->m_nDeleteTime = DeleteTime;
		pParticle3D->m_fTransSize = fTransSize;
		pParticle3D->m_nType = nType;

		pParticle3D->Init();
	}
	return pParticle3D;
}

//==============================================
//				初期化処理
//==============================================
HRESULT CParticle3D::Init(void)
{
	m_nCnt = 0;
	m_PatternAnim = 0;
	m_fAngle = D3DX_PI;//角度
	m_fRange = 2.0f;//円の大きさ
	m_fActionAngle = 10.0f;
	CBillboard::Init();

	return S_OK;
}

//==============================================
//				終了処理
//==============================================
void CParticle3D::Uninit(void)
{

	CBillboard::Uninit();
}

//==============================================
//				更新処理
//==============================================
void CParticle3D::Update(void)
{
	//位置情報の取得 / 更新
	D3DXVECTOR3 pos = CBillboard::GetPos();
	D3DXVECTOR3 Fixed = CBillboard::GetPos();
	pos += m_move;

	//向き・回転情報の取得 / 更新
	D3DXVECTOR3 rot = CBillboard::GetRot();
	rot += m_rot;

	//カラー情報の取得
	D3DXCOLOR col = CBillboard::GetCol();

	//中心を軸に回転させる
	if (m_bAngle == true)
	{
		m_fActionAngle += -0.19f;//回転速度
		pos.x = m_fRange*(float)sin(m_fAngle + m_fActionAngle) + (Fixed.x);
		pos.z = m_fRange*(float)cos(m_fAngle + m_fActionAngle) + (Fixed.z);
		//pos.y += 2.0f;
	}
	//値の更新
		m_nDeleteTime--;
	if (m_nType == 0)
	{
		col.a -= 0.01f;
	}

	//情報の反映
	CBillboard::SetPos(pos);
	CBillboard::SetRot(rot);
	CBillboard::SetCol(col);
	CBillboard::SetParticle(m_fTransSize, CBillboard::GetCol());
	
	if (m_nType == 0)
	{
		CBillboard::SetTexAnim(2, 4, 3, true);
	}

	if (m_nDeleteTime <= 0)//消滅時間に達したら
	{
		CParticle3D::Uninit();
	}
}

//==============================================
//					描画処理
//==============================================
void CParticle3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillboard::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	//Zテストを元の値に戻す
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);


	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//==============================================
//			外部情報からテクスチャの読み込み
//==============================================
HRESULT CParticle3D::TextureLoad(void)
{
	FILE *pFile;

	char * pStrCur;//先頭文字列のポインタ
	char aLine[256];//文字列の読み込み
	char aStr[256];//文字列の抜き出し
	int nCntTexture = 0;//読み込むテクスチャ数をカウント

						//外部テキストの読み込み処理
	pFile = fopen("DATA\\TEXT\\PARTICLE.txt", "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CScene3D::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "TEX_LOAD", strlen("TEX_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CScene3D::GetLIneTop(&aLine[0]);

					if (memcmp(pStrCur, "NUM_TEXTURE = ", strlen("NUM_TEXTURE = ")) == 0)
					{
						pStrCur += strlen("NUM_TEXTURE = ");
						strcpy(aStr, pStrCur);
						m_nNumTexture = atoi(aStr);
					}

					if (memcmp(pStrCur, "TEXTURE_NAME ", strlen("TEXTURE_NAME ")) == 0)
					{

						pStrCur += strlen("TEXTURE_NAME ");

						strcpy(aStr, pStrCur);
						while (1)
						{
							if (pStrCur[strlen(pStrCur) - 1] != 'g')
							{
								pStrCur[strlen(pStrCur) - 1] = '\0';//改行文字をNULL文字に変換(参考サイト::http://hisashi.me/blog/?p=714)
							}
							else
							{
								break;
							}

							strcpy(&m_aFileNameTexture[nCntTexture][0], pStrCur);
						}

						nCntTexture += 1;
					}

					if (memcmp(pStrCur, "END_TEX_LOAD", strlen("END_TEX_LOAD")) == 0)
					{
						break;
					}
				}
			}
			if (memcmp(pStrCur, "END_TEX_LOAD", strlen("END_TEX_LOAD")) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);

	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	for (int nCnt = 0; nCnt < m_nNumTexture; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aFileNameTexture[nCnt], &m_pTexture[nCnt]);
	}

	return S_OK;
}
//==============================================
//				テクスチャの破棄
//==============================================
void CParticle3D::TextureUnLoad(void)
{
	for (int nCnt = 0; nCnt < m_nNumTexture; nCnt++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
