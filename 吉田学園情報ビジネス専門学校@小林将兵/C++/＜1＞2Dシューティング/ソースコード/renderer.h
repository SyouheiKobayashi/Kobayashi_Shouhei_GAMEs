//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
// �����_�����O���� [renderer.h]
// Author : Kobayashi_Sho-hei(���� ����)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"

//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//+ �����_�����OCLASS(��{�N���X)
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�f�o�C�X���̏�����(�|�C���^��Ԃ������̏ꍇ/�����b�g:�\�[�X�ɏ����Ȃ��Ă���������)
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

private:
	

#ifdef _DEBUG
	void DrawFPS(void);//FPS�\�L
#endif

	//! �����o�ϐ���
	LPDIRECT3D9				m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)

	


#ifdef _DEBUG
	LPD3DXFONT				m_pFont;			// �t�H���g�ւ̃|�C���^
#endif


};

#endif