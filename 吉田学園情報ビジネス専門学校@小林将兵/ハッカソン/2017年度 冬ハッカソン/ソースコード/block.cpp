//=============================================================================
//
// �u���b�N���� [block.cpp]
// Author : komatsu
//
//=============================================================================
#include "block.h"
#include "player.h"
#include "input.h"
#include "sound.h"
#include "time.h"
#include "player.h"
#include "score.h"
#include "itemstate.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BLOCK_TEXTURENAME1 "data/TEXTURE/Home01.png"		//�e�N�X�`��1
#define BLOCK_TEXTURENAME2 "data/TEXTURE/Home02.png"		//�e�N�X�`��2
#define BLOCK_TEXTURENAME3 "data/TEXTURE/Home03.png"		//�e�N�X�`��3
#define BLOCK_TEXTURENAME4 "data/TEXTURE/Home04.png"		//�e�N�X�`��4
#define MAX_BLOCKTEXTURE	(4)								//�e�N�X�`���̍ő吔
#define	MAX_BLOCK			(128)							//�u���b�N�̍ő吔
#define MAX_PATTERN			(1)								//�p�^�[���̐�
#define ANIMATION_SPEED		(1)								//�A�j���[�V�������x
#define COLLISION_AREA		(10.0f)							//�����蔻��̒���
#define TEX_X				(1.0f)							//�e�N�X�`����X
#define TEX_Y				(1.0f)							//�e�N�X�`����Y

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureBlock[MAX_BLOCK] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
Block g_aBlock[MAX_BLOCK];									//�u���b�N�̏��

//=============================================================================
// ����������
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �u���b�N�̏��̏�����
	for(int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].nCounterAnim = 0;
		g_aBlock[nCntBlock].nPatternAnim = 0;
		g_aBlock[nCntBlock].bChange = false;
		g_aBlock[nCntBlock].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME1, &g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME2, &g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME3, &g_pTextureBlock[2]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME4, &g_pTextureBlock[3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight, g_aBlock[nCntBlock].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight, g_aBlock[nCntBlock].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, g_aBlock[nCntBlock].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, g_aBlock[nCntBlock].pos.z);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBlock(void)
{
	int nCntTex;

	for (nCntTex = 0; nCntTex < MAX_BLOCKTEXTURE; nCntTex++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureBlock[nCntTex] != NULL)
		{
			g_pTextureBlock[nCntTex]->Release();
			g_pTextureBlock[nCntTex] = NULL;
		}
	}
	
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBlock(void)
{
	Player pPlayer = *GetPlayer();

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight - pPlayer.move.y, g_aBlock[nCntBlock].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight - pPlayer.move.y, g_aBlock[nCntBlock].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight - pPlayer.move.y, g_aBlock[nCntBlock].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight - pPlayer.move.y, g_aBlock[nCntBlock].pos.z);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)	//�u���b�N���g�p����Ă���
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 + (4 * nCntBlock), 2);
		}
	}
}
//=============================================================================
// �u���b�N�̐ݒ菈��
//=============================================================================
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)	
		{//�u���b�N���g�p����Ă��Ȃ�
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].nType = nType;
			g_aBlock[nCntBlock].bChange = false;
			g_aBlock[nCntBlock].bUse = true;
			break;
		}
	}
}

//=============================================================================
// �u���b�N�̓����蔻�菈��
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth)
{
	bool bLand = false;
	Player *pPlayer;
	pPlayer = GetPlayer();

	ItemState *pItemState;
	pItemState = GetItemState();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�u���b�N���g�p����Ă���
			if (g_aBlock[nCntBlock].pos.x + (fWidth - COLLISION_AREA) >= pPos->x - g_aBlock[nCntBlock].fWidth		//��
				&& g_aBlock[nCntBlock].pos.x - (fWidth - COLLISION_AREA) <= pPos->x + g_aBlock[nCntBlock].fWidth)	//�E
			{//�u���b�N�Ɠ���y���ɂ���
				if (g_aBlock[nCntBlock].pos.y + fHeight >= pPos->y - g_aBlock[nCntBlock].fHeight					//��
					&& g_aBlock[nCntBlock].pos.y <= pPos->y + g_aBlock[nCntBlock].fHeight)							//��
				{//�u���b�N�Ɠ���x���ɂ���
					if (pPos->y >= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight
						&& pPosOld->y <= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight)
					{//�ォ��
						pPos->y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;
						pMove->y = 0.0f;
					}
					else if (pPos->y <= g_aBlock[nCntBlock].pos.y + fHeight
						&& pPosOld->y >= g_aBlock[nCntBlock].pos.y + fHeight)
					{//������
						if (pPlayer->bItem == true && g_aBlock[nCntBlock].bChange == false)
						{
							pItemState->bUse = false;
							g_aBlock[nCntBlock].bChange = true;
							pPlayer->bItem = false;
							AddScore(1000);
						}
						bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y + fHeight;
						pMove->y = 0.0f;
					}
					else if (pPos->x >= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - (fWidth - COLLISION_AREA)
						&& pPosOld->x <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth)
					{//������
						pPos->x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - (fWidth - COLLISION_AREA);
						pMove->x = 0.0f;
					}
					else if (pPos->x <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + (fWidth - COLLISION_AREA)
						&& pPosOld->x >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
					{//�E����
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + (fWidth - COLLISION_AREA);
						pMove->x = 0.0f;
					}
				}
			}
		}
	}
	return bLand;
}

Block *GetBlock(void)
{
	return &g_aBlock[0];
}