//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//			�I�u�W�F�N�g�������� [object.h]
//		Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _OBJECT_H_
#define _OBJECT_H_

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "sceneX.h"

class CInputKeyboard;
class CInputXPad;
class CInputMouse;
class CSound;
class CPlayer;
//==============================================
//					�}�N����`
//==============================================
#define OBJ_TEXT ("DATA\\TEXT\\OBJ_LODE.txt")
#define OBJ_TEXTURE_NUM	(64)

//�I�u�W�F�N�g�̓����蔻��␳���l
#define OBJ_X	(10.0f)
#define OBJ_Y	(0.0f)
#define OBJ_Z	(10.0f)
#define OBJ_UNDER	(28)

//�I�u�W�F�N�g�g�p��
#define MAX_OBJECT	(256)

//==============================================
//			�V�[��X�̔h�� �� �I�u�W�F�N�g
//==============================================
class CObject : public CSceneX
{
public:

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CObject(int nPriority = DRAW_OBJECT, DATA_TYPE dataType = DATA_TYPE_OBJECT);
	~CObject();
	static CObject *Create(int nObjType, int nTexType, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

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
	void SwitchFlag(void);	//�X�C�b�`�n�M�~�b�N
	void Gimmick(void);		//�M�~�b�N�����̂܂Ƃ�
	void Debug(void);
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�I�u�W�F�N�g�EUV�̓ǂݍ���  /���
	// @   @   @   @   @   @   @   @   @   @   @   @
	static HRESULT ObjectLoad(void);
	static void ObjectUnLoad(void);

	static HRESULT TextureLoad(void);
	static void TextureUnLoad(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	//�����蔻��Ɋւ��鏈����
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,//�㔻��
		D3DXVECTOR3 *pMove,int nType);

	bool CollSide(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,//������
		D3DXVECTOR3 *pMove, int nType);

	void SetRide(bool bRide);//����Ă��邩�m�F
	void SetGimmickFlag(bool bFlag);
	void SetLadderFlag(bool bFlag);
	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	static int GetCreateNum(void) { return m_nCreateNum; }
	bool GetSide(void) { return m_bSide; }
	static int GetSwitchNum(void) { return m_nSwitchNum; }
	bool GetLadderFlag(void) { return m_bLadderFlag; }
	bool GetBlockUP(void) { return m_bBlockUP; }
private:
	static CSound *m_pSound;
	CPlayer *m_pPlayer;

	static LPDIRECT3DTEXTURE9 m_pTexture[OBJ_TEXTURE_NUM];				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;									//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;													//�ʒu
	D3DXVECTOR3 m_move;													//�ړ�
	D3DXVECTOR3 m_rot;													//����

	//�O���f�[�^����̓ǂݍ��݂Ɏg�p����ϐ�
	static int m_nNumObject;							//�ǂݍ��ރI�u�W�F�N�g�̎�ސ�
	static int m_nNumTexture;							//�ǂݍ��މ摜�̐�
	static char m_aFileNameObject[MAX_OBJECT][256];		//�I�u�W�F�N�g�̖��O
	static char m_aFileNameTexture[MAX_OBJECT][256];	//�I�u�W�F�N�g�Ɏg�p����摜�EUV�̖��O

	//�I�u�W�F�N�g���
	int m_objType;							//�g�p����I�u�W�F�N�g�̃f�[�^�ԍ�
	static LPD3DXMESH m_pMesh[MAX_OBJECT];
	static LPD3DXBUFFER m_pBuffMat[MAX_OBJECT];
	static DWORD m_pNumMat[MAX_OBJECT];

	//�����蔻��ɕK�v�ȏ���
	D3DXVECTOR3 m_VtxMin;
	D3DXVECTOR3 m_VtxMax;

	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//�������ꂽ���̋L��
	static int m_nCreateNum;

	//��ɏ���Ă��邩�H
	bool m_bRide;
	//���ɐG��Ă��邩�H
	bool m_bSide;

	//�M�~�b�N�̃t���O
	bool m_bGimmickFlag;
	int m_nFlagTimeCnt;
	static int m_nSwitchNum;//�X�C�b�`�����������ꂽ��

	bool m_bLadderFlag;		//��q�̃M�~�b�N

	bool m_bBlockUP;		//�㉺�M�~�b�N
	int m_nUPCnt;

	bool m_bRotGimmick;		//��]�n�M�~�b�N�̋N��Check
	bool m_bDrillGimmick;	//�h�����M�~�b�N
	int m_nDrillCnt;

};




#endif