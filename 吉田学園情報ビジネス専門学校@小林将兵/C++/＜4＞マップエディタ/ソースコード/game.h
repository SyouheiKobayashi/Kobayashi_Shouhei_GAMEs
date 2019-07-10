//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�Q�[������ [game.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _GAME_H_
#define _GAME_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "manager.h"
#include "fade.h"

//==============================================
//�}�N����`
//==============================================
#define OBJ_CREATE	(100)


//==============================================
//�O���錾
//==============================================
class CDebug;
class CLight;
class CCamera;
class CScene2D;
class CScene3D;
class CMeshField;
class CSceneX;
class CObject;
class CPlayer;

//==============================================
//�Q�[��
//==============================================
class CGame
{
public:
	//�R���X�g���N�^ / �f�X�g���N�^
	CGame();
	~CGame();

	//����
	static CGame *Create();

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void NullCheck(void);
	void CreateData(void);
	void ObjCreate();
	void ObjDelete();
	void Save(void);
	void Debug(void);


	//Get�֐�(���g�ň��������𑼂̃v���O�����Ŏg�p���鏈��)
	static CDebug *GetDebug(void) { return m_pDebug; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CScene3D *GetScene3D(void) { return m_pScene3D; }
	static CMeshField *GetMeshField(void) { return m_pMeshField; }
	static CObject *GetObj(int nCnt) { return m_pObject[nCnt]; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }

	int GetInputMode(void) { return m_nInputMode; }

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�X�N���[�����W�����[���h���W�ɕϊ�
	// @   @   @   @   @   @   @   @   @   @   @   @
	static D3DXVECTOR3* ScreenToWorld
	(D3DXVECTOR3* pout,
		int nScreenPosX,
		int nScreenPosY,
		float fProjectionSpace_Z,//�ˉe��Ԃ�Z�����߂�
		int ScreenWide,
		int ScreenHeight,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj);

	static D3DXVECTOR3* CalculationPoint
	(D3DXVECTOR3* pout,
		int nScreenPosX,
		int nScreenPosY,
		int ScreenWide,
		int ScreenHeight,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj);

private:
	static CDebug *m_pDebug;
	static CLight *m_pLight;
	static CCamera *m_pCamera;
	static CScene2D *m_pScene2D;
	static CScene3D *m_pScene3D;
	static CMeshField *m_pMeshField;
	static CSceneX *m_pSceneX;
	static CObject *m_pObject[OBJ_CREATE];
	static CPlayer *m_pPlayer;

	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//��ʑJ�ڏ���
	CFade::FADE m_pFade;

	int m_nInputMode;//���݂̓��͏��

	//�f�o�b�N�p
	int m_nCreateCnt;

};

#endif

