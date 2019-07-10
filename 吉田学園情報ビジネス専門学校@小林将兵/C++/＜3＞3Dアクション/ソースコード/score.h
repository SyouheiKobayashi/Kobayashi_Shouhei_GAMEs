//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					�X�R�A���� [score.h]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"
#include "scene.h"

//==============================================
//					�}�N����`
//==============================================
#define MAX_SCOREDIGIT	(3)//�ő包��
#define MAX_RANK	(5)//�ő叇�� / �}�l�[�W���Ɏ�ł��ŏ����Ă邩��C��t����!!
#define SCORE_SIZE_X	(20)
#define SCORE_SIZE_Y	(26)
#define SCORE_SPACE		(45)

class CNumber;
//==============================================
//				�V�[���̔h�� �� �X�R�A
//==============================================
class CScore : public CScene
{
public:
	typedef enum//�X�R�A���[�h
	{
		GAME_SCORE = 0,	//�Q�[���X�R�A
		RANKING_SCORE,	//�����L���O�X�R�A
		MAX_SCORE
	}SCORE_TYPE;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CScore(int nPriority = DRAW_2D, DATA_TYPE nObjType = DATA_TYPE_2D);
	~CScore();
	static CScore *Create(D3DXVECTOR3 pos, SCORE_TYPE type);//�X�R�A�̐�������

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					��Պ֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	virtual HRESULT Init(void) = 0;
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	int GetNowScore(void) { return m_nScore; }//���݃X�R�A�̎擾

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Set�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	void SetPos(D3DXVECTOR3 pos);
	void AddScore(int nValue);//�X�R�A���_

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;//�|���S���̈ʒu


protected:
	int m_nScore;				//���݂̃X�R�A
	int m_nTotalScore;			//���v�X�R�A
	int m_nScoreNo[MAX_SCOREDIGIT];	//�X�R�A�̌���

};

//! ==============================================
//!			�X�R�A�̔h�� �� �Q�[���Ŏg�p����X�R�A
//! ==============================================
class CGameScore : public CScore
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CGameScore();
	~CGameScore();

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					��Պ֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CNumber *m_apNumber[MAX_SCOREDIGIT];
};

//! ==============================================
//!			�X�R�A�̔h�� �� �����L���O�Ŏg�p����X�R�A
//! ==============================================
class CRankingScore : public CScore
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CRankingScore();
	~CRankingScore();

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					��Պ֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetRankingSort(int nScore);			//�X�R�A�̃\�[�g

private:
	
	CNumber *m_apNumber[MAX_RANK][MAX_SCOREDIGIT];	//[�ő叇��][����]
	int m_nDigt[MAX_RANK][MAX_SCOREDIGIT];			//���̍X�V�Ŏg�p
	int m_NewRecord;								//�L�^���X�V���ꂽ�Ƃ�

};

#endif