#ifndef ThreeDButton_h__
#define ThreeDButton_h__

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

class C3DButton : public Engine::CGameObject
{
private:
	explicit C3DButton(LPDIRECT3DDEVICE9 pGraphicDev, wstring wstrTexName, _float fLength, _float fRotY, _bool bIsRight, UISTATE eUIState);
	virtual ~C3DButton(void);

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual HRESULT	LateReady_GameObject(void);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void Render_GameObject(void) override;


private:
	HRESULT		Add_Component(void);
	HRESULT		SetUp_ConstantTable(LPD3DXEFFECT& pEffect);
	void		BillBoard();
public:
	void			ChangeEnable(_bool bIsOn);

private:
	
	void			Blink_Image(_float fTimeDelta, _float fSpeed);
	void			Set_ButtonPos();
	void			ButtonMoveSet();
	void			SelectMode();
private:
	Engine::CRcTex*			m_pBufferCom = nullptr;
	Engine::CTexture*		m_pTextureCom = nullptr;
	Engine::CTransform*		m_pTransformCom = nullptr;
	Engine::CTransform*		m_pTargetTransformCom = nullptr;
	Engine::CRenderer*		m_pRendererCom = nullptr;
	Engine::CShader*		m_pShaderCom = nullptr;
	CThirdPersonCamera*		m_pCam = nullptr;
	wstring					m_wstrTexName = L"";
	_vec3					m_vScale;
	_bool					m_bIsOn = false;
	_float					m_fSin = 0.f;
	_float					m_fAlpha = 1.f;
	_float					m_fFrameCnt = 0;
	_float					m_fFrameMax = 90.f;
	_float					m_fRotY=0.f;
	_float					m_fLength = 0.f;
	_vec3					m_vPos = { INIT_VEC3 };
	_bool					m_bIsRight = true;
	_bool					m_bIsSelect = false;
	_uint					m_uiButtonIdx =0;
	_bool					m_iSelectMode=false;
	UISTATE					m_eUIState;
	const _matrix*				m_pTargetWorld=nullptr;
public:
	static C3DButton*		Create(LPDIRECT3DDEVICE9 pGraphicDev,  wstring wstrTexName, _float fLength,_float fRotY,_bool bIsRight =true,UISTATE eUIState=UI_END);

private:
	virtual void Free(void) override;
};

#endif // ThreeDButton_h__
