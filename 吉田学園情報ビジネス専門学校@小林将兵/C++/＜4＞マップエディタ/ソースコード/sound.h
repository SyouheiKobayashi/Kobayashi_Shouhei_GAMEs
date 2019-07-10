////���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
////�T�E���h���� [sound.h]
////Author : Kobayashi_Sho-hei / ���� ����
////���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//#ifndef _SOUND_H_
//#define _SOUND_H_
//
////=================================================
////include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
////=================================================
//#include "main.h"
//
////==============================================
////�T�E���h
////==============================================
//class CSound
//{
//public:
//	typedef struct
//	{
//		char *pFilename;	// �t�@�C����
//		int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
//	} SOUNDPARAM;
//
////�T�E���h�t�@�C��
//	typedef enum
//	{
//		SOUND_TITLE = 0,
//		SE_ATTACK,
//		SOUND_LABEL_MAX,
//	} SOUND_LABEL;
//
//	//�R���X�g���N�^ / �f�X�g���N�^
//	CSound();
//	~CSound();
//
//	//����
//	static CSound *Create(HWND hWnd);
//
//	//��ՂƂȂ�֐�(������ / �I��)
//	HRESULT Init(HWND hWnd);
//	void Uninit(void);
//
//	//�Đ��E��~
//	HRESULT PlaySound(SOUND_LABEL label);
//	void StopSound(SOUND_LABEL label);
//	void StopSound(void);
//
//	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
//	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
//
//private:
//	IXAudio2 *m_pXAudio2 = NULL;								//XAudio2�I�u�W�F�N�g�ւ̃|�C���^
//	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			//�}�X�^�[�{�C�X�ւ̃|�C���^
//	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	//�\�[�X�{�C�X�ւ̃|�C���^
//	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					//�I�[�f�B�I�f�[�^�ւ̃|�C���^
//	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					//�I�[�f�B�I�f�[�^�T�C�Y
//
//	//�e���f�ނ̃p�����[�^
//	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
//	{
//		/*{ "DATA\\SOUND\\BGM\\title.wav", -1 },	
//		{ "DATA\\SOUND\\SE\\ATTACK.wav", 0 },*/
//	};
//
//
//};
//
//#endif
