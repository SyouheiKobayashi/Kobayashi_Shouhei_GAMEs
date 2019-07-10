//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// 入力処理 [input.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

#define	NUM_KEY_MAX			(256)	// キーの最大数
#define NUM_BUTTON_MAX		(32)			// ボタンの最大数

#define MAX_CONTROLLERS (4)
#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.
#define XINPUT_STICK_MAX (32767)			// スティック最大値
#define XINPUT_STICK_MIN (-32768)			// スティック最小値

#define	NUM_MOUSE_MAX			(8)			// マウス入力数の最大数

//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//!+ インプット(入力)CLASS(基本クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//=============================================================================
// マクロ定義
//=============================================================================
#define	NUM_KEY_MAX			(256)	// キーの最大数
#define JOYPAD_MAX			(1)		// ジョイパッドの接続数

//=============================================================================
// 入力クラス
//=============================================================================
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;		// オブジェクト本体は1つ
	LPDIRECTINPUTDEVICE8 m_pDevice;		// デバイスの数だけ作る
};

class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];			// プレスの状態
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	// トリガーの状態
};

class CInputDIPad : public CInput
{// DIパッド（親：CInput）
public:
	typedef enum
	{// ボタン以外のタイプ
		DIPADOTHER_AXES_UP = NUM_BUTTON_MAX,	// 十字キー上
		DIPADOTHER_AXES_LEFT,					// 十字キー左
		DIPADOTHER_AXES_RIGHT,					// 十字キー右
		DIPADOTHER_AXES_DOWN,					// 十字キー下
		DIPADOTHER_STICK_L_UP,					// Lスティック上
		DIPADOTHER_STICK_L_LEFT,				// Lスティック左
		DIPADOTHER_STICK_L_RIGHT,				// Lスティック右
		DIPADOTHER_STICK_L_DOWN,				// Lスティック下
		DIPADOTHER_STICK_R_UP,					// Rスティック上
		DIPADOTHER_STICK_R_LEFT,				// Rスティック左
		DIPADOTHER_STICK_R_RIGHT,				// Rスティック右
		DIPADOTHER_STICK_R_DOWN,				// Rスティック下
		DIPADOTHER_MAX
	}DIPADOTHER;

	CInputDIPad();								// コンストラクタ
	virtual ~CInputDIPad();						// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理

	bool GetPress(int nButton);					// プレス
	bool GetTrigger(int nButton);				// トリガー
	bool GetRelease(int nButton);				// リリース
	bool GetStick(int nLR);						// スティック
	float GetStickRot(int nLR);					// スティック向き

private:
	BYTE m_aJoyStatePress[DIPADOTHER_MAX];		// プレス	
	BYTE m_aJoyStateTrigger[DIPADOTHER_MAX];	// トリガー
	BYTE m_aJoyStateRelease[DIPADOTHER_MAX];	// リリース

	float m_LStickRot;							// Lスティック向き
	float m_RStickRot;							// Rスティック向き
};

class CInputXPad
{// Xパッド
public:
	typedef enum
	{// ボタン以外のタイプ
		XPADOTHER_BUTTON = 0,					// ボタン
		XPADOTHER_TRIGGER_LEFT,					// Lトリガー
		XPADOTHER_TRIGGER_RIGHT,				// Rトリガー
		XPADOTHER_STICK_L_UP,					// Lスティック上
		XPADOTHER_STICK_L_LEFT,					// Lスティック左
		XPADOTHER_STICK_L_RIGHT,				// Lスティック右
		XPADOTHER_STICK_L_DOWN,					// Lスティック下
		XPADOTHER_STICK_R_UP,					// Rスティック上
		XPADOTHER_STICK_R_LEFT,					// Rスティック左
		XPADOTHER_STICK_R_RIGHT,				// Rスティック右
		XPADOTHER_STICK_R_DOWN,					// Rスティック下
		XPADOTHER_MAX
	}XPADOTHER;

	typedef struct
	{// XINPUTコントローラー
		XINPUT_STATE state;		// 情報
		bool bConnected;		// 入力有無
	}CONTROLER_STATE;

	CInputXPad();								// コンストラクタ
	virtual ~CInputXPad();						// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理

	static int GetInputNum(void);						// 入力数取得

	bool GetALL(int nType, int nIdxPad);				// オール
	bool GetPress(int nButton, int nIdxPad);			// プレス
	bool GetPress(XPADOTHER nButton, int nIdxPad);		// プレス
	bool GetTrigger(int nButton, int nIdxPad);			// トリガー
	bool GetTrigger(XPADOTHER nButton, int nIdxPad);	// トリガー
	bool GetRelease(int nButton, int nIdxPad);			// リリース
	bool GetRelease(XPADOTHER nButton, int nIdxPad);	// リリース

	bool GetStick(int nLR, int nIdxPad);				// スティック
	float GetStickRot(int nLR, int nIdxPad);			// スティック向き

private:
	HRESULT UpdateControllerState(void);		// コントローラー入力数更新

	CONTROLER_STATE m_Controllers[MAX_CONTROLLERS];		// XINPUTコントローラー
	bool			m_bDeadZoneOn;						// スティック

	static int		m_nInputNum;						// 入力数

	WORD m_aJoyStatePress[MAX_CONTROLLERS][XPADOTHER_MAX];			// プレス	
	WORD m_aJoyStateTrigger[MAX_CONTROLLERS][XPADOTHER_MAX];		// トリガー
	WORD m_aJoyStateRelease[MAX_CONTROLLERS][XPADOTHER_MAX];		// リリース

	float m_LStickRot[MAX_CONTROLLERS];					// Lスティック向き
	float m_RStickRot[MAX_CONTROLLERS];					// Rスティック向き
};


//==============================================
//マウス
//==============================================
class CInputMouse : public CInput
{
public:
	typedef enum
	{
		MOUSE_L = 0,	//左
		MOUSE_R,		//右
		MOUSE_M,		//ホイールクリック
		MOUSE_MAX
	}MOUSE_OPERATION_TYPE;

	CInputMouse();
	~CInputMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);						//プレスの処理
	bool GetTrigger(int nKey);						//トリガーの処理
	DIMOUSESTATE2 GetWheel() { return m_aMouse; }	//ホイールの処理
	D3DXVECTOR3 GetPos() { return m_pos; }			//マウスの取得

private:
	BYTE m_aKeyState[MOUSE_MAX];			//プレスの処理
	BYTE m_aKeyStateTrigger[MOUSE_MAX];		//トリガーの処理
	DIMOUSESTATE m_aWheel[MOUSE_MAX];		//ホイールの処理
	DIMOUSESTATE2 m_aMouse;					//マウス情報
	D3DXVECTOR3 m_pos;						//マウスの位置情報
	HWND m_hWnd;
};
#endif