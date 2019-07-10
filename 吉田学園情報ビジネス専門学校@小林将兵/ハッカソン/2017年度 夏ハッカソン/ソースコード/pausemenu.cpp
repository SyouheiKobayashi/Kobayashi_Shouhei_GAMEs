//************************************************************************************************************************
//
// �|�[�Y���j���[���� [PauseMenu.cpp]
// Author : Kishida Rei
//
//************************************************************************************************************************
#include "pausemenu.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************************************************************************************************************
// �}�N����`
//*****************************************************************************************************************************************************************************
#define	MAX_TYPE_PAUSEMENU		(3)								// �L�[�̎��
#define PAUSEMENU_TEXTURENAME_0	"data/TEXTURE/pause000.png"		//�L�[�̃e�N�X�`��1
#define PAUSEMENU_TEXTURENAME_1	"data/TEXTURE/pause001.png"		//�L�[�̃e�N�X�`��2
#define PAUSEMENU_TEXTURENAME_2	"data/TEXTURE/pause002.png"		//�L�[�̃e�N�X�`��3




#define PAUSEMENU_POS_X		(200.0f)							//�w�i����X���W
#define PAUSEMENU_POS_Y		(45.0f)							//�w�i����Y���W


#define MENU_CONTINUE (0)		//�R���e�B�j���[
#define MENU_RETRY (1)		//���g���C
#define MENU_QUIT (2)		//modori



//*****************************************************************************************************************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_apTexturePauseMenu[MAX_TYPE_PAUSEMENU] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseMenu = NULL;					// ���_�o�b�t�@�ւ̃|�C���^

PAUSEMENU g_aPauseMenu[MAX_TYPE_PAUSEMENU];
int g_nNowSelect;    //���݂̑I�����
//************************************************************************************************************************
// ����������
//************************************************************************************************************************
void InitPauseMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPauseMenu;	//�L�[�̃J�E���g

						// �f�o�C�X�̎擾
	pDevice = GetDevice();


	g_nNowSelect = CONTINUE;
	
		g_aPauseMenu[CONTINUE].pos = D3DXVECTOR3(640, 250, 0);
		g_aPauseMenu[RETRY].pos = D3DXVECTOR3(640, 350, 0);
		g_aPauseMenu[QUIT].pos = D3DXVECTOR3(640, 450, 0);

		g_aPauseMenu[CONTINUE].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		g_aPauseMenu[RETRY].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		g_aPauseMenu[QUIT].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

		g_aPauseMenu[CONTINUE].nType = 0;
		g_aPauseMenu[RETRY].nType = 1;
		g_aPauseMenu[QUIT].nType = 2;


		g_aPauseMenu[CONTINUE].state = PAUSEMENUSTATE_NORMAL;
		g_aPauseMenu[RETRY].state = PAUSEMENUSTATE_NORMAL;
		g_aPauseMenu[QUIT].state = PAUSEMENUSTATE_NORMAL;

		g_aPauseMenu[CONTINUE].uState = PAUSEMENUSTATE_NONE;
		g_aPauseMenu[RETRY].uState = PAUSEMENUSTATE_NONE;
		g_aPauseMenu[QUIT].uState = PAUSEMENUSTATE_NONE;

	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	D3DXCreateTextureFromFile(pDevice, PAUSEMENU_TEXTURENAME_0, &g_apTexturePauseMenu[MENU_CONTINUE]);
	D3DXCreateTextureFromFile(pDevice, PAUSEMENU_TEXTURENAME_1, &g_apTexturePauseMenu[MENU_RETRY]);
	D3DXCreateTextureFromFile(pDevice, PAUSEMENU_TEXTURENAME_2, &g_apTexturePauseMenu[MENU_QUIT]);




	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TYPE_PAUSEMENU,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseMenu,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPauseMenu = 0; nCntPauseMenu < MAX_TYPE_PAUSEMENU; nCntPauseMenu++)
	{
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aPauseMenu[nCntPauseMenu].pos.x - PAUSEMENU_POS_X, g_aPauseMenu[nCntPauseMenu].pos.y - PAUSEMENU_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPauseMenu[nCntPauseMenu].pos.x + PAUSEMENU_POS_X, g_aPauseMenu[nCntPauseMenu].pos.y - PAUSEMENU_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPauseMenu[nCntPauseMenu].pos.x - PAUSEMENU_POS_X, g_aPauseMenu[nCntPauseMenu].pos.y + PAUSEMENU_POS_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPauseMenu[nCntPauseMenu].pos.x + PAUSEMENU_POS_X, g_aPauseMenu[nCntPauseMenu].pos.y + PAUSEMENU_POS_Y, 0.0f);

		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
		
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseMenu->Unlock();
}

