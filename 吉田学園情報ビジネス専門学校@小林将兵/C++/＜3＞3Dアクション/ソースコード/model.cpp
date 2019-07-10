//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//���f������ [model.cpp]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "scene.h"
#include "model.h"
#include "manager.h"
#include "input.h"
#include "debugLog.h"

//==============================================
//�R���X�g���N�^
//==============================================
CModel::CModel()
{
	
	m_pVtxBuff = NULL;				//���_�o�b�t�@�ւ̃|�C���^

}
//==============================================
//�f�X�g���N�^
//==============================================
CModel::~CModel()
{

}

//==============================================
//����
//==============================================
CModel *CModel::Create(D3DXVECTOR3 pos)
{
	CModel *pModel = NULL;

	if (pModel == NULL)
	{
		pModel = new CModel;
		pModel->m_pos = pos;
		pModel->Init();
	}
	return pModel;
}
//==============================================
//����������
//==============================================
HRESULT CModel::Init(void)
{
	return S_OK;
}

//==============================================
//�I������
//==============================================
void CModel::Uninit(void)
{
	//�g�p�����eCPP�ō폜�E���
}

//==============================================
//�X�V����
//==============================================
void CModel::Update(void)
{

}

//==============================================
//�`�揈��
//==============================================
void CModel::Draw(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;
	D3DXMATRIX m_proj;
	

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	D3DXMATRIX mtxParent;

	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();


	for (int nCntMat = 0; nCntMat < (int)m_pNumMat; nCntMat++)
	{

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&m_pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);

		// ���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);

	}
	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

}

//==============================================
///���f���̓ǂݍ���
//==============================================
void CModel::BindModel(LPD3DXBUFFER buffMat, DWORD numMat, LPD3DXMESH mesh)
{
	m_pBuffMat = buffMat;
	m_pNumMat = numMat;
	m_pMesh = mesh;
}
//==============================================
///���f���ɒ���t����摜�̓ǂݍ���
//==============================================
void CModel::BindTexture(LPDIRECT3DTEXTURE9 textureInfo)
{
	m_pTexture = textureInfo;
}

//==============================================
///			���f�����Ƃ̐e�����߂�
//==============================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}

//==============================================
///			���f�����Ƃ̈ʒu�����߂�
//==============================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==============================================
//				���f�����Ƃ̉�]
//==============================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//==============================================
//						�F
//==============================================
void CModel::SetCol(D3DXCOLOR col)
{
	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	if (m_pMat != NULL)
	{
		m_pMat->MatD3D.Diffuse = col;
		m_pMat->MatD3D.Ambient = col;
	}
}
