//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//シーン処理 [scene.cpp]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "scene.h"
#include "renderer.h"
#include "debugLog.h"

//!静的処理
int CScene::m_NumALL = 0;
int CScene::m_nNumPriority[DRAW_MAX] = {};
CScene *CScene::m_pTop[DRAW_MAX] = {};
CScene *CScene::m_pCur[DRAW_MAX] = {};
//? ==============================================
//?+ コンストラクタ
//? ==============================================
CScene::CScene(int nPriority, DATA_TYPE nObjType)
{
	m_nPriority = nPriority;
	m_DataType = nObjType;
	m_bDeath = false;

	if (m_pTop[nPriority] == NULL)
	{
		m_pTop[nPriority] = this;//先頭データの生成

	}
	if (m_pCur[nPriority] != NULL)
	{
		m_pCur[nPriority]->m_pNext = this;//現在の最後尾のデータより次に新しくデータ生成

	}

	this->m_pPrev = m_pCur[nPriority];//カレント中身なし&&NULL
	this->m_pNext = NULL;
	m_pCur[nPriority] = this;//scene情報を入れる

	m_nNumPriority[m_nPriority]++;

	m_NumALL++;//生成されたobjの総数を増やす
}

//? ==============================================
//?+ デストラクタ
//? ==============================================
CScene::~CScene()
{

}

//? ==============================================
//?+ 終了・全データ解放処理
//? ==============================================
void CScene::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < DRAW_MAX; nCnt++)
	{
		CScene *pTop, *pNext;
		pNext = m_pTop[nCnt];

		while (pNext != NULL)//NULLになるまで
		{
			pTop = pNext;
			pNext = pTop->m_pNext;
			pTop->Uninit();
		}

		//! ------------------------------------------------
		//!+ 死亡フラグ対象objの削除
		//! ------------------------------------------------
		CScene *pSceneTop;
		pSceneTop = m_pTop[nCnt];
		while (pSceneTop != NULL)//NULLになるまで
		{
			CScene *pSceneNext;
			pSceneNext = pSceneTop->m_pNext;//情報の記憶
			if (pSceneTop->m_bDeath == true)//死亡フラグがtrueなら...
			{
				pSceneTop->Delete();
			}
			pSceneTop = pSceneNext;
		}

		m_pTop[nCnt] = NULL;
		m_pCur[nCnt] = NULL;
	}
	m_NumALL = 0;//生成されたobjの総数を0に...
}

//? ==============================================
//?+ 更新処理
//? ==============================================
void CScene::UpdateAll()
{	
	for (int nCnt = 0; nCnt < DRAW_MAX; nCnt++)
	{


		CScene *pSceneTop;
		pSceneTop = m_pTop[nCnt];

		while (pSceneTop != NULL)//NULLになるまで
		{
			CScene *pSceneNext;
			pSceneNext = pSceneTop->m_pNext;//←<記憶するIDの方法と似ている> && 情報が消えないように...
			pSceneTop->Update();
 			pSceneTop = pSceneNext;
		}
	}
		//! ------------------------------------------------
		//!+ 死亡フラグ対象objの削除
		//! ------------------------------------------------
	for (int nCnt = 0; nCnt < DRAW_MAX; nCnt++)
	{
		CScene *pSceneTop;
		pSceneTop = m_pTop[nCnt];
		while (pSceneTop != NULL)//NULLになるまで
		{
			CScene *pSceneNext;
			pSceneNext = pSceneTop->m_pNext;//情報の記憶
			if (pSceneTop->m_bDeath == true)//死亡フラグがtrueなら...
			{
				pSceneTop->Delete();
			}
			pSceneTop = pSceneNext;
		}
	}
}

//? ==============================================
//?+ 描画処理
//? ==============================================
void CScene::DrawAll()
{
	for (int nCnt = 0; nCnt < DRAW_MAX; nCnt++)
	{
		CScene *pSceneTop;
		pSceneTop = m_pTop[nCnt];

		while (pSceneTop != NULL)//NULLになるまで
		{
			CScene *pSceneNext;
			pSceneNext = pSceneTop->m_pNext;//←<記憶するIDの方法と似ている> && 情報が消えないように...
			pSceneTop->Draw();
			pSceneTop = pSceneNext;
		}
	}
}
//? ==============================================
//?+ 死亡フラグをたてる
//? ==============================================
void CScene::Release(void)
{
	m_bDeath = true;
}

//? ==============================================
//?+ 死亡フラグがたっている対象objの削除
//? ==============================================
void  CScene::Delete(void)
{
		if (m_pPrev != NULL)//topとcurの間を消す場合...
		{
			m_pPrev->m_pNext = m_pNext;
		}
		if (m_pNext != NULL)//topとcurの間を消す場合...
		{
			m_pNext->m_pPrev = m_pPrev;
		}
		if (this == m_pTop[m_nPriority])	//topを消す場合...
		{
			m_pTop[m_nPriority] = m_pTop[m_nPriority]->m_pNext;
		}

		if (this == m_pCur[m_nPriority])//curを消す場合...
		{
			m_pCur[m_nPriority] = m_pCur[m_nPriority]->m_pPrev;
		}

		m_nNumPriority[m_nPriority]--;
	delete this;//条件を満たした後に自身を消す

	

	m_NumALL--;//生成されたobjの総数を減らす
}

//? ==============================================
//?+ 死亡フラグがたっている対象objの削除
//? ==============================================
void CScene::SetDataType(DATA_TYPE dataType)//
{
	m_DataType = dataType;//他処理からobjの情報を取得する
}
