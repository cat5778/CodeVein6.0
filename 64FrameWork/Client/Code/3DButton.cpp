#include "stdafx.h"
#include "3DButton.h"

#include "Export_Function.h"
#include "ThirdPersonCamera.h"

C3DButton::C3DButton(LPDIRECT3DDEVICE9 pGraphicDev, wstring wstrTexName, _float fLength, _float fRotY, _bool bIsRight, UISTATE eUIState)
	: Engine::CGameObject(pGraphicDev),m_wstrTexName(wstrTexName),m_fLength(fLength),m_fRotY(fRotY), m_bIsRight(bIsRight), m_eUIState(eUIState)
{

}

C3DButton::~C3DButton(void)
{

}

HRESULT C3DButton::Ready_GameObject(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_vScale.x = m_pTextureCom->Get_ImageInfo().Width*0.001f;
	m_vScale.y = m_pTextureCom->Get_ImageInfo().Height*0.001f;
	m_vScale.z = m_pTextureCom->Get_ImageInfo().Width*0.001f;
	
	m_pTransformCom->Set_Scale(m_vScale.x, m_vScale.y, m_vScale.z);

	return S_OK;
}

HRESULT C3DButton::LateReady_GameObject(void)
{

	m_pCam=dynamic_cast<CThirdPersonCamera*>(Engine::Get_GameObject(L"UI", L"ThirdPersonCamera"));
	//m_pTargetTransformCom = dynamic_cast<Engine::CTransform*>(Engine::Get_Component(L"UI", L"ThirdPersonCamera", L"Com_Transform", Engine::ID_DYNAMIC));

	return S_OK;
}

_int C3DButton::Update_GameObject(const _float& fTimeDelta)
{
	if (!m_bIsOn)
		return 0;
	ButtonMoveSet();
	
	
	Blink_Image(fTimeDelta, 100.f);

	Engine::CGameObject::Update_GameObject(fTimeDelta);	
	BillBoard();
	m_pRendererCom->Add_RenderGroup(Engine::RENDER_ALPHA, this);




	return 0;
}

void C3DButton::Render_GameObject(void)
{

	LPD3DXEFFECT	pEffect = m_pShaderCom->Get_EffectHandle();
	NULL_CHECK(pEffect);
	pEffect->AddRef();

	_uint	iPassMax = 0;

	SetUp_ConstantTable(pEffect);

	pEffect->Begin(&iPassMax, 0);

	pEffect->BeginPass(1);

	m_pBufferCom->Render_Buffer();

	pEffect->EndPass();

	pEffect->End();

	Safe_Release(pEffect);
}

