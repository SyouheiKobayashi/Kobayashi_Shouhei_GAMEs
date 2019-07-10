//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//? �|�[�Y����
//? Kobayashi / ����
//? ���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "pause.h"
#include "game.h"

//? ==================================================
//? �}�N����`
//? ==================================================
#define PAUSE_TEXTURENAME "DATA\\TEXTURE\\pause00.png" //�ǂݍ��ރe�N�X�`��
#define PAUSE_POS_X (0)						 //�w�i�̍���X���W
#define PAUSE_POS_Y (0)						 //�w�i�̍���Y���W
#define PAUSE_WIDTH (SCREEN_WIDTH)				 //�w�i�̕�
#define PAUSE_HEIGHT (SCREEN_HEIGHT)			 //�w�i�̍���

//? ==================================================
//? �O���[�o���ϐ�
//? ==================================================
LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;


//? ==================================================
//? ������
//? ==================================================
#if 1
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURENAME, &g_pTexturePause);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

				   //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PAUSE_POS_X + PAUSE_WIDTH, PAUSE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y + PAUSE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PAUSE_POS_X + PAUSE_WIDTH, PAUSE_POS_Y + PAUSE_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();
}
#endif
//? ==================================================
//? �I��
//? ==================================================
#if 1
void UninitPause(void)
{
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}
#endif
//? ==================================================
//? �X�V
//? ==================================================
#if 1
void UpdataPause(void)
{

}
#endif
//? ==================================================
//? �`��
//? ==================================================
#if 1
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X����������
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePause);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
#endif