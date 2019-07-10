//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �����G�t�F�N�g���� [explosion.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"
#include "scene2D.h"

//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �����G�t�F�N�gCLASS(<scene2D>�̔h���N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CExplosion : public CScene2D
{
public:
	CExplosion();
	~CExplosion();
	static HRESULT Load(void);//�e�N�X�`����K�v���ǂݍ���
	static void UnLoad(void);//�g�p���Ă���e�N�X�`���𑼂̏����ŏ������Ȃ��悤�ɂ���
	static CExplosion *Create(D3DXVECTOR3 pos);//�e�̐���(�ʒu���)

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//���L�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_move;//�ړ�����

	 //! <�|���S���̃A�j���[�V�����Ɋւ���ϐ�>
	int m_CntAnim;//�A�j���[�V�����̑���
	int m_PatternAnim;//�A�j���[�V�����̕�����

};

#endif