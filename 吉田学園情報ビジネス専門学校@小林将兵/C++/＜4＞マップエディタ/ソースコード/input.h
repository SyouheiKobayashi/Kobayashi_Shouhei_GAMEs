//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// ���͏��� [input.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔
#define NUM_BUTTON_MAX		(32)			// �{�^���̍ő吔

#define MAX_CONTROLLERS (4)
#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.
#define XINPUT_STICK_MAX (32767)			// �X�e�B�b�N�ő�l
#define XINPUT_STICK_MIN (-32768)			// �X�e�B�b�N�ŏ��l

#define	NUM_MOUSE_MAX			(8)			// �}�E�X���͐��̍ő吔

//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//!+ �C���v�b�g(����)CLASS(��{�N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//=============================================================================
// �}�N����`
//=============================================================================
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔
#define JOYPAD_MAX			(1)		// �W���C�p�b�h�̐ڑ���

//=============================================================================
// ���̓N���X
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
	static LPDIRECTINPUT8 m_pInput;		// �I�u�W�F�N�g�{�̂�1��
	LPDIRECTINPUTDEVICE8 m_pDevice;		// �f�o�C�X�̐��������
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
	BYTE m_aKeyState[NUM_KEY_MAX];			// �v���X�̏��
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	// �g���K�[�̏��
};

class CInputDIPad : public CInput
{// DI�p�b�h�i�e�FCInput�j
public:
	typedef enum
	{// �{�^���ȊO�̃^�C�v
		DIPADOTHER_AXES_UP = NUM_BUTTON_MAX,	// �\���L�[��
		DIPADOTHER_AXES_LEFT,					// �\���L�[��
		DIPADOTHER_AXES_RIGHT,					// �\���L�[�E
		DIPADOTHER_AXES_DOWN,					// �\���L�[��
		DIPADOTHER_STICK_L_UP,					// L�X�e�B�b�N��
		DIPADOTHER_STICK_L_LEFT,				// L�X�e�B�b�N��
		DIPADOTHER_STICK_L_RIGHT,				// L�X�e�B�b�N�E
		DIPADOTHER_STICK_L_DOWN,				// L�X�e�B�b�N��
		DIPADOTHER_STICK_R_UP,					// R�X�e�B�b�N��
		DIPADOTHER_STICK_R_LEFT,				// R�X�e�B�b�N��
		DIPADOTHER_STICK_R_RIGHT,				// R�X�e�B�b�N�E
		DIPADOTHER_STICK_R_DOWN,				// R�X�e�B�b�N��
		DIPADOTHER_MAX
	}DIPADOTHER;

	CInputDIPad();								// �R���X�g���N�^
	virtual ~CInputDIPad();						// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����

	bool GetPress(int nButton);					// �v���X
	bool GetTrigger(int nButton);				// �g���K�[
	bool GetRelease(int nButton);				// �����[�X
	bool GetStick(int nLR);						// �X�e�B�b�N
	float GetStickRot(int nLR);					// �X�e�B�b�N����

private:
	BYTE m_aJoyStatePress[DIPADOTHER_MAX];		// �v���X	
	BYTE m_aJoyStateTrigger[DIPADOTHER_MAX];	// �g���K�[
	BYTE m_aJoyStateRelease[DIPADOTHER_MAX];	// �����[�X

	float m_LStickRot;							// L�X�e�B�b�N����
	float m_RStickRot;							// R�X�e�B�b�N����
};

class CInputXPad
{// X�p�b�h
public:
	typedef enum
	{// �{�^���ȊO�̃^�C�v
		XPADOTHER_BUTTON = 0,					// �{�^��
		XPADOTHER_TRIGGER_LEFT,					// L�g���K�[
		XPADOTHER_TRIGGER_RIGHT,				// R�g���K�[
		XPADOTHER_STICK_L_UP,					// L�X�e�B�b�N��
		XPADOTHER_STICK_L_LEFT,					// L�X�e�B�b�N��
		XPADOTHER_STICK_L_RIGHT,				// L�X�e�B�b�N�E
		XPADOTHER_STICK_L_DOWN,					// L�X�e�B�b�N��
		XPADOTHER_STICK_R_UP,					// R�X�e�B�b�N��
		XPADOTHER_STICK_R_LEFT,					// R�X�e�B�b�N��
		XPADOTHER_STICK_R_RIGHT,				// R�X�e�B�b�N�E
		XPADOTHER_STICK_R_DOWN,					// R�X�e�B�b�N��
		XPADOTHER_MAX
	}XPADOTHER;

	typedef struct
	{// XINPUT�R���g���[���[
		XINPUT_STATE state;		// ���
		bool bConnected;		// ���͗L��
	}CONTROLER_STATE;

	CInputXPad();								// �R���X�g���N�^
	virtual ~CInputXPad();						// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����

	static int GetInputNum(void);						// ���͐��擾

	bool GetALL(int nType, int nIdxPad);				// �I�[��
	bool GetPress(int nButton, int nIdxPad);			// �v���X
	bool GetPress(XPADOTHER nButton, int nIdxPad);		// �v���X
	bool GetTrigger(int nButton, int nIdxPad);			// �g���K�[
	bool GetTrigger(XPADOTHER nButton, int nIdxPad);	// �g���K�[
	bool GetRelease(int nButton, int nIdxPad);			// �����[�X
	bool GetRelease(XPADOTHER nButton, int nIdxPad);	// �����[�X

	bool GetStick(int nLR, int nIdxPad);				// �X�e�B�b�N
	float GetStickRot(int nLR, int nIdxPad);			// �X�e�B�b�N����

private:
	HRESULT UpdateControllerState(void);		// �R���g���[���[���͐��X�V

	CONTROLER_STATE m_Controllers[MAX_CONTROLLERS];		// XINPUT�R���g���[���[
	bool			m_bDeadZoneOn;						// �X�e�B�b�N

	static int		m_nInputNum;						// ���͐�

	WORD m_aJoyStatePress[MAX_CONTROLLERS][XPADOTHER_MAX];			// �v���X	
	WORD m_aJoyStateTrigger[MAX_CONTROLLERS][XPADOTHER_MAX];		// �g���K�[
	WORD m_aJoyStateRelease[MAX_CONTROLLERS][XPADOTHER_MAX];		// �����[�X

	float m_LStickRot[MAX_CONTROLLERS];					// L�X�e�B�b�N����
	float m_RStickRot[MAX_CONTROLLERS];					// R�X�e�B�b�N����
};


//==============================================
//�}�E�X
//==============================================
class CInputMouse : public CInput
{
public:
	typedef enum
	{
		MOUSE_L = 0,	//��
		MOUSE_R,		//�E
		MOUSE_M,		//�z�C�[���N���b�N
		MOUSE_MAX
	}MOUSE_OPERATION_TYPE;

	CInputMouse();
	~CInputMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);						//�v���X�̏���
	bool GetTrigger(int nKey);						//�g���K�[�̏���
	DIMOUSESTATE2 GetWheel() { return m_aMouse; }	//�z�C�[���̏���
	D3DXVECTOR3 GetPos() { return m_pos; }			//�}�E�X�̎擾

private:
	BYTE m_aKeyState[MOUSE_MAX];			//�v���X�̏���
	BYTE m_aKeyStateTrigger[MOUSE_MAX];		//�g���K�[�̏���
	DIMOUSESTATE m_aWheel[MOUSE_MAX];		//�z�C�[���̏���
	DIMOUSESTATE2 m_aMouse;					//�}�E�X���
	D3DXVECTOR3 m_pos;						//�}�E�X�̈ʒu���
	HWND m_hWnd;
};
#endif