//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �A�N�V�������� [action.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "input.h"
#include "game.h"
#include "player.h"
#include "action.h"
#include "bullet.h"
#include "effect.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "bloodGauge.h"

//�}�N��
//�ǂݍ��ރe�N�X�`����
#define TEXTURE_NAME01	("DATA\\��02.png")
//�A�N�V�����̃T�C�Y��
#define B_SIZE_H	(10.0f)
#define B_SIZE_W	(10.0f)
//�A�N�V�����̑��x��
#define PB_SPEED	(10.0f)
#define EB_SPEED	(-10.0f)

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CAction::m_pTexture[ACTION_TEX] = {};
//! =============================================================================
//! �R���X�g���N�^
//! =============================================================================
CAction::CAction() :CScene2D(OBJ_DRAW::DRAW_BULLET)
{
	m_ActionType = OBJTYPE_NONE;

	m_nActionTime = 0;

	 m_fAngle = (D3DX_PI);//�p�x
	 m_fActionAngle = 0.0f;//�������@�ɑ΂��ē����p�x
}
//! =============================================================================
//! �f�X�g���N�^
//! =============================================================================
CAction::~CAction()
{

}

//! =============================================================================
//! Tex�ǂݍ���
//! =============================================================================
HRESULT CAction::Load(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture[0]);

	return S_OK;
}
//! =============================================================================
//! �g�pTex�̔j��
//! =============================================================================
void CAction::UnLoad(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < ACTION_TEX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//! =============================================================================
//! ��������
//! =============================================================================
#if 1
CAction *CAction::Create(D3DXVECTOR3 pos,OBJ_TYPE ObjType)
{

	CAction *pAction = NULL;
	if (pAction == NULL)
	{
		pAction = new CAction;
		pAction->Init();
		pAction->SetBulletType(ObjType);//�e�̃^�C�v����
		pAction->SetSize(B_SIZE_H+500, B_SIZE_W+500 );//�e�̃T�C�Y
		pAction->SetPos(pos);////�v���C���[�̈ړ����(�ύX�E�X�V)������
		pAction->BindTexture(m_pTexture[0]);
		pAction->m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pAction->m_fRange = 300;//�~�̑傫��
		pAction->m_fActionAngle = 10.01f;
	}
	
	return pAction;
}
#endif

//! =============================================================================
//! ������
//! =============================================================================
HRESULT CAction::Init(void)
{
	CScene2D::Init();
	//SetObjType(CScene::OBJTYPE_BULLET);//�^�C�v�𓖂Ă͂߂�

	m_nActionTime = 0;

	return S_OK;
}
//! =============================================================================
//! �I��
//! =============================================================================
void CAction::Uninit(void)
{
	CScene2D::Uninit();

}
//! =============================================================================
//! �X�V
//! =============================================================================
void CAction::Update(void)
{
	CScene2D::Update();
	int nLife = 0;
	int nBloodLife = 0;


	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 SicklePos = CAction::GetPos();//���̈ʒu���擾

	//D3DXVECTOR3 EnemyBulletPos = CEnemy::GetBullet()->GetPos();

	m_nActionTime += 1;//�\�����Ԃ̉��Z
	m_fActionAngle += 0.18f;//�ʂ�`��(�~�ړ�)����

	SicklePos.x = m_fRange*(float)sin(m_fAngle - m_fActionAngle) + (PlayerPos.x);
	SicklePos.y = m_fRange*(float)cos(m_fAngle - m_fActionAngle) + (PlayerPos.y);

	//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
	// �v���C���[�̒e�ł���Ȃ火
	//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
	if (m_ActionType == CScene::OBJTYPE_PLAYER)
	{

		SicklePos += m_move;//�擾�����ʒu�Ɉړ��ʂ����Z����
		CScene2D::SetPos(SicklePos);//�e�̈ړ��𔽉f����
		CScene2D::SetRot(-0.2f);
		/*CEffect::Create(SicklePos + D3DXVECTOR3(0.0f, 30.0f, 0.0f), D3DXCOLOR(0.5f, 0.0f, 0.7f, 1.0f));
		CEffect::Create(SicklePos + D3DXVECTOR3(0.0f, -30.0f, 0.0f), D3DXCOLOR(0.5f, 0.0f, 0.7f, 1.0f));*/


		//! �e�̉�ʊO������
		if (SCREEN_WIDTH < PlayerPos.x)
		{
			//CExplosion::Create(pos);
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

				//! �G�Ƃ̂����蔻��
				if (ObjType == OBJ_TYPE::OBJTYPE_ENEMY)//�Gobj�Ȃ�
				{
					CScene2D *pEnemy = (CScene2D*)pScene;//CScene2D��GetPos���g����悤�ɃL���X�g(�ϊ�)����
					D3DXVECTOR3 EnemyPos = pEnemy->GetPos();//�G�̈ʒu���擾
					nLife = pEnemy->GetLife();//�G�̗̑͂��擾

					CPlayer *pPlayer = CGame::GetPlayer();
					nBloodLife = pPlayer->GetBloodLife();

					//! �Z�͈͓̔��ɓ�������...
					if (EnemyPos.x - B_SIZE_W*25.0f < SicklePos.x && SicklePos.x < EnemyPos.x + B_SIZE_W*10.0f
						&& EnemyPos.y - B_SIZE_H*10.0f < SicklePos.y&& SicklePos.y < EnemyPos.y + B_SIZE_H*10.0f)
					{
						if (m_ActionType == OBJ_TYPE::OBJTYPE_PLAYER)//! ���@�̋Z�ł����
						{
							nLife -= 100;//���炷

							if (nLife <= 0)
							{
								CScore *pScore = CGame::GetScore();
								pScore->AddScore(100);
								nBloodLife += 1;
								CExplosion::Create(EnemyPos);//�G�̈ʒu�Ŕ����A�j���[�V����
								pScene->Uninit();//�����ď���
							}

							pEnemy->SetLife(nLife);
							pPlayer->SetBloodLife(nBloodLife);
						}
					}
				}

				//! �e�Ƃ̂����蔻��
				CScene2D *pScene2D = (CScene2D*)pScene;//Scene2D�ɃL���X�g
				CBullet *pBullet = (CBullet*)pScene2D;//Bullet�ɃL���X�g
				int nB = pBullet->GetType();
				if (ObjType == OBJ_TYPE::OBJTYPE_BULLET)//�Gobj�Ȃ�
				{
					CScene2D *pBullet = (CScene2D*)pScene;//CScene2D��GetPos���g����悤�ɃL���X�g(�ϊ�)����
					D3DXVECTOR3 BulletPos = pBullet->GetPos();//�e�̈ʒu���擾


					//! �Z�͈͓̔��ɓ�������...
					if (BulletPos.x - B_SIZE_W*25.0f < SicklePos.x && SicklePos.x < BulletPos.x + B_SIZE_W*10.0f
						&& BulletPos.y - B_SIZE_H*10.0f < SicklePos.y&& SicklePos.y < BulletPos.y + B_SIZE_H*10.0f)
					{
						if (nB == CBullet::TYPE::ENEMY)
						{
							if (m_ActionType == OBJ_TYPE::OBJTYPE_PLAYER)//! ���@�̋Z�ł����
							{
								CScore *pScore = CGame::GetScore();
								pScore->AddScore(234);
								pBullet->Uninit();
							}
						}

					}

				}

			}
		}
	}

	if (45 <= m_nActionTime)
	{
		this->Uninit();//�������g(�e)������(����if���ɓ����Ɗђʒe���ǂ�)
	}
}

//! =============================================================================
//! �`��
//! =============================================================================
void CAction::Draw(void)
{
	CScene2D::Draw();
}

//! =============================================================================
//! �e�̎�ޔ��ʏ���
//! =============================================================================
void CAction::SetBulletType(OBJ_TYPE ObjType)
{
	m_ActionType = ObjType;
}
