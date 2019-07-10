//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//				3Dパーティクル処理 [particle3D.h]
//			Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _PARTICLE3D_H_
#define _PARTICLE3D_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "billboard.h"

#define MAX_PARTICLE3D	(200)

class CBillboard;
//==============================================
//			ビルボードの派生 → 3Dパーティクル
//==============================================
class CParticle3D : public CBillboard
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CParticle3D(int nPriority = DRAW_BILLBOARD, DATA_TYPE nObjType = DATA_TYPE_BILLBOARD);
	~CParticle3D();
	static CParticle3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, bool bAngle,int DeleteTime, float fTransSize, int nType);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					基盤関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				画像の読み込み・解放
	// @   @   @   @   @   @   @   @   @   @   @   @
	static HRESULT TextureLoad(void);
	static void TextureUnLoad(void);


private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_PARTICLE3D];	//共有テクスチャへのポインタ
													
	//外部テキストの読み込み処理
	static int m_nNumTexture;								//読み込むテクスチャの数
	static char m_aFileNameTexture[MAX_PARTICLE3D][256];	//使用するテクスチャの名前
	
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//回転量
	int m_nType;			//適用させる画像タイプ
	float m_fTransSize;		//時間変化によるサイズ変換用
	int m_nDeleteTime;		//自然消滅する時間

	//アニメーション処理変数
	int m_nCnt;
	int m_PatternAnim;

	float m_fAngle;//現在の角度
	float m_fActionAngle;//中心を軸に回転
	float m_fRange;//軸との距離

	bool m_bAngle;

};

#endif