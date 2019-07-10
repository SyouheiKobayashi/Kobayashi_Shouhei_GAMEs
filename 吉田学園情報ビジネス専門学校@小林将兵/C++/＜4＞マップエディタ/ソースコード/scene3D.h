//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//3D�|���S���������� [scene3D.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "scene.h"

//==============================================
//�V�[���̔h�� �� 3D�|���S��
//==============================================
class CScene3D : public CScene
{
public:
	//�R���X�g���N�^ / �f�X�g���N�^
	CScene3D(int nPriority = DRAW_3D, DATA_TYPE dataType = DATA_TYPE_3D);
	~CScene3D();

	//����
	static CScene3D *Create();

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//Set�֐�(�������̐��l�A�f�[�^�����炢�K�� / ��ɔh��(�q)�N���X�Ŏg�p)
	void BindTexture(LPDIRECT3DTEXTURE9 textureInfo);	//! �摜�������炢�A�����`��
	void SetPos(D3DXVECTOR3 pos);						//! �ʒu
	void SetSize(float fSizeX, float fSizeY, float fSizeZ);			//! �T�C�Y
	void SetCol(D3DXCOLOR col);							//! �F
	void FlashTex(void);								//! �_��
	void SetTexAnim(int nAnimSpeed, int nWidth,			//! �����A�j���[�V����
		int nHeight, int nPattern);						//! (�A�j���[�V�����̑����A���̕������A�c�̕������A�v�Z�Ŋ���o�����)


private:
	LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_rot;						//����
	D3DXCOLOR m_col;						//�F
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X
	float m_fSizeX;							//X�T�C�Y
	float m_fSizeY;							//Y�T�C�Y
	float m_fSizeZ;							//Z�T�C�Y

	//�_�łɊւ��鏈��
	bool m_bFlash;							//�������̐؂�ւ�
	float fFlashCnt;						//�_�ł��鑬�x


};




#endif