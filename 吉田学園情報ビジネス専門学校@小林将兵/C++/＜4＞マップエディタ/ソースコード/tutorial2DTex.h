//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�`���[�g���A���p�摜�������� [tutorial2DTex.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _TUTORIAL2DTEX_H_
#define _TUTORIAL2DTEX_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "scene2D.h"

//==============================================
//�}�N����`
//==============================================
#define TEX_MAX	(20)

//==============================================
//scene2D�̔h�� �� �`���[�g���A���p�摜
//==============================================
class CTutorial2DTex : public CScene2D
{
public:

	//�R���X�g���N�^ / �f�X�g���N�^
	CTutorial2DTex(int nPriority = DRAW_2D, DATA_TYPE nObjType = DATA_TYPE_2D);
	~CTutorial2DTex();

	//����
	static CTutorial2DTex *Create(int nTexType,D3DXVECTOR3 pos , float nSizeX, float nSizeY);

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�I�u�W�F�N�g�Ɂw�g�p����摜�x�̓ǂݍ���
	static HRESULT TextureLoad(void);
	static void TextureUnLoad(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_MAX];	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;								//�|���S���̈ʒu


};




#endif