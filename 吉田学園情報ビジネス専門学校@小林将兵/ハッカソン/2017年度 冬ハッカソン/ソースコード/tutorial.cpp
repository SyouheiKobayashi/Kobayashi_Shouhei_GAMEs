//=========================================================================
// �^�C�g������ [tutorial.cpp]
// Kobayashi Syouhei / ���я���
//=========================================================================
#include "main.h"	//���C������
#include "tutorial.h"	//�^�C�g������
#include "input.h"	//���͏���
#include "fade.h"	//�t�F�[�h��ʐ؂�ւ�����
#include "sound.h"

//=========================================================================
//�}�N��
//=========================================================================
#define Tutorial_TEXTURENAME "data/TEXTURE/tutorial_.jpg"		//�ǂݍ��ރe�N�X�`��
#define Tutorial_POS_X (0)							//�w�i�̍���X���W
#define Tutorial_POS_Y (0)						    //�w�i�̍���Y���W
#define Tutorial_WIDTH (SCREEN_WIDTH)				//�w�i�̕�
#define Tutorial_HEIGHT (SCREEN_HEIGHT)			//�w�i�̍���

//=========================================================================
//�O���[�o��
//=========================================================================
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;			//���_�o�b�t�@�ւ̃|�C���^

															//=========================================================================
															//�^�C�g�� / ������
															//=========================================================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̏���

								//PlaySound(SOUND_LABEL_BGM000);

								//���e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME, &g_pTextureTutorial);

	//�����_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

						//�����_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//�����_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(Tutorial_POS_X, Tutorial_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Tutorial_POS_X + Tutorial_WIDTH, Tutorial_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Tutorial_POS_X, Tutorial_POS_Y + Tutorial_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Tutorial_POS_X + Tutorial_WIDTH, Tutorial_POS_Y + Tutorial_HEIGHT, 0.0f);

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

	//�����_�o�b�t�@���A�����b�N
	g_pVtxBuffTutorial->Unlock();
}

//=========================================================================
//�^�C�g�� / �I��
//=========================================================================
void UninitTutorial(void)
{
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
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
	FADE pFade;
	pFade = *GetFade();
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

	//���e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorial);

	//�����_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
