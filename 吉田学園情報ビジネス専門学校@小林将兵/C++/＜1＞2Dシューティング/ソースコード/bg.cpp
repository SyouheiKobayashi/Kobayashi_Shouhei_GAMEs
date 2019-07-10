//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �w�i���� [bg.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "bg.h"
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"
#include "time.h"
#include "game.h"

//�}�N��
#define TEXTURE_NAME01	("DATA\\TEX\\bg\\bg_towards.jpg")//���V
#define TEXTURE_NAME02	("DATA\\TEX\\bg\\BG00.png")//�钠
#define TEXTURE_NAME03	("DATA\\TEX\\bg\\BG01.png")//�L���L��
#define TEXTURE_NAME04	("DATA\\TEX\\bg\\BG02.png")//�R
#define TEXTURE_NAME05	("DATA\\TEX\\bg\\BG03.png")//�n��
#define TEXTURE_NAME06	("DATA\\TEX\\bg\\BG04.png")//�X

//�ÓI�ϐ�
LPDIRECT3DTEXTURE9 CBG::m_aTexture[MAX_TEXTURE] = {};
//! =============================================================================
//! �R���X�g���N�^
//! =============================================================================
#if 1
CBG::CBG() :CScene(OBJ_DRAW::DRAW_BG)
{
	//! <�l���N���A�ȏ�Ԃɂ���>
	
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
	}

	m_nScrollCnt = NULL;
}
#endif
//! =============================================================================
//! �f�X�g���N�^
//! =============================================================================
#if 1
CBG::~CBG()
{
	
}
#endif
//! =============================================================================
//! Tex�ǂݍ���
//! =============================================================================
HRESULT CBG::Load(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_aTexture[0]);//��
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME02, &m_aTexture[1]);//��
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME03, &m_aTexture[2]);//�L���L��
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME04, &m_aTexture[3]);//�R
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME05, &m_aTexture[4]);//�n��
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME06, &m_aTexture[5]);//�X


	return S_OK;
}
//! =============================================================================
//! �g�pTex�̔j��
//! =============================================================================
void CBG::UnLoad(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (m_aTexture[nCnt] != NULL)
		{
			m_aTexture[nCnt]->Release();
			m_aTexture[nCnt] = NULL;
		}
	}
}

//! =============================================================================
//! ��������
//! =============================================================================
CBG *CBG::Create(void)
{
	CBG *pBG = NULL;
	if (pBG == NULL)
	{
		pBG = new CBG;
		pBG->Init();
	}
	return pBG;
}
//! =============================================================================
//! ������
//! =============================================================================
HRESULT CBG::Init(void)
{
	

	SetObjType(CScene::OBJTYPE_BG);//�^�C�v�𓖂Ă͂߂�

	m_nScrollCnt = NULL;

	/*cManager::MODE pMode = cManager::GetMode();
	if (pMode == cManager::MODE_TITLE)
	{
	}*/
		for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
		{
			m_apScene2D[nCnt] = new CScene2D(OBJ_DRAW::DRAW_BG);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_aTexture[nCnt]);
		}

	return S_OK;
}
//! =============================================================================
//! �I��
//! =============================================================================
void CBG::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
		m_apScene2D[nCnt] = NULL;
	}
	//�������g��delete	<Scene>��delete�������g�p
	Release();
}
//! =============================================================================
//! �X�V
//! =============================================================================
void CBG::Update(void)
{
	m_nScrollCnt--;
	m_apScene2D[0]->SetScroll(0.0005f, m_nScrollCnt,2);//(�X�N���[�����x,���Zor���Z,1=�c 2=��)
	m_apScene2D[1]->SetScroll(0.0005f, m_nScrollCnt, 2);
	m_apScene2D[2]->SetScroll(0.00015f, m_nScrollCnt, 2);
	m_apScene2D[3]->SetScroll(0.0003f, m_nScrollCnt, 2);
	m_apScene2D[4]->SetScroll(0.0015f, m_nScrollCnt, 2);
	m_apScene2D[5]->SetScroll(0.0015f, m_nScrollCnt, 2);

	//m_apScene2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	CManager::MODE mode;
	mode = CManager::GetMode();
	if (mode == CManager::MODE_GAME)
	{
		CTime *pTime = CGame::GetTime();
		
		int nTimeNow = pTime->GetTimeNow();
		float nTime = nTimeNow*0.001f;
		m_apScene2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, nTime-0.5f));
		m_apScene2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, nTime-0.5f));
	}
}
//! =============================================================================
//! �`��
//! =============================================================================
void CBG::Draw(void)
{
	
}
//! =============================================================================
//! pos / �ʒu�X�V
//! =============================================================================
void CBG::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ʏ�\���w�i(�T�C�Y�ω��A��]�Ȃ�,�e.cpp�ŃT�C�Y�̏���������)
	pVtx[0].pos = D3DXVECTOR3(-100, -100, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+100, -100, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-100, +100, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(+100, +100, 0.0f) + m_pos;


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}