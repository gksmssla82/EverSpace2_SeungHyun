#include "stdafx.h"
#include "Song_Ship_Body.h"
#include "GameInstance.h"
#include "Player_RightBody.h"
#include <tchar.h>
#include "Normal_Turret.h"
#include "Rocket_Turret.h"
#include "Cam_Free.h"
#include "Cam_TPS.h"
#include "Cam_FPS.h"
#include "Cam_Shoulder.h"
#include "Normal_Bullet.h"
#include "Math_Utillity.h"
#include "HpBar.h"
#include "Lazer_Turret.h"
#include <Fire_PSystem.h>
#include "Booster_PSystem.h"
#include "Smoke_PSystem.h"
#include <Move_PSystem.h>
#include "Teleport_Effect.h"
#include "Enemy_StagBeetle.h"
#include <Trajectory.h>



CSong_Ship_Body::CSong_Ship_Body()
{

}

CSong_Ship_Body::CSong_Ship_Body(const CSong_Ship_Body & Prototype)
{
	*this = Prototype;

}

HRESULT CSong_Ship_Body::Initialize_Prototype()
{
	m_AnchorPosition = _float3(1.4f, 1.f, -0.5f);
	return S_OK;
}

HRESULT CSong_Ship_Body::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	

	m_pTrajectorys.push_back(static_cast<CTrajectory*>(GAMEINSTANCE->Add_GameObject<CTrajectory>(LEVEL_STATIC, TEXT("Trajectory")))); 
	m_pTrajectorys.back()->Make_TrajectoryNode(200, m_pTransformCom, _float3(15.f, 2.f, -15.f));
	WEAK_PTR(m_pTrajectorys.back());

	m_pTrajectorys.push_back(static_cast<CTrajectory*>(GAMEINSTANCE->Add_GameObject<CTrajectory>(LEVEL_STATIC, TEXT("Trajectory"))));
	m_pTrajectorys.back()->Make_TrajectoryNode(200, m_pTransformCom, _float3(-15.f, 2.f, -15.f));
	WEAK_PTR(m_pTrajectorys.back());

	m_pTrajectorys.push_back(static_cast<CTrajectory*>(GAMEINSTANCE->Add_GameObject<CTrajectory>(LEVEL_STATIC, TEXT("Trajectory"))));
	m_pTrajectorys.back()->Make_TrajectoryNode(200, m_pTransformCom, _float3(25.f, 0.5f, -28.f));
	WEAK_PTR(m_pTrajectorys.back());

	m_pTrajectorys.push_back(static_cast<CTrajectory*>(GAMEINSTANCE->Add_GameObject<CTrajectory>(LEVEL_STATIC, TEXT("Trajectory"))));
	m_pTrajectorys.back()->Make_TrajectoryNode(200, m_pTransformCom, _float3(-25.f, 0.5f, -28.f));
	WEAK_PTR(m_pTrajectorys.back());

	//->Get_Component<CTransform>()->Add_Position(_float3(0.f, 0.f, -7.5f))
	//GAMEINSTANCE->Set_Current_Camera(TEXT("TPS"));

	return S_OK;
}

void CSong_Ship_Body::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	if (KEY_INPUT(KEY::Z, KEY_STATE::TAP))
	{
		m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -1.f);
	}

	if (KEY_INPUT((KEY::Q), KEY_STATE::TAP))
	{
		GAMEINSTANCE->Add_GameObject<CEnemy_StagBeetle>(LEVEL_SELECTPLANET, TEXT("Enemy_StagBeetle"), nullptr, nullptr, true);
	}

	/*if (Get_Controller() == CONTROLLER::PLAYER)
	{
		if (KEY_INPUT(KEY::LBUTTON, KEY_STATE::HOLD))
		{
			for (auto& elem : m_pMyPosinList)
			{
				elem->Command_Fire();
			}
		}
	}*/

}

void CSong_Ship_Body::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CSong_Ship_Body::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(0.01f, 0.01f, 0.01f), true);
	
	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");
	D3DXHANDLE DiffuseHandle = (*Shader)->GetParameterByName(0, "Diffuse");
	D3DXHANDLE SpecularHandle = (*Shader)->GetParameterByName(0, "Specular");
	D3DXHANDLE ShininessHandle = (*Shader)->GetParameterByName(0, "shininess");

	float floatArray[3];
	floatArray[0] = 0.5f;
	floatArray[1] = 0.5f;
	floatArray[2] = 0.5f;


	float Specular = 1.f;
	float Diffuse = 0.6f;
	float Shininess = 1.f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);
	(*Shader)->SetFloat(DiffuseHandle, Diffuse);
	(*Shader)->SetFloat(SpecularHandle, Specular);
	(*Shader)->SetFloat(ShininessHandle, Shininess);

	

	return S_OK;
}

