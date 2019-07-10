//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					�G�l�~�[���� [enemy.h]
//			Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "sceneX.h"

//==============================================
//					�}�N����`
//==============================================
#define ENEMY01_UV	("DATA/TEXTURE/MODEL/enemy01.png")

//�v���C���[�X�e�[�^�X
#define ENEMY_SPEED	(1.5f)
#define ENEMY_GRAVITY	(0.5f)
#define ENEMY_PARTS		(11)
#define ENEMY_MAX_PATTERN		(10)
#define ENEMY_JUMP	(7.0f)

//==============================================
//					�O���錾
//==============================================
class CSound;
class CModel;
class CInputKeyboard;
class CInputXPad;
class CInputMouse;
class CPlayer;
//==============================================
//			�V�[��X�̔h�� �� �G�l�~�[
//==============================================
class CEnemy : public CScene
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
		KEY aKey[ENEMY_PARTS];//���f���̃p�[�c��
	}KEY_INFO;

	//���[�V�������
	typedef struct
	{
		int nLoop;
		int nNumKey;
		KEY_INFO aKeyInfo[ENEMY_MAX_PATTERN];//���[�V�����̐�
	}MOTION_INFO;

	typedef enum
	{
		NEUTRAL = 0,
		WALK,
		STOP,
		MOTION_MAX
	}MOTION_TYPE;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CEnemy(int nPriority = DRAW_MODEL, DATA_TYPE nObjType = DATA_TYPE_ENEMY);
	~CEnemy();
	static CEnemy *Create(int nAIType,D3DXVECTOR3 pos, D3DXVECTOR3 rot);

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
	void CurrentMode();//���݂̃��[�h�ɂ���ď���ύX����
	void Gravity(void);
	void MOVE(void);//�v���C���[�̈ړ�����
	void JUMP(void);//�v���C���[�̃W�����v����
	void CollObj(void);//�I�u�W�F�N�g�Ƃ̓����蔻��
	void TitleEvent(void);	//�^�C�g�����̉��o
	void NULLCheck(void);   //�ꊇNULL�� / ������
	void Debug(void);//�f�o�b�N�p

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
	//�����蔻��Ɋւ��鏈��
	void Vtx(void);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,
		D3DXVECTOR3 *pMove);
	void SetPos(D3DXVECTOR3 pos);
	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	static int GetCreateNum(void) { return m_nCreateNum; }

	D3DXVECTOR3 GetPos(void) {return m_pos; }		//�ʒu
	D3DXVECTOR3 GetMove(void) { return m_move; }	//�ړ���
	D3DXVECTOR3 GetRot(void) { return m_rot; }		//����
	bool GetSearchCheck(void) { return m_bSearchCheck; }//�G�l�~�[�͈͓���
	bool GetMoveStop(void) { return m_bMoveStop; }//�G���_���[�W���󂯂Ď~�܂��Ă��邩
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
	CObject *m_pObj;
	CPlayer * m_pPlayer;
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			���f���̓ǂݍ��݁E�e�q�֌W
	// @   @   @   @   @   @   @   @   @   @   @   @
	CModel *m_pModel[ENEMY_PARTS];
	static LPD3DXMESH m_pMesh[ENEMY_PARTS];
	static LPD3DXBUFFER m_pBuffMat[ENEMY_PARTS];
	static DWORD m_pNumMat[ENEMY_PARTS];
	static int m_nNumModel;//���f���p�[�c��
	static char m_aFileNameModel[ENEMY_PARTS][256];//�ǂݍ��ރ��f����

	// @   @   @   @   @   @   @   @   @   @   @   @
	//				���[�V�����Ɋւ�����
	// @   @   @   @   @   @   @   @   @   @   @   @
	int m_nNumKey;				//�L�[�̑���
	KEY_INFO *m_pKeyInfo;		//�L�[���̃|�C���^
	int m_nKey;					//���݂̃L�[
	int m_nCntFrame;			//���[�V�����J�E���^�[
	static int m_nNumParts;		//�p�[�c��
	static int m_aIndexParent[ENEMY_PARTS];
	static KEY m_aKeyOffseet[ENEMY_PARTS];
	MOTION_INFO m_aMotionInfo[MOTION_MAX];		//���[�V�����ő吔
	KEY_INFO m_aKeyInfo000[ENEMY_MAX_PATTERN];	//���[�V�����̎��
	MOTION_TYPE	motionType;						//�����̃��[�V����
	int  m_nUseMotionType;						//�g�p���郂�[�V����(�����ł͐��l�����̃��[�V�����ɕύX�����邽�߂ɉ��Z���Ă������������邽��int�^��)
	bool m_bLoopCheck;							//���[�v���邩���Ȃ����̃`�F�b�N

	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//�������ꂽ���̋L��
	static int m_nCreateNum;

	//�v���C���[�����ɏ���Ă���̂�?
	bool m_bMeshcheck;				//���b�V���ɏ���Ă��邩?
	bool m_bObjRide[OBJ_CREATE];	//obj�ɏ���Ă��邩?
	int m_nCurrentObj;				//���݃v���C���[���ǂ̃u���b�N�ɏ���Ă��邩
	bool m_bObjSide[OBJ_CREATE];	//obj�̉��ɂ��邩
	int m_nCurrentSideObj;			//���݃v���C���[���ǂ̃u���b�N�̉��ɂ��邩

	float m_fRotation;	//�v���C���[�̎���]
	D3DXVECTOR3 m_Sabun;//���炩�ȕ����]���̂��߂Ɏg��

	//�����蔻��ɕK�v�ȏ���
	D3DXVECTOR3 m_VtxMin;	//�ŏ��l
	D3DXVECTOR3 m_VtxMax;	//�ő�l
	bool m_bRide;			//��ɏ���Ă��邩�H
	
	D3DXVECTOR3 m_OriginPos;//�����n

	int m_nTitleEventCnt;//�^�C�g�����̉��o
	bool m_bTitleEvent;
	bool m_bStop;

	bool m_bSearchCheck;//�G�l�~�[�͈͓̔��ɓ����Ă��邩�H
	
	//���܂ꂽ�ۂ̏���
	bool	m_bMoveStop;
	int		m_MoveStopTime;

	int m_nAIType;//�s���p�^�[��
};




#endif