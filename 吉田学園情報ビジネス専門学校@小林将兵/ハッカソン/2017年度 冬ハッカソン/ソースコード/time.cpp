//=============================================================================
//
// �^�C������ [time.cpp]
// Author : komatsu
//
//=============================================================================
#include "time.h"
#include "game.h"
#include "fade.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TIME_TEXTURENAME	"data/TEXTURE/number001.png"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_TIME			(3)								//�^�C���̌���

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
TIME g_Time;						// �^�C��
int g_nTimeCounter;

//=============================================================================
// ����������
//=============================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �^�C���̏�����
	g_Time.nTime = 45;
	g_Time.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_Time.col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	g_nTimeCounter = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TIME_TEXTURENAME, &g_pTextureTime);

	// ���_���̍쐬
	MakeVertexTime(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTime(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTime(void)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^
	int nCntTime;
	int nTexData;

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	if (g_nTimeCounter % 60 == 0 && g_Time.nTime >= 0)
	{
		g_Time.nTime--;		//���Ԍo��
	}

	nTexData = g_Time.nTime;

	if (g_Time.nTime >= 0)
	{
		for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
		{
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2((nTexData % 10) * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((nTexData % 10) * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 1.0f);

			nTexData /= 10;

			if (g_Time.nTime <= 10)
			{
				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else
			{
				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
		}
	}

	g_nTimeCounter++;
	GAMESTATE pGamestate;
	pGamestate = GetGameState();
	if (g_Time.nTime == 0)
	{
		g_Time.nTime = 0;
		pGamestate = GAMESTATE_NORMAL;
		if (pGamestate == GAMESTATE_NORMAL && pGamestate != GAMESTATE_END)
		{
			SetFade(MODE_RANKING);
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTime(void)
{
	int nCntScore;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	// �|���S���̕`��
	for (nCntScore = 0; nCntScore < MAX_TIME; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 + (4 * nCntScore), 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	int nCntTime;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0, g_Time.pos.x = 650; nCntTime < MAX_TIME; nCntTime++, g_Time.pos.x -= 30)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_Time.pos.x, 20.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Time.pos.x + 30.0f, 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Time.pos.x, 70.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Time.pos.x + 30.0f, 70.0f, 0.0f);

		//���_
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		
		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		
		if (nCntTime == 1)
		{
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.3f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.4f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.3f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.4f, 1.0f);
		}
		else
		{
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// �^�C���̎擾
//=============================================================================
TIME GetTime(void)
{
	return g_Time;
}

//=============================================================================
// �^�C���̎擾
//=============================================================================
void TimeOver(void)
{
	GAMESTATE pGamestate;
	pGamestate = GetGameState();
	if (g_Time.nTime == 0)
	{
		g_Time.nTime = 0;
		pGamestate = GAMESTATE_NORMAL;
		if (pGamestate == GAMESTATE_NORMAL && pGamestate != GAMESTATE_END)
		{
			SetGameState(GAMESTATE_END);
		}
	}
}
