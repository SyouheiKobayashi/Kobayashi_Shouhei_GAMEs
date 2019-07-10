//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 弾・バレット処理 [bullet.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
#include "scene2D.h"

#define MAX_B_TEX	(2)
//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ 弾・バレットCLASS(<scene2D>の派生クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CBullet : public CScene2D
{
public:
	typedef enum//アクションによる敵の弾だけを消すために必要な処理
	{
		NONE = 0,
		PLAYER,
		ENEMY
	}TYPE;

	typedef enum//弾射出のバリエーションパターン
	{
		PATTERN_PLAYER = 0,
		PATTERN01,
		PATTERN02,
		PATTERN03,
		PATTERN04,
		PATTERN05,
		PATTERN06,
		PATTERN07,
		PATTERN08,
		PATTERN09,
		PATTERN_ALL
	}BULLET_PATTERN;

	CBullet();
	~CBullet();
	static HRESULT Load(void);//テクスチャを必要分読み込む
	static void UnLoad(void);//使用しているテクスチャを他の処理で消させないようにする
	static CBullet *Create(D3DXVECTOR3 pos, int size, OBJ_TYPE ObjType, TYPE type,int nTexType, BULLET_PATTERN pattern);//弾の生成(位置情報,弾の判別)

	HRESULT Init(BULLET_PATTERN pattern);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBulletType(OBJ_TYPE ObjType, TYPE type);//誰の弾かを判別

	int GetType(void) { return m_nRType; }

	bool GetPauseFlag(void) { return m_bPause; }//現在のフラグの取得

	

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_B_TEX];//共有テクスチャへのポインタ
	CScene2D *m_apScene2D[MAX_B_TEX];
	D3DXVECTOR3 m_move;//移動処理
	OBJ_TYPE m_BulletType;//誰の弾かを判別

	int m_nRType;
	bool m_bPause;

	int m_nBulletPattern;

	D3DXVECTOR3 m_PlayerPos;
	D3DXVECTOR3 m_EnemyPos;
	bool m_Die;
};

#endif