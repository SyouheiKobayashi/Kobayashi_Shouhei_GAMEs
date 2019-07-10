//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�f�o�b�N���O���� [debugLog.cpp]
//Author : Kobayashi_Sho-hei/���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "debugLog.h"
#include "manager.h"

//=====================================================================
//�ÓI�����o�ϐ�
//=====================================================================
char CDebug::m_aStr[MAX_WORD] = {};
LPD3DXFONT CDebug::m_pFont = NULL;

//==============================================
//�R���X�g���N�^
//==============================================
CDebug::CDebug()
{
	
}

//==============================================
//�f�X�g���N�^
//==============================================
CDebug::~CDebug()
{

}

//==============================================
//����
//==============================================
CDebug*CDebug::Create(void)
{
	CDebug *pDebug = NULL;

	if (pDebug == NULL)
	{
		pDebug = new CDebug;
		pDebug->Init();
	}
	return pDebug;
}

//==============================================
//������
//==============================================
void CDebug::Init(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
}

//==============================================
//�I��
//==============================================
void CDebug::Uninit(void)
{
	if (m_pFont != NULL)
	{
		delete this;
	}
}

//==============================================
//���͂��ꂽ�������̕\�L
//==============================================
void CDebug::DebugLog(char * fmt, ...)
{
	//�f�o�b�N�p
#ifdef _DEBUG
		char CharData[MAX_WORD];
		va_list ap;
		va_start(ap, fmt);

		vsprintf(CharData, fmt, ap);

		va_end(ap);

		strcat(m_aStr, CharData);
#endif
}

//==============================================
//�`��\��
//==============================================
void CDebug::Draw(void)
{
	//�f�o�b�N�p
#ifdef _DEBUG
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	strcpy(m_aStr, "");
#endif
}