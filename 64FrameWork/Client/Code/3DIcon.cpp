//#include "stdafx.h"
//#include "3DIcon.h"
//
//#include "Export_Function.h"
//#include "ThirdPersonCamera.h"
//
//CIcon::CIcon(LPDIRECT3DDEVICE9 pGraphicDev, wstring wstrTexName, _matrix worldMap)
//	: Engine::CGameObject(pGraphicDev),m_wstrTexName(wstrTexName)
//{
//		m_TargetWorld = worldMap;
//}
//
//CIcon::~CIcon(void)
//{
//
//}
//
//HRESULT CIcon::Ready_GameObject(void)
//{
//	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
//	m_vScale.x = m_pTextureCom->Get_ImageInfo().Width*0.001f;
//	m_vScale.y = m_pTextureCom->Get_ImageInfo().Height*0.001f;
//	m_vScale.z = m_pTextureCom->Get_ImageInfo().Width*0.001f;
//	
//	m_pTransformCom->Set_Scale(m_vScale.x, m_vScale.y, m_vScale.z);
//
//	return S_OK;
//}
//
//HRESULT CIcon::LateReady_GameObject(void)
//{
//
//	m_pCam=dynamic_cast<CThirdPersonCamera*>(Engine::Get_GameObject(L"UI", L"ThirdPersonCamera"));
//
//	return S_OK;
//}
//
//_int CIcon::Update_GameObject(const _float& fTimeDelta)
//{
//	if (!m_bIsOn)
//		return 0;
//	
//
//
//	Engine::CGameObject::Update_GameObject(fTimeDelta);	
//	
//	m_pRendererCom->Add_RenderGroup(Engine::RENDER_ALPHA, this);
//
//
//	//TestPos();
//
//
//	return 0;
//}
//
//void CIcon::Render_GameObject(void)
//{
//
//	LPD3DXEFFECT	pEffect = m_pShaderCom->Get_EffectHandle();
//	NULL_CHECK(pEffect);
//	pEffect->AddRef();
//
//	_uint	iPassMax = 0;
//
//	SetUp_ConstantTable(pEffect);
//
//	pEffect->Begin(&iPassMax, 0);
//
//	pEffect->BeginPass(1);
//
//	m_pBufferCom->Render_Buffer();
//
//	pEffect->EndPass();
//
//	pEffect->End();
//
//	Safe_Release(pEffect);
//}
//
//HRESULT CIcon::Add_Component(void)
//{
//	Engine::CComponent*		pComponent = nullptr;
//
//	pComponent = m_pBufferCom = dynamic_cast<Engine::CRcTex*>(Engine::Clone(RESOURCE_STATIC, L"Buffer_RcTex"));
//	NULL_CHECK_RETURN(pComponent, E_FAIL);
//	m_pComponentMap[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);
//
//	pComponent = m_pTransformCom = Engine::CTransform::Create();
//	NULL_CHECK_RETURN(pComponent, E_FAIL);
//	m_pComponentMap[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);
//
//	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>(Engine::Clone(RESOURCE_STAGE, m_wstrTexName.c_str()));
//	NULL_CHECK_RETURN(pComponent, E_FAIL);
//	m_pComponentMap[Engine::ID_STATIC].emplace(L"Com_Texture", pComponent);
//
//	pComponent = m_pRendererCom = Engine::Get_Renderer();
//	NULL_CHECK_RETURN(pComponent, E_FAIL);
//	pComponent->AddRef();
//	m_pComponentMap[Engine::ID_STATIC].emplace(L"Com_Renderer", pComponent);
//	
//	pComponent = m_pShaderCom = dynamic_cast<Engine::CShader*>(Engine::Clone_Prototype(L"Shader_3DUI"));
//	NULL_CHECK_RETURN(pComponent, E_FAIL);
//	m_pComponentMap[Engine::ID_STATIC].emplace(L"Com_Shader", pComponent);
//	
//	return S_OK;
//}
//
//
//
//HRESULT CIcon::SetUp_ConstantTable(LPD3DXEFFECT& pEffect)
//{
//	_matrix			matWorld, matView, matProj;
//
//	m_pTransformCom->Get_WorldMatrix(&m_TargetWorld);
//	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
//	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
//
//	pEffect->SetMatrix("g_matWorld", &matWorld);
//	pEffect->SetMatrix("g_matView", &matView);
//	pEffect->SetMatrix("g_matProj", &matProj);
//
//	m_pTextureCom->Set_Texture(pEffect, "g_BaseTexture", _uint(m_fFrameCnt));
//	Engine::SetUp_OnShader(pEffect, L"Target_Depth", "g_DepthTexture");
//	pEffect->SetFloat("g_TextureA", m_fAlpha);
//
//
//	return S_OK;
//}
//
//CIcon * CIcon::Create(LPDIRECT3DDEVICE9 pGraphicDev, wstring wstrTexName, _matrix worldMap)
//{
//	CIcon*	pInstance = new CIcon(pGraphicDev, wstrTexName, worldMap);
//
//	if (FAILED(pInstance->Ready_GameObject()))
//		Engine::Safe_Release(pInstance);
//
//	return pInstance;
//}
//
//void CIcon::Free(void)
//{
//
//
//	Engine::CGameObject::Free();
//}
//
