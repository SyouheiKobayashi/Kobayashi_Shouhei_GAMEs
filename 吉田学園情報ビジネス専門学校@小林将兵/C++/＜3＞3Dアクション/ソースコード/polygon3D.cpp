//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					3D�e�N�X�`������ [Tex3D.cpp]
//			Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "input.h"
#include "polygon3D.h"
#include "scene3D.h"

//==============================================
//				�ÓI�����o�ϐ�
//==============================================
const char *CPolygon3D::m_apTexName[] =
{
	"DATA/TEXTURE/EFFECT/effect01.png",		//0
	"DATA/TEXTURE/EFFECT/effect_gate.png",
	"DATA/TEXTURE/STAGE01_BG.jpg",
	"DATA/TEXTURE/STAGE02_BG.jpg",
	"DATA/TEXTURE/STAGE03_BG.jpg",
	"DATA/TEXTURE/EFFECT/effect02.png",		//5
	"DATA/TEXTURE/UI/UI01.png",
	"DATA/TEXTURE/UI/GAME_STAGE02_UI.png",
	"DATA/TEXTURE/UI/GAME_STAGE02_UI02.png",
	"DATA/TEXTURE/WINDOW02.png"
,	"DATA/TEXTURE/EFFECT/effect03.png",		//10

};

LPDIRECT3DTEXTURE9 CPolygon3D::m_apTexture[POLYGON3D_MAX] = {};

//==============================================
//					�R���X�g���N�^
//==============================================
CPolygon3D::CPolygon3D(int nPriority, DATA_TYPE dataType) :CBillboard(nPriority, dataType)
{
	m_fRadius = 0;//���a(�傫��)
	m_nLife = 0;//�\������(����)
}

//==============================================
//					�f�X�g���N�^
//==============================================
CPolygon3D::~CPolygon3D()
{

}

//==============================================
//					����
//==============================================
CPolygon3D *CPolygon3D::Create(int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nAnimSpeed, int nWidth, int nHight, bool bLoop)
 {

	CPolygon3D *pTex3D = NULL;
	if (pTex3D == NULL)
	{
		pTex3D = new CPolygon3D;
		//pTex3D->m_nUseEventTex = nUseEventTex;
		pTex3D->BindTexture(m_apTexture[nTexType]);
		pTex3D->m_nType = nTexType;
		pTex3D->SetSize(size);
		pTex3D->SetPos(pos);
		pTex3D->SetRot(rot);
		pTex3D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pTex3D->m_nAnimSpeed = nAnimSpeed;
		pTex3D->m_nWidth = nWidth;
		pTex3D->m_nHight = nHight;
		pTex3D->m_bLoop = bLoop;

		pTex3D->Init();
	}
	return pTex3D;
}

//==============================================
//				����������
//==============================================
HRESULT CPolygon3D::Init(void)
{
	m_nCnt = 0;
	CBillboard::Init();

	return S_OK;
}

//==============================================
//				�I������
//==============================================
void CPolygon3D::Uninit(void)
{
	CBillboard::Uninit();
}

//==============================================
//				�X�V����
//==============================================
void CPolygon3D::Update(void)
{
	CBillboard::SetTexAnim(m_nAnimSpeed, m_nWidth, m_nHight, m_bLoop);

	if (m_nType == 1)
	{
		m_nCnt++;
		if (m_nCnt <= 70)
		{
			CBillboard::SetChangeSize(2.0f);
		}
		CBillboard::SetSpin(0.05f);
	}
}

//==============================================
//					�`�揈��
//==============================================
void CPolygon3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���u�����f�B���O�����Z�����ɐݒ�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillboard::Draw();

	//���u�����f�B���O�����ɖ߂�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==============================================
//			�O����񂩂�e�N�X�`���̓ǂݍ���
//==============================================
HRESULT CPolygon3D::TextureLoad(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�K�v�e�N�X�`���̓ǂݍ���
	for (int nCnt = 0; nCnt < POLYGON3D_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, m_apTexName[nCnt], &m_apTexture[nCnt]);
	}

	return S_OK;

}
//==============================================
//				�e�N�X�`���̔j��
//==============================================
void CPolygon3D::TextureUnLoad(void)
{
	for (int nCnt = 0; nCnt < POLYGON3D_MAX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
