//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 2Dポリゴン処理 [player.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "scene2D.h"

class CBullet;
class CAction;
//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ プレイヤーCLASS(<scene2D>の派生クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CPlayer : public CScene2D
{
public:
	typedef enum
	{
		CURE = 0,//自己回復
		ADD_TIME,//タイム加算
		SICKLE//攻撃技
	}MODE;


	CPlayer();
	~CPlayer();
	static HRESULT Load(void);//テクスチャを必要分読み込む
	static void UnLoad(void);//使用しているテクスチャを他の処理で消させないようにする
	static CPlayer *Create(float fWIDTH,float fHEIGHT,int nLife);//(横サイズ,縦サイズ)

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBloodLife(int nSetBloodLife);
	int GetBloodLife(void) { return m_nBloodLife; }

	int GetMode(void) { return m_nActionMode; }//現在の状態を取得

	bool GetUse01(void) { return m_bUse01; }//使用可能状況の確認
	bool GetUse02(void) { return m_bUse02; }//使用可能状況の確認
	bool GetUse03(void) { return m_bUse03; }//使用可能状況の確認

	
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//共有テクスチャへのポインタ
	static CAction *m_pAction;

	D3DXVECTOR3 m_Move;
	//! <ポリゴンのアニメーションに関する変数>
	int m_CntAnim;//アニメーションの速さ
	int m_PatternAnim;//アニメーションの分割数
	int m_nBloodLife;
	int m_nActionPos;//アクション使用時のpos加算処理

	int m_nActionMode;//現在の状態

	MODE m_mode;

	bool m_bUse01, m_bUse02, m_bUse03,m_bTimeCheck;//使用可能かどうか


};




#endif