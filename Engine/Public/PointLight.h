#pragma once
#include "Light.h"

BEGIN(Engine)

class ENGINE_DLL CPointLight :
    public CLight
{
private:
    explicit CPointLight() = default;
    CPointLight(const CPointLight& Prototype);
    virtual ~CPointLight() = default;

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

    void Set_FixedLight(_bool _bFixed) { m_bFixed = _bFixed; }

public:
    // CLight��(��) ���� ��ӵ�
    static CPointLight* Create();
    virtual CComponent* Clone(void* pArg) override;
    virtual void Free() override;

private:
    ID3DXMesh*  m_pMesh = nullptr;
    _bool       m_bFixed = false;
};

END