//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "title.h"
#include "main.h"
#include "fade.h"
#include "sound.h"
#include "bgtitle.h"
#include "snow.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TYPE_TITLE (2)
#define TITLE_TEXTURENAME_0	"data/TEXTURE/title.png"		//�w�i�̃e�N�X�`��3
#define TITLE_TEXTURENAME_1	"data/TEXTURE/press_enter.png"		//�w�i�̃e�N�X�`��3


#define TITLE_POS_X		(400.0f)							//�w�i����X���W
#define TITLE_POS_Y		(220.0f)							//�w�i����Y���W

#define ENTER_POS_X   (200.0f)		//Enter�L�[���W
#define ENTER_POS_Y   (40.0f)		//Enter�L�[���W

#define TITLE_WIDTH		(SCREEN_WIDTH / 2)				//�w�i�̕�
#define TITLE_HEIGHT		(SCREEN_HEIGHT /2)				//�w�i�̍���
//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTitle[MAX_TYPE_TITLE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;					// ���_�o�b�t�@�ւ̃|�C���^


TITLE g_aTitle[MAX_TYPE_TITLE];

int g_nCntScene; //�����L���O�ւ̑J��
int g_nColorChange;
int LengthCounter;
bool bUseTitle;
//=============================================================================
// ����������
//=============================================================================
void InitTitle(void)
{

	//�w�i������
	InitBGTitle();

	InitSnow();


	LPDIRECT3DDEVICE9 pDevice;


	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	g_nCntScene = 0;

	LengthCounter = 3;
	
	//�^�C�g���ʒu
	g_aTitle[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 0.0f);
	g_aTitle[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 50, 520, 0.0f);

	g_aTitle[0].move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	g_aTitle[1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	g_aTitle[0].nType = 0;
	g_aTitle[1].nType = 1;



	g_aTitle[0].fHeight = 60;
	g_aTitle[0].fWidth = 80;

	

	g_aTitle[1].TitleType = TITLETYPE_NONE;
	g_aTitle[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aTitle[1].state = TITLESTATE_NONE;


	g_aTitle[0].bUse = true;
	g_aTitle[1].bUse = false;


	g_aTitle[0].fLength = sqrtf((g_aTitle[0].fWidth / 2 + g_aTitle[0].fWidth / 2) * (g_aTitle[0].fHeight / 2 + g_aTitle[0].fHeight / 2));
	g_aTitle[0].fAngle = atan2f(g_aTitle[0].fWidth / 2, g_aTitle[0].fHeight / 2);


	// �e�N�X�`���̓ǂݍ���(2�̕�)
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME_0, &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME_1, &g_pTextureTitle[1]);

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TYPE_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aTitle[0].pos.x + sinf(-D3DX_PI + g_aTitle[0].fAngle + g_aTitle[0].rot.x) * g_aTitle[0].fLength,
		g_aTitle[0].pos.y + cosf(-D3DX_PI + g_aTitle[0].fAngle + g_aTitle[0].rot.y) * g_aTitle[0].fLength,
		0.0f);


	pVtx[1].pos = D3DXVECTOR3(g_aTitle[0].pos.x + sinf(D3DX_PI - g_aTitle[0].fAngle + g_aTitle[0].rot.x) * g_aTitle[0].fLength,
		g_aTitle[0].pos.y + cosf(D3DX_PI - g_aTitle[0].fAngle + g_aTitle[0].rot.y) * g_aTitle[0].fLength,
		0.0f);


	pVtx[2].pos = D3DXVECTOR3(g_aTitle[0].pos.x + sinf(-g_aTitle[0].fAngle + g_aTitle[0].rot.x) * g_aTitle[0].fLength,
		g_aTitle[0].pos.y + cosf(-g_aTitle[0].fAngle + g_aTitle[0].rot.y) * g_aTitle[0].fLength,
		0.0f);


	pVtx[3].pos = D3DXVECTOR3(g_aTitle[0].pos.x + sinf(g_aTitle[0].fAngle + g_aTitle[0].rot.x) * g_aTitle[0].fLength,
		g_aTitle[0].pos.y + cosf(g_aTitle[0].fAngle + g_aTitle[0].rot.y) * g_aTitle[0].fLength,
		0.0f);

	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	//���_�̍��W
	pVtx[4].pos = D3DXVECTOR3(g_aTitle[1].pos.x - ENTER_POS_X, g_aTitle[1].pos.y - ENTER_POS_Y, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_aTitle[1].pos.x + ENTER_POS_X, g_aTitle[1].pos.y - ENTER_POS_Y, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_aTitle[1].pos.x - ENTER_POS_X, g_aTitle[1].pos.y + ENTER_POS_Y, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(g_aTitle[1].pos.x + ENTER_POS_X, g_aTitle[1].pos.y + ENTER_POS_Y, 0.0f);

	//1.0f�ŌŒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//���_�J���[
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);




	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	

}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	//�w�i�I��
	UninitBGTitle();

	UninitSnow();


	

	// �e�N�X�`���̊J��
	for (int nCount = 0; nCount < MAX_TYPE_TITLE; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTitle[nCount] != NULL)
		{
			g_pTextureTitle[nCount]->Release();
			g_pTextureTitle[nCount] = NULL;
		}
	}


	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	FADE pFade;
	pFade = *GetFade();

	// ���_���̍쐬
	VERTEX_2D *pVtx;


	//�w�i�X�V
	UpdateBGTitle();

	UpdateSnow();
	
	g_nCntScene++;



	if (g_nCntScene % 690 == 0)
	{
		if (pFade == FADE_NONE)
		{
			
				//���[�h�I��
				SetFade(MODE_RANKING);
			
		}
	}



	
	
	
	if (g_aTitle[1].TitleType == TITLETYPE_NONE)
	{
		switch (g_aTitle[1].state)
		{
		case TITLESTATE_NONE:
			g_aTitle[1].col.a -= 0.02f;
			if (g_aTitle[1].col.a <= 0.1f)
			{
				g_aTitle[1].col.a = 0.1f;
				g_aTitle[1].state = TITLESTATE_USE;
			}
			break;

		case TITLESTATE_USE:
			g_aTitle[1].col.a += 0.02f;
			if (g_aTitle[1].col.a >= 1.0f)
			{
				g_aTitle[1].col.a = 1.0f;
				g_aTitle[1].state = TITLESTATE_NONE;
			}
			break;
		}
	}
	else if (g_aTitle[1].TitleType == TITLETYPE_NEXT)
	{
		switch (g_aTitle[1].state)
		{
		case TITLESTATE_NONE:
			g_aTitle[1].col.r -= 0.9f;
			if (g_aTitle[1].col.r <= 0.1f)
			{
				g_aTitle[1].col.r = 0.1f;
				g_aTitle[1].state = TITLESTATE_USE;
			}
			break;

		case TITLESTATE_USE:
			g_aTitle[1].col.r += 0.9f;
			if (g_aTitle[1].col.r >= 1.0f)
			{
				g_aTitle[1].col.r = 1.0f;
				g_aTitle[1].state = TITLESTATE_NONE;
			}
			break;
		}
	}

	
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	

	if (g_aTitle[0].fLength < 420)
	{
		g_aTitle[0].fLength += LengthCounter;
		g_aTitle[0].rot.x += 0.11f;
		g_aTitle[0].rot.y += 0.11f;
		
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			

			g_aTitle[0].fLength = 420;
			//g_aTitle[0].rot.x = 0.0f;
			//g_aTitle[0].rot.y = 0.0f;

			g_aTitle[0].rot.x = +0.001f;
			g_aTitle[0].rot.y = +0.001f;
		}
		
	}
	else
	{

		g_aTitle[1].bUse = true;
		if (pFade == FADE_NONE)
		{

			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				//PlaySound(SOUND_LABEL_SE_DECIDE);
				//���[�h�I��				
				SetFade(MODE_MENU);
				g_aTitle[1].col.r = 1.0f;
				g_aTitle[1].TitleType = TITLETYPE_NEXT;
				
			}
		
			
			if (GetKeyboardTrigger(DIK_R) == true)
			{
				//PlaySound(SOUND_LABEL_SE_DECIDE);
				//���[�h�I��
				SetFade(MODE_RANKING);
			}
			if (GetKeyboardTrigger(DIK_T) == true)
			{
				//PlaySound(SOUND_LABEL_SE_DECIDE);
				//���[�h�I��
				SetFade(MODE_RESULT);
			}

			//if (GetKeyboardTrigger(DIK_Y) == true)
			//{
			//	PlaySound(SOUND_LABEL_SE_DECIDE);
			//	//���[�h�I��
			//	SetFade(MODE_TUTO);
			//}
			//if (GetKeyboardTrigger(DIK_G) == true)
			//{
			//	PlaySound(SOUND_LABEL_SE_DECIDE);
			//	//���[�h�I��
			//	SetFade(MODE_GAME);
			//}
		}
	}
	
	

		

	

	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aTitle[0].pos.x + sinf(-D3DX_PI + g_aTitle[0].fAngle + g_aTitle[0].rot.x) * g_aTitle[0].fLength,
		g_aTitle[0].pos.y + cosf(-D3DX_PI + g_aTitle[0].fAngle + g_aTitle[0].rot.y) * g_aTitle[0].fLength,
		0.0f);


	pVtx[1].pos = D3DXVECTOR3(g_aTitle[0].pos.x + sinf(D3DX_PI - g_aTitle[0].fAngle + g_aTitle[0].rot.x) * g_aTitle[0].fLength,
		g_aTitle[0].pos.y + cosf(D3DX_PI - g_aTitle[0].fAngle + g_aTitle[0].rot.y) * g_aTitle[0].fLength,
		0.0f);


	pVtx[2].pos = D3DXVECTOR3(g_aTitle[0].pos.x + sinf(-g_aTitle[0].fAngle + g_aTitle[0].rot.x) * g_aTitle[0].fLength,
		g_aTitle[0].pos.y + cosf(-g_aTitle[0].fAngle + g_aTitle[0].rot.y) * g_aTitle[0].fLength,
		0.0f);


	pVtx[3].pos = D3DXVECTOR3(g_aTitle[0].pos.x + sinf(g_aTitle[0].fAngle + g_aTitle[0].rot.x) * g_aTitle[0].fLength,
		g_aTitle[0].pos.y + cosf(g_aTitle[0].fAngle + g_aTitle[0].rot.y) * g_aTitle[0].fLength,
		0.0f);

	//���_�J���[
	pVtx[4].col = g_aTitle[1].col;
	pVtx[5].col = g_aTitle[1].col;
	pVtx[6].col = g_aTitle[1].col;
	pVtx[7].col = g_aTitle[1].col;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	//�w�i�`��
	DrawBGTitle();

	
	 DrawSnow();


	LPDIRECT3DDEVICE9 pDevice;
	// �|���S���̕`��


	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCntTitle = 0; nCntTitle < MAX_TYPE_TITLE; nCntTitle++)
	{

		if (g_aTitle[nCntTitle].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTitle[g_aTitle[nCntTitle].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
		}
	}

}


