//#ifndef ThreeDIcon_h__
//#define ThreeDIcon_h__
//
//#include "Defines.h"
//#include "GameObject.h"
//
//BEGIN(Engine)
//
//class CRcTex;
//class CTexture;
//class CTransform;
//class CRenderer;
//class CShader;
//
//END
//class CThirdPersonCamera;
//
//class CIcon : public Engine::CGameObject
//{
//private:
//	explicit CIcon(LPDIRECT3DDEVICE9 pGraphicDev, wstring wstrTexName,_matrix worldMap);
//	virtual ~CIcon(void);
//
//public:
//	virtual HRESULT Ready_GameObject(void) override;
//	virtual HRESULT	LateReady_GameObject(void);
//	virtual _int Update_GameObject(const _float& fTimeDelta) override;
//	virtual void Render_GameObject(void) override;
//
//
//private:
//	HRESULT		Add_Component(void);
//	HRESULT		SetUp_ConstantTable(LPD3DXEFFECT& pEffect);
//
//	_bool			IsOn() { return m_bIsOn; }
//
//private:
//	Engine::CRcTex*			m_pBufferCom = nullptr;
//	Engine::CTexture*		m_pTextureCom = nullptr;
//	Engine::CTransform*		m_pTransformCom = nullptr;
//	Engine::CTransform*		m_pTargetTransformCom = nullptr;
//	Engine::CRenderer*		m_pRendererCom = nullptr;
//	Engine::CShader*		m_pShaderCom = nullptr;
//	CThirdPersonCamera*		m_pCam = nullptr;
//	wstring					m_wstrTexName = L"";
//	_vec3					m_vScale;
//	_bool					m_bIsOn = false;
//	_bool					m_bIsSelectParent=false;
//	_float					m_fSin = 0.f;
//	_float					m_fAlpha = 1.f;
//	_float					m_fFrameCnt = 0;
//	_float					m_fFrameMax = 90.f;
//	_float					m_fRotY=0.f;
//	_float					m_fLength = 0.f;
//	_vec3					m_vPos = { INIT_VEC3 };
//	_bool					m_bIsRight = true;
//	_bool					m_bIsSelect = false;
//	_uint					m_uiButtonIdx =0;
//	_bool					m_iSelectMode=false;
//	UISTATE					m_eUIState;
//	_matrix					m_TargetWorld;
//
//	_vec3					m_vConvertPos;
//	wstring					m_wstrItem;
//
//public:
//	static CIcon*		Create(LPDIRECT3DDEVICE9 pGraphicDev,  wstring wstrTexName, _matrix worldMap);
//
//private:
//	virtual void Free(void) override;
//};
//
//#endif // ThreeDIcon_h__
