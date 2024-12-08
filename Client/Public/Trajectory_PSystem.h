#pragma once
#include "Client_Defines.h"
#include "ParticleSystem.h"

BEGIN(Engine)
class CTransform;

END


BEGIN(Client)

class CTrajectory_PSystem final :
    public CParticleSystem
{
private:
    CTrajectory_PSystem() = default;
    CTrajectory_PSystem(const CTrajectory_PSystem& Prototype);
    virtual ~CTrajectory_PSystem() = default;

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
    

    virtual void ResetParticle(ParticleDesc* attribute) override;

private:
    list<CTransform*> m_pTargetTransforms;

public:

    // CParticleSystem��(��) ���� ��ӵ�
    static CTrajectory_PSystem* Create();
    virtual CGameObject* Clone(void* pArg) override;

public:
    //��ü�� ���°� Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnEnable(void* _Arg = nullptr) override;

    //��ü�� ���°� ��Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnDisable() override;
    
};

END