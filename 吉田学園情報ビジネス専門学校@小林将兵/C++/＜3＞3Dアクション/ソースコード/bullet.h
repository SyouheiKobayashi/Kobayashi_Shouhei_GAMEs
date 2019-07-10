//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//				バレット処理 [bullet.h]
//			Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _BULLET_H_
#define _BULLET_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "billboard.h"

#define BULLET_TEX_MAX	(2)

class CPlayer;
class CSound;
//==============================================
//			ビルボードの派生 → バレット
//==============================================
class CBullet : public CBillboard
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CBullet(int nPriority = DRAW_BULLET, DATA_TYPE nObjType = DATA_TYPE_BILLBOARD);
	~CBullet();
	static CBullet *Create(int nLife,D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nTexType, int nAnimSpeed, int nWidth, int nHight, bool bLoop);

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
	static CSound *m_pSound;
	CPlayer *m_pPlayer;
	static const char *m_apTexName[];//使用するテクスチャ
	static LPDIRECT3DTEXTURE9 m_apTexture[BULLET_TEX_MAX];//共有テクスチャへのポインタ
	
	int m_nType;

	int m_nLife;//表示時間(寿命)

	//アニメーションに関する変数
	int m_nAnimSpeed;
	int m_nWidth;
	int m_nHight;
	bool m_bLoop;
};

#endif