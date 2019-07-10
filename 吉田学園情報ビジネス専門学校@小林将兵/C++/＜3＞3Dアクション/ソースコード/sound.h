//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//�T�E���h���� [sound.h]
//Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _SOUND_H_
#define _SOUND_H_

//=================================================
//include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"

//==============================================
//�T�E���h
//==============================================
class CSound
{
public:
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

//�T�E���h�t�@�C��
	typedef enum
	{
		BGM_SOUND_TITLE = 0,
		BGM_SOUND_GAME01,
		BGM_SOUND_GAME02,
		BGM_SOUND_GAME03,
		BGM_SOUND_RANKING,
		SE_BUTTON,
		SE_CHARGE,
		SE_COUNT,
		SE_TIMEUP,
		SE_CRASH,
		SE_DAMAGE,
		SE_JUMP,
		SE_GATE,
		SE_SWITCH,
		SE_BULLET_DAMAGE,
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//�R���X�g���N�^ / �f�X�g���N�^
	CSound();
	~CSound();

	//����
	static CSound *Create(HWND hWnd);

	//��ՂƂȂ�֐�(������ / �I��)
	HRESULT Init(HWND hWnd);
	void Uninit(void);

	//�Đ��E��~
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	IXAudio2 *m_pXAudio2 = NULL;								//XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			//�}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	//�\�[�X�{�C�X�ւ̃|�C���^
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					//�I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					//�I�[�f�B�I�f�[�^�T�C�Y

	//�e���f�ނ̃p�����[�^
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "DATA\\SOUND\\BGM\\TITLE.wav", -1 },	
		{ "DATA\\SOUND\\BGM\\GAME01.wav", -1 },
		{ "DATA\\SOUND\\BGM\\GAME02.wav", -1 },
		{ "DATA\\SOUND\\BGM\\GAME03.wav", -1 },
		{ "DATA\\SOUND\\BGM\\RANKING.wav", -1 },
		{ "DATA\\SOUND\\SE\\BUTTON.wav", 0 },
		{ "DATA\\SOUND\\SE\\CHARGE.wav", 0 },
		{ "DATA\\SOUND\\SE\\COUNT.wav", 0 },
		{ "DATA\\SOUND\\SE\\TIMEUP.wav", 0 },
		{ "DATA\\SOUND\\SE\\CRASH.wav", 0 },
		{ "DATA\\SOUND\\SE\\DAMAGE.wav", 0 },
		{ "DATA\\SOUND\\SE\\JUMP.wav", 0 },
		{ "DATA\\SOUND\\SE\\GATE.wav", 0 },
		{ "DATA\\SOUND\\SE\\SWITCH.wav", 0 },
		{ "DATA\\SOUND\\SE\\BULLET_DAMAGE.wav", 0 },

	};


};

#endif
