//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "main.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PATTERN (10)
#define POS_X (0.2f * (g_nPatternAnim % 5))
#define POS_Y (0.5f * (g_nPatternAnim / 5))
#define MOVE (1.2f)

#define HALF_X (60.0f)	//X������
#define HALF_Y (60.0f)	//Y������

#define LIMIT_MIN_X (45)	//��ʒ[-X
#define LIMIT_MAX_X (1250)	//��ʒ[X
#define LIMIT_MIN_Y (25)	//��ʒ[-Y
#define LIMIT_MAX_Y (700)	//��ʒ[Y




//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//���_�o�b�t�@�ւ̃|�C���^
PLAYER g_Player;	//�v���C���[
int g_nCounterAnim;									//�A�j���[�V�����J�E���^�[
int g_nPatternAnim;									//�A�j���[�V�����p�^�[��No.
int nCoolTime;
int nWeapon_Select;	//����
int g_aaa = 0;

//=============================================================================
// �v���C���[��������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_nCounterAnim = 0;//�J�E���g�^�C�}�[��0�ɂ���
	g_nPatternAnim = 0;//�`�ʃJ�E���g��0�ɂ���
	//g_Player.pos = D3DXVECTOR3(200, 535, 0.0f);//�v���C���[���S���W
	g_Player.pos = D3DXVECTOR3(600, 535, 0.0f);//�v���C���[���S���W

	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���

	nWeapon_Select = WEAPON_VALCAN;

	g_Player.state = PLAYERSTATE_NORMAL;
	g_Player.bDisp = true;
	g_Player.nCounterState = 0;
	g_Player.nCntStamina = 0;


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/HackingCharaMotion.png", &g_pTexturePolygon);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W

	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - HALF_X, g_Player.pos.y - HALF_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + HALF_X, g_Player.pos.y - HALF_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - HALF_X, g_Player.pos.y + HALF_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + HALF_X, g_Player.pos.y + HALF_Y, 0.0f);


	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolygon->Unlock();
}
//=============================================================================
// �v���C���[��������
//=============================================================================
void UnInitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}
//=============================================================================
// �v���C���[�X�V����
//=============================================================================
void UpdatePlayer(void)
{
	int nReload = 0;
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^
	g_nCounterAnim++;			//�J�E���^�[���Z

	MODE *pMode;
	pMode = GetMode();

	switch (g_Player.state)
	{
		case PLAYERSTATE_NORMAL:
			
			// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// ���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPolygon->Unlock();
			break;

		

		case PLAYERSTATE_CHARGE:
			
			// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 0.4f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.4f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.4f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.4f, 0.0f, 1.0f);

			// ���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPolygon->Unlock();
			if (GetKeyboardRelease(DIK_RETURN) == true)
			{
				g_Player.state = PLAYERSTATE_NORMAL;
				g_Player.nCntCharge = 0;
				PlaySound(SOUND_LABEL_SE_SLASH2);


			}
			break;

		case PLAYERSTATE_TIRED:
			
			// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 0.2f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.2f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.2f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.2f, 0.0f, 1.0f);
			// ���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPolygon->Unlock();
		
			g_Player.nCounterState--;
			if (g_Player.nCounterState <= 0)
			{
				g_Player.state = PLAYERSTATE_NORMAL;
				g_Player.nCntStamina = 0;
			}
			
			break;

		
		
	}


	
	
#if 0
		//===================================================
		//�C�ӂ̃L�[(RETURN�L�[)�������ꂽ���ǂ���(�g���K�[) //
		//===================================================

	D3DXVECTOR3 PlayerSlash;

	PlayerSlash.x = g_Player.pos.x + 55;

	PlayerSlash.y = g_Player.pos.y;

	if (g_Player.bDisp == true)
	{
		if (g_Player.state == PLAYERSTATE_NORMAL)
		{
			//VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

			

			if (GetKeyboardPress(DIK_RETURN) == true)
			{

				/*g_Player.nCntStamina++;
				if (g_Player.nCntStamina > 18)
				{
					g_Player.nCounterState = 60;
					g_Player.state = PLAYERSTATE_TIRED;
				}*/

				SetBullet(PlayerSlash, D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER, 10.0f, 5);

				//g_Player.nCounterAnim++; //�J�E���^�[�̉��Z �����̑��x
				//if (g_Player.nCounterAnim % 4 == 0)
				//{
				//	g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % 8;//�p�^�[��No.�X�V
				//}



				//// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				//g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);


				//pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - 80, g_Player.pos.y - 80, 0.0f);
				//pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + 80, g_Player.pos.y - 80, 0.0f);
				//pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - 80, g_Player.pos.y + 80, 0.0f);
				//pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + 80, g_Player.pos.y + 80, 0.0f);

				//pVtx[0].tex = D3DXVECTOR2(0.125f*g_Player.nPatternAnim, 0.0f);
				//pVtx[1].tex = D3DXVECTOR2(0.125f*g_Player.nPatternAnim + 0.125f, 0.0f);
				//pVtx[2].tex = D3DXVECTOR2(0.125f*g_Player.nPatternAnim, 1.0f);
				//pVtx[3].tex = D3DXVECTOR2(0.125f*g_Player.nPatternAnim + 0.125f, 1.0f);

				//// ���_�o�b�t�@���A�����b�N����
				//g_pVtxBuffPolygon->Unlock();

				//if (g_Player.nPatternAnim > 5)
				//{
				//	PlaySound(SOUND_LABEL_SE_SLASH);
				//}

				//if (g_Player.nPatternAnim >= 8)
				//{
				//	g_Player.nPatternAnim = 0;
				//	g_Player.bDisp = false;
				//}

#endif

#if 1

				D3DXVECTOR3 PlayerSlash;

				PlayerSlash.x = g_Player.pos.x + 70;

				PlayerSlash.y = g_Player.pos.y;
					//�U�����[�V����
					//
					//	
					g_Player.state = PLAYERSTATE_A;
					if (GetKeyboardPress(DIK_RETURN) == false)
					{
						g_aaa = 0;
						g_nPatternAnim = 0;
					}
					if (GetKeyboardPress(DIK_RETURN) == true)
					{
						g_aaa++;
						g_nPatternAnim++;

						/*if (g_aaa > 5)
						{*/
							SetBullet(PlayerSlash, D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER, 20.0f, 4);
							PlaySound(SOUND_LABEL_SE_SLASH2);
						//}

						if (g_aaa > 8)
						{
							g_Player.state = PLAYERSTATE_B;
						}
					}
					switch (g_Player.state)
					{
					case PLAYERSTATE_A:
						if (GetKeyboardPress(DIK_RETURN) == true)
						{
							g_nPatternAnim = ((g_nPatternAnim)+1) % 8;//�p�^�[��No.�X�V

						}
						break;
					case PLAYERSTATE_B:
					{
						g_nPatternAnim = 0;
						break;
					}

					}




					// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
					g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
					pVtx[0].tex = D3DXVECTOR2(g_nPatternAnim*0.125f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(g_nPatternAnim*0.125f + 0.125f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(g_nPatternAnim*0.125f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(g_nPatternAnim*0.125f + 0.125f, 1.0f);
					////���_���W�̐ݒ� / �傫��
					//pVtx[0].pos = D3DXVECTOR3(-25 + g_posPlayer.x, g_posPlayer.y - 20, 0.0f);
					//pVtx[1].pos = D3DXVECTOR3(25 + g_posPlayer.x, g_posPlayer.y - 20, 0.0f);
					//pVtx[2].pos = D3DXVECTOR3(-25 + g_posPlayer.x, g_posPlayer.y + 60, 0.0f);
					//pVtx[3].pos = D3DXVECTOR3(25 + g_posPlayer.x, g_posPlayer.y + 60, 0.0f);

					////}

					//g_player.pos = g_posPlayer;
					//g_player.move = g_movePlayer;

					//���_�o�b�t�@���A�����b�N
					g_pVtxBuffPolygon->Unlock();

				}

#endif

			

		

	
				
		
	
			//=====================================================
			//�C�ӂ̃L�[(RETURN�L�[)�������ꂽ���ǂ���(�`���[�W) //
			//====================================================
			/*if (GetKeyboardPress(DIK_RETURN) == true)
			{

				g_Player.nCntCharge++;
				PlaySound(SOUND_LABEL_SE_CHARGE2);
				if (g_Player.nCntCharge >= 200)
				{
					g_Player.state = PLAYERSTATE_CHARGE;
					StopSound(SOUND_LABEL_SE_CHARGE2);
				}

			}

			if (GetKeyboardPress(DIK_RETURN) != true)
			{
				g_Player.nCntCharge = 0;
			}
		*/

			
	
////���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
//g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
//
//pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - HALF_X, g_Player.pos.y - HALF_Y, 0.0f);
//pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + HALF_X, g_Player.pos.y - HALF_Y, 0.0f);
//pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - HALF_X, g_Player.pos.y + HALF_Y, 0.0f);
//pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + HALF_X, g_Player.pos.y + HALF_Y, 0.0f);
//
//
////���_�o�b�t�@���A�����b�N����
//g_pVtxBuffPolygon->Unlock();



//=============================================================================
// �v���C���[�`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	if (g_Player.bDisp == true)
	{
	
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`��
	pDevice->SetTexture(0, g_pTexturePolygon);

	
		//�v���C���[�`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);
	}
}


//=============================================================================
// �v���C���[�̃_���[�W����
//=============================================================================
void HitPlayer(int nDamage)
{
}


//=============================================================================
// �v���C���[�̎擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}


