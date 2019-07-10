//=============================================================================
// �w�i����[bg.cpp]
// Author:Kobayashi/���� ����
//=============================================================================
#include "main.h"
#include "bg.h"

//=============================================================================
//�}�N��
//=============================================================================
#define BG_TYPE (4)//�w�i�̖���
#define BG_TEXTURENAME "DATA\\TEXTURE\\�w�iP__.jpg" //�傫�Ȕw�i
#define BG_TEXTURENAME2 "DATA\\TEXTURE\\�w�iZ.png" //�_
#define BG_TEXTURENAME3 "DATA\\TEXTURE\\����B_.png" //����
#define BG_TEXTURENAME4 "DATA\\TEXTURE\\����B_.png" //����


#define BG_POS_X (0)						 //�w�i�̍���X���W
#define BG_POS_Y (0)						 //�w�i�̍���Y���W
#define BG_WIDTH (SCREEN_WIDTH)				 //�w�i�̕�
#define BG_HEIGHT (SCREEN_HEIGHT)			 //�w�i�̍���
#define H_SIZE (200)


//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBG[BG_TYPE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;

int g_nCountAnimBG; //�A�j���[�V�����J�E���^�[

int SpeedAnimationBG;//�A�j���[�V�������x
int PatternAnimationBG;//�A�j���[�V�����̃p�^�[����

//D3DXVECTOR2 g_BG[1];//
//=============================================================================
//�w�i�̏���������
//=============================================================================
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

 //[�A�j���[�V����]
	g_nCountAnimBG = 0;

	SpeedAnimationBG=0;
	PatternAnimationBG=0;
	
	//�f�o�C�X�̏���
	pDevice = GetDevice();

	/*for (int nCount = 0; nCount < BG_TYPE; nCount++)
	{
		g_BG[nCount] = D3DXVECTOR2(0.0f, 0.0f);
	}*/

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME, &g_pTextureBG[0]);//�w�i
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME2, &g_pTextureBG[1]);//�_
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME3, &g_pTextureBG[2]);//
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME3, &g_pTextureBG[3]);//����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * BG_TYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBG = 0; nCntBG < BG_TYPE; nCntBG++)
	{
		//�傫�Ȕw�i�e�N�X�`��
#if 1
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BG_POS_X + BG_WIDTH, BG_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y + BG_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BG_POS_X + BG_WIDTH, BG_POS_Y + BG_HEIGHT, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
#endif
		//�_�e�N�X�`��
#if 1
		//���_���W�̐ݒ�
		pVtx[4].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(BG_POS_X + BG_WIDTH, BG_POS_Y, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y + BG_HEIGHT, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(BG_POS_X + BG_WIDTH, BG_POS_Y + BG_HEIGHT, 0.0f);

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
#endif

#if 1
		//���_���W�̐ݒ�
		pVtx[8].pos = D3DXVECTOR3(H_SIZE, 0, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(H_SIZE *2, 0, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(H_SIZE, H_SIZE, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(H_SIZE *2, H_SIZE, 0.0f);

		//rhw�̐ݒ�
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[8].col = D3DCOLOR_RGBA(255, 2055, 255, 0);
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 0);

		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(0.125f, 1.0f);
#endif

#if 1
		//���_���W�̐ݒ�
		pVtx[12].pos = D3DXVECTOR3(H_SIZE, 0, 0.0f);
		pVtx[13].pos = D3DXVECTOR3(H_SIZE * 2, 0, 0.0f);
		pVtx[14].pos = D3DXVECTOR3(H_SIZE, H_SIZE, 0.0f);
		pVtx[15].pos = D3DXVECTOR3(H_SIZE * 2, H_SIZE, 0.0f);

		//rhw�̐ݒ�
		pVtx[12].rhw = 1.0f;
		pVtx[13].rhw = 1.0f;
		pVtx[14].rhw = 1.0f;
		pVtx[15].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[12].col = D3DCOLOR_RGBA(255, 2055, 255, 0);
		pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 0);

		pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[13].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[15].tex = D3DXVECTOR2(0.125f, 1.0f);
#endif
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBG->Unlock();
}

//=============================================================================
//�w�i�̏I������
//=============================================================================
void UninitBG(void)
{
	for (int nCnt = 0; nCnt < BG_TYPE; nCnt++)
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

//=============================================================================
//�w�i�̍X�V����
//=============================================================================
void UpdateBG(void)
{
#if 1
	g_nCountAnimBG++; //�J�E���^�[�̉��Z
	
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	g_nCountAnimBG++; //�J�E���^�[�̉��Z

	//�e�N�X�`�����W�̐ݒ�
	//�c�X�N���[����
#if 0
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f - (0.001f * g_nCountAnimBG));
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f - (0.001f * g_nCountAnimBG));
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f - (0.001f * g_nCountAnimBG));
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f - (0.001f * g_nCountAnimBG));
#endif
	//���X�N���[����
