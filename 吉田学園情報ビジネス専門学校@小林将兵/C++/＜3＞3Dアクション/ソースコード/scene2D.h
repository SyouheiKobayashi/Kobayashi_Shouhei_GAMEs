//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					2D�|���S������ [scene2D.h]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "scene.h"

//==============================================
//				�V�[���̔h�� �� 2D�|���S��
//==============================================
class CScene2D : public CScene
{
public:

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CScene2D(int nPriority = DRAW_2D, DATA_TYPE dataType = DATA_TYPE_2D);
	~CScene2D();
	static CScene2D *Create(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					��Պ֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	void BindTexture(LPDIRECT3DTEXTURE9 textureInfo);	//�摜�������炢�A�����`��
	void SetPos(D3DXVECTOR3 pos);						//�ʒu
	void SetMove(D3DXVECTOR3 move);						//�ړ�
	void SetSpin(float fSpinSpeed);						//��]
	void SetSize(float fSizeX, float fSizeY);			//�T�C�Y
	void SetCol(D3DXCOLOR col);							//�F
	void FlashTex(void);								//�_��
	void SetTexAnim(int nAnimSpeed, int nWidth,			//�����A�j���[�V����
					int nHeight, bool bLoop);			//(�A�j���[�V�����̑����A���̕������A�c�̕������A���[�v�̉�)
	void SetAnimSize(float fCnt,int nSpeed);			//�g��E�k���A�j���[�V����
	void SetScroll(float fSpeed, bool bVector, int nType);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXCOLOR GetCol(void) { return m_col; }

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;			//�|���S���̈ʒu
	D3DXCOLOR m_col;						//�F
	float m_fSizeX;							//���T�C�Y
	float m_fSizeY;							//�c�T�C�Y

	//�_�łɊւ��鏈��
	bool m_bFlash;							//�������̐؂�ւ�
	float m_fFlashCnt;						//�_�ł��鑬�x

	//��]
	float m_fAngle;							//�p�x
	float m_fLengs;							//����
	float m_fSpinSpeed;						//��]���x

	//�A�j���[�V��������
	int m_nCnt;
	int m_PatternAnim;

	//�T�C�Y�ύX�J�E���g
	int m_nSizeCnt;
	bool m_bSizeChange;

	//�X�N���[��
	int m_nScrollCnt;
};




#endif