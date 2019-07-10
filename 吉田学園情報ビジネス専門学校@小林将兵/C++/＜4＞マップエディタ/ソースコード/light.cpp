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
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		m_light[nCnt] = {};
		m_vecDir[nCnt] = {};
	}

	SetLight(0, D3DXVECTOR3(0.5f, -0.7f, 0.2f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetLight(1, D3DXVECTOR3(3.5f, 0.1f, -0.8f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetLight(2, D3DXVECTOR3(0.1f, -0.8f, 2.1f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//? *指先を軸にpos数値通りにある程度動かせばライトがどの方向に向けて光を当てているのか大体わかるはず
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
//ライトの設定
//==============================================
void CLight::SetLight(int nLightNumber, D3DXVECTOR3 pos, D3DXCOLOR col)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	ZeroMemory(&m_light, sizeof(D3DLIGHT9));// ライトのクリア

	m_light[nLightNumber].Type = D3DLIGHT_DIRECTIONAL;// ライトの種類を設定

	m_light[nLightNumber].Diffuse = col;// ライトの拡散光を設定

	// ライトの方向の設定

	m_vecDir[nLightNumber] = pos;

	D3DXVec3Normalize(&m_vecDir[nLightNumber], &m_vecDir[nLightNumber]);
	m_light[nLightNumber].Direction = m_vecDir[nLightNumber];

	pDevice->SetLight(nLightNumber, &m_light[nLightNumber]);	// ライトのタイプ設定

	pDevice->LightEnable(nLightNumber, TRUE);// ライトを有効に
}

