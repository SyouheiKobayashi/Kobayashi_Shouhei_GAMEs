//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// 2D�|���S������ [scene2D.cpp]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "scene2D.h"
#include "manager.h"
#include "input.h"

//�}�N��
//#define TEXTURE_NAME01	("DATA\\akira000.png")

//�O���[�o��
//=============================================================================
//+ 2D�|���S���̃R���X�g���N�^
//=============================================================================
#if 1
CScene2D::CScene2D(int nPriority = 3):CScene(nPriority)
{
	//! <�l���N���A�ȏ�Ԃɂ���>
	m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);//�\������|���S���̈�

	//m_fAngle = 0;//�p�x
	//m_fLengs = 0;//����
	//m_fSpin = 0;//��]�̑��x
	//m_fSize = 0.0f;
	
	m_nLife = 0;
}
#endif
//=============================================================================
//+ 2D�|���S���̃f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
//+ �|���S���̏���������
//=============================================================================
HRESULT CScene2D::Init(void)
{
	//! <�����l�̐ݒ�>
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);//�\������|���S���̈ʒu

	//m_fSpin = 0;//��]�̑��x
	//m_fSize = 0.0f;//�g��E�k��
	
	m_nLife = 0;

	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();//NULL����Ȃ�������GetDevice

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME01, &m_pTexture);


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S���̈ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	/*pVtx[0].pos = D3DXVECTOR3(-m_fWIDTH, -m_fHEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_fWIDTH, -m_fHEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWIDTH, +m_fHEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_fWIDTH, +m_fHEIGHT, 0.0f);*/


	// �e�N�X�`���̐���
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[���
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//+ �|���S���̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	// �e�N�X�`���̔j��
	//! �e�e�N�X�`��������.cpp�ɏ�������ł���

	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�������g��delete	<Scene>��delete�������g�p
	Release();
}

//=============================================================================
//+ �|���S���̍X�V����
//=============================================================================
void CScene2D::Update(void)
{
	//! <�|���S���̉�]�Ɋւ���ϐ�>
	//m_fAngle = atan2f(100, 100);//����s�\
	//m_fLengs = 100;//�S�̓I�ȃT�C�Y���ς��

	//m_fAngle = atan2f(m_fWIDTH, m_fHEIGHT);//����s�\
	//m_fLengs = sqrtf((m_fWIDTH/2)*(m_fWIDTH/2)+ (m_fHEIGHT / 2)*(m_fHEIGHT / 2));//�S�̓I�ȃT�C�Y���ς��
	//m_fSpin += 0.01f;//��]�̑��x
#if 0
	 //! <�|���S���̊g��E�k���Ɋւ���ϐ�>
	switch (m_size)
	{
	case Big:
		m_fSize += 1.5f;//�g�傷��l
		
		if (80.0f <= m_fSize)
		{
			m_size = Small;
		}
		break;

	case Small:
		m_fSize -= 1.5f;//�k������l
		if (m_fSize <= 0.0f)
		{
			m_size = Big;
		}
		break;
	}
#endif
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S���̃T�C�Y�A��]��̏���
	//pVtx[0].pos = D3DXVECTOR3(sinf(m_fAngle - D3DX_PI + m_fSpin), cosf(m_fAngle - D3DX_PI + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	//pVtx[1].pos = D3DXVECTOR3(sinf(-m_fAngle + D3DX_PI + m_fSpin), cosf(-m_fAngle + D3DX_PI + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	//pVtx[2].pos = D3DXVECTOR3(sinf(-m_fAngle + m_fSpin), cosf(-m_fAngle + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	//pVtx[3].pos = D3DXVECTOR3(sinf(m_fAngle + m_fSpin), cosf(m_fAngle + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	
	//�ʏ�\���|���S��(�T�C�Y�ω��A��]�Ȃ�,�e.cpp�ŃT�C�Y�̏���������)
	/*pVtx[0].pos = D3DXVECTOR3(-m_fWIDTH, - m_fHEIGHT, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+ m_fWIDTH, - m_fHEIGHT, 0.0f)+ m_pos;
	pVtx[2].pos = D3DXVECTOR3(- m_fWIDTH, + m_fHEIGHT, 0.0f)+ m_pos;
	pVtx[3].pos = D3DXVECTOR3(+ m_fWIDTH, + m_fHEIGHT, 0.0f)+ m_pos;*/



	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	
}

//=============================================================================
//+ �|���S���̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
 	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=============================================================================
//+ �|���S����Set����
//=============================================================================
void CScene2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ʏ�\���|���S��(�T�C�Y�ω��A��]�Ȃ�,�e.cpp�ŃT�C�Y�̏���������)
	pVtx[0].pos = D3DXVECTOR3(-m_fWIDTH, -m_fHEIGHT, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+m_fWIDTH, -m_fHEIGHT, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-m_fWIDTH, +m_fHEIGHT, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(+m_fWIDTH, +m_fHEIGHT, 0.0f) + m_pos;


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//=============================================================================
//+ �|���S���̃J���[Set����
//=============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) + col;
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) + col;
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) + col;
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) + col;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//=============================================================================
//+ �|���S���Ɏg�p����e�N�X�`�����̎擾
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 m_pShareTexture)
{
	m_pTexture = m_pShareTexture;
}

