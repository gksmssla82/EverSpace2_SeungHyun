#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CRigid_Body;
class CState_Move;
class CTargeting;
class CStatus;
class CTargeting;
class CAI_Controller;
class CCollider_Sphere;
class CNormal_Turret;

END

BEGIN(Client)
class CNormal_Turret;
class CBayonet_Turret;
class CTurret;
class CLazer_Turret;
class CEnemy_GPS;
class CMonster abstract : public CGameObject
{
protected:
    CMonster() = default;
    virtual ~CMonster() = default;

public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg)override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
    virtual HRESULT Render() override;

protected: /* For My Component*/
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CRigid_Body* m_pRigidBodyCom = nullptr;
    CState_Move* m_pStateCom = nullptr;
    CTargeting* m_pTargetingCom = nullptr;
    CStatus* m_pStatusCom = nullptr;
    CCollider_Sphere* m_pColliderCom = nullptr;
    CAI_Controller* m_pAIControllerCom = nullptr;

protected:
    list<CTurret*> m_pPosinList;
    list<CBayonet_Turret*> m_pBayonetList;
    list<CLazer_Turret*> m_pLazerList;
    _float m_fTime = 3.f;
    //CEnemy_GPS* m_pGPS = nullptr;

protected:
    CGameObject* m_pHPBar = nullptr;

public:
    virtual void On_Change_Controller(const CONTROLLER& _IsAI);

private:
    void Update_Target(CGameObject* _Target);

protected:
    void LookAt_Camera();
    HRESULT SetUp_Components();
    virtual void SetUp_Components_For_Child() PURE;
    virtual void Drop_Item();
   
protected: /* For Event Function */
    virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
    virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
    virtual void On_Collision_Exit(CCollider* _Other_Collider) override;
    virtual void OnTimerEvent(const _uint _iEventIndex) override;

public:
    //��ü�� ���°� Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnEnable(void* _Arg = nullptr) override;

    //��ü�� ���°� ��Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnDisable() override;



public:
    virtual void Free() override;

};

END