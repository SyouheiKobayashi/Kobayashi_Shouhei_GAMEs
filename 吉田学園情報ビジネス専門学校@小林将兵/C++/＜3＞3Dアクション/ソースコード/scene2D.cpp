//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//					2D�|���S������ [scene2D.h]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "scene2D.h"
#include "manager.h"
#include "input.h"
#include "debugLog.h"

//==============================================
//					�R���X�g���N�^
//==============================================
CScene2D::CScene2D(int nPriority, DATA_TYPE dataType):CScene(nPriority, dataType)
{

}
//==============================================
//					�f�X�g���N�^
//==============================================
CScene2D::~CScene2D()
{

}
//==============================================
//					����
//==============================================
CScene2D *CScene2D::Create(void)
{
	CScene2D *pScene2D = NULL;
	
	if (pScene2D == NULL)
	{
		pScene2D = new CScene2D;
		pScene2D->Init();
	}
	return pScene2D;
}
//==============================================
//				����������
//==============================================
HRESULT CScene2D::Init(void)
{
	m_bFlash = false;
	m_fFlashCnt = 0.0f;
	m_nSizeCnt = 0;
	m_bSizeChange = true;
	m_nScrollCnt = 0;
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_���̍쐬
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, NULL, &m_pTexture);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̈ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fSizeX +m_pos.x, -m_fSizeY +m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, -m_fSizeY +m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fSizeX +m_pos.x, m_fSizeY + m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, m_fSizeY + m_pos.y, 0.0f);

	//�e�N�X�`���̐���
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
	pVtx[0].col = D3DXCOLOR(m_col);
	pVtx[1].col = D3DXCOLOR(m_col);
	pVtx[2].col = D3DXCOLOR(m_col);
	pVtx[3].col = D3DXCOLOR(m_col);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}
//==============================================
//					�I������
//==============================================
void CScene2D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();//���S�t���O�𗧂Ă�
}

//==============================================
//					�X�V����
//==============================================
void CScene2D::Update(void)
{

}

//==============================================
//					�`�揈��
//==============================================
void CScene2D::Draw(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
 	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//==============================================
//				�摜���̎擾�E���f
//==============================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 textureInfo)
{
	m_pTexture = textureInfo;
}

//==============================================
//				�ʒu���̎擾�E���f
//==============================================
void CScene2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==============================================
//				��]���̎擾�E���f
//==============================================
void CScene2D::SetSpin(float fSpinSpeed)
{
	m_fAngle = atan2f(m_fSizeX, m_fSizeY);
	m_fLengs = sqrtf((m_fSizeX )*(m_fSizeX ) + (m_fSizeY )*(m_fSizeY ));
	m_fSpinSpeed += fSpinSpeed;//��]���x

	//���_���̍쐬
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̃T�C�Y�A��]��̏���
	pVtx[0].pos = D3DXVECTOR3(sinf(m_fAngle + D3DX_PI + m_fSpinSpeed), cosf(m_fAngle + D3DX_PI + m_fSpinSpeed), 0.0f)*(m_fLengs + 0) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(sinf(-m_fAngle + D3DX_PI + m_fSpinSpeed), cosf(-m_fAngle + D3DX_PI + m_fSpinSpeed), 0.0f)*(m_fLengs + 0) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(sinf(-m_fAngle + m_fSpinSpeed), cosf(-m_fAngle + m_fSpinSpeed), 0.0f)*(m_fLengs + 0) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(sinf(m_fAngle + m_fSpinSpeed), cosf(m_fAngle + m_fSpinSpeed), 0.0f)*(m_fLengs + 0) + m_pos;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==============================================
//				�T�C�Y���̎擾�E���f
//==============================================
void CScene2D::SetSize(float fSizeX, float fSizeY)
{
	m_fSizeX = fSizeX;
	m_fSizeY = fSizeY;
}

//==============================================
//					 �F
//==============================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	m_col = col;
	//���_���̍쐬
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�J���[���
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//==============================================
//					�_��
//==============================================
void CScene2D::FlashTex(void)
{
	
	switch(m_bFlash)
	{
	case true:
		m_fFlashCnt+=0.03f;
		m_col = D3DXCOLOR(m_fFlashCnt, m_fFlashCnt, m_fFlashCnt, m_fFlashCnt);
		if (m_fFlashCnt >= 1.0f)
		{
			m_bFlash = false;
		}
		break;

	case false:
		m_fFlashCnt-=0.03f;
		m_col = D3DXCOLOR(m_fFlashCnt, m_fFlashCnt, m_fFlashCnt, m_fFlashCnt);
		if (m_fFlashCnt <= 0.0f)
		{
			m_bFlash = true;
		}
		break;
	}

	//���_���̍쐬
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�J���[���
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//								�A�j���[�V����
//=============================================================================
void CScene2D::SetTexAnim(int nCntAnim, int nWidth, int nHight, bool bLoop)
{
	m_nCnt++; //�J�E���^�[�̉��Z �����̑��x

	if (m_nCnt % nCntAnim == 0)
	{
		m_PatternAnim = (m_PatternAnim + 1) % (nWidth * nHight);//�p�^�[��No.�X�V
	}

	//���_���̍쐬
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight));
		pVtx[1].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth) + (1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight));
		pVtx[2].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight) + (1.0f / nHight));
		pVtx[3].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth) + (1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight) + (1.0f / nHight));

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}

	if (bLoop == false)//���[�v���Ȃ��ꍇ
	{
		if (m_PatternAnim >= (nWidth * nHight) - 1)
		{
			CScene2D::Uninit();
		}
	}
}

void CScene2D::SetAnimSize(float fCnt, int nSpeed)
{
	
	switch (m_bSizeChange)
	{
	case true:
		m_nSizeCnt++;
		m_fSizeX += fCnt;
		m_fSizeY += fCnt;
		if (m_nSizeCnt >= nSpeed)
		{
			m_nSizeCnt = 0;
			m_bSizeChange = false;
		}
			break;

	case false:
		m_nSizeCnt++;
		m_fSizeX += -fCnt;
		m_fSizeY += -fCnt;
		if (m_nSizeCnt >= nSpeed)
		{
			m_nSizeCnt = 0;
			m_bSizeChange = true;
		}
			break;


	}
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_���̍쐬
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�|���S���̈ʒu��ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, -m_fSizeY + m_pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, -m_fSizeY + m_pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, m_fSizeY + m_pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, m_fSizeY + m_pos.y, 0.0f);

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//==============================================
//						�ړ�
//==============================================
void CScene2D::SetMove(D3DXVECTOR3 move)
{
	m_pos += move;
	//���_���̍쐬
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̈ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, -m_fSizeY + m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, -m_fSizeY + m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fSizeX + m_pos.x, m_fSizeY + m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fSizeX + m_pos.x, m_fSizeY + m_pos.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//==============================================
//					�X�N���[��
//==============================================
void CScene2D::SetScroll(float fSpeed, bool bVector, int nType)
{
	//�X�N���[������
	if (bVector == true)
	{
		m_nScrollCnt++;
	}
	else if (bVector == false)
	{
		m_nScrollCnt--;
	}

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (nType == 0)//���X�N���[��
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (fSpeed * m_nScrollCnt), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f + (fSpeed * m_nScrollCnt), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (fSpeed * m_nScrollCnt), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f + (fSpeed * m_nScrollCnt), 1.0f);
	}

	if (nType == 1)//�c�X�N���[��
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + (fSpeed * m_nScrollCnt));
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + (fSpeed * m_nScrollCnt));
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + (fSpeed * m_nScrollCnt));
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + (fSpeed * m_nScrollCnt));
	}
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


