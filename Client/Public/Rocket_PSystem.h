#pragma once
#include "Client_Defines.h"
#include "ParticleSystem.h"
BEGIN(Engine)

END

BEGIN(Client)

class CRocket_PSystem final : public CParticleSystem
{

private:
    CRocket_PSystem() = default;
    CRocket_PSystem(const CRocket_PSystem& Prototype);
    virtual ~CRocket_PSystem() = default;

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
    _float3     m_BeginColor;
    _float3     m_EndColor;

public:

    // CParticleSystem��(��) ���� ��ӵ�
    static CRocket_PSystem* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

public:
    //��ü�� ���°� Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnEnable(void* _Arg = nullptr) override;

    //��ü�� ���°� ��Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnDisable() override;
};

END