#ifndef ThreeDUI_h__
#define ThreeDUI_h__

#include "Defines.h"
#include "GameObject.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;
class CRenderer;
class CShader;

END
class CThirdPersonCamera;
class C3DButton;
class C3DUI : public Engine::CGameObject
{
private:
	explicit C3DUI(LPDIRECT3DDEVICE9 pGraphicDev, wstring wstrTexName, _float fLength, _float fRotY, _bool bIsRight, UISTATE eUIState);
	virtual ~C3DUI(void);

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual HRESULT	LateReady_GameObject(void);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	
	virtual void Render_GameObject(void) override;


public:
	void		ChangeEnable();
	void		ChangeEnable(_bool bIsEnable);
	void		InteractionUI();
	_bool		IsOn() { return m_bIsOn; }
	wstring		Get_ItemName();
private:
	HRESULT		Add_Component(void);
	HRESULT		SetUp_ConstantTable(LPD3DXEFFECT& pEffect);
	void		BillBoard();
	void		TestPos();
	void		InsertSlot();
private:

	Engine::CRcTex*			m_pBufferCom = nullptr;
	Engine::CTexture*		m_pTextureCom = nullptr;
	Engine::CTransform*		m_pTransformCom = nullptr;
	//Engine::CTransform*		m_pTargetTransformCom = nullptr;
	Engine::CRenderer*		m_pRendererCom = nullptr;
	Engine::CShader*		m_pShaderCom = nullptr;
	CThirdPersonCamera*		m_pCam = nullptr;
	wstring					m_wstrTexName = L"";
	_vec3					m_vScale;
	_float					m_fFrameCnt = 0;
	_float					m_fFrameMax = 90.f;
	_float					m_fRotY=0.f;
	_float					m_fLength = 0.f;
	_matrix					m_matBill;
	_bool					m_bIsRight = true;
	UISTATE					m_eUIState;
	C3DButton*				m_pButton= nullptr;
	_bool					m_bIsOn = false;
	wstring					m_wstrItem;

public:
	static C3DUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev,  wstring wstrTexName, _float fLength,_float fRotY,_bool bIsRight =true, UISTATE eUIState=UI_END);

private:
	virtual void Free(void) override;
};

#endif // ThreeDUI_h__
