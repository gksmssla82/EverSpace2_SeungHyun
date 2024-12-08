#pragma once

#include "Client_Defines.h"
#include "Bullet.h"

BEGIN(Engine)
class CMesh_Cube;
class CSpotLight;
class CPointLight;
END

BEGIN(Client)

class CNormal_Bullet final : public CBullet
{
private:
    explicit CNormal_Bullet();
    explicit CNormal_Bullet(const CNormal_Bullet& Prototype);
    virtual ~CNormal_Bullet() = default;

public:
    // CGameObject��(��) ���� ��ӵ�
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
    virtual HRESULT Render() override;

    virtual void Init_BulletPosition(_float4x4* _pWorldMat) override;

private:
    CMesh_Cube* m_pMeshCom = nullptr;
    CPointLight* m_pLight = nullptr;
    CCollider_Sphere* m_pColliderCom = nullptr;

private:
    _bool       m_bFirst = true;

public:
    //void Link_PosinTransform(CTransform* _pTransform);

public: /* For Event Function */
    virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
    virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
    virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

public:
    //��ü�� ���°� Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnEnable(void* _Arg = nullptr) override;

    //��ü�� ���°� ��Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnDisable() override;

protected:
    // CBullet��(��) ���� ��ӵ�
    virtual HRESULT SetUp_Components_For_Child(COLLISION_TYPE _eCollisionType) override;

public:
    static CNormal_Bullet* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

    
};

END
