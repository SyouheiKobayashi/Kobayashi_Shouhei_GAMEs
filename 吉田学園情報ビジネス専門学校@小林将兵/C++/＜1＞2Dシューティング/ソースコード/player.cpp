//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �v���C���[���� [player.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "manager.h"
#include "input.h"
#include "game.h"
#include "sound.h"
#include "UI.h"
#include "life.h"
#include "bloodGauge.h"
#include "player.h"
#include "bullet.h"
#include "action.h"
#include "time.h"
#include "explosion.h"

//�}�N��
//�ǂݍ��ރe�N�X�`����
#define TEXTURE_NAME01	("DATA\\TEX\\player_Anim01.png")
//�v���C���[�̃T�C�Y��
#define P_SIZE_H	(45)//�c�T�C�Y
#define P_SIZE_W	(45)//���T�C�Y
//�e�E�o���b�g�̃A�j���[�V�����ݒ聫
#define	P_ANIM_SPEED	(12)//�A�j���[�V��������
#define	P_ANIM_W	(4)//������
#define	P_ANIM_H	(1)//�c����

//�ÓI�����o�ϐ�
CAction *CPlayer::m_pAction = NULL;
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
//=============================================================================
//+ �v���C���[�̃R���X�g���N�^
//=============================================================================
CPlayer::CPlayer() :CScene2D(OBJ_DRAW::DRAW_PLAYER)
{
	m_Move = D3DXVECTOR3(8.0f,8.0f,0.0f);
	m_CntAnim = 0;//�A�j���[�V�����̑���
	m_PatternAnim = 0;//�A�j���[�V�����̕�����
	m_nBloodLife = 0;
	m_nActionPos = 0;

	m_nActionMode = CURE;
	m_bUse01 = false;
	m_bUse02 = false;
	m_bUse03 = false;
	m_bTimeCheck = false;
}

//=============================================================================
//+ �v���C���[�̃f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}
//=============================================================================
//+ �v���C���[�̕K�v���ǂݍ���
//=============================================================================
HRESULT CPlayer::Load(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture);

	return S_OK;
}
//=============================================================================
//+ �v���C���[�𑼂̏����ɂ��폜�������Ȃ�
//=============================================================================
void CPlayer::UnLoad(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//+ �v���C���[�̐�������
//=============================================================================
#if 1
CPlayer *CPlayer::Create(float fWIDTH, float fHEIGHT, int nLife)
{
	CPlayer *pPlayer = NULL;
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
		pPlayer->Init();
		pPlayer->BindTexture(m_pTexture);
		pPlayer->SetSize(P_SIZE_H, P_SIZE_W);//�v���C���[�̃T�C�Y
		pPlayer->SetPos(D3DXVECTOR3(150.0f, 250.0f, 0.0f));//�v���C���[�����ʒu
		pPlayer->SetLife(nLife);

	
		//cLife�̃��C�t�ݒ菈��
		CLife * pLife = CGame::GetLife();
		pLife->SetLife(nLife);

	}
	return pPlayer;
}
#endif

//=============================================================================
//+ �v���C���[�̏���������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	CScene2D::Init();
	m_Move = D3DXVECTOR3(8.0f, 8.0f, 0.0f);
	SetObjType(CScene::OBJTYPE_PLAYER);//�^�C�v�𓖂Ă͂߂�
	m_CntAnim = 0;//�A�j���[�V�����̑���
	m_PatternAnim = 0;//�A�j���[�V�����̕�����
	m_nActionPos = 0;
	return S_OK;
}

//=============================================================================
//+ �v���C���[�̏I������
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
	
}

