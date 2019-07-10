//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//���f������ [model.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _MODEL_H_
#define _MODEL_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "scene.h"

//==============================================
//�}�N����`
//==============================================
#define MODEL_NAME	("DATA/MODEL/car000.x")


//==============================================
//���f��
//==============================================
class CModel
{
public:
	//�R���X�g���N�^ / �f�X�g���N�^
	CModel();
	~CModel();

	//����
	static CModel *Create(D3DXVECTOR3 pos);

	//��ՂƂȂ�֐�(������ / �I�� / �X�V / �`��)
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�g�p���郂�f���E�摜�̓ǂݍ���
	void BindModel(LPD3DXBUFFER buffMat, DWORD numMat, LPD3DXMESH mesh);
	void BindTexture(LPDIRECT3DTEXTURE9 textureInfo);

	void SetParent(CModel *pModel);//�p�[�c���Ƃ̐e�����߂�

	void SetPos(D3DXVECTOR3 pos);//�ʒu
	void SetRot(D3DXVECTOR3 rot);//����
	void SetCol(D3DXCOLOR col);//�J���[

	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_move;						//�ړ�
	D3DXVECTOR3 m_rot;						//����
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X

	//���f�����
	D3DXMATERIAL *m_pMat;
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_pNumMat;

	CModel *m_pParent;//�e���f���̃|�C���^

};




#endif