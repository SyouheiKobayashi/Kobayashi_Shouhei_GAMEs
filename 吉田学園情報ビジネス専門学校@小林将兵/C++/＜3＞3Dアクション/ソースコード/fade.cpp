//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�t�F�[�h���� [fade.cpp]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "fade.h"
#include "manager.h"
#include "scene.h"
#include "input.h"

//=====================================================================
//�ÓI�����o�ϐ�
//=====================================================================
CFade::FADE CFade::m_fade = FADE_NONE;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CFade::CFade()
{
	m_pVtxBuff = NULL;//���_�o�b�t�@�ւ̃|�C���^
}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CFade::~CFade()
{

}
//=============================================================================
//��������
//=============================================================================
CFade *CFade::Create(void)
{
	CFade *pFade = NULL;

	if (pFade == NULL)
	{
		pFade = new CFade;
		pFade->Init();
	}
	return pFade;
}
//=============================================================================
//����������
//=============================================================================
HRESULT CFade::Init(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_���̍쐬
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̈ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//�e�N�X�`���̐���
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[���
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}
//=============================================================================
//�I������
//=============================================================================
void CFade::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}


}
//=============================================================================
//�X�V����
//=============================================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)//���X�ɉ�ʂ�\������
	{
		if (m_fade == FADE_IN)
		{
			m_Color.a -= 0.02f;

			if (m_Color.a <= 0.0f)
			{
				m_Color.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}

		else if (m_fade == FADE_OUT)//���X�ɉ�ʂ��Â�����
		{
			m_Color.a += 0.02f;

			if (m_Color.a >= 1.0f)
			{
				m_Color.a = 1.0f;
				m_fade = FADE_IN;

				SetStateMode(m_NextMode);//���̃��[�h�̏���
			}
		}
	}

	VERTEX_2D*pVtx;

	 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���(�J���[)�̍X�V
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}
//=============================================================================
//�`�揈��
//=============================================================================
void CFade::Draw(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
//�ݒ�
//=============================================================================
void CFade::SetFade(STATE_MODE nextMode)
{
	m_fade = FADE_OUT;
	m_NextMode = nextMode;
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

}