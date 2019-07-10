//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 制限時間処理 [time.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#include "scene.h"

#define MAX_DIGIT	(3)
class CNumber;
//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ シーン2DCLASS(<Scene>の派生クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CTime : public CScene
{
public:
	CTime();
	~CTime();

	static CTime *Create(void);//スコアの生成処理

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos);//得た情報を反映させる

	void AddScore(int nValue);//得点

	int GetTimeNow(void) { return m_nTimeNow; }//ゲーム上の現在の時間
	int GetEnemyCreateTime(void) { return m_nEnemyCreateTime; }//敵生成時間
	bool GetPlayerFlag(void) { return m_bPlayerFlag; }//時間管理によるプレイヤーの有無

	void SetLife(int nAddLife);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;			// ポリゴンの位置

	CNumber *m_apNumber[MAX_DIGIT];//number処理を扱いため
	int m_nTimeNow;//現在の時間
	int m_nTimeDigit[MAX_DIGIT];//桁数

	int m_nEnemyCreateTime;//敵の生成する時間

	int m_nUnintTime;//次の画面遷移までの時間
	bool m_nCheck;//UIを複数生成させない

	bool m_bPlayerFlag;//時間管理によるプレイヤーの有無
	

};




#endif