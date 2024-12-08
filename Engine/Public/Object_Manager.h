#pragma once

/* ��ü���� ������ �����ϳ�. */
/* ������ü�� ã�Ƽ� �����Ͽ� ��(����)���� ��Ƽ� �����ϴ�.*/

#include "Base.h"

BEGIN(Engine)

class CTransform;
class CParticleSystem;

class CObject_Manager final : public CBase
{
	DECLARE_SINGLETON(CObject_Manager)
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;

public:
	HRESULT Reserve_Container(_uint iNumLevels);

public:
	/* ������ü�� �߰��Ѵ�. */
	class CGameObject* Get_Player();


	void Tick(_float fTimeDelta);
	void Object_Tick(list<CGameObject*>* _ObjList, _float fTimeDelta);
	void LateTick(_float fTimeDelta);
	void Remove_Dead_Object();

public:
	void Clear(_uint iLevelIndex);


private:
	map<const _char*, class CGameObject*>			m_Prototypes;
	typedef map<const _char*, class CGameObject*>	PROTOTYPES;

private:

	vector<map<const _tchar*, list<CGameObject*>>>				m_pLayers;
	typedef map<const _tchar*, list<CGameObject*>>	LAYERS;
	_uint					m_iNumLevels = 0;


private:
	class CGameObject* Find_Prototype(const _char* pPrototypeTag);
	
public:
	list<CGameObject*>* Find_Layer(_uint iLevelIndex, const _tchar* pLayerTag);

public:
	virtual void Free() override;

public: /* Template Function */
	template <typename T>
	T* Add_Prototype()
	{
		static_assert(is_base_of<CGameObject, T>::value, "T Isn't base of CGameObject");

		T* pInstance = T::Create();

		m_Prototypes.emplace(typeid(T).name(), pInstance);

		return pInstance;
	}
	
	template <typename T>
	T* Add_GameObject(_uint iLevelIndex, const _tchar* pLayerTag, CTransform* pParent = nullptr ,void* pArg = nullptr, _bool _bMemoryPool = false)
	{
		static_assert(is_base_of<CGameObject, T>::value, "T Isn't base of CGameObject");

		if (m_iNumLevels <= iLevelIndex)
		{
			//�߸��� ���� �ε���
#ifdef _DEBUG
			assert(false);
#endif
			return nullptr;
		}

		CGameObject* pPrototype = nullptr;

		auto iter = find_if(m_Prototypes.begin(), m_Prototypes.end(), CTag_Finder_c_str(typeid(T).name()));

		if (iter != m_Prototypes.end())
		{
			pPrototype = (*iter).second;
		}

		if (nullptr == pPrototype)
		{
			pPrototype = Add_Prototype<T>();
		}

		if (_bMemoryPool)
		{
			for (auto& elem : m_pLayers[iLevelIndex][pLayerTag])
			{
				if (!elem->Get_Enable())
				{
					elem->Set_Enable(true, pArg);
					
					return static_cast<T*>(elem);
				}
			}
		}


		CGameObject* pCloneObject = pPrototype->Clone(pArg);

		pCloneObject->Set_Internal_Tag(pLayerTag);

		if (nullptr == pCloneObject)
			return nullptr;

		m_pLayers[iLevelIndex][pLayerTag].push_back(pCloneObject);

		if (pParent)
		{
			CTransform* pTransfromCom = pCloneObject->Get_Component<CTransform>();
			pTransfromCom->Set_Parent(pParent);
			pParent->Add_Child(pTransfromCom);
		}
		pCloneObject->OnEnable(pArg);

		return static_cast<T*>(pCloneObject);
	}

	template <typename T>
	CGameObject* Get_ParticleSystem(_uint iLevelIndex, const _tchar* pLayerTag, CTransform* pParent = nullptr, void* pArg = nullptr)
	{
		static_assert(is_base_of<CParticleSystem, T>::value, "T Isn't base of CParticleSystem");

		if (m_iNumLevels <= iLevelIndex)
		{
			//�߸��� ���� �ε���
#ifdef _DEBUG
			assert(false);
#endif
			return nullptr;
		}

		CGameObject* pPrototype = nullptr;

		auto iter = find_if(m_Prototypes.begin(), m_Prototypes.end(), CTag_Finder_c_str(typeid(T).name()));

		if (iter != m_Prototypes.end())
		{
			pPrototype = (*iter).second;
		}

		if (nullptr == pPrototype)
		{
			pPrototype = Add_Prototype<T>();
		}

		for (auto& elem : m_pLayers[iLevelIndex][pLayerTag])
		{
			elem->Set_Enable(true, pArg);

			return elem;
		}


		CGameObject* pCloneObject = pPrototype->Clone(pArg);

		pCloneObject->Set_Internal_Tag(pLayerTag);

		if (nullptr == pCloneObject)
			return nullptr;

		m_pLayers[iLevelIndex][pLayerTag].push_back(pCloneObject);

		if (pParent)
		{
			CTransform* pTransfromCom = pCloneObject->Get_Component<CTransform>();
			pTransfromCom->Set_Parent(pParent);
			pParent->Add_Child(pTransfromCom);
		}
		pCloneObject->OnEnable();

		return pCloneObject;
	}
};

END