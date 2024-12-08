#include "stdafx.h"
#include "TransportShip_HpBar.h"
#include "GameInstance.h"


CTransportShip_HpBar::CTransportShip_HpBar(const CTransportShip_HpBar& Prototype)
{
	*this = Prototype;

	m_pTransformCom = Add_Component<CTransform>();


}

HRESULT CTransportShip_HpBar::Initialize_Prototype()
{

	return S_OK;
}

HRESULT CTransportShip_HpBar::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinCX, g_iWinCY, 0.0f, 1.f);

	/*m_fX = 640.f;
	m_fY = 85.f;*/

	m_fX = 640.f;
	m_fY = 85.f;

	m_fSizeX = 380.0f;
	m_fSizeY = 8.f;


	return S_OK;
}

void CTransportShip_HpBar::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

    list<CGameObject*>* ShipLayer =  GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("TransportShip"));

	if (!ShipLayer)
	{
		return;
	}

	CGameObject* ShipObject = (*ShipLayer).back();

	if (ShipObject)
	{
		CStatus* pShipStatusCom = ShipObject->Get_Component<CStatus>();

		if (pShipStatusCom->Get_Status().fHp != pShipStatusCom->Get_Status().fMaxHp)
		{
			_float Damage = pShipStatusCom->Get_Status().fMaxHp - pShipStatusCom->Get_Status().fHp;

			_float AfterHp = pShipStatusCom->Get_Status().fMaxHp - Damage;

			if (pShipStatusCom->Get_Status().fHp <= AfterHp)
			{
				for (int i = 1; i < Damage + 1; ++i)
				{
					if (m_fX <= 640.f * AfterHp / (pShipStatusCom->Get_Status().fMaxHp) ||
						m_fSizeX <= 380.f * AfterHp / (pShipStatusCom->Get_Status().fMaxHp))
					{
						m_fX = 0.050 * i + 640.f * AfterHp / (pShipStatusCom->Get_Status().fMaxHp);
						m_fSizeX = 380.f * AfterHp / (pShipStatusCom->Get_Status().fMaxHp);
					}
				}

				if (pShipStatusCom->Get_Status().fHp <= 0)
				{
					m_fX = 260;
					m_fSizeX = 0;
				}

				else
					m_fX -= 0.3f;
				m_fSizeX -= 0.3f;
			}
		}
	}
	

	m_pTransformCom->Scaling(_float3(m_fSizeX, m_fSizeY, 1.f) * 2);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - (g_iWinCX >> 1), -m_fY + (g_iWinCY >> 1), 0.f));

	SetRect(&m_rcRect, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f,
		m_fX + m_fSizeX * 0.5f, m_fY + m_fSizeY * 0.5f);

}

void CTransportShip_HpBar::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);



	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_UI, this);
}

HRESULT CTransportShip_HpBar::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	m_pRendererCom->Bind_Texture(0);



	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 120);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	_float4x4 CurView, CurProj;
	DEVICE->GetTransform(D3DTS_VIEW, &CurView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &CurProj);

	_float4x4	ViewMatrix;
	D3DXMatrixIdentity(&ViewMatrix);

	DEVICE->SetTransform(D3DTS_VIEW, &ViewMatrix);
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	m_pVIBufferCom->Render();

	m_pRendererCom->UnBind_Texture();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	DEVICE->SetTransform(D3DTS_VIEW, &CurView);
	DEVICE->SetTransform(D3DTS_PROJECTION, &CurProj);



	return S_OK;

}






void CTransportShip_HpBar::Update_Hp_Bar(CStatus* pStatus)
{
	m_pStatusCom = pStatus;
}

HRESULT CTransportShip_HpBar::SetUp_Components()
{
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("TransportShip_HP_Bar"), MEMORY_TYPE::MEMORY_STATIC);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);




	return S_OK;
}

CTransportShip_HpBar* CTransportShip_HpBar::Create()
{
	CREATE_PIPELINE(CTransportShip_HpBar);
}

CGameObject* CTransportShip_HpBar::Clone(void* pArg)
{
	CLONE_PIPELINE(CTransportShip_HpBar);
}

void CTransportShip_HpBar::Free()
{
	__super::Free();

	delete this;
}