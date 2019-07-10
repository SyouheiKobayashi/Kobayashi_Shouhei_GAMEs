//=============================================================================
//
// �|�[�Y���j���[���� [menu.cpp]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#include "pausemenu.h"
//#include "sound.h"
#include "fade.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PMENU_TEXTURENAME1	"data/TEXTURE/pause000.png"	// �|�[�Y�̃e�N�X�`����
#define PMENU_TEXTURENAME2	"data/TEXTURE/pause001.png"	// �|�[�Y�̃e�N�X�`����
#define PMENU_TEXTURENAME3	"data/TEXTURE/pause002.png"	// �|�[�Y�̃e�N�X�`����
#define PMENU_SIZE_X	(200.0f)		// ���j���[�̑傫��(X)
#define PMENU_SIZE_Y	(45.0f)			// ���j���[�̑傫��(Y)
#define PMENU_FLASHING	(10)			// ���j���[�̓_��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePmenu[MAX_PAUSEMENU] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPmenu = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
PAUSEMENU g_Pmenu[MAX_PAUSEMENU];
int nSelect;	// ���݂̏��
int g_nNumSelect;

//=============================================================================
// ����������
//=============================================================================
void InitPmenu(void)
{
	int nCntMenu;

	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���̏�����
	g_Pmenu[CONTINUE].pos = D3DXVECTOR3(640, 250, 0.0f);	
	g_Pmenu[RETRY].pos = D3DXVECTOR3(640, 350, 0.0f);
	g_Pmenu[QUIT].pos = D3DXVECTOR3(640, 450, 0.0f);

	g_Pmenu[CONTINUE].nType = 0;
	g_Pmenu[RETRY].nType = 1;
	g_Pmenu[QUIT].nType = 2;

	g_nNumSelect = CONTINUE;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PMENU_TEXTURENAME1, &g_pTexturePmenu[CONTINUE]);
	D3DXCreateTextureFromFile(pDevice, PMENU_TEXTURENAME2, &g_pTexturePmenu[RETRY]);
	D3DXCreateTextureFromFile(pDevice, PMENU_TEXTURENAME3, &g_pTexturePmenu[QUIT]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSEMENU,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPmenu,
		NULL);

	VERTEX_2D*pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPmenu->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMenu = 0; nCntMenu < MAX_PAUSEMENU; nCntMenu++)
	{
		// ���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_Pmenu[nCntMenu].pos.x - PMENU_SIZE_X, g_Pmenu[nCntMenu].pos.y - PMENU_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Pmenu[nCntMenu].pos.x + PMENU_SIZE_X, g_Pmenu[nCntMenu].pos.y - PMENU_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Pmenu[nCntMenu].pos.x - PMENU_SIZE_X, g_Pmenu[nCntMenu].pos.y + PMENU_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Pmenu[nCntMenu].pos.x + PMENU_SIZE_X, g_Pmenu[nCntMenu].pos.y + PMENU_SIZE_Y, 0.0f);

		// 1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	// ���_�f�[�^�̃|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPmenu->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitPmenu(void)
{
	int nCntMenu;

	for (nCntMenu = 0; nCntMenu < MAX_PAUSEMENU; nCntMenu++)
	{
		// �e�N�X�`���̔j��
		if (g_pTexturePmenu[nCntMenu] != NULL)
		{
			g_pTexturePmenu[nCntMenu]->Release();
			g_pTexturePmenu[nCntMenu] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPmenu != NULL)
	{
		g_pVtxBuffPmenu->Release();
		g_pVtxBuffPmenu = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePmenu(void)
{
	SelectPmenu();

	//PAUSECHECK *pPause;
	//pPause = GetPauseMenu();

	//if (GetKeyboardTrigger(DIK_P) == true)
	//{
	//	pPause->bPause = false;
	//}

	if (GetKeyboardRepeat(DIK_W) == true)
	{
		//PlaySound(SOUND_LABEL_SE_CURSOR);
		g_nNumSelect = (g_nNumSelect + (MAX_PAUSEMENU - 1)) % MAX_PAUSEMENU;	// �I����Ԃ��P�グ��
		SelectPmenu();
	}

	if (GetKeyboardRepeat(DIK_S) == true)
	{
		//PlaySound(SOUND_LABEL_SE_CURSOR);
		g_nNumSelect = (g_nNumSelect + 1) % MAX_PAUSEMENU;						// �I����Ԃ��P������
		SelectPmenu();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPmenu(void)
{
	int nCntMenu;

	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPmenu, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntMenu = 0; nCntMenu < MAX_PAUSEMENU; nCntMenu++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePmenu[g_Pmenu[nCntMenu].nType]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntMenu, 2);
	}
}

//=============================================================================
// �I������
//=============================================================================
void SelectPmenu(void)
{
	PAUSECHECK *pPause;
	pPause = GetPauseMenu();

	FADE pFade;
	pFade = *GetFade();

	VERTEX_2D*pVtx;	// ���_���ւ̃|�C���^

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		switch (g_nNumSelect)
		{
		case CONTINUE:
			pPause->bPause = false;
			break;

		case RETRY:
			if (pFade == FADE_NONE)
			{
				if (GetKeyboardTrigger(DIK_RETURN) == true)
				{
					SetFade(MODE_GAME);
					InitPlayer();
				}
			}
			break;

		case QUIT:
			if (pFade == FADE_NONE)
			{
				if (GetKeyboardTrigger(DIK_RETURN) == true)
				{
					SetFade(MODE_TITLE);
				}
			}
			break;
		}
	}

	if (g_nNumSelect == CONTINUE)
	{
		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPmenu->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (CONTINUE * 4);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffPmenu->Unlock();
	}
	else if (g_nNumSelect != CONTINUE)
	{
		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPmenu->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (CONTINUE * 4);

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffPmenu->Unlock();
	}

	if (g_nNumSelect == RETRY)
	{
		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPmenu->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (RETRY * 4);

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffPmenu->Unlock();
	}
	else if (g_nNumSelect != RETRY)
	{
		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPmenu->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (RETRY * 4);

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffPmenu->Unlock();
	}

	if (g_nNumSelect == QUIT)
	{
		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPmenu->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (QUIT * 4);

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffPmenu->Unlock();
	}
	else if (g_nNumSelect != QUIT)
	{
		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPmenu->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (QUIT * 4);

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffPmenu->Unlock();
	}
}

