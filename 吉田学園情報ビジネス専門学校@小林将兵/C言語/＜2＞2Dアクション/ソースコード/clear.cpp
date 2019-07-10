//=========================================================================
// �N���A��ʂ̏��� [clear.cpp]
// Kobayashi Syouhei / ���я���
//=========================================================================
#include "main.h"	//���C������
#include "clear.h"	//�N���A����
#include "input.h"	//���͏���
#include "fade.h"	//�t�F�[�h��ʐ؂�ւ�����

//=========================================================================
//�}�N��
//=========================================================================
#define Clear_TEXTURENAME "DATA\\TEXTURE\\�I�v�[�i.jpg"		//�ǂݍ��ރe�N�X�`��
#define Clear_POS_X (0)							//�w�i�̍���X���W
#define Clear_POS_Y (0)						    //�w�i�̍���Y���W
#define Clear_WIDTH (SCREEN_WIDTH)					//�w�i�̕�
#define Clear_HEIGHT (SCREEN_HEIGHT)				//�w�i�̍���

//=========================================================================
//�O���[�o��
//=========================================================================
LPDIRECT3DTEXTURE9 g_pTextureClear = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffClear = NULL;			//���_�o�b�t�@�ւ̃|�C���^

//=========================================================================
//�N���A / ������
//=========================================================================
void InitClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̏���


								//���e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, Clear_TEXTURENAME, &g_pTextureClear);

	//�����_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffClear,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

						//�����_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffClear->Lock(0, 0, (void**)&pVtx, 0);

	//�����_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(Clear_POS_X, Clear_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Clear_POS_X + Clear_WIDTH, Clear_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Clear_POS_X, Clear_POS_Y + Clear_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Clear_POS_X + Clear_WIDTH, Clear_POS_Y + Clear_HEIGHT, 0.0f);

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
	g_pVtxBuffClear->Unlock();
}

//=========================================================================
//�^�C�g�� / �I��
//=========================================================================
void UninitClear(void)
{
	if (g_pTextureClear != NULL)
	{
		g_pTextureClear->Release();
		g_pTextureClear = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffClear != NULL)
	{
		g_pVtxBuffClear->Release();
		g_pVtxBuffClear = NULL;
	}
}

//=========================================================================
//�N���A / �X�V
//=========================================================================
void UpdateClear(void)
{
	FADE pFade;
	pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//���[�h�̐ݒ�
			SetFade(MODE_TITLE);
		}
	}
}

//=========================================================================
//�N���A / �`��
//=========================================================================
void DrawClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//���f�o�C�X����������
	pDevice = GetDevice();
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�����_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffClear, 0, sizeof(VERTEX_2D));

	//���e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureClear);

	//�����_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