HRESULT C3DButton::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<Engine::CRcTex*>(Engine::Clone(RESOURCE_STATIC, L"Buffer_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_pComponentMap[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	pComponent = m_pTransformCom = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_pComponentMap[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);

	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>(Engine::Clone(RESOURCE_STAGE, m_wstrTexName.c_str()));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_pComponentMap[Engine::ID_STATIC].emplace(L"Com_Texture", pComponent);

	pComponent = m_pRendererCom = Engine::Get_Renderer();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->AddRef();
	m_pComponentMap[Engine::ID_STATIC].emplace(L"Com_Renderer", pComponent);
	
	pComponent = m_pShaderCom = dynamic_cast<Engine::CShader*>(Engine::Clone_Prototype(L"Shader_3DUI"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_pComponentMap[Engine::ID_STATIC].emplace(L"Com_Shader", pComponent);
	
	return S_OK;
}



HRESULT C3DButton::SetUp_ConstantTable(LPD3DXEFFECT& pEffect)
{
	_matrix			matWorld, matView, matProj;

	m_pTransformCom->Get_WorldMatrix(&matWorld);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", &matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	m_pTextureCom->Set_Texture(pEffect, "g_BaseTexture", _uint(m_fFrameCnt));
	Engine::SetUp_OnShader(pEffect, L"Target_Depth", "g_DepthTexture");
	pEffect->SetFloat("g_TextureA", m_fAlpha);


	return S_OK;
}

void C3DButton::BillBoard()
{
	_vec3 vUp = { 0.f, 1.f, 0.f };
	_vec3 vLook = m_pCam->Get_Look();
	_vec3 vRight;
	D3DXVec3Normalize(&vLook, &vLook);
	D3DXVec3Cross(&vRight, &vUp, &vLook);
	D3DXVec3Normalize(&vRight, &vRight);

	_vec3 vDir;
	m_bIsRight ? vDir = vRight*0.3f + vLook : vDir = vRight*-0.3f + vLook;
	D3DXVec3Normalize(&vDir, &vDir);

	_vec3 vTargetPos = m_pCam->Get_CamPos() + (vDir*m_fLength);
	m_pTransformCom->Set_Pos(vTargetPos.x, vTargetPos.y + m_vPos.y, vTargetPos.z);

	_matrix	matWorld, matView, matBill;

	m_pTransformCom->Get_WorldMatrix(&matWorld);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixIdentity(&matBill);

	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, NULL, &matBill);


	_matrix matY;
	D3DXMatrixRotationY(&matY, D3DXToRadian(m_fRotY));
	m_pTransformCom->Set_WorldMatrix(&(matBill*matY * matWorld));

	Engine::CGameObject::Compute_ViewZ(&m_pTransformCom->m_vInfo[Engine::INFO_POS]);

}

void C3DButton::ChangeEnable(_bool bIsOn)
{
	m_bIsOn = bIsOn;
}

void C3DButton::Blink_Image(_float fTimeDelta, _float fSpeed)
{
	m_fSin += fTimeDelta*fSpeed;

	if (m_fSin > 180.f)
		m_fSin = 0.f;
	m_fAlpha = 1.f - (sinf(D3DXToRadian(m_fSin))*0.5f);


}

void C3DButton::Set_ButtonPos()
{
	switch (m_eUIState)
	{
	case UI_SHOP:
		break;
	case UI_INVEN:
		break;
	case UI_PORTAL:
		break;
	case UI_SHOP_SUB:
	{
		switch (m_uiButtonIdx)
		{
		case RB_MENU_1:
			m_vPos.y = 0.19f;
			break;
		case RB_MENU_2:
			m_vPos.y = 0.08f;
			break;
		case RB_MENU_3:
			m_vPos.y = -0.04f;
			break;
		}
	}	
	break;
	case UI_INVEN_SUB:
	case UI_PORTAL_SUB:
		m_vPos.y = 0.19f;
		break;
	case UI_END:
		break;
	default:
		break;
	}



	switch (m_uiButtonIdx)
	{
	case RB_MENU_1:
		m_vPos.y = 0.19f;
		break;
	case RB_MENU_2:
		m_vPos.y = 0.08f;
		break;
	case RB_MENU_3:
		m_vPos.y = -0.04f;
		break;
	case RB_MENU_END:

		break;

	default:
		break;
	}
}

void C3DButton::ButtonMoveSet()
{

	if (CKeyMgr::GetInstance()->KeyDown(KEY_DOWN))
	{
		if (m_uiButtonIdx > RB_MENU_3)
			m_uiButtonIdx = RB_MENU_3;
		else
			m_uiButtonIdx++;
	}
	else if (CKeyMgr::GetInstance()->KeyDown(KEY_UP))
	{
		if (m_uiButtonIdx < RB_MENU_1)
			m_uiButtonIdx = RB_MENU_1;
		else
			m_uiButtonIdx--;

	}
	Set_ButtonPos();

	if (CKeyMgr::GetInstance()->KeyPressing(KEY_J))
	{
		m_vPos.y = 0.f;
		cout << m_vPos.y << endl;
	}

}

void C3DButton::SelectMode()
{
	m_bIsSelect != m_bIsSelect;

	if (m_bIsSelect)
		m_pTransformCom->Set_Scale(m_vScale.x*0.5f, m_vScale.y*0.5f, m_vScale.z*0.5f);
	else
		m_pTransformCom->Set_Scale(m_vScale.x, m_vScale.y, m_vScale.z);

}

C3DButton* C3DButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, wstring wstrTexName, _float fLength, _float fRotY, _bool bIsLeft, UISTATE eUIState)
{
	C3DButton*	pInstance = new C3DButton(pGraphicDev, wstrTexName, fLength,fRotY,bIsLeft, eUIState);

	if (FAILED(pInstance->Ready_GameObject()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void C3DButton::Free(void)
{


	Engine::CGameObject::Free();
}