//=============================================================================
//+ �T�C�Y�ύXSet����
//=============================================================================
void CScene2D::SetSize(float fWIDTH, float fHEIGHT)
{
	m_fWIDTH = fWIDTH;
	m_fHEIGHT = fHEIGHT;

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_fWIDTH, -m_fHEIGHT, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+m_fWIDTH, -m_fHEIGHT, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-m_fWIDTH, +m_fHEIGHT, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(+m_fWIDTH, +m_fHEIGHT, 0.0f) + m_pos;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//=============================================================================
//+ ��]Set����
//=============================================================================
void CScene2D::SetRot(float fSpin)
{
	//! <�|���S���̉�]�Ɋւ���ϐ�>
	m_fAngle = atan2f(100, 100);//����s�\
	m_fLengs = 100;//�S�̓I�ȃT�C�Y���ς��

	m_fAngle = atan2f(m_fWIDTH, m_fHEIGHT);//����s�\
	m_fLengs = sqrtf((m_fWIDTH/2)*(m_fWIDTH/2)+ (m_fHEIGHT / 2)*(m_fHEIGHT / 2));//�S�̓I�ȃT�C�Y���ς��
	m_fSpin += fSpin;//��]�̑��x

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S���̃T�C�Y�A��]��̏���
	pVtx[0].pos = D3DXVECTOR3(sinf(m_fAngle - D3DX_PI + m_fSpin), cosf(m_fAngle - D3DX_PI + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(sinf(-m_fAngle + D3DX_PI + m_fSpin), cosf(-m_fAngle + D3DX_PI + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(sinf(-m_fAngle + m_fSpin), cosf(-m_fAngle + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(sinf(m_fAngle + m_fSpin), cosf(m_fAngle + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CScene2D::SetTimeRot(int nTime)
{
	//! <�|���S���̉�]�Ɋւ���ϐ�>
	m_fAngle = atan2f(100, 100);//����s�\
	m_fLengs = 100;//�S�̓I�ȃT�C�Y���ς��

	m_fAngle = atan2f(m_fWIDTH, m_fHEIGHT);//����s�\
	m_fLengs = sqrtf((m_fWIDTH / 2)*(m_fWIDTH / 2) + (m_fHEIGHT / 2)*(m_fHEIGHT / 2));//�S�̓I�ȃT�C�Y���ς��
	m_fSpin = (float)nTime;//��]�̑��x

					 // ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S���̃T�C�Y�A��]��̏���
	pVtx[0].pos = D3DXVECTOR3(sinf(m_fAngle - D3DX_PI + m_fSpin), cosf(m_fAngle - D3DX_PI + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(sinf(-m_fAngle + D3DX_PI + m_fSpin), cosf(-m_fAngle + D3DX_PI + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(sinf(-m_fAngle + m_fSpin), cosf(-m_fAngle + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(sinf(m_fAngle + m_fSpin), cosf(m_fAngle + m_fSpin), 0.0f)*(m_fLengs + m_fSize) + m_pos;


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
//+ �A�j���[�V����Set����
//=============================================================================
void CScene2D::SetTexAnim(int nCntAnim,int nWidth, int nHight, int nPattern)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth),				   (nPattern / nWidth)*(1.0f / nHight));
	pVtx[1].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth) + (1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHight));
	pVtx[2].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth),				   (nPattern / nWidth)*(1.0f / nHight) + (1.0f / nHight));
	pVtx[3].tex = D3DXVECTOR2(nPattern*(1.0f / nWidth) + (1.0f / nWidth), (nPattern / nWidth)*(1.0f / nHight) + (1.0f / nHight));

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//+ �X�N���[��Set����
//=============================================================================
void CScene2D::SetScroll(float fscrollSpeed, int nScrollCnt, int nScrollType)
{
	int nCnt = 0;
	

	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	nCnt++; //�J�E���^�[�̉��Z


	if (nScrollType == 1)//�c�X�N
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (fscrollSpeed * nScrollCnt));
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (fscrollSpeed * nScrollCnt));
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (fscrollSpeed * nScrollCnt));
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (fscrollSpeed * nScrollCnt));
		if (pVtx[0].tex.y < 0.0f)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		}

		if (pVtx[1].tex.y < 0.0f)
		{
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}

	if (nScrollType == 2)//���X�N
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f - (fscrollSpeed * nScrollCnt), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f - (fscrollSpeed * nScrollCnt), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f - (fscrollSpeed * nScrollCnt), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f - (fscrollSpeed * nScrollCnt), 1.0f);

		if (pVtx[0].tex.x < 0.0f)
		{
			pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		}

		if (pVtx[1].tex.x < 0.0f)
		{
			pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}


//=============================================================================
//+ �e���C�t�̐ݒ�(�̗͂⎞�Ԍo�ߓ�)����
//=============================================================================
void CScene2D::SetLife(int nSetLife)
{
	m_nLife = nSetLife;
	/*if (m_nLife >= 15)
	{
		m_nLife =15;
	}*/
	this;//�u���C�N���̒l�̊m�F�ɕ֗�
}

