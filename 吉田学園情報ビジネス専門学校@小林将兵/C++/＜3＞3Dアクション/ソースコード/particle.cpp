//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//				3D�p�[�e�B�N������ [particle3D.cpp]
//			Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "input.h"
#include "particle.h"
#include "scene3D.h"

//==============================================
//				�ÓI�����o�ϐ�
//==============================================

LPDIRECT3DTEXTURE9 CParticle3D::m_pTexture[MAX_PARTICLE3D] = {};
int CParticle3D::m_nNumTexture = NULL;
char CParticle3D::m_aFileNameTexture[MAX_PARTICLE3D][256] = {};

//==============================================
//					�R���X�g���N�^
//==============================================
CParticle3D::CParticle3D(int nPriority, DATA_TYPE dataType) :CBillboard(nPriority, dataType)
{

}

//==============================================
//					�f�X�g���N�^
//==============================================
CParticle3D::~CParticle3D()
{

}

//==============================================
//					����
//==============================================
CParticle3D *CParticle3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, bool bAngle, int DeleteTime, float fTransSize, int nType)
{

	CParticle3D *pParticle3D = NULL;
	if (pParticle3D == NULL)
	{
		pParticle3D = new CParticle3D;
		pParticle3D->BindTexture(m_pTexture[nType]);
		pParticle3D->SetPos(pos);
		pParticle3D->m_move = move;
		pParticle3D->m_rot = rot;
		pParticle3D->SetCol(col);
		pParticle3D->m_bAngle = bAngle;
		pParticle3D->SetSize(D3DXVECTOR3(1.0f,1.0f,0.0f));
		pParticle3D->m_nDeleteTime = DeleteTime;
		pParticle3D->m_fTransSize = fTransSize;
		pParticle3D->m_nType = nType;

		pParticle3D->Init();
	}
	return pParticle3D;
}

//==============================================
//				����������
//==============================================
HRESULT CParticle3D::Init(void)
{
	m_nCnt = 0;
	m_PatternAnim = 0;
	m_fAngle = D3DX_PI;//�p�x
	m_fRange = 2.0f;//�~�̑傫��
	m_fActionAngle = 10.0f;
	CBillboard::Init();

	return S_OK;
}

//==============================================
//				�I������
//==============================================
void CParticle3D::Uninit(void)
{

	CBillboard::Uninit();
}

//==============================================
//				�X�V����
//==============================================
void CParticle3D::Update(void)
{
	//�ʒu���̎擾 / �X�V
	D3DXVECTOR3 pos = CBillboard::GetPos();
	D3DXVECTOR3 Fixed = CBillboard::GetPos();
	pos += m_move;

	//�����E��]���̎擾 / �X�V
	D3DXVECTOR3 rot = CBillboard::GetRot();
	rot += m_rot;

	//�J���[���̎擾
	D3DXCOLOR col = CBillboard::GetCol();

	//���S�����ɉ�]������
	if (m_bAngle == true)
	{
		m_fActionAngle += -0.19f;//��]���x
		pos.x = m_fRange*(float)sin(m_fAngle + m_fActionAngle) + (Fixed.x);
		pos.z = m_fRange*(float)cos(m_fAngle + m_fActionAngle) + (Fixed.z);
		//pos.y += 2.0f;
	}
	//�l�̍X�V
		m_nDeleteTime--;
	if (m_nType == 0)
	{
		col.a -= 0.01f;
	}

	//���̔��f
	CBillboard::SetPos(pos);
	CBillboard::SetRot(rot);
	CBillboard::SetCol(col);
	CBillboard::SetParticle(m_fTransSize, CBillboard::GetCol());
	
	if (m_nType == 0)
	{
		CBillboard::SetTexAnim(2, 4, 3, true);
	}

	if (m_nDeleteTime <= 0)//���Ŏ��ԂɒB������
	{
		CParticle3D::Uninit();
	}
}

//==============================================
//					�`�揈��
//==============================================
void CParticle3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillboard::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	//Z�e�X�g�����̒l�ɖ߂�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);


	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//==============================================
//			�O����񂩂�e�N�X�`���̓ǂݍ���
//==============================================
HRESULT CParticle3D::TextureLoad(void)
{
	FILE *pFile;

	char * pStrCur;//�擪������̃|�C���^
	char aLine[256];//������̓ǂݍ���
	char aStr[256];//������̔����o��
	int nCntTexture = 0;//�ǂݍ��ރe�N�X�`�������J�E���g

						//�O���e�L�X�g�̓ǂݍ��ݏ���
	pFile = fopen("DATA\\TEXT\\PARTICLE.txt", "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CScene3D::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "TEX_LOAD", strlen("TEX_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CScene3D::GetLIneTop(&aLine[0]);

					if (memcmp(pStrCur, "NUM_TEXTURE = ", strlen("NUM_TEXTURE = ")) == 0)
					{
						pStrCur += strlen("NUM_TEXTURE = ");
						strcpy(aStr, pStrCur);
						m_nNumTexture = atoi(aStr);
					}

					if (memcmp(pStrCur, "TEXTURE_NAME ", strlen("TEXTURE_NAME ")) == 0)
					{

						pStrCur += strlen("TEXTURE_NAME ");

						strcpy(aStr, pStrCur);
						while (1)
						{
							if (pStrCur[strlen(pStrCur) - 1] != 'g')
							{
								pStrCur[strlen(pStrCur) - 1] = '\0';//���s������NULL�����ɕϊ�(�Q�l�T�C�g::http://hisashi.me/blog/?p=714)
							}
							else
							{
								break;
							}

							strcpy(&m_aFileNameTexture[nCntTexture][0], pStrCur);
						}

						nCntTexture += 1;
					}

					if (memcmp(pStrCur, "END_TEX_LOAD", strlen("END_TEX_LOAD")) == 0)
					{
						break;
					}
				}
			}
			if (memcmp(pStrCur, "END_TEX_LOAD", strlen("END_TEX_LOAD")) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);

	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	for (int nCnt = 0; nCnt < m_nNumTexture; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aFileNameTexture[nCnt], &m_pTexture[nCnt]);
	}

	return S_OK;
}
//==============================================
//				�e�N�X�`���̔j��
//==============================================
void CParticle3D::TextureUnLoad(void)
{
	for (int nCnt = 0; nCnt < m_nNumTexture; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
