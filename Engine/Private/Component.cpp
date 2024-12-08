#include "..\Public\Component.h"

CComponent::CComponent()
{
	//Safe_AddRef(m_pGraphic_Device);
}

CComponent::CComponent(const CComponent & Prototype)
{
	//Safe_AddRef(m_pGraphic_Device);
}

HRESULT CComponent::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CComponent::Initialize(void * pArg)
{
	return S_OK;
}

HRESULT CComponent::Set_Owner(CGameObject* _pOwner)
{
	m_pOwner = _pOwner;
	return S_OK;
}

CGameObject* CComponent::Get_Owner()
{
	return m_pOwner;
}

void CComponent::Free()
{
	__super::Free();


	//Safe_Release(m_pGraphic_Device);
}