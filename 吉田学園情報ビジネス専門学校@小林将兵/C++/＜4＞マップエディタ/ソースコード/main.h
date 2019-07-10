//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//���C������ [main.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _MAIN_H_
#define _MAIN_H_
#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION (0x0800) //�r���h���̌x���Ώ�

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include <windows.h>
#include "d3dx9.h"		//�`��ɕK�v�ȏ���
#include"dinput.h"		//���͏����ɕK�v
#include "xaudio2.h"	//�T�E���h�����ɕK�v
#include <Xinput.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>

//==============================================
//���C�u�����t�@�C���ւ̃����N
//==============================================
#pragma comment(lib,"d3d9.lib")			//�`��ɕK�v�ȏ���
#pragma comment(lib,"d3dx9.lib")		//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g(���i)�ɕK�v
#pragma comment(lib,"winmm.lib")		//�V�X�e�����������ɕK�v
#pragma comment(lib,"dinput8.lib")		//���͏����ɕK�v
#pragma comment(lib, "xinput.lib")	

//==============================================
//�}�N���̒�`
//==============================================
#define SCREEN_WIDTH	(1280)		//�E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)		//�E�C���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//3�c�|���S�����_�t�H�[�}�b�g(���_���W[3D] / ���_�J���[ / �e�N�X�`�����W)
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//#define MAX_SCENE	(4444)//Scene(�|���S��)�̍ő吔

//==============================================
//�\���̂̐錾
//==============================================
//2D�Ɋւ��鏈��
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_2D;

//3D�Ɋւ��鏈��
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_3D;

//==============================================
//�O���錾
//==============================================
class cRenderer;
class cScene;

int GetFPS(void);

#endif