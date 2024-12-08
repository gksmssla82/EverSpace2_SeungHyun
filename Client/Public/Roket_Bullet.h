#pragma once

#include "Client_Defines.h"
#include "Bullet.h"

BEGIN(Engine)
class CMesh_Cube;
class CSpotLight;
class CMesh_Test;
class CTargeting;
END

BEGIN(Client)

class CRocket_Bullet final : public CBullet
{
private:
    explicit CRocket_Bullet();
    explicit CRocket_Bullet(const CRocket_Bullet& Prototype);
    virtual ~CRocket_Bullet() = default;

public:
    // CGameObject��(��) ���� ��ӵ�
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
    virtual HRESULT Render() override;

    virtual void Init_BulletPosition(_float4x4* _pWorldMat);

    void    Set_Target(CGameObject* _pTarget);


private:
    CSpotLight* m_pLight = nullptr;
    CMesh_Test* m_pMeshCom = nullptr;
    CTargeting* m_pTargetingCom = nullptr;
    CCollider_Sphere* m_pColliderCom = nullptr;

private:
    CGameObject* m_pTarget = nullptr;

public: /* For Event Function */
    virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
    virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
    virtual void On_Collision_Exit(CCollider* _Other_Collider) override;
    virtual void OnTimerEvent(const _uint _iEventIndex) override;


protected:
    // CBullet��(��) ���� ��ӵ�
    virtual HRESULT SetUp_Components_For_Child(COLLISION_TYPE _eCollisionType) override;
    virtual void OnEnable(void* _Arg = nullptr) override;

    virtual void OnDisable() override;


public:
    static CRocket_Bullet* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

    
};

END
