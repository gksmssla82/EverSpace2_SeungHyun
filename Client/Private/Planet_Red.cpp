#include "stdafx.h"
#include "Planet_Red.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Level_Loading.h"
#include "Dive.h"

CPlanet_Red::CPlanet_Red()
{
}

CPlanet_Red::CPlanet_Red(const CPlanet_Red& Prototype)
{
	*this = Prototype;
}


HRESULT CPlanet_Red::Initialize(void* pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;


	_float3 StartPos = { 1.f, 100.f, 300.f };
	_tchar* PontText = TEXT("Red Planet \n �� ���� ���� \n �ӹ� : ȭ���� ȣ��  \n  ���̵� :���ڡڡڡڡڡ�  \n ���� : XXX");
	_point PontPos = { (LONG)m_vScreenPos.x + 40, (LONG)m_vScreenPos.y - 10 };
	_float3 MyScale = _float3(100.f, 100.f, 50.f);
	_uint TextureIndex = 2;

	SetUp_Varialbes_For_Child(StartPos, PontText, PontPos, TextureIndex, LEVEL::LEVEL_REDPLANET, MyScale);

	m_pDiveUi = GAMEINSTANCE->Add_GameObject<CDive>(LEVEL_SELECTPLANET, TEXT("Dive"));
	m_pDiveUi->Set_Enable(false);


	return S_OK;
}

void CPlanet_Red::SetUp_Components_For_Child()
{
}



	

CPlanet_Red* CPlanet_Red::Create()
{
	CREATE_PIPELINE(CPlanet_Red);
}

CGameObject* CPlanet_Red::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlanet_Red);
}

void CPlanet_Red::Free()
{
	__super::Free();

	delete this;
}

