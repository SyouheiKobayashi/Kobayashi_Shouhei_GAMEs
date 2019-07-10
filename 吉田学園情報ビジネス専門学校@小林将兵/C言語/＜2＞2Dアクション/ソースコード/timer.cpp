//=============================================================================
// �������Ԃ̏��� [timer.cpp]
// Author : Kobayashi / ���� ����
//=============================================================================
#include "main.h"
#include "game.h"
#include "timer.h"
#include "fade.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_NAME	"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TIMER_SET (16)//��������
#define MAX_DISPLAY (3)//�\������
#define TIMER_WIDTH (25.0f)//���T�C�Y
#define TIMER_HEIGHT (35.0f)//�c�T�C�Y

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nCounter;	//��ԊǗ��̃J�E���^�[
	int nTime;		//�^�C��
}TIMER;

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTimer = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;		//���_�o�b�t�@�ւ̃|�C���^

TIMER g_Timer;					//�X�R�A

int g_nTimer[MAX_DISPLAY];		//�\�����錅

//=============================================================================
// ����������
 //=============================================================================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�X�R�A������
	g_Timer.nTime = TIMER_SET*100;

	g_Timer.pos = D3DXVECTOR3(600, 50, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,TEXTURE_NAME,&g_pTextureTimer);

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
	bool bSize = false; //�T�C�Y��3����

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_����ݒ�
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	g_Timer.nTime--;//���Ԃ����炷

	if (g_Timer.nTime == 0)//�c�莞��0�ɂȂ�����
	{
		FADE pFade;

		pFade = GetFade();
				
		//���[�h�ݒ�
		//SetFade(MODE_RESULT);
		
		g_Timer.nTime = 0;
		SetGameState(GAMESTATE_END);
	}

	for (int nCntTimer = 0; nCntTimer < MAX_DISPLAY; nCntTimer++)
	{
			//���l3����������
#if 1
			g_nTimer[0] = g_Timer.nTime % 100000 / 10000;
			g_nTimer[1] = g_Timer.nTime % 10000 / 1000;
			g_nTimer[2] = g_Timer.nTime % 1000 / 100;
#endif
			//���l2����������
#if 0
			g_nTimer[0] = g_Timer.nTime % 10000 / 1000;
			g_nTimer[1] = g_Timer.nTime % 1000 / 100;
#endif

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f + 0.1f * g_nTimer[nCntTimer], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + 0.1f * g_nTimer[nCntTimer], 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + 0.1f * g_nTimer[nCntTimer], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f * g_nTimer[nCntTimer], 1.0f);

			if (g_Timer.nTime == 1100)//�c�莞��10�ɂȂ�����
			{
				//�\������鐧�����Ԃ̃J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
			}
			if (g_Timer.nTime == 600)//�c�莞��5�ɂȂ�����
			{
				//�\������鐧�����Ԃ̃J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}

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

	for (nCntTimer = 0; nCntTimer < MAX_DISPLAY; nCntTimer++)
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
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DISPLAY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	// ���_����ݒ�
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTimer = 0; nCntTimer < MAX_DISPLAY; nCntTimer++)
	{
		pVtx[0].pos = D3DXVECTOR3(g_Timer.pos.x - TIMER_WIDTH, g_Timer.pos.y - TIMER_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Timer.pos.x + TIMER_WIDTH, g_Timer.pos.y - TIMER_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Timer.pos.x - TIMER_WIDTH, g_Timer.pos.y + TIMER_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Timer.pos.x + TIMER_WIDTH, g_Timer.pos.y + TIMER_HEIGHT, 0.0f);

		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�\������鐧�����Ԃ̃J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
		g_Timer.pos.x += 45;//�\���Ԋu
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();
}


