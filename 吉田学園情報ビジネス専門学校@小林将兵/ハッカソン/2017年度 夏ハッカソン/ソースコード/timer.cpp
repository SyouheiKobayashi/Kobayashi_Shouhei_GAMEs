//=============================================================================
//
// �^�C�}�[���� [timer.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "timer.h"
#include "main.h"
#include "fade.h"
#include "game.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_Timer		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);

#define MAX_TIMER (4)
#define TIMER_X (30.0f)
#define TIMER_Y (45.0f)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nCounter;	//��ԊǗ��̃J�E���^�[
	int nTime;		//�^�C��
}TIMER;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTimer = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
TIMER					g_Timer;					// �X�R�A
int						g_aTimer[MAX_TIMER];		//




//=============================================================================
// ����������
 //=============================================================================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�X�R�A������
	g_Timer.nTime = 2000;

	g_Timer.pos = D3DXVECTOR3(600, 50, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_Timer,		// �t�@�C���̖��O
		&g_pTextureTimer);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexTimer(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTimer(void)
{

	// �e�N�X�`���̊J��
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTimer(void)
{
	
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	
	
	g_Timer.nTime--;

	if (g_Timer.nTime == 0)
	{
		FADE pFade;

		pFade = *GetFade();
				
				//���[�h�ݒ�
				SetFade(MODE_CLEAR);
		
		g_Timer.nTime = 0;
		SetGameState(GAMESTATE_FAILED);
	}
		
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
		{
			g_aTimer[0] = g_Timer.nTime % 10000 / 1000;
			g_aTimer[1] = g_Timer.nTime % 1000 / 100;
			g_aTimer[2] = g_Timer.nTime % 100 / 10;
			g_aTimer[3] = g_Timer.nTime % 10;


			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f + 0.1f * g_aTimer[nCntTimer], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + 0.1f * g_aTimer[nCntTimer], 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + 0.1f * g_aTimer[nCntTimer], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f * g_aTimer[nCntTimer], 1.0f);



			pVtx += 4;

		}
		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTimer->Unlock();
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTimer(void)
{
	int nCntTimer;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTimer);

	for (nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTimer * 4, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;


	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);



	// ���_����ݒ�
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{

		pVtx[0].pos = D3DXVECTOR3(g_Timer.pos.x - TIMER_X, g_Timer.pos.y - TIMER_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Timer.pos.x + TIMER_X, g_Timer.pos.y - TIMER_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Timer.pos.x - TIMER_X, g_Timer.pos.y + TIMER_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Timer.pos.x + TIMER_X, g_Timer.pos.y + TIMER_Y, 0.0f);


		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.7f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.7f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.7f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.7f, 1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);


		pVtx += 4;

		if (nCntTimer == 1)
		{
			
			g_Timer.pos.x += 80;
		}
		else
		{
			g_Timer.pos.x += 50;
		}

	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();
}


