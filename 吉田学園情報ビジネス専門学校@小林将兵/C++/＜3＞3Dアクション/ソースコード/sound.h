//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//サウンド処理 [sound.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _SOUND_H_
#define _SOUND_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"

//==============================================
//サウンド
//==============================================
class CSound
{
public:
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント(-1でループ再生)
	} SOUNDPARAM;

//サウンドファイル
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

	//コンストラクタ / デストラクタ
	CSound();
	~CSound();

	//生成
	static CSound *Create(HWND hWnd);

	//基盤となる関数(初期化 / 終了)
	HRESULT Init(HWND hWnd);
	void Uninit(void);

	//再生・停止
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	IXAudio2 *m_pXAudio2 = NULL;								//XAudio2オブジェクトへのポインタ
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			//マスターボイスへのポインタ
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	//ソースボイスへのポインタ
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					//オーディオデータへのポインタ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					//オーディオデータサイズ

	//各音素材のパラメータ
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