#if 1
	pVtx[4].tex = D3DXVECTOR2(0.0f + (0.0005f * g_nCountAnimBG), 0.0f );
	pVtx[5].tex = D3DXVECTOR2(1.0f + (0.0005f * g_nCountAnimBG), 0.0f );
	pVtx[6].tex = D3DXVECTOR2(0.0f + (0.0005f * g_nCountAnimBG), 1.0f );
	pVtx[7].tex = D3DXVECTOR2(1.0f + (0.0005f * g_nCountAnimBG), 1.0f );
#endif

	if (pVtx[4].tex.x < 0.0f)
	{
		pVtx[4].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[7].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	if (pVtx[6].tex.x < 0.0f)
	{
		pVtx[5].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
//------------------------------------
// �A�j���[�V��������
//------------------------------------
	SpeedAnimationBG++; //�J�E���^�[�̉��Z
	if ((SpeedAnimationBG % 20) == 0)
	{
		PatternAnimationBG = (PatternAnimationBG+1) % 8;//�p�^�[��No.�X�V

		pVtx[8].tex = D3DXVECTOR2(0.0f + (PatternAnimationBG*0.125f), 0.0f);
		pVtx[9].tex = D3DXVECTOR2(0.125f + (PatternAnimationBG*0.125f), 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f + (PatternAnimationBG*0.125f), 1.0f);
		pVtx[11].tex = D3DXVECTOR2(0.125f + (PatternAnimationBG*0.125f), 1.0f);

		pVtx[12].tex = D3DXVECTOR2(0.0f + (PatternAnimationBG*0.125f), 0.0f);
		pVtx[13].tex = D3DXVECTOR2(0.125f + (PatternAnimationBG*0.125f), 0.0f);
		pVtx[14].tex = D3DXVECTOR2(0.0f + (PatternAnimationBG*0.125f), 1.0f);
		pVtx[15].tex = D3DXVECTOR2(0.125f + (PatternAnimationBG*0.125f), 1.0f);
	}

	//���_���W�̐ݒ�
	pVtx[8].pos = D3DXVECTOR3(H_SIZE, 300, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(H_SIZE * 2, 300, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(H_SIZE, H_SIZE+300 , 0.0f);
	pVtx[11].pos = D3DXVECTOR3(H_SIZE * 2, H_SIZE+300, 0.0f);

	pVtx[12].pos = D3DXVECTOR3(H_SIZE+300, 100, 0.0f);
	pVtx[13].pos = D3DXVECTOR3((H_SIZE * 2) + 300, 100, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(H_SIZE + 300, H_SIZE + 100, 0.0f);
	pVtx[15].pos = D3DXVECTOR3((H_SIZE * 2) + 300, H_SIZE + 100, 0.0f);

	pVtx += 4;
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBG->Unlock();
#endif
}

//=============================================================================
//�w�i�̕`�揈��
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X����������
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBG = 0; nCntBG < BG_TYPE; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBG[nCntBG]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG * 4, 2);
	}
}
