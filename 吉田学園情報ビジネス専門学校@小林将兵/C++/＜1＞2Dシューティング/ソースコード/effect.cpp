//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �����G�t�F�N�g���� [effect.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "effect.h"

//�}�N��
//�ǂݍ��ރe�N�X�`����
#define TEXTURE_NAME01	("DATA\\effect000.jpg")
//�G�t�F�N�g�̃T�C�Y��
#define B_SIZE_H	(40.0f)//�c�T�C�Y
#define B_SIZE_W	(80.0f)//���T�C�Y
//�G�t�F�N�g�̃A�j���[�V�����ݒ聫
#define	EX_ANIM_SPEED	(5)//�A�j���[�V��������
#define	EX_ANIM_W	(8)//������
#define	EX_ANIM_H	(1)//�c����

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;
//! =============================================================================
//! �R���X�g���N�^
//! =============================================================================
CEffect::CEffect():CScene2D(OBJ_DRAW::DRAW_EFFECT)
{
	
	m_fRadius = 0;			// ���a(�傫��)
	m_nLife = 0;				// �\������(����)
}

//! =============================================================================
//! �f�X�g���N�^
//! =============================================================================
CEffect::~CEffect()
{

}

//! =============================================================================
//! Tex�ǂݍ���
//! =============================================================================
HRESULT CEffect::Load(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture);

	return S_OK;
}
//! =============================================================================
//! Tex�j��
//! =============================================================================
void CEffect::UnLoad(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//! =============================================================================
//! ����
//! =============================================================================
#if 1
CEffect *CEffect::Create(D3DXVECTOR3 pos,D3DXCOLOR col)
{

	CEffect *pEffect = NULL;
	if (pEffect == NULL)
	{
		pEffect = new CEffect;
		pEffect->Init();
		//pEffect->SetSize(B_SIZE_H, B_SIZE_W);//�e�̃T�C�Y
		pEffect->BindTexture(m_pTexture);
		pEffect->SetPos(pos);////�v���C���[�̈ړ����(�ύX�E�X�V)������
		pEffect->SetCol(col);
		//pEffect->SetLife(20);
	}
	return pEffect;
}
#endif

//! =============================================================================
//! ������
//! =============================================================================
HRESULT CEffect::Init(void)
{
	CScene2D::Init();

	
	m_fRadius = 20;			// ���a(�傫��)
	SetSize(m_fRadius, m_fRadius);
	m_nLife = 10;				// �\������(����)

	return S_OK;
}

//! =============================================================================
//! �I��
//! =============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//! =============================================================================
//! �X�V
//! =============================================================================
void CEffect::Update(void)
{


	m_fRadius--;
	if (m_fRadius <= 0)
	{
		m_fRadius = 0;
	}
	//���_���W�̐ݒ� / �G�t�F�N�g�|���S���̒��S�_������o��
	SetSize(m_fRadius, m_fRadius-10);
	m_nLife--;
	if (m_nLife <= 0)
	{
		this->Uninit();//�������g������
	}
}

//! =============================================================================
//! �`��
//! =============================================================================
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		CScene2D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}