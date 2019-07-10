//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �V�[������ [scene.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �|���S��CLASS(��{�N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CScene
{
public:
	//! �I�u�W�F�N�g�̎��
	typedef enum
	{
		OBJTYPE_NONE = 0,//������obj
		OBJTYPE_BG,//�w�i��obj
		OBJTYPE_PLAYER,//�v���C���[��obj
		OBJTYPE_ENEMY,//�G��obj
		OBJTYPE_BULLET,//�e��obj
		OBJTYPE_EFFECT,
		OBJTYPE_EXPLOSION,//������obj
		OBJTYPE_UI,//UI��obj
		OBJTYPE_MAX
	}OBJ_TYPE;

	//! �I�u�W�F�N�g�`�揇(�l���������قǉ��A�傫���قǎ�O��)
	typedef enum
	{
		DRAW_BG = 0,//�w�i
		DRAW_PLAYER,//�v���C���[
		DRAW_ENEMY,//�G
		DRAW_BULLET,//�e
		DRAW_EFFECT,//�G�t�F�N�g
		DRAW_EXPLOSION,//�����A�j���[�V����
		DRAW_UI,//UI
		DRAW_INFO,//���(�X�R�A,���C�t�Ȃǂ̃X�e�[�^�X�\�L)
		DRAW_PAUSE,
		DRAW_ALL//�ő�`�搔
	}OBJ_DRAW;


	CScene();
	CScene(int nPriority);//�f�t�H���g����
	~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void SetPos(D3DXVECTOR3 pos) = 0;

	static void ReleaseAll(void);//�|���S���̏I���E�f�[�^�������
	static void UpdateAll();//�|���S���̍X�V����
	static void UpdateAll(OBJ_DRAW DrowType);//�|�[�Y�p�|���S���̍X�V����
	static void DrawAll();//�|���S���̕`�揈��

	static int GetNumAll(void) { return m_NumALL; }//obj�̑���

	void SetObjType(OBJ_TYPE ObjType);//obj�̔���
	OBJ_TYPE GetObjType(void) { return m_ObjType; }
	static CScene *GetScene(int nPrio, int nIndx) { return m_apScene[nPrio][nIndx]; }



protected:
	void Release(void);//�|���S����delete����

private:
	//! �ÓI����
	static CScene *m_apScene[OBJ_DRAW::DRAW_ALL][MAX_SCENE];//[�D�揇��][obj�̍ő吔]
	static int m_NumALL;//�|���S���̑���
	int m_nID;//obj���ɔԍ���^����

	int m_nPriority;//�`�揇

	OBJ_TYPE m_ObjType;
};


#endif