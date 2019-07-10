//=============================================================================
// �|�[�Y�̏��� [pause.cpp]
// Author:Kobayashi/���� ����
//=============================================================================
#include "main.h"
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "game.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define PAUSE_TEXTURENAME	""								// �ǂݍ��ރe�N�X�`��
#define PAUSE_TEXTURENAME1	""		// �ǂݍ��ރe�N�X�`��1
#define PAUSE_TEXTURENAME2	""		// �ǂݍ��ރe�N�X�`��2
#define PAUSE_TEXTURENAME3	""		// �ǂݍ��ރe�N�X�`��2
#define PAUSE_TEXTURENAME4	""		// �ǂݍ��ރe�N�X�`��2
#define PAUSE_POS_X		(0)							// �w�i�̍���X���W
#define PAUSE_POS_Y		(0)							// �w�i�̍���Y���W
#define PAUSE_POS_X1	(SCREEN_WIDTH)				// �|�[�Y1�̑傫��
#define PAUSE_POS_Y1	(SCREEN_HEIGHT)				// �|�[�Y1�̑傫��
#define PAUSE_POS_X2	(620)						// �|�[�Y2�̑傫��
#define PAUSE_POS_Y2	(130)						// �|�[�Y2�̑傫��
#define PAUSE_POS_X3	(620)						// �|�[�Y3�̑傫��
#define PAUSE_POS_Y3	(130)						// �|�[�Y3�̑傫��
#define PAUSE_POS_X4	(620)						// �|�[�Y4�̑傫��
#define PAUSE_POS_Y4	(130)						// �|�[�Y4�̑傫��
#define MAX_PAUSE		(5)							// �w�i�̐�
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_PAUSE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
PAUSE g_aPause[MAX_PAUSE];
int g_nSelect;
bool g_bSelect;
int g_nPressCounter;
//=============================================================================
// �����������i�|���S���j
//=============================================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^
	VERTEX_2D*pVtx;				// ���_���ւ̃|�C���^
	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �w�i�̏��̏�����
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		g_aPause[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���W
		g_aPause[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �������W
		g_aPause[nCntPause].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);// �F
		g_aPause[nCntPause].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �w�i�̈ړ���
		g_aPause[nCntPause].nType = 0;								// �^�C�v
		g_aPause[nCntPause].nCounterAnim = 0;						// �J�E���^�[
		g_aPause[nCntPause].nPatternAnim = 0;						// �p�^�[��No
		g_aPause[nCntPause].bUse = false;							// �g�p����Ă��邩�ǂ���
	}
	g_nSelect = PAUSETYPE_CONTINUE;
	g_bSelect = false;
	g_nPressCounter = 0;
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
							PAUSE_TEXTURENAME1,
							&g_pTexturePause[1]);
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
							PAUSE_TEXTURENAME2,
							&g_pTexturePause[2]);
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
							PAUSE_TEXTURENAME3,
							&g_pTexturePause[3]);
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
							PAUSE_TEXTURENAME4,
							&g_pTexturePause[4]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE,
							D3DUSAGE_WRITEONLY,
							FVF_VERTEX_2D,
							D3DPOOL_MANAGED,
							&g_pVtxBuffPause,
							NULL);

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-(SCREEN_WIDTH / 2), -(SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2), -(SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;
	pVtx[2].pos = D3DXVECTOR3(-(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;

	pVtx[4].pos = D3DXVECTOR3(-(PAUSE_POS_X1 / 2), -(PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;
	pVtx[5].pos = D3DXVECTOR3((PAUSE_POS_X1 / 2), -(PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;
	pVtx[6].pos = D3DXVECTOR3(-(PAUSE_POS_X1 / 2), (PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;
	pVtx[7].pos = D3DXVECTOR3((PAUSE_POS_X1 / 2), (PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;

	pVtx[8].pos = D3DXVECTOR3(-(PAUSE_POS_X2 / 2), -(PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;
	pVtx[9].pos = D3DXVECTOR3((PAUSE_POS_X2 / 2), -(PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;
	pVtx[10].pos = D3DXVECTOR3(-(PAUSE_POS_X2 / 2), (PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;
	pVtx[11].pos = D3DXVECTOR3((PAUSE_POS_X2 / 2), (PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;

	pVtx[12].pos = D3DXVECTOR3(-(PAUSE_POS_X3 / 2), -(PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;
	pVtx[13].pos = D3DXVECTOR3((PAUSE_POS_X3 / 2), -(PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;
	pVtx[14].pos = D3DXVECTOR3(-(PAUSE_POS_X3 / 2), (PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;
	pVtx[15].pos = D3DXVECTOR3((PAUSE_POS_X3 / 2), (PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;

	/*pVtx[16].pos = D3DXVECTOR3(-(PAUSE_POS_X4 / 2), -(PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;
	pVtx[17].pos = D3DXVECTOR3((PAUSE_POS_X4 / 2), -(PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;
	pVtx[18].pos = D3DXVECTOR3(-(PAUSE_POS_X4 / 2), (PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;
	pVtx[19].pos = D3DXVECTOR3((PAUSE_POS_X4 / 2), (PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;*/
	// �e�N�X�`�����W�̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);
	/*pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[17].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[19].tex = D3DXVECTOR2(1.0f, 1.0f);*/
	for (int nCntPause = 0 ; nCntPause < MAX_PAUSE; nCntPause++,pVtx += 4)
	{
		
		// rhw�̐ݒ�
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].rhw = 1.0f;
		}

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_aPause[nCntPause].col;
		pVtx[1].col = g_aPause[nCntPause].col;
		pVtx[2].col = g_aPause[nCntPause].col;
		pVtx[3].col = g_aPause[nCntPause].col;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

}
//=============================================================================
// �I�������i�|���S���j
//=============================================================================
void UninitPause(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < MAX_PAUSE; nCntTex++)
	{
		if (g_pTexturePause[nCntTex] != NULL)
		{
			g_pTexturePause[nCntTex]->Release();
			g_pTexturePause[nCntTex] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}
//=============================================================================
// �X�V�����i�|���S���j
//=============================================================================
void UpdatePause(void)
{
	VERTEX_2D*pVtx;
	FADE pFADE;
	pFADE = GetFade();

	if (pFADE == FADE_NONE)
	{
		if (g_nSelect == PAUSETYPE_CONTINUE)
		{// continu
			g_aPause[g_nSelect + 2].col = D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f);
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				ReleaseGamePause();
			}
		}
		else if (g_nSelect == PAUSETYPE_RETRY)
		{// retry
			g_aPause[g_nSelect + 2].col = D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f);
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				SetFade(MODE_GAME);
			}
		}
		//else if (g_nSelect == PAUSETYPE_QUIT)
		//{// quit
		//	g_aPause[g_nSelect + 2].col = D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f);
		//	if (GetKeyboardTrigger(DIK_RETURN) == true)
		//	{
		//		SetFade(MODE_TITLE);
		//		SetGameState(GAMESTATE_NONE);
		//	}
		//}
	}
	if (GetKeyboardTrigger(DIK_S) == true)
	{// ���Ɉړ�(�P�́j
		g_aPause[g_nSelect + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		g_nSelect = (g_nSelect + 1) % PAUSETYPE_MAX;
	}
	else if (GetKeyboardTrigger(DIK_W) == true)
	{// ��Ɉړ�(�P��)
		g_aPause[g_nSelect + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		g_nSelect = (g_nSelect + (PAUSETYPE_MAX-1)) % PAUSETYPE_MAX;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{// ���Ɉړ�(�A��)
		g_nPressCounter++;
		if (g_nPressCounter >= 30)
		{
			if (g_nPressCounter % 10 == 0)
			{
				g_aPause[g_nSelect + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				g_nSelect = (g_nSelect + 1) % PAUSETYPE_MAX;
			}
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{// ��Ɉړ�(�A��)
		g_nPressCounter++;
		if (g_nPressCounter >= 30)
		{
			if (g_nPressCounter % 10 == 0)
			{
				g_aPause[g_nSelect + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				g_nSelect = (g_nSelect + (PAUSETYPE_MAX-1)) % PAUSETYPE_MAX;
			}
		}
	}
	if (GetKeyboardTrigger(DIK_W) == true)
	{// ��������J�E���^�[���Z�b�g
		g_nPressCounter = 0;
	}
	else if (GetKeyboardTrigger(DIK_S) == true)
	{// ��������J�E���^�[���Z�b�g
		g_nPressCounter = 0;
	}
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		for (int nCnt = 0; nCnt < PAUSETYPE_MAX; nCnt++)
		{
			g_aPause[nCnt + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		}
		g_nSelect = 0;
	}

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++, pVtx += 4)
	{
		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_aPause[nCntPause].col;
		pVtx[1].col = g_aPause[nCntPause].col;
		pVtx[2].col = g_aPause[nCntPause].col;
		pVtx[3].col = g_aPause[nCntPause].col;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}
//=============================================================================
// �`�揈���i�|���S���j
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^
	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePause[g_aPause[nCntPause].nType]);
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
								nCntPause * 4,
								2);
	}
}
//=============================================================================
// �|�[�Y�̐ݒ�
//=============================================================================
void SetPause(D3DXVECTOR3 pos,D3DXCOLOR col, int nType)
{
	VERTEX_2D*pVtx;

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		if (g_aPause[nCntPause].bUse == false)
		{// �w�i���g�p����Ă��Ȃ�
			g_aPause[nCntPause].pos = pos;
			g_aPause[nCntPause].Initpos = pos;
			g_aPause[nCntPause].col = col;
			g_aPause[nCntPause].nType = nType;			
			g_aPause[nCntPause].bUse = true;	// �g�p���Ă����Ԃɂ���
			break;
		}
	}
	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-(SCREEN_WIDTH / 2), -(SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2), -(SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;
	pVtx[2].pos = D3DXVECTOR3(-(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f) + g_aPause[0].pos;
	pVtx[4].pos = D3DXVECTOR3(-(PAUSE_POS_X1 / 2), -(PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;
	pVtx[5].pos = D3DXVECTOR3((PAUSE_POS_X1 / 2), -(PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;
	pVtx[6].pos = D3DXVECTOR3(-(PAUSE_POS_X1 / 2), (PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;
	pVtx[7].pos = D3DXVECTOR3((PAUSE_POS_X1 / 2), (PAUSE_POS_Y1 / 2), 0.0f) + g_aPause[1].pos;
	pVtx[8].pos = D3DXVECTOR3(-(PAUSE_POS_X2 / 2), -(PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;
	pVtx[9].pos = D3DXVECTOR3((PAUSE_POS_X2 / 2), -(PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;
	pVtx[10].pos = D3DXVECTOR3(-(PAUSE_POS_X2 / 2), (PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;
	pVtx[11].pos = D3DXVECTOR3((PAUSE_POS_X2 / 2), (PAUSE_POS_Y2 / 2), 0.0f) + g_aPause[2].pos;
	pVtx[12].pos = D3DXVECTOR3(-(PAUSE_POS_X3 / 2), -(PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;
	pVtx[13].pos = D3DXVECTOR3((PAUSE_POS_X3 / 2), -(PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;
	pVtx[14].pos = D3DXVECTOR3(-(PAUSE_POS_X3 / 2), (PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;
	pVtx[15].pos = D3DXVECTOR3((PAUSE_POS_X3 / 2), (PAUSE_POS_Y3 / 2), 0.0f) + g_aPause[3].pos;
	/*pVtx[16].pos = D3DXVECTOR3(-(PAUSE_POS_X4 / 2), -(PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;
	pVtx[17].pos = D3DXVECTOR3((PAUSE_POS_X4 / 2), -(PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;
	pVtx[18].pos = D3DXVECTOR3(-(PAUSE_POS_X4 / 2), (PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;
	pVtx[19].pos = D3DXVECTOR3((PAUSE_POS_X4 / 2), (PAUSE_POS_Y4 / 2), 0.0f) + g_aPause[4].pos;*/
	g_pVtxBuffPause->Unlock();
}

