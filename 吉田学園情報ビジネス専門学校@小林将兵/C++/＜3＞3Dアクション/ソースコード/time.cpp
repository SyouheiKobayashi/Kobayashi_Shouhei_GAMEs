//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					時間処理 [time.cpp]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "time.h"
#include "number.h"
#include "fade.h"
#include "timeCharge.h"
#include "game.h"

//==============================================
//					コンストラクタ
//==============================================
CTime::CTime(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_nTimeDigit[nCnt] = 0;
		m_apNumber[nCnt] = NULL;
	}
}

//==============================================
//					デストラクタ
//==============================================
CTime::~CTime()
{

}

//==============================================
//						生成
//==============================================
CTime *CTime::Create(int fTime,D3DXVECTOR2 size, D3DXVECTOR2 pos)
{
	CTime *pTime = NULL;

	if (pTime == NULL)
	{
		pTime = new CTime;
		pTime->m_nTimeSet = fTime;
		pTime->m_size = size;
		pTime->m_pos = pos;
		pTime->Init();
	}

	return pTime;
}
//==============================================
//				初期化処理
//==============================================
HRESULT CTime::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apNumber[nCnt] = new CNumber;
		m_apNumber[nCnt]->Init();
		m_apNumber[nCnt]->SetSize(m_size.x, m_size.y);
		m_apNumber[nCnt]->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), m_size.x*2.0f, nCnt);
	}
	
	m_nTime = m_nTimeSet * 100;
	return S_OK;
}
//==============================================
//				終了処理
//==============================================
void CTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		//↓呼び出したnumber処理を使う
		m_apNumber[nCnt]->Uninit();
		m_apNumber[nCnt] = NULL;
	}

	Release();
}
//==============================================
//				更新処理
//==============================================
void CTime::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumber[nCnt]->Update();
		m_apNumber[nCnt]->SetNumber(m_nTimeDigit[nCnt]);//カウント分間隔をあける
	}

	if (CManager::GetMode() == CManager::MODE_CHARGETIME)//チャージタイム
	{
		CTimeCharge *pChargeTime = CManager::GetTimeCharge();
		m_nTime = pChargeTime->GetChargeTime() * 100;

		if (pChargeTime->GetFlag() == true)//終了フラグが立っているなら
		{
			for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
			{
				m_apNumber[nCnt]->SetScale(12, 1.5f);
			}
		}
	}
	if (CManager::GetMode() == CManager::MODE_GAME)//ゲームであれば減算する
	{
		if (CGame::GetPageStop() == true)
		{

			m_nTime -= 2;
			if (m_nTime <= 0)
			{
				m_nTime = 0;
			}
		}
		
	}

	m_nTimeDigit[0] = m_nTime % 100000 / 10000;
	m_nTimeDigit[1] = m_nTime % 10000 / 1000;
	m_nTimeDigit[2] = m_nTime % 1000 / 100;

}
//==============================================
//					描画処理
//==============================================
void CTime::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}

void CTime::SetDemeritTime(int nTime)
{
	m_nTime -= nTime * 100;
}
