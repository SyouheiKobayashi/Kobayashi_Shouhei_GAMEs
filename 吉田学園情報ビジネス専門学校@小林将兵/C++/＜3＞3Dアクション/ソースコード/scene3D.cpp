//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					3D�|���S���������� [scene3D.h]
//			Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "scene3D.h"
#include "manager.h"
#include "debugLog.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "player.h"
//==============================================
//				3D�|���S���̃R���X�g���N�^
//==============================================
CScene3D::CScene3D(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	m_pTexture = NULL;								//�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;								//���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fSizeX = 0.0f;								//X�T�C�Y
	m_fSizeY = 0.0f;								//Y�T�C�Y
	m_fSizeZ = 0.0f;								//Z�T�C�Y
		
}
//==============================================
//			3D3D�|���S���̂̃f�X�g���N�^
//==============================================
CScene3D::~CScene3D()
{

}

//==============================================
//				3D�|���S���̐���
//==============================================

CScene3D *CScene3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float pos0, float pos1, float pos2, float pos3)
{
	CScene3D *pScene3D = NULL;

	if (pScene3D == NULL)
	{
		pScene3D = new CScene3D;
		pScene3D->m_pos = pos;
		pScene3D->m_fSizeX = size.x;
		pScene3D->m_fSizeZ = size.z;
		pScene3D->m_pos0 = pos0;
		pScene3D->m_pos1 = pos1;
		pScene3D->m_pos2 = pos2;
		pScene3D->m_pos3 = pos3;

		pScene3D->Init();

	}
	return pScene3D;
}
//==============================================
//				3D�|���S���̏���������
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
	pVtx[0].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, m_fSizeY + m_pos0, m_fSizeZ + m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, m_fSizeY + m_pos1, m_fSizeZ + m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, m_fSizeY + m_pos2, -m_fSizeZ + m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, m_fSizeY + m_pos3, -m_fSizeZ + m_pos.z);

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
//				3D�|���S���̏I������
//==============================================
void CScene3D::Uninit(void)
{
	Release();
}

//==============================================
//			�@3D�|���S���̍X�V����
//==============================================
void CScene3D::Update(void)
{
	CScene3D::CrossProduct();//�O�ϓ��Ϗ���

}

//==============================================
//			3D�|���S���̕`�揈��
//==============================================
void CScene3D::Draw(void)
{
#if 0
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
#endif
}

//==============================================
//			�摜���̎擾�E���f
//==============================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 textureInfo)
{
	m_pTexture = textureInfo;
}


//==============================================
//			�ʒu���̎擾�E���f
//==============================================
void CScene3D::SetPos(D3DXVECTOR3 pos)
{

}

//==============================================
//			�T�C�Y���̎擾�E���f
//==============================================
void CScene3D::SetSize(float fSizeX, float fSizeY, float fSizeZ)
{
	m_fSizeX = fSizeX;
	m_fSizeY = fSizeY;
	m_fSizeZ = fSizeZ;
}

//==============================================
//				�F���̎擾�E���f
//==============================================
void CScene3D::SetCol(D3DXCOLOR col)
{
	m_col = col;
}


