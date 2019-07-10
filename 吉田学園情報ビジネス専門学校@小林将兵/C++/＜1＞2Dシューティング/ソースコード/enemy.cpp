//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �G�E�G�l�~�[���� [enemy.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "input.h"
#include "enemy.h"
#include "bullet.h"

//�}�N��
//�ǂݍ��ރe�N�X�`����
#define ENEMY_TEX01	("DATA\\runningman000.png")
#define ENEMY_TEX02	("DATA\\IMG_0011.png")
#define ENEMY_TEX03	("DATA\\TEX\\enemy\\enemy003.png")
#define ENEMY_TEX04	("DATA\\TEX\\enemy\\enemy000.png")
#define ENEMY_TEX05	("DATA\\TEX\\enemy\\enemy001.png")
#define ENEMY_TEX06	("DATA\\TEX\\enemy\\enemy004.png")
//�G�E�G�l�~�[�̃T�C�Y��
#define E_SIZE_H	(30)
#define E_SIZE_W	(30)
//�e�E�o���b�g�̃A�j���[�V�����ݒ聫
#define	E_ANIM_SPEED	(5)//�A�j���[�V��������
#define	E_ANIM_W	(8)//������
#define	E_ANIM_H	(1)//�c����
//�G�E�G�l�~�[�̍U���Ԋu��
#define E_INTERVAL	(70)
//�ÓI�����o�ϐ�
CBullet *CEnemy::m_pBullet = NULL;
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[ENEMY_ALL] = {};

//! =============================================================================
//! �R���X�g���N�^
//! =============================================================================
CEnemy::CEnemy() :CScene2D(OBJ_DRAW::DRAW_ENEMY)
{
	m_CntAnim = 0;//�A�j���[�V�����̑���
	m_PatternAnim = 0;//�A�j���[�V�����̕�����

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	m_nIntervalAttack = 0;

	m_nEnemyType = 0;

	m_nRndPattern = rand() % 3;

	
}

//! =============================================================================
//! �f�X�g���N�^
//! =============================================================================
CEnemy::~CEnemy()
{

}

//! =============================================================================
//! Tex�ǂݍ���
//! =============================================================================
HRESULT CEnemy::Load(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX01, &m_pTexture[ENEMY01]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX02, &m_pTexture[ENEMY02]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX03, &m_pTexture[ENEMY03]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX04, &m_pTexture[ENEMY04]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX05, &m_pTexture[ENEMY05]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX06, &m_pTexture[ENEMY_BOSS]);

	return S_OK;
}
//! =============================================================================
//!�@Tex�j���@
//! =============================================================================
void CEnemy::UnLoad(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0;nCnt <ENEMY_ALL;nCnt++)
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
CEnemy *CEnemy::Create(int nType,int X_pos, int Y_pos, int Life)
{
	CEnemy *pEnemy = NULL;
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;
		pEnemy->Init(nType);
		pEnemy->BindTexture(m_pTexture[nType]);
		pEnemy->SetSize(E_SIZE_H, E_SIZE_W);//�G�E�G�l�~�[�̃T�C�Y
		pEnemy->SetPos(D3DXVECTOR3((float)X_pos, (float)Y_pos, 0.0f));//�G�E�G�l�~�[�����ʒu
		pEnemy->SetLife(Life);
	}
	return pEnemy;
}
#endif

//! =============================================================================
//!�@������
//! =============================================================================
HRESULT CEnemy::Init(int nType)
{
	CScene2D::Init();

	CScene::SetObjType(OBJ_TYPE::OBJTYPE_ENEMY);//�^�C�v�𓖂Ă͂߂�
	
	m_CntAnim = 0;//�A�j���[�V�����̑���
	m_PatternAnim = 0;//�A�j���[�V�����̕�����

	//m_move = D3DXVECTOR3(0.0f, -5.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	m_nIntervalAttack = 0;

	m_nEnemyType = nType;

	m_nRndPattern = rand() % 3;

	

	return S_OK;
}

