//=============================================================================
//
// �w�i���� [bgtitle.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "bgtitle.h"
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_BGTITLE		(5)								// �w�i�̎��
#define BGTITLE_TEXTURENAME_0	"data/TEXTURE/pause100.png"		//�w�i�̃e�N�X�`��3
#define BGTITLE_TEXTURENAME_1	"data/TEXTURE/bg.png"		//�w�i�̃e�N�X�`��2
#define BGTITLE_TEXTURENAME_2	"data/TEXTURE/cloud2.png"		//�w�i�̃e�N�X�`��1
#define BGTITLE_TEXTURENAME_3	"data/TEXTURE/title01.png"		//�w�i�̃e�N�X�`��1
#define BGTITLE_TEXTURENAME_4	"data/TEXTURE/ground.png"		//�w�i�̃e�N�X�`��1


#define BG_POS_X		(0)							//�w�i����X���W
#define BG_POS_Y		(0)							//�w�i����Y���W
#define BG_WIDTH		(SCREEN_WIDTH)				//�w�i�̕�
#define BG_HEIGHT		(SCREEN_HEIGHT)				//�w�i�̍���
//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBGTitle[MAX_TYPE_BGTITLE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBGTitle = NULL;					// ���_�o�b�t�@�ւ̃|�C���^

D3DXVECTOR2 g_BGTitle[2];

