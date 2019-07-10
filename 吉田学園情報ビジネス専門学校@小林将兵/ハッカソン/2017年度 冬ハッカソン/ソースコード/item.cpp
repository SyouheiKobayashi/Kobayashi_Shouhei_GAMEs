//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : komatsu
//
//=============================================================================
#include "item.h"
#include "player.h"
#include "score.h"	
#include "game.h"
#include "sound.h"
#include "itemstate.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ITEM_TEXTURENAME	"data/TEXTURE/snow_crystal001.png"	//�\������t�@�C���̖��O
#define MAX_ITEM_TEX		(1)									//�ǂݍ��ރe�N�X�`���̐�
#define ITEM_POS_X			(20.0f)								//�A�C�e���̕�
#define ITEM_POS_Y			(20.0f)								//�A�C�e���̍���
#define COUNTER_ANIM_RESET	(4)									//�p�^�[����
#define ANIMATION_SPEED		(10)								//�A�j���[�V�������x
#define TEX_X				(0.2f)								//�e�N�X�`����X
#define TEX_Y				(1.0f)								//�e�N�X�`����Y

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureItem[MAX_ITEM] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Item g_aItem[MAX_ITEM];								//�A�C�e���̏��

//=============================================================================
// ����������
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	// �A�C�e���̏��̏�����
	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].nCounterAnim = 0;
		g_aItem[nCntItem].nPatternAnim = 0;
		g_aItem[nCntItem].fHeight = ITEM_POS_X;
		g_aItem[nCntItem].fWidth = ITEM_POS_Y;
		g_aItem[nCntItem].bUse = false;		
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,ITEM_TEXTURENAME,&g_pTextureItem[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.z);
		
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
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{
	for (int nCntTex = 0; nCntTex < MAX_ITEM_TEX; nCntTex++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureItem[nCntTex] != NULL)
		{
			g_pTextureItem[nCntTex]->Release();
			g_pTextureItem[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	Player pPlayer = *GetPlayer();

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);	

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{//�g�p���Ă���
			//���_���W�X�V
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.z);

			g_aItem[nCntItem].nCounterAnim++;	//�J�E���^���Z

			if ((g_aItem[nCntItem].nCounterAnim % ANIMATION_SPEED) == 0)
			{//�A�j���[�V�����̍X�V
				g_aItem[nCntItem].nPatternAnim = (g_aItem[nCntItem].nPatternAnim + 1 % COUNTER_ANIM_RESET);

				//�e�N�X�`�����W�X�V
				pVtx[0].tex = D3DXVECTOR2(TEX_X * (g_aItem[nCntItem].nPatternAnim % COUNTER_ANIM_RESET), 1.0f *(g_aItem[nCntItem].nPatternAnim / COUNTER_ANIM_RESET));
				pVtx[1].tex = D3DXVECTOR2(TEX_X * (g_aItem[nCntItem].nPatternAnim % COUNTER_ANIM_RESET) + TEX_X, 1.0f *(g_aItem[nCntItem].nPatternAnim / COUNTER_ANIM_RESET));
				pVtx[2].tex = D3DXVECTOR2(TEX_X * (g_aItem[nCntItem].nPatternAnim % COUNTER_ANIM_RESET), 1.0f *(g_aItem[nCntItem].nPatternAnim / COUNTER_ANIM_RESET) + TEX_Y);
				pVtx[3].tex = D3DXVECTOR2(TEX_X * (g_aItem[nCntItem].nPatternAnim % COUNTER_ANIM_RESET) + TEX_X, 1.0f *(g_aItem[nCntItem].nPatternAnim / COUNTER_ANIM_RESET) + TEX_Y);
			}
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)	//�A�C�e�����g�p����Ă���
		{
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 + (4 * nCntItem), 2);
		}
	}
}

//=============================================================================
// �A�C�e���̐ݒ菈��
//=============================================================================
void SetItem(D3DXVECTOR3 pos, int nType)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{//�A�C�e�����g�p����Ă��Ȃ�
			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].nType = nType;
			g_aItem[nCntItem].bUse = true;
			break;
		}
	}
}

//=============================================================================
// �A�C�e���̓����蔻��
//=============================================================================
void CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, float fHeight, float fWidth)
{
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true && pPlayer->bItem == false)
		{//�A�C�e�����g���Ă���
			if (g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth >= pPos->x
				&& g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fWidth <= pPos->x)
			{//�A�C�e���Ɠ���y���ɂ���
				if (g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fHeight <= pPos->y
					&& g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight >= pPos->y)
				{//�A�C�e���Ɠ���x���ɂ���
					SetItemState(0);
					AddScore(500);
					pPlayer->bItem = true;
					g_aItem[nCntItem].bUse = false;
				}
			}
		}
	}
}