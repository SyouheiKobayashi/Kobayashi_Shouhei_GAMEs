//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//モデル処理 [model.cpp]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "scene.h"
#include "model.h"
#include "manager.h"
#include "input.h"
#include "debugLog.h"

//==============================================
//コンストラクタ
//==============================================
CModel::CModel()
{
	
	m_pVtxBuff = NULL;				//頂点バッファへのポインタ

}
//==============================================
//デストラクタ
//==============================================
CModel::~CModel()
{

}

//==============================================
//生成
//==============================================
CModel *CModel::Create(D3DXVECTOR3 pos)
{
	CModel *pModel = NULL;

	if (pModel == NULL)
	{
		pModel = new CModel;
		pModel->m_pos = pos;
		pModel->Init();
	}
	return pModel;
}
//==============================================
//初期化処理
//==============================================
HRESULT CModel::Init(void)
{
	return S_OK;
}

//==============================================
//終了処理
//==============================================
void CModel::Uninit(void)
{
	//使用した各CPPで削除・解放
}

//==============================================
//更新処理
//==============================================
void CModel::Update(void)
{

}

//==============================================
//描画処理
//==============================================
void CModel::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;
	D3DXMATRIX m_proj;
	

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	D3DXMATRIX mtxParent;

	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		// ワールドマトリックスの設定
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	

	// マテリアルデータへのポインタを取得
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();


	for (int nCntMat = 0; nCntMat < (int)m_pNumMat; nCntMat++)
	{

		// マテリアルの設定
		pDevice->SetMaterial(&m_pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);

		// モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);

	}
	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);

}

//==============================================
///モデルの読み込み
//==============================================
void CModel::BindModel(LPD3DXBUFFER buffMat, DWORD numMat, LPD3DXMESH mesh)
{
	m_pBuffMat = buffMat;
	m_pNumMat = numMat;
	m_pMesh = mesh;
}
//==============================================
///モデルに張り付ける画像の読み込み
//==============================================
void CModel::BindTexture(LPDIRECT3DTEXTURE9 textureInfo)
{
	m_pTexture = textureInfo;
}

//==============================================
///			モデルごとの親を決める
//==============================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}

//==============================================
///			モデルごとの位置を決める
//==============================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==============================================
//				モデルごとの回転
//==============================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//==============================================
//						色
//==============================================
void CModel::SetCol(D3DXCOLOR col)
{
	//マテリアルデータへのポインタを取得
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	if (m_pMat != NULL)
	{
		m_pMat->MatD3D.Diffuse = col;
		m_pMat->MatD3D.Ambient = col;
	}
}
