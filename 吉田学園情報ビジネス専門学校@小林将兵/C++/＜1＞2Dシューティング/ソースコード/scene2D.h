//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// 2D�|���S������ [scene2D.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
#include "main.h"
#include "scene.h"

//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �V�[��2DCLASS(<Scene>�̔h���N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CScene2D : public CScene
{
public:
	//�摜�̊g��k��
	typedef enum
	{
		Big = 0,//�g��
		Small,//�k��
		ALL
	}SIZE;
	
	CScene2D(int nPriority);//�f�t�H���g����
	~CScene2D();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	D3DXVECTOR3 GetPos(void) { return m_pos; }//���������|���S���̈ʒu���擾����
	float GetHeight(void) { return m_fHEIGHT; }
	float GetWidth(void) { return m_fWIDTH; }
	void SetPos(D3DXVECTOR3 pos);//�������𔽉f������
	void SetCol(D3DXCOLOR col);
	void SetSize(float fWIDTH, float fHEIGHT);//�|���S���̃T�C�Y�ύX
	void SetRot(float fSpin);
	void SetTimeRot(int nTime);

	//�e�N�X�`���̃A�j���[�V��������(�A�j���[�V�����̑���,��������,�c������,�p�^�[����)
	void SetTexAnim(int nCntAnim, int nWidth,int nHight,int nPattern);

	//�e�N�X�`���̃X�N���[������(�X�N���[�X�̑���,+-�ŃX�N���[�������̕ύX,�c�X�N�����X�N��)
	void SetScroll(float fscrollSpeed,int nScrollCnt,int nScrollType);
	void BindTexture(LPDIRECT3DTEXTURE9 m_pShareTexture);

	//�̗͐ݒ�
	void SetLife(int nSetLife);
	int GetLife(void) { return m_nLife; }

private:
	//! �����o�ϐ���
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	float					m_fWIDTH;
	float					m_fHEIGHT;

	//! <�|���S���̉�]�Ɋւ���ϐ�>
	float m_fAngle;//�p�x
	float m_fLengs;//����
	float m_fSpin;//��]
	//! <�|���S���̊g��E�k���Ɋւ���ϐ�>
	float m_fSize;
	SIZE m_size = Big;//�񋓌^
	int m_nLife;//�̗�,���Ԍo��

};




#endif