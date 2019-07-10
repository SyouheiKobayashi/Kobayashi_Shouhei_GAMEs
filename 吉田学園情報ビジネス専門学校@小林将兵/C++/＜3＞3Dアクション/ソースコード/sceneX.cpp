//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//						X���f���������� [sceneX.h]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "sceneX.h"
#include "manager.h"
#include "debugLog.h"
#include "input.h"
#include "game.h"

//==============================================
//					�R���X�g���N�^
//==============================================
CSceneX::CSceneX(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{

}
//==============================================
//					�f�X�g���N�^
//==============================================
CSceneX::~CSceneX()
{

}

//==============================================
//					����
//==============================================
CSceneX *CSceneX::Create(void)
{
	CSceneX *pSceneX = NULL;

	if (pSceneX == NULL)
	{
		pSceneX = new CSceneX;
		pSceneX->Init();
	}
	return pSceneX;
}

//==============================================
//					����������
//==============================================
HRESULT CSceneX::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//? ��X�t�@�C���̓ǂݍ��݂͊ecpp�ōs�����̏����擾���Ďg�p����

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
	m_modelSize = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//�T�C�Y�̕ύX
	Vtx();											//�����蔻��

	return S_OK;
}

//==============================================
//					�I������
//==============================================
void CSceneX::Uninit(void)
{
	//? �����b�V���̊J���A�}�e���A���̊J���͊ecpp�ŉ���A�폜���Ă���

	Release();
}

//==============================================
//					�X�V����
//==============================================
void CSceneX::Update(void)
{
	
}

//==============================================
//					�`�揈��
//==============================================
void CSceneX::Draw(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;

	D3DXMATRIX scale_matrix;//�T�C�Y�ύX�p

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�ړ��𔽉f
	D3DXMatrixTranslation(&m_mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	//���f���̊g��/�k��
	D3DXMatrixScaling(&scale_matrix, m_modelSize.x, m_modelSize.y, m_modelSize.z);
	m_mtxTrans = scale_matrix * m_mtxTrans;//�g��k��*�ړ�

	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);
	m_mtxTrans = m_mtxRot * m_mtxTrans;//��]*(�g��k��*�ړ�)

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxTrans);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_pNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&m_pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);

		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

void CSceneX::DrawShadow(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;

	D3DXMATRIX scale_matrix;//�T�C�Y�ύX�p

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	 //��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//�ړ��𔽉f
	D3DXMatrixTranslation(&m_mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	m_mtxTrans = m_mtxRot * m_mtxTrans;

	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	// �e�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	vecLight = D3DXVECTOR4(0.2f, 10.8f, 0.2f, 0.0f);
	pos = D3DXVECTOR3(m_pos.x, m_pos.y-50.0f, m_pos.z);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	//���[���h�Ɖe�̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxShadow);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntMat = 0; nCntMat < (int)m_pNumMat; nCntMat++)
	{
		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//+ ��������I�u�W�F�N�g�{���̕`��
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&m_mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);
	m_mtxTrans = m_mtxRot * m_mtxTrans;


	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxTrans);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_pNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&m_pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);

		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}
//==============================================
//			�����蔻��Ɋւ��鏈��
//==============================================
void CSceneX::Vtx(void)
{
	int nNumVtx;
	DWORD sizeFVF;
	BYTE *pVtxBuff;

	m_VtxMin = D3DXVECTOR3(10000, 10000, 10000);	//�ő�l
	m_VtxMax = D3DXVECTOR3(-10000, -10000, -10000);	//�ŏ��l

	//���_���̎擾
	nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVer = 0; nCntVer < nNumVtx; nCntVer++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
													
		if (m_VtxMin.x >= vtx.x)
		{
			m_VtxMin.x = vtx.x;
		}
		if (m_VtxMin.y >= vtx.y)
		{
			m_VtxMin.y = vtx.y;
		}
		if (m_VtxMin.z >= vtx.z)
		{
			m_VtxMin.z = vtx.z;
		}
		
		if (m_VtxMax.x <= vtx.x)
		{
			m_VtxMax.x = vtx.x;
		}
		if (m_VtxMax.y <= vtx.y)
		{
			m_VtxMax.y = vtx.y;
		}
		if (m_VtxMax.z <= vtx.z)
		{
			m_VtxMax.z = vtx.z;
		}
		//�T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	D3DXVECTOR3 size = GetModelSize();
	m_VtxMin = D3DXVECTOR3(m_VtxMin.x * m_modelSize.x, m_VtxMin.y * m_modelSize.y, m_VtxMin.z * m_modelSize.z);
	m_VtxMax = D3DXVECTOR3(m_VtxMax.x * m_modelSize.x, m_VtxMax.y * m_modelSize.y, m_VtxMax.z * m_modelSize.z);

	m_VtxMin = D3DXVECTOR3(m_VtxMin.x, m_VtxMin.y, m_VtxMin.z);
	m_VtxMax = D3DXVECTOR3(m_VtxMax.x, m_VtxMax.y, m_VtxMax.z);

	//���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();
}

//==============================================
//				�g�p���f���̓ǂݍ���
//==============================================
void CSceneX::BindObject(LPD3DXBUFFER buffMat, DWORD numMat, LPD3DXMESH mesh)
{
	m_pBuffMat = buffMat;
	m_pNumMat = numMat;
	m_pMesh = mesh;
}

//==============================================
//				�g�p����UV�̓ǂݍ���
//==============================================
void CSceneX::BindTexture(LPDIRECT3DTEXTURE9 textureInfo)
{
	m_pTexture = textureInfo;
}

//==============================================
//					�ʒu
//==============================================
void CSceneX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//==============================================
//					�ړ�
//==============================================
void CSceneX::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
	m_pos += m_move;
}
//==============================================
//					��],�X��
//==============================================
void CSceneX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//==============================================
//					�T�C�Y�̕ύX
//==============================================
void CSceneX::SetModelSize(float fModelSizeX, float fModelSizeY, float fModelSizeZ)
{
	m_modelSize = D3DXVECTOR3(fModelSizeX, fModelSizeY, fModelSizeZ);
}

//==============================================
//						�F
//==============================================
void CSceneX::SetCol(D3DXCOLOR col)
{
	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	if (m_pMat != NULL)
	{
		m_pMat->MatD3D.Diffuse = col;
		m_pMat->MatD3D.Ambient = col;
	}
}

//==============================================
//			�O���f�[�^��ǂݍ��ނ��߂̏���
//==============================================
char *CSceneX::ReadLine(FILE *pFile, char *pDst)
{
	fgets(pDst, 256, pFile);

	while (1)
	{
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			fgets(pDst, 256, pFile);

		}
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += 1;
		}
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += 1;
		}
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			fgets(pDst, 256, pFile);

		}
		else
		{
			break;
		}
	}

	return pDst;
}

char *CSceneX::GetLIneTop(char *pSrc)
{
	while (1)
	{
		if (memcmp(pSrc, " ", strlen(" ")) == 0)
		{
			pSrc += 1;
		}
		else if (memcmp(pSrc, "\t", strlen("\t")) == 0)
		{
			pSrc += 1;
		}
		else
		{
			break;
		}
	}

	return pSrc;
}

int CSceneX::PopString(char *pSrc, char *pDst)
{
	int nCnt = 0;

	while (1)
	{
		nCnt += 1;
		if (memcmp(pSrc, " ", strlen(" ")) == 0)
		{
			pSrc = "\0";
			break;
		}
		else
		{
			pSrc += 1;
		}
	}

	strcpy(pDst, pSrc);

	return nCnt;
}