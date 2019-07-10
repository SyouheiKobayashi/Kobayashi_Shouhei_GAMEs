//=============================================================================
// ���E�ǁA��Q�����̏��� [block.cpp]
// Author:Kobayashi/���� ����
//=============================================================================
#include "main.h"
#include "sound.h"
#include "game.h"
#include "input.h"
#include "block.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SIZE (50)//���@�̑傫��
#define	BLOCK_TYPE (7)//�u���b�N�̎��
#define UPYUKA_SPEED (-2.0f)//���X�s�[�h
#define HIDARI_SPEED (-2.0f)//���X�s�[�h

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureBlock[BLOCK_TYPE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

Block g_Block[MAX_BLOCK];//�u���b�N�\����

int g_nCntBlock;

//=============================================================================
// �u���b�N�̏�����
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �u���b�N�̏��̏�����
	for (g_nCntBlock = 0; g_nCntBlock < MAX_BLOCK; g_nCntBlock++)
	{
		g_Block[g_nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[g_nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[g_nCntBlock].fWidth = 0.0f;
		g_Block[g_nCntBlock].fHeight = 0.0f;
		g_Block[g_nCntBlock].nBlockType = 0;
		g_Block[g_nCntBlock].bUse = false; //true=�g�p���Ă��� / false=�g�p���Ă��Ȃ�
		g_Block[g_nCntBlock].Determine = false;//���n���Ă��Ȃ�


	// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\����.jpg", &g_pTextureBlock[0]);//���p�u���b�N
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\Block03��.jpg", &g_pTextureBlock[1]);//���p�u���b�N
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\Block03�c��.jpg", &g_pTextureBlock[2]);//���p�u���b�N
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\����.jpg", &g_pTextureBlock[3]);//���p�u���b�N
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\����.jpg", &g_pTextureBlock[4]);//�㉺��
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\����.jpg", &g_pTextureBlock[5]);//���ރu���b�N
		D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\����.jpg", &g_pTextureBlock[6]);//���E�ړ��u���b�N

		// ���_���̍쐬
		VERTEX_2D *pVtx;

		// ���_�o�b�t�@�𐶐�
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffBlock,
			NULL);

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

		for (g_nCntBlock = 0; g_nCntBlock < MAX_BLOCK; g_nCntBlock++)
		{

			//�u���b�N�̈ʒu
			pVtx[0].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x, g_Block[g_nCntBlock].pos.y, 0.0f);

			pVtx[1].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth, g_Block[g_nCntBlock].pos.y, 0.0f);

			pVtx[2].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x, g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight, 0.0f);

			pVtx[3].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth, g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;//���_�f�[�^�̏����S���i�߂�
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �u���b�N�̏I��
//=============================================================================
void UninitBlock(void)
{
	for (g_nCntBlock = 0; g_nCntBlock < BLOCK_TYPE; g_nCntBlock++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureBlock[g_nCntBlock] != NULL)
		{
			g_pTextureBlock[g_nCntBlock]->Release();
			g_pTextureBlock[g_nCntBlock] = NULL;
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
// �u���b�N�̍X�V
//=============================================================================
void UpdateBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();
																						   
	// ���_���̍쐬
	VERTEX_2D *pVtx;


	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
   	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (g_nCntBlock = 0; g_nCntBlock < MAX_BLOCK; g_nCntBlock++)
	{
		g_Block[g_nCntBlock].bUse = true;
		if (g_Block[g_nCntBlock].bUse == true)
		{
			g_Block[g_nCntBlock].pos += g_Block[g_nCntBlock].move;//�u���b�N�̈ړ�

			if (g_Block[g_nCntBlock].pos.y < -50)//�X�N���[���O�ɏo���ꍇ�̏���
			{
				g_Block[g_nCntBlock].pos.y = SCREEN_HEIGHT;
			}
			//if (g_Block[g_nCntBlock].pos.y > SCREEN_HEIGHT)//�X�N���[���O�ɏo���ꍇ�̏���
			//{
			//	g_Block[g_nCntBlock].pos.y = 0;
			//}
			if (g_Block[g_nCntBlock].pos.x < -150)//�X�N���[���O�ɏo���ꍇ�̏���
			{
				g_Block[g_nCntBlock].pos.x = SCREEN_WIDTH;
			}
			if (g_Block[g_nCntBlock].nBlockType == 3)//�u���b�N�̏㉺�^��
			{
				if (488 == g_Block[g_nCntBlock].pos.y)//�~�߂�
				{
					g_Block[g_nCntBlock].move.y = 0.0f;
				}
				if (500 < g_Block[g_nCntBlock].pos.y)//�㏸
				{
					g_Block[g_nCntBlock].move.y = UPYUKA_SPEED;
				}
			}
			if (g_Block[g_nCntBlock].nBlockType == 4)//�u���b�N�̏㉺�^��
			{
				if (170 > g_Block[g_nCntBlock].pos.y)//���~
				{
					g_Block[g_nCntBlock].move.y = 2.0f;
				}
				if (340 < g_Block[g_nCntBlock].pos.y)//�㏸
				{
					g_Block[g_nCntBlock].move.y = UPYUKA_SPEED - 1.0f;
				}
			}
			if (g_Block[g_nCntBlock].nBlockType == 5)//�u���b�N�̏㉺�^��
			{
				if (670 == g_Block[g_nCntBlock].pos.y)//�~�߂�
				{
					g_Block[g_nCntBlock].move.y = 0.0f;
				}
				if (800 < g_Block[g_nCntBlock].pos.y)//�㏸
				{
					g_Block[g_nCntBlock].move.y = UPYUKA_SPEED;
				}
			}

			if (g_Block[g_nCntBlock].nBlockType == 6)//�u���b�N�̍��E�^��
			{
				if (850 > g_Block[g_nCntBlock].pos.x)//��
				{
					g_Block[g_nCntBlock].move.x = -HIDARI_SPEED;
				}
				if (950 < g_Block[g_nCntBlock].pos.x)//�E
				{
					g_Block[g_nCntBlock].move.x = HIDARI_SPEED;
				}
			}

			//�u���b�N�̈ʒu
			pVtx[0].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x, g_Block[g_nCntBlock].pos.y, 0.0f);

			pVtx[1].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth, g_Block[g_nCntBlock].pos.y, 0.0f);

			pVtx[2].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x, g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight, 0.0f);

			pVtx[3].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth, g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		}
		pVtx += 4;//���_�f�[�^�̏����S���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �u���b�N�̕`��
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(int g_nCntBlock = 0; g_nCntBlock < MAX_BLOCK; g_nCntBlock++)
	{
		if (g_Block[g_nCntBlock].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock[g_Block[g_nCntBlock].nBlockType]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, g_nCntBlock*4, 2);
		}
	}
}

