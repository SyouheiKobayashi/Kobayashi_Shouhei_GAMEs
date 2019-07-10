//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//						�r���{�[�h���� [billboard.h]
//				Author : Kobayashi_Sho-hei/���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "scene.h"

//==============================================
//					�}�N����`
//==============================================
#define TEXBILLBOARD_NAME	("DATA/TEXTURE/bullet000.png")
#define TEXBILLBOARD_DEFAULTSIZE	(5)

//==============================================
//				�V�[���h�� �� �r���{�[�h
//==============================================
class CBillboard : public CScene
{
public:

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CBillboard(int nPriority = DRAW_BILLBOARD, DATA_TYPE nObjType = DATA_TYPE_BILLBOARD);
	~CBillboard();
	static CBillboard *Create(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					��Պ֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Draw02(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			  �e�N�X�`�����̎󂯎��
	// @   @   @   @   @   @   @   @   @   @   @   @
	void BindTexture(LPDIRECT3DTEXTURE9 textureInfo);


	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size;}
	D3DXCOLOR GetCol(void) { return m_col;}

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	void SetSize(D3DXVECTOR3 size);
	void SetChangeSize(float fsize);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetCol(D3DXCOLOR col);
	void SetTexAnim(int nCntAnim, int nWidth, int nHight, bool bLoop);	//�A�j���[�V����(�R�}����)
	void SetParticle(float fTransSize, D3DXCOLOR col);
	void SetSpin(float fSpinSpeed);										//��]
	void FlashTex(void);												//�_��

private:
	LPDIRECT3DTEXTURE9		m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//����
	D3DXCOLOR m_col;		//�F

	//�T�C�Y�ύX
	D3DXVECTOR3 m_size;

	//�A�j���[�V��������
	int m_nCnt;
	int m_PatternAnim;

	//��]
	float m_fAngle;							//�p�x
	float m_fLengs;							//����
	float m_fSpinSpeed;						//��]���x

	//�_�łɊւ��鏈��
	bool m_bFlash;							//�������̐؂�ւ�
	float fFlashCnt;						//�_�ł��鑬�x

};




#endif