HRESULT CSong_Ship_Body::Render()
{
	
	__super::Render();


	
	m_pMeshCom->Render_Mesh();

	

	return S_OK;
}



void CSong_Ship_Body::On_Change_Controller(const CONTROLLER& _IsAI)
{
	__super::On_Change_Controller(_IsAI);
}

void CSong_Ship_Body::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CSong_Ship_Body::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Stay(_Other_Collider);
}

void CSong_Ship_Body::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

void CSong_Ship_Body::SetUp_Components_For_Child()
{
#pragma region Collider Setting
	m_pColliderCom->Set_Collider_Size(_float3(3.f, 3.f, 3.f));

#pragma endregion Collider Setting


#pragma region Status Setting

	CStatus::STATUS		Status;
	Status.fMaxHp = 30.f;
	Status.fHp = Status.fMaxHp;
	Status.fAttack = 7.f;
	Status.fMaxArmor = 5.f;
	Status.fArmor = Status.fMaxArmor;
	Status.fMaxBooster = 22.f;
	Status.fBooster = Status.fMaxBooster;

	

	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);


#pragma endregion Status Setting

#pragma region Mesh Setting

	m_pMeshCom = Add_Component<CMesh_Ship5>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);

#pragma endregion Mesh Setting

#pragma region Rigid_Body Setting
	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	/*RigidBodyDesc.m_fOwnerSpeed = 30.f;
	RigidBodyDesc.m_fOwnerAccel = 1.f;*/
	RigidBodyDesc.m_fOwnerSpeed = 30.f;
	RigidBodyDesc.m_fOwnerAccel = 1.f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);
	RigidBodyDesc.m_fOwnerRadAccel = 0.3f;
	RigidBodyDesc.m_fOwnerJump = 5.f;
	RigidBodyDesc.m_fOwnerJumpScale = 1.f;

	RigidBodyDesc.m_fFrictional = 0.05f;
	RigidBodyDesc.m_fRadFrictional = 0.02f;
	RigidBodyDesc.m_fRadZ = 0.01f;

	RigidBodyDesc.m_fOwnerLiftSpeed = 100.f;
	RigidBodyDesc.m_fOwnerLiftAccel = 10.f;
	RigidBodyDesc.m_fRadDrag = 1.f;
	RigidBodyDesc.m_fDirDrag = 0.05f;
	RigidBodyDesc.m_fBoosterSpeed = 100.f;
	RigidBodyDesc.m_fBoosterAccel = 1.f;

	m_pRigid_BodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigid_BodyCom->Set_WeakPtr(&m_pRigid_BodyCom);
	m_pRigid_BodyCom->Link_TransformCom(m_pTransformCom);

#pragma endregion Rigid_Body Setting

#pragma region Posin Setting

	GAMEINSTANCE->Add_GameObject<CNormal_Turret>(LEVEL_STATIC, TEXT("Normal_Turret"), m_pTransformCom);
	GAMEINSTANCE->Add_GameObject<CNormal_Turret>(LEVEL_STATIC, TEXT("Normal_Turret"), m_pTransformCom);
	//GAMEINSTANCE->Add_GameObject<CRocket_Turret>(LEVEL_STATIC, TEXT("Rocket_Turret"), m_pTransformCom);
	//GAMEINSTANCE->Add_GameObject<CRocket_Turret>(LEVEL_STATIC, TEXT("Rocket_Turret"), m_pTransformCom);


	//CLazer_Turret* LazerPosin = static_cast<CLazer_Turret*>(GAMEINSTANCE->Add_GameObject<CLazer_Turret>(LEVEL_STATIC, TEXT("Lazer_Turret"), m_pTransformCom));


#pragma endregion Posin Setting

#pragma region Controller Setting

	m_pAI_ControllerCom->Link_Object(this);
	m_pAI_ControllerCom->Set_Enable(false);

	m_pPlayer_ControllerCom->Link_Object(this);
	m_pPlayer_ControllerCom->Set_Enable(false);

#pragma endregion Controller Setting

#pragma region State Setting

	m_pStateCom->Link_RigidBody(m_pRigid_BodyCom);
	m_pStateCom->Link_AI_Transform(m_pTransformCom);

#pragma endregion State Setting

	//Set_Controller(CONTROLLER::PLAYER);
}


CSong_Ship_Body * CSong_Ship_Body::Create()
{
	CREATE_PIPELINE(CSong_Ship_Body);
}

CGameObject * CSong_Ship_Body::Clone(void* pArg)
{
	CLONE_PIPELINE(CSong_Ship_Body);
}

void CSong_Ship_Body::Free()
{
	__super::Free();

	for (auto& elem : m_pTrajectorys)
	{
		elem->Set_Dead_AllTrajectory();
		RETURN_WEAKPTR(elem);
	}
	
	delete this;
}
