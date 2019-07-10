//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//						�Q�[������ [game.h]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _GAME_H_
#define _GAME_H_

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "manager.h"
#include "fade.h"

//==============================================
//					�}�N����`
//==============================================
#define ENEMY_CREATE	(5)
#define POLYGON3D_CREATE	(6)
#define SCENE3D_CREATE	(5)
#define POLYGON2D_TEX_GAME	(8)
#define DEFAULT_TIME	(50)

//==============================================
//					�O���錾
//==============================================
class CDebug;
class CSound;
class CLight;
class CCamera;
class CScene2D;
class CPolygon2D;
class CScene3D;
class CPolygon3D;
class CBullet;
class CParticle3D;
class CNumber;
class CScore;
class CTime;
class CStencilShadow;
class CObject;
class CPlayer;
class CEnemy;

//==============================================
//						�Q�[��
//==============================================
class CGame
{
public:
	//�ǂݍ��񂾃I�u�W�F�N�g�̌����A�ʒu
	typedef struct
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	}OBJECT;

	typedef enum
	{
		STAGE_01 = 0,
		STAGE_02,
		STAGE_03,
		STAGE_MAX
	}STAGE_NUMBER;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CGame();
	~CGame();
	static CGame *Create();

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					��Պ֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					�ǉ��֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	void NullCheck(void);
	void BulkLoadData(void);	//���f���A�e�N�X�`���̓ǂݍ���
	void BulkUnLoadData(void);	//���f���A�e�N�X�`���̉��
	void MAP_LOAD(void);		//�}�b�v���̓ǂݍ���
	void CreateData(void);		//(�ǂݍ��܂ꂽ)���f���A�I�u�W�F�N�g�̐���
	void Debug(void);			//�f�o�b�N�p
	void DebugLoop(void);
	void SwitchFlag();			//�X�e�[�W��̃X�C�b�`�����ׂĉ����ꂽ��
	void GameModeCheck();		//�Q�[���̏�Ԃ��`�F�b�N
	void EventStage01();		//�X�e�[�W01�p�C�x���g
	void EventStage02();		//�X�e�[�W02�p�C�x���g
	void EventStage03();		//�X�e�[�W03�p�C�x���g

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	static void SetSwitchFlagNum();//�X�C�b�`�����������̂�

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	static CDebug *GetDebug(void) { return m_pDebug; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CPolygon2D *GetPolygon2D(int nCnt) { return m_pPolygon2D[nCnt]; }
	static CScene3D *GetScene3D(int nCnt) { return m_pScene3D[nCnt]; }
	static CPolygon3D *GetPolygon3D(int nCnt) { return m_pPolygon3D[nCnt]; }
	static CBullet *GetBullet(void) { return m_pBullet; }
	static CParticle3D *GetParticle3D(void) { return m_pParticle3D; }
	static CNumber *GetNumber(void) { return m_pNumber; }
	static CScore *GetScore(void) { return m_pScore; }
	static CTime *GetTime(void) { return m_pTime; }
	static CStencilShadow *GetStencilShadow(void) { return m_pStencilShadow; }
	static CObject *GetObj(int nCnt) { return m_pObject[nCnt]; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CEnemy *GetEnemy(int nCnt) { return m_pEnemy[nCnt];}

	bool GetNextStage(void) {return bNextStage;}
	static int GetStageCnt(void) { return m_nStageCnt; }
	static bool GetDivided(void) { return m_bDivided; }
	static bool GetDivided02(void) { return m_bDivided02; }
	static bool GetPageStop(void) { return m_bPageStop; }
	static bool GetDeath(void) { return m_bDeath; }

private:
	static CDebug *m_pDebug;
	static CSound *m_pSound;
	static CLight *m_pLight;
	static CCamera *m_pCamera;
	static CScene2D *m_pScene2D;
	static CPolygon2D *m_pPolygon2D[POLYGON2D_TEX_GAME];
	static CScene3D *m_pScene3D[SCENE3D_CREATE];
	static CPolygon3D * m_pPolygon3D[POLYGON3D_CREATE];
	static CBullet *m_pBullet;
	static CParticle3D *m_pParticle3D;
	static CNumber *m_pNumber;
	static CScore * m_pScore;
	static CTime * m_pTime;
	static CStencilShadow *m_pStencilShadow;
	static CObject *m_pObject[OBJ_CREATE];
	static CPlayer *m_pPlayer;
	static CEnemy *m_pEnemy[ENEMY_CREATE];


	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//��ʑJ�ڏ���
	CFade::FADE m_pFade;

	//�O���f�[�^����ǂݍ��񂾏���ۊ�
	FILE *m_pFile;
	int m_nMaxObjCreateNum;
	int m_nObjType[50];
	int m_nTexType[50];
	OBJECT m_ObjOffseet[50];

	static int m_nStageCnt;//�X�e�[�W���Ǘ�����ϐ�

	static int m_nSwitchFlagNum;//�X�C�b�`���N��������
	bool bNextStage;			//���̃X�e�[�W�Ɉړ��\���`�F�b�N

	//�`���[�g���A��(STAGE1�p)
	int m_nPageCnt;
	static bool m_bPageStop;

	//(STAGE2�p)
	//�e�̕ϐ�
	float m_fBillCnt;
	int m_BulletTime;
	//�����ꓹ
	static bool m_bDivided;		//�s��
	static bool m_bDivided02;	//�߂蓹

	//�Q�[���I�[�o�[���o
	int m_nFadeTime;
	static bool m_bDeath;//���S��Ԃ̊m�F

	//�f�o�b�N�p
	int m_nCreateCnt;
	int m_nDebugCnt;

};

#endif

