//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//? �w�i����[bg.cpp]
//? Author : ���я��� / Kobayashi Shouhei
//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "main.h"
#include "bg.h"

//? ==================================================
//?+ �}�N��
//? ==================================================
#define BG_TEXTURENAME "DATA\\TEXTURE\\bg000.png" //�ǂݍ��ރe�N�X�`��
#define BG_POS_X (0)						 //�w�i�̍���X���W
#define BG_POS_Y (0)						 //�w�i�̍���Y���W
#define BG_WIDTH (SCREEN_WIDTH)				 //�w�i�̕�
#define BG_HEIGHT (SCREEN_HEIGHT)			 //�w�i�̍���

//? ==================================================
//+ �O���[�o���ϐ�
//? ==================================================
LPDIRECT3DTEXTURE9 g_pTextureBG[2] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;

int g_nCountAnimBG; //�A�j���[�V�����J�E���^�[

//? ==================================================
//+ ������
//? ==================================================
void InitBG(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCountAnimBG = 0;//�A�N�V�����J�E���g

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME, &g_pTextureBG[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBG->Unlock();
}

//? ==================================================
//+ �I��
//? ==================================================

void UninitBG(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_pTextureBG[nCnt] != NULL)
		{
			g_pTextureBG[nCnt]->Release();
			g_pTextureBG[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//? ==================================================
//+ �X�V
//? ==================================================
void UpdateBG(void)
{
	g_nCountAnimBG++;//�A�j���[�V�����̃J�E���g�A�b�v
	
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (0.001f * g_nCountAnimBG));
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (0.001f * g_nCountAnimBG));
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (0.001f * g_nCountAnimBG));
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (0.001f * g_nCountAnimBG));

	/*pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (0.01f * g_nCountAnimBG));
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (0.01f * g_nCountAnimBG));
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (0.01f * g_nCountAnimBG));
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (0.01f * g_nCountAnimBG));*/

	if (pVtx[0].tex.x < 0.0f)
	{
		pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	if (pVtx[1].tex.x < 0.0f)
	{
		pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBG->Unlock();
}

//? ==================================================
//+ �`��
//? ==================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X����������
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBG[nCnt]);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}
