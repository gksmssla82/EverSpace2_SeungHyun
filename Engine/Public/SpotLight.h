#pragma once
#include "Light.h"

BEGIN(Engine)

class ENGINE_DLL CSpotLight :
    public CLight
{
private:
    explicit CSpotLight() = default;
    CSpotLight(const CSpotLight& Prototype);
    virtual ~CSpotLight() = default;

public:
    virtual HRESULT Initialize_Prototype();
    virtual HRESULT Initialize(void* pArg);

    // CCollider��(��) ���� ��ӵ�
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;

    // CLight��(��) ���� ��ӵ�
    virtual void DrawLight() override;
    // CLight��(��) ���� ��ӵ�
    virtual void Bind_ConstBuffer() override;

public:
    // CLight��(��) ���� ��ӵ�
    static CSpotLight* Create();
    virtual CComponent* Clone(void* pArg) override;
    virtual void Free() override;

private:
    ID3DXMesh* m_pMesh = nullptr;
};

END