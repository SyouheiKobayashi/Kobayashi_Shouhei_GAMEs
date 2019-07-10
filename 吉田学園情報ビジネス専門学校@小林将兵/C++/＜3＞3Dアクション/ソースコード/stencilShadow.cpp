//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�X�e���V���V���h�E�������� [stencilShadow.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "debugLog.h"
#include "input.h"
#include "sceneX.h"
#include "stencilShadow.h"
#include "game.h"
#include "player.h"
#include "polygon2D.h"

//=====================================================================
//�ÓI�����o�ϐ�
//=====================================================================
//�e�L�X�g�ǂݍ��݊֘A
int CStencilShadow::m_nNumObject = NULL;
int CStencilShadow::m_nNumTexture = NULL;
char CStencilShadow::m_aFileNameObject[MAX_STENCIL][256] = {};
char CStencilShadow::m_aFileNameTexture[MAX_STENCIL][256] = {};
//���f�����
int CStencilShadow::m_objType = 0;
LPD3DXMESH CStencilShadow::m_pMesh[MAX_STENCIL] = {};
LPD3DXBUFFER CStencilShadow::m_pBuffMat[MAX_STENCIL] = {};
DWORD CStencilShadow::m_pNumMat[MAX_STENCIL] = {};
//�摜�֘A
LPDIRECT3DTEXTURE9 CStencilShadow::m_pTexture[STENCIL_TEXTURE_NUM] = {};

int CStencilShadow::m_nCreateNum = 0;//�������ꂽ���̋L��

CPolygon2D *CStencilShadow::m_pPolygon2D = NULL;


//==============================================
//�R���X�g���N�^
//==============================================
CStencilShadow::CStencilShadow(int nPriority, DATA_TYPE dataType) :CSceneX(nPriority, dataType)
{
	//m_pTexture = NULL;		//�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;		//���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);
	/*m_VtxMin = GetVtxMin();
	m_VtxMax = GetVtxMax();*/
	
}
//==============================================
//�f�X�g���N�^
//==============================================
CStencilShadow::~CStencilShadow()
{

}

//==============================================
//����
//==============================================
CStencilShadow *CStencilShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_nCreateNum += 1;
	CStencilShadow *pObject = NULL;
	if (pObject == NULL)
	{
		pObject = new CStencilShadow;
		pObject->BindObject(m_pBuffMat[0], m_pNumMat[0], m_pMesh[0]);	//�g�p����I�u�W�F�N�g
		pObject->BindTexture(m_pTexture[0]);							//�g�p����摜
		pObject->Init();
		pObject->SetPos(pos);					//�ʒu�̔��f
		pObject->SetRot(rot);
	}
	return pObject;
}
//==============================================
//����������
//==============================================
HRESULT CStencilShadow::Init(void)
{
	CSceneX::Init();

	

	//�f�o�C�X���̎擾
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
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	
	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[���
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================
//�I������
//==============================================
void CStencilShadow::Uninit(void)
{
	m_nCreateNum = 0;

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CSceneX::Uninit();

}

//==============================================
//�X�V����
//==============================================
void CStencilShadow::Update(void)
{
	CSceneX::Update();
	
	CPlayer *pPlayer = CGame::GetPlayer();
	
	SetPos(D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y-30.0f, pPlayer->GetPos().z));
	//Debug();
	
}

//==============================================
//�`�揈��
//==============================================
void CStencilShadow::Draw(void)
{
	if (CGame::GetDeath() == false)
	{
		//�f�o�C�X���̎擾
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);//�F�̐���

		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_ZERO);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCR);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);//�\�ʃJ�����O
		CSceneX::Draw();//�\�J�����O�p���f���̕\��

		pDevice->SetRenderState(D3DRS_STENCILREF, 1);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_ZERO);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//���ʃJ�����O
		CSceneX::Draw();//���ʃJ�����O�p�̃��f���\��

		//? �J���[��߂�����
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);

		pDevice->SetRenderState(D3DRS_STENCILREF, 2);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);//���ׂĂ�ΏۂɌ���
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);//�X�e���V���AZ�e�X�g�Ƃ��ɒʂ��Ă���
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);//�X�e���V���̂ݒʂ��Ă���
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);//�X�e���V���̂ݒʂ��ĂȂ�

		//? �؂蔲���p�̃|���S��(�}�X�N)�̕`��
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//? ���Ƃɖ߂�
		pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
}

//==============================================
//�g�p����I�u�W�F�N�g�̓ǂݍ���
//==============================================
HRESULT CStencilShadow::ObjectLoad(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();


	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("DATA\\MODEL\\shadow001.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat[0],
		NULL,
		&m_pNumMat[0],
		&m_pMesh[0]);


	return S_OK;
}
//==============================================
//�g�p�����I�u�W�F�N�g�̔j��
//==============================================
void CStencilShadow::ObjectUnLoad(void)
{
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		//���b�V���̊J��
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		//�}�e���A���֘A�̊J��
		if (m_pNumMat[nCnt] != NULL)
		{
			m_pNumMat[nCnt] = NULL;
		}
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}
	}
}

//==============================================
//�I�u�W�F�N�g�ɔ��f������摜�̓ǂݍ���
//==============================================
HRESULT CStencilShadow::TextureLoad(void)
{
	FILE *pFile;

	char * pStrCur;//�擪������̃|�C���^
	char aLine[256];//������̓ǂݍ���
	char aStr[256];//������̔����o��
	int nCntTexture = 0;

	//�e�L�X�g�̓ǂݍ��݁�
	pFile = fopen(STENCIL_TEXT, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "TEXTURE_LOAD", strlen("TEXTURE_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					//�I�u�W�F�N�g�Ɏg�p����摜�̐�
					if (memcmp(pStrCur, "NUM_TEXTURE = ", strlen("NUM_TEXTURE = ")) == 0)
					{
						pStrCur += strlen("NUM_TEXTURE = ");
						strcpy(aStr, pStrCur);
						m_nNumTexture = atoi(aStr);
					}

					//�I�u�W�F�N�g�Ɏg�p����摜�̖��O
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

					//�ǂݍ��݂̏I���
					if (memcmp(pStrCur, "END_TEXTURE_LOAD", strlen("END_TEXTURE_LOAD")) == 0)
					{
						break;
					}
				}

			}
			//�ǂݍ��݂̏I���
			if (memcmp(pStrCur, "END_TEXTURE_LOAD", strlen("END_TEXTURE_LOAD")) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);

	//�f�o�C�X���̎擾
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
//�I�u�W�F�N�g�ɔ��f�������摜�̔j��
//==============================================
void CStencilShadow::TextureUnLoad(void)
{
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//==============================================
//�f�o�b�N
//==============================================
void CStencilShadow::Debug(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	if (m_pInputKeyboard->GetPress(DIK_LEFT) == true)
	{
		pos.x -= 1.0f;
	}
	if (m_pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{
		pos.x += 1.0f;
	}
	SetPos(pos);

	if (m_pInputKeyboard->GetPress(DIK_W) == true)
	{
		rot.x -= 0.05f;
	}
	if (m_pInputKeyboard->GetPress(DIK_S) == true)
	{
		rot.x += 0.05f;
	}
	if (m_pInputKeyboard->GetPress(DIK_A) == true)
	{
		rot.z -= 0.05f;
	}
	if (m_pInputKeyboard->GetPress(DIK_D) == true)
	{
		rot.z += 0.05f;
	}
	SetRot(rot);

	CDebug::DebugLog("\n�I�u�W�F�N�g�������@%d", m_nCreateNum);

}

