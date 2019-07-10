//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
//						�Q�[�����������Ԃ����߂鏈�� [timeCharge.h]
//				Author : Kobayashi_Sho-hei / ���� ����
//���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��
#ifndef _TIMECHARGE_H_
#define _TIMECHARGE_H_

//=================================================
//		include / ���̃f�[�^�E�R�[�h�̌Ăяo���E���p
//=================================================
#include "main.h"
#include "manager.h"
#include "fade.h"

//==============================================
//					�}�N����`
//==============================================
#define POLYGON2D_TEX_TC	(5)


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
class CNumber;
class CTime;
class CObject;
class CPlayer;

//==============================================
//			 �������Ԃ����߂鏈��
//==============================================
class CTimeCharge
{
public:
	// @   @   @   @   @   @   @   @   @   @   @   @
	//			�R���X�g���N�^�E�f�X�g���N�^�E����
	// @   @   @   @   @   @   @   @   @   @   @   @
	CTimeCharge();
	~CTimeCharge();
	static CTimeCharge *Create();

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
	void CreateData(void);
	void Event(void);
	void Debug(void);
	void DebugLoop(void);

	// @   @   @   @   @   @   @   @   @   @   @   @
	//					Get�֐�
	// @   @   @   @   @   @   @   @   @   @   @   @
	static CDebug *GetDebug(void) { return m_pDebug; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CPolygon2D *GetPolygon2D(int nCnt) { return m_pPolygon2D[nCnt]; }
	static CScene3D *GetScene3D(void) { return m_pScene3D; }
	static CMeshField *GetMeshField(void) { return m_pMeshField; }
	static CBillboard *GetBillboard(void) { return m_pBillboard; }
	static CPolygon3D *GetPolygon3D(void) { return m_pPolygon3D; }
	static CParticle3D *GetParticle3D(void) { return m_pParticle3D; }
	static CNumber *GetNumber(void) { return m_pNumber; }
	static CTime *GetTime(void) { return m_pTime; }
	static CObject *GetObj(int nCnt) { return m_pObject; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }

	int GetChargeTime(void) { return m_nChargeTime; }//�`���[�W���ꂽ����
	bool GetFlag(void) {return m_bFlag;}//�`���[�W�^�C���̏I��
private:
	static CDebug *m_pDebug;
	static CSound *m_pSound;
	static CLight *m_pLight;
	static CCamera *m_pCamera;
	static CScene2D *m_pScene2D;
	static CPolygon2D *m_pPolygon2D[POLYGON2D_TEX_TC];
	static CScene3D *m_pScene3D;
	static CMeshField *m_pMeshField;
	static CBillboard *m_pBillboard;
	static CPolygon3D * m_pPolygon3D;
	static CParticle3D *m_pParticle3D;
	static CNumber *m_pNumber;
	static CTime * m_pTime;
	static CObject *m_pObject;
	static CPlayer *m_pPlayer;

	//�L�[�{�[�h�E�R���g���[���[�̎擾����
	CInputKeyboard *m_pInputKeyboard;
	CInputXPad *m_pInputXPad;
	CInputMouse *m_pInputMouse;

	//��ʑJ�ڏ���
	CFade::FADE m_pFade;

	int m_nCntTime;
	bool m_bRotationSwitch;
	float m_fRotation;	//���f����]�p
	int m_nChargeTime;	//���Ԃ������璙�߂��̂��L�^����

	int m_nCntChargeTime;//�`���[�W�\����
	bool m_bFlag;//�I���t���O

	bool m_bStartFlag;
	int m_nStartCnt;
	bool m_ChargeStart;

	int m_nDebugCnt;

};

#endif

