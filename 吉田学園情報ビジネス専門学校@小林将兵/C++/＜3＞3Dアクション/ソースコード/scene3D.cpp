//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					3Dポリゴン処理処理 [scene3D.h]
//			Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "scene3D.h"
#include "manager.h"
#include "debugLog.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "player.h"
//==============================================
//				3Dポリゴンのコンストラクタ
//==============================================
CScene3D::CScene3D(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	m_pTexture = NULL;								//テクスチャへのポインタ
	m_pVtxBuff = NULL;								//頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fSizeX = 0.0f;								//Xサイズ
	m_fSizeY = 0.0f;								//Yサイズ
	m_fSizeZ = 0.0f;								//Zサイズ
		
}
//==============================================
//			3D3Dポリゴンののデストラクタ
//==============================================
CScene3D::~CScene3D()
{

}

//==============================================
//				3Dポリゴンの生成
//==============================================

CScene3D *CScene3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float pos0, float pos1, float pos2, float pos3)
{
	CScene3D *pScene3D = NULL;

	if (pScene3D == NULL)
	{
		pScene3D = new CScene3D;
		pScene3D->m_pos = pos;
		pScene3D->m_fSizeX = size.x;
		pScene3D->m_fSizeZ = size.z;
		pScene3D->m_pos0 = pos0;
		pScene3D->m_pos1 = pos1;
		pScene3D->m_pos2 = pos2;
		pScene3D->m_pos3 = pos3;

		pScene3D->Init();

	}
	return pScene3D;
}
//==============================================
//				3Dポリゴンの初期化処理
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
	pVtx[0].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, m_fSizeY + m_pos0, m_fSizeZ + m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, m_fSizeY + m_pos1, m_fSizeZ + m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, m_fSizeY + m_pos2, -m_fSizeZ + m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, m_fSizeY + m_pos3, -m_fSizeZ + m_pos.z);

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
//				3Dポリゴンの終了処理
//==============================================
void CScene3D::Uninit(void)
{
	Release();
}

//==============================================
//			　3Dポリゴンの更新処理
//==============================================
void CScene3D::Update(void)
{
	CScene3D::CrossProduct();//外積内積処理

}

//==============================================
//			3Dポリゴンの描画処理
//==============================================
void CScene3D::Draw(void)
{
#if 0
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
#endif
}

//==============================================
//			画像情報の取得・反映
//==============================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 textureInfo)
{
	m_pTexture = textureInfo;
}


//==============================================
//			位置情報の取得・反映
//==============================================
void CScene3D::SetPos(D3DXVECTOR3 pos)
{

}

//==============================================
//			サイズ情報の取得・反映
//==============================================
void CScene3D::SetSize(float fSizeX, float fSizeY, float fSizeZ)
{
	m_fSizeX = fSizeX;
	m_fSizeY = fSizeY;
	m_fSizeZ = fSizeZ;
}

//==============================================
//				色情報の取得・反映
//==============================================
void CScene3D::SetCol(D3DXCOLOR col)
{
	m_col = col;
}


