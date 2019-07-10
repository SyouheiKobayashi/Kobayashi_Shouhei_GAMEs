//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// ���C�t���� [life.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _LIFE_H_
#define _LIFE_H_
#include "main.h"
#include "scene.h"

#define MAX_LIFE	(15)
class CGauge;
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ ���C�tCLASS(<Scene>�̔h���N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CLife : public CScene
{
public:
	CLife();
	~CLife();

	static HRESULT Load(void);//�e�N�X�`����K�v���ǂݍ���
	static void UnLoad(void);//�g�p���Ă���e�N�X�`���𑼂̏����ŏ������Ȃ��悤�ɂ���

	static CLife *Create(void);//�X�R�A�̐�������

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos);//�������𔽉f������

	void SetLife(int nLife);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu

	CGauge *m_apGauge[MAX_LIFE];//number��������������
	static int m_nLife;
	static int m_nLifeGauge[MAX_LIFE];

};




#endif