//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
//ステンシルシャドウ処理処理 [stencilShadow.h]
//Author : Kobayashi_Sho-hei / 小林 将兵
//◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆　◆
#include "manager.h"
#include "debugLog.h"
#include "input.h"
#include "sceneX.h"
#include "stencilShadow.h"
#include "game.h"
#include "player.h"
#include "polygon2D.h"

//=====================================================================
//静的メンバ変数
//=====================================================================
//テキスト読み込み関連
int CStencilShadow::m_nNumObject = NULL;
int CStencilShadow::m_nNumTexture = NULL;
char CStencilShadow::m_aFileNameObject[MAX_STENCIL][256] = {};
char CStencilShadow::m_aFileNameTexture[MAX_STENCIL][256] = {};
//モデル情報
int CStencilShadow::m_objType = 0;
LPD3DXMESH CStencilShadow::m_pMesh[MAX_STENCIL] = {};
LPD3DXBUFFER CStencilShadow::m_pBuffMat[MAX_STENCIL] = {};
DWORD CStencilShadow::m_pNumMat[MAX_STENCIL] = {};
//画像関連
LPDIRECT3DTEXTURE9 CStencilShadow::m_pTexture[STENCIL_TEXTURE_NUM] = {};

int CStencilShadow::m_nCreateNum = 0;//生成された数の記憶

CPolygon2D *CStencilShadow::m_pPolygon2D = NULL;


//==============================================
//コンストラクタ
//==============================================
CStencilShadow::CStencilShadow(int nPriority, DATA_TYPE dataType) :CSceneX(nPriority, dataType)
{
	//m_pTexture = NULL;		//テクスチャへのポインタ
	m_pVtxBuff = NULL;		//頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);
	/*m_VtxMin = GetVtxMin();
	m_VtxMax = GetVtxMax();*/
	
}
//==============================================
//デストラクタ
//==============================================
CStencilShadow::~CStencilShadow()
{

}

//==============================================
//生成
//==============================================
CStencilShadow *CStencilShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_nCreateNum += 1;
	CStencilShadow *pObject = NULL;
	if (pObject == NULL)
	{
		pObject = new CStencilShadow;
		pObject->BindObject(m_pBuffMat[0], m_pNumMat[0], m_pMesh[0]);	//使用するオブジェクト
		pObject->BindTexture(m_pTexture[0]);							//使用する画像
		pObject->Init();
		pObject->SetPos(pos);					//位置の反映
		pObject->SetRot(rot);
	}
	return pObject;
}
//==============================================
//初期化処理
//==============================================
HRESULT CStencilShadow::Init(void)
{
	CSceneX::Init();

	

	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点情報の作成
	VERTEX_2D *pVtx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの位置を設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	
	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//カラー情報
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================
//終了処理
//==============================================
void CStencilShadow::Uninit(void)
{
	m_nCreateNum = 0;

	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CSceneX::Uninit();

}

//==============================================
//更新処理
//==============================================
void CStencilShadow::Update(void)
{
	CSceneX::Update();
	
	CPlayer *pPlayer = CGame::GetPlayer();
	
	SetPos(D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y-30.0f, pPlayer->GetPos().z));
	//Debug();
	
}

//==============================================
//描画処理
//==============================================
void CStencilShadow::Draw(void)
{
	if (CGame::GetDeath() == false)
	{
		//デバイス情報の取得
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);//色の制御

		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_ZERO);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCR);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);//表面カリング
		CSceneX::Draw();//表カリング用モデルの表示

		pDevice->SetRenderState(D3DRS_STENCILREF, 1);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_ZERO);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//裏面カリング
		CSceneX::Draw();//裏面カリング用のモデル表示

		//? カラーを戻す処理
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);

		pDevice->SetRenderState(D3DRS_STENCILREF, 2);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);//すべてを対象に見る
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);//ステンシル、Zテストともに通っている
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);//ステンシルのみ通っている
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);//ステンシルのみ通ってない

		//? 切り抜き用のポリゴン(マスク)の描画
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//? もとに戻す
		pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
}