//=============================================================================
// �u���b�N�̐ݒ�
//=============================================================================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, int nBlockType)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (g_nCntBlock = 0; g_nCntBlock < MAX_BLOCK; g_nCntBlock++)
	{
		if (g_Block[g_nCntBlock].bUse == false)	//�u���b�N���g�p���Ă���
		{
			g_Block[g_nCntBlock].pos = pos;
			g_Block[g_nCntBlock].move = move;
			g_Block[g_nCntBlock].fWidth = fWidth;
			g_Block[g_nCntBlock].fHeight = fHeight;
			g_Block[g_nCntBlock].nBlockType = nBlockType;
			g_Block[g_nCntBlock].bUse = true;

			//�u���b�N�̈ʒu
			pVtx[0].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x, g_Block[g_nCntBlock].pos.y, 0.0f);

			pVtx[1].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth, g_Block[g_nCntBlock].pos.y, 0.0f);

			pVtx[2].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x, g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight, 0.0f);

			pVtx[3].pos = D3DXVECTOR3(g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth, g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight, 0.0f);

			break;
		}
		pVtx += 4;
		
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �u���b�N�̏Փ˔���
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos,		//���@�̌��݂̈ʒu
					D3DXVECTOR3 *pPosOld,	//���@�̂ЂƂO�̈ʒu
					D3DXVECTOR3 * pMove,	//���@�̈ړ���
					float fWidth,
					float fHeight)	
{
	bool bLand = false; //���n���Ă��Ȃ�

	/*if (g_Block[g_nCntBlock].nBlockType == 0)//�����^�C�v�O�Ȃ�c���蔲���\�Ȃ�
	{
	}*/

	for (g_nCntBlock = 0; g_nCntBlock < MAX_BLOCK; g_nCntBlock++)
	{
		if (g_Block[g_nCntBlock].bUse == true)//�u���b�N���g���Ă���
		{
			g_Block[g_nCntBlock].Determine = false;//�P��̃u���b�N�̔�������ɖ߂� / ����������
			//�u���b�N / �n�ʔ��菈�� / ��Ɖ�
			if (pPos->x <= g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth && pPos->x >= g_Block[g_nCntBlock].pos.x)
			{
				//���ォ��̏Փ˔���
				if (pPosOld->y <= g_Block[g_nCntBlock].pos.y&&pPos->y >= g_Block[g_nCntBlock].pos.y)
				{	
					//*pPos->y += g_Block[g_nCntBlock].pos.y;
					
					g_Block[g_nCntBlock].Determine = true;
					bLand = true;//�n�� / �u���b�N�ɂ߂荞�񂾂�
					pPos->y = g_Block[g_nCntBlock].pos.y; //�����������n�ʂ̏�
					pMove->y = 0.0f;// �������x���Ȃ��� / �}�C�i�X���l�ɂ���Ǝ����W�����v�I�ȉ���

					//���c�ړ��p
					if (g_Block[g_nCntBlock].nBlockType == 4&& g_Block[g_nCntBlock].move.y == UPYUKA_SPEED - 1.0f)//�㏸���ɓK��
					{
						pPos->y = g_Block[g_nCntBlock].pos.y+ UPYUKA_SPEED - 1.0f;//�����������n�ʂ̏�
					}

					if (g_Block[g_nCntBlock].nBlockType == 5 && g_Block[g_nCntBlock].move.y == UPYUKA_SPEED)//�㏸���ɓK��
					{
						pPos->y = g_Block[g_nCntBlock].pos.y + UPYUKA_SPEED;//�����������n�ʂ̏�
					}
					//if (g_Block[g_nCntBlock].nBlockType == 5 && g_Block[g_nCntBlock].move.y == 3.0f)//�㏸���ɓK��
					//{
					//	pPos->y = g_Block[g_nCntBlock].pos.y +13.0f;//�����������n�ʂ̏�
					//}
					//if (g_Block[g_nCntBlock].move.y = 0.7f)
					//{
					//	pPos->y = g_Block[g_nCntBlock].pos.y - 0.7f;//!!���@���u���b�N�ɏ��Əd���ŉ�����
					//}
					//���@���u���b�N�̏�ɏ������u���b�N��������
					if (g_Block[g_nCntBlock].nBlockType == 3)//�u���b�N�̏㉺�^��
					{
						g_Block[g_nCntBlock].move.y = 2.0f;
						pPos->y = g_Block[g_nCntBlock].pos.y;//!!���@���u���b�N�ɏ��Ɨ�����
					}
					if (g_Block[g_nCntBlock].nBlockType == 5)//�u���b�N�̏㉺�^��
					{
						g_Block[g_nCntBlock].move.y = 2.0f;
						pPos->y = g_Block[g_nCntBlock].pos.y;//!!���@���u���b�N�ɏ��Ɨ�����
					}
					
					//�����ړ��p
					if (g_Block[g_nCntBlock].nBlockType == 6)
					{
						pPos->x += g_Block[g_nCntBlock].move.x;//��Q�����ړ����������@�ɑ��
					}

				 //���C�ӂ̃L�[(S�L�[)�������ꂽ���ǂ��� / ���@�̉��ړ��H�̏�����
					//if (GetKeyboardPress(DIK_S) == true)
					//{
					//	//g_Block[g_nCntBlock].bUse = false;//���h��������
					//	pPos->y = g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight * 2 + 10; //�����������n�ʂ̉�
					//}
				}

				//��������̏Փ˔���
				else if (pPosOld->y - PLAYER_SIZE >= g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight
					&& pPos->y - PLAYER_SIZE <= g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight)
				{
					g_Block[g_nCntBlock].Determine = true;
					//bLand = true;//�n�� / �u���b�N�ɂ߂荞�񂾂�
					//�u���b�N�̍���*2+���������l
					pPos->y= g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight*3; //�����������n�ʂ̉�
					pMove->y = 0.0f; // �������x���Ȃ���
				}

				//�u���b�N / �����菈��
				if (pPos->y <= g_Block[g_nCntBlock].pos.y+ PLAYER_SIZE * 1.5f + g_Block[g_nCntBlock].fHeight && pPos->y >= g_Block[g_nCntBlock].pos.y)
				{
					if (g_Block[g_nCntBlock].Determine == false)//�u���b�N�ɏ���Ă��牡����
					{
							//��������̏Փ˔���
							if (pPosOld->x <= g_Block[g_nCntBlock].pos.x && pPos->x >= g_Block[g_nCntBlock].pos.x)
							{
								bLand = true;//�n�� / �u���b�N�ɂ߂荞�񂾂�
								pPos->x = pPosOld->x; //��Q���ɂ߂荞�񂾏ꍇ�̏���
								pMove->x = -1.0f; // ���x���Ȃ���
							}

							if (g_Block[g_nCntBlock].nBlockType == 6)//�ړ����̓����蔻��
							{//�ړ�����u���b�N���A�ߋ��̎��@�̋��ꏊ(�����ꏊ)�𑫂��Ă���
								if (pPosOld->x + HIDARI_SPEED <= g_Block[g_nCntBlock].pos.x && pPos->x >= g_Block[g_nCntBlock].pos.x)
								{
									bLand = true;//�n�� / �u���b�N�ɂ߂荞�񂾂�
									pPos->x = pPosOld->x; //��Q���ɂ߂荞�񂾏ꍇ�̏���
									pMove->x = -1.0f; // ���x���Ȃ���
								}
							}

							//���E����̏Փ˔��� / ���@�̑傫���Q�{��	
							else if (pPosOld->x >= g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth && pPos->x <= g_Block[g_nCntBlock].pos.x + g_Block[g_nCntBlock].fWidth)
							{
								bLand = true;//�n�� / �u���b�N�ɂ߂荞�񂾂�
								pPos->x = pPosOld->x; //��Q���ɂ߂荞�񂾏ꍇ�̏���
								pMove->x = 1.0f; // ���x���Ȃ���
							}
					}
				}

				//���u���b�N / ������̏���
#if 0
				if (bLand == false)//���n���Ă��Ȃ� / �󒆂ɂ���
				{
					if (pPos->y >= g_Block[g_nCntBlock].pos.y && pPos->y - PLAYER_SIZE * 2 <= g_Block[g_nCntBlock].pos.y + g_Block[g_nCntBlock].fHeight)
					{
						bLand = true;//�n�� / �u���b�N�ɂ߂荞�񂾂� / �g���ƃ��b�N�}���d�l
						pPos->x = pPosOld->x; //��Q���ɂ߂荞�񂾏ꍇ�̏���
						pMove->x = 0.0f; // ���x���Ȃ���
					}
				}
#endif
			}
		}
	}
	return bLand;
}

//=============================================================================
// �u���b�N�̎擾
//=============================================================================
Block *GetBlock(void)
{
	return &g_Block[0];
}