//************************************************************************************************************************
// �I������
//************************************************************************************************************************
void UnInitPauseMenu(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_TYPE_PAUSEMENU; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (g_apTexturePauseMenu[nCntTex] != NULL)
		{
			g_apTexturePauseMenu[nCntTex]->Release();
			g_apTexturePauseMenu[nCntTex] = NULL;
		}
	}


	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPauseMenu != NULL)
	{
		g_pVtxBuffPauseMenu->Release();
		g_pVtxBuffPauseMenu = NULL;
	}
}

//************************************************************************************************************************
// �X�V����
//************************************************************************************************************************
void UpdatePauseMenu(void)
{
	//g_nNowSelect = CONTINUE;
	PAUSECHECK *pPause;
	pPause = GetPauseCheck();

	FADE pFade;
	pFade = *GetFade();



	PushPauseMenu();

	VERTEX_2D *pVtx;
			


	if (g_aPauseMenu[g_nNowSelect].state == PAUSEMENUSTATE_SELECT)
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);
		switch (g_aPauseMenu[g_nNowSelect].uState)
		{
		case PAUSEMENUSTATE_NONE:
			g_aPauseMenu[g_nNowSelect].col.a -= 0.02f;
			if (g_aPauseMenu[g_nNowSelect].col.a <= 0.0f)
			{
				g_aPauseMenu[g_nNowSelect].col.a = 0.0f;
				g_aPauseMenu[g_nNowSelect].uState = PAUSEMENUSTATE_USE;
			}
			break;

		case PAUSEMENUSTATE_USE:
			g_aPauseMenu[g_nNowSelect].col.a += 0.02f;
			if (g_aPauseMenu[g_nNowSelect].col.a >= 1.0f)
			{
				g_aPauseMenu[g_nNowSelect].col.a = 1.0f;
				g_aPauseMenu[g_nNowSelect].uState = PAUSEMENUSTATE_NONE;
			}
			break;
		}
		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPauseMenu->Unlock();
	}







	
			if (GetKeyboardTrigger(DIK_W) == true)
			{//W�L�[
				PlaySound(SOUND_LABEL_SE_SELECT);
				g_nNowSelect = (g_nNowSelect + (MAX_MENU - 1)) % MAX_MENU;//�I����Ԃ���グ��
				//PushPauseMenu();
				
			}


			else if (GetKeyboardTrigger(DIK_S) == true)
			{//S�L�[
				PlaySound(SOUND_LABEL_SE_SELECT);
				g_nNowSelect = (g_nNowSelect + 1 ) % MAX_MENU;//�I����Ԃ��������
				//PushPauseMenu();
				
			}

			else if (GetKeyboardTrigger(DIK_RETURN) == true)
			{//RETURN�L�[
				//PushPauseMenu();
				switch (g_nNowSelect)
				{//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
				case CONTINUE://�Q�[���I�𒆂Ȃ�
					pPause->bPause = false;
					break;


				case RETRY://�ݒ�I�𒆂Ȃ�
					if (pFade == FADE_NONE)
					{
						if (GetKeyboardTrigger(DIK_RETURN) == true)
						{
							PlaySound(SOUND_LABEL_SE_DECIDE);
							SetFade(MODE_GAME);
						}
					}
					break;

				case QUIT://�ݒ�I�𒆂Ȃ�
					if (pFade == FADE_NONE)
					{
						if (GetKeyboardTrigger(DIK_RETURN) == true)
						{
							PlaySound(SOUND_LABEL_SE_DECIDE);
							SetFade(MODE_TITLE);
						}
					}
					break;
				}
			}







			if (g_nNowSelect == CONTINUE)
			{//�I����
				g_aPauseMenu[CONTINUE].state = PAUSEMENUSTATE_SELECT;
				// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (CONTINUE * 4);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffPauseMenu->Unlock();
			}
			if (g_nNowSelect != CONTINUE)
			{//�ʏ펞
				g_aPauseMenu[CONTINUE].state = PAUSEMENUSTATE_NORMAL;

				// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (CONTINUE * 4);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffPauseMenu->Unlock();
			}


			if (g_nNowSelect == RETRY)
			{//�I����
				g_aPauseMenu[RETRY].state = PAUSEMENUSTATE_SELECT;

				// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (RETRY * 4);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffPauseMenu->Unlock();
			}
			if (g_nNowSelect != RETRY)
			{//�ʏ펞
				g_aPauseMenu[RETRY].state = PAUSEMENUSTATE_NORMAL;

				// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (RETRY * 4);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffPauseMenu->Unlock();
			}

			if (g_nNowSelect == QUIT)
			{//�I����
			 // ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (QUIT * 4);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffPauseMenu->Unlock();
			}
			if (g_nNowSelect != QUIT)
			{//�ʏ펞
			 // ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (QUIT * 4);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffPauseMenu->Unlock();
			}


			if (g_aPauseMenu[g_nNowSelect].state == PAUSEMENUSTATE_SELECT)
			{
				// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);
				switch (g_aPauseMenu[g_nNowSelect].uState)
				{
				case PAUSEMENUSTATE_NONE:
					g_aPauseMenu[g_nNowSelect].col.a -= 0.02f;
					if (g_aPauseMenu[g_nNowSelect].col.a <= 0.0f)
					{
						g_aPauseMenu[g_nNowSelect].col.a = 0.0f;
						g_aPauseMenu[g_nNowSelect].uState = PAUSEMENUSTATE_USE;
					}
					break;

				case PAUSEMENUSTATE_USE:
					g_aPauseMenu[g_nNowSelect].col.a += 0.02f;
					if (g_aPauseMenu[g_nNowSelect].col.a >= 1.0f)
					{
						g_aPauseMenu[g_nNowSelect].col.a = 1.0f;
						g_aPauseMenu[g_nNowSelect].uState = PAUSEMENUSTATE_NONE;
					}
					break;
				}
				// ���_�o�b�t�@���A�����b�N����
				g_pVtxBuffPauseMenu->Unlock();
			}



}
	

