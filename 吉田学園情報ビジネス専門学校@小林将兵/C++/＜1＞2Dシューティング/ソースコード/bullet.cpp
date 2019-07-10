//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �e�E�o���b�g���� [bullet.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "input.h"
#include "game.h"
#include "sound.h"
#include "player.h"
#include "bullet.h"
#include "effect.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "bloodGauge.h"
#include "fade.h"
#include "pause.h"

//�}�N��
//�ǂݍ��ރe�N�X�`����
#define TEXTURE_NAME01	("DATA\\bullet001.png")
#define TEXTURE_NAME02	("DATA\\star00.png")
//�e�E�o���b�g�̃T�C�Y��
#define B_SIZE_H	(10.0f)
#define B_SIZE_W	(10.0f)
//�e�E�o���b�g�̑��x��
#define PB_SPEED	(10.0f)
#define EB_SPEED	(-10.0f)

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_B_TEX] = {};
//! =============================================================================
//! �R���X�g���N�^
//! =============================================================================
CBullet::CBullet() :CScene2D(OBJ_DRAW::DRAW_BULLET)
{
	m_BulletType = OBJTYPE_NONE;
	m_nRType = NONE;
	m_nBulletPattern = PATTERN01;

	m_PlayerPos = D3DXVECTOR3(0,0,0);
	m_EnemyPos = D3DXVECTOR3(0, 0, 0);
}

//! =============================================================================
//! �f�X�g���N�^
//! =============================================================================
CBullet::~CBullet()
{

}

