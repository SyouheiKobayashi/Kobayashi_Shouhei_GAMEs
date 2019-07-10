//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�V�[������ [scene.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _SCENE_H_
#define _SCENE_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"

//==============================================
//�V�[��(�f�[�^�̊Ǘ�)
//==============================================
class CScene
{
public:
	typedef enum//�`��̎�ށE�D�揇��
	{
		DRAW_3D = 0,
		DRAW_BILLBOARD,
		DRAW_OBJECT,
		DRAW_MODEL,
		DRAW_2D,
		DRAW_PAUSE,
		DRAW_MAX
	}DRAW_TYPE;

	
	typedef enum//�f�[�^�̎��
	{
		DATA_TYPE_NONE = 0,	//�^�C�v / �Y���Ȃ�
		DATA_TYPE_2D,
		DATA_TYPE_3D,
		DATA_TYPE_BILLBOARD,
		DATA_TYPE_OBJECT,
		DATA_TYPE_MODEL,
		DATA_TYPE_ENEMY,
		DATA_TYPE_MAX		//�I�u�W�F�N�g�ő吔
	}DATA_TYPE;

	//�R���X�g���N�^ / �f�X�g���N�^
	CScene(int nDrawPriority = 0, DATA_TYPE nDataType = DATA_TYPE_NONE);
	~CScene();

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	//���e�N���X�̃��\�b�h���A�h���N���X�̃��\�b�h�ŏ���������
	//https://ameblo.jp/nana-2007-july/entry-10038342175.html
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);			//�S�f�[�^�̏I���E�������
	static void UpdateAll();				//�S�f�[�^�̍X�V����
	static void DrawAll();					//�S�f�[�^�̕`�揈��
	void Delete(void);						//�e�I�����������s���ꂽ�f�[�^�̍폜
	void SetDataType(DATA_TYPE DataType);	//�e�����Ŏg�p�����I�u�W�F�N�g�^�C�v���̎擾

protected:
	void Release(void);						//�f�[�^�̍폜(���S�t���O�����Ă�)

private:
	int m_nPriority;//�`��̗D�揇��
	DATA_TYPE m_DataType;//�f�[�^�̃^�C�v
	static int m_nNumPriority[DRAW_MAX];

	static CScene *m_pTop[DRAW_MAX];	//�擪obj�̃|�C���^
	static CScene *m_pCur[DRAW_MAX];	//(���݂�)�Ō�̃|�C���^
	CScene *m_pPrev;									//�O�̃f�[�^�̃|�C���^
	CScene *m_pNext;									//���̃f�[�^�̃|�C���^
	bool m_bDeath;										//�f�[�^�̎��S�t���O

	//�f�o�b�N�p
	static int m_NumALL;//�Sobj�̐�
};


#endif