//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//					時間処理 [time.h]
//				Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#include "scene.h"

#define MAX_DIGIT	(3)
class CNumber;

//==============================================
//				シーンの派生 → 2Dポリゴン
//==============================================
class CTime : public CScene
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			コンストラクタ・デストラクタ・生成
	// @   @   @   @   @   @   @   @   @   @   @   @
	CTime(int nPriority = DRAW_2D, DATA_TYPE nObjType = DATA_TYPE_2D);
	~CTime();
	static CTime *Create(int fTime,D3DXVECTOR2 size, D3DXVECTOR2 pos);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					基盤関数
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetTime(void) { return m_nTime; }//現在の時間を取得
	void SetDemeritTime(int nTime);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ

	CNumber *m_apNumber[MAX_DIGIT];			//number処理を扱いため

	int m_nTime;		//現在の時間
	int m_nTimeSet;	//時間の設定
	D3DXVECTOR2 m_size; //サイズ
	D3DXVECTOR2 m_pos;	//位置

	int m_nTimeDigit[MAX_DIGIT];//桁数
};




#endif