#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
BEGIN(Engine)
class CRenderer;
class CTransform;
class CCollider_OBB;
class CRigid_Body;
class CTargeting;
class CStatus;
class CMesh_Cube;
class CCollider_Pre;
class CState_Move;
class CAI_Controller;
class CPlayer_Controller;
class CMesh_ShinShip;
class CCollider_Sphere;
class CMesh_Ship2;
class CCollider_Mesh;
END

BEGIN(Client)
class CNormal_Turret;

class CAI_TransportShip final : public CGameObject
{
private:
	CAI_TransportShip();
	CAI_TransportShip(const CAI_TransportShip& Prototype);
	virtual ~CAI_TransportShip() = default;


public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
	virtual HRESULT Render() override;



private:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CCollider_Sphere* m_pColliderCom = nullptr;
	CRigid_Body* m_pRigidBodyCom = nullptr;
	//CTargeting* m_pTargetingCom = nullptr;
	CStatus* m_pStatusCom = nullptr;
	//CMesh_Cube* m_pMeshCom = nullptr;
	CMesh_Ship2* m_pMeshCom = nullptr;
	CState_Move* m_pStateCom = nullptr;
	CAI_Controller* m_pAIControllerCom = nullptr;
	//CCollider_Mesh* m_pColliderMesh = nullptr;

private:
	CGameObject* m_pHpBar = nullptr;

private:
	list<CNormal_Turret*>	m_pMyPosinList;
	_bool					m_bTargetMode = false;
	_float					m_fSpawnTime = 3.f;
	_float                  m_fTransLevelTime = 3.f;

protected: /* For Event Function */
	virtual void On_Change_Controller(const CONTROLLER& _IsAI) override;

public: /* For Event Function */
	virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
	virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
	virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

private: /* ���� ��ü���� �ʿ��� ������Ʈ�� �����ؿ´�. */
	HRESULT SetUp_Components();
	void Spawn_SpaceShip();




public:
	static CAI_TransportShip* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END