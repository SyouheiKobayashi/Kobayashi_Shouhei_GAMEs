//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//				3D�|���S������ [polygon3D.h]
//			Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _POLYGON3D_H_
#define _POLYGON3D_H_

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "billboard.h"

#define POLYGON3D_MAX	(11)

//==============================================
//			�r���{�[�h�̔h�� �� 3D�|���S��
//==============================================
class CPolygon3D : public CBillboard
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CPolygon3D(int nPriority = DRAW_BILLBOARD, DATA_TYPE nObjType = DATA_TYPE_BILLBOARD);
	~CPolygon3D();
	static CPolygon3D *Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nAnimSpeed, int nWidth, int nHight, bool bLoop);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					��Պ֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				�摜�̓ǂݍ��݁E���
	// @   @   @   @   @   @   @   @   @   @   @   @
	static HRESULT TextureLoad(void);
	static void TextureUnLoad(void);


private:
	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	static const char *m_apTexName[];//�g�p����e�N�X�`��
	static LPDIRECT3DTEXTURE9 m_apTexture[POLYGON3D_MAX];//���L�e�N�X�`���ւ̃|�C���^
	
	int m_nType;
	 
	float m_fRadius;//���a(�傫��)
	int m_nLife;//�\������(����)

	//�A�j���[�V�����Ɋւ���ϐ�
	int m_nAnimSpeed;
	int m_nWidth;
	int m_nHight;
	bool m_bLoop;
	int m_nCnt;
};

#endif