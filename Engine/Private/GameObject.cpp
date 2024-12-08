#include "..\Public\GameObject.h"
#include "GameInstance.h"
#include <iostream>

CGameObject::CGameObject()
{
	//Safe_AddRef(m_pGraphic_Device);
}

CGameObject::CGameObject(const CGameObject & Prototype)
{
	//Safe_AddRef(m_pGraphic_Device);
}

void CGameObject::Free()
{
	//Safe_Release(m_pGraphic_Device);
	__super::Free();

	for (auto& elem : m_pComs)
	{
		Safe_Release(elem.second);
	}
	
	m_pComs.clear();

	//delete this;
}

void CGameObject::Broadcast_EventMessage(void* _Arg)
{
	On_EventMessage(_Arg);

	CTransform* myTransform = Get_Component<CTransform>();

	//�ڽ� Ʈ������ ����Ʈ
	list<CTransform*>* Children = myTransform->Get_Children();

	ISVALID(Children, );

	//�³� for��
	for (auto& elem : *Children)
	{
		//������(GameObject) -> Set_Controller
		if (elem)
		{
			elem->Get_Owner()->Broadcast_EventMessage(_Arg);
		}

		
	}
}

void CGameObject::Tick(_float fTimeDelta)
{
	for (auto& elem : m_pComs)
	{
		if (elem.second)
		{
			elem.second->Tick(fTimeDelta);
		}
	}

}

void CGameObject::LateTick(_float fTimeDelta)
{

	for (auto& elem : m_pComs)
	{
		if (elem.second)
		{
			elem.second->LateTick(fTimeDelta);
		}
	}
}

HRESULT CGameObject::Render_Begin(ID3DXEffect** Shader)
{
	for (auto& elem : m_pComs)
	{
		if (elem.second)
		{
			elem.second->Render_Begin(Shader);
		}
	}

	return S_OK;
}

HRESULT CGameObject::Render()
{
	for (auto& elem : m_pComs)
	{
		if (elem.second)
		{
			elem.second->Render();
		}
	}

	return S_OK;
}

void CGameObject::Set_Controller(const CONTROLLER& _eController)
{
	if (m_eController != _eController)
	{
		m_eController = _eController;
		On_Change_Controller(_eController);
	}

	/// �� �Ʒ� �ڵ�� ��������� �� �ڽĵ��� ��Ʈ�ѷ��� ��������.

	//�� Ʈ������ �ޱ�
	CTransform* myTransform = Get_Component<CTransform>();

	//�ڽ� Ʈ������ ����Ʈ
	list<CTransform*>* Children = myTransform->Get_Children();

	ISVALID(Children, );

	//�³� for��
	for (auto& elem : *Children)
	{
		if (elem)
		{
			elem->Get_Owner()->Set_Controller(_eController);
		}

		//������(GameObject) -> Set_Controller
	}

}

void CGameObject::Set_Dead()
{
	m_bDead = true;

	CTransform* pMyTransform = Get_Component<CTransform>();

	if (!pMyTransform)
	{
		return;
	}

	list<CTransform*>* pMyChildren = pMyTransform->Get_Children();

	for (auto& elem : *pMyChildren)
	{
		if(elem)
			elem->Get_Owner()->Set_Dead();
	}

}

void CGameObject::Set_Internal_Tag(const _tchar* _Tag)
{
	m_Tag = _Tag;
}

list<CGameObject*> CGameObject::Get_Children_From_Key(const _tchar* _Key)
{
	list<CGameObject*> Target_Children;

	Add_List_Child_From_Key(_Key, Target_Children);

	return Target_Children;
}

void CGameObject::Add_List_Child_From_Key(const _tchar* _Key, list<CGameObject*>& _List)
{

	CTransform* pMyTransform = Get_Component<CTransform>();

	if (!pMyTransform)
	{
		return;
	}

	//�±װ� ���� ������ ����Ʈ�� ����ش�.
	if (!lstrcmp(_Key, m_Tag))
	{
		_List.push_back(this);
	}

	for (auto& elem : *pMyTransform->Get_Children())
	{
		if(elem)
			elem->Get_Owner()->Add_List_Child_From_Key(_Key, _List);
	}

}




//��Ʈ�ѷ��� ����� �� ȣ��ȴ�.
void CGameObject::On_Change_Controller(const CONTROLLER& _IsAI)
{
	//do nothing.
}

void CGameObject::On_Collision_Enter(CCollider* _Other_Collider)
{
}

void CGameObject::On_Collision_Stay(CCollider* _Other_Collider)
{
}

void CGameObject::On_Collision_Exit(CCollider* _Other_Collider)
{
}

HRESULT CGameObject::Compute_CamDistance(CTransform* pTransform)
{
	

	_float4x4		ViewMatrix;

	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	_float3		vCamDir = *(_float3*)&ViewMatrix.m[3][0] - pTransform->Get_State(CTransform::STATE_POSITION);

	m_fCamDistance = D3DXVec3Length(&vCamDir);


	return S_OK;
}
