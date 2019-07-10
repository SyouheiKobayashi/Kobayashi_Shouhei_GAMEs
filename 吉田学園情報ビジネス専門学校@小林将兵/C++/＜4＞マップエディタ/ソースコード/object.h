//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�I�u�W�F�N�g�������� [object.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _OBJECT_H_
#define _OBJECT_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "sceneX.h"

//==============================================
//�}�N����`
//==============================================
#define OBJ_TEXT ("DATA\\TEXT\\OBJ_LODE.txt")
#define OBJ_TEXTURE_NUM	(64)

//�I�u�W�F�N�g�̓����蔻��␳���l
#define OBJ_X	(0.0f)
#define OBJ_Y	(0.0f)
#define OBJ_Z	(0.0f)
#define OBJ_UNDER	(28)

//�I�u�W�F�N�g�g�p��
#define MAX_OBJECT	(256)

//==============================================
//�V�[��X�̔h�� �� �I�u�W�F�N�g
//==============================================
class CObject : public CSceneX
{
public:
	/*typedef enum
	{
		OBJ_TYPE00 = 0,
		OBJ_TYPE01,
		OBJ_TYPE_MAX
	}OBJ_TYPE;*/

	//�R���X�g���N�^ / �f�X�g���N�^
	CObject(int nPriority = DRAW_OBJECT, DATA_TYPE dataType = DATA_TYPE_OBJECT);
	~CObject();
	
	//����
	static CObject *Create(int nObjType, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Debug(void);

	//�����蔻��Ɋւ��鏈����
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,
		D3DXVECTOR3 *pMove);

	//�g�p����w�I�u�W�F�N�g�x�̓ǂݍ���
	static HRESULT ObjectLoad(void);
	static void ObjectUnLoad(void);

	//�I�u�W�F�N�g�Ɂw�g�p����摜�x�̓ǂݍ���
	static HRESULT TextureLoad(void);
	static void TextureUnLoad(void);

	//Get�֐�(���g�ň��������𑼂̃v���O�����Ŏg�p���鏈��)
	static int GetCreateNum(void) { return m_nCreateNum; }
	//static OBJ_TYPE GetObjType(void) { return m_objType; }


private:
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
	static int m_objType;							//�g�p����I�u�W�F�N�g�̃f�[�^�ԍ�
	static LPD3DXMESH m_pMesh[MAX_OBJECT];
	static LPD3DXBUFFER m_pBuffMat[MAX_OBJECT];
	static DWORD m_pNumMat[MAX_OBJECT];

	//�����蔻��ɕK�v�ȏ���
	D3DXVECTOR3 m_VtxMin;
	D3DXVECTOR3 m_VtxMax;

	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;

	//�������ꂽ���̋L��
	static int m_nCreateNum;
};




#endif