#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CLoading final : public CGameObject
{
private:
    explicit CLoading() = default;
    explicit CLoading(const CLoading& Prototype);
    virtual ~CLoading() = default;

public:
    // CGameObject��(��) ���� ��ӵ�
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render() override;

private:
    _float					m_fX, m_fY, m_fSizeX, m_fSizeY;
    _float4x4				m_ProjMatrix;

private:
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CVIBuffer_Rect* m_pVIBufferCom = nullptr;

private:
    HRESULT SetUp_Components();

public:
    static CLoading* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};


END

