//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					3D�|���S���������� [scene3D.h]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "scene.h"

class CPlayer;
//==============================================
//			�V�[���̔h�� �� 3D�|���S��
//==============================================
class CScene3D : public CScene
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CScene3D(int nPriority = DRAW_3D, DATA_TYPE dataType = DATA_TYPE_3D);
	~CScene3D();
	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,float pos0, float pos1, float pos2, float pos3);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					��Պ֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	void BindTexture(LPDIRECT3DTEXTURE9 textureInfo);			//�摜�������炢�A�����`��
	void SetPos(D3DXVECTOR3 pos);								//�ʒu
	void SetSize(float fSizeX, float fSizeY, float fSizeZ);		//�T�C�Y
	void SetCol(D3DXCOLOR col);									//�F
	void FlashTex(void);										//�_��
	void SetTexAnim(int nAnimSpeed, int nWidth,					//�����A�j���[�V����
		int nHeight, int nPattern);	
	//(�A�j���[�V�����̑����A���̕������A�c�̕������A�v�Z�Ŋ���o�����)

	//�|���S���̓����蔻��
	void CrossProduct(void);//�O�ςƓ���
	float SetHight(D3DXVECTOR3 pos, bool bJudge);//�����𔽉f�����邽�߂̏��𓾂�
	float GetDotPosY(void) { return m_DotPosY; }
	bool GetCheck(void) { return m_bCheck; }


	// @   @   @   @   @   @   @   @   @   @   @   @
	//				�O���f�[�^�̓ǂݎ��
	// @   @   @   @   @   @   @   @   @   @   @   @
	static char *ReadLine(FILE *pFile, char *pDst);
	static char *GetLIneTop(char *pSrc);
	static int PopString(char *pSrc, char *pDst);


private:
	CPlayer *m_pPlayer;

	LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_rot;						//����
	D3DXCOLOR m_col;						//�F
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X
	float m_fSizeX;							//X�T�C�Y
	float m_fSizeY;							//Y�T�C�Y
	float m_fSizeZ;							//Z�T�C�Y

	//�_�łɊւ��鏈��
	bool m_bFlash;							//�������̐؂�ւ�
	float fFlashCnt;						//�_�ł��鑬�x

	//�|���S���̓����蔻��
	//�p�x������
	float m_pos0, m_pos1, m_pos2, m_pos3;
	D3DXVECTOR3 m_nor0;
	D3DXVECTOR3 m_nor1;
	D3DXVECTOR3 m_vec0;
	D3DXVECTOR3 m_vec1;
	float m_DotPosY;	//�v���C���[�̈ʒu���Z�p
	bool m_bCheck;		//����Ă���̂�?

};




#endif