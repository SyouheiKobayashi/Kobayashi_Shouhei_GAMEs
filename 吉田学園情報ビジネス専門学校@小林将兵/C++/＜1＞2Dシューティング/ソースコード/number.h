//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �����E�i���o�[���� [number.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include "main.h"

//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �����E�i���o�[CLASS(��{�N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CNumber
{
public:
	CNumber();
	~CNumber();

	static HRESULT Load(void);//�e�N�X�`����K�v���ǂݍ���
	static void UnLoad(void);//�g�p���Ă���e�N�X�`���𑼂̏����ŏ������Ȃ��悤�ɂ���
	static CNumber *Create(void);//�����E�i���o�[�̐�������

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(int nNumber);
	void SetPos(D3DXVECTOR3 pos, int nSpace,int nCnt);//(�ʒu���,�Ԋu,�����Ԋu��������)
	void SetSize(float X, float Y);//�|���S���̃T�C�Y�ύX


	//D3DXVECTOR3 GetPos(void);//�������������E�i���o�[�̈ʒu���擾����
	//void SetSize(float fWIDTH, float fHEIGHT);//�����E�i���o�[�̃T�C�Y�ύX

	//void BindTexture(LPDIRECT3DTEXTURE9 m_pShareTexture);

private:
	//! �����o�ϐ���
	static LPDIRECT3DTEXTURE9	m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	float					m_SizeX;
	float					m_SizeY;


};




#endif