//==============================================
//			�_�ŏ��̎擾�E���f
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
//							�A�j���[�V����Set����
//=============================================================================
void CScene3D::SetTexAnim(int nCntAnim, int nWidth, int nHeight, int nPattern)
{
	//���_���̍쐬
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight));
	pVtx[1].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth) + (1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight));
	pVtx[2].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight) + (1.0f / nHeight));
	pVtx[3].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth) + (1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHeight) + (1.0f / nHeight));

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//							�O�ρE���ϔ��菈��
//=============================================================================
void CScene3D::CrossProduct(void)
{
	D3DXVECTOR3 vector1[6];
	D3DXVECTOR3 vector2[6];
	float fVectorPos[6];

	m_pPlayer = CGame::GetPlayer();

	if (m_pPlayer != NULL)
	{
		D3DXVECTOR3 playerPos = m_pPlayer->GetPos();//�ʒu�擾
		playerPos -= m_pos;

		//���_���̍쐬
		VERTEX_3D *pVtx;
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//+ �O�ϔ��菈��
		vector1[0] = pVtx[0].pos - pVtx[1].pos;//���S�_
		vector2[0] = playerPos - pVtx[0].pos;//�v���C���[�Ƃ̒��S�_
		fVectorPos[0] = (vector1[0].z*vector2[0].x) - (vector1[0].x * vector2[0].z);


		vector1[1] = pVtx[1].pos - pVtx[3].pos;//���S�_
		vector2[1] = playerPos - pVtx[1].pos;//�v���C���[�Ƃ̒��S�_
		fVectorPos[1] = (vector1[1].z*vector2[1].x) - (vector1[1].x * vector2[1].z);

		vector1[2] = pVtx[3].pos - pVtx[2].pos;//���S�_
		vector2[2] = playerPos - pVtx[3].pos;//�v���C���[�Ƃ̒��S�_
		fVectorPos[2] = (vector1[2].z*vector2[2].x) - (vector1[2].x * vector2[2].z);


		vector1[3] = pVtx[2].pos - pVtx[0].pos;//���S�_
		vector2[3] = playerPos - pVtx[2].pos;//�v���C���[�Ƃ̒��S�_
		fVectorPos[3] = (vector1[3].z*vector2[3].x) - (vector1[3].x * vector2[3].z);

		vector1[4] = pVtx[2].pos - pVtx[1].pos;//���S�_
		vector2[4] = playerPos - pVtx[2].pos;//�v���C���[�Ƃ̒��S�_
		fVectorPos[4] = (vector1[4].z*vector2[4].x) - (vector1[4].x * vector2[4].z);

		vector1[5] = pVtx[1].pos - pVtx[2].pos;//���S�_
		vector2[5] = playerPos - pVtx[1].pos;//�v���C���[�Ƃ̒��S�_
		fVectorPos[5] = (vector1[5].z*vector2[5].x) - (vector1[5].x * vector2[5].z);

		//+ ���ϔ��菈��
		if (fVectorPos[4] < 0 && fVectorPos[1] < 0 && fVectorPos[2] < 0)
		{
			m_bCheck = true;
			if (m_fSizeY <= playerPos.y)
			{
				m_DotPosY = SetHight(playerPos, true);//�|���S����̏ꍇ
			}
			else
			{
				m_DotPosY = playerPos.y;//�|���S�����ɓ������ꍇ
			}
		}
		
		else if (fVectorPos[5] < 0 && fVectorPos[3] < 0 && fVectorPos[0] < 0)
		{
			m_bCheck = true;
			if (m_fSizeY <= playerPos.y)
			{
				m_DotPosY = SetHight(playerPos, false);//�|���S����̏ꍇ
			}
			else
			{
				m_DotPosY = playerPos.y;//�|���S�����ɓ������ꍇ
			}
		}
		else//���ϊO
		{
			m_bCheck = false;

			if (playerPos.y <= 0)
			{
				m_DotPosY = 0;//����鐔�l��艺�ɉ����Ȃ�
			}
		}

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
//							��邽�߂̓����蔻�菈��
//=============================================================================
float CScene3D::SetHight(D3DXVECTOR3 pos, bool bJudge)
{
	//���_���̍쐬
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 V01 = (bJudge ? pVtx[3].pos : pVtx[0].pos);//���ƂȂ钸�_
	D3DXVECTOR3 V02 = pVtx[1].pos;//�����_�ƂȂ��钸�_
	D3DXVECTOR3 V03 = pVtx[2].pos;//�����_�ƂȂ��钸�_

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
	VecA.y = -((VecA.x * DotNor.x) + (VecA.z * DotNor.z)) / DotNor.y;

	float fData;
	fData = ((VecA.x * DotNor.x) + (VecA.y * DotNor.y) + (VecA.z *DotNor.z));

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return VecA.y + fSave + m_pos.y;
}

//==============================================
//	�O���f�[�^�̓ǂݍ��݂Ɋւ��鏈��(�ȉ�3������)
//==============================================
char *CScene3D::ReadLine(FILE *pFile, char *pDst)
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

char *CScene3D::GetLIneTop(char *pSrc)
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

int CScene3D::PopString(char *pSrc, char *pDst)
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
