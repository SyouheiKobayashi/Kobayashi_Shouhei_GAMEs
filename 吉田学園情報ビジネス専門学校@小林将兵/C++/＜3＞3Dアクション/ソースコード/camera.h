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
#include "input.h"

//==============================================
//�}�N����`
//==============================================
#define CAMERA_V D3DXVECTOR3(-150.0f, 140.0f, -220.0f)		//�����_����̋���(��ɒ����_����������)
#define CAMERA_R D3DXVECTOR3(-150.0f, 120.0f, 0.0f)			//�����_�̈ʒu(��ɃJ�����̒��S�ł���)
#define CAMERA_WIDTH (60.0f)//�J��������̍L��

//==============================================
//�J����
//==============================================
class CCamera
{
public:
	//�R���X�g���N�^ / �f�X�g���N�^
	CCamera();
	~CCamera();

	//����
	static CCamera *Create(void);

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	void Init(void);
	void Uninit(void);
	void Update(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					�ǉ��֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	void DebugCameraMove();
	void CameraView();

	//Get�֐�(���g�ň��������𑼂̃v���O�����Ŏg�p���鏈��)
	float GetRotation(void) { return m_fRotation; }
	D3DXMATRIX GetMtxProjection(void) { return m_mtxProjection; }
	D3DXMATRIX GetMtxViex(void) { return m_mtxViex; }
	//Set�֐�(�������̐��l�A�f�[�^�����炢�K�� / ��ɔh��(�q)�N���X�Ŏg�p)
	void SetCamera(void);//�J�����̊�{���
	void SetV(D3DXVECTOR3 posV);
	void SetR(D3DXVECTOR3 posR);

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

	float m_Radian;//�J�����̋���
	float m_fRotation;//��

	float m_fCameraPosZ;//�v���C���[�̈ʒu�ɂ��J�����̒l�̕ύX

	CInputKeyboard *m_pInputKeyboard;

	
};

#endif
