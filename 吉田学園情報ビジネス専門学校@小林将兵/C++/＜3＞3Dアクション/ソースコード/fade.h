//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//フェード処理 [fade.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _FADE_H_
#define _FADE_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "manager.h"

//==============================================
//マネージャー管理 → フェード(画面暗転)
//==============================================
class CFade : public CManager
{
public:
	typedef enum
	{
		FADE_NONE = 0,		//使用してない状態
		FADE_IN,			//画面が現れる
		FADE_OUT,			//画面が徐々に消える
		FADE_MAX
	} FADE;

	//コンストラクタ / デストラクタ
	CFade();
	~CFade();

	//生成
	static CFade *Create(void);

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//Get関数(自身で扱った情報を他のプログラムで使用する処理)
	static FADE GetFade(void) { return m_fade; }

	//Set関数(他処理の数値、データをもらい適応 / 主に派生(子)クラスで使用)
	void SetFade(STATE_MODE nextMode);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//頂点バッファへのポインタ
	static FADE m_fade;//現在のフェード状態を記憶
	STATE_MODE m_NextMode;//次のモード
	D3DXCOLOR m_Color;//フェードの色

};




#endif