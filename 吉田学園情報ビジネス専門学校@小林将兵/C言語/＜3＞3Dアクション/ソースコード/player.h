//=============================================================================
// ���f������ [player.h]
// Author :Kobayashi/���я���//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MODEL (1)

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	LPDIRECT3DTEXTURE9 pTexture;

	DWORD nNumMat;
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;			//��]
	int nIdxModelParent;//�e���f���Ƃ̃C���f�b�N�X
	bool bUse;
}MODEL;

typedef struct
{
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 posOld;			//�ЂƂO
	D3DXVECTOR3 move;			//�ړ�
	D3DXVECTOR3 rot;			//��]
	D3DXVECTOR3 VtxMax;
	D3DXVECTOR3 VtxMin;
	MODEL aModel[MAX_MODEL];
	bool bUse;
}PLAYER;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(void);
#endif
