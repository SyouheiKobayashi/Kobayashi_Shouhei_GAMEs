//=============================================================================
// �A�C�e������ [item.cpp]
// Author:Kobayashi/���� ����
//=============================================================================
#include "main.h"
#include "sound.h"
#include "game.h"
#include "input.h"
#include "player.h"
#include "item.h"
#include "explosion.h"
#include "score.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	ITEM_TYPE (3)//�u���b�N�̎��
#define ITEM_SIZE (50)//�A�C�e���̃T�C�Y

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureItem[ITEM_TYPE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

Item g_Item[MAX_ITEM];//�u���b�N�\����

int g_nCntItem;
int g_NumItem;//�A�C�e���̑���

//=============================================================================
// �u���b�N�̏�����
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �A�C�e���̏��̏�����
	for (g_nCntItem = 0; g_nCntItem < MAX_ITEM; g_nCntItem++)
	{
		g_Item[g_nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[g_nCntItem].nItemType = 0;
		g_Item[g_nCntItem].bUse = false; //true=�g�p���Ă��� / false=�g�p���Ă��Ȃ�
		g_Item[g_nCntItem].bTouch = false;//�G��Ă��Ȃ�

		//�A�j���[�V��������
		g_Item[g_nCntItem].SpeedAnimation = 0;
		g_Item[g_nCntItem].PatternAnimation = 0;

		g_NumItem = 0;

		 // �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\coin000.png", &g_pTextureItem[0]);	//�R�C���e�N�X�`��
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\coin000.png", &g_pTextureItem[1]);	//�R�C���e�N�X�`��
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\��B.png", &g_pTextureItem[2]);	//�R�C���e�N�X�`��

		 // ���_���̍쐬
		VERTEX_2D *pVtx;


		// ���_�o�b�t�@�𐶐�
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffItem,
			NULL);

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCB = 0; nCB < MAX_ITEM; nCB++)
		{

			//�A�C�e���̈ʒu
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//�e�N�X�`��
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

			pVtx += 4;//���_�f�[�^�̏����S���i�߂�
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
	g_NumItem = 0;
}

//=============================================================================
// �u���b�N�̏I��
//=============================================================================
void UninitItem(void)
{
	int nCntText;

	for (nCntText = 0; nCntText < ITEM_TYPE; nCntText++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureItem[nCntText] != NULL)
		{
			g_pTextureItem[nCntText]->Release();
			g_pTextureItem[nCntText] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// �u���b�N�̍X�V
//=============================================================================
void UpdateItem(void)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (g_nCntItem = 0; g_nCntItem < MAX_ITEM; g_nCntItem++)
	{
		if (g_Item[g_nCntItem].bUse == true)
		{
			g_Item[g_nCntItem].SpeedAnimation++; //�J�E���^�[�̉��Z
			if ((g_Item[g_nCntItem].SpeedAnimation % 8) == 0)
			{
				g_Item[g_nCntItem].PatternAnimation = (g_Item[g_nCntItem].PatternAnimation + 1) % 4;//�p�^�[��No.�X�V

				pVtx[0].tex = D3DXVECTOR2((g_Item[g_nCntItem].PatternAnimation*0.25f), 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_Item[g_nCntItem].PatternAnimation*0.25f) + 0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((g_Item[g_nCntItem].PatternAnimation*0.25f), 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_Item[g_nCntItem].PatternAnimation*0.25f) + 0.25f, 1.0f);
			}
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �u���b�N�̕`��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (g_nCntItem = 0; g_nCntItem < MAX_ITEM; g_nCntItem++)
	{
		if (g_Item[g_nCntItem].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItem[g_Item[g_nCntItem].nItemType]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, g_nCntItem * 4, 2);
		}
	}
}

//=============================================================================
// �u���b�N�̐ݒ�
//=============================================================================
void SetItem(D3DXVECTOR3 pos, int nItemType)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (g_nCntItem = 0; g_nCntItem < MAX_ITEM; g_nCntItem++)
	{
		if (g_Item[g_nCntItem].bUse == false)	//�u���b�N���g�p���Ă���
		{
			g_Item[g_nCntItem].pos = pos;
			g_Item[g_nCntItem].nItemType = nItemType;
			g_Item[g_nCntItem].bUse = true;

			//�A�C�e���̈ʒu
			pVtx[0].pos = D3DXVECTOR3(g_Item[g_nCntItem].pos.x, g_Item[g_nCntItem].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Item[g_nCntItem].pos.x + ITEM_SIZE, g_Item[g_nCntItem].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Item[g_nCntItem].pos.x, g_Item[g_nCntItem].pos.y + ITEM_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Item[g_nCntItem].pos.x + ITEM_SIZE, g_Item[g_nCntItem].pos.y + ITEM_SIZE, 0.0f);

			if (nItemType == 1)
			{
				//�J���[
				pVtx[0].col = D3DCOLOR_RGBA(200, 0, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(200, 0, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(200, 0, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(200, 0, 0, 255);
			}
			if (nItemType == 2)
			{
				//�J���[
				pVtx[0].col = D3DCOLOR_RGBA(200, 100, 50, 255);
				pVtx[1].col = D3DCOLOR_RGBA(200, 200, 50, 255);
				pVtx[2].col = D3DCOLOR_RGBA(200, 100, 50, 255);
				pVtx[3].col = D3DCOLOR_RGBA(200, 200, 50, 255);
			}

			if (nItemType == 0)
			{
				g_NumItem++;//�A�C�e���̑��������Z

			}
			if (nItemType == 1)
			{
				g_NumItem++;//�A�C�e���̑��������Z

			}
			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
//						�A�C�e���̓����蔻��
//=============================================================================
bool CollisionItem(D3DXVECTOR3 *pPos,		//�A�C�e���̌��݂̈ʒu
	D3DXVECTOR3 *pPosOld,	//�A�C�e���̂ЂƂO�̈ʒu
	D3DXVECTOR3 * pMove,	//�A�C�e���̈ړ���
	float fWidth,
	float fHeight)
{
	int nCntTouch;

	for (nCntTouch = 0; nCntTouch < MAX_ITEM; nCntTouch++)
	{
		if (g_Item[nCntTouch].bUse == true)//�A�C�e��������������
		{	//�����蔻��͈̔�
			if (pPos->x <= g_Item[nCntTouch].pos.x + ITEM_SIZE && pPos->x >= g_Item[nCntTouch].pos.x&&
				pPos->y <= g_Item[nCntTouch].pos.y + ITEM_SIZE*2 && pPos->y >= g_Item[nCntTouch].pos.y)//*2�����蔻��̊g��@
																										//�v���C���[��pos�������ɂ��邽��
			{
				
				if (g_Item[nCntTouch].nItemType == 2)
				{
					PlaySound(SOUND_LABEL_SE_HIT000);//�A�C�e�����莞�̉�
				}
				else
				{
					PlaySound(SOUND_LABEL_SE_COIN);//�A�C�e�����莞�̉�
				}

				if (g_Item[nCntTouch].nItemType == 2)
				{
					SetExplosion(g_Item[nCntTouch].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				AddScore(100);//�A�C�e�����莞�̃|�C���g
				if (g_Item[nCntTouch].nItemType == 1)
				{
					AddScore(400);//+���|�C���g
				}
				if (g_Item[nCntTouch].nItemType == 2)
				{
					AddScore(-600);
				}

				g_Item[nCntTouch].bUse = false;//�A�C�e����\�����Ȃ�

				if (g_Item[nCntTouch].nItemType == 0)
				{
					g_NumItem--;//�A�C�e���̑��������炷
				}
				if (g_Item[nCntTouch].nItemType == 1)
				{
					g_NumItem--;//�A�C�e���̑��������炷
				}

				if (g_NumItem <= 0)
				{//�A�C�e�������ׂď���������
					SetGameState(GAMESTATE_CLEAR);
				}
			}
		}
	}
	return g_Item[nCntTouch].bTouch;
}

//=============================================================================
// �A�C�e���̎擾
//=============================================================================
Item *GetItem(void)
{
	return &g_Item[0];
}
