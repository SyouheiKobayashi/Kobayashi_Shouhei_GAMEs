//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// ���C�t���� [life.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "life.h"
#include "Gauge.h"
#include "manager.h"

//�}�N��
#define LIFE_SIZE_X	(30)
#define LIFE_SIZE_Y	(15)
#define LIFE_SPACE		(30)
#define LIFE_POS_X	(52)
#define LIFE_POS_Y	(SCREEN_HEIGHT-75)

//�ǂݍ��ރe�N�X�`����
#define TEXTURE_NAME01	("DATA\\PLAYER_LIFE.jpg")
//�ÓI�����o�ϐ�
int CLife::m_nLife = 0;
int CLife::m_nLifeGauge[MAX_LIFE] = {};
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;

//=============================================================================
//+ ���C�t�̃R���X�g���N�^
//=============================================================================
CLife::CLife() :CScene(OBJ_DRAW::DRAW_UI)
{
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		m_apGauge[nCnt] = NULL;
	}

}
//=============================================================================
//+ ���C�t�̃f�X�g���N�^
//=============================================================================
CLife::~CLife()
{

}
//=============================================================================
//+ ���C�t�̐�������
//=============================================================================
CLife *CLife::Create(void)
{
	CLife *pLife = NULL;

	if (pLife == NULL)
	{
		pLife = new CLife;
		pLife->Init();
	}

	return pLife;
}

//=============================================================================
//+ �����E�i���o�[��Tex�̕K�v���ǂݍ���
//=============================================================================
HRESULT CLife::Load(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture);

	return S_OK;
}
//=============================================================================
//+ ���C�t��Tex�𑼂̏����ɂ��폜�������Ȃ�
//=============================================================================
void CLife::UnLoad(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//+ ���C�t�̏���������
//=============================================================================
HRESULT CLife::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apGauge[nCnt] = new CGauge;
		m_apGauge[nCnt]->Init();
		m_apGauge[nCnt]->SetSize(LIFE_SIZE_X, LIFE_SIZE_Y);
		m_apGauge[nCnt]->SetPos(D3DXVECTOR3(LIFE_POS_X, LIFE_POS_Y, 0.0f), LIFE_SPACE, nCnt);
		
	}
	return S_OK;
}
//=============================================================================
//+ ���C�t�̏I������
//=============================================================================
void CLife::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apGauge[nCnt]->Uninit();
		m_apGauge[nCnt] = NULL;
	}
	//�������g��delete	<Scene>��delete�������g�p
	Release();
}
//=============================================================================
//+ ���C�t�̍X�V����
//=============================================================================
void CLife::Update(void)
{
	
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apGauge[nCnt]->Update();
		m_apGauge[nCnt]->SetNumber(m_nLifeGauge[nCnt]);//�J�E���g���Ԋu��������
	}
}
//=============================================================================
//+ ���C�t�̕`�揈��
//=============================================================================
void CLife::Draw(void)
{
	
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	for (int nCnt = 0; nCnt < m_nLife; nCnt++)
	{
		//���Ăяo����number�������g��
		m_apGauge[nCnt]->Draw();
	}
}

void CLife::SetPos(D3DXVECTOR3 pos)
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

void CLife::SetLife(int nLife)
{
	m_nLife = nLife;
	
}