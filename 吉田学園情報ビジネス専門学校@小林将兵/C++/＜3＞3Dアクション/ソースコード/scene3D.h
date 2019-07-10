//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					3Dポリゴン処理処理 [scene3D.h]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//=================================================
//		include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "scene.h"

class CPlayer;
//==============================================
//			シーンの派生 → 3Dポリゴン
//==============================================
class CScene3D : public CScene
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CScene3D(int nPriority = DRAW_3D, DATA_TYPE dataType = DATA_TYPE_3D);
	~CScene3D();
	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,float pos0, float pos1, float pos2, float pos3);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					基盤関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	void BindTexture(LPDIRECT3DTEXTURE9 textureInfo);			//画像情報をもらい、それを描画
	void SetPos(D3DXVECTOR3 pos);								//位置
	void SetSize(float fSizeX, float fSizeY, float fSizeZ);		//サイズ
	void SetCol(D3DXCOLOR col);									//色
	void FlashTex(void);										//点滅
	void SetTexAnim(int nAnimSpeed, int nWidth,					//分割アニメーション
		int nHeight, int nPattern);	
	//(アニメーションの速さ、横の分割数、縦の分割数、計算で割り出される)

	//ポリゴンの当たり判定
	void CrossProduct(void);//外積と内積
	float SetHight(D3DXVECTOR3 pos, bool bJudge);//高さを反映させるための情報を得る
	float GetDotPosY(void) { return m_DotPosY; }
	bool GetCheck(void) { return m_bCheck; }


	// @   @   @   @   @   @   @   @   @   @   @   @
	//				外部データの読み取り
	// @   @   @   @   @   @   @   @   @   @   @   @
	static char *ReadLine(FILE *pFile, char *pDst);
	static char *GetLIneTop(char *pSrc);
	static int PopString(char *pSrc, char *pDst);


private:
	CPlayer *m_pPlayer;

	LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_rot;						//向き
	D3DXCOLOR m_col;						//色
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス
	float m_fSizeX;							//Xサイズ
	float m_fSizeY;							//Yサイズ
	float m_fSizeZ;							//Zサイズ

	//点滅に関する処理
	bool m_bFlash;							//透明率の切り替え
	float fFlashCnt;						//点滅する速度

	//ポリゴンの当たり判定
	//角度をつける
	float m_pos0, m_pos1, m_pos2, m_pos3;
	D3DXVECTOR3 m_nor0;
	D3DXVECTOR3 m_nor1;
	D3DXVECTOR3 m_vec0;
	D3DXVECTOR3 m_vec1;
	float m_DotPosY;	//プレイヤーの位置加算用
	bool m_bCheck;		//乗っているのか?

};




#endif