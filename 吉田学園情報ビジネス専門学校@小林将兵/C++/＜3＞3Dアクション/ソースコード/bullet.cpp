//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//				�o���b�g���� [bullet.cpp]
//			Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "sound.h"
#include "input.h"
#include "debugLog.h"
#include "game.h"
#include "bullet.h"
#include "polygon3D.h"
#include "scene3D.h"
#include "player.h"
#include "time.h"

//==============================================
//				�ÓI�����o�ϐ�
//==============================================
const char *CBullet::m_apTexName[] =
{
	"DATA/TEXTURE/bullet01.png",	//0
	"DATA/TEXTURE/WINDOW.png"
};

LPDIRECT3DTEXTURE9 CBullet::m_apTexture[BULLET_TEX_MAX] = {};
CSound *CBullet::m_pSound = NULL;

//==============================================
//					�R���X�g���N�^
//==============================================
CBullet::CBullet(int nPriority, DATA_TYPE dataType) :CBillboard(nPriority, dataType)
{

}

//==============================================
//					�f�X�g���N�^
//==============================================
CBullet::~CBullet()
{

}

//==============================================
//					����
//==============================================
CBullet *CBullet::Create(int nLife, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nTexType, int nAnimSpeed, int nWidth, int nHight, bool bLoop)
 {

	CBullet *pTex3D = NULL;
	if (pTex3D == NULL)
	{
		pTex3D = new CBullet;
		pTex3D->m_nLife = nLife;//�\������(����)
		pTex3D->SetPos(pos);
		pTex3D->SetRot(rot);
		pTex3D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pTex3D->SetSize(size);
		pTex3D->m_nType = nTexType;
		pTex3D->BindTexture(m_apTexture[nTexType]);
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
HRESULT CBullet::Init(void)
{
	m_pSound = CManager::GetSound();
	m_pPlayer = NULL;
	CBillboard::Init();

	return S_OK;
}

//==============================================
//				�I������
//==============================================
void CBullet::Uninit(void)
{
	/*if (m_pSound != NULL)
	{
		m_pSound->StopSound();
	}*/
	CBillboard::Uninit();
}

//==============================================
//				�X�V����
//==============================================
void CBullet::Update(void)
{
	CBillboard::SetTexAnim(m_nAnimSpeed, m_nWidth, m_nHight, m_bLoop);

	//�ʒu�X�V
	D3DXVECTOR3 bulletPos = GetPos();


	if (m_nType == 0)
	{
		bulletPos.x -= 2.0f;
		SetPos(bulletPos);
		m_pPlayer = CGame::GetPlayer();
		if (m_pPlayer != NULL)
		{
			D3DXVECTOR3 playerPos = m_pPlayer->GetPos();
			if (GetPos().x + 10.0f > playerPos.x / 2.0f && GetPos().x - 10.0f < playerPos.x / 2.0f && GetPos().y + playerPos.y / 2 >= playerPos.y && GetPos().y - playerPos.y / 2 <= playerPos.y && GetPos().z > playerPos.z / 2.0f)
			{
				CDebug::DebugLog("\n�q�b�g");
				if (m_pSound != NULL)
				{
					m_pSound->PlaySound(CSound::SE_BULLET_DAMAGE);
				}
				CTime *pTime = CGame::GetTime();
				pTime->SetDemeritTime(3);//�_���[�W����
				CPolygon3D::Create(0, D3DXVECTOR3(playerPos.x / 2.0f, playerPos.y / 2.0f + 10.0f, playerPos.z - 10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), 2, 4, 3, false);
				Uninit();
			}
		}
	}
	else
	{
		bulletPos.x -= 3.0f;
		SetPos(bulletPos);
	}
	m_nLife--;
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//==============================================
//					�`�揈��
//==============================================
void CBullet::Draw(void)
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
HRESULT CBullet::TextureLoad(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�K�v�e�N�X�`���̓ǂݍ���
	for (int nCnt = 0; nCnt < BULLET_TEX_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, m_apTexName[nCnt], &m_apTexture[nCnt]);
	}

	return S_OK;

}
//==============================================
//				�e�N�X�`���̔j��
//==============================================
void CBullet::TextureUnLoad(void)
{
	for (int nCnt = 0; nCnt < BULLET_TEX_MAX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