int nCntTime;
//=============================================================================
// ����������
//=============================================================================
void InitBGTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBG;	//�w�i�̃J�E���g

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	nCntTime = 0;
	for (int nCount = 0; nCount < MAX_TYPE_BGTITLE; nCount++)
	{
		g_BGTitle[0] = D3DXVECTOR2(0.0f, 0.0f);
		g_BGTitle[1] = D3DXVECTOR2(0.0f, 0.0f);
		g_BGTitle[2] = D3DXVECTOR2(0.0f, 0.0f);
	}

	// �e�N�X�`���̓ǂݍ���(3�̕�)
	D3DXCreateTextureFromFile(pDevice, BGTITLE_TEXTURENAME_0, &g_pTextureBGTitle[0]);
	D3DXCreateTextureFromFile(pDevice, BGTITLE_TEXTURENAME_1, &g_pTextureBGTitle[1]);
	D3DXCreateTextureFromFile(pDevice, BGTITLE_TEXTURENAME_2, &g_pTextureBGTitle[2]);
	D3DXCreateTextureFromFile(pDevice, BGTITLE_TEXTURENAME_3, &g_pTextureBGTitle[3]);
	D3DXCreateTextureFromFile(pDevice, BGTITLE_TEXTURENAME_4, &g_pTextureBGTitle[4]);

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TYPE_BGTITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBGTitle,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBGTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < MAX_TYPE_BGTITLE; nCntBG++)
	{
		//====================================
		//
		//	�悭�킩��Ȃ�
		//
		//====================================
		//���_�̍��W
		//pVtx[0].pos = D3DXVECTOR3(0 , 0.0f , 0.0f);
		//pVtx[1].pos = D3DXVECTOR3( BG_WIDTH , 0.0f , 0.0f);
		//pVtx[2].pos = D3DXVECTOR3( 0 , BG_HEIGHT , 0.0f);
		//pVtx[3].pos = D3DXVECTOR3(BG_WIDTH , BG_HEIGHT, 0.0f);

		////1.0f�ŌŒ�
		//pVtx[0].rhw = 1.0f;
		//pVtx[1].rhw = 1.0f;
		//pVtx[2].rhw = 1.0f;
		//pVtx[3].rhw = 1.0f;

		////���_�J���[
		//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		////�e�N�X�`�����W
		//
		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);







		//====================================
		//
		//	�w�i
		//
		//====================================
		//���_�̍��W
		pVtx[4].pos = D3DXVECTOR3(0, 0.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(BG_WIDTH , 0.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(0, SCREEN_HEIGHT , 0.0f);
		pVtx[7].pos = D3DXVECTOR3(BG_WIDTH , SCREEN_HEIGHT, 0.0f);

		//1.0f�ŌŒ�
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//���_�J���[
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[4].tex = D3DXVECTOR2(0.0, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);






		//====================================
		//
		//	�_
		//
		//====================================
		pVtx[8].pos = D3DXVECTOR3(0, -50, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(BG_WIDTH, -50, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(0, BG_HEIGHT - 150, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT -150, 0.0f);

		//1.0f�ŌŒ�
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//���_�J���[
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[11].tex = D3DXVECTOR2(0.0f, 1.0f);


		//====================================
		//
		//	�X
		//
		//====================================
		pVtx[12].pos = D3DXVECTOR3(0, -50, 0.0f);
		pVtx[13].pos = D3DXVECTOR3(BG_WIDTH, -50, 0.0f);
		pVtx[14].pos = D3DXVECTOR3(0, 720, 0.0f);
		pVtx[15].pos = D3DXVECTOR3(BG_WIDTH, 720, 0.0f);

		//1.0f�ŌŒ�
		pVtx[12].rhw = 1.0f;
		pVtx[13].rhw = 1.0f;
		pVtx[14].rhw = 1.0f;
		pVtx[15].rhw = 1.0f;

		//���_�J���[
		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W

		pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);



		//====================================
		//
		//	�n��
		//
		//====================================
		pVtx[16].pos = D3DXVECTOR3(0 ,450 , 0.0f);
		pVtx[17].pos = D3DXVECTOR3( BG_WIDTH ,450 , 0.0f);
		pVtx[18].pos = D3DXVECTOR3( 0 , BG_HEIGHT , 0.0f);
		pVtx[19].pos = D3DXVECTOR3(BG_WIDTH , BG_HEIGHT, 0.0f);

		//1.0f�ŌŒ�
		pVtx[16].rhw = 1.0f;
		pVtx[17].rhw = 1.0f;
		pVtx[18].rhw = 1.0f;
		pVtx[19].rhw = 1.0f;

		//���_�J���[
		pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		
		pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[17].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[19].tex = D3DXVECTOR2(1.0f, 1.0f);


		
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBGTitle->Unlock();

	

}

//=============================================================================
// �I������
//=============================================================================
void UninitBGTitle(void)
{
	

	// �e�N�X�`���̊J��
	for (int nCount = 0; nCount < MAX_TYPE_BGTITLE; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBGTitle[nCount] != NULL)
		{
			g_pTextureBGTitle[nCount]->Release();
			g_pTextureBGTitle[nCount] = NULL;
		}
	}


	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBGTitle != NULL)
	{
		g_pVtxBuffBGTitle->Release();
		g_pVtxBuffBGTitle = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBGTitle(void)
{
	//int nCounter = 0;

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	
	g_BGTitle[0].x -= 0.002f;
	//g_BGTitle[1].x -= 0.002f;
	g_BGTitle[2].x -= 0.0025f;

	
	nCntTime++;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBGTitle->Lock(0, 0, (void**)&pVtx, 0);
	
			//�e�N�X�`�����W���X�V
			pVtx[0].tex = D3DXVECTOR2(g_BGTitle[0].x, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_BGTitle[0].x - 1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_BGTitle[0].x, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_BGTitle[0].x - 1.0f, 1.0f);

			//pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�

			////�e�N�X�`�����W���X�V
			//pVtx[4].tex = D3DXVECTOR2(g_BGTitle[1].x, 0.0f);
			//pVtx[5].tex = D3DXVECTOR2(g_BGTitle[1].x - 1.0f, 0.0f);
			//pVtx[6].tex = D3DXVECTOR2(g_BGTitle[1].x, 1.0f);
			//pVtx[7].tex = D3DXVECTOR2(g_BGTitle[1].x - 1.0f, 1.0f);
			////pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�

			//�e�N�X�`�����W���X�V
			pVtx[8].tex = D3DXVECTOR2(g_BGTitle[2].x, 0.0f);
			pVtx[9].tex = D3DXVECTOR2(g_BGTitle[2].x - 1.0f, 0.0f);
			pVtx[10].tex = D3DXVECTOR2(g_BGTitle[2].x, 1.0f);
			pVtx[11].tex = D3DXVECTOR2(g_BGTitle[2].x - 1.0f, 1.0f);


			////���_�J���[
			//pVtx[0].col = D3DXCOLOR(0.7f - (0.00054f * nCntTime), 0.8f - (0.00085f * nCntTime), 1.0f - (0.0018f * nCntTime), 1.0f);
			//pVtx[1].col = D3DXCOLOR(0.7f - (0.00054f * nCntTime), 0.8f - (0.00085f * nCntTime), 1.0f - (0.0018f * nCntTime), 1.0f);
			//pVtx[2].col = D3DXCOLOR(0.8f - (0.00055f * nCntTime), 0.9f - (0.0055f * nCntTime), 1.0f - (0.0016f * nCntTime), 1.0f);
			//pVtx[3].col = D3DXCOLOR(0.8f - (0.00055f * nCntTime), 0.9f - (0.0055f * nCntTime), 1.0f - (0.0016f * nCntTime), 1.0f);

			////���_�J���[
			//pVtx[4].col = D3DXCOLOR(1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f);
			//pVtx[5].col = D3DXCOLOR(1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f);
			//pVtx[6].col = D3DXCOLOR(1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f);
			//pVtx[7].col = D3DXCOLOR(1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f);


	
			////���_
			//pVtx[8].col = D3DXCOLOR(1.0f - (0.00045f * nCntTime), 1.0f - (0.00045f * nCntTime), 1.0f - (0.00045f * nCntTime), 1.0f);
			//pVtx[9].col = D3DXCOLOR(1.0f - (0.00045f * nCntTime), 1.0f - (0.00045f * nCntTime), 1.0f - (0.00045f * nCntTime), 1.0f);
			//pVtx[10].col = D3DXCOLOR(1.0f - (0.00045f * nCntTime), 1.0f - (0.00045f * nCntTime), 1.0f - (0.00045f * nCntTime), 1.0f);
			//pVtx[11].col = D3DXCOLOR(1.0f - (0.00045f * nCntTime), 1.0f - (0.00045f * nCntTime), 1.0f - (0.00045f * nCntTime), 1.0f);


			////���_�J���[
			//pVtx[12].col = D3DXCOLOR(1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f);
			//pVtx[13].col = D3DXCOLOR(1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f);
			//pVtx[14].col = D3DXCOLOR(1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f);
			//pVtx[15].col = D3DXCOLOR(1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f - (0.0003f * nCntTime), 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBGTitle->Unlock();

	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBGTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	// �|���S���̕`��

		
			// �f�o�C�X�̎擾
			pDevice = GetDevice();

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffBGTitle, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCntBG = 0; nCntBG < MAX_TYPE_BGTITLE; nCntBG++)
	{

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBGTitle[nCntBG]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG * 4, 2);
		
	}
}


