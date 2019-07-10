//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					2D�|���S������ [polygon2D.h]
//			Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _POLYGON2D_H_
#define _POLYGON2D_H_

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "scene2D.h"

//==============================================
//					�}�N����`
//==============================================
#define POLYGON2D_MAX	(27)

class CInputMouse;
//==============================================
//		scene2D�̔h�� �� 2D�|���S��
//==============================================
class CPolygon2D : public CScene2D
{
public:

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CPolygon2D(int nPriority = DRAW_2D, DATA_TYPE nObjType = DATA_TYPE_2D);
	~CPolygon2D();
	static CPolygon2D *Create(int nTexType,bool bRotation , D3DXVECTOR3 pos , D3DXCOLOR col,float nSizeX, float nSizeY,
								int nAnimSpeed, int nWidth, int nHight, bool bLoop);

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

	void Debug(void);//�f�o�b�N����

private:
	static const char *m_apTexName[];//�g�p����e�N�X�`��
	static LPDIRECT3DTEXTURE9 m_apTexture[POLYGON2D_MAX];	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;								//�|���S���̈ʒu
	CInputMouse *m_pInputMouse;

	int m_nPolygonType;	//2D�|���S���ԍ��̊���U��
	bool m_bRotation;	//��]�����邩

	//�A�j���[�V�����Ɋւ���ϐ�
	int m_nAnimSpeed;
	int m_nWidth;
	int m_nHight;
	bool m_bLoop;
};




#endif