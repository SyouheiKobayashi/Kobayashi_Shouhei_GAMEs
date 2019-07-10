//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//ライト処理 [light.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _LIGHT_H_
#define _LIGHT_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"

//==============================================
//マクロ定義
//==============================================
#define MAX_LIGHT (3)//使用するライトの最大数

//==============================================
//ライト
//==============================================
class CLight
{
public:
	//コンストラクタ / デストラクタ
	CLight();
	~CLight();

	//生成
	static CLight *Create(void);

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	void Init(void);
	void Uninit(void);
	void Update(void);

	void SetLight(int nLightNumber, D3DXVECTOR3 pos, D3DXCOLOR col);


private:
	
	D3DLIGHT9 m_light[MAX_LIGHT];//用意するライトの数
	D3DXVECTOR3 m_vecDir[MAX_LIGHT];//用意したライトの方法
	int m_nMode;
	bool m_bReset;

};


#endif
