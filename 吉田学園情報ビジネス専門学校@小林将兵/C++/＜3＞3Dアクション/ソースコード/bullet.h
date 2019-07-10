//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//				�o���b�g���� [bullet.h]
//			Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _BULLET_H_
#define _BULLET_H_

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "billboard.h"

#define BULLET_TEX_MAX	(2)

class CPlayer;
class CSound;
//==============================================
//			�r���{�[�h�̔h�� �� �o���b�g
//==============================================
class CBullet : public CBillboard
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CBullet(int nPriority = DRAW_BULLET, DATA_TYPE nObjType = DATA_TYPE_BILLBOARD);
	~CBullet();
	static CBullet *Create(int nLife,D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nTexType, int nAnimSpeed, int nWidth, int nHight, bool bLoop);

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
	static CSound *m_pSound;
	CPlayer *m_pPlayer;
	static const char *m_apTexName[];//�g�p����e�N�X�`��
	static LPDIRECT3DTEXTURE9 m_apTexture[BULLET_TEX_MAX];//���L�e�N�X�`���ւ̃|�C���^
	
	int m_nType;

	int m_nLife;//�\������(����)

	//�A�j���[�V�����Ɋւ���ϐ�
	int m_nAnimSpeed;
	int m_nWidth;
	int m_nHight;
	bool m_bLoop;
};

#endif