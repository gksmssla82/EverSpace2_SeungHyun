#pragma once
/* ������Ʈ���� ������ ������ �ִ´�. */
#include "Renderer.h"
#include "VIBuffer_Rect.h"
#include "VIBuffer_Terrain.h"
#include "VIBuffer_Cube.h"
#include "Transform.h"
#include "Mesh_Cube.h"
#include "Mesh_Terrain.h"
#include "Camera.h"
#include "Status.h"
#include "Font.h"
#include "Rigid_Body.h"
#include "Collider.h"
#include "Collider_OBB.h"
#include "Collier_Sphere.h"
#include "Collider_Ray.h"
#include "State_Move.h"
#include "Targeting.h"
#include "Mesh_Test.h"
#include "Mesh_SongShip.h"
#include "Collider_Pre.h"
#include "Controller.h"
#include "AI_Controller.h"
#include "Player_Controller.h"
#include "Lock_Controller.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "Mesh_KangShip.h"
#include "Mesh_EnemySpace.h"
#include "Mesh_ShinShip.h"
#include "Mesh_Canon.h"
#include "Mesh_HongShip.h"
#include "Mesh_Ship1.h"
#include "Mesh_Ship2.h"
#include "Mesh_Ship3.h"
#include "Mesh_Ship4.h"
#include "Mesh_Ship5.h"
#include "Mesh_Ship6.h"
#include "Collider_Mesh.h"


BEGIN(Engine)

class CComponent_Manager final : public CBase
{
	DECLARE_SINGLETON(CComponent_Manager)
public:
	CComponent_Manager();
	virtual ~CComponent_Manager() = default;

public:
	//HRESULT Reserve_Container(_uint iNumLevels);
	CComponent* Add_Prototype(const _char* pPrototypeTag, class CComponent* pPrototype);


private:
	_uint			m_iNumLevels = 0;

	map<const _char*, class CComponent*>				m_pPrototypes;
	typedef map<const _char*, class CComponent*>		PROTOTYPES;

private:
	class CComponent* Find_Components(const _char* pPrototypeTag);

public:
	virtual void Free() override;

public: /* Template Function*/
	template <typename T>
	T* Clone_Component(void* pArg)
	{
		/*
		T�� ������Ʈ�� ��� �޴��� �˻��մϴ�.
		��? T�� ������Ʈ�� �ƴ� �ٸ� Ŭ������ ������ ���� ������ �����մϴ�.
		*/
		static_assert(is_base_of<CComponent, T>::value, "T isn't base of CComponent : CComponent_Manager");
		
		CComponent** pPrototype = nullptr;
		/*Find_Components*/
		auto	iter = find_if(m_pPrototypes.begin(), m_pPrototypes.end(), CTag_Finder_c_str(typeid(T).name()));

		if (iter != m_pPrototypes.end())
		{
			pPrototype = &iter->second;
		}

		if (nullptr == pPrototype)
		{
			/*Add_Prototype*/
			CComponent* T_Instance = T::Create();

			m_pPrototypes.emplace(typeid(T).name(), T_Instance);

			return static_cast<T*>(T_Instance->Clone(pArg));
		}

		return static_cast<T*>((*pPrototype)->Clone(pArg));
	}
};

END