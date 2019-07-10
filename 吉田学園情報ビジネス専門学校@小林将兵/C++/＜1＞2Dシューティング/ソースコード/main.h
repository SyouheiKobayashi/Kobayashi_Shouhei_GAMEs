//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// ���C������ [main.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _MAIN_H_
#define _MAIN_H_


//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h" //�`��ɕK�v�ȏ���
#define DIRECTINPUT_VERSION (0x0800) //�r���h���̌x���Ώ�
#include"dinput.h" //���͏����ɕK�v
#include "xaudio2.h"//�T�E���h�����ɕK�v
#include <Xinput.h>
#include <stdlib.h>
#include <time.h>
//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib") //�`��ɕK�v�ȏ���
#pragma comment(lib,"d3dx9.lib") //[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib") //DirectX�R���|�[�l���g(���i)�ɕK�v
#pragma comment(lib,"winmm.lib") //�V�X�e�����������ɕK�v
#pragma comment(lib,"dinput8.lib") //���͏����ɕK�v
#pragma comment(lib, "xinput.lib")	

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)		// �E�C���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define MAX_SCENE	(4444)//Scene(�|���S��)�̍ő吔
#define MAX_NUM_PRI	(10)//�ő�D�揇��
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_2D;

//! �O���錾<#include���g�p���Ȃ��ꍇ>
class cRenderer;
class cScene;
//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************

int GetFPS(void);


#endif