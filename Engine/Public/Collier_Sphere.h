#pragma once
#include "Collider.h"

BEGIN(Engine)

class ENGINE_DLL CCollider_Sphere :
    public CCollider
{
protected:
    explicit CCollider_Sphere() = default;
    CCollider_Sphere(const CCollider_Sphere& Prototype);
    virtual ~CCollider_Sphere() = default;

public:
    virtual HRESULT Initialize_Prototype();
    virtual HRESULT Initialize(void* pArg);

    // CCollider을(를) 통해 상속됨
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    HRESULT Debug_Render();

public:
    virtual void Set_Collider_Size(const _float3& _Size) override;

    virtual _float3 Get_Collider_Size() override;

    virtual _float3 Get_Collider_Position() override;

private:
    _float m_fSize = 0.f;
    _float3 m_vColliderPosition;

private: /* For Debug Mesh */
    ID3DXMesh* m_pMesh = nullptr;
    _ulong			m_dwFVF;


public:
    static CCollider_Sphere* Create();
    virtual	CComponent* Clone(void* pArg) override;
    virtual void Free() override;



};

END
