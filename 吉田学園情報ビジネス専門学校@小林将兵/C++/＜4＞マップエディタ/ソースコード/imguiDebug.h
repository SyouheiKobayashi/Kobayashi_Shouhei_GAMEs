//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//imgui���� [imguiDebug.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _IMGUI_H_
#define _IMGUI_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"

//==============================================
//imgui����
//==============================================
class CImguiDebug
{
public:
	
	//�R���X�g���N�^ / �f�X�g���N�^
	CImguiDebug();
	~CImguiDebug();

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	void Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Tutorial(void);	//�L�[�{�[�h��������
	void Tutorial02(void);	//�}�E�X��������

private:

};




#endif