//************************************************************************************************************************
// �`�揈��
//************************************************************************************************************************
void DrawPauseMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	// �|���S���̕`��

			// �f�o�C�X�̎擾
			pDevice = GetDevice();

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffPauseMenu, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCntPauseMenu = 0; nCntPauseMenu < MAX_TYPE_PAUSEMENU; nCntPauseMenu++)
	{
		

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTexturePauseMenu[g_aPauseMenu[nCntPauseMenu].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPauseMenu * 4, 2);
		}
	

}


//************************************************************************************************************************
// �L�[����
//************************************************************************************************************************
//void PushPauseMenu(int nCntPauseMenu)
void PushPauseMenu(void)
{
	PAUSECHECK *pPause;
	pPause = GetPauseCheck();

	FADE pFade;
	pFade = *GetFade();

	//VERTEX_2D *pVtx;




	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//�G���^�[�L�[�������ꂽ��

		switch (g_nNowSelect)
		{//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
		case CONTINUE://�Q�[���I�𒆂Ȃ�
			pPause->bPause = false;
			break;


		case RETRY://�ݒ�I�𒆂Ȃ�
			if (pFade == FADE_NONE)
			{
				if (GetKeyboardTrigger(DIK_RETURN) == true)
				{
					PlaySound(SOUND_LABEL_SE_DECIDE);
					SetFade(MODE_GAME);
				}
			}
			break;

		case QUIT://�ݒ�I�𒆂Ȃ�
			if (pFade == FADE_NONE)
			{
				if (GetKeyboardTrigger(DIK_RETURN) == true)
				{
					PlaySound(SOUND_LABEL_SE_DECIDE);
					SetFade(MODE_TITLE);
				}
			}
			break;
		}
	}
}
	
	
		
	
	
	
//************************************************************************************************************************
// �L�[�摜�̐ݒ�
//************************************************************************************************************************
void SetPauseMenu(D3DXVECTOR3 pos, int nType)
{
	
}


//************************************************************************************************************************
// �L�[�̎擾
//************************************************************************************************************************
PAUSEMENU *GetPauseMenu(void)
{
	return &g_aPauseMenu[0];
}





