//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
// シーン処理 [scene.h]
// Author : Kobayashi_Sho-hei(小林 将兵)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇　◇
//+ ポリゴンCLASS(基本クラス)
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
class CScene
{
public:
	//! オブジェクトの種類
	typedef enum
	{
		OBJTYPE_NONE = 0,//虚無のobj
		OBJTYPE_BG,//背景のobj
		OBJTYPE_PLAYER,//プレイヤーのobj
		OBJTYPE_ENEMY,//敵のobj
		OBJTYPE_BULLET,//弾のobj
		OBJTYPE_EFFECT,
		OBJTYPE_EXPLOSION,//爆発のobj
		OBJTYPE_UI,//UIのobj
		OBJTYPE_MAX
	}OBJ_TYPE;

	//! オブジェクト描画順(値が小さいほど奥、大きいほど手前に)
	typedef enum
	{
		DRAW_BG = 0,//背景
		DRAW_PLAYER,//プレイヤー
		DRAW_ENEMY,//敵
		DRAW_BULLET,//弾
		DRAW_EFFECT,//エフェクト
		DRAW_EXPLOSION,//爆発アニメーション
		DRAW_UI,//UI
		DRAW_INFO,//情報(スコア,ライフなどのステータス表記)
		DRAW_PAUSE,
		DRAW_ALL//最大描画数
	}OBJ_DRAW;


	CScene();
	CScene(int nPriority);//デフォルト引数
	~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void SetPos(D3DXVECTOR3 pos) = 0;

	static void ReleaseAll(void);//ポリゴンの終了・データ解放処理
	static void UpdateAll();//ポリゴンの更新処理
	static void UpdateAll(OBJ_DRAW DrowType);//ポーズ用ポリゴンの更新処理
	static void DrawAll();//ポリゴンの描画処理

	static int GetNumAll(void) { return m_NumALL; }//objの総数

	void SetObjType(OBJ_TYPE ObjType);//objの判別
	OBJ_TYPE GetObjType(void) { return m_ObjType; }
	static CScene *GetScene(int nPrio, int nIndx) { return m_apScene[nPrio][nIndx]; }



protected:
	void Release(void);//ポリゴンのdelete処理

private:
	//! 静的処理
	static CScene *m_apScene[OBJ_DRAW::DRAW_ALL][MAX_SCENE];//[優先順位][objの最大数]
	static int m_NumALL;//ポリゴンの総数
	int m_nID;//obj一つ一つに番号を与える

	int m_nPriority;//描画順

	OBJ_TYPE m_ObjType;
};


#endif