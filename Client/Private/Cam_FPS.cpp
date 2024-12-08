#include "stdafx.h"
#include "Cam_FPS.h"
#include "GameInstance.h"

CCam_FPS::CCam_FPS(const CCam_FPS& Prototype)
{
	*this = Prototype;
	Add_Component<CTransform>();
}

HRESULT CCam_FPS::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCam_FPS::Initialize(void* pArg)
{
	//m_szName = L"Cam_FPS";
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.f, 1.f, 0.f));
	m_pTransformCom->LookAt(_float3(0.f, 1.f, 1.f));

	m_pCameraCom = Add_Component<CCamera>();
	m_pCameraCom->Set_WeakPtr(&m_pCameraCom);
	m_pCameraCom->Link_TransformCom(m_pTransformCom);

	////////////////
	//CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	//RigidBodyDesc.m_fOwnerSpeed = 7.f;
	//RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);
	//
	//RigidBodyDesc.m_fFrictional = 0.1f;
	//RigidBodyDesc.m_fRadFrictional = 0.1f;
	//
	//m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	//m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	//m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);
	//////////////////

	return S_OK;
}

void CCam_FPS::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	CTransform* pCamTargetTransformCom = m_pCameraCom->Get_Target();

	if (!pCamTargetTransformCom)
	{
		return;
	}

	_float3 vLook = pCamTargetTransformCom->Get_State(CTransform::STATE_LOOK, true);
	_float3 vPos = pCamTargetTransformCom->Get_State(CTransform::STATE_POSITION, true);
	_float3 vUp = pCamTargetTransformCom->Get_State(CTransform::STATE_UP, true);
	_float3 vRight= pCamTargetTransformCom->Get_State(CTransform::STATE_RIGHT, true);;


	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos, true);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook, true);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp, true);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight, true);

	//m_pTransformCom->LookAt(_float3(0.f, 1.f, 1.f));

}

void CCam_FPS::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CCam_FPS::Render()
{
	__super::Render();

	return S_OK;
}

CCam_FPS* CCam_FPS::Create()
{
	CREATE_PIPELINE(CCam_FPS);
}

CGameObject* CCam_FPS::Clone(void* pArg)
{
	CLONE_PIPELINE(CCam_FPS);
}

void CCam_FPS::Free()
{
	__super::Free();

	delete this;
}
