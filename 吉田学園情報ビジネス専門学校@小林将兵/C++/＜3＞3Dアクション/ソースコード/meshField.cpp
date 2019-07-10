//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					mesh���� [mesh.h]
//			Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "meshField.h"
#include "manager.h"
#include "game.h"
#include "input.h"
#include "debugLog.h"
#include "player.h"

//==============================================
//					�R���X�g���N�^
//==============================================
CMeshField::CMeshField(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_bCheck = false;
	m_DotPosY = 0.0f;
}
//==============================================
//					�f�X�g���N�^
//==============================================
CMeshField::~CMeshField()
{

}

//==============================================
//						����
//==============================================
CMeshField *CMeshField::Create(int nTexType,MESH_TYPE type, D3DXVECTOR3 startPos, int nSize, int nNumX, int nNumZ)
{
	CMeshField *pMeshField = NULL;

	if (pMeshField == NULL)
	{
		pMeshField = new CMeshField;
		pMeshField->m_nSelectTex = nTexType;
		pMeshField->m_nMeshType = type;
		pMeshField->m_startPos = startPos;
		pMeshField->m_nSize = nSize;
		pMeshField->m_nNumX = nNumX;
		pMeshField->m_nNumZ = nNumZ;
		pMeshField->m_nNumIndxMeshField = (nNumX * nNumZ) * 2 + (nNumZ - 1) * 4 + 2;
		pMeshField->m_nNumPolygonMeshField = (nNumX * nNumZ) * 2 + (nNumZ - 1) * 4;
		pMeshField->m_nNumVertexMeshField = (nNumX + 1)*(nNumZ + 1);
		pMeshField->Init();
	}
	return pMeshField;
}
//==============================================
//				����������
//==============================================
HRESULT CMeshField::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bCheck = false;
	m_DotPosY = 0.0f;

	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_���̍쐬
	VERTEX_3D *pVtx;

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertexMeshField,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndxMeshField,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESH_TEX01, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, MESH_TEX02, &m_pTexture[1]);


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���b�V���t�B�[���h�̈ʒu��ݒ�

	for (int nCntZ = 0; nCntZ < m_nNumZ + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nNumX + 1; nCntX++)
		{
			//���_
			if (m_nMeshType == XZ)
			{
				pVtx[nCntZ * (m_nNumX + 1) + nCntX].pos = D3DXVECTOR3((float)m_startPos.x + (float)(m_nSize*nCntX), m_startPos.y, (float)m_startPos.z + (float)(-m_nSize*nCntZ));
			}
			else if (m_nMeshType == XY)
			{
				pVtx[nCntZ * (m_nNumX + 1) + nCntX].pos = D3DXVECTOR3((float)m_startPos.x + (float)(m_nSize*nCntX), (float)m_startPos.z + (float)(-m_nSize*nCntZ), m_startPos.y);
			}
			//�e�N�X�`��
			pVtx[nCntZ * (m_nNumX + 1) + nCntX].tex = D3DXVECTOR2((-1.0f*nCntX), (1.0f*nCntZ));
			//�J���[
			pVtx[nCntZ * (m_nNumX + 1) + nCntX].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//�@��(�����������̂��ߕK�����b�N / �A�����b�N�̊Ԃ�)
	CMeshField::MeshNormaVector();

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	WORD*pIdx;//�C���f�b�N�X�f�[�^�̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^������
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntT = 0, nCntIdx = 0; nCntT < m_nNumZ; nCntT++)
	{
		for (int nCntY = 0; nCntY < m_nNumX + 1; nCntY++, nCntIdx++)
		{
			pIdx[0] = (m_nNumX + 1) + nCntIdx;
			pIdx[1] = 0 + nCntIdx;
			pIdx += 2;

			//���ɐi��ł����P���Ȃ��Ȃ�����&&nCntY�Ǝ����̎w�肵�����̃T�C�Y����v�����Ƃ�
			if (nCntT < m_nNumZ - 1 && nCntY == m_nNumX)
			{
				pIdx[0] = 0 + nCntIdx;
				pIdx[1] = (m_nNumX + 1) + nCntIdx + 1;
				pIdx += 2;
			}
		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//==============================================
//				�I������
//==============================================
void CMeshField::Uninit(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	Release();
}

//==============================================
//				�X�V����
//==============================================
void CMeshField::Update(void)
{
	//�L�[�{�[�h�̎擾����
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//���݂̃��[�h���擾
	int mode = CManager::GetMode();

	//�v���C���[���̎擾����
	if (mode == CManager::STATE_MODE::MODE_GAME)
	{
		m_pPlayer = CGame::GetPlayer();
	}

	if (m_pPlayer != NULL)
	{
		D3DXVECTOR3 playerPos = m_pPlayer->GetPos();
		m_DotPosY = GetHight(playerPos);
	}

	CMeshField::MeshNormaVector();//�@��

}

//==============================================
//					�`�揈��
//==============================================
void CMeshField::Draw(void)
{
	//�f�o�C�X���̎擾��
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

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture[m_nSelectTex]);

	//���b�V���t�B�[���h�̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertexMeshField, 0, m_nNumPolygonMeshField);

}

//==============================================
//					�@������
//==============================================
void CMeshField::MeshNormaVector(void)
{
	//���_���̍쐬
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntZ = 0; nCntZ < m_nNumZ + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nNumX + 1; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;//�e���b�V�����_�̏��
			D3DXVECTOR3 vec0, vec1, vec2;//�e���b�V�����_�̌q��

			if (nCntZ == 0)
			{
				if (nCntX == 0)
				{
					pPos0 = &pVtx[0].pos;
					pPos1 = &pVtx[m_nNumX + 1].pos;
					pPos2 = &pVtx[m_nNumX + 2].pos;
					pPos3 = &pVtx[1].pos;

					vec0 = *pPos1 - *pPos0;
					vec1 = *pPos2 - *pPos0;
					vec2 = *pPos3 - *pPos0;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//���K��

					D3DXVec3Cross(&m_nor[1], &vec2, &vec1);
					D3DXVec3Normalize(&m_nor[1], &m_nor[1]);//���K��

					pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 0))].nor = (m_nor[0] + m_nor[1]) / 2;

				}
				else if (nCntX == m_nNumX)
				{				
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX - 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX * 3 - (nCntX - 1)))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].pos;

					vec0 = *pPos0 - *pPos3;
					vec1 = *pPos2 - *pPos3;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//���K��
					pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].nor = m_nor[0];
				}
				else
				{
					//����
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) * (nCntX + 0))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + ((m_nNumX + 1) + (nCntX)))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].pos;

					vec0 = *pPos0 - *pPos3;
					vec1 = *pPos2 - *pPos3;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//���K��

					//�E��
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 0))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + m_nNumX + 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + m_nNumX + 1))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 1))].pos;

					vec0 = *pPos1 - *pPos0;
					vec1 = *pPos2 - *pPos0;
					vec2 = *pPos3 - *pPos0;

					D3DXVec3Cross(&m_nor[1], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[1], &m_nor[1]);//���K��
					D3DXVec3Cross(&m_nor[2], &vec2, &vec1);
					D3DXVec3Normalize(&m_nor[2], &m_nor[2]);//���K��

					pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 0))].nor = (m_nor[0] + m_nor[1] + m_nor[2]) / 3;
				}

			}
			else if (nCntZ == m_nNumZ)
			{
				if (nCntX == 0)
				{	
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) - (m_nNumX + 1))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 0))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 1))].pos;

					vec0 = *pPos2 - *pPos1;
					vec1 = *pPos0 - *pPos1;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//���K��
					pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 0))].nor = m_nor[0];

				}
				else if (nCntX == m_nNumX)
				{			
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) - 2)].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX - 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) - (nCntX - (nCntX - 1)))].pos;

					vec0 = *pPos3 - *pPos2;
					vec1 = *pPos0 - *pPos2;
					vec2 = *pPos1 - *pPos2;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//���K��
					D3DXVec3Cross(&m_nor[1], &vec2, &vec1);
					D3DXVec3Normalize(&m_nor[1], &m_nor[1]);//���K��

					pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].nor = (m_nor[0] + m_nor[1]) / 2;

				}
				else
				{
					//x1z02		
					//����
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) - (m_nNumX + 1))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (1))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) - (3))].pos;

					vec0 = *pPos3 - *pPos2;
					vec1 = *pPos0 - *pPos2;
					vec2 = *pPos1 - *pPos2;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//���K��
					D3DXVec3Cross(&m_nor[1], &vec2, &vec1);
					D3DXVec3Normalize(&m_nor[1], &m_nor[1]);//���K��

															//�E��
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) - (2))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (m_nNumX))].pos;

					vec0 = *pPos2 - *pPos1;
					vec1 = *pPos0 - *pPos1;

					D3DXVec3Cross(&m_nor[2], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[2], &m_nor[2]);//���K��

					pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].nor = (m_nor[0] + m_nor[1] + m_nor[2]) / 3;
				}

			}
			else
			{
				if (nCntX == 0)
				{
					//�㑤
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) - (m_nNumX + 1))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + 1)].pos;

					vec0 = *pPos2 - *pPos1;
					vec1 = *pPos0 - *pPos1;

					D3DXVec3Cross(&m_nor[2], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[2], &m_nor[2]);//���K��

					//����
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 0))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + m_nNumX + 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + m_nNumX + 2))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX + 1))].pos;

					vec0 = *pPos1 - *pPos0;
					vec1 = *pPos2 - *pPos0;
					vec2 = *pPos3 - *pPos0;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//���K��
					D3DXVec3Cross(&m_nor[1], &vec2, &vec1);
					D3DXVec3Normalize(&m_nor[1], &m_nor[1]);//���K��

					pVtx[(nCntZ*(m_nNumX + 1) + (nCntX))].nor = (m_nor[0] + m_nor[1] + m_nor[2]) / 3;
				}
				else if (nCntX == m_nNumX)
				{
					//�㑤
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) - (2))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + (m_nNumX - 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (m_nNumX))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) - (1))].pos;

					vec0 = *pPos3 - *pPos2;
					vec1 = *pPos0 - *pPos2;
					vec2 = *pPos1 - *pPos2;

					D3DXVec3Cross(&m_nor[0], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[0], &m_nor[0]);//���K��
					D3DXVec3Cross(&m_nor[1], &vec2, &vec1);
					D3DXVec3Normalize(&m_nor[1], &m_nor[1]);//���K��

					//����
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) + (m_nNumX - 1))].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1)) + ((m_nNumX * 2) + 1)].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) + m_nNumX)].pos;

					vec0 = *pPos0 - *pPos3;
					vec1 = *pPos2 - *pPos3;

					D3DXVec3Cross(&m_nor[2], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[2], &m_nor[2]);//���K��

					pVtx[(nCntZ*(m_nNumX + 1) + m_nNumX)].nor = (m_nor[0] + m_nor[1] + m_nor[2]) / 3;
				}
				else
				{
					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) - ((m_nNumX + 1) - nCntX))].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + nCntX)].pos;

					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (1 + nCntX))].pos;

					vec0 = *pPos2 - *pPos1;
					vec1 = *pPos0 - *pPos1;

					D3DXVec3Cross(&m_nor[2], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[2], &m_nor[2]);//���K��
					//----------------------------------------------

					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) + (nCntX - 1))].pos;

					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + ((m_nNumX + 1) + (nCntX)))].pos;
					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) + nCntX)].pos;

					vec0 = *pPos0 - *pPos3;
					vec1 = *pPos2 - *pPos3;

					D3DXVec3Cross(&m_nor[3], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[3], &m_nor[3]);//���K��
					////----------------------------------------------

					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) + nCntX)].pos;
					pPos1 = &pVtx[(nCntZ*(m_nNumX + 1) + (m_nNumX + nCntX) + 1)].pos;
					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (m_nNumX + nCntX) + 2)].pos;

					vec0 = *pPos1 - *pPos0;
					vec1 = *pPos2 - *pPos0;

					D3DXVec3Cross(&m_nor[4], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[4], &m_nor[4]);//���K��
					////----------------------------------------------

					pPos0 = &pVtx[(nCntZ*(m_nNumX + 1) + nCntX)].pos;

					pPos2 = &pVtx[(nCntZ*(m_nNumX + 1) + (m_nNumX + 2) + nCntX)].pos;

					pPos3 = &pVtx[(nCntZ*(m_nNumX + 1) + nCntX) + 1].pos;

					vec0 = *pPos2 - *pPos0;
					vec1 = *pPos3 - *pPos0;

					D3DXVec3Cross(&m_nor[5], &vec1, &vec0);
					D3DXVec3Normalize(&m_nor[5], &m_nor[5]);//���K��

					pVtx[(nCntZ*(m_nNumX + 1) + nCntX)].nor = (m_nor[2] + m_nor[3] + m_nor[4] + m_nor[5]) / 4;
				}
			}
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//==============================================
//				�N���̓����蔻��
//==============================================
float CMeshField::GetHight(D3DXVECTOR3 pos)
{
	if (m_nMeshType == XZ)
	{
		//���[�J��
		D3DXVECTOR3 vector1[6];
		D3DXVECTOR3 vector2[6];
		float fVectorPos[6];
		float fHeight = 0.0f;

		//�v���C���[���̎擾������
		int mode = CManager::GetMode();

		if (mode == CManager::STATE_MODE::MODE_GAME)
		{
			m_pPlayer = CGame::GetPlayer();
		}

		if (m_pPlayer != NULL)
		{
			D3DXVECTOR3 playerPos = m_pPlayer->GetPos();//�ʒu

			//���_���̍쐬
			VERTEX_3D *pVtx;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			int nMeshX, nMeshZ;

			int p0, p1, p2, p3;

			//�͈͓��`�F�b�N
			if (pVtx[0].pos.x < playerPos.x && playerPos.x< pVtx[m_nNumX].pos.x&&pVtx[0].pos.z > playerPos.z && playerPos.z > pVtx[m_nNumZ*(m_nNumX + 1)].pos.z)
			{
				m_bCheck = true;

				//���b�V�����_0
				nMeshX = (int)(pos.x - pVtx[0].pos.x) / m_nSize;
				nMeshZ = (int)(pos.z - pVtx[0].pos.z) / -m_nSize;

				//�e���b�V���̒��_�����߂�
				p0 = nMeshZ*(m_nNumX + 1) + nMeshX;//����
				p1 = nMeshZ*(m_nNumX + 1) + nMeshX + 1;//�E��
				p2 = (nMeshZ + 1)*(m_nNumX + 1) + (nMeshX + 1);//�E��
				p3 = (nMeshZ + 1)*(m_nNumX + 1) + nMeshX;//����

				vector1[0] = pVtx[p2].pos - pVtx[p0].pos;//���S�_
				vector2[0] = playerPos - pVtx[p0].pos;//�v���C���[�Ƃ̒��S�_

				D3DXVECTOR3 V01 = pVtx[p3].pos;//���ƂȂ钸�_
				D3DXVECTOR3 V02 = pVtx[p0].pos;//�����_�ƂȂ��钸�_
				D3DXVECTOR3 V03 = pVtx[p2].pos;//�����_�ƂȂ��钸�_

				fVectorPos[0] = (vector1[0].z*vector2[0].x) - (vector1[0].x * vector2[0].z);//���_���q��

				if (fVectorPos[0] < 0)
				{
					V01 = pVtx[p1].pos;
				}

				float fSave;//���_���̕ۑ�
				fSave = V01.y;

				//�S�̂�y�����_��������
				V03.y -= V01.y;
				V02.y -= V01.y;
				V01.y -= V01.y;

				//�@��
				D3DXVECTOR3 DotNor;
				m_vec0 = V02 - V01;
				m_vec1 = V03 - V01;
				D3DXVec3Cross(&DotNor, &m_vec0, &m_vec1);
				D3DXVec3Normalize(&DotNor, &DotNor);//���K��

				//VecA�����߂�(�v���C���[�̒��_�ƃ|���S���̒��_)
				D3DXVECTOR3 VecA;
				VecA = pos - V01;

				//�t�Z
				fHeight = -((VecA.x * DotNor.x) + (VecA.z * DotNor.z)) / DotNor.y + fSave;
			}
			else
			{
				m_bCheck = false;
			}

			// ���_�o�b�t�@���A�����b�N����
			m_pVtxBuff->Unlock();


		}
		return fHeight;
	}
}

//==============================================
//			�@�@�N���̐���
//==============================================
void CMeshField::SetHight(D3DXVECTOR3 pos, float fValue, float fRange)
{
	if (m_nMeshType == XZ)
	{
		//���_���̍쐬
		VERTEX_3D *pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntZ = 0; nCntZ <= m_nNumZ; nCntZ++)
		{
			for (int nCntX = 0; nCntX <= m_nNumX; nCntX++)
			{
				float fLength = (float)sqrt((pos.x - pVtx->pos.x)*(pos.x - pVtx->pos.x) + (pos.z - pVtx->pos.z)*(pos.z - pVtx->pos.z));//�Ώۂ̒��_�̋���
				if (fLength <= fRange)//�͈͓��`�F�b�N
				{
					float fHight = cosf((D3DX_PI / 2)*(fLength / fRange))*fValue;//�����̔䗦�ɉ���������
					pVtx->pos.y += fHight;
				}

				pVtx++;//4���_�𓮂���
			}
		}

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}

}