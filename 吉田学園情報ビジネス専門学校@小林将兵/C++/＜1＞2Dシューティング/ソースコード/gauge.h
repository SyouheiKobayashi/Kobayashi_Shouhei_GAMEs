//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �Q�[�W���� [gauge.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _GAUGE_H_
#define _GAUGE_H_
#include "main.h"

//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �Q�[�WCLASS(��{�N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CGauge
{
public:
	CGauge();
	~CGauge();

	static CGauge *Create(void);//�����E�i���o�[�̐�������

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(int nNumber);
	void SetPos(D3DXVECTOR3 pos, int nSpace, int nCnt);//(�ʒu���,�Ԋu,�����Ԋu��������)
	void SetSize(float X, float Y);//�|���S���̃T�C�Y�ύX

	
private:
	//! �����o�ϐ���
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	float					m_SizeX;
	float					m_SizeY;


};




#endif