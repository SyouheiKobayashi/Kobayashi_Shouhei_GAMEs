//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//						�r���{�[�h���� [billboard.cpp]
//				Author : Kobayashi_Sho-hei/���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#include "billboard.h"
#include "manager.h"
#include "input.h"
#include "debugLog.h"

//==============================================
//					�R���X�g���N�^
//==============================================
CBillboard::CBillboard(int nPriority, DATA_TYPE dataType) :CScene(nPriority, dataType)
{
	m_pVtxBuff = NULL;		//���_�o�b�t�@�ւ̃|�C���^
}
//==============================================
//					�f�X�g���N�^
//==============================================
CBillboard::~CBillboard()
{

}

//==============================================
//			  �e�N�X�`�����̎󂯎��
//==============================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 textureInfo)
{
	m_pTexture = textureInfo;
}


//==============================================
//					����
//==============================================
CBillboard *CBillboard::Create(void)
{
	CBillboard *pBillboard = NULL;

	if (pBillboard == NULL)
	{
		pBillboard = new CBillboard;
		pBillboard->Init();

	}
	return pBillboard;
}

//==============================================
//				����������
//==============================================
HRESULT CBillboard::Init(void)
{
	m_nCnt = 0;
	m_PatternAnim = 0;

	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_���̍쐬
	VERTEX_3D *pVtx;

	//���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, TEXBILLBOARD_NAME, &m_pTexture);


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�r���{�[�h�̈ʒu��ݒ�
 	pVtx[0].pos = D3DXVECTOR3(-m_size.x+m_pos.x, m_size.y + m_pos.y, m_size.z + m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x + m_pos.x, m_size.y + m_pos.y, m_size.z + m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x + m_pos.x, -m_size.y + m_pos.y, m_size.z + m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_size.x + m_pos.x, -m_size.y + m_pos.y, m_size.z + m_pos.z);

	//�e�N�X�`���̐���
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);


	//�J���[���
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================
//					�I������
//==============================================
void CBillboard::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//==============================================
//					�X�V����
//==============================================
void CBillboard::Update(void)
{
}

//==============================================
//					�`�揈��
//==============================================
void CBillboard::Draw(void)
{
	//�f�o�C�X���̎擾��
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxView, mtxTrans, mtxRot;//�v�Z�p�}�g���b�N�X

	//�A���t�@�e�X�g����(�������ɂ��摜�̐؂��茻�ۂ𖳌��ɂ���)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);//REF = Reference:�Q��
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//FUNC = Function:�@�\ //GREATER = �`���傫��

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	if (CManager::GetMode() == CManager::MODE_RANKING)//RANKING�̂Ƃ��̂ݏ�ɃJ�����̕��֌�������
	{
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		m_mtxWorld._11 = mtxView._11;
		m_mtxWorld._12 = mtxView._21;
		m_mtxWorld._13 = mtxView._31;
		m_mtxWorld._21 = mtxView._12;
		m_mtxWorld._22 = mtxView._22;
		m_mtxWorld._23 = mtxView._32;
		m_mtxWorld._31 = mtxView._13;
		m_mtxWorld._32 = mtxView._23;
		m_mtxWorld._33 = mtxView._33;
	}

	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));


	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);


	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�r���{�[�h�̕`��
  	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//==============================================
//					�T�C�Y
//==============================================
void CBillboard::SetSize(D3DXVECTOR3 size)
{
	m_size.x = size.x;
	m_size.y = size.y;
	m_size.z = size.z;

	
}
void CBillboard::SetChangeSize(float fsize)
{

	m_size.x += fsize;
	m_size.y += fsize;

	//���_���̍쐬
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�r���{�[�h�̈ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x,  m_pos.y+ m_size.y , m_pos.z + m_size.z  );
	pVtx[1].pos = D3DXVECTOR3(m_pos.x+ m_size.x,  m_pos.y+ m_size.y, m_pos.z + m_size.z );
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x,m_pos.y - m_size.y , m_pos.z + m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y , m_pos.z + m_size.z );

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==============================================
//					�ʒu
//==============================================
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
 	m_pos = pos;
	
	//���_���̍쐬
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�r���{�[�h�̈ʒu��ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, m_pos.z + m_size.z);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, m_pos.z + m_size.z);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, m_pos.z + m_size.z);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, m_pos.z + m_size.z);

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}
//==============================================
//					��]
//==============================================
void CBillboard::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;

}
//==============================================
//					�F
//==============================================
void CBillboard::SetCol(D3DXCOLOR col)
{
	m_col = col;

	VERTEX_3D*pVtx;
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�ݒ�
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//==============================================
//			�A�j���[�V����(�R�}����)
//==============================================
void CBillboard::SetTexAnim(int nCntAnim, int nWidth, int nHight, bool bLoop)
{
	m_nCnt++; //�J�E���^�[�̉��Z �����̑��x

	if (m_nCnt % nCntAnim == 0)
	{
		m_PatternAnim = (m_PatternAnim + 1) % (nWidth * nHight);//�p�^�[��No.�X�V
	}

	//���_���̍쐬
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight));
	pVtx[1].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth) + (1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight));
	pVtx[2].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight) + (1.0f / nHight));
	pVtx[3].tex = D3DXVECTOR2(m_PatternAnim*(1.0f / nWidth) + (1.0f / nWidth), (m_PatternAnim / nWidth)*(1.0f / nHight) + (1.0f / nHight));

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();


	if (bLoop == false)//���[�v���Ȃ��ꍇ
	{
		if (m_PatternAnim >= (nWidth * nHight) - 1)
		{
			CBillboard::Uninit();
		}
	}
}

//==============================================
//					�p�[�e�B�N��
//==============================================
void CBillboard::SetParticle(float fTransSize, D3DXCOLOR col)
{
	VERTEX_3D*pVtx;

	m_size.x += fTransSize;
	m_size.y += fTransSize;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ� 
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, -m_size.y, m_size.z);

	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(col);
	pVtx[1].col = D3DXCOLOR(col);
	pVtx[2].col = D3DXCOLOR(col);
	pVtx[3].col = D3DXCOLOR(col);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==============================================
//				��]���̎擾�E���f
//==============================================
void CBillboard::SetSpin(float fSpinSpeed)
{
	m_fAngle = -atan2f(m_size.x, m_size.y);
	m_fLengs = -sqrtf((m_size.x)*(m_size.x)+(m_size.y)*(m_size.y));
	m_fSpinSpeed += fSpinSpeed;//��]���x

							   //���_���̍쐬
	VERTEX_3D *pVtx;

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
//			�_�ŏ��̎擾�E���f
//==============================================
void CBillboard::FlashTex(void)
{
	switch (m_bFlash)
	{
	case true:
		fFlashCnt += 0.03f;
		m_col = D3DXCOLOR(fFlashCnt, fFlashCnt, fFlashCnt, fFlashCnt);
		if (fFlashCnt >= 1.0f)
		{
			m_bFlash = false;
		}
		break;

	case false:
		fFlashCnt -= 0.03f;
		m_col = D3DXCOLOR(fFlashCnt, fFlashCnt, fFlashCnt, fFlashCnt);
		if (fFlashCnt <= 0.0f)
		{
			m_bFlash = true;
		}
		break;
	}
}
