//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�`���[�g���A���p�摜�������� [tutorial2DTex.cpp]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "tutorial2DTex.h"
#include "manager.h"
#include "input.h"
#include "debugLog.h"
#include "game.h"

LPDIRECT3DTEXTURE9 CTutorial2DTex::m_pTexture[TEX_MAX] = {};

//==============================================
//�R���X�g���N�^
//==============================================
CTutorial2DTex::CTutorial2DTex(int nPriority, DATA_TYPE dataType) :CScene2D(nPriority, dataType)
{
	m_pVtxBuff = NULL;		//���_�o�b�t�@�ւ̃|�C���^
}
//==============================================
//�f�X�g���N�^
//==============================================
CTutorial2DTex::~CTutorial2DTex()
{

}

//==============================================
//����
//==============================================
CTutorial2DTex *CTutorial2DTex::Create(int nTexType,D3DXVECTOR3 pos, float nSizeX, float nSizeY)
{

	CTutorial2DTex *pTexture2D = NULL;

	if (pTexture2D == NULL)
	{
		pTexture2D = new CTutorial2DTex;
		pTexture2D->BindTexture(m_pTexture[nTexType]);
		pTexture2D->SetPos(pos);
		pTexture2D->SetSize(nSizeX, nSizeY);
		pTexture2D->Init();
	}
	return pTexture2D;
}
//==============================================
//����������
//==============================================
HRESULT CTutorial2DTex::Init(void)
{
	CScene2D::Init();

	return S_OK;
}
//==============================================
//�I������
//==============================================
void CTutorial2DTex::Uninit(void)
{
	CScene2D::Uninit();

}

//==============================================
//�X�V����
//==============================================
void CTutorial2DTex::Update(void)
{
	CScene2D::Update();
}

//==============================================
//�`�揈��
//==============================================
void CTutorial2DTex::Draw(void)
{
	CScene2D::Draw();
}

//==============================================
//���f������摜�̓ǂݍ���
//==============================================
HRESULT CTutorial2DTex::TextureLoad(void)
{

	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "DATA/TEXTURE/T03.jpg", &m_pTexture[0]);

	return S_OK;
}

//==============================================
//���f�������摜�̔j��
//==============================================
void CTutorial2DTex::TextureUnLoad(void)
{

	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

}