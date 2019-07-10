//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 敵・エネミー処理 [enemy.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "scene2D.h"

//#define MAX_ENEMY_TYPE	(5)

class CBullet;
//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ 敵・エネミーCLASS(<scene2D>の派生クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CEnemy : public CScene2D
{
public:

	typedef enum
	{
		ENEMY01 = 0,
		ENEMY02,
		ENEMY03,
		ENEMY04,
		ENEMY05,
		ENEMY_BOSS,
		ENEMY_ALL
	}ENEMY_TYPE;

	CEnemy();
	~CEnemy();
	static HRESULT Load(void);//テクスチャを必要分読み込む
	static void UnLoad(void);//使用しているテクスチャを他の処理で消させないようにする
	static CEnemy *Create(int nType ,int X_pos, int Y_pos,int Life);//(縦サイズ,横サイズ,ライフ)

	HRESULT Init(int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void EnemyPattern(void);

	static CBullet *GetBullet(void) { return m_pBullet; }
	int GetEnemyType(void) { return m_nEnemyType; }//タイプ情報の取得

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[ENEMY_ALL];//共有テクスチャへのポインタ
	static CBullet *m_pBullet;

	//! <ポリゴンのアニメーションに関する変数>
	int m_CntAnim;//アニメーションの速さ
	int m_PatternAnim;//アニメーションの分割数

	
	D3DXVECTOR3 m_move;//移動変数
	int m_nIntervalAttack;//攻撃間隔変数

	int m_nEnemyType;
	int m_nRndPattern;//パターン

	D3DXVECTOR3 m_PlayerPos;
	D3DXVECTOR3 m_EnemyPos;
};




#endif