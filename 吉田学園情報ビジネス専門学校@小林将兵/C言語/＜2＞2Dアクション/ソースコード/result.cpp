//=========================================================================
// ���U���g��ʂ̏��� [result.cpp]
// Kobayashi Syouhei / ���я���
//=========================================================================
#include "main.h"	//���C������
#include "result.h"	//���U���g����
#include "input.h"	//���͏���
#include "fade.h"	//�t�F�[�h��ʐ؂�ւ�����

//=========================================================================
//�}�N��
//=========================================================================
#define Result_TEXTURENAME "DATA\\TEXTURE\\�����Ԃ�.png"		//�ǂݍ��ރe�N�X�`��
#define Result_POS_X (0)							//�w�i�̍���X���W
#define Result_POS_Y (0)						    //�w�i�̍���Y���W
#define Result_WIDTH (SCREEN_WIDTH)					//�w�i�̕�
#define Result_HEIGHT (SCREEN_HEIGHT)				//�w�i�̍���

//=========================================================================
//�O���[�o��
//=========================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;			//���_�o�b�t�@�ւ̃|�C���^

//=========================================================================
//���U���g / ������
//=========================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̏���


	//���e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, Result_TEXTURENAME, &g_pTextureResult);

	//�����_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

						//�����_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//�����_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(Result_POS_X, Result_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Result_POS_X + Result_WIDTH, Result_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Result_POS_X, Result_POS_Y + Result_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Result_POS_X + Result_WIDTH, Result_POS_Y + Result_HEIGHT, 0.0f);

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
	g_pVtxBuffResult->Unlock();
}

//=========================================================================
//�^�C�g�� / �I��
//=========================================================================
void UninitResult(void)
{
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//=========================================================================
//���U���g / �X�V
//=========================================================================
void UpdateResult(void)
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
//���U���g / �`��
//=========================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//���f�o�C�X����������
	pDevice = GetDevice();
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�����_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	//�����_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
