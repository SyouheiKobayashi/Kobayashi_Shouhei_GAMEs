//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �t�F�[�h���� [fade.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

#include "fade.h"
#include "manager.h"
#include "scene.h"
#include "input.h"


//�ÓI�����o�ϐ�
CFade::FADE CFade::m_fade = FADE_IN;
//! =============================================================================
//! �R���X�g���N�^
//! =============================================================================
CFade::CFade()
{
	//! <�l���N���A�ȏ�Ԃɂ���>
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
}
//! =============================================================================
//! �f�X�g���N�^
//! =============================================================================
CFade::~CFade()
{

}
//! =============================================================================
//! ����
//! =============================================================================
CFade *CFade::Create(void)
{
	CFade *pNumber = NULL;

	if (pNumber == NULL)
	{
		pNumber = new CFade;
		pNumber->Init();
	}
	return pNumber;
}
//! =============================================================================
//! ������
//! =============================================================================
HRESULT CFade::Init(void)
{
	//! <�����l�̐ݒ�>
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();//NULL����Ȃ�������GetDevice

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S���̈ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// �e�N�X�`���̐���
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

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}
//! =============================================================================
//! �I��
//! =============================================================================
void CFade::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}
//! =============================================================================
//! �X�V
//! =============================================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)//? �t�F�[�h�C����ԂȂ�
		{
			m_colorFade.a -= 0.02f;//�t�F�[�h�𔖂����Ă���

			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;//! 0.0f�ȏ�ɂ����Ȃ�
				m_fade = FADE_NONE;//�g�p���ĂȂ���Ԃ�
			}
		}
		
		else if (m_fade == FADE_OUT)//? �t�F�[�h�A�E�g��ԂȂ�
		{
			m_colorFade.a += 0.02f;//�t�F�[�h��Z������

			if (m_colorFade.a >= 1.0f)//��萔�l�ȏ�Ȃ�
			{
				m_colorFade.a = 1.0f;//! 1.0f�ȏ�ɂ����Ȃ�
				m_fade = FADE_IN;//�t�F�[�h�C����Ԃ�

				SetMode(m_modeNext);//�t�F�[�h�A�E�g���I������A���̃��[�h�ɕς��
			}
		}
	}

	VERTEX_2D*pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^������
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���(�J���[)�̍X�V
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}
//! =============================================================================
//!�@�`��
//! =============================================================================
void CFade::Draw(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//! =============================================================================
//! �t�F�[�h�̐ݒ菈��
//! =============================================================================
void CFade::SetFade(MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

}

