//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					mesh���� [mesh.h]
//			Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "scene.h"

//==============================================
//					�}�N����`
//==============================================
#define MESH_TEX01	("DATA/TEXTURE/mesh01.png")
#define MESH_TEX02	("DATA/TEXTURE/mesh02.png")

class CPlayer;
//==============================================
//		scene�̔h�� �� ���b�V��
//==============================================
class CMeshField : public CScene
{
public:
	typedef enum
	{
		XZ = 0,
		XY,
		MAX
	}MESH_TYPE;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CMeshField(int nPriority = DRAW_3D, DATA_TYPE nObjType = DATA_TYPE_3D);
	~CMeshField();
	static CMeshField *Create(int nTexType,MESH_TYPE type ,D3DXVECTOR3 startPos ,int nSize,int nNumX, int nNumZ);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					��Պ֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					���̑��֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	void MeshNormaVector(void);//�@�����ɂ�閾�Õ\��


	float GetHight(D3DXVECTOR3 pos);				//���b�V���̍����𔽉f�����邽�߂̏��𓾂�
	float GetDotPosY(void) { return m_DotPosY; }
	bool GetCheck(void) { return m_bCheck; }		//���b�V���ɐG��Ă��邩 / ����Ă��邩

	//�N���\��
	void SetHight(D3DXVECTOR3 pos, float fValue, float fRange);

private:
	LPDIRECT3DTEXTURE9		m_pTexture[2];	//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//�C���f�b�N�X�̃|�C���^

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//����
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X

	//�@���Ɋւ���ϐ�
	D3DXVECTOR3 m_nor[6];
	D3DXVECTOR3 m_vec0;
	D3DXVECTOR3 m_vec1;
	D3DXVECTOR3 m_vec2;
	D3DXVECTOR3 m_vec3;

	int m_nNumIndxMeshField;	//�C���f�b�N�X��
	int m_nNumPolygonMeshField;	//�|���S����
	int m_nNumVertexMeshField;	//���_��

	CPlayer *m_pPlayer;

	bool m_bCheck;	//����Ă���̂�?

	float m_DotPosY;//�v���C���[�̈ʒu���Z�p

	int m_nSelectTex;			//�g�p����摜
	int m_nMeshType;			//�c������
	D3DXVECTOR3 m_startPos;		//�����n�_
	int m_nSize;				//����̃T�C�Y
	int m_nNumX;				//���̌�
	int m_nNumZ;				//�c�̌�

};




#endif