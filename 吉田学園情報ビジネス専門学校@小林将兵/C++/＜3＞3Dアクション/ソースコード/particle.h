//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//				3D�p�[�e�B�N������ [particle3D.h]
//			Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _PARTICLE3D_H_
#define _PARTICLE3D_H_

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "billboard.h"

#define MAX_PARTICLE3D	(200)

class CBillboard;
//==============================================
//			�r���{�[�h�̔h�� �� 3D�p�[�e�B�N��
//==============================================
class CParticle3D : public CBillboard
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CParticle3D(int nPriority = DRAW_BILLBOARD, DATA_TYPE nObjType = DATA_TYPE_BILLBOARD);
	~CParticle3D();
	static CParticle3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, bool bAngle,int DeleteTime, float fTransSize, int nType);

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
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_PARTICLE3D];	//���L�e�N�X�`���ւ̃|�C���^
													
	//�O���e�L�X�g�̓ǂݍ��ݏ���
	static int m_nNumTexture;								//�ǂݍ��ރe�N�X�`���̐�
	static char m_aFileNameTexture[MAX_PARTICLE3D][256];	//�g�p����e�N�X�`���̖��O
	
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//��]��
	int m_nType;			//�K�p������摜�^�C�v
	float m_fTransSize;		//���ԕω��ɂ��T�C�Y�ϊ��p
	int m_nDeleteTime;		//���R���ł��鎞��

	//�A�j���[�V���������ϐ�
	int m_nCnt;
	int m_PatternAnim;

	float m_fAngle;//���݂̊p�x
	float m_fActionAngle;//���S�����ɉ�]
	float m_fRange;//���Ƃ̋���

	bool m_bAngle;

};

#endif