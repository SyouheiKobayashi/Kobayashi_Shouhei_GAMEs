//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//3D�|���S���������� [scene3D.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "scene3D.h"
#include "manager.h"
#include "debugLog.h"
#include "input.h"
#include "game.h"
//==============================================
//3D�|���S���̃R���X�g���N�^
//==============================================
CScene3D::CScene3D(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	m_pTexture = NULL;								//�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;								//���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fSizeX = 100.0f;								//X�T�C�Y
	m_fSizeY = 0.0f;								//Y�T�C�Y
	m_fSizeZ = 100.0f;								//Z�T�C�Y
		
}
//==============================================
//3D3D�|���S���̂̃f�X�g���N�^
//==============================================
CScene3D::~CScene3D()
{

}

//==============================================
//3D�|���S���̐���
//==============================================

CScene3D *CScene3D::Create()
{
	CScene3D *pScene3D = NULL;

	if (pScene3D == NULL)
	{
		pScene3D = new CScene3D;
		pScene3D->Init();

	}
	return pScene3D;
}
//==============================================
//3D�|���S���̏���������
//==============================================
HRESULT CScene3D::Init(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_���̍쐬
	VERTEX_3D *pVtx;

	//���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, NULL, &m_pTexture);


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//3D�|���S���̂̈ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, m_fSizeY, m_fSizeZ + m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, m_fSizeY, m_fSizeZ + m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, m_fSizeY, -m_fSizeZ + m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, m_fSizeY, -m_fSizeZ + m_pos.z);

	//�e�N�X�`���̐���
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);

	//�J���[���
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================
//3D�|���S���̏I������
//==============================================
void CScene3D::Uninit(void)
{
	Release();
}

//==============================================
//3D�|���S���̍X�V����
//==============================================
void CScene3D::Update(void)
{

}

//==============================================
//3D�|���S���̕`�揈��
//==============================================
void CScene3D::Draw(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));


	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//3D�|���S���̂̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//==============================================
//�摜���̎擾�E���f
//==============================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 textureInfo)
{
	m_pTexture = textureInfo;
}


//==============================================
//�ʒu���̎擾�E���f
//==============================================
void CScene3D::SetPos(D3DXVECTOR3 pos)
{

}

//==============================================
//�T�C�Y���̎擾�E���f
//==============================================
void CScene3D::SetSize(float fSizeX, float fSizeY, float fSizeZ)
{
	m_fSizeX = fSizeX;
	m_fSizeY = fSizeY;
	m_fSizeZ = fSizeZ;
}

//==============================================
//�F���̎擾�E���f
//==============================================
void CScene3D::SetCol(D3DXCOLOR col)
{
	m_col = col;
}


//==============================================
//�_�ŏ��̎擾�E���f
//==============================================
void CScene3D::FlashTex(void)
{
	switch (m_bFlash)
	{
	case true:
		fFlashCnt += 0.03f;
		m_col = D3DXCOLOR(fFlashCnt, fFlashCnt, fFlashCnt, fFlashCnt);
		if (fFlashCnt >= 1.0f)
		{
			m_bFlash = false;
		}
		break;

	case false:
		fFlashCnt -= 0.03f;
		m_col = D3DXCOLOR(fFlashCnt, fFlashCnt, fFlashCnt, fFlashCnt);
		if (fFlashCnt <= 0.0f)
		{
			m_bFlash = true;
		}
		break;
	}
}

//=============================================================================
//�A�j���[�V����Set����
//=============================================================================
void CScene3D::SetTexAnim(int nCntAnim, int nWidth, int nHeight, int nPattern)
{
	//���_���̍쐬
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight));
	pVtx[1].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth) + (1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight));
	pVtx[2].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight) + (1.0f / nHeight));
	pVtx[3].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth) + (1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight) + (1.0f / nHeight));

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
