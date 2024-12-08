#pragma once
#include "Client_Defines.h"
#include "ParticleSystem.h"
BEGIN(Engine)
class CTransform;
END

BEGIN(Client)

class CBooster_PSystem final : public CParticleSystem
{
private:
    CBooster_PSystem() = default;
    CBooster_PSystem(const CBooster_PSystem& Prototype);
    virtual ~CBooster_PSystem() = default;

public:
    // CGameObject��(��) ���� ��ӵ�
    virtual HRESULT Initialize_Prototype() override;

    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta);
    virtual void LateTick(_float fTimeDelta);
    //���� ���� �۾� ���� (������� ����)
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr);
    virtual HRESULT Render();

public:
    virtual void ResetParticle(ParticleDesc* Desc) override;

private:
    _float     m_fCurSpeed;
    _float     m_fMaxSpeed;
    _float3     m_BeginColor;
    _float3     m_EndColor;

    _uint m_iTextureCount = 0;

public:

    // CParticleSystem��(��) ���� ��ӵ�
    static CBooster_PSystem* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

public:
    //��ü�� ���°� Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnEnable(void* _Arg = nullptr) override;

    //��ü�� ���°� ��Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnDisable() override;

};

END