//! =============================================================================
//! �I��
//! =============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//! =============================================================================
//! �X�V
//! =============================================================================
void CEnemy::Update(void)
{
	CScene2D::Update();
	EnemyPattern();
	//�L�[�{�[�h���g�p���邽�߂̏�����
	//cInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//�G�E�G�l�~�[�̈ʒu���̏������s�����߂̏�����
	D3DXVECTOR3 pos = CScene2D::GetPos();

	//! <�G�E�G�l�~�[�̃A�j���[�V��������>
	m_CntAnim++; //�J�E���^�[�̉��Z �����̑��x
	if (m_nEnemyType == 0)
	{
		if (m_CntAnim % E_ANIM_SPEED == 0)
		{
			m_PatternAnim = (m_PatternAnim + 1) % (E_ANIM_W * E_ANIM_H);//�p�^�[��No.�X�V
		}

		CScene2D::SetTexAnim(E_ANIM_SPEED, E_ANIM_W, E_ANIM_H, m_PatternAnim);

		if (m_PatternAnim >= (E_ANIM_W * E_ANIM_H) - 1)
		{
			m_PatternAnim = 0;
		}
	}
	//! <�G�E�G�l�~�[�̍��E�ړ����邾���̏���>
	//pos.y += m_move.y;
	/*if (pos.y <= 0)
	{
		m_move.y = 5.0f;
		pos.y += m_move.y;
	}
	if (SCREEN_HEIGHT <= pos.y)
	{
		m_move.y = -5.0f;
		pos.y += m_move.y;
	}*/


	//�|���ꂸ��ʊO�ɏo���ꍇ...
	if (pos.x < -5)
	{
		
		CScene2D::Uninit();
	}
	else if (pos.y < -90)
	{

		CScene2D::Uninit();
	}
	else if (pos.y > SCREEN_HEIGHT+90)
	{

		CScene2D::Uninit();
	}

#if 1

	//! <�G�E�G�l�~�[�̒e�̔��ˏ���>
	
	//if (m_nEnemyType == 0)
	//{
	//	if (m_nIntervalAttack % E_INTERVAL == 0)
	//	{
	//		//�e�̐���(bullet�����̌Ăяo��)//(�����ʒu,�e�̃T�C�Y,�^�C�v�̔���,�g�pTex�̔ԍ�)
	//		m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1);
	//		//cBullet::Create(pos + D3DXVECTOR3(-20.0f, -15.0f, 0.0f), CScene::OBJTYPE_ENEMY);
	//	}
	//}

	//if (m_nEnemyType == 1)
	//{
	//	if (m_nIntervalAttack % E_INTERVAL-10 == 0)
	//	{
	//		//�e�̐���(bullet�����̌Ăяo��)//(�����ʒu,�e�̃T�C�Y,�^�C�v�̔���,�g�pTex�̔ԍ�)
	//		m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 7.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1);
	//		m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, -7.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1);
	//	}
	//}
#endif

	
}

