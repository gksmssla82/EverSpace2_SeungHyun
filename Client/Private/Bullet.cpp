#include "stdafx.h"
#include "Bullet.h"
#include "GameInstance.h"

CBullet::CBullet()
{
}

void CBullet::Tick(_float fTimeDelta)
{
    __super::Tick(fTimeDelta);

	if (m_fLifeTime < 0.f)
	{
		//Set_Dead();
		Set_Enable(false);
	}

	m_fLifeTime -= fTimeDelta;

}

void CBullet::LateTick(_float fTimeDelta)
{
    __super::LateTick(fTimeDelta);

}

HRESULT CBullet::SetUp_Components(COLLISION_TYPE _eCollisionType)
{
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);



	/*_float3 ColliderSize = m_pTransformCom->Get_Scaled();
	_float3 RenderScale = _float3(0.2f, 0.2f, 0.2f);
	ColliderSize.x *= RenderScale.x;
	ColliderSize.y *= RenderScale.y;
	ColliderSize.z *= RenderScale.z;

	m_pColliderCom->Set_Collider_Size(ColliderSize);*/

	SetUp_Components_For_Child(_eCollisionType);

    return S_OK;
}

void CBullet::Init_BulletPosition(_float4x4* _pWorldMat)
{
	//�Ѿ��� ���� ����� �θ� ���� ������ ���� ����� �ȴ�.
	m_pTransformCom->Set_LocalMatrix(*_pWorldMat);
}

void CBullet::OnEnable(void* _Arg)
{
	D3DXMATRIX IdentityMat;
	D3DXMatrixIdentity(&IdentityMat);

	m_fLifeTime = m_fMaxTime;
	m_pTransformCom->Set_LocalMatrix(IdentityMat);
	m_pRigidBodyCom->SetUp_Origin_DirVector();
	m_pRigidBodyCom->Reset_Force();

	
	
}

void CBullet::OnDisable()
{

}


void CBullet::Free()
{
    __super::Free();
}
