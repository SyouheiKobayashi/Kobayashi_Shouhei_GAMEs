//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//シーン処理 [scene.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _SCENE_H_
#define _SCENE_H_

//=================================================
//include / 他のデータ・コードの呼び出し・利用
//=================================================
#include "main.h"

//==============================================
//シーン(データの管理)
//==============================================
class CScene
{
public:
	typedef enum//描画の種類・優先順位
	{
		DRAW_3D = 0,
		DRAW_BILLBOARD,
		DRAW_OBJECT,
		DRAW_MODEL,
		DRAW_2D,
		DRAW_PAUSE,
		DRAW_MAX
	}DRAW_TYPE;

	
	typedef enum//データの種類
	{
		DATA_TYPE_NONE = 0,	//タイプ / 該当なし
		DATA_TYPE_2D,
		DATA_TYPE_3D,
		DATA_TYPE_BILLBOARD,
		DATA_TYPE_OBJECT,
		DATA_TYPE_MODEL,
		DATA_TYPE_ENEMY,
		DATA_TYPE_MAX		//オブジェクト最大数
	}DATA_TYPE;

	//コンストラクタ / デストラクタ
	CScene(int nDrawPriority = 0, DATA_TYPE nDataType = DATA_TYPE_NONE);
	~CScene();

	//基盤となる関数(初期化 / 終了 / 更新 / 描画)
	//※親クラスのメソッドを、派生クラスのメソッドで書き換える
	//https://ameblo.jp/nana-2007-july/entry-10038342175.html
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);			//全データの終了・解放処理
	static void UpdateAll();				//全データの更新処理
	static void DrawAll();					//全データの描画処理
	void Delete(void);						//各終了処理を実行されたデータの削除
	void SetDataType(DATA_TYPE DataType);	//各処理で使用したオブジェクトタイプ情報の取得

protected:
	void Release(void);						//データの削除(死亡フラグをたてる)

private:
	int m_nPriority;//描画の優先順位
	DATA_TYPE m_DataType;//データのタイプ
	static int m_nNumPriority[DRAW_MAX];

	static CScene *m_pTop[DRAW_MAX];	//先頭objのポインタ
	static CScene *m_pCur[DRAW_MAX];	//(現在の)最後のポインタ
	CScene *m_pPrev;									//前のデータのポインタ
	CScene *m_pNext;									//次のデータのポインタ
	bool m_bDeath;										//データの死亡フラグ

	//デバック用
	static int m_NumALL;//全objの数
};


#endif