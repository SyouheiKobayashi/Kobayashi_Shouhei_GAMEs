//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �������ԏ��� [time.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#include "scene.h"

#define MAX_DIGIT	(3)
class CNumber;
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �V�[��2DCLASS(<Scene>�̔h���N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CTime : public CScene
{
public:
	CTime();
	~CTime();

	static CTime *Create(void);//�X�R�A�̐�������

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos);//�������𔽉f������

	void AddScore(int nValue);//���_

	int GetTimeNow(void) { return m_nTimeNow; }//�Q�[����̌��݂̎���
	int GetEnemyCreateTime(void) { return m_nEnemyCreateTime; }//�G��������
	bool GetPlayerFlag(void) { return m_bPlayerFlag; }//���ԊǗ��ɂ��v���C���[�̗L��

	void SetLife(int nAddLife);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu

	CNumber *m_apNumber[MAX_DIGIT];//number��������������
	int m_nTimeNow;//���݂̎���
	int m_nTimeDigit[MAX_DIGIT];//����

	int m_nEnemyCreateTime;//�G�̐������鎞��

	int m_nUnintTime;//���̉�ʑJ�ڂ܂ł̎���
	bool m_nCheck;//UI�𕡐����������Ȃ�

	bool m_bPlayerFlag;//���ԊǗ��ɂ��v���C���[�̗L��
	

};




#endif