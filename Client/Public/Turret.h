#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTransform;
class CRenderer;
class CMesh_Cube;
class CMesh_Test;
class CCollider_Sphere;
class CSpotLight;
END

BEGIN(Client)
class CTurret : public CGameObject
{
protected:
	CTurret();
	virtual ~CTurret() = default;

protected:
	virtual HRESULT Initialize_Prototype() final;
	virtual HRESULT Initialize(void* pArg) PURE;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) final;
    virtual HRESULT Render();

protected:
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CMesh_Cube* m_pMeshCom = nullptr;
    CTransform* m_pPlayerTransformCom = nullptr;
    CMesh_Test* m_pMeshTestCom = nullptr;
    CCollider_Sphere* m_pColliderCom = nullptr;
    CSpotLight* m_pLightCom = nullptr;

private:
    CGameObject* m_pBoxObject = nullptr;
protected:
    CGameObject* m_pTarget = nullptr;//Rocket bullet�� ���� �� �Ѱ��ֱ�
    _tchar* m_pEventMessage;

protected:
    _float	 m_fCurTime = 0.f;
    _float	 m_fMaxTime;
    _float3  m_vScale;
    _float   floatArray[3];
protected:
    HRESULT SetUp_Components();
    virtual void SetUp_Components_For_Child() PURE;
    void SetUp_Variables_For_Child(_float _fMaxTime, _float3  _vScale, _float   _floatArray[3]);


protected: /* For Event Function */
    virtual void On_Change_Controller(const CONTROLLER& _eController) override;
    virtual void On_EventMessage(void* _Arg) override;
    virtual void Command_Fire() PURE;

    virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
    virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
    virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

    //��ü�� ���°� Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnEnable(void* _Arg = nullptr) override;

    //��ü�� ���°� ��Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnDisable() override;

private:
    _bool       LookAt_Targeting();
    void        LookAt_Aim();

public:
    void        Set_Player_Target(CGameObject* _Target);
    void        Set_AI_Target(CGameObject* _Target);
    
private:
    _float      m_fLifeTime = 30.f;
    _float      m_fMagnetic = 3.f;

public:
    virtual void Free() override;
};
END