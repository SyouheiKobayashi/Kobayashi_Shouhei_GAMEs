//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 2Dポリゴン処理 [scene2D.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
#include "main.h"
#include "scene.h"

//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ シーン2DCLASS(<Scene>の派生クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CScene2D : public CScene
{
public:
	//画像の拡大縮小
	typedef enum
	{
		Big = 0,//拡大
		Small,//縮小
		ALL
	}SIZE;
	
	CScene2D(int nPriority);//デフォルト引数
	~CScene2D();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	D3DXVECTOR3 GetPos(void) { return m_pos; }//生成したポリゴンの位置を取得する
	float GetHeight(void) { return m_fHEIGHT; }
	float GetWidth(void) { return m_fWIDTH; }
	void SetPos(D3DXVECTOR3 pos);//得た情報を反映させる
	void SetCol(D3DXCOLOR col);
	void SetSize(float fWIDTH, float fHEIGHT);//ポリゴンのサイズ変更
	void SetRot(float fSpin);
	void SetTimeRot(int nTime);

	//テクスチャのアニメーション処理(アニメーションの速さ,横分割数,縦分割数,パターン数)
	void SetTexAnim(int nCntAnim, int nWidth,int nHight,int nPattern);

	//テクスチャのスクロール処理(スクロースの速さ,+-でスクロール方向の変更,縦スクか横スクか)
	void SetScroll(float fscrollSpeed,int nScrollCnt,int nScrollType);
	void BindTexture(LPDIRECT3DTEXTURE9 m_pShareTexture);

	//体力設定
	void SetLife(int nSetLife);
	int GetLife(void) { return m_nLife; }

private:
	//! メンバ変数↓
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ

	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	float					m_fWIDTH;
	float					m_fHEIGHT;

	//! <ポリゴンの回転に関する変数>
	float m_fAngle;//角度
	float m_fLengs;//距離
	float m_fSpin;//回転
	//! <ポリゴンの拡大・縮小に関する変数>
	float m_fSize;
	SIZE m_size = Big;//列挙型
	int m_nLife;//体力,時間経過

};




#endif