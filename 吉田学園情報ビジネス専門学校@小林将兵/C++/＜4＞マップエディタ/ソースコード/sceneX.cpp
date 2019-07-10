//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//Xモデル処理処理 [sceneX.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "sceneX.h"
#include "manager.h"
#include "debugLog.h"
#include "input.h"
#include "game.h"

//==============================================
//コンストラクタ
//==============================================
CSceneX::CSceneX(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	//? ※テクスチャ情報はここでNULLにしない
	//? ※モデルに貼り付けないため

	//m_pVtxBuff = NULL;		//頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}
//==============================================
//デストラクタ
//==============================================
CSceneX::~CSceneX()
{

}

//==============================================
//生成
//==============================================

CSceneX *CSceneX::Create(void)
{
	CSceneX *pSceneX = NULL;

	if (pSceneX == NULL)
	{
		pSceneX = new CSceneX;
		pSceneX->Init();
	}
	return pSceneX;
}
//==============================================
//初期化処理
//==============================================
HRESULT CSceneX::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//? ※Xファイルの読み込みは各cppで行いその情報を取得して使用する

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
	m_modelSize = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//サイズの変更
	Vtx();

	return S_OK;
}

//==============================================
//終了処理
//==============================================
void CSceneX::Uninit(void)
{
	//? ※メッシュの開放、マテリアルの開放は各cppで解放、削除している

	Release();
}

//==============================================
//更新処理
//==============================================
void CSceneX::Update(void)
{
	
}

//==============================================
//描画処理
//==============================================
void CSceneX::Draw(void)
{
	//デバイス情報の取得↓
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;
	

	D3DXMATRIX scale_matrix;//サイズ変更用

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//移動を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//モデルの拡大/縮小
	D3DXMatrixScaling(&scale_matrix, m_modelSize.x, m_modelSize.y, m_modelSize.z);
	mtxTrans = scale_matrix * mtxTrans;//拡大縮小*移動

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	mtxTrans = mtxRot * mtxTrans;//回転*(拡大縮小*移動)

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxTrans);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_pNumMat; nCntMat++)
	{

		//マテリアルの設定
		pDevice->SetMaterial(&m_pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//==============================================
//当たり判定に関する処理
//==============================================
void CSceneX::Vtx(void)
{
	int nNumVtx;
	DWORD sizeFVF;
	BYTE *pVtxBuff;

	m_VtxMin = D3DXVECTOR3(10000, 10000, 10000);	//最大値
	m_VtxMax = D3DXVECTOR3(-10000, -10000, -10000);	//最小値

	//頂点数の取得
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVer = 0; nCntVer < nNumVtx; nCntVer++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
													
		if (m_VtxMin.x >= vtx.x)
		{
			m_VtxMin.x = vtx.x;
		}
		if (m_VtxMin.y >= vtx.y)
		{
			m_VtxMin.y = vtx.y;
		}
		if (m_VtxMin.z >= vtx.z)
		{
			m_VtxMin.z = vtx.z;
		}
		
		if (m_VtxMax.x <= vtx.x)
		{
			m_VtxMax.x = vtx.x;
		}
		if (m_VtxMax.y <= vtx.y)
		{
			m_VtxMax.y = vtx.y;
		}
		if (m_VtxMax.z <= vtx.z)
		{
			m_VtxMax.z = vtx.z;
		}
		//サイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	D3DXVECTOR3 size = GetModelSize();
	m_VtxMin = D3DXVECTOR3(m_VtxMin.x * m_modelSize.x, m_VtxMin.y * m_modelSize.y, m_VtxMin.z * m_modelSize.z);
	m_VtxMax = D3DXVECTOR3(m_VtxMax.x * m_modelSize.x, m_VtxMax.y * m_modelSize.y, m_VtxMax.z * m_modelSize.z);

	m_VtxMin = D3DXVECTOR3(m_VtxMin.x, m_VtxMin.y, m_VtxMin.z);
	m_VtxMax = D3DXVECTOR3(m_VtxMax.x, m_VtxMax.y, m_VtxMax.z);


	//頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();

}

//==============================================
//使用読み込み
//==============================================
void CSceneX::BindObject(LPD3DXBUFFER buffMat, DWORD numMat, LPD3DXMESH mesh)
{
	m_pBuffMat = buffMat;
	m_pNumMat = numMat;
	m_pMesh = mesh;
}

//==============================================
//使用テクスチャの読み込み
//==============================================
void CSceneX::BindTexture(LPDIRECT3DTEXTURE9 textureInfo)
{
	m_pTexture = textureInfo;
}

//==============================================
//位置
//==============================================
void CSceneX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//==============================================
//移動
//==============================================
void CSceneX::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
	m_pos += m_move;
}
//==============================================
//回転,傾き
//==============================================
void CSceneX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//==============================================
//サイズの変更
//==============================================
void CSceneX::SetModelSize(float fModelSizeX, float fModelSizeY, float fModelSizeZ)
{
	m_modelSize = D3DXVECTOR3(fModelSizeX, fModelSizeY, fModelSizeZ);
}

//==============================================
//色・透明率
//==============================================
void CSceneX::SetColAlpha(D3DXCOLOR col)
{
	//マテリアルデータへのポインタを取得
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	if (m_pMat != NULL)
	{
		m_pMat->MatD3D.Diffuse = col;
		m_pMat->MatD3D.Ambient = col;
	}

}

//==============================================
//object.cppの個々のタイプを記憶
//==============================================
void CSceneX::SaveObjType(int nType)
{
	m_nSaveObjType = nType;
}

//==============================================
// 外部データを読み込むための処理
//==============================================
char *CSceneX::ReadLine(FILE *pFile, char *pDst)
{
	fgets(pDst, 256, pFile);

	while (1)//空き行の確認
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

char *CSceneX::GetLIneTop(char *pSrc)
{
	while (1)//空きマスの確認
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

int CSceneX::PopString(char *pSrc, char *pDst)
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