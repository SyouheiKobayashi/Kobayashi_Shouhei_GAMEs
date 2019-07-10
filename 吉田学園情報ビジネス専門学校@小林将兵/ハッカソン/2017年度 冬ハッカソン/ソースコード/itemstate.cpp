//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : komatsu
//
//=============================================================================
#include "itemstate.h"
#include "player.h"
#include "score.h"	
#include "game.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ITEM_TEXTURENAME	"data/TEXTURE/snow_crystal001.png"	//�\������t�@�C���̖��O
#define MAX_ITEM_TEX		(1)									//�ǂݍ��ރe�N�X�`���̐�
#define MAX_ITEM			(1)									//���Ă�A�C�e���̍ő吔
#define ITEM_POS_X			(30.0f)								//�A�C�e���̕�
#define ITEM_POS_Y			(30.0f)								//�A�C�e���̍���
#define COUNTER_ANIM_RESET	(4)									//�p�^�[����
#define ANIMATION_SPEED		(10)								//�A�j���[�V�������x
#define TEX_X				(0.2f)								//�e�N�X�`����X
#define TEX_Y				(1.0f)								//�e�N�X�`����Y

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureItemState[MAX_ITEM] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemState = NULL;				//���_�o�b�t�@�ւ̃|�C���^
ItemState g_aItemState[MAX_ITEM];								//�A�C�e���̏��

//=============================================================================
// ����������
//=============================================================================
void InitItemState(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	// �A�C�e���̏��̏�����
	for(int nCntItemState = 0; nCntItemState < MAX_ITEM; nCntItemState++)
	{
		g_aItemState[nCntItemState].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
		g_aItemState[nCntItemState].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aItemState[nCntItemState].nCounterAnim = 0;
		g_aItemState[nCntItemState].nPatternAnim = 0;
		g_aItemState[nCntItemState].fHeight = ITEM_POS_X;
		g_aItemState[nCntItemState].fWidth = ITEM_POS_Y;
		g_aItemState[nCntItemState].bUse = false;		
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,ITEM_TEXTURENAME,&g_pTextureItemState[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItemState,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffItemState->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItemState = 0; nCntItemState < MAX_ITEM; nCntItemState++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aItemState[nCntItemState].pos.x - g_aItemState[nCntItemState].fHeight, g_aItemState[nCntItemState].pos.y - g_aItemState[nCntItemState].fWidth, g_aItemState[nCntItemState].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aItemState[nCntItemState].pos.x + g_aItemState[nCntItemState].fHeight, g_aItemState[nCntItemState].pos.y - g_aItemState[nCntItemState].fWidth, g_aItemState[nCntItemState].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aItemState[nCntItemState].pos.x - g_aItemState[nCntItemState].fHeight, g_aItemState[nCntItemState].pos.y + g_aItemState[nCntItemState].fWidth, g_aItemState[nCntItemState].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aItemState[nCntItemState].pos.x + g_aItemState[nCntItemState].fHeight, g_aItemState[nCntItemState].pos.y + g_aItemState[nCntItemState].fWidth, g_aItemState[nCntItemState].pos.z);
		
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
		
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItemState->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitItemState(void)
{
	for (int nCntTex = 0; nCntTex < MAX_ITEM_TEX; nCntTex++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureItemState[nCntTex] != NULL)
		{
			g_pTextureItemState[nCntTex]->Release();
			g_pTextureItemState[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffItemState != NULL)
	{
		g_pVtxBuffItemState->Release();
		g_pVtxBuffItemState = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItemState(void)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffItemState->Lock(0, 0, (void**)&pVtx, 0);	

	for (int nCntItemState = 0; nCntItemState < MAX_ITEM; nCntItemState++)
	{
		if (g_aItemState[nCntItemState].bUse == true)
		{//�g�p���Ă���
			g_aItemState[nCntItemState].nCounterAnim++;	//�J�E���^���Z

			if ((g_aItemState[nCntItemState].nCounterAnim % ANIMATION_SPEED) == 0)
			{//�A�j���[�V�����̍X�V
				g_aItemState[nCntItemState].nPatternAnim = (g_aItemState[nCntItemState].nPatternAnim + 1 % COUNTER_ANIM_RESET);

				//�e�N�X�`�����W�X�V
				pVtx[0].tex = D3DXVECTOR2(TEX_X * (g_aItemState[nCntItemState].nPatternAnim % COUNTER_ANIM_RESET), 1.0f *(g_aItemState[nCntItemState].nPatternAnim / COUNTER_ANIM_RESET));
				pVtx[1].tex = D3DXVECTOR2(TEX_X * (g_aItemState[nCntItemState].nPatternAnim % COUNTER_ANIM_RESET) + TEX_X, 1.0f *(g_aItemState[nCntItemState].nPatternAnim / COUNTER_ANIM_RESET));
				pVtx[2].tex = D3DXVECTOR2(TEX_X * (g_aItemState[nCntItemState].nPatternAnim % COUNTER_ANIM_RESET), 1.0f *(g_aItemState[nCntItemState].nPatternAnim / COUNTER_ANIM_RESET) + TEX_Y);
				pVtx[3].tex = D3DXVECTOR2(TEX_X * (g_aItemState[nCntItemState].nPatternAnim % COUNTER_ANIM_RESET) + TEX_X, 1.0f *(g_aItemState[nCntItemState].nPatternAnim / COUNTER_ANIM_RESET) + TEX_Y);
			}
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItemState->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItemState(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffItemState, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for(int nCntItemState = 0; nCntItemState < MAX_ITEM; nCntItemState++)
	{
		if (g_aItemState[nCntItemState].bUse == true)	//�A�C�e�����g�p����Ă���
		{
			pDevice->SetTexture(0, g_pTextureItemState[g_aItemState[nCntItemState].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 + (4 * nCntItemState), 2);
		}
	}
}

//=============================================================================
// �A�C�e���̐ݒ菈��
//=============================================================================
void SetItemState(int nType)
{
	for (int nCntItemState = 0; nCntItemState < MAX_ITEM; nCntItemState++)
	{
		if (g_aItemState[nCntItemState].bUse == false)
		{//�A�C�e�����g�p����Ă��Ȃ�
			g_aItemState[nCntItemState].nType = nType;
			g_aItemState[nCntItemState].bUse = true;
			break;
		}
	}
}

ItemState *GetItemState(void)
{
	return &g_aItemState[0];
}