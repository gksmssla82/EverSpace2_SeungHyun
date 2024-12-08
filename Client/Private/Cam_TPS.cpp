#include "stdafx.h"
#include "Cam_TPS.h"
#include "GameInstance.h"
#include "Math_Utillity.h"

CCam_TPS::CCam_TPS(const CCam_TPS& Prototype)
{
	*this = Prototype;
	Add_Component<CTransform>();
}

HRESULT CCam_TPS::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCam_TPS::Initialize(void* pArg)
{
	
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom); 

	m_pCameraCom = Add_Component<CCamera>();
	m_pCameraCom->Set_WeakPtr(&m_pCameraCom);

	m_pCameraCom->Link_TransformCom(m_pTransformCom);

	m_vCurPos = _float3(0.f, 0.f, 0.f);

	return S_OK;
}

void CCam_TPS::Tick(_float fTimeDelta)
{
	if (GAMEINSTANCE->Get_Camera(CURRENT_CAMERA) == m_pCameraCom)
	{
		__super::Tick(fTimeDelta);


		CTransform* pCamTargetTransformCom = m_pCameraCom->Get_Target();

		if (!pCamTargetTransformCom)
		{
			return;
		}


		if (!pCamTargetTransformCom->Get_Owner()->Get_Enable())
		{
			return;
		}

		_float3 vLook = pCamTargetTransformCom->Get_State(CTransform::STATE_LOOK, true);
		_float3 vPos = pCamTargetTransformCom->Get_State(CTransform::STATE_POSITION, true);
		_float3 vUp = pCamTargetTransformCom->Get_State(CTransform::STATE_UP, true);

		_float3 vRight;
		_float  fRatio = 0.f;
		CRigid_Body* pTargetRigidBody = pCamTargetTransformCom->Get_Owner()->Get_Component<CRigid_Body>();
		if (pTargetRigidBody)
		{
			_float3 vTargetSpeed = pTargetRigidBody->Get_Vector(RIGID_BODY::SPEED);
			_float	fMaxSpeed = pTargetRigidBody->Get_RigidDesc().m_fBoosterSpeed;

			if (0.f > D3DXVec3Dot(&vLook, &vTargetSpeed))
				fRatio = 0.f;
			else
			{
				fRatio = D3DXVec3Length(&vTargetSpeed) / fMaxSpeed;
				if (1.f < fRatio)
					fRatio = 1.f;
			}

		}
		m_fCurTime -= fTimeDelta;

		if (0.f > m_fCurTime)
		{
			m_fMovement = CMath_Utillity::fLerp(m_fMovement, 10 * fRatio, 0.03f);

		}


		vPos -= vLook * (15.f + m_fMovement);
		vPos += vUp * 3.f;

		D3DXVec3Cross(&vRight, &vUp, &vLook);
		D3DXVec3Cross(&vUp, &vLook, &vRight);


		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		if (0.f > m_fCurTime)
		{
			m_vCurPos.x = CMath_Utillity::fLerp(m_vCurPos.x, pt.x - g_iWinCX * 0.5f, 0.01f);
			m_vCurPos.y = CMath_Utillity::fLerp(m_vCurPos.y, pt.y - g_iWinCY * 0.5f, 0.01f);
			m_fCurTime = m_fLerpTime;
		}

		vPos += vRight * m_vCurPos.x * 0.01f;
		vPos -= vUp * m_vCurPos.y * 0.01f;

		D3DXMATRIX	matRotation;
		_float fRadian = m_vCurPos.x * 0.001f;
		if (D3DXToRadian(30.f) < fabs(fRadian))
		{
			if (0.f < fRadian)
				fRadian = D3DXToRadian(30.f);
			else if (0.f > fRadian)
				fRadian = -1.f * D3DXToRadian(30.f);
		}
		//����ü ������ ���� ���ؼ�
		D3DXMatrixRotationAxis(&matRotation, &vLook, fRadian);

		D3DXVec3TransformNormal(&vUp, &vUp, &matRotation);
		D3DXVec3Cross(&vRight, &vUp, &vLook);


		m_ptPrePos = pt;


		m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);
		m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
		m_pTransformCom->Update_WorldMatrix();
	}
	else
	{
		m_fMovement = 0.f;
		m_vCurPos.x = 0.f;
		m_vCurPos.y = 0.f;
		m_fCurTime = m_fLerpTime;
	} 
}

void CCam_TPS::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	
}

HRESULT CCam_TPS::Render()
{
	__super::Render();

	return S_OK;
}

CCam_TPS* CCam_TPS::Create()
{
	CREATE_PIPELINE(CCam_TPS);
}

CGameObject* CCam_TPS::Clone(void* pArg)
{
	CLONE_PIPELINE(CCam_TPS);
}

void CCam_TPS::Free()
{
	__super::Free();

	delete this;
}