//==============================================
//使用するオブジェクトの読み込み
//==============================================
HRESULT CStencilShadow::ObjectLoad(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();


	//Xファイルの読み込み
	D3DXLoadMeshFromX("DATA\\MODEL\\shadow001.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat[0],
		NULL,
		&m_pNumMat[0],
		&m_pMesh[0]);


	return S_OK;
}
//==============================================
//使用したオブジェクトの破棄
//==============================================
void CStencilShadow::ObjectUnLoad(void)
{
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		//メッシュの開放
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		//マテリアル関連の開放
		if (m_pNumMat[nCnt] != NULL)
		{
			m_pNumMat[nCnt] = NULL;
		}
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}
	}
}

//==============================================
//オブジェクトに反映させる画像の読み込み
//==============================================
HRESULT CStencilShadow::TextureLoad(void)
{
	FILE *pFile;

	char * pStrCur;//先頭文字列のポインタ
	char aLine[256];//文字列の読み込み
	char aStr[256];//文字列の抜き出し
	int nCntTexture = 0;

	//テキストの読み込み↓
	pFile = fopen(STENCIL_TEXT, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			pStrCur = CSceneX::ReadLine(pFile, &aLine[0]);
			strcpy(&aLine[0], pStrCur);

			if (memcmp(pStrCur, "TEXTURE_LOAD", strlen("TEXTURE_LOAD")) == 0)
			{
				while (1)
				{
					fgets(&aLine[0], 256, pFile);
					pStrCur = CSceneX::GetLIneTop(&aLine[0]);

					//オブジェクトに使用する画像の数
					if (memcmp(pStrCur, "NUM_TEXTURE = ", strlen("NUM_TEXTURE = ")) == 0)
					{
						pStrCur += strlen("NUM_TEXTURE = ");
						strcpy(aStr, pStrCur);
						m_nNumTexture = atoi(aStr);
					}

					//オブジェクトに使用する画像の名前
					if (memcmp(pStrCur, "TEXTURE_NAME ", strlen("TEXTURE_NAME ")) == 0)
					{
						pStrCur += strlen("TEXTURE_NAME ");

						strcpy(aStr, pStrCur);
						while (1)
						{
							if (pStrCur[strlen(pStrCur) - 1] != 'g')
							{
								pStrCur[strlen(pStrCur) - 1] = '\0';//改行文字をNULL文字に変換(参考サイト::http://hisashi.me/blog/?p=714)

							}

							else
							{
								break;
							}

							strcpy(&m_aFileNameTexture[nCntTexture][0], pStrCur);
						}

						nCntTexture += 1;
					}

					//読み込みの終わり
					if (memcmp(pStrCur, "END_TEXTURE_LOAD", strlen("END_TEXTURE_LOAD")) == 0)
					{
						break;
					}
				}

			}
			//読み込みの終わり
			if (memcmp(pStrCur, "END_TEXTURE_LOAD", strlen("END_TEXTURE_LOAD")) == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);

	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	for (int nCnt = 0; nCnt < m_nNumTexture; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aFileNameTexture[nCnt], &m_pTexture[nCnt]);
	}

	return S_OK;
}
//==============================================
//オブジェクトに反映させた画像の破棄
//==============================================
void CStencilShadow::TextureUnLoad(void)
{
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//==============================================
//デバック
//==============================================
void CStencilShadow::Debug(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	//キーボード・コントローラーの取得処理
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputXPad = CManager::GetInputXPad();
	if (m_pInputKeyboard->GetPress(DIK_LEFT) == true)
	{
		pos.x -= 1.0f;
	}
	if (m_pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{
		pos.x += 1.0f;
	}
	SetPos(pos);

	if (m_pInputKeyboard->GetPress(DIK_W) == true)
	{
		rot.x -= 0.05f;
	}
	if (m_pInputKeyboard->GetPress(DIK_S) == true)
	{
		rot.x += 0.05f;
	}
	if (m_pInputKeyboard->GetPress(DIK_A) == true)
	{
		rot.z -= 0.05f;
	}
	if (m_pInputKeyboard->GetPress(DIK_D) == true)
	{
		rot.z += 0.05f;
	}
	SetRot(rot);

	CDebug::DebugLog("\nオブジェクト生成数　%d", m_nCreateNum);

}

