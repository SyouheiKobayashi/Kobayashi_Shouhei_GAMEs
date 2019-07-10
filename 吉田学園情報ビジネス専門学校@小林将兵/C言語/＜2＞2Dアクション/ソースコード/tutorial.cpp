//=========================================================================
// �`���[�g���A������ [tutorial.cpp]
// Author:Kobayashi/���� ����
//=========================================================================
#include "main.h"	//���C������
#include "tutorial.h"
#include "input.h"	//���͏���
#include "fade.h"	//�t�F�[�h��ʐ؂�ւ�����
#include "sound.h"

//=========================================================================
//�}�N��
//=========================================================================
#define TH_TYPE (9)//�w�i�̖���
#define Tutorial_TEXTURENAME "DATA\\TEXTURE\\�w�iP_.jpg"//�ǂݍ��ރe�N�X�`��
#define Tutorial_TEXTURENAME2 "DATA\\TEXTURE\\�`���[�g���A��_.png"//�ǂݍ��ރe�N�X�`��
#define Tutorial_TEXTURENAME3 "DATA\\TEXTURE\\W.jpg"
#define Tutorial_TEXTURENAME4 "DATA\\TEXTURE\\S.jpg"
#define Tutorial_TEXTURENAME5 "DATA\\TEXTURE\\A.jpg"
#define Tutorial_TEXTURENAME6 "DATA\\TEXTURE\\D.jpg"
#define Tutorial_TEXTURENAME7 "DATA\\TEXTURE\\�X�y�[�X.jpg"
#define Tutorial_TEXTURENAME8 "DATA\\TEXTURE\\��B.png"
#define Tutorial_TEXTURENAME9 "DATA\\TEXTURE\\�����o��.png"

#define Tutorial_POS_X (0)							//�w�i�̍���X���W
#define Tutorial_POS_Y (0)						    //�w�i�̍���Y���W
#define Tutorial_WIDTH (SCREEN_WIDTH)				//�w�i�̕�
#define Tutorial_HEIGHT (SCREEN_HEIGHT)			//�w�i�̍���

//=========================================================================
//�O���[�o��
//=========================================================================
LPDIRECT3DTEXTURE9 g_pTextureTutorial[TH_TYPE] = {};				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;			//���_�o�b�t�@�ւ̃|�C���^

