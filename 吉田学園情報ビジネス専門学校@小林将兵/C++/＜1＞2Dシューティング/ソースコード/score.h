//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �X�R�A���� [score.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"
#include "scene.h"

#define MAX	(7)
class CNumber;
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �V�[��2DCLASS(<Scene>�̔h���N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CScore : public CScene
{
public:
	typedef enum
	{
		GAME_SCORE = 0,
		RANKING_SCORE,
		MAX_SCORE

	}SCORE_TYPE;

	CScore();
	~CScore();

	static CScore *Create(D3DXVECTOR3 pos, SCORE_TYPE type);//�X�R�A�̐�������

	virtual HRESULT Init(void) = 0;
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;
	
	
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	void SetPos(D3DXVECTOR3 pos);//�������𔽉f������

	void AddScore(int nValue);//�X�R�A���_

	void SaveScore(int nValue);//�Q�[���̃X�R�A�ꎞ�I�Z�[�u

	int GetNowScore(void) { return m_nScore; }//���݃X�R�A�̎擾
	void SetScore(int nNowScore);

	

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu

protected:
	int m_nScore;//���_�̋L�^
	int m_nScoreNo[MAX];//����

};

class CGameScore : public CScore
{
public:
	CGameScore();
	~CGameScore();

	//�e���N���G�C�g������

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos);


	void Uninit(void);
	void Update(void);
	void Draw(void);


private:
	
	CNumber *m_apNumber[MAX];//number��������������
	

};

class CRankingScore : public CScore
{
public:
	CRankingScore();
	~CRankingScore();

	//�e���N���G�C�g������

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos);


	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetRankingSort(int nScore);

private:

	CNumber *m_apNumber[5][MAX];//number��������������
	int m_nDigt[5][7];

};

#endif