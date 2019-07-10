//==============================================================================
// �T�E���h���� [sound.h]
// Author:Kobayashi/���� ����
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
// �p�����[�^�\���̒�`
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

//�T�E���h�t�@�C��
	typedef enum
	{
		SOUND_TITLE = 0,	
		SOUND_GAME,
		SOUND_RANKING,
		SOUND_ACTION_SE01,
		SOUND_ACTION_SE02,
		SOUND_ACTION_SE03,
		SOUND_DAMAGE_SE,
		SOUND_DELETE_SE,
		SOUND_SWITCH_SE,
		SOUND_BULLET_SE,
		//SOUND_LABEL_GAME,			// �Q�[��
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();
	~CSound();
	static CSound *Create(HWND hWnd);//�t�F�[�h�̐�������
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

	
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

																// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "DATA\\BGM\\BGM\\title.wav", -1 },		// �^�C�g��
		{ "DATA\\BGM\\BGM\\game.wav", -1 },
		{ "DATA\\BGM\\BGM\\ranking.wav", -1 },
		{ "DATA\\BGM\\SE\\action01.wav", 0 },
		{ "DATA\\BGM\\SE\\action02.wav", 0 },
		{ "DATA\\BGM\\SE\\action03.wav", 0 },
		{ "DATA\\BGM\\SE\\damage.wav", 0 },
		{ "DATA\\BGM\\SE\\delete.wav", 0 },
		{ "DATA\\BGM\\SE\\switch.wav", 0 },
		{ "DATA\\BGM\\SE\\bullet.wav", 0 },
		//{ "DATA\\SE\\������02.wav", 0 },		
		//{ "DATA\\BGM\\�z���[�_��.wav", -1 },		// ���U���g
		//{ "DATA\\SE\\������02.wav", 0 },			// ������
		//{ "DATA\\SE\\�����߂�.wav", 0 },			// �q�b�g��0
		//{ "DATA\\SE\\���v�̍���.wav", 0 },			// �q�b�g��1
		//{ "DATA\\SE\\�R�C��.wav", 0 },	// �R�C����
		//{ "DATA\\SE\\decide000.wav", 0 }		// �I����
	};


};

#endif
