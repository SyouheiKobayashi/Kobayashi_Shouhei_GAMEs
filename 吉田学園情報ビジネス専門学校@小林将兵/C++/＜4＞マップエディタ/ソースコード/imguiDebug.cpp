//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//imgui���� [imguiDebug.cpp]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "imguiDebug.h"
#include "imconfig.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"
#include "imstb_rectpack.h"
#include "imstb_textedit.h"
#include "imstb_truetype.h"

#include "game.h"
#include "player.h"
#include "model.h"
//=====================================================================
//�ÓI�����o�ϐ�
//=====================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CImguiDebug::CImguiDebug()
{
	
}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CImguiDebug::~CImguiDebug()
{

}

//=============================================================================
//����������
//=============================================================================
void CImguiDebug::Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
{
	//ImGui�p�̃e�L�X�g�f�[�^�𐶐�����
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//AddFontFromFileTTF�֐�
	//��P���� : �t�H���g�f�[�^�̃t�@�C���p�X��
	//��Q���� : �t�H���g�̃T�C�Y
	//��R���� : NULL��OK
	//��S���� : ���{��ɂ��������io.Fonts->GetGlyphRangesJapanese�Ŋ�{�I��OK
	io.Fonts->AddFontFromFileTTF("c:/Windows/Fonts/meiryo.ttc", 20.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	//ImGui�𐶐�����
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);
	ImGui::StyleColorsClassic();
}
//=============================================================================
//�I������
//=============================================================================
void CImguiDebug::Uninit(void)
{
	//ImGui���I��������
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

}
//=============================================================================
//�X�V����
//=============================================================================
void CImguiDebug::Update(void)
{
	CGame * pGame = CManager::GetGame();
	CPlayer *pPlayer = CGame::GetPlayer();

	//�V�����t���[����p�ӂ���
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//�E�B���h�E�����J�n
	ImGui::Begin(u8"Map_Editor Ver3.0", false);
	//�E�B���h�E���Ƀ^�O�𑝂₷
	ImGui::CollapsingHeader(u8"Information");

	if (pPlayer != NULL)
	{
		int nNowSampleView = pPlayer->GetSampleObjType();
		ImGui::Text(u8"���ݕ\�����Ă���T���v��");
		ImGui::InputInt(u8"", &nNowSampleView);
		if (nNowSampleView > CModel::GetMaxCreateNum())
		{
			nNowSampleView = 0;
		}
		if (nNowSampleView < 0)
		{
			nNowSampleView = CModel::GetMaxCreateNum();
		}
		pPlayer->SetSampleObj(nNowSampleView);

		ImGui::Text(u8"�T���v���̈ʒu");
		D3DXVECTOR3 pos = pPlayer->GetPos();
		ImGui::InputFloat3(u8"", pos);
		pPlayer->SetPos(pos);

		ImGui::Text(u8"�T���v���̉�]��");
		D3DXVECTOR3 rot = pPlayer->GetRot();
		ImGui::InputFloat3(u8" ", rot);//�ЂƘg�J����[u8"�������J����"]�I�����ł��Ȃ��Ȃ�
		pPlayer->SetRot(rot);

	}
	//���݂̏���ۑ�����
	//if (ImGui::Button(u8"�ۑ�����"))
	//{
	//	ImGui::SameLine();
	//}

	//if (ImGui::CollapsingHeader(u8"Information02"))
	//{
	//	ImGui::Text(u8"W,A,S,D [�I�u�W�F�N�g�̈ړ�]");
	//	ImGui::Text(u8"��,��,��,�E [�J�����̈ړ�]");
	//	if (ImGui::CollapsingHeader(u8"������@02"))
	//	{
	//		ImGui::Text(u8"��,��,��,�E [�J�����̈ړ�]02");
	//	}
	//}
	
	//�E�B���h�E�����I��
	ImGui::End();

	if (pGame->GetInputMode() == 0)
	{
		Tutorial();//�L�[�{�[�h�p����
	}
	else if (pGame->GetInputMode() == 1)
	{
		Tutorial02();//�}�E�X�p����
	}

	//�t���[�����I��������
	ImGui::EndFrame();
	//u8�c���{��

}
//=============================================================================
//�`�揈��
//=============================================================================
void CImguiDebug::Draw(void)
{
	//Update�Ő�������ImGui��\������
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void CImguiDebug::Tutorial(void)
{
	//�E�B���h�E�����J�n
	ImGui::Begin(u8"�L�[�{�[�h�̑������", false);
	
	//�L�ړ��e
	ImGui::Text(u8"[F1] : ���_�ύX   [F2�L�[] : ����̕ύX");
	ImGui::Text(u8"[WASDQE�L�[] : �I�u�W�F�N�g�̈ړ�   [���L�[ / 0�L�[] : �J�����̈ړ� / ������	[�ʒu�̏�����] : ENTER�L�[");
	ImGui::Text(u8"[1�E2�L�[] : �I�u�W�F�N�g�̕ύX   [�X�y�[�X�L�[] : ����   [BackSpace] : �ЂƂO�ɖ߂�   [F5�L�[] : �O���e�L�X�g�ɏo��<OBJ_OUTPUT.txt>");

	//�E�B���h�E�����I��
	ImGui::End();
}

void CImguiDebug::Tutorial02(void)
{
	//�E�B���h�E�����J�n
	ImGui::Begin(u8"�}�E�X�̑������", false);

	//�L�ړ��e
	ImGui::Text(u8"[F1] : ���_�ύX(�}�E�X�ړ���XZ�p�EXY�p�ɕύX)   [F2�L�[] : ����̕ύX");
	ImGui::Text(u8"[�}�E�X�Ɉˑ�] : �I�u�W�F�N�g�̈ړ�   [WASDQE�L�[] : �J�����̈ړ�    [X�L�[] : ������   [�E�N���b�N������] : ���_�̉�]");
	ImGui::Text(u8"[�z�C�[���̉�]] : �I�u�W�F�N�g�̕ύX   [���N���b�N] : ����   [BackSpace] : �ЂƂO�ɖ߂�   [F5�L�[] : �O���e�L�X�g�ɏo��<OBJ_OUTPUT.txt>");

	//�E�B���h�E�����I��
	ImGui::End();
}


