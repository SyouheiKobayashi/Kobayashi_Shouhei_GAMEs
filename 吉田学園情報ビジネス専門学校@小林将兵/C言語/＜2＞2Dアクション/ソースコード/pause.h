//=============================================================================
// �|�[�Y�̏��� [pause.h]
// Author:Kobayashi/���� ����
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	PAUSETYPE_CONTINUE = 0,
	PAUSETYPE_RETRY,
	//PAUSETYPE_QUIT,
	PAUSETYPE_MAX
}PAUSETYPE;
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 Initpos;// �����ʒu
	D3DXCOLOR col;		// �F
	D3DXVECTOR3 move;	// �ړ� 
	int nType;			// ���
	int nCounterAnim;	// �J�E���^�[
	int nPatternAnim;	// �p�^�[��
	bool bUse;			// �g�p���Ă��邩�ǂ���
} PAUSE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
void SetPause(D3DXVECTOR3 pos, D3DXCOLOR col, int nType);
#endif