//=============================================================================
//+ �v���C���[�̍X�V����
//=============================================================================
void CPlayer::Update(void)
{
	CScene2D::Update();
	
	
	int nLife = 0;

	CTime *pTime = CGame::GetTime();
	int nTimeNow = pTime->GetTimeNow();

	//�L�[�{�[�h���g�p���邽�߂̏�����
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//�Q�[���p�b�h�Ă�
	CInputXPad *pInputXPad = CManager::GetInputXPad();

	CSound *pSound = CManager::GetSound();
	//�v���C���[�̈ړ��������s�����߂̏�����
	D3DXVECTOR3 pos = CScene2D::GetPos();

	
	
	bool bPlayerFlag = pTime->GetPlayerFlag();
	if (bPlayerFlag == true)
	{

		//! <�v���C���[�̈ړ�����>
		if (pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || pInputKeyboard->GetPress(DIK_W) == true)
		{
			pos.y -= m_Move.y;
			if (pos.y < 25)
			{
				pos.y = 25;
			}
		}
		
		if (pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true || pInputKeyboard->GetPress(DIK_S) == true)
		{
			pos.y += m_Move.y;
			if (SCREEN_HEIGHT - 120 < pos.y)
			{
				pos.y = SCREEN_HEIGHT - 120;
			}

		}
		if (pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == true || pInputKeyboard->GetPress(DIK_A) == true)
		{
			pos.x -= m_Move.x;
			if (pos.x <= 25)
			{
				pos.x = 25;
			}
		}
		if (pInputXPad->GetPress(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true || pInputKeyboard->GetPress(DIK_D) == true)
		{
			pos.x += m_Move.x;
			if (SCREEN_WIDTH-25< pos.x)
			{
				pos.x = SCREEN_WIDTH-25;
			}

		}

		//�v���C���[�̈ړ����(�ύX�E�X�V)�̏�����
		CScene2D::SetPos(pos);

		//! <�v���C���[�̃A�j���[�V��������>
		m_CntAnim++; //�J�E���^�[�̉��Z �����̑��x
		if (m_CntAnim % P_ANIM_SPEED == 0)
		{
			m_PatternAnim = (m_PatternAnim + 1) % (P_ANIM_W * P_ANIM_H);//�p�^�[��No.�X�V
		}

		CScene2D::SetTexAnim(P_ANIM_SPEED, P_ANIM_W, P_ANIM_H, m_PatternAnim);

		if (m_PatternAnim >= (P_ANIM_W * P_ANIM_H) - 1)
		{
			m_PatternAnim = 0;
		}

		//! <�v���C���[�̒e�̔��ˏ���>
		if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_B, 0) == true || pInputKeyboard->GetTrigger(DIK_SPACE) == true)
		{
				//�e�̐���(bullet�����̌Ăяo��)//(�����ʒu,�e�̃T�C�Y,�^�C�v�̔���,�g�pTex�̔ԍ�)
				CBullet::Create(pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), 10, CScene::OBJTYPE_PLAYER, CBullet::TYPE::PLAYER, 0, CBullet::PATTERN_PLAYER);
				CBullet::Create(pos + D3DXVECTOR3(0.0f, -20.0f, 0.0f), 10, CScene::OBJTYPE_PLAYER, CBullet::TYPE::PLAYER, 0, CBullet::PATTERN_PLAYER);
				pSound->PlaySound(CSound::SOUND_BULLET_SE);
			
		}

		//�Z�̑I������
		if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER, 0) == true || pInputKeyboard->GetTrigger(DIK_E) == true)
		{
			pSound->PlaySound(CSound::SOUND_SWITCH_SE);
				m_nActionMode += 1;
				if (m_nActionMode > SICKLE)
				{
					m_nActionMode = CURE;
				}
			
		}
		if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_LEFT_SHOULDER, 0) == true || pInputKeyboard->GetTrigger(DIK_Q) == true)
		{
			pSound->PlaySound(CSound::SOUND_SWITCH_SE);
				m_nActionMode -= 1;
				if (m_nActionMode < CURE)
				{
					m_nActionMode = SICKLE;
				}
		}

		//��
		if (m_nBloodLife >= 3)//���t�Q�[�W��3�ȏ�ł���...
		{
			m_bUse01 = true;//�g�����Ԃ�
		}
		else if (m_nBloodLife < 3)
		{
			m_bUse01 = false;//�g���Ȃ���Ԃ�
		}

		//����
		if (m_nBloodLife >= 5)//���t�Q�[�W��5�ȏ�ł���...
		{
			m_bUse02 = true;//�g�����Ԃ�
		}
		else if (m_nBloodLife < 5)
		{
			m_bUse02 = false;//�g���Ȃ���Ԃ�
		}

		//�U��
		if (m_nBloodLife >= 10)//���t�Q�[�W��10�ȏ�ł���...
		{
			m_bUse03 = true;//�g�����Ԃ�

		}
		else if (m_nBloodLife < 10)
		{
			m_bUse03 = false;//�g���Ȃ���Ԃ�
		}
		if (m_nBloodLife >= 15)//���t�Q�[�W��10�ȏ�ł���...
		{
			m_nBloodLife = 15;//�g�����Ԃ�
		}

		if (pInputXPad->GetTrigger(XINPUT_GAMEPAD_Y, 0) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			{
				//<�񕜋Z>���g������...
				if (m_nActionMode == CURE)//�����̈�v...
				{
					if (m_nBloodLife >= 3)//���t�Q�[�W��3�ȏ�ł���...
					{
						if (m_bUse01 == true)
						{
							int NumAll = CScene::GetNumAll();//�����̊l��
							for (int nCntP = 0; nCntP < OBJ_DRAW::DRAW_ALL; nCntP++)//�`�摍������
							{
								for (int nCnt = 0; nCnt < NumAll; nCnt++)//��������
								{
									CScene *pScene;
									pScene = CScene::GetScene(nCntP, nCnt);//�S�V�[�����̎擾

									if (pScene != NULL)
									{
										CScene::OBJ_TYPE ObjType;
										ObjType = pScene->GetObjType();//�^�C�v���̎擾


										if (ObjType == OBJ_TYPE::OBJTYPE_PLAYER)//�^�C�v���v���C���[�Ȃ�...
										{
											CScene2D *pPlayer = (CScene2D*)pScene;//CScene2D�̎����Ă����񂪗~�����̂ŃL���X�g
											nLife = pPlayer->GetLife();//�v���C���[�̃��C�t���擾

											nLife += 3;//�v���C���[�̃��C�t�ɒl�����Z����
											pSound->PlaySound(CSound::SOUND_ACTION_SE01);
											if (nLife >= 15)//�����ő僉�C�t�ȏ�̉񕜂������ꍇ
											{
												nLife = 15;//����z����h��
											}

											CLife *pLife = CGame::GetLife();//���C�t�Q�[�W(�`����)�Ɏg�p���邽�߂̏��擾
											pLife->SetLife(nLife);//�`����̔��f
											pPlayer->SetLife(nLife);//�v���C���[�̃��C�t�ɔ��f
										}
									}
								}
							}

							m_nBloodLife -= 3;
						}
					}
				}

				//<���ԑ���>���g������...
				if (m_nActionMode == ADD_TIME)//�����̈�v...
				{
					if (m_nBloodLife >= 5)//���t�Q�[�W��3�ȏ�ł���...
					{
						if (m_bUse02 == true)
						{
							if (nTimeNow > (1 * 100))
							{
								nTimeNow += (10 * 100);
								pTime->SetLife(nTimeNow);
								pSound->PlaySound(CSound::SOUND_ACTION_SE02);
								m_nBloodLife -= 5;

							}
						}
					}
				}

				//<�U���Z>���g������...
				if (m_nActionMode == SICKLE)//���l����v���Ă���
				{
					if (m_nBloodLife >= 10)//���t�Q�[�W��10�ȏ�ł���...
					{
						if (m_bUse03 == true)
						{
							//�A�N�V�����̐���(action�����̌Ăяo��)//(�����ʒu,�e�̃T�C�Y,�^�C�v�̔���,�g�pTex�̔ԍ�)
							CAction::Create(pos + D3DXVECTOR3(0.0f, -250.0f, 0.0f), CScene::OBJTYPE_PLAYER);
							
							pSound->PlaySound(CSound::SOUND_ACTION_SE03);
							m_nBloodLife -= 10;
						}
					}
				}
			}
		}

	}
}

//=============================================================================
//+ �v���C���[�̕`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//���t���̍X�V
void CPlayer::SetBloodLife(int nSetBloodLife)
{
	m_nBloodLife = nSetBloodLife;
	this;//�u���C�N���̒l�̊m�F�ɕ֗�
}
