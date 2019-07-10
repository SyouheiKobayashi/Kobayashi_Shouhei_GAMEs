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

	void SetLight(int nLightNumber, D3DXVECTOR3 pos, D3DXCOLOR col);


private:
	
	D3DLIGHT9 m_light[MAX_LIGHT];//�p�ӂ��郉�C�g�̐�
	D3DXVECTOR3 m_vecDir[MAX_LIGHT];//�p�ӂ������C�g�̕��@
	int m_nMode;
	bool m_bReset;

};


#endif