//! =============================================================================
//! �ǂݍ���
//! =============================================================================
HRESULT CBullet::Load(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME02, &m_pTexture[1]);

	return S_OK;
}
//! =============================================================================
//! Tex�j��
//! =============================================================================
void CBullet::UnLoad(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_B_TEX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//! =============================================================================
//! ����
//! =============================================================================
#if 1
CBullet *CBullet::Create(D3DXVECTOR3 pos,int size, OBJ_TYPE ObjType, TYPE type,int nTexType, BULLET_PATTERN pattern)
{

	CBullet *pBullet = NULL;
	if (pBullet == NULL)
	{
		pBullet = new CBullet;
		pBullet->Init(pattern);
		pBullet->SetBulletType(ObjType, type);//�e�̃^�C�v����
		pBullet->SetSize(B_SIZE_H+ size, B_SIZE_W + size);//�e�̃T�C�Y
		pBullet->SetPos(pos);////�v���C���[�̈ړ����(�ύX�E�X�V)������
		pBullet->BindTexture(m_pTexture[nTexType]);
		pBullet->m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	return pBullet;
}
#endif

//! =============================================================================
//! ������
//! =============================================================================
HRESULT CBullet::Init(BULLET_PATTERN pattern)
{
	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_BULLET);//�^�C�v�𓖂Ă͂߂�
	//m_nRType = NONE;
	m_bPause = false;

	/*CEnemy *pEnemyType = CGame::GetEnemy();
	m_nBulletPattern = pEnemyType->GetEnemyType();*/

	m_nBulletPattern = pattern;

	m_PlayerPos = D3DXVECTOR3(0, 0, 0);
	m_EnemyPos = D3DXVECTOR3(0, 0, 0);

	return S_OK;
}

//! =============================================================================
//! �I��
//! =============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();

}
//! =============================================================================
//! �X�V
//! =============================================================================
void CBullet::Update(void)
{
	CScene2D::Update();
	int nLife = 0;
	int nBloodLife = 0;
	
	CSound *pSound = CManager::GetSound();
	D3DXVECTOR3 pos = CScene2D::GetPos();//�v���C���[�̈ʒu���擾
	

//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �v���C���[�̒e�ł���Ȃ火
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
	if(m_BulletType == CScene::OBJTYPE_PLAYER)
	{
	
		if (m_nBulletPattern == PATTERN_PLAYER)
		{
			m_move.x = 10.0f;
			pos += m_move;//�擾�����ʒu�Ɉړ��ʂ����Z����
			CScene2D::SetPos(pos);//�e�̈ړ��𔽉f����

			CEffect::Create(pos + D3DXVECTOR3(0.0f, 3.0f, 0.0f), D3DXCOLOR(0.5f, 0.0f, 0.7f, 1.0f));
			CEffect::Create(pos + D3DXVECTOR3(0.0f, -3.0f, 0.0f), D3DXCOLOR(0.5f, 0.0f, 0.7f, 1.0f));
		}
		//! �e�̉�ʊO������
		if (SCREEN_WIDTH < pos.x)
		{
			CScene2D::Uninit();
		}
	}

//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �G�̒e�ł���Ȃ火
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
	if (m_BulletType == CScene::OBJTYPE_ENEMY)
	{
		if (m_nBulletPattern == PATTERN01)//�꒼��
		{
			m_move.x = -12;
			pos += m_move;//�擾�����ʒu�Ɉړ��ʂ����Z����
		}
		if (m_nBulletPattern == PATTERN02)//�قڈ꒼��
		{
			m_move.x = -12;
			m_move.y = -2 + (float)(rand() % 4);
			pos += m_move;//�擾�����ʒu�Ɉړ��ʂ����Z����
		}

		if (m_nBulletPattern == PATTERN03)
		{
			m_move.x = -10.0f;
			m_move.y = 7.0f;
			pos += m_move;//�擾�����ʒu�Ɉړ��ʂ����Z����
		}

		if (m_nBulletPattern == PATTERN04)
		{
			m_move.x = -10.0f;
			m_move.y = -7.0f;
			pos += m_move;//�擾�����ʒu�Ɉړ��ʂ����Z����
		}
		
		if (m_nBulletPattern == PATTERN05)//�ォ��̍U��
		{
			m_move.x = -2.0f;
			m_move.y = 10.0f;
			pos += m_move;//�擾�����ʒu�Ɉړ��ʂ����Z����
			CEffect::Create(pos + D3DXVECTOR3(2.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}

		if (m_nBulletPattern == PATTERN06)
		{
			m_move.x = (-15.0f+(rand() % -3));
			
			pos += m_move;//�擾�����ʒu�Ɉړ��ʂ����Z����
		}
		if (m_nBulletPattern == PATTERN07)
		{
			m_move.x = (+15.0f + (rand() % -3));

			pos += m_move;//�擾�����ʒu�Ɉړ��ʂ����Z����
		}

		if (m_nBulletPattern == PATTERN08)
		{
			m_move.x = -15;
			m_move.y = -1 + (float)(rand() % -6);

			pos += m_move;//�擾�����ʒu�Ɉړ��ʂ����Z����
		}
		if (m_nBulletPattern == PATTERN09)
		{
			m_move.x = -15;
			m_move.y = 1 + (float)(rand() % 6);

			pos += m_move;//�擾�����ʒu�Ɉړ��ʂ����Z����
		}
		CScene2D::SetPos(pos);//�e�ړ����f
							  //! *���̏�������ɒe���������������Ȃ��I�I

		//��ʊO����					  
		if (pos.x < 0)
		{
			
			CScene2D::Uninit();
		}
		else if (pos.y < 0|| SCREEN_HEIGHT < pos.y)
		{
			CScene2D::Uninit();
		}
		
	}

//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �����蔻�菈��
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

	//��obj�����̊l��&&�g����悤�Ƀ��[�J���ɏ���^����
	int NumAll = CScene::GetNumAll();

	for (int nCntP = 0; nCntP < OBJ_DRAW::DRAW_ALL; nCntP++)//�p�ӂ��ꂽobj��for����
	{
		for (int nCnt = 0; nCnt < NumAll; nCnt++)//�p�ӂ��ꂽobj��for����
		{
			CScene *pScene;
			pScene = CScene::GetScene(nCntP, nCnt);

			if (pScene != NULL)
			{
				CScene::OBJ_TYPE ObjType;
				ObjType = pScene->GetObjType();//�^�C�v�̊m�F

				//! ���@�Ƃ̂����蔻��
				if (ObjType == OBJ_TYPE::OBJTYPE_PLAYER)//�v���C���[obj�Ȃ�
				{
					CScene2D *pPlayer = (CScene2D*)pScene;//CScene2D��GetPos���g����悤�ɃL���X�g(�ϊ�)����
					D3DXVECTOR3 PlayerPos = pPlayer->GetPos();//�G�̈ʒu���擾
					nLife = pPlayer->GetLife();//�v���C���[�̗̑͂��擾


					if (PlayerPos.x - B_SIZE_W*2.0f < pos.x && pos.x < PlayerPos.x + B_SIZE_W*2.0f
						&& PlayerPos.y - B_SIZE_H*4.0f < pos.y&& pos.y < PlayerPos.y + B_SIZE_H*4.0f)
					{
						if (m_BulletType == OBJ_TYPE::OBJTYPE_ENEMY&&m_nRType == ENEMY)//! �G�̒e�ł����
						{
							CExplosion::Create(PlayerPos);//���@�̈ʒu�Ŕ����A�j���[�V����
							pSound->PlaySound(CSound::SOUND_DAMAGE_SE);
							nLife -= 1;//���炷
							CLife *pLife = CGame::GetLife();//�v���C���[�̃��C�t���擾
							pLife->SetLife(nLife);



							if (nLife <= 0)
							{
								nLife = 0;
								//pScene->Uninit();//�����ď���
								//pSound->PlaySound(CSound::SOUND_DELETE_SE);
								pPlayer->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

							}

							this->Release();//�������g(�e)������
							pPlayer->SetLife(nLife);
						}
					}

				}

				//! �G�Ƃ̂����蔻��
				if (ObjType == OBJ_TYPE::OBJTYPE_ENEMY)//�Gobj�Ȃ�
				{
					CScene2D *pEnemy = (CScene2D*)pScene;//CScene2D��GetPos���g����悤�ɃL���X�g(�ϊ�)����
					D3DXVECTOR3 EnemyPos = pEnemy->GetPos();//�G�̈ʒu���擾
					nLife = pEnemy->GetLife();//�G�̗̑͂��擾


					CPlayer *pPlayer = CGame::GetPlayer();
					nBloodLife = pPlayer->GetBloodLife();


					//! �͈�
					if (EnemyPos.x - B_SIZE_W*3.0f < pos.x && pos.x < EnemyPos.x + B_SIZE_W*3.0f
						&& EnemyPos.y - B_SIZE_H*5.0f < pos.y&& pos.y < EnemyPos.y + B_SIZE_H*5.0f)
					{
						if (m_BulletType == OBJ_TYPE::OBJTYPE_PLAYER &&m_nRType == PLAYER)//! ���@�̒e�ł����
						{
							CExplosion::Create(EnemyPos);//�G�̈ʒu�Ŕ����A�j���[�V����

							pSound->PlaySound(CSound::SOUND_DAMAGE_SE);
							nLife -= 1;//���炷
							if (nLife <= 0)
							{
								CScore *pScore = CGame::GetScore();
								pScore->AddScore(800);
								nBloodLife += 2;
								pSound->PlaySound(CSound::SOUND_DELETE_SE);
								pEnemy->Uninit();
							}


							this->Release();//�e������

							pEnemy->SetLife(nLife);
							pPlayer->SetBloodLife(nBloodLife);
						}
					}

				}
			}
		}
	}

	
}

//! =============================================================================
//! �`��
//! =============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//! =============================================================================
//! �e��łL���� / �g�pTex�ԍ�
//! =============================================================================
void CBullet::SetBulletType(OBJ_TYPE ObjType, TYPE type)
{
	m_BulletType = ObjType;
	m_nRType = type;
}
