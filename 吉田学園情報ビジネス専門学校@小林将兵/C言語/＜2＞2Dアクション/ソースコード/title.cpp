//=========================================================================
// �^�C�g����ʂ̏��� [title.cpp]
// Author:Kobayashi/���� ����
//=========================================================================
#include "main.h"	//���C������
#include "title.h"	//�^�C�g������
#include "input.h"	//���͏���
#include "fade.h"	//�t�F�[�h��ʐ؂�ւ�����

//=========================================================================
//�}�N��
//=========================================================================
#define T_TYPE (2)//�w�i�̖���
#define Title_TEXTURENAME "DATA\\TEXTURE\\�w�iP_.jpg"//�ǂݍ��ރe�N�X�`��
#define Title_TEXTURENAME2 "DATA\\TEXTURE\\�^�C�g������.png"//�ǂݍ��ރe�N�X�`��

#define Title_POS_X (0)							//�w�i�̍���X���W
#define Title_POS_Y (0)						    //�w�i�̍���Y���W
#define Title_WIDTH (SCREEN_WIDTH)				//�w�i�̕�
#define Title_HEIGHT (SCREEN_HEIGHT)			//�w�i�̍���

//=========================================================================
//�O���[�o��
//=========================================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle[T_TYPE] = {};				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;			//���_�o�b�t�@�ւ̃|�C���^

int g_ScrollAnim;
//=========================================================================
//�^�C�g�� / ������
//=========================================================================
void InitTitle(void)
{
	g_ScrollAnim = 0;

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̏���
	
	//���e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, Title_TEXTURENAME, &g_pTextureTitle[0]);//�����w�i�p
	D3DXCreateTextureFromFile(pDevice, Title_TEXTURENAME2, &g_pTextureTitle[1]);//�^�C�g������

	//�����_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * T_TYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//�����_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntT = 0; nCntT < T_TYPE; nCntT++)
	{
		//�����_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(Title_POS_X, Title_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Title_POS_X + Title_WIDTH, Title_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(Title_POS_X, Title_POS_Y + Title_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Title_POS_X + Title_WIDTH, Title_POS_Y + Title_HEIGHT, 0.0f);

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
//--------------------
//�^�C�g������
//--------------------
		//���_���W�̐ݒ�
		pVtx[4].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(Title_WIDTH, 0, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(0, Title_HEIGHT, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(Title_WIDTH, Title_HEIGHT, 0.0f);

		//rhw�̐ݒ�
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//�����_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//=========================================================================
//�^�C�g�� / �I��
//=========================================================================
void UninitTitle(void)
{
	for (int nCnt = 0; nCnt < T_TYPE; nCnt++)
	{
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//=========================================================================
//�^�C�g�� / �X�V
//=========================================================================
void UpdateTitle(void)
{
	g_ScrollAnim++;

	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.0005f * g_ScrollAnim), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + (0.0005f * g_ScrollAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (0.0005f * g_ScrollAnim), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + (0.0005f * g_ScrollAnim), 1.0f);

	if (pVtx[0].tex.x < 0.0f)
	{
		pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	if (pVtx[2].tex.x < 0.0f)
	{
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	}

	pVtx += 4;
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();

	FADE pFade;
	pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//���[�h�̐ݒ�
			SetFade(MODE_TUTORIAL);
		}
	}
}

//=========================================================================
//�^�C�g�� / �`��
//=========================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//���f�o�C�X����������
	pDevice = GetDevice();

	//�����_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//�����_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBG = 0; nCntBG < T_TYPE; nCntBG++)
	{
		//���e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCntBG]);


		//���|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG*4, 2);
	}
}
