//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					�v���C���[���� [player.h]
//			Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "sceneX.h"
#include "game.h"
//==============================================
//					�}�N����`
//==============================================
#define MODEL_UV	("DATA/TEXTURE/MODEL/player.png")

//�v���C���[�X�e�[�^�X
#define PLAYER_SPEED	(2.2f)
#define PLAYER_GRAVITY	(0.5f)
#define PLAYER_PARTS		(11)
#define PLAYER_MAX_PATTERN		(10)
#define PLAYER_JUMP	(7.0f)

//==============================================
//					�O���錾
//==============================================
class CSound;
class CModel;
class CScene3D;
class CObject;
class CEnemy;
//==============================================
//			�V�[��X�̔h�� �� �v���C���[
//==============================================
class CPlayer : public CScene
{
public:
	//���f�����Ƃ̈ʒu�A��]
	typedef struct
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	}KEY;

	//�L�[���
	typedef struct
	{
		int nFrame;
		KEY aKey[PLAYER_PARTS];//���f���̃p�[�c��
	}KEY_INFO;

	//���[�V�������
	typedef struct
	{
		int nLoop;
		int nNumKey;
		KEY_INFO aKeyInfo[PLAYER_MAX_PATTERN];//���[�V�����̐�
	}MOTION_INFO;

	typedef enum
	{
		NEUTRAL = 0,
		WALK,
		RANKING,
		EVENT,
		WINDOW,
		WINDOW_WAIT,
		MOTION_MAX
	}MOTION_TYPE;

	typedef enum
	{
		LEFT = 0,
		RIGHT,
		FRONT,
		BACK,
		JUDGE_MAX
	}JUDGE_COLL;

	typedef enum
	{
		OBJ = 0,
		ENEMY,
		TYPE_MAX
	}COLL_TYPE;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CPlayer(int nPriority = DRAW_MODEL, DATA_TYPE nObjType = DATA_TYPE_PLAYER);
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					��Պ֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					�ǉ��֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	void CurrentMode();		//���݂̃��[�h�ɂ���ď���ύX����
	void Gravity(void);
	void MOVE(void);		//�v���C���[�̈ړ�����
	void JUMP(void);		//�v���C���[�̃W�����v����
	void Polygon3D(void);
	void CollObj(void);		//�I�u�W�F�N�g�Ƃ̓����蔻��
	void CollEnemy(void);	//�I�u�W�F�N�g�Ƃ̓����蔻��
	void LadderEvent(void);	//��q�̃C�x���g
	void SetDamageAction(float fX,float fY,int nType);	//�_���[�W���󂯂��ۂ̉��o(�^�C�v�͓G�Ȃ̂��A�M�~�b�Nobj��)
	void TitleEvent(void);	//�^�C�g�����̉��o
	void NULLCheck(void);   //�ꊇNULL�� / ������
	void Debug(void);		//�f�o�b�N�p

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			���f���EUV�̓ǂݍ���  /���
	// @   @   @   @   @   @   @   @   @   @   @   @
	static HRESULT ModelLoad(void);
	static void ModelUnLoad(void);
	static HRESULT TextureLoad(void);
	static void TextureUnLoad(void);
	
	// @   @   @   @   @   @   @   @   @   @   @   @
	//					���[�V�����֘A
	// @   @   @   @   @   @   @   @   @   @   @   @
	void ModelLode(void);							//���f���̓ǂݍ���
	void MotionLoad(void);							//���[�V�����̓ǂݍ���
	void UpdateMotion(void);						//���[�V�����̍X�V

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	void SetPos(D3DXVECTOR3 pos);
	void SetDamageState(int nType, bool bState);
	void SetKnockBack(int nState);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	D3DXVECTOR3 GetPos(void) {return m_pos; }		//�ʒu
	D3DXVECTOR3 GetMove(void) { return m_move; }	//�ړ���
	D3DXVECTOR3 GetRot(void) { return m_rot; }		//����
	int GetSideObjNum(void) { return m_nCurrentSideObj; }
	bool GetSide(int nCnt) { return m_bObjSide[nCnt]; }
	int GetCurrentObj(void) { return m_nCurrentObj; }
	bool GetOutStage(void) { return m_bOutStage; }
	bool GetAutoJump(void) { return m_bAutoJump; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_posOld;					//�ߋ��̈ʒu���
	D3DXVECTOR3 m_move;						//�ړ�
	D3DXVECTOR3 m_rot;						//����
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X

	//�������̃|�C���^
	static CSound *m_pSound;
	CCamera *m_pCamera;
	CScene3D *m_pScene3D[SCENE3D_CREATE];
	CObject *m_pObj;
	CEnemy * m_pEnemy;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			���f���̓ǂݍ��݁E�e�q�֌W
	// @   @   @   @   @   @   @   @   @   @   @   @
	CModel *m_pModel[PLAYER_PARTS];
	static LPD3DXMESH m_pMesh[PLAYER_PARTS];
	static LPD3DXBUFFER m_pBuffMat[PLAYER_PARTS];
	static DWORD m_pNumMat[PLAYER_PARTS];
	static int m_nNumModel;//���f���p�[�c��
	static char m_aFileNameModel[PLAYER_PARTS][256];//�ǂݍ��ރ��f����

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				���[�V�����Ɋւ�����
	// @   @   @   @   @   @   @   @   @   @   @   @
	int m_nNumKey;				//�L�[�̑���
	KEY_INFO *m_pKeyInfo;		//�L�[���̃|�C���^
	int m_nKey;					//���݂̃L�[
	int m_nCntFrame;			//���[�V�����J�E���^�[
	static int m_nNumParts;		//�p�[�c��
	static int m_aIndexParent[PLAYER_PARTS];
	static KEY m_aKeyOffseet[PLAYER_PARTS];
	MOTION_INFO m_aMotionInfo[MOTION_MAX];		//���[�V�����ő吔
	KEY_INFO m_aKeyInfo000[PLAYER_MAX_PATTERN];	//���[�V�����̎��
	MOTION_TYPE	motionType;						//�����̃��[�V����
	int  m_nUseMotionType;						//�g�p���郂�[�V����(�����ł͐��l�����̃��[�V�����ɕύX�����邽�߂ɉ��Z���Ă������������邽��int�^��)
	bool m_bLoopCheck;							//���[�v���邩���Ȃ����̃`�F�b�N

	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//�v���C���[�����ɏ���Ă���̂�?
	bool m_bPolygon3DCheck[SCENE3D_CREATE];			//�|���S���ɏ���Ă��邩?
	int m_nCurrent3DPolygon;				//���݃v���C���[���ǂ�3D�|���S���ɏ���Ă��邩
	bool m_bMeshcheck;				//���b�V���ɏ���Ă��邩?
	bool m_bObjRide[OBJ_CREATE];	//obj�ɏ���Ă��邩?
	int m_nCurrentObj;				//���݃v���C���[���ǂ̃u���b�N�ɏ���Ă��邩
	bool m_bObjSide[OBJ_CREATE];	//obj�̉��ɂ��邩
	int m_nCurrentSideObj;			//���݃v���C���[���ǂ̃u���b�N�̉��ɂ��邩
	bool m_bEnemyRide[ENEMY_CREATE];	//�G�l�~�[�ɏ���Ă��邩?
	int m_nCurrentEnemy;				//���݃v���C���[���ǂ̃u���b�N�ɏ���Ă��邩
	bool m_bScene3DRide;

	float m_fRotation;	//�v���C���[�̎���]
	D3DXVECTOR3 m_Sabun;//���炩�ȕ����]���̂��߂Ɏg��

	bool m_bDamageState[TYPE_MAX];//�_���[�W���󂯂Ă��邩?

	int m_nKnockBack;//�O�㍶�E�ǂ���Ń_���[�W���󂯂���?
	int m_nStateCnt;//��Ԃ̌p��

	bool m_bAutoMove;//�C�x���g�ɂ���Ď����ňړ�������

	bool m_bLadderFlag;//��q�C�x���g

	bool m_bBlockUpCheck;//�㉺������

	bool m_bOutStage;//�X�e�[�W�O�ɂȂ����ꍇ
	int m_nReTime;//�ċN�̎���
	
	//�^�C�g�����̉��o
	int m_nTitleEventCnt;
	bool m_bTitleEvent;
	bool m_bStop;

	bool m_bAutoJump;
};




#endif