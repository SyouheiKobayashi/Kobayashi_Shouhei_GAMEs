//=============================================================================
// �J�������� [camera.cpp]
// Author : Kobayashi/���я���
//=============================================================================
#include "camera.h"
#include "player.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_SITEN D3DXVECTOR3(0, 80, -1400)//���_
#define CAMERA_KYORI (35.0f)//�J�����̋�����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
camera g_camera;
//float Radian;
int g_nCntTime = 0;

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	g_camera.posV = CAMERA_SITEN;						//���_
	g_camera.posR = D3DXVECTOR3(0, 80, 0);				//�����_
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//g_camera.posVDest = D3DXVECTOR3(0, 0, 0);			//(�ړI��)���_
	//g_camera.posRDest = D3DXVECTOR3(0, 0, 0);			//(�ړI��)�����_

	//D3DXVECTOR3 rot = D3DXVECTOR3(0, 0, 0);				//(���݂�)����
	//D3DXVECTOR3 rotDest = D3DXVECTOR3(0, 0, 0);			//(�ړI��)����
	g_camera.Radian = CAMERA_KYORI;
	//g_camera.fKaiten = 0;
	//Radian = CAMERA_KYORI;

	g_nCntTime = 0;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	//^^^^^^^^^^^^^^^^^^^^^^^^^^
	//�J�����ړ�[W][S][A][D]
	//^^^^^^^^^^^^^^^^^^^^^^^^^^

		/*g_camera.posV.x += sinf(g_camera.fKaiten) * 5;
		g_camera.posV.z += cosf(g_camera.fKaiten) * 5;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.fKaiten) * 200;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.fKaiten) * 200;*/
#if 1
	if (GetKeyboardPress(DIK_W) == true)
	{//									����
		g_camera.posV.x += sinf(g_camera.fKaiten) * 5;
		g_camera.posV.z += cosf(g_camera.fKaiten) * 5;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.fKaiten) * 200;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.fKaiten) * 200;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{
		g_camera.posV.x += sinf(D3DX_PI + g_camera.fKaiten) * 5;
		g_camera.posV.z += cosf(D3DX_PI + g_camera.fKaiten) * 5;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.fKaiten) * 200;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.fKaiten) * 200;
	}
	if (GetKeyboardPress(DIK_D) == true)
	{
		g_camera.posV.x += sinf((D3DX_PI / 2) + g_camera.fKaiten) * 5;
		g_camera.posV.z += cosf((D3DX_PI / 2) + g_camera.fKaiten) * 5;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.fKaiten) * 200;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.fKaiten) * 200;
	}
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_camera.posV.x += sinf((-D3DX_PI / 2) + g_camera.fKaiten) * 5;
		g_camera.posV.z += cosf((-D3DX_PI / 2) + g_camera.fKaiten) * 5;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.fKaiten) * 200;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.fKaiten) * 200;
	}
#endif
	//^^^^^^^^^^^^^^^^^^^^^^^^^^
	//		���_[T][Y][U]
	//^^^^^^^^^^^^^^^^^^^^^^^^^^
#if 1
	if (GetKeyboardPress(DIK_T) == true)//��]
	{
		if (GetKeyboardPress(DIK_LSHIFT) == true)
		{
			g_camera.fKaiten -= 0.02f;
			if (g_camera.fKaiten < -D3DX_PI)
			{
				g_camera.fKaiten = D3DX_PI;
			}
			g_camera.posV.x = g_camera.posR.x - sinf(g_camera.fKaiten) * 200;
			g_camera.posV.z = g_camera.posR.z - cosf(g_camera.fKaiten) * 200;
		}
		else
		{
			g_camera.fKaiten += 0.02f;
			if (g_camera.fKaiten > D3DX_PI)
			{
				g_camera.fKaiten = -D3DX_PI;
			}
			g_camera.posV.x = g_camera.posR.x - sinf(g_camera.fKaiten) * 200;
			g_camera.posV.z = g_camera.posR.z - cosf(g_camera.fKaiten) * 200;
		}
	}
	if (GetKeyboardPress(DIK_Y) == true)//�㉺
	{
		if (GetKeyboardPress(DIK_LSHIFT) == true)
		{
			g_camera.posV.y -= 3;
		}
		else
		{
			g_camera.posV.y += 3;
		}
	}
	if (GetKeyboardPress(DIK_U) == true)//�g�� �k��
	{
		if (GetKeyboardPress(DIK_LSHIFT) == true)
		{
			g_camera.Radian++;
		}
		else
		{
			g_camera.Radian--;
		}
	}

