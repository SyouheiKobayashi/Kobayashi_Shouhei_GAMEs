//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					���ԏ��� [time.h]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#include "scene.h"

#define MAX_DIGIT	(3)
class CNumber;

//==============================================
//				�V�[���̔h�� �� 2D�|���S��
//==============================================
class CTime : public CScene
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CTime(int nPriority = DRAW_2D, DATA_TYPE nObjType = DATA_TYPE_2D);
	~CTime();
	static CTime *Create(int fTime,D3DXVECTOR2 size, D3DXVECTOR2 pos);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					��Պ֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetTime(void) { return m_nTime; }//���݂̎��Ԃ��擾
	void SetDemeritTime(int nTime);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

	CNumber *m_apNumber[MAX_DIGIT];			//number��������������

	int m_nTime;		//���݂̎���
	int m_nTimeSet;	//���Ԃ̐ݒ�
	D3DXVECTOR2 m_size; //�T�C�Y
	D3DXVECTOR2 m_pos;	//�ʒu

	int m_nTimeDigit[MAX_DIGIT];//����
};




#endif