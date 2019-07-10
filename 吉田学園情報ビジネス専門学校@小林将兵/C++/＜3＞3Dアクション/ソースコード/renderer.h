//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�����_�����O���� [renderer.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _RENDERER_H_
#define _RENDERER_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"

//==============================================
//�����_�����O
//==============================================
class CRenderer
{
public:
	//�R���X�g���N�^ / �f�X�g���N�^
	CRenderer();
	~CRenderer();

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//Get�֐�(�g�p�����ϐ��Ȃǂ̏��𑼂̃v���O�����Ŏg�p���鏈��)
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

private:
	LPDIRECT3D9				m_pD3D;			//Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;	//Device�I�u�W�F�N�g(�`��ɕK�v)

	//�f�o�b�N�p
#ifdef _DEBUG
	LPD3DXFONT				m_pFont;		//�t�H���g�ւ̃|�C���^
#endif
};

#endif