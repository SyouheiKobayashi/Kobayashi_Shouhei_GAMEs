//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �����G�t�F�N�g���� [explosion.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"

//�}�N��
//�ǂݍ��ރe�N�X�`����
#define TEXTURE_NAME01	("DATA\\explosion000.png")
//�����̃T�C�Y��
#define B_SIZE_H	(50.0f)//�c�T�C�Y
#define B_SIZE_W	(50.0f)//���T�C�Y
//�����̃A�j���[�V�����ݒ聫
#define	EX_ANIM_SPEED	(5)//�A�j���[�V��������
#define	EX_ANIM_W	(8)//������
#define	EX_ANIM_H	(1)//�c����

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;
//! =============================================================================
//! �R���X�g���N�^
//! =============================================================================
CExplosion::CExplosion():CScene2D(OBJ_DRAW::DRAW_EXPLOSION)
{
	m_CntAnim = 0;//�A�j���[�V�����̑���
	m_PatternAnim = 0;//�A�j���[�V�����̕�����
}

//! =============================================================================
//! �f�X�g���N�^
//! =============================================================================
CExplosion::~CExplosion()
{

}

//! =============================================================================
//! Tex�ǂݍ���
//! =============================================================================
HRESULT CExplosion::Load(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture);

	return S_OK;
}
//! =============================================================================
//!�@Tex�j��
//! =============================================================================
void CExplosion::UnLoad(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//! =============================================================================
//!�@����
//! =============================================================================
#if 1
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{

	CExplosion *pExplosion = NULL;
	if (pExplosion == NULL)
	{
		pExplosion = new CExplosion;
		pExplosion->Init();
		pExplosion->SetSize(B_SIZE_H, B_SIZE_W);//�e�̃T�C�Y
		pExplosion->SetPos(pos);////�v���C���[�̈ړ����(�ύX�E�X�V)������
		pExplosion->BindTexture(m_pTexture);
	}
	return pExplosion;
}
#endif

//! =============================================================================
//! ������
//! =============================================================================
HRESULT CExplosion::Init(void)
{
	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_EXPLOSION);//�^�C�v�𓖂Ă͂߂�
	m_CntAnim = 0;//�A�j���[�V�����̑���
	m_PatternAnim = 0;//�A�j���[�V�����̕�����
	return S_OK;
}

//! =============================================================================
//! �I��
//! =============================================================================
void CExplosion::Uninit(void)
{

	CScene2D::Uninit();
}

//! =============================================================================
//! �X�V
//! =============================================================================
void CExplosion::Update(void)
{
	m_CntAnim++; //�J�E���^�[�̉��Z �����̑��x
	if (m_CntAnim % EX_ANIM_SPEED == 0)
	{
		m_PatternAnim = (m_PatternAnim + 1) % (EX_ANIM_W * EX_ANIM_H);//�p�^�[��No.�X�V
	}

	CScene2D::SetTexAnim(EX_ANIM_SPEED, EX_ANIM_W, EX_ANIM_H, m_PatternAnim);

	if (m_PatternAnim >= (EX_ANIM_W * EX_ANIM_H) - 1)
	{
		//�g�p�����e������
		CScene2D::Uninit();
	}
	
}

//! =============================================================================
//! �`��
//! =============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}