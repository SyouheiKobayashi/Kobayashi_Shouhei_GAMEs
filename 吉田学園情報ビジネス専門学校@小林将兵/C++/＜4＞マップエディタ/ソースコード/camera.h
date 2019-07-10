//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�J�������� [camera.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _CAMERA_H_
#define _CAMERA_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"

//==============================================
//�}�N����`
//==============================================
#define CAMERA_V D3DXVECTOR3(0.0f, 50.0f, -400.0f)//�����_����̋���(��ɒ����_����������)
#define CAMERA_R D3DXVECTOR3(0.0f, 0.0f, 0.0f)//�����_�̈ʒu(��ɃJ�����̒��S�ł���)
#define CAMERA_WIDTH (50.0f)//�J��������̍L��
#define CAMERA_INIT_V (400.0f)//�����_����̋���(��ɒ����_����������)

class CGame;
class CInputKeyboard;
class CInputXPad;
class CInputMouse;

//==============================================
//�J����
//==============================================
class CCamera
{
public:
	typedef enum        //���[�h�̎��
	{
		MODE_XYZ = 0,	//�L�[�{�[�h����̂�
		MODE_XZ,		//�}�E�X������\
		MODE_MAX		//�ő吔
	}CAMERA_MODE;

	//�R���X�g���N�^ / �f�X�g���N�^
	CCamera();
	~CCamera();

	//����
	static CCamera *Create(void);

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	void Init(void);
	void Uninit(void);
	void Update(void);

	void MOVE(void);			//���̓��[�h�ɂ��J��������2���
	void MOVE02(void);

	void PointViewRot(void);	//�����_�����Ɏ��_�̉�](��ɒ����_����������)
	void NoteViewRot(void);		//���_�̉�](�����_���R���p�X�̂悤�Ɉ���])

	//Get�֐�(���g�ň��������𑼂̃v���O�����Ŏg�p���鏈��)
	float GetRotation(void) { return m_fRotation; }
	D3DXMATRIX GetMtxProjection(void) { return m_mtxProjection; }
	D3DXMATRIX GetMtxViex(void) { return m_mtxViex; }
	int GetCameraMode(void) {return m_nCameraMode;}//���݂̃J�����̏��
	D3DXVECTOR3 GetPosR(void) { return m_posR; }
	D3DXVECTOR3 GetR(void) { return m_posR; }
	//Set�֐�(�������̐��l�A�f�[�^�����炢�K�� / ��ɔh��(�q)�N���X�Ŏg�p)
	void SetCamera(void);//�J�����̊�{���

private:
	D3DXVECTOR3 m_posV;		//(���݂�)���_
	D3DXVECTOR3 m_posR;		//(���݂�)�����_
	D3DXVECTOR3 m_vecU;
	D3DXVECTOR3 m_posVDest;	//(�ړI��)���_
	D3DXVECTOR3 m_posRDest;	//(�ړI��)�����_
	D3DXVECTOR3 m_rot;		//(���݂�)����
	D3DXVECTOR3 m_rotDest;	//(�ړI��)����
	D3DXMATRIX m_mtxProjection;
	D3DXMATRIX m_mtxViex;

	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	float m_Radian;//�J�����̋���
	float m_fRotation;//��

	CGame *m_pGame;
	int m_nCameraMode;//���[�h�̕ύX
};

#endif