//! =============================================================================
//! �`��
//! =============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//! =============================================================================
//! �G�̍U�� / �ړ��p�^�[��
//! =============================================================================
void CEnemy::EnemyPattern(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPos();//�G�ʒu�擾
	m_nIntervalAttack++;
	

	switch (m_nEnemyType)//�^�C�v�̔���
	{
	case ENEMY01:

		pos += D3DXVECTOR3(-5.0f, 0.0f, 0.0f);//�ړ�


		if (m_nIntervalAttack % 60 == 0)//�U���Ԋu
		{
			//�e�̐���(bullet�����̌Ăяo��)//(�����ʒu,�e�̃T�C�Y,�^�C�v�̔���,�g�pTex�̔ԍ�)
			m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN01);
		}
		break;
		//! =============================================================================
	case ENEMY02:

		//�ړ��p�^�[��
		if (m_nRndPattern == 0)//�^������
		{
			pos += D3DXVECTOR3(-8.0f, 0.0f, 0.0f);
			//�U���Ԋu
			if (m_nIntervalAttack % 70 == 0)
			{
				//�e�̐���(bullet�����̌Ăяo��)//(�����ʒu,�e�̃T�C�Y,�^�C�v�̔���,�g�pTex�̔ԍ�)
				m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN02);
			}

		}
		if (m_nRndPattern == 1)//����
		{

			pos += D3DXVECTOR3(-8.0f, D3DX_PI, 0.0f);
			//�U���Ԋu
			if (m_nIntervalAttack % 70 == 0)
			{
				//�e�̐���(bullet�����̌Ăяo��)//(�����ʒu,�e�̃T�C�Y,�^�C�v�̔���,�g�pTex�̔ԍ�)
				m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN04);
			}
		}
		if (m_nRndPattern == 2)//���
		{
			pos += D3DXVECTOR3(-8.0f, -D3DX_PI, 0.0f);
			//�U���Ԋu
			if (m_nIntervalAttack % 70 == 0)
			{
				//�e�̐���(bullet�����̌Ăяo��)//(�����ʒu,�e�̃T�C�Y,�^�C�v�̔���,�g�pTex�̔ԍ�)
				m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN03);
			}
		}
		
		
		break;
		//! =============================================================================
	case ENEMY03:
		//�ړ��p�^�[��
		
			pos += D3DXVECTOR3(-6.0f, 0.0f, 0.0f);
		//�U���Ԋu
		if (m_nIntervalAttack % 80 == 0)
		{
			//�e�̐���(bullet�����̌Ăяo��)//(�����ʒu,�e�̃T�C�Y,�^�C�v�̔���,�g�pTex�̔ԍ�)
			m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN05);
			//cBullet::Create(pos + D3DXVECTOR3(-20.0f, -15.0f, 0.0f), CScene::OBJTYPE_ENEMY);
		}
		break;

//! =============================================================================
	case ENEMY04:

		pos += D3DXVECTOR3(0.0f, -11.0f, 0.0f);
		//�U���Ԋu
		if (m_nIntervalAttack % 10-(rand() % 4) == 0)
		{
			//�e�̐���(bullet�����̌Ăяo��)//(�����ʒu,�e�̃T�C�Y,�^�C�v�̔���,�g�pTex�̔ԍ�)
			if (210 < pos.x)
			{
				m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN06);
			}
			else
			{
				m_pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN07);

			}
			//cBullet::Create(pos + D3DXVECTOR3(-20.0f, -15.0f, 0.0f), CScene::OBJTYPE_ENEMY);
		}
		break;
		//! =============================================================================

	case ENEMY05:

		pos += D3DXVECTOR3(-8.0f, 0.0f, 0.0f);
		//�U���Ԋu
		if (m_nIntervalAttack % 10 - (rand() % 4) == 0)
		{
			//�e�̐���(bullet�����̌Ăяo��)//(�����ʒu,�e�̃T�C�Y,�^�C�v�̔���,�g�pTex�̔ԍ�)

			CBullet::Create(pos + D3DXVECTOR3(0.0f, 3.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN08);
			CBullet::Create(pos + D3DXVECTOR3(0.0f, -3.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN09);

		}
		break;
		//! =============================================================================

	case ENEMY_BOSS:

		pos += D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		//�U���Ԋu
		if (m_nIntervalAttack % 50 - (rand() % 4) == 0)
		{
			//�e�̐���(bullet�����̌Ăяo��)//(�����ʒu,�e�̃T�C�Y,�^�C�v�̔���,�g�pTex�̔ԍ�)
			for (int nCnt = 0; nCnt < 30; nCnt++)
			{
				CBullet::Create(pos + D3DXVECTOR3(0.0f, 7.0f - (rand() % 10), 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN08);
				CBullet::Create(pos + D3DXVECTOR3(0.0f, -7.0f + (rand() % 10), 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN09);

			}
			//CBullet::Create(pos + D3DXVECTOR3(0.0f, -3.0f, 0.0f), 10, CScene::OBJTYPE_ENEMY, CBullet::TYPE::ENEMY, 1, CBullet::PATTERN09);

		}
		break;
	}
	

	CScene2D::SetPos(pos);//�ړ��ʔ��f
}
