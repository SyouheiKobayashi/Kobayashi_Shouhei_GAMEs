//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �Q�[�W���� [gaugecpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

#include "gauge.h"
#include "manager.h"
#include "scene.h"

//=============================================================================
//+ �����E�i���o�[�̃R���X�g���N�^
//=============================================================================
CGauge::CGauge()
{
	//! <�l���N���A�ȏ�Ԃɂ���>
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	m_SizeX = NULL;
	m_SizeY = NULL;


	//m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);//�\������|���S���̈�


}
//=============================================================================
//+ �����E�i���o�[�̃f�X�g���N�^
//=============================================================================
CGauge::~CGauge()
{

}
//=============================================================================
//+ �����E�i���o�[�̐�������
//=============================================================================
CGauge *CGauge::Create(void)
{
	CGauge *pNumber = NULL;

	if (pNumber == NULL)
	{
		pNumber = new CGauge;
		pNumber->Init();
		//pNumber->SetPos(D3DXVECTOR3 (100.0f,100.0f,0.0f));

	}
	return pNumber;
}
//=============================================================================
//+ �����E�i���o�[�̏���������
//=============================================================================
HRESULT CGauge::Init(void)
{
	//! <�����l�̐ݒ�>
	//m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);//�\������|���S���̈ʒu

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
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

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
//=============================================================================
//+ �����E�i���o�[�̏I������
//=============================================================================
void CGauge::Uninit(void)
{

	// �e�N�X�`���̔j��
	//! �e�e�N�X�`��������.cpp�ɏ�������ł���

	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}
//=============================================================================
//+ �����E�i���o�[�̍X�V����
//=============================================================================
void CGauge::Update(void)
{

}
//=============================================================================
//+ �����E�i���o�[�̕`�揈��
//=============================================================================
void CGauge::Draw(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//=============================================================================
//+ �����`�悷�邽�߂̏���
//=============================================================================
void CGauge::SetNumber(int nNumber)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	// �e�N�X�`���̐���
	pVtx[0].tex = D3DXVECTOR2(0.0f + nNumber * 1.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + nNumber * 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + nNumber * 1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + nNumber * 1.0f, 1.0f);


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//+ �\���ʒu,�Ԋu,��
//=============================================================================
void CGauge::SetPos(D3DXVECTOR3 pos, int nSpace, int nCnt)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S���̈ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x + (nSpace*nCnt), pos.y - m_SizeY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + m_SizeX + (nSpace * nCnt), pos.y - m_SizeY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x + (nSpace * nCnt), pos.y + m_SizeY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + m_SizeX + (nSpace * nCnt), pos.y + m_SizeY, 0.0f);


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//+ �T�C�Y��Set����
//=============================================================================
void CGauge::SetSize(float X, float Y)
{
	m_SizeX = X;
	m_SizeY = Y;
}