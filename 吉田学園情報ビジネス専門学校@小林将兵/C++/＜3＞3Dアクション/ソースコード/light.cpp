//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//カメラ処理 [camera.cpp]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "light.h"
#include "input.h"
#include "manager.h"

//==============================================
//コンストラクタ
//==============================================
CLight::CLight()
{
	

}
//==============================================
//デストラクタ
//==============================================
CLight::~CLight()
{

}
//==============================================
//生成
//==============================================
CLight *CLight::Create(void)
{
	CLight *pLight = NULL;

	if (pLight == NULL)
	{
		pLight = new CLight;
		pLight->Init();

	}
	return pLight;
}

//==============================================
//初期化
//==============================================
void CLight::Init(void)
{
	//ライトの初期化
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		
		m_Light[nCnt] = {};
		m_vecDir[nCnt] = {};

	}

	SetDirectionla(0,D3DXCOLOR(10.0f,10.0f,10.0f,10.0f), D3DXVECTOR3(-0.5f,-1.0f,1.0f));
	SetDirectionla(1, D3DXCOLOR(10.0f, 10.0f, 10.0f, 10.0f), D3DXVECTOR3(0.5f, -1.0f, 1.0f));
	//SetPoint(0, D3DXCOLOR(10.0f, 10.0f, 10.0f, 10.0f), D3DXVECTOR3(-100.0f, 1.0f, 0.0f),D3DXVECTOR3(-0.5f, -1.0f, 1.0f));
	//SetSpot(0, D3DXCOLOR(100000.0f, 100000.0f, 100000.0f, 100000.0f), D3DXVECTOR3(100.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

}

//==============================================
//終了
//==============================================
void CLight::Uninit(void)
{
	delete this;
}

//==============================================
//更新
//==============================================
void CLight::Update(void)
{

}

//==============================================
//				ディレクショナルライト
//==============================================
void CLight::SetDirectionla(int lightNum, D3DXCOLOR col, D3DXVECTOR3 rot)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));

	///光源の種類:平行光源(ディレクショナル光源)
	m_Light[lightNum].Type = D3DLIGHT_DIRECTIONAL;
	///拡散光
	m_Light[lightNum].Diffuse.r = col.r;
	m_Light[lightNum].Diffuse.g = col.g;
	m_Light[lightNum].Diffuse.b = col.b;
	m_Light[lightNum].Diffuse.a = col.a;
	///環境光(明るくなる)
	m_Light[lightNum].Ambient.r = 0.1f;
	m_Light[lightNum].Ambient.g = 0.1f;
	m_Light[lightNum].Ambient.b = 0.1f;
	m_Light[lightNum].Ambient.a = 1.0f;
	///光源の向き
	///スポット光源、ディレクショナル光源の場合のみ意味がある。
	m_Light[lightNum].Direction.x = rot.x;
	m_Light[lightNum].Direction.y = rot.y;
	m_Light[lightNum].Direction.z = rot.z;
	//光源の有効範囲:1000
	m_Light[lightNum].Range = 1000.0f;

	//ライトをセット
	pDevice->SetLight(lightNum, &m_Light[lightNum]);
	//ライトを有効にする。
	pDevice->LightEnable(lightNum, TRUE);
	//ライティングします。
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//ライトとは別軸でライティング効果を生みます。
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x00444444);
}

void CLight::SetPoint(int lightNum, D3DXCOLOR col, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));

	///光源の種類:平行光源(ディレクショナル光源)
	m_Light[lightNum].Type = D3DLIGHT_POINT;
	///拡散光
	m_Light[lightNum].Diffuse.r = col.r;
	m_Light[lightNum].Diffuse.g = col.g;
	m_Light[lightNum].Diffuse.b = col.b;
	m_Light[lightNum].Diffuse.a = col.a;
	///環境光(明るくなる)
	m_Light[lightNum].Ambient.r = 0.1f;
	m_Light[lightNum].Ambient.g = 0.1f;
	m_Light[lightNum].Ambient.b = 0.1f;
	m_Light[lightNum].Ambient.a = 1.0f;

	///光源の位置
	m_Light[lightNum].Position.x = pos.x;
	m_Light[lightNum].Position.y = pos.y;
	m_Light[lightNum].Position.z = pos.z;

	///光源の向き
	///スポット光源、ディレクショナル光源の場合のみ意味がある。
	m_Light[lightNum].Direction.x = rot.x;
	m_Light[lightNum].Direction.y = rot.y;
	m_Light[lightNum].Direction.z = rot.z;

	//ライトの強度、
	m_Light[lightNum].Attenuation0 = 0.0f;
	m_Light[lightNum].Attenuation1 = 0.0f;
	m_Light[lightNum].Attenuation2 = 0.0f;

	//光源の有効範囲:1000
	m_Light[lightNum].Range = 1000.0f;

	//ライトをセット
	pDevice->SetLight(lightNum, &m_Light[lightNum]);
	//ライトを有効にする。
	pDevice->LightEnable(lightNum, TRUE);
	//ライティングします。
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//ライトとは別軸でライティング効果を生みます。
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x00444444);
}

void CLight::SetSpot(int lightNum, D3DXCOLOR col, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	ZeroMemory(&m_Light[lightNum], sizeof(D3DLIGHT9));

	///光源の種類:平行光源(ディレクショナル光源)
	m_Light[lightNum].Type = D3DLIGHT_SPOT;
	///拡散光
	m_Light[lightNum].Diffuse.r = col.r;
	m_Light[lightNum].Diffuse.g = col.g;
	m_Light[lightNum].Diffuse.b = col.b;
	m_Light[lightNum].Diffuse.a = col.a;
	///環境光(明るくなる)
	m_Light[lightNum].Ambient.r = 0.1f;
	m_Light[lightNum].Ambient.g = 0.1f;
	m_Light[lightNum].Ambient.b = 0.1f;
	m_Light[lightNum].Ambient.a = 1.0f;

	///光源の位置
	m_Light[lightNum].Position.x = pos.x;
	m_Light[lightNum].Position.y = pos.y;
	m_Light[lightNum].Position.z = pos.z;

	///光源の向き
	///スポット光源、ディレクショナル光源の場合のみ意味がある。
	m_Light[lightNum].Direction.x = rot.x;
	m_Light[lightNum].Direction.y = rot.y;
	m_Light[lightNum].Direction.z = rot.z;

	//ライトの強度、
	m_Light[lightNum].Attenuation0 = 1.0f;
	m_Light[lightNum].Attenuation1 = 1.0f;
	m_Light[lightNum].Attenuation2 = 1.0f;

	m_Light[lightNum].Theta = 2.00f;	//よく光が当たる場所
	m_Light[lightNum].Phi = 3.00f;	//若干光が当たる場所

	
	//光源の有効範囲 / 最大1000.0f
	m_Light[lightNum].Range = 1000.0f;

	//ライトをセット
	pDevice->SetLight(lightNum, &m_Light[lightNum]);
	//ライトを有効にする。
	pDevice->LightEnable(lightNum, TRUE);
	//ライティングします。
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//ライトとは別軸でライティング効果を生みます。
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x00444444);
}