//==============================================
//			点滅情報の取得・反映
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
//							アニメーションSet処理
//=============================================================================
void CScene3D::SetTexAnim(int nCntAnim, int nWidth, int nHeight, int nPattern)
{
	//頂点情報の作成
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight));
	pVtx[1].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth) + (1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight));
	pVtx[2].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight) + (1.0f / nHeight));
	pVtx[3].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth) + (1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight) + (1.0f / nHeight));

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//							外積・内積判定処理
//=============================================================================
void CScene3D::CrossProduct(void)
{
	D3DXVECTOR3 vector1[6];
	D3DXVECTOR3 vector2[6];
	float fVectorPos[6];

	m_pPlayer = CGame::GetPlayer();

	if (m_pPlayer != NULL)
	{
		D3DXVECTOR3 playerPos = m_pPlayer->GetPos();//位置取得
		playerPos -= m_pos;

		//頂点情報の作成
		VERTEX_3D *pVtx;
		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//+ 外積判定処理
		vector1[0] = pVtx[0].pos - pVtx[1].pos;//中心点
		vector2[0] = playerPos - pVtx[0].pos;//プレイヤーとの中心点
		fVectorPos[0] = (vector1[0].z*vector2[0].x) - (vector1[0].x * vector2[0].z);


		vector1[1] = pVtx[1].pos - pVtx[3].pos;//中心点
		vector2[1] = playerPos - pVtx[1].pos;//プレイヤーとの中心点
		fVectorPos[1] = (vector1[1].z*vector2[1].x) - (vector1[1].x * vector2[1].z);

		vector1[2] = pVtx[3].pos - pVtx[2].pos;//中心点
		vector2[2] = playerPos - pVtx[3].pos;//プレイヤーとの中心点
		fVectorPos[2] = (vector1[2].z*vector2[2].x) - (vector1[2].x * vector2[2].z);


		vector1[3] = pVtx[2].pos - pVtx[0].pos;//中心点
		vector2[3] = playerPos - pVtx[2].pos;//プレイヤーとの中心点
		fVectorPos[3] = (vector1[3].z*vector2[3].x) - (vector1[3].x * vector2[3].z);

		vector1[4] = pVtx[2].pos - pVtx[1].pos;//中心点
		vector2[4] = playerPos - pVtx[2].pos;//プレイヤーとの中心点
		fVectorPos[4] = (vector1[4].z*vector2[4].x) - (vector1[4].x * vector2[4].z);

		vector1[5] = pVtx[1].pos - pVtx[2].pos;//中心点
		vector2[5] = playerPos - pVtx[1].pos;//プレイヤーとの中心点
		fVectorPos[5] = (vector1[5].z*vector2[5].x) - (vector1[5].x * vector2[5].z);

		//+ 内積判定処理
		if (fVectorPos[4] < 0 && fVectorPos[1] < 0 && fVectorPos[2] < 0)
		{
			m_bCheck = true;
			if (m_fSizeY <= playerPos.y)
			{
				m_DotPosY = SetHight(playerPos, true);//ポリゴン上の場合
			}
			else
			{
				m_DotPosY = playerPos.y;//ポリゴン下に入った場合
			}
		}
		
		else if (fVectorPos[5] < 0 && fVectorPos[3] < 0 && fVectorPos[0] < 0)
		{
			m_bCheck = true;
			if (m_fSizeY <= playerPos.y)
			{
				m_DotPosY = SetHight(playerPos, false);//ポリゴン上の場合
			}
			else
			{
				m_DotPosY = playerPos.y;//ポリゴン下に入った場合
			}
		}
		else//内積外
		{
			m_bCheck = false;

			if (playerPos.y <= 0)
			{
				m_DotPosY = 0;//基準する数値より下に下げない
			}
		}

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
//							乗るための当たり判定処理
//=============================================================================
float CScene3D::SetHight(D3DXVECTOR3 pos, bool bJudge)
{
	//頂点情報の作成
	VERTEX_3D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 V01 = (bJudge ? pVtx[3].pos : pVtx[0].pos);//軸となる頂点
	D3DXVECTOR3 V02 = pVtx[1].pos;//軸頂点とつながる頂点
	D3DXVECTOR3 V03 = pVtx[2].pos;//軸頂点とつながる頂点

	float fSave;//頂点情報の保存
	fSave = V01.y;
	//全体のy軸頂点を下げる
	V03.y -= V01.y;
	V02.y -= V01.y;
	V01.y -= V01.y;

	//法線
	D3DXVECTOR3 DotNor;
	m_vec0 = V02 - V01;
	m_vec1 = V03 - V01;
	D3DXVec3Cross(&DotNor, &m_vec0, &m_vec1);
	D3DXVec3Normalize(&DotNor, &DotNor);//正規化


	//VecAを求める(プレイヤーの頂点とポリゴンの頂点)
	D3DXVECTOR3 VecA;
	VecA = pos - V01;

	//逆算
	VecA.y = -((VecA.x * DotNor.x) + (VecA.z * DotNor.z)) / DotNor.y;

	float fData;
	fData = ((VecA.x * DotNor.x) + (VecA.y * DotNor.y) + (VecA.z *DotNor.z));

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return VecA.y + fSave + m_pos.y;
}

//==============================================
//	外部データの読み込みに関する処理(以下3つ↓↓↓)
//==============================================
char *CScene3D::ReadLine(FILE *pFile, char *pDst)
{
	fgets(pDst, 256, pFile);

	while (1)
	{
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			fgets(pDst, 256, pFile);

		}
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += 1;
		}
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += 1;
		}
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			fgets(pDst, 256, pFile);

		}
		else
		{
			break;
		}
	}

	return pDst;
}

char *CScene3D::GetLIneTop(char *pSrc)
{
	while (1)
	{
		if (memcmp(pSrc, " ", strlen(" ")) == 0)
		{
			pSrc += 1;
		}
		else if (memcmp(pSrc, "\t", strlen("\t")) == 0)
		{
			pSrc += 1;
		}
		else
		{
			break;
		}
	}

	return pSrc;
}

int CScene3D::PopString(char *pSrc, char *pDst)
{
	int nCnt = 0;

	while (1)
	{
		nCnt += 1;
		if (memcmp(pSrc, " ", strlen(" ")) == 0)
		{
			pSrc = "\0";
			break;
		}
		else
		{
			pSrc += 1;
		}
	}

	strcpy(pDst, pSrc);

	return nCnt;
}
