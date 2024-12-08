#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END


BEGIN(Client)

class CSpeed_UI final : public CGameObject
{
public:
	CSpeed_UI() = default;
	CSpeed_UI(const CSpeed_UI& Prototype);
	virtual ~CSpeed_UI() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CVIBuffer_Rect* m_pVIBufferCom = nullptr;

private:
	_float					m_fX, m_fY, m_fSizeX, m_fSizeY;
	_point					m_ptMouse;
	_float4x4				m_ProjMatrix;
	RECT					m_rcRect;
	_bool                   m_bSwitchTaget = false;

private:
	HRESULT SetUp_Components();

public:
	static CSpeed_UI* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END