int SpeedAnimationTH;
int PatternAnimationTH;
int nCC;
//=========================================================================
//�^�C�g�� / ������
//=========================================================================
void InitTutorial(void)
{
	SpeedAnimationTH = 0;
	PatternAnimationTH = 0;
	nCC = 0;

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̏���

								//PlaySound(SOUND_LABEL_BGM000);

								//���e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME, &g_pTextureTutorial[0]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME2, &g_pTextureTutorial[1]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME3, &g_pTextureTutorial[2]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME4, &g_pTextureTutorial[3]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME5, &g_pTextureTutorial[4]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME6, &g_pTextureTutorial[5]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME7, &g_pTextureTutorial[6]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME8, &g_pTextureTutorial[7]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME9, &g_pTextureTutorial[8]);

	//�����_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4* TH_TYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//�����_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntT = 0; nCntT < TH_TYPE; nCntT++)
	{
		//�����_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Tutorial_WIDTH, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, Tutorial_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Tutorial_WIDTH, Tutorial_HEIGHT, 0.0f);

		//��rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�����_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//--------
//�����\�L
//--------
		//�����_���W�̐ݒ�
		pVtx[4].pos = D3DXVECTOR3(50,50, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(350, 50, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(50, 150, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(350, 150, 0.0f);

		//��rhw�̐ݒ�
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//�����_�J���[�̐ݒ�
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���e�N�X�`�����W�̐ݒ�
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

//--------
//	W
//--------
		//�����_���W�̐ݒ�
		pVtx[8].pos = D3DXVECTOR3(250, 300, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(350, 300, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(250, 400, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(350, 400, 0.0f);

		//��rhw�̐ݒ�
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//�����_�J���[�̐ݒ�
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���e�N�X�`�����W�̐ݒ�
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);
//--------
//	S
//--------
	//�����_���W�̐ݒ�
	pVtx[12].pos = D3DXVECTOR3(250, 410, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(350, 410, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(250, 510, 0.0f);
	pVtx[15].pos = D3DXVECTOR3(350, 510, 0.0f);

	//��rhw�̐ݒ�
	pVtx[12].rhw = 1.0f;
	pVtx[13].rhw = 1.0f;
	pVtx[14].rhw = 1.0f;
	pVtx[15].rhw = 1.0f;

	//�����_�J���[�̐ݒ�
	pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���e�N�X�`�����W�̐ݒ�
	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);

//--------
//	A
//--------
	//�����_���W�̐ݒ�
	pVtx[16].pos = D3DXVECTOR3(140, 410, 0.0f);
	pVtx[17].pos = D3DXVECTOR3(240, 410, 0.0f);
	pVtx[18].pos = D3DXVECTOR3(140, 510, 0.0f);
	pVtx[19].pos = D3DXVECTOR3(240, 510, 0.0f);

	//��rhw�̐ݒ�
	pVtx[16].rhw = 1.0f;
	pVtx[17].rhw = 1.0f;
	pVtx[18].rhw = 1.0f;
	pVtx[19].rhw = 1.0f;

	//�����_�J���[�̐ݒ�
	pVtx[16].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[17].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[18].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[19].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���e�N�X�`�����W�̐ݒ�
	pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[17].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[19].tex = D3DXVECTOR2(1.0f, 1.0f);

//--------
//	D
//--------
	//�����_���W�̐ݒ�
	pVtx[20].pos = D3DXVECTOR3(360, 410, 0.0f);
	pVtx[21].pos = D3DXVECTOR3(460, 410, 0.0f);
	pVtx[22].pos = D3DXVECTOR3(360, 510, 0.0f);
	pVtx[23].pos = D3DXVECTOR3(460, 510, 0.0f);

	//��rhw�̐ݒ�
	pVtx[20].rhw = 1.0f;
	pVtx[21].rhw = 1.0f;
	pVtx[22].rhw = 1.0f;
	pVtx[23].rhw = 1.0f;

	//�����_�J���[�̐ݒ�
	pVtx[20].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[21].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[22].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[23].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���e�N�X�`�����W�̐ݒ�
	pVtx[20].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[21].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[22].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[23].tex = D3DXVECTOR2(1.0f, 1.0f);

//--------
//	SPACE
//--------
	//�����_���W�̐ݒ�
	pVtx[24].pos = D3DXVECTOR3(580, 420, 0.0f);
	pVtx[25].pos = D3DXVECTOR3(800, 420, 0.0f);
	pVtx[26].pos = D3DXVECTOR3(580, 510, 0.0f);
	pVtx[27].pos = D3DXVECTOR3(800, 510, 0.0f);

	//��rhw�̐ݒ�
	pVtx[24].rhw = 1.0f;
	pVtx[25].rhw = 1.0f;
	pVtx[26].rhw = 1.0f;
	pVtx[27].rhw = 1.0f;

	//�����_�J���[�̐ݒ�
	pVtx[24].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[25].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[26].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[27].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���e�N�X�`�����W�̐ݒ�
	pVtx[24].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[25].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[26].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[27].tex = D3DXVECTOR2(1.0f, 1.0f);

//--------
//	��
//--------
	//�����_���W�̐ݒ�
	pVtx[28].pos = D3DXVECTOR3(880, 570, 0.0f);
	pVtx[29].pos = D3DXVECTOR3(1000, 570, 0.0f);
	pVtx[30].pos = D3DXVECTOR3(880, 670, 0.0f);
	pVtx[31].pos = D3DXVECTOR3(1000, 670, 0.0f);

	//��rhw�̐ݒ�
	pVtx[28].rhw = 1.0f;
	pVtx[29].rhw = 1.0f;
	pVtx[30].rhw = 1.0f;
	pVtx[31].rhw = 1.0f;

	//�����_�J���[�̐ݒ�
	pVtx[28].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[29].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[30].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[31].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���e�N�X�`�����W�̐ݒ�
	pVtx[28].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[29].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[30].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[31].tex = D3DXVECTOR2(0.25f, 1.0f);

	//--------
	//	�����o��
	//--------
	//�����_���W�̐ݒ�
	pVtx[32].pos = D3DXVECTOR3(880, 370, 0.0f);
	pVtx[33].pos = D3DXVECTOR3(1200, 370, 0.0f);
	pVtx[34].pos = D3DXVECTOR3(880, 570, 0.0f);
	pVtx[35].pos = D3DXVECTOR3(1200, 570, 0.0f);

	//��rhw�̐ݒ�
	pVtx[32].rhw = 1.0f;
	pVtx[33].rhw = 1.0f;
	pVtx[34].rhw = 1.0f;
	pVtx[35].rhw = 1.0f;

	//�����_�J���[�̐ݒ�
	pVtx[32].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[33].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[34].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[35].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���e�N�X�`�����W�̐ݒ�
	pVtx[32].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[33].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[34].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[35].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//�����_�o�b�t�@���A�����b�N
	g_pVtxBuffTutorial->Unlock();
}

//=========================================================================
//�^�C�g�� / �I��
//=========================================================================
void UninitTutorial(void)
{
	for (int nCnt = 0; nCnt < TH_TYPE; nCnt++)
	{
		if (g_pTextureTutorial[nCnt] != NULL)
		{
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
	//StopSound();
}

//=========================================================================
//�^�C�g�� / �X�V
//=========================================================================
void UpdateTutorial(void)
{
	

	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	nCC++;
	pVtx[4].col = D3DCOLOR_RGBA(255 - nCC, 255 - nCC, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255 - nCC, 255 - nCC, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);

	pVtx[16].col = D3DCOLOR_RGBA(255, 255, 255 - nCC, 255);
	pVtx[17].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);
	pVtx[18].col = D3DCOLOR_RGBA(255, 255, 255 - nCC, 255);
	pVtx[19].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);

	pVtx[20].col = D3DCOLOR_RGBA(255, 255, 255 - nCC, 255);
	pVtx[21].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);
	pVtx[22].col = D3DCOLOR_RGBA(255, 255, 255 - nCC, 255);
	pVtx[23].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);

	pVtx[24].col = D3DCOLOR_RGBA(255, 255, 255 - nCC, 255);
	pVtx[25].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);
	pVtx[26].col = D3DCOLOR_RGBA(255, 255, 255 - nCC, 255);
	pVtx[27].col = D3DCOLOR_RGBA(255, 255 - nCC, 255, 255);

#if 0
	if (GetKeyboardPress(DIK_W) == true)
	{
		pVtx[8].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	if (GetKeyboardPress(DIK_W) == false)
	{
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	if (GetKeyboardPress(DIK_S) == true)
	{
		pVtx[12].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[13].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[14].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[15].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	if (GetKeyboardPress(DIK_S) == false)
	{
		pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	if (GetKeyboardPress(DIK_A) == true)
	{
		pVtx[16].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[17].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[18].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[19].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	if (GetKeyboardPress(DIK_A) == false)
	{
		pVtx[16].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[17].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[18].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[19].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	if (GetKeyboardPress(DIK_D) == true)
	{
		pVtx[20].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[21].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[22].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[23].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	if (GetKeyboardPress(DIK_D) == false)
	{
		pVtx[20].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[21].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[22].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[23].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		pVtx[24].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[25].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[26].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[27].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	if (GetKeyboardPress(DIK_SPACE) == false)
	{
		pVtx[24].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[25].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[26].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[27].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
#endif
		SpeedAnimationTH++; //�J�E���^�[�̉��Z
		if ((SpeedAnimationTH % 8) == 0)
		{
			PatternAnimationTH = (PatternAnimationTH + 1) % 4;//�p�^�[��No.�X�V

			pVtx[28].tex = D3DXVECTOR2((PatternAnimationTH*0.25f), 0.0f);
			pVtx[29].tex = D3DXVECTOR2((PatternAnimationTH*0.25f) + 0.25f, 0.0f);
			pVtx[30].tex = D3DXVECTOR2((PatternAnimationTH*0.25f), 1.0f);
			pVtx[31].tex = D3DXVECTOR2((PatternAnimationTH*0.25f) + 0.25f, 1.0f);
		}
		pVtx += 4;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();

	FADE pFade;
	pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//���[�h�̐ݒ�
			SetFade(MODE_GAME);
		}

	}
}

//=========================================================================
//�^�C�g�� / �`��
//=========================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//���f�o�C�X����������
	pDevice = GetDevice();

	//�����_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//�����_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTH = 0; nCntTH < TH_TYPE; nCntTH++)
	{
		//���e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTutorial[nCntTH]);


		//���|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTH*4, 2);
	}
}
