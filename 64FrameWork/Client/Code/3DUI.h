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

class C3DUI : public Engine::CGameObject
{
private:
	explicit C3DUI(LPDIRECT3DDEVICE9 pGraphicDev, wstring wstrTexName);
	virtual ~C3DUI(void);

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual HRESULT	LateReady_GameObject(void);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void Render_GameObject(void) override;

private:
	HRESULT		Add_Component(void);
	HRESULT		SetUp_ConstantTable(LPD3DXEFFECT& pEffect);

private:
	Engine::CRcTex*			m_pBufferCom = nullptr;
	Engine::CTexture*		m_pTextureCom = nullptr;
	Engine::CTransform*		m_pTransformCom = nullptr;
	Engine::CTransform*		m_pTargetTransformCom = nullptr;
	Engine::CRenderer*		m_pRendererCom = nullptr;
	Engine::CShader*		m_pShaderCom = nullptr;

	wstring					m_wstrTexName = L"";
	_vec3					m_vScale;
	_float					m_fFrameCnt = 0;
	_float					m_fFrameMax = 90.f;
	
	_matrix					m_matBill;

public:
	static C3DUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev,  wstring wstrTexName);

private:
	virtual void Free(void) override;
};

#endif // ThreeDUI_h__
