//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// フェード処理 [fade.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "manager.h"

//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ フェードCLASS(マネージャ派生)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CFade : public CManager
{
public:
	typedef enum
	{
		FADE_NONE = 0,// 使用してない状態
		FADE_IN,// フェードイン状態
		FADE_OUT,// フェードアウト状態
		FADE_MAX
	} FADE;

	CFade();
	~CFade();

	static CFade *Create(void);//フェードの生成処理

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetFade(MODE modeNext);
	static FADE GetFade(void) { return m_fade; }


private:
	//! メンバ変数↓
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	 static FADE m_fade;					// 現在のフェード状態を記憶
	MODE m_modeNext;				// 次のモード
	D3DXCOLOR m_colorFade;			// フェードの色

};




#endif