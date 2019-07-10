//==============================================================================
// サウンド処理 [sound.h]
// Author:Kobayashi/小林 将兵
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
// パラメータ構造体定義
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント(-1でループ再生)
	} SOUNDPARAM;

//サウンドファイル
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
		//SOUND_LABEL_GAME,			// ゲーム
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();
	~CSound();
	static CSound *Create(HWND hWnd);//フェードの生成処理
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

	
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのポインタ
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイスへのポインタ
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイスへのポインタ
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータへのポインタ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

																// 各音素材のパラメータ
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "DATA\\BGM\\BGM\\title.wav", -1 },		// タイトル
		{ "DATA\\BGM\\BGM\\game.wav", -1 },
		{ "DATA\\BGM\\BGM\\ranking.wav", -1 },
		{ "DATA\\BGM\\SE\\action01.wav", 0 },
		{ "DATA\\BGM\\SE\\action02.wav", 0 },
		{ "DATA\\BGM\\SE\\action03.wav", 0 },
		{ "DATA\\BGM\\SE\\damage.wav", 0 },
		{ "DATA\\BGM\\SE\\delete.wav", 0 },
		{ "DATA\\BGM\\SE\\switch.wav", 0 },
		{ "DATA\\BGM\\SE\\bullet.wav", 0 },
		//{ "DATA\\SE\\落下音02.wav", 0 },		
		//{ "DATA\\BGM\\ホラー神社.wav", -1 },		// リザルト
		//{ "DATA\\SE\\落下音02.wav", 0 },			// 落下音
		//{ "DATA\\SE\\巻き戻し.wav", 0 },			// ヒット音0
		//{ "DATA\\SE\\時計の刻み.wav", 0 },			// ヒット音1
		//{ "DATA\\SE\\コイン.wav", 0 },	// コイン音
		//{ "DATA\\SE\\decide000.wav", 0 }		// 選択音
	};


};

#endif
