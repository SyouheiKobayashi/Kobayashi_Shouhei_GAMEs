//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// アクション処理 [action.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _ACTION_H_
#define _ACTION_H_
#include "main.h"
#include "scene2D.h"

#define ACTION_TEX	(1)
//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ アクションCLASS(<scene2D>の派生クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CAction : public CScene2D
{
public:
	

	CAction();
	~CAction();
	static HRESULT Load(void);//テクスチャを必要分読み込む
	static void UnLoad(void);//使用しているテクスチャを他の処理で消させないようにする
	static CAction *Create(D3DXVECTOR3 pos,OBJ_TYPE ObjType);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBulletType(OBJ_TYPE ObjType);//誰の弾かを判別
	

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[ACTION_TEX];//共有テクスチャへのポインタ
	CScene2D *m_apScene2D[ACTION_TEX];
	D3DXVECTOR3 m_move;//移動処理
	OBJ_TYPE m_ActionType;//誰の弾かを判別

	int m_nActionTime;//表示時間

	float m_fAngle;//現在の角度
	float m_fActionAngle;//鎌が自機に対して動く角度
	float m_fRange;//自機と鎌の距離

	

};

#endif