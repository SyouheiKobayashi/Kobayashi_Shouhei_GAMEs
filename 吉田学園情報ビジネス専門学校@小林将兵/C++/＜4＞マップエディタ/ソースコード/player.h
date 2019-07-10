//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�v���C���[���� [player.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "sceneX.h"
#include "input.h"
//==============================================
//�}�N����`
//==============================================
#define MODEL_UV	("DATA/TEXTURE/MODEL/player.png")

//�v���C���[�X�e�[�^�X
#define SAMPLE_OBJ_NUM	(32)

class CGame;
class CModel;
//==============================================
//�V�[���̔h�� �� �v���C���[
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

	typedef enum
	{
		SAMPLE_OBJ00 = 0,
		SAMPLE_OBJ01,
		SAMPLE_OBJ_MAX
	}SAMPLE_OBJ;

	//�R���X�g���N�^ / �f�X�g���N�^
	CPlayer(int nPriority = DRAW_MODEL, DATA_TYPE nObjType = DATA_TYPE_MODEL);
	~CPlayer();

	//�g�p���郂�f���̓ǂݍ���/�폜
	static HRESULT ModelLoad(void);
	static void ModelUnLoad(void);

	//�g�p���郂�f��UV�̓ǂݍ���/�폜
	static HRESULT TextureLoad(void);
	static void TextureUnLoad(void);

	//����
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SampleChange(void);	//�\�����Ă���T���v����ς���
	void OperationManual(void);	//�J�����̃��[�h�����擾���A���f���̑�����@��ς���
	void MOVE(void);			//�v���C���[�̈ړ�����

	//���f���Ɋւ��鏈��
	void ModelLode(void);		//���f���̓ǂݍ���

	void Debug(void);//�f�o�b�N�p

	//Get�֐�(���g�ň��������𑼂̃v���O�����Ŏg�p���鏈��)
	D3DXVECTOR3 GetPos(void) {return m_pos; }					//�ʒu
	D3DXVECTOR3 GetMove(void) { return m_move; }				//�ړ���
	D3DXVECTOR3 GetRot(void) { return m_rot; }					//����
	int GetSampleObjType(void) { return m_nSampleObj_ViewType; }//���ݑI������Ă���OBJ

	//Set�֐�
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetSampleObj(int num);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[SAMPLE_OBJ_NUM];	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_move;						//�ړ�
	D3DXVECTOR3 m_rot;						//����
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X

	//�g�p���郂�f�����
	CModel *m_pModel[SAMPLE_OBJ_NUM];
	static LPD3DXMESH m_pMesh[SAMPLE_OBJ_NUM];
	static LPD3DXBUFFER m_pBuffMat[SAMPLE_OBJ_NUM];
	static DWORD m_pNumMat[SAMPLE_OBJ_NUM];
	static int m_nNumModel;//���f���p�[�c��
	static int m_nNumTex;//�e�N�X�`����
	static char m_aFileNameModel[SAMPLE_OBJ_NUM][256];//�ǂݍ��ރ��f����
	static char m_aFileNameTex[SAMPLE_OBJ_NUM][256];//�ǂݍ��ރe�N�X�`����
	static KEY m_aKeyOffseet[SAMPLE_OBJ_NUM];//�����ʒu

	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//���ݕ\�����Ă���I�u�W�F�N�g
	int m_nSampleObj_ViewType;

	CGame *m_pGame;

};




#endif