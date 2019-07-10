//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//						ビルボード処理 [billboard.h]
//				Author : Kobayashi_Sho-hei/小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "scene.h"

//==============================================
//					マクロ定義
//==============================================
#define TEXBILLBOARD_NAME	("DATA/TEXTURE/bullet000.png")
#define TEXBILLBOARD_DEFAULTSIZE	(5)

//==============================================
//				シーン派生 → ビルボード
//==============================================
class CBillboard : public CScene
{
public:

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CBillboard(int nPriority = DRAW_BILLBOARD, DATA_TYPE nObjType = DATA_TYPE_BILLBOARD);
	~CBillboard();
	static CBillboard *Create(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					基盤関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Draw02(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			  テクスチャ情報の受け取り
	// @   @   @   @   @   @   @   @   @   @   @   @
	void BindTexture(LPDIRECT3DTEXTURE9 textureInfo);


	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size;}
	D3DXCOLOR GetCol(void) { return m_col;}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	void SetSize(D3DXVECTOR3 size);
	void SetChangeSize(float fsize);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetCol(D3DXCOLOR col);
	void SetTexAnim(int nCntAnim, int nWidth, int nHight, bool bLoop);	//アニメーション(コマ送り)
	void SetParticle(float fTransSize, D3DXCOLOR col);
	void SetSpin(float fSpinSpeed);										//回転
	void FlashTex(void);												//点滅

private:
	LPDIRECT3DTEXTURE9		m_pTexture;	//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_rot;		//向き
	D3DXCOLOR m_col;		//色

	//サイズ変更
	D3DXVECTOR3 m_size;

	//アニメーション処理
	int m_nCnt;
	int m_PatternAnim;

	//回転
	float m_fAngle;							//角度
	float m_fLengs;							//距離
	float m_fSpinSpeed;						//回転速度

	//点滅に関する処理
	bool m_bFlash;							//透明率の切り替え
	float fFlashCnt;						//点滅する速度

};




#endif