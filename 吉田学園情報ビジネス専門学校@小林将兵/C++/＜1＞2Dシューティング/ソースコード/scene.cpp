//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// オブジェクト処理 [scene.cpp]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "scene.h"
#include "renderer.h"
//#include "scene2D.h"


//! 静的処理
CScene *CScene::m_apScene[OBJ_DRAW::DRAW_ALL][MAX_SCENE] = {};
int CScene::m_NumALL = 0;
//=============================================================================
//+ オブジェクトのコンストラクタ
//=============================================================================
CScene::CScene()
{
	
}

//=============================================================================
//+ オブジェクトのコンストラクタ
//=============================================================================
CScene::CScene(int nPriority = 3)
{
	for (int nCntS = 0; nCntS < MAX_SCENE; nCntS++)
	{
			if (m_apScene[nPriority][nCntS] == NULL)
			{
				m_apScene[nPriority][nCntS] = this;//cSnene2Dがはいる
				m_nID = nCntS;//自分自身の番号を覚えさせる
				m_nPriority = nPriority;
				m_NumALL++;
				break;
			}
	}
}

//=============================================================================
//+ オブジェクトのデストラクタ
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
//+ オブジェクトの終了・データ解放処理
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntP = 0; nCntP < OBJ_DRAW::DRAW_ALL; nCntP++)
	{
		for (int nCntS = 0; nCntS < MAX_SCENE; nCntS++)
		{
			if (m_apScene[nCntP][nCntS] != NULL)//何かしらの情報が入っていた場合
			{
				m_apScene[nCntP][nCntS]->Uninit();

				delete m_apScene[nCntP][nCntS];//中の情報を捨てる
				m_apScene[nCntP][nCntS] = NULL;//NULLに戻す
			}
		}
	}
}
//=============================================================================
//+ オブジェクトの更新処理
//=============================================================================
void CScene::UpdateAll()
{
	for (int nCntP = 0; nCntP < OBJ_DRAW::DRAW_ALL; nCntP++)
	{
		for (int nCntS = 0; nCntS < MAX_SCENE; nCntS++)
		{
			if (m_apScene[nCntP][nCntS] != NULL)//情報が入っているなら
			{
				m_apScene[nCntP][nCntS]->Update();
			}
		}
	}
}

void CScene::UpdateAll(OBJ_DRAW DrowType)
{

	for (int nCntS = 0; nCntS < MAX_SCENE; nCntS++)
	{
		if (m_apScene[DrowType][nCntS] != NULL)//情報が入っているなら
		{
			m_apScene[DrowType][nCntS]->Update();
		}
	}

}
//=============================================================================
//+ オブジェクトの描画処理
//=============================================================================
void CScene::DrawAll()
{
	for (int nCntP = 0; nCntP < OBJ_DRAW::DRAW_ALL; nCntP++)
	{
		for (int nCntS = 0; nCntS < MAX_SCENE; nCntS++)
		{
			if (m_apScene[nCntP][nCntS] != NULL)//情報が入っているなら
			{
				m_apScene[nCntP][nCntS]->Draw();
			}
		}
	}
}
//=============================================================================
//+ オブジェクトのdelete処理
//=============================================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)//情報が入っているなら
	{
		int nID;//m_nIDの情報を覚えさせておく(deleteした瞬間m_nIDの情報が失われるため)
		nID = m_nID;

		int nPriority;//優先順位の記憶(deleteした瞬間m_nPriorityの情報が失われるため)
		nPriority = m_nPriority;

		//delete処理↓
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_NumALL--;
	}
}

//=============================================================================
//+ objのSet処理
//=============================================================================
void CScene::SetObjType(OBJ_TYPE ObjType)//
{
	m_ObjType= ObjType;//他処理からobjの情報を取得する
}