#endif
	//^^^^^^^^^^^^^^^^^^^^^^^^^^
	//		�����_[G][H][J]
	//^^^^^^^^^^^^^^^^^^^^^^^^^^
#if 0
	if (GetKeyboardPress(DIK_G) == true)//��]
	{
		if (GetKeyboardPress(DIK_LSHIFT) == true)
		{
			g_camera.fKaiten -= 0.05f;
			if (g_camera.fKaiten < -D3DX_PI)
			{
				g_camera.fKaiten = D3DX_PI;
			}
			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.fKaiten) * 200;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.fKaiten) * 200;
		}
		else
		{
			g_camera.fKaiten += 0.05f;
			if (g_camera.fKaiten > D3DX_PI)
			{
				g_camera.fKaiten = -D3DX_PI;
			}
			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.fKaiten) * 200;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.fKaiten) * 200;
		}
	}
	/*if (GetKeyboardPress(DIK_H) == true)
	{
		if (GetKeyboardPress(DIK_LSHIFT) == true)
		{
			g_camera.posR.y--;
		}
		else
		{
			g_camera.posR.y++;
		}
	}
	if (GetKeyboardPress(DIK_J) == true)
	{
		if (GetKeyboardPress(DIK_LSHIFT) == true)
		{
			g_camera.posR.z--;
		}
		else
		{
			g_camera.posR.z++;
		}
	}*/
#endif
	//^^^^^^^^^^^^^^^^^^^^^^^^^^
	//		 �z�u���Z�b�g[Q]
	//^^^^^^^^^^^^^^^^^^^^^^^^^^
#if 0
	if (GetKeyboardPress(DIK_Q) == true)
	{
		InitCamera();
	}
#endif

	PLAYER *pPlayer = GetPlayer();

	//^^^^^^^^^^^^^^^^^^^^^^^^^^
	//	�J�����̎����ǔ�����
	//^^^^^^^^^^^^^^^^^^^^^^^^^^
#if 0
	/*(g_camera.posRDest.x) = pPlayer->pos.x - sinf(pPlayer->rot.y)*80;
	(g_camera.posRDest.y) = pPlayer->pos.y;
	(g_camera.posRDest.z) = pPlayer->pos.z - cosf(pPlayer->rot.y)*80;*/

	(g_camera.posRDest.x) = pPlayer->pos.x - sinf(pPlayer->rot.y) * 80;
	(g_camera.posRDest.y) = pPlayer->pos.y;
	(g_camera.posRDest.z) = pPlayer->pos.z - cosf(pPlayer->rot.y) * 60;

	(g_camera.posVDest.x) = g_camera.posRDest.x - sinf(g_camera.rot.y) * 200;
	(g_camera.posVDest.y) = g_camera.posRDest.y;
	(g_camera.posVDest.z) = g_camera.posRDest.z - cosf(g_camera.rot.y) * 200;

	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x)*0.09f;
	g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y)*0.05f;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z)*0.09f;

	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x)*0.09f;
	g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y + 50)*0.05f;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z)*0.09f;
#endif

	//^^^^^^^^^^^^^^^^^^^^^^^^^^
	//	�J�����̉�荞�ݏ���
	//^^^^^^^^^^^^^^^^^^^^^^^^^^
#if 0
	if (GetKeyboardPress(DIK_UP) == false &&
		GetKeyboardPress(DIK_DOWN) == false &&
		GetKeyboardPress(DIK_RIGHT) == false &&
		GetKeyboardPress(DIK_LEFT) == false)
	{
		g_nCntTime++;
		if (g_nCntTime >= 100)
		{
			g_camera.fKaiten = (pPlayer->rot.y + D3DX_PI) - g_camera.rot.y;
			if (g_camera.fKaiten > D3DX_PI)
			{
				g_camera.fKaiten -= D3DX_PI*2.0f;
			}
			else if (g_camera.fKaiten < -D3DX_PI)
			{
				g_camera.fKaiten += D3DX_PI*2.0f;
			}

			g_camera.rot.y += g_camera.fKaiten*0.05f;

			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y -= D3DX_PI*2.0f;
			}
			else if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y += D3DX_PI*2.0f;
			}

			g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * 200;
			g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * 200;
		}
	}
	else
	{
		g_nCntTime = 0;//����������
	}
#endif
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(g_camera.Radian),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxViex);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_camera.mtxViex,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxViex);
}
//=============================================================================
// �J�������̏���
//=============================================================================
camera *GetCamera(void)
{
	return &g_camera;
}