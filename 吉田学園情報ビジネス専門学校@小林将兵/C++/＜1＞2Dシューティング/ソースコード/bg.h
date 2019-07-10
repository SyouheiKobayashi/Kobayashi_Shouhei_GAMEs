//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �w�i���� [bg.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "scene.h"

#define MAX_TEXTURE	(6)//�摜�ő吔

//�N���X�̌Ăяo��
class CScene2D;
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �w�iCLASS(<Scene>�̔h���N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CBG : public CScene
{
public:

	CBG();
	~CBG();

	static HRESULT Load(void);//�e�N�X�`����K�v���ǂݍ���
	static void UnLoad(void);//�g�p���Ă���e�N�X�`���𑼂̏����ŏ������Ȃ��悤�ɂ���

	static CBG *Create(void);//�|���S���̐�������

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);//�������𔽉f������


private:
	//! �����o�ϐ���
	static LPDIRECT3DTEXTURE9 m_aTexture[MAX_TEXTURE];
	CScene2D *m_apScene2D[MAX_TEXTURE];

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu

	int m_nScrollCnt;//�X�N���[�����Z�p
};




#endif