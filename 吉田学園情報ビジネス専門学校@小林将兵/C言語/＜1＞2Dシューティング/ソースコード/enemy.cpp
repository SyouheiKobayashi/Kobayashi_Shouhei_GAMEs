//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//? �G���� [enemy.cpp]
//? Author :���� / Kobayshi
//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "enemy.h"
#include "explosion.h"
#include "bullet.h"
#include "game.h"
#include "score.h"
#include "player.h"
#include "sound.h"
//? ==================================================
//? �O���[�o���ϐ��錾
//? ==================================================
LPDIRECT3DTEXTURE9		g_apTextureEnemy[ENEMY_TYPE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
ENEMY g_aEnemy[ENEMY_MAX];										//�G�̏��
MOVE g_move;
int g_nNumEnemy;//�G�̑���
int g_nCountAnimE; //�A�j���[�V�����J�E���^�[
int g_nPatternAnimE;//�A�j���[�V�����p�^�[��No.
//? ==================================================
//? ����������
//? ==================================================
void InitEnemy(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	g_nCountAnimE = 0;
	g_nPatternAnimE = 0;
	g_nNumEnemy = 0;
	g_move = MOVE_R;
	// �G�̏��̏�����
	for(int nCntEnemy = 0; nCntEnemy < ENEMY_MAX; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 1;
		g_aEnemy[nCntEnemy].bUse = false;
		
	}

	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\ENEMY\\enemy100.png", &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\ENEMY\\enemy101.png", &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\ENEMY\\enemy102.png", &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, "DATA\\TEXTURE\\ENEMY\\enemy103.png", &g_apTextureEnemy[3]);

	// ���_���̍쐬
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * ENEMY_MAX,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(int nCntEnemy = 0; nCntEnemy < ENEMY_MAX; nCntEnemy++)
	{
		////���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);


		pVtx += 4;//���_�f�[�^�̏����S���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
	//g_nNumEnemy = 0;//�G�̑������N���A
}

//? ==================================================
//? �I������
//? ==================================================
void UninitEnemy(void)
{
	// �e�N�X�`���̊J��
	for(int nCntTex = 0; nCntTex < ENEMY_TYPE; nCntTex++)
	{
		// �e�N�X�`���̊J��
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//? ==================================================
//? �X�V����
//? ==================================================
void UpdateEnemy(void)
{
	float nKakudo;//�p�x�̕ϐ�
	PLAYER *pPlayer;
	pPlayer = GetPlayer();//�v���C���[���̎擾

	

	// ���_���̍쐬
	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL://�ʏ펞�̏���
				g_aEnemy[nCntEnemy].nCounterState++;
				if (g_aEnemy[nCntEnemy].nCounterState % ENEMY_INTERVAL == 0)
				{
					//�v���C���[�̈ʒu�Ɍ����Ĕ���
					nKakudo = atan2f(pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(nKakudo)*6.0f, cosf(nKakudo)*6.0f, 0.0f), BULLETTYPE_ENEMY);
				}
				break;

			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;//�ʏ�̏�Ԃɖ߂�

					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				break;
			}
		}
			switch (g_move)
			{
			case MOVE_R:
				g_aEnemy[nCntEnemy].move.x = 5.0f;
				g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
				if (g_aEnemy[nCntEnemy].pos.x == SCREEN_WIDTH-60)
				{
					g_move = MOVE_L;
				}
				break;

			case MOVE_L:

				g_aEnemy[nCntEnemy].move.x = 5.0f;
				g_aEnemy[nCntEnemy].pos.x -= g_aEnemy[nCntEnemy].move.x;
				if (-160 == g_aEnemy[nCntEnemy].pos.x)
				{
					g_move = MOVE_R;
				}

				break;
			}

		pVtx[0].pos = D3DXVECTOR3(-ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.x, -ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.x, -ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.x, +ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.x, +ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.y, 0.0f);

		//!+ <�G�l�~�[�̃A�j���[�V����>
		g_aEnemy[nCntEnemy].nCountAnimE++; 
		if ((g_aEnemy[nCntEnemy].nCountAnimE % 20) == 0)
		{
			g_aEnemy[nCntEnemy].nPatternAnimE = (g_aEnemy[nCntEnemy].nPatternAnimE + 1) % 2;

			pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aEnemy[nCntEnemy].nPatternAnimE*0.5f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f + (g_aEnemy[nCntEnemy].nPatternAnimE*0.5f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aEnemy[nCntEnemy].nPatternAnimE*0.5f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f + (g_aEnemy[nCntEnemy].nPatternAnimE*0.5f), 1.0f);
		}


		pVtx += 4;

	}
	g_pVtxBuffEnemy->Unlock();
}

//? ==================================================
//? �`�揈��
//? ==================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(int nCntEnemy = 0; nCntEnemy < ENEMY_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//? ==================================================
//? �G�̐ݒ�
//? ==================================================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < ENEMY_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)	//�G���g�p����Ă��Ȃ�
		{
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nLife = 5;
			g_aEnemy[nCntEnemy].bUse = true;


			//���_���W�̐ݒ� / �傫��
			pVtx[0].pos = D3DXVECTOR3(-ENEMY_SIZE+ g_aEnemy[nCntEnemy].pos.x,  - ENEMY_SIZE+ g_aEnemy[nCntEnemy].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.x,  - ENEMY_SIZE+ g_aEnemy[nCntEnemy].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.x,  + ENEMY_SIZE+ g_aEnemy[nCntEnemy].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(ENEMY_SIZE + g_aEnemy[nCntEnemy].pos.x,  + ENEMY_SIZE+ g_aEnemy[nCntEnemy].pos.y, 0.0f);

			g_nNumEnemy++;//�G�̑��������Z

			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//? ==================================================
//? �G�̒ʏ�A�_���[�W���̕\������
//? ==================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)	//�̗͂�0�ȉ��ɂȂ����ꍇ
	{
		//[�G�����j�������̔����̐���]
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_aEnemy[nCntEnemy].bUse = false;

		PlaySound(SOUND_EXPLOSION);
 		AddScore(1000);//�X�R�A
		g_nNumEnemy--;//�G�̑������炷

		if (g_nNumEnemy <= 0)//�N���A����
		{
			SetGameState(GAMESTATE_END);
		}
	}
	else//�̗͂��]���Ă�ꍇ�̏���
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;//��e��
		g_aEnemy[nCntEnemy].nCounterState = 5;//�_���[�W�\���̎���

		//���_�J���[�̐ݒ�
		VERTEX_2D *pVtx;
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += (nCntEnemy * 4);
		//��e���̃J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		g_pVtxBuffEnemy->Unlock();
	}
}
//? ==================================================
//? �G�̎擾
//? ==================================================
ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}
