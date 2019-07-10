//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//プレイヤー処理 [player.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"
#include "sceneX.h"
#include "input.h"
//==============================================
//マクロ定義
//==============================================
#define MODEL_UV	("DATA/TEXTURE/MODEL/player.png")

//プレイヤーステータス
#define SAMPLE_OBJ_NUM	(32)

class CGame;
class CModel;
//==============================================
//シーンの派生 → プレイヤー
//==============================================
class CPlayer : public CScene
{
public:
	//モデルごとの位置、回転
	typedef struct
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	}KEY;

	typedef enum
	{
		SAMPLE_OBJ00 = 0,
		SAMPLE_OBJ01,
		SAMPLE_OBJ_MAX
	}SAMPLE_OBJ;

	//コンストラクタ / デストラクタ
	CPlayer(int nPriority = DRAW_MODEL, DATA_TYPE nObjType = DATA_TYPE_MODEL);
	~CPlayer();

	//使用するモデルの読み込み/削除
	static HRESULT ModelLoad(void);
	static void ModelUnLoad(void);

	//使用するモデルUVの読み込み/削除
	static HRESULT TextureLoad(void);
	static void TextureUnLoad(void);

	//生成
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SampleChange(void);	//表示しているサンプルを変える
	void OperationManual(void);	//カメラのモード情報を取得し、モデルの操作方法を変える
	void MOVE(void);			//プレイヤーの移動操作

	//モデルに関する処理
	void ModelLode(void);		//モデルの読み込み

	void Debug(void);//デバック用

	//Get関数(自身で扱った情報を他のプログラムで使用する処理)
	D3DXVECTOR3 GetPos(void) {return m_pos; }					//位置
	D3DXVECTOR3 GetMove(void) { return m_move; }				//移動量
	D3DXVECTOR3 GetRot(void) { return m_rot; }					//向き
	int GetSampleObjType(void) { return m_nSampleObj_ViewType; }//現在選択されているOBJ

	//Set関数
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetSampleObj(int num);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[SAMPLE_OBJ_NUM];	//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_move;						//移動
	D3DXVECTOR3 m_rot;						//向き
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	//使用するモデル情報
	CModel *m_pModel[SAMPLE_OBJ_NUM];
	static LPD3DXMESH m_pMesh[SAMPLE_OBJ_NUM];
	static LPD3DXBUFFER m_pBuffMat[SAMPLE_OBJ_NUM];
	static DWORD m_pNumMat[SAMPLE_OBJ_NUM];
	static int m_nNumModel;//モデルパーツ数
	static int m_nNumTex;//テクスチャ数
	static char m_aFileNameModel[SAMPLE_OBJ_NUM][256];//読み込むモデル名
	static char m_aFileNameTex[SAMPLE_OBJ_NUM][256];//読み込むテクスチャ名
	static KEY m_aKeyOffseet[SAMPLE_OBJ_NUM];//初期位置

	//キーボード・コントローラーの取得処理
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//現在表示しているオブジェクト
	int m_nSampleObj_ViewType;

	CGame *m_pGame;

};




#endif