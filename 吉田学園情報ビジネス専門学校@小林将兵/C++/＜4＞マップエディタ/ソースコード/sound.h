////◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
////サウンド処理 [sound.h]
////Author : Kobayashi_Sho-hei / 小林 将兵
////◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//#ifndef _SOUND_H_
//#define _SOUND_H_
//
////=================================================
////include / 他のデータ・コードの呼び出し・利用
////=================================================
//#include "main.h"
//
////==============================================
////サウンド
////==============================================
//class CSound
//{
//public:
//	typedef struct
//	{
//		char *pFilename;	// ファイル名
//		int nCntLoop;		// ループカウント(-1でループ再生)
//	} SOUNDPARAM;
//
////サウンドファイル
//	typedef enum
//	{
//		SOUND_TITLE = 0,
//		SE_ATTACK,
//		SOUND_LABEL_MAX,
//	} SOUND_LABEL;
//
//	//コンストラクタ / デストラクタ
//	CSound();
//	~CSound();
//
//	//生成
//	static CSound *Create(HWND hWnd);
//
//	//基盤となる関数(初期化 / 終了)
//	HRESULT Init(HWND hWnd);
//	void Uninit(void);
//
//	//再生・停止
//	HRESULT PlaySound(SOUND_LABEL label);
//	void StopSound(SOUND_LABEL label);
//	void StopSound(void);
//
//	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
//	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
//
//private:
//	IXAudio2 *m_pXAudio2 = NULL;								//XAudio2オブジェクトへのポインタ
//	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			//マスターボイスへのポインタ
//	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	//ソースボイスへのポインタ
//	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					//オーディオデータへのポインタ
//	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					//オーディオデータサイズ
//
//	//各音素材のパラメータ
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
