//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					�i���o�[���� [number.cpp]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"

//==============================================
//				�ÓI�����o�ϐ�
//==============================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//==============================================
//					�R���X�g���N�^
//==============================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
}

//==============================================
//					�f�X�g���N�^
//==============================================
CNumber::~CNumber()
{

}

//==============================================
//						����
//==============================================
CNumber *CNumber::Create(void)
{
	CNumber *pNumber = NULL;

	if (pNumber == NULL)
	{
		pNumber = new CNumber;
		pNumber->Init();
	}
	return pNumber;
}
//==============================================
//				����������
//==============================================
HRESULT CNumber::Init(void)
{
	m_SizeX = 0;
	m_SizeY = 0;
	m_nChangeCnt = 0;
	bChange = true;

	//�f�o�C�X���̎擾��
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
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

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
//==============================================
//				�I������
//==============================================
void CNumber::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	delete this;
}
//==============================================
//				�X�V����
//==============================================
void CNumber::Update(void)
{
	
}

//==============================================
//					�`�揈��
//==============================================
void CNumber::Draw(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//==============================================
//�@�@�@�@�@		���l�̔��f
//==============================================
void CNumber::SetNumber(int nNumber)
{
	//���_���̍쐬
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	//�e�N�X�`���̐���
	pVtx[0].tex = D3DXVECTOR2(0.0f + nNumber * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + nNumber * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + nNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + nNumber * 0.1f, 1.0f);


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//==============================================
//				�\���ʒu�E�Ԋu�E����
//==============================================
void CNumber::SetPos(D3DXVECTOR3 pos, float fSpace, int nDigitNum)
{
	m_pos = pos;
	m_fSpace = fSpace;
	m_nDigitNum = nDigitNum;
	//���_���̍쐬
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̈ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y - m_SizeY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y - m_SizeY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y + m_SizeY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y + m_SizeY, 0.0f);


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==============================================
//					�T�C�Y�̒���
//==============================================
void CNumber::SetSize(float X, float Y)
{
	m_SizeX = X;
	m_SizeY = Y;
}

//==============================================
//				�g��k�����o
//==============================================
void CNumber::SetScale(int nChangeTime,float fSpeed)
{

	if (bChange == true)
	{
		m_nChangeCnt++;
		m_fSpace += fSpeed;
		m_pos.x -= fSpeed;
		m_SizeX += fSpeed;
		m_SizeY += fSpeed;
		if (m_nChangeCnt > nChangeTime)
		{
			bChange = false;
			m_nChangeCnt = 0;
		}
	}
	if (bChange == false)
	{
		m_nChangeCnt++;
		m_fSpace -= fSpeed;
		m_pos.x += fSpeed;
		m_SizeX -= fSpeed;
		m_SizeY -= fSpeed;
		if (m_nChangeCnt > nChangeTime)
		{
			bChange = true;
			m_nChangeCnt = 0;

		}
	}

	//���_���̍쐬
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̈ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y - m_SizeY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y - m_SizeY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y + m_SizeY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_SizeX + (m_fSpace * m_nDigitNum), m_pos.y + m_SizeY, 0.0f);


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//==============================================
//					�J���[�̒���
//==============================================
void CNumber::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;
						
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	m_pVtxBuff->Unlock();
}

//==============================================
//					�摜�̓ǂݍ���
//==============================================
HRESULT CNumber::TextureLoad(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TIME_TEX_NAME01, &m_pTexture);

	return S_OK;
}
//==============================================
//			�@�@�摜�̉��
//==============================================
void CNumber::TextureUnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
