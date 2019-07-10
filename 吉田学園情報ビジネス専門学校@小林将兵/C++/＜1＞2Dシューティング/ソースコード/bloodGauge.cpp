//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// ���C�t���� [CBloodGauge.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "game.h"
#include "bloodGauge.h"
#include "gauge.h"
#include "manager.h"
#include "player.h"

//�}�N��
#define BlOOD_SIZE_X	(40)
#define BlOOD_SIZE_Y	(20)
#define BlOOD_SPACE		(30)
#define BlOOD_POS_X	(45)
#define BlOOD_POS_Y	(SCREEN_HEIGHT-27)

//�ǂݍ��ރe�N�X�`����
#define TEXTURE_NAME01	("DATA\\PLAYER_BLOOD.png")
//�ÓI�����o�ϐ�
int CBloodGauge::m_nBlood = 0;
int CBloodGauge::m_nBloodGauge[MAX_BLOOD] = {};
LPDIRECT3DTEXTURE9 CBloodGauge::m_pTexture = NULL;

//! =============================================================================
//! �R���X�g���N�^
//! =============================================================================
CBloodGauge::CBloodGauge() :CScene(OBJ_DRAW::DRAW_UI)
{
	for (int nCnt = 0; nCnt < MAX_BLOOD; nCnt++)
	{
		m_apGauge[nCnt] = NULL;
	}

}
//! =============================================================================
//! �f�X�g���N�^
//! =============================================================================
CBloodGauge::~CBloodGauge()
{

}
//! =============================================================================
//! ��������
//! =============================================================================
CBloodGauge *CBloodGauge::Create(void)
{
	CBloodGauge *pLife = NULL;

	if (pLife == NULL)
	{
		pLife = new CBloodGauge;
		pLife->Init();
	}

	return pLife;
}

//! =============================================================================
//! Tex�ǂݍ�����
//! =============================================================================
HRESULT CBloodGauge::Load(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture);

	return S_OK;
}
//! =============================================================================
//! Tex�̔j��
//! =============================================================================
void CBloodGauge::UnLoad(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//! =============================================================================
//!�@������
//! =============================================================================
HRESULT CBloodGauge::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_BLOOD; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apGauge[nCnt] = new CGauge;
		m_apGauge[nCnt]->Init();
		m_apGauge[nCnt]->SetSize(BlOOD_SIZE_X, BlOOD_SIZE_Y);
		m_apGauge[nCnt]->SetPos(D3DXVECTOR3(BlOOD_POS_X, BlOOD_POS_Y, 0.0f), BlOOD_SPACE, nCnt);
		
	}
	return S_OK;
}
//! =============================================================================
//! �I��
//! =============================================================================
void CBloodGauge::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BLOOD; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apGauge[nCnt]->Uninit();
		m_apGauge[nCnt] = NULL;
	}
	//�������g��delete	<Scene>��delete�������g�p
	Release();
}
//! =============================================================================
//! �X�V
//! =============================================================================
void CBloodGauge::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_BLOOD; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apGauge[nCnt]->Update();
		m_apGauge[nCnt]->SetNumber(m_nBloodGauge[nCnt]);//�J�E���g���Ԋu��������
	}
}
//! =============================================================================
//! �`��
//! =============================================================================
void CBloodGauge::Draw(void)
{

	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	CPlayer *pPlayer = CGame::GetPlayer();
	m_nBlood = pPlayer->GetBloodLife();

	//���t�Q�[�W����𒴂��Ȃ�
	if (m_nBlood >= 16)
	{
		m_nBlood = 15;
	}
	

	for (int nCnt = 0; nCnt < m_nBlood; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apGauge[nCnt]->Draw();
	}
}

//! =============================================================================
//! pos / �ʒu�X�V
//! =============================================================================

void CBloodGauge::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ʏ�\���w�i(�T�C�Y�ω��A��]�Ȃ�,�e.cpp�ŃT�C�Y�̏���������)
	pVtx[0].pos = D3DXVECTOR3(-100, -100, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+100, -100, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-100, +100, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(+100, +100, 0.0f) + m_pos;


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}