#include "stdafx.h"
#include "Planet_Exo.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Level_Loading.h"
#include "Dive.h"

CPlanet_Exo::CPlanet_Exo()
{
}

CPlanet_Exo::CPlanet_Exo(const CPlanet_Exo& Prototype)
{
	*this = Prototype;
}

HRESULT CPlanet_Exo::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float3 StartPos = { -400.f, 100.f, 250.f };
	_tchar* FontText = TEXT("Exo Planet \n �� ���� ���� \n \n �ӹ� : ���� \n ���̵� :���ڡڡڡ�  \n ���� : XXX");
	_point PontPos = { (LONG)m_vScreenPos.x + 40, (LONG)m_vScreenPos.y - 10 };
	_float3 MyScale = _float3(100.f, 100.f, 50.f);
	_uint TextureIndex = 1;
	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(-250.f, 200.f, 250.f));

	m_pDiveUi = GAMEINSTANCE->Add_GameObject<CDive>(LEVEL_SELECTPLANET, TEXT("Dive"));
	m_pDiveUi->Set_Enable(false);


	SetUp_Varialbes_For_Child(StartPos, FontText, PontPos, TextureIndex, LEVEL::LEVEL_EXOPLANET, MyScale);

	return S_OK;
}


void CPlanet_Exo::SetUp_Components_For_Child()
{
	
}


CPlanet_Exo* CPlanet_Exo::Create()
{
	CREATE_PIPELINE(CPlanet_Exo);
}

CGameObject* CPlanet_Exo::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlanet_Exo);
}

void CPlanet_Exo::Free()
{
	__super::Free();

	delete this;
}
