//=============================================================================
//
// �X�e�[�^�X�o�[���� [statusbar.cpp]
// Author : komatsu keisuke
//
//=============================================================================
#include "statusbar.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define STATUSBAR_TEXTURENAME	"data/TEXTURE/bg001.png"	//�\������t�@�C���̖��O
#define MAX_TEXTURE			(1)								//�ǂݍ��ރe�N�X�`���̐�
#define TEX_X				(1.0f)							//�e�N�X�`����X
#define TEX_Y				(1.0f)							//�e�N�X�`����Y

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureStatusBar[MAX_TEXTURE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStatusBar = NULL;			//���_�o�b�t�@�ւ̃|�C���^

//=============================================================================
// �|���S������������
//=============================================================================
void InitStatusBar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, STATUSBAR_TEXTURENAME, &g_pTextureStatusBar[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffStatusBar,
								NULL);
	//���_�o�b�t�@�ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffStatusBar->Lock(0, 0, (void**)&pVtx, 0);

	//�X�e�[�^�X�o�[
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 100.0f, 0.0f);

	//rwhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TEX_X, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TEX_Y);
	pVtx[3].tex = D3DXVECTOR2(TEX_X, TEX_Y);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffStatusBar->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitStatusBar(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureStatusBar[nCntTex] != NULL)
		{
			g_pTextureStatusBar[nCntTex]->Release();
			g_pTextureStatusBar[nCntTex] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffStatusBar != NULL)
	{
		g_pVtxBuffStatusBar->Release();
		g_pVtxBuffStatusBar = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStatusBar(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStatusBar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X���擾

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStatusBar, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureStatusBar[nCntTex]);
	
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTex * 4, 2);
	}
}