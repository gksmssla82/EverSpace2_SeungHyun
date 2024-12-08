#include "stdafx.h"
#include "EnemySpace_Body.h"
#include "GameInstance.h"
#include "Normal_Turret.h"
#include "State_Move.h"
#include "MovingCamera.h"
#include <TargetingBox.h>
#include "Math_Utillity.h"
#include "Mesh_EnemySpace.h"
#include <Fire_PSystem.h>
#include <Bomb_Effect.h>
#include <Smoke_PSystem.h>
#include "Move_PSystem.h"
#include <AI_HPBar.h>
#include <Lazer_Turret.h>

CEnemySpace_Body::CEnemySpace_Body(const CEnemySpace_Body& Prototype)
{
	*this = Prototype;
}

HRESULT CEnemySpace_Body::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CEnemySpace_Body::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

#pragma region �ʱ� ��ġ ����


	/*m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(rand() % 100, rand() % 20, 300.f + 20.f));
	m_pTransformCom->Update_WorldMatrix();*/

#pragma endregion �ʱ� ��ġ ����

	__super::Initialize(pArg);

	

	return S_OK;
}

void CEnemySpace_Body::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
 
}

void CEnemySpace_Body::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	m_fTime -= fTimeDelta;



	_float3 Speed = m_pRigidBodyCom->Get_Vector(RIGID_BODY::SPEED);
	
	/*if (fabs(D3DXVec3Length(&Speed)) > 5.f)
	{
		D3DCOLOR color = D3DCOLOR_ARGB(255, 0, 255, 0);
		((CMove_PSystem*)GAMEINSTANCE->Get_ParticleSystem<CMove_PSystem>(CURRENT_LEVEL, TEXT("Particle_Smoke")))->AddParticle(500 * fTimeDelta, m_pTransformCom, color);
	}*/


	m_pRigidBodyCom->Update_Transform(fTimeDelta);
	_float3 vPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);

	if(GAMEINSTANCE->IsIn(&vPos))
		m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);

}

HRESULT CEnemySpace_Body::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(0.15f, 0.15f, 0.15f), true);
	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");

	float floatArray[3];
	floatArray[0] = 0.3f;
	floatArray[1] = 0.3f;
	floatArray[2] = 0.3f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);


	return S_OK;
}

HRESULT CEnemySpace_Body::Render()
{

	__super::Render();

	m_pMeshCom->Render_Mesh();

	return S_OK;
}



void CEnemySpace_Body::SetUp_Components_For_Child()
{
	CStatus::STATUS Status;
	Status.fAttack = 1.f;
	Status.fArmor = 5.f;
	Status.fMaxHp = 20.f;
	Status.fHp = Status.fMaxHp;

	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);

	m_pMeshCom = Add_Component<CMesh_EnemySpace>();
	m_pMeshCom->Set_WeakPtr((void**)&m_pMeshCom);

	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 20.f;
	RigidBodyDesc.m_fOwnerAccel = 4.f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);
	RigidBodyDesc.m_fOwnerRadAccel = 0.1f;
	RigidBodyDesc.m_fOwnerJump = 5.f;
	RigidBodyDesc.m_fOwnerJumpScale = 1.f;

	RigidBodyDesc.m_fFrictional = 0.05f;
	RigidBodyDesc.m_fRadFrictional = 0.02f;
	RigidBodyDesc.m_fRadZ = 0.01f;

	RigidBodyDesc.m_fOwnerLiftSpeed = 20.f;
	RigidBodyDesc.m_fOwnerLiftAccel = 0.3f;
	RigidBodyDesc.m_fRadDrag = 1.f;
	RigidBodyDesc.m_fDirDrag = 0.05f;

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);


	
	m_pStateCom->Link_RigidBody(m_pRigidBodyCom);
	m_pStateCom->Link_AI_Transform(m_pTransformCom);


	COLLISION_TYPE eBulletCollisionType = COLLISION_TYPE::MONSTER_ATTACK;

	//CNormal_Turret* Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom, &eBulletCollisionType));
	//Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 1.5f, 0.f));
	//m_pPosinList.push_back(Posin);
	//Posin->Set_WeakPtr(&m_pPosinList.back());

	//Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom, &eBulletCollisionType));
	//Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.5f, 0.f));
	//m_pPosinList.push_back(Posin);
	//Posin->Set_WeakPtr(&m_pPosinList.back());

	CLazer_Turret* LazerPosin = static_cast<CLazer_Turret*>(GAMEINSTANCE->Add_GameObject<CLazer_Turret>(LEVEL_STATIC, TEXT("Lazer_Turret"), m_pTransformCom, &eBulletCollisionType));
	LazerPosin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 1.5f, 0.f));
	m_pPosinList.push_back(LazerPosin);
	LazerPosin->Set_WeakPtr(&m_pPosinList.back());

	LazerPosin = static_cast<CLazer_Turret*>(GAMEINSTANCE->Add_GameObject<CLazer_Turret>(LEVEL_STATIC, TEXT("Lazer_Turret"), m_pTransformCom, &eBulletCollisionType));
	LazerPosin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.5f, 0.f));
	m_pPosinList.push_back(LazerPosin);
	LazerPosin->Set_WeakPtr(&m_pPosinList.back());

	m_pAIControllerCom->Link_Object(this);
	m_pAIControllerCom->Set_Enable(false);
	m_pAIControllerCom->Set_UsableStates(m_pAIControllerCom->Get_States_Preset_AI_Default());



	COLLISION_TYPE eCollisionType = COLLISION_TYPE::MONSTER;
	m_pColliderCom = Add_Component<CCollider_Sphere>(&eCollisionType);
	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Set_Collider_Size(_float3(10.f, 10.f, 10.f));
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);

	Set_Controller(CONTROLLER::AI);
}



void CEnemySpace_Body::On_Change_Controller(const CONTROLLER& _IsAI)
{
	__super::On_Change_Controller(_IsAI);
}


CEnemySpace_Body* CEnemySpace_Body::Create()
{
	CREATE_PIPELINE(CEnemySpace_Body);
}

CGameObject* CEnemySpace_Body::Clone(void* pArg)
{
	CLONE_PIPELINE(CEnemySpace_Body);
}

void CEnemySpace_Body::Free()
{
	__super::Free();

	delete this;
}

void CEnemySpace_Body::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CEnemySpace_Body::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Stay(_Other_Collider);
}

void CEnemySpace_Body::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}
