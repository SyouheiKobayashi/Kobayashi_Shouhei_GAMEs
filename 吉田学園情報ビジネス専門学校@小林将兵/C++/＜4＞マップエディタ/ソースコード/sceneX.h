//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//X���f���������� [sceneX.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _SCENEX_H_
#define _SCENEX_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "scene.h"

//==============================================
//�}�N����`
//==============================================

//==============================================
//�V�[���̔h�� �� X���f��
//==============================================
class CSceneX : public CScene
{
public:
	//�R���X�g���N�^ / �f�X�g���N�^
	CSceneX(int nPriority = DRAW_MODEL, DATA_TYPE dataType = DATA_TYPE_MODEL);
	~CSceneX();

	//����
	static CSceneX *Create(void);

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Vtx(void);

	//Set�֐�(�������̐��l�A�f�[�^�����炢�K�� / ��ɔh��(�q)�N���X�Ŏg�p)
	void BindObject(LPD3DXBUFFER buffMat, DWORD numMat, LPD3DXMESH mesh);		//! X���f���E����ɑ΂��Ďg�p������摜�������炢�����K���E�`��
	void BindTexture(LPDIRECT3DTEXTURE9 textureInfo);							//! �V
	void SetPos(D3DXVECTOR3 pos);												//! �ʒu
	void SetMove(D3DXVECTOR3 move);												//! �ړ�
	void SetRot(D3DXVECTOR3 rot);												//! ��]
	void SetModelSize(float fModelSizeX, float fModelSizeY, float fModelSizeZ);	//! �T�C�Y
	void SetColAlpha(D3DXCOLOR col);											//! �F�E������
	void SaveObjType(int nType);												//! �^�C�v�̋L��

	//Get�֐�(���g�ň��������𑼂̃v���O�����Ŏg�p���鏈��)
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetModelSize(void) { return m_modelSize; }

	//�����蔻��Ɋւ��鏈��
	D3DXVECTOR3 GetVtxMin(void) { return m_VtxMin; }
	D3DXVECTOR3 GetVtxMax(void) { return m_VtxMax; }

	int GetSaveObjType(void) { return m_nSaveObjType; }							//! �����O���ɏo�͂��邽��

	//�O���̓ǂݍ��݂Ɋւ��鏈����
	static char *ReadLine(FILE *pFile, char *pDst);
	static char *GetLIneTop(char *pSrc);
	static int PopString(char *pSrc, char *pDst);


private:
	LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_move;						//�ړ�
	D3DXVECTOR3 m_rot;						//����
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_modelSize;				//���f���g��k��

	D3DXMATERIAL *m_pMat;
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_pNumMat;

	//�����蔻��ɕK�v�ȏ���
	D3DXVECTOR3 m_VtxMin;	//�ŏ��l
	D3DXVECTOR3 m_VtxMax;	//�ő�l

	int m_nSaveObjType;		//object.cpp�̌X�̃^�C�v���L��

};




#endif