//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//���C�g���� [light.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _LIGHT_H_
#define _LIGHT_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"

//==============================================
//�}�N����`
//==============================================
#define MAX_LIGHT (3)//�g�p���郉�C�g�̍ő吔

//==============================================
//���C�g
//==============================================
class CLight
{
public:
	//�R���X�g���N�^ / �f�X�g���N�^
	CLight();
	~CLight();

	//����
	static CLight *Create(void);

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	void Init(void);
	void Uninit(void);
	void Update(void);

	void SetDirectionla(int lightNum, D3DXCOLOR col, D3DXVECTOR3 rot);//�����̋��� / �����̌���
	void SetPoint(int lightNum, D3DXCOLOR col, D3DXVECTOR3 pos,D3DXVECTOR3 rot);//�����̋��� / �����̈ʒu / �����̌���
	void SetSpot(int lightNum, D3DXCOLOR col, D3DXVECTOR3 pos, D3DXVECTOR3 rot);//�����̋��� / �����̈ʒu / �����̌���

private:
	D3DLIGHT9 m_Light[2];//�p�ӂ��郉�C�g�̐�
	D3DXVECTOR3 m_vecDir[2];//�p�ӂ������C�g�̕��@


};


#endif
