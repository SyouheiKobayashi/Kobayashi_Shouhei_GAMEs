//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//						�^�C�g������ [title.h]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _TITLE_H_
#define _TITLE_H_

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "manager.h"
#include "fade.h"

//==============================================
//					�}�N����`
//==============================================
//#define OBJ_CREATE	(50)


//==============================================
//					�O���錾
//==============================================
class CDebug;
class CSound;
class CLight;
class CCamera;
class CScene2D;
class CPolygon2D;
class CScene3D;
class CMeshField;
class CBillboard;
class CPolygon3D;
class CParticle3D;
class CObject;
class CPlayer;
class CEnemy;
//==============================================
//					  �^�C�g��
//==============================================
class CTitle
{
public:
	//�ǂݍ��񂾃I�u�W�F�N�g�̌����A�ʒu
	typedef struct
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	}OBJECT;

	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CTitle();
	~CTitle();
	static CTitle *Create();

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					��Պ֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					�ǉ��֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	void NullCheck(void);
	void BulkLoadData(void);
	void BulkUnLoadData(void);
	void MAP_LOAD(void);
	void CreateData(void);
	void DebugLoop(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	static CDebug *GetDebug(void) { return m_pDebug; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CPolygon2D *GetPolygon2D(void) { return m_pPolygon2D; }
	static CScene3D *GetScene3D(void) { return m_pScene3D; }
	static CMeshField *GetMeshField(void) { return m_pMeshField; }
	static CBillboard *GetBillboard(void) { return m_pBillboard; }
	static CPolygon3D *GetPolygon3D(void) { return m_pPolygon3D; }
	static CParticle3D *GetParticle3D(void) { return m_pParticle3D; }
	static CObject *GetObj(int nCnt) { return m_pObject[nCnt]; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CEnemy *GetEnemy(void) { return m_pEnemy; }

private:
	static CDebug *m_pDebug;
	static CSound *m_pSound;
	static CLight *m_pLight;
	static CCamera *m_pCamera;
	static CScene2D *m_pScene2D;
	static CPolygon2D *m_pPolygon2D;
	static CScene3D *m_pScene3D;
	static CMeshField *m_pMeshField;
	static CBillboard *m_pBillboard;
	static CPolygon3D * m_pPolygon3D;
	static CParticle3D *m_pParticle3D;
	static CObject *m_pObject[OBJ_CREATE];
	static CPlayer *m_pPlayer;
	static CEnemy *m_pEnemy;

	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//��ʑJ�ڏ���
	CFade::FADE m_pFade;
	bool m_bFadeCheck;
	int m_nFadeStartTime;//�J�ڂ��n�߂鎞��

	//�O���f�[�^����ǂݍ��񂾏���ۊ�
	int m_nMaxObjCreateNum;
	int m_nObjType[50];
	int m_nTexType[50];
	OBJECT m_ObjOffseet[50];

	//�f�o�b�N�p
	int m_nCreateCnt;
	int m_nDebugCnt;
};

#endif

