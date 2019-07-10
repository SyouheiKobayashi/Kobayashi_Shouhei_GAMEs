//=============================================================================
//
// �^�C�}�[���� [timer.cpp]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#include "timer.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TIMER0		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TIMER1		"data/TEXTURE/frame_timer.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define NUM_TIMER	(3)		// �^�C�}�[�̍ő包��
#define TIMER_SIZE	(25)	// �^�C�}�[�̕����̑傫��
#define MAX_TEX		(2)
#define MAX_TIMER	(NUM_TIMER + 1)
#define FRAME_SIZE_X	(200)	// �t���[���̑傫��
#define FRAME_SIZE_Y	(150)	// �t���[���̑傫��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTimer[MAX_TEX] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
TIMER g_aTimer[MAX_TIMER];		// �^�C�}�[
int g_nTimer;		// ��������
int g_nCntSecond;	// �b�̃J�E���g

//=============================================================================
// ����������
//=============================================================================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntTimer = 0; nCntTimer < NUM_TIMER; nCntTimer++)
	{
		g_aTimer[nCntTimer].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 50.0f + (nCntTimer * 50.0f), 80, 0.0f);
		g_aTimer[nCntTimer].nType = 0;
	}

	g_aTimer[NUM_TIMER].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0.0f);
	g_aTimer[NUM_TIMER].nType = 1;

	g_nTimer = 60;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,TEXTURE_TIMER0,&g_pTextureTimer[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TIMER1, &g_pTextureTimer[1]);

	// ���_���̍쐬
	MakeVertexTimer(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTimer(void)
{
	for (int nCntTimer = 0; nCntTimer < MAX_TEX; nCntTimer++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureTimer[nCntTimer] != NULL)
		{
			g_pTextureTimer[nCntTimer]->Release();
			g_pTextureTimer[nCntTimer] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
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
	int nCntTimer;
	int aNumber[NUM_TIMER];

	// ���_����ݒ�
	VERTEX_2D *pVtx;
		
	g_nCntSecond++;

	if (g_nCntSecond % 60 == 0 && g_nTimer > 0)
	{// ���Ԃ����炷
		g_nTimer--;	// �J�E���g�_�E��
	}

	if (g_nTimer <= 0 && g_nCntSecond % 60 == 0)
	{// �^�C���I�[�o�[
		SetGameState(GAMESTATE_END);
	}

	aNumber[0] = g_nTimer % 1000 / 100;;
	aNumber[1] = g_nTimer % 100 / 10;
	aNumber[2] = g_nTimer % 10;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTimer = 0; nCntTimer < NUM_TIMER; nCntTimer++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntTimer] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntTimer] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntTimer] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntTimer] * 0.1f, 1.0f);

		pVtx += 4;	// ���_�f�[�^�̃|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTimer[g_aTimer[nCntTimer].nType]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTimer, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntTimer;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTimer = 0; nCntTimer < NUM_TIMER; nCntTimer++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aTimer[nCntTimer].pos.x - TIMER_SIZE, g_aTimer[nCntTimer].pos.y - TIMER_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTimer[nCntTimer].pos.x + TIMER_SIZE, g_aTimer[nCntTimer].pos.y - TIMER_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTimer[nCntTimer].pos.x - TIMER_SIZE, g_aTimer[nCntTimer].pos.y + TIMER_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTimer[nCntTimer].pos.x + TIMER_SIZE, g_aTimer[nCntTimer].pos.y + TIMER_SIZE, 0.0f);

		// 1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	// ���_�f�[�^�̃|�C���^��4�i�߂�
	}

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aTimer[NUM_TIMER].pos.x - FRAME_SIZE_X, g_aTimer[NUM_TIMER].pos.y - FRAME_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTimer[NUM_TIMER].pos.x + FRAME_SIZE_X, g_aTimer[NUM_TIMER].pos.y - FRAME_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTimer[NUM_TIMER].pos.x - FRAME_SIZE_X, g_aTimer[NUM_TIMER].pos.y + FRAME_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTimer[NUM_TIMER].pos.x + FRAME_SIZE_X, g_aTimer[NUM_TIMER].pos.y + FRAME_SIZE_Y, 0.0f);

	// 1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();
}

//=============================================================================
// �c�@�̎擾
//=============================================================================
int *GetTimer(void)
{
	return &g_nTimer;
}