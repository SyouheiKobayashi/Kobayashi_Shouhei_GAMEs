//=========================================================================
// �`���[�g���A������ [tutorial.cpp]
// Author:Kobayashi/���� ����
//=========================================================================
#include "main.h"	//���C������
#include "sound.h"
#include "tutorial.h"
#include "camera.h"	//�J��������
#include "light.h"	//���C�g����
#include "stage.h"
#include "fade.h"
#include "input.h"	//���͏���

//=========================================================================
//�}�N��
//=========================================================================
#define TH_TYPE (5)//�w�i�̖���
#define Tutorial_TEXTURENAME "DATA\\TEXTURE\\Tutorial00.png"//�ǂݍ��ރe�N�X�`��
#define Tutorial_TEXTURENAME2 "DATA\\TEXTURE\\Tutorial01.png"//�ǂݍ��ރe�N�X�`��
#define Tutorial_TEXTURENAME3 "DATA\\TEXTURE\\PUSH ENTER00.png"//�ǂݍ��ރe�N�X�`��
#define Tutorial_TEXTURENAME4 "DATA\\TEXTURE\\GAME START00.png"//�ǂݍ��ރe�N�X�`��
#define Tutorial_TEXTURENAME5 "DATA\\TEXTURE\\Tutorial02.png"//�ǂݍ��ރe�N�X�`��

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
camera *pCameraTutorial;
TUTORIAL_STATE state;
D3DXCOLOR col;
//=========================================================================
//�^�C�g�� / ������
//=========================================================================
void InitTutorial(void)
{
	InitCamera();
	InitLight();
	InitStage();
	PlaySound(SOUND_LABEL_TITLE);

	state = TUTORIAL_0;
	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	SpeedAnimationTH = 0;
	PatternAnimationTH = 0;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();		//�f�o�C�X�̏���

	camera *pCamera = GetCamera();//�J�����̓ǂݍ���
	pCamera[0].Radian = 45.0f;

	//PlaySound(SOUND_LABEL_BGM000);

	//���e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME, &g_pTextureTutorial[0]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME2, &g_pTextureTutorial[1]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME3, &g_pTextureTutorial[2]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME4, &g_pTextureTutorial[3]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME5, &g_pTextureTutorial[4]);


	//�����_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TH_TYPE,
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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		//===============================================================================
				//�����_���W�̐ݒ�
		pVtx[4].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(Tutorial_WIDTH, 0, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(0, Tutorial_HEIGHT, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(Tutorial_WIDTH, Tutorial_HEIGHT, 0.0f);

		//��rhw�̐ݒ�
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//�����_�J���[�̐ݒ�
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

		//���e�N�X�`�����W�̐ݒ�
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

		//===============================================================================
		//�����_���W�̐ݒ�
		pVtx[8].pos = D3DXVECTOR3(850, 500, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(Tutorial_WIDTH+80, 500, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(850, Tutorial_HEIGHT+100, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(Tutorial_WIDTH+80, Tutorial_HEIGHT+100, 0.0f);

		//��rhw�̐ݒ�
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//�����_�J���[�̐ݒ�
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���e�N�X�`�����W�̐ݒ�
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�����_���W�̐ݒ�
		pVtx[12].pos = D3DXVECTOR3(850, 500, 0.0f);
		pVtx[13].pos = D3DXVECTOR3(Tutorial_WIDTH + 80, 500, 0.0f);
		pVtx[14].pos = D3DXVECTOR3(850, Tutorial_HEIGHT + 100, 0.0f);
		pVtx[15].pos = D3DXVECTOR3(Tutorial_WIDTH + 80, Tutorial_HEIGHT + 100, 0.0f);

		//��rhw�̐ݒ�
		pVtx[12].rhw = 1.0f;
		pVtx[13].rhw = 1.0f;
		pVtx[14].rhw = 1.0f;
		pVtx[15].rhw = 1.0f;

		//�����_�J���[�̐ݒ�
		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���e�N�X�`�����W�̐ݒ�
		pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�����_���W�̐ݒ�
		pVtx[16].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[17].pos = D3DXVECTOR3(Tutorial_WIDTH, 0, 0.0f);
		pVtx[18].pos = D3DXVECTOR3(0, Tutorial_HEIGHT, 0.0f);
		pVtx[19].pos = D3DXVECTOR3(Tutorial_WIDTH, Tutorial_HEIGHT, 0.0f);

		//��rhw�̐ݒ�
		pVtx[16].rhw = 1.0f;
		pVtx[17].rhw = 1.0f;
		pVtx[18].rhw = 1.0f;
		pVtx[19].rhw = 1.0f;

		//�����_�J���[�̐ݒ�
		pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

		//���e�N�X�`�����W�̐ݒ�
		pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[17].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[19].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//�����_�o�b�t�@���A�����b�N
	g_pVtxBuffTutorial->Unlock();
}

//=========================================================================
//�^�C�g�� / �I��
//=========================================================================
void UninitTutorial(void)
{
	UninitCamera();
	UninitLight();
	UninitStage();
	StopSound();

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
}

//=========================================================================
//�^�C�g�� / �X�V
//=========================================================================
void UpdateTutorial(void)
{
	UpdateCamera();
	UpdateLight();
	UpdateStage();

	

	pCameraTutorial = GetCamera();

	pCameraTutorial->posV.x = sinf(pCameraTutorial->fKaiten) * 5;
	pCameraTutorial->posV.z = cosf(pCameraTutorial->fKaiten) * 5;

	pCameraTutorial->posR.x = pCameraTutorial->posV.x + sinf(pCameraTutorial->fKaiten) * 200;
	pCameraTutorial->posR.z = pCameraTutorial->posV.z + cosf(pCameraTutorial->fKaiten) * 200;

	//pCameraTutorial->vecU = D3DXVECTOR3(D3DX_PI, 1.0f, 0.0f);
	FADE pFade;
	pFade = *GetFade();

	VERTEX_2D*pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);
	//+ PUSH_ENTER�\��
	if (pVtx[16].col == D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))
	{
		switch (state)
		{
		case TUTORIAL_0:
			col.a += 0.03;
			if (col.a >= 1.0f)
			{
				col.a = 1.0f;
				state = TUTORIAL_1;
			}

			break;

		case TUTORIAL_1:
			col.a -= 0.03;
			if (col.a <= 0.0f)
			{
				col.a = 0.0f;
				state = TUTORIAL_0;
			}

			break;

		}
		pVtx[8].col = col;
		pVtx[9].col = col;
		pVtx[10].col = col;
		pVtx[11].col = col;
	}
	else if (pVtx[16].col == D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
	{
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	}
	//+ PUSH_ENTER_GAME_START�\��
	if (pVtx[0].col == D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f)&& pVtx[4].col == D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))
	{
		switch (state)
		{
		case TUTORIAL_0:
			col.a += 0.03;
			if (col.a >= 1.0f)
			{
				col.a = 1.0f;
				state = TUTORIAL_1;
			}

			break;

		case TUTORIAL_1:
			col.a -= 0.03;
			if (col.a <= 0.0f)
			{
				col.a = 0.0f;
				state = TUTORIAL_0;
			}

			break;

		}
		pVtx[12].col = col;
		pVtx[13].col = col;
		pVtx[14].col = col;
		pVtx[15].col = col;
	}
	else if (pVtx[0].col == D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)|| pVtx[4].col == D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
	{
		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	}


//�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��
//+	�y�[�W����
//�� ��	�� �� �� �� �� �� �� ��	�� �� �� �� �� �� �� ��	�� �� �� �� �� �� �� ��	�� �� �� �� �� ��

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//�����_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	}

	if (GetKeyboardTrigger(DIK_RETURN) == false && pVtx[0].col == D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f) && 
		pVtx[16].col == D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))
	{
		//�����_�J���[�̐ݒ�
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true&& 
		pVtx[4].col == D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
	{
		//�����_�J���[�̐ݒ�
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		//�����_�J���[�̐ݒ�
		pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	}
	else if (pVtx[16].col == D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) && GetKeyboardTrigger(DIK_RETURN) == true)
	{
			if (pFade == FADE_NONE)
			{
				//���[�h�̐ݒ�
				SetFade(MODE_GAME);
			}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();

	
}

//=========================================================================
//�^�C�g�� / �`��
//=========================================================================
void DrawTutorial(void)
{
	DrawStage();
	camera *pCamera = GetCamera();
	SetCamera();

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
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTH * 4, 2);
	}
}