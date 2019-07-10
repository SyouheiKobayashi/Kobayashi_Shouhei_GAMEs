//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					2D�e�N�X�`������ [Tex2D.cpp]
//			Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "polygon2D.h"
#include "manager.h"
#include "camera.h"
#include "input.h"
#include "debugLog.h"
#include "game.h"

//==============================================
//				�ÓI�����o�ϐ�
//==============================================
const char *CPolygon2D::m_apTexName[] =
{
	//�^�C�g��
	"DATA/TEXTURE/UI/TITLE01.png",//0
	"DATA/TEXTURE/UI/TITLE02.png",
	"DATA/TEXTURE/UI/TITLE03.png",
	"DATA/TEXTURE/UI/TITLE04.png",
	"DATA/TEXTURE/UI/TITLE05.png",
	"DATA/TEXTURE/UI/TITLE06.png",
	//�^�C���`���[�W
	"DATA/TEXTURE/UI/TIME_CHARGE01.png",//6
	"DATA/TEXTURE/UI/TIME_CHARGE02.png",
	"DATA/TEXTURE/UI/TIME_CHARGE03.png",
	"DATA/TEXTURE/UI/TIME_CHARGE04.jpg",
	"DATA/TEXTURE/UI/TIME_CHARGE05.jpg",
	//�Q�[��
	"DATA/TEXTURE/STAGE03_CRASH.png",
	//�����L���O
	"DATA/TEXTURE/UI/RANKING_01.png",//12
	"DATA/TEXTURE/UI/RANKING_02.png",

	//�^�C���`���[�W
	"DATA/TEXTURE/UI/TIME_CHARGE06.png",//����
	"DATA/TEXTURE/UI/TIME_CHARGE07.jpg",	//������ 15

	//�Q�[��
	"DATA/TEXTURE/UI/GAME_UI01.png",
	"DATA/TEXTURE/UI/GAME_UI02.png",
	"DATA/TEXTURE/UI/GAME_UI03.jpg",
	"DATA/TEXTURE/UI/GAME_UI04.jpg",
	"DATA/TEXTURE/UI/GAME_UI05.jpg",//20
	"DATA/TEXTURE/UI/GAME_UI06.png",

	//���U���g
	"DATA/TEXTURE/UI/RESULT01.jpg",
	"DATA/TEXTURE/UI/RESULT02.jpg",

	"DATA/TEXTURE/UI/TITLE00.png",
	"DATA/TEXTURE/UI/GAME_UI07.jpg",//25
	"DATA/TEXTURE/UI/GAME_UI08.jpg"//26
};

LPDIRECT3DTEXTURE9 CPolygon2D::m_apTexture[POLYGON2D_MAX] = {};

//==============================================
//					�R���X�g���N�^
//==============================================
CPolygon2D::CPolygon2D(int nPriority, DATA_TYPE dataType) :CScene2D(nPriority, dataType)
{
	//m_pVtxBuff = NULL;
}
//==============================================
//					�f�X�g���N�^
//==============================================
CPolygon2D::~CPolygon2D()
{

}

//==============================================
//						����
//==============================================
CPolygon2D *CPolygon2D::Create(int nTexType, bool bRotation, D3DXVECTOR3 pos, D3DXCOLOR col, float nSizeX, float nSizeY, 
								int nAnimSpeed, int nWidth, int nHight, bool bLoop)
{
	CPolygon2D *pPolygon2D = NULL;

	if (pPolygon2D == NULL)
	{
		pPolygon2D = new CPolygon2D;
		pPolygon2D->m_nPolygonType = nTexType;
		pPolygon2D->m_bRotation = bRotation;
		pPolygon2D->BindTexture(m_apTexture[nTexType]);
		pPolygon2D->SetPos(pos);
		pPolygon2D->SetCol(col);
		pPolygon2D->SetSize(nSizeX, nSizeY);
		pPolygon2D->m_nAnimSpeed = nAnimSpeed;
		pPolygon2D->m_nWidth = nWidth;
		pPolygon2D->m_nHight = nHight;
		pPolygon2D->m_bLoop = bLoop;
		pPolygon2D->Init();
	}
	return pPolygon2D;
}
//==============================================
//				����������
//==============================================
HRESULT CPolygon2D::Init(void)
{
	CScene2D::Init();

	return S_OK;
}
//==============================================
//				�I������
//==============================================
void CPolygon2D::Uninit(void)
{
	CScene2D::Uninit();

}

//==============================================
//				�X�V����
//==============================================
void CPolygon2D::Update(void)
{
	if (m_bRotation == true)
	{
		SetSpin(0.05f);
	}
	if (m_nPolygonType == 6)
	{
		CScene2D::SetAnimSize(4.0f,18);
	}
	if (m_nPolygonType == 7)
	{
		if (CScene2D::GetPos().x <= 650.0f)
		{
			CScene2D::SetMove(D3DXVECTOR3(30.0f, 0.0f, 0.0f));
		}
	}
	if (m_nPolygonType == 8 || m_nPolygonType == 24)
	{
		CScene2D::FlashTex();
	}
	if (m_nPolygonType == 9|| m_nPolygonType == 10 || m_nPolygonType == 16 || m_nPolygonType == 17)
	{
		CScene2D::SetScroll(0.004f,true,0);
	}
	if (m_nPolygonType == 14 || m_nPolygonType == 18 || m_nPolygonType == 19 || m_nPolygonType == 20)
	{
		CScene2D::SetTexAnim(m_nAnimSpeed, m_nWidth, m_nHight, m_bLoop);
	}
	Debug();
}

//==============================================
//					�`�揈��
//==============================================
void CPolygon2D::Draw(void)
{
	CScene2D::Draw();
}

//==============================================
//				�摜�̓ǂݍ���
//==============================================
HRESULT CPolygon2D::TextureLoad(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�K�v�e�N�X�`���̓ǂݍ���
	for (int nCnt = 0; nCnt < POLYGON2D_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, m_apTexName[nCnt], &m_apTexture[nCnt]);
	}

	return S_OK;
}

//==============================================
//			�@�@�摜�̉��
//==============================================
void CPolygon2D::TextureUnLoad(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < POLYGON2D_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//==============================================
//					�f�o�b�N�p����
//==============================================
void CPolygon2D::Debug(void)
{

	CDebug::DebugLog("\n2DTex��XXX�ʒu %f", GetPos().x);
	CDebug::DebugLog("\n2DTex��YYY�ʒu %f", GetPos().y);
}