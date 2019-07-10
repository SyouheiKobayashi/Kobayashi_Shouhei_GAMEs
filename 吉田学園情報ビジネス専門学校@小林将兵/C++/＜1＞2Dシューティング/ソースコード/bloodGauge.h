//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// ���t�Q�[�W���� [bloodGauge.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _BLOODGAUGE_H_
#define _BLOODGAUGE_H_
#include "main.h"
#include "scene.h"

#define MAX_BLOOD	(16)
class CGauge;
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ ���tCLASS(<Scene>�̔h���N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CBloodGauge : public CScene
{
public:
	CBloodGauge();
	~CBloodGauge();

	static HRESULT Load(void);//�e�N�X�`����K�v���ǂݍ���
	static void UnLoad(void);//�g�p���Ă���e�N�X�`���𑼂̏����ŏ������Ȃ��悤�ɂ���

	static CBloodGauge *Create(void);//�X�R�A�̐�������

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos);//�������𔽉f������

	

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu

	CGauge *m_apGauge[MAX_BLOOD];//number��������������
	static int m_nBlood;
	static int m_nBloodGauge[MAX_BLOOD];

};




#endif