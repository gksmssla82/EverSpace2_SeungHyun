#include "stdafx.h"
#include "Player.h"
#include "GameInstance.h"
#include "Normal_Turret.h"
#include <Booster_PSystem.h>
#include <Move_PSystem.h>
#include <Bomb_Effect.h>
#include "Enemy_StagBeetle.h"
#include "Trajectory.h"
#include <Bullet.h>
#include <Rocket_Turret.h>
#include <Lazer_Turret.h>

CPlayer::CPlayer()
{
}

HRESULT CPlayer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlayer::Initialize(void* pArg)
{
	return S_OK;
}

void CPlayer::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	if (m_pRigid_BodyCom->Get_Booster())
	{
		//GAMEINSTANCE->Get_ParticleSystem<CBooster_PSystem>(CURRENT_LEVEL, TEXT("Particle_Booster"));
		((CBooster_PSystem*)GAMEINSTANCE->Get_ParticleSystem<CBooster_PSystem>(CURRENT_LEVEL, TEXT("Particle_Booster"), nullptr, nullptr))->AddParticle(900 * fTimeDelta, m_pTransformCom);

		for (auto& elem : m_pTrajectorys)
		{
			elem->Set_Draw(true);
			elem->Set_Alpha(0.8f);
		}

	}
	else if (m_pRigid_BodyCom->Get_Booster() == false)
	{
		_float3 Speed = m_pRigid_BodyCom->Get_Vector(RIGID_BODY::SPEED);
		
		_float vNow = fabs(D3DXVec3Length(&Speed)) / 30.f;
		if (vNow > 0.9f)
		{
			for (auto& elem : m_pTrajectorys)
			{
				elem->Set_Alpha(vNow / 5.f);
			}

			
			D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 0, 0);
			//((CMove_PSystem*)GAMEINSTANCE->Get_ParticleSystem<CMove_PSystem>(CURRENT_LEVEL, TEXT("Particle_Smoke")))->AddParticle(500 * fTimeDelta, m_pTransformCom, color);
		}

		else
		{
			for (auto& elem : m_pTrajectorys)
			{
				elem->Set_Draw(false);
				
			}
		}

		
	}

	Update_TurretList();
	


	list<CGameObject*>* pAiObect = GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player"));
	_uint i = 0;

	if (!pAiObect)
		return;

	//�� ���� �ֳ�>??
	/*if (Get_Controller() != CONTROLLER::PLAYER)
		return;*/

	for (auto& elem : *pAiObect)
	{
		if (KEY_INPUT((KEY)((_uint)KEY::NUM1 + i), KEY_STATE::TAP))
		{
			if (CONTROLLER::PLAYER != elem->Get_Controller() )
			{
				//CCamera* pCurCamera = GAMEINSTANCE->Get_Camera();
				//CTransform* pCurCameraTransform = nullptr;//�̰Ը³�
				//if (pCurCamera)
				//	pCurCameraTransform = pCurCamera->Get_Transform();

				//if (pCurCameraTransform)
				//{
				//	GAMEINSTANCE->Switch_Player(pCurCameraTransform, elem->Get_Component<CTransform>(), TEXT("TPS"), 1.f);
				//}

				if (elem->Get_Enable())
				{
					elem->Set_Controller(CONTROLLER::PLAYER);
					elem->Get_Component<CRigid_Body>()->Reset_Force();
				}
			} 
		}
		++i;
	}

	if (Get_Controller() == CONTROLLER::AI)
		return;

	if (KEY_INPUT(KEY::NUM7, KEY_STATE::TAP))
	{

		CGameObject* Turret = nullptr;
		Turret = GAMEINSTANCE->Add_GameObject<CNormal_Turret>(LEVEL_STATIC, TEXT("Normal_Turret"), nullptr, nullptr, true);
		GAMEINSTANCE->PlaySoundW(TEXT("Drop_Turret.wav"), 0.3f);
		Turret->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION, true));

	}

	if (KEY_INPUT(KEY::NUM8, KEY_STATE::TAP))
	{

		CGameObject* Turret = nullptr;
		Turret = GAMEINSTANCE->Add_GameObject<CRocket_Turret>(LEVEL_STATIC, TEXT("Normal_Turret"), nullptr, nullptr, true);
		GAMEINSTANCE->PlaySoundW(TEXT("Drop_Turret.wav"), 0.3f);
		Turret->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION, true));

	}

	if (KEY_INPUT(KEY::NUM9, KEY_STATE::TAP))
	{

		CGameObject* Turret = nullptr;
		Turret = GAMEINSTANCE->Add_GameObject<CLazer_Turret>(LEVEL_STATIC, TEXT("Normal_Turret"), nullptr, nullptr, true);
		GAMEINSTANCE->PlaySoundW(TEXT("Drop_Turret.wav"), 0.3f);
		Turret->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION, true));

	}


}

void CPlayer::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	ISVALID(m_pRendererCom, );

	m_fTime -= fTimeDelta;
	if (m_fTime < 0.f)
	{
		if (Get_Controller() == CONTROLLER::PLAYER)
		{
			Update_PosinTarget(m_pTargetingCom->Get_TargetMode());
		}
		else
		{
			m_pTargetingCom->Set_TargetMode(TARGETMODE::TARGET_MULTIRAY);
			m_pTargetingCom->Make_TargetList_Distance(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Monster")), m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), 10000.f);
			//m_pTargetingCom->Make_TargetList_Distance(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Monster")), m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), 10000.f);
			Update_PosinTarget(m_pTargetingCom->Get_TargetMode());
		}
		m_fTime = 0.16f;
	}
	m_pRigid_BodyCom->Update_Transform(fTimeDelta);

	_float3 vPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);

	if (GAMEINSTANCE->IsIn(&vPos))
		m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);
}

HRESULT CPlayer::Render_Begin(ID3DXEffect** Shader)
{
	return S_OK;
}

HRESULT CPlayer::Render()
{
	__super::Render();
	m_pColliderCom->Debug_Render();

	return S_OK;
}

void CPlayer::On_Change_Controller(const CONTROLLER& _IsAI)
{

	if (_IsAI == CONTROLLER::PLAYER)
	{
		
		m_pAI_ControllerCom->Set_Enable(false);
		m_pPlayer_ControllerCom->Set_Enable(true);
		m_pLock_ControllerCom->Set_Enable(false);

		m_pRigid_BodyCom->Set_Mouse(true);

		
		GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("FPS"));
		GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("Shoulder"));
		GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("TPS"));
		GAMEINSTANCE->Set_Current_Camera(TEXT("TPS"));

		list<CGameObject*>* pAiObect = GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player"));

		m_pTargetingCom->Set_TargetMode(TARGETMODE::TARGET_SINGLE);

		if (pAiObect == nullptr)
			return;

		for (auto& elem : *pAiObect)
		{
			if (elem == this)
			{
				continue;
			}

			if(elem->Get_Enable())
				elem->Set_Controller(CONTROLLER::AI);
		}

		
	}
	else if (_IsAI == CONTROLLER::AI)
	{
		m_pAI_ControllerCom->Set_Enable(true);
		m_pPlayer_ControllerCom->Set_Enable(false);
		m_pRigid_BodyCom->Set_Mouse(false);	
	}

	else if (_IsAI == CONTROLLER::LOCK)
	{
		m_pAI_ControllerCom->Set_Enable(false);
		m_pPlayer_ControllerCom->Set_Enable(false);
		m_pLock_ControllerCom->Set_Enable(true);
		m_pRigid_BodyCom->Reset_Force();
		m_pRigid_BodyCom->Set_Mouse(false);
	}

}

void CPlayer::On_Collision_Enter(CCollider* _Other_Collider)
{
	if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::MONSTER_ATTACK && Get_Controller() == CONTROLLER::PLAYER)
	{
		GAMEINSTANCE->Add_Shaking(0.3f, 0.1f);
		
		GAMEINSTANCE->PlaySoundW(TEXT("Player_Hit.wav"), 1.f);


		_float fDamage = static_cast<CBullet*>(_Other_Collider->Get_Owner())->Get_Damage();

		m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -fDamage);

		if (m_pStatusCom->Get_Status().fHp <= DBL_EPSILON)
		{
			//Set_Dead();

			//m_pPlayer_ControllerCom->Set_Lock(true);
			m_pStatusCom->Set_FULL_HP();
			_float3 MyPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);
			((CBomb_Effect*)GAMEINSTANCE->Add_GameObject<CBomb_Effect>(CURRENT_LEVEL, TEXT("Bomb"), nullptr, nullptr, false))->Set_Pos(MyPos);

			////Change_NearstPlayer();

			if (!m_pMyTurretList.empty())
			{
				GAMEINSTANCE->Add_TimerEvent(1, this, 1.f, false, false);
				GAMEINSTANCE->Set_TimeScale(0.1f);
				GAMEINSTANCE->Add_Shaking(3.1f, 0.01f);
				m_pMyTurretList.back()->Set_Dead();
			}
				
			else
			{
				Change_NearstPlayer();
				Set_Dead();
				//m_pRendererCom->Set_Enable(false);
				
			}

			////Set_Controller(CONTROLLER::LOCK);
			
			

			
			//_float3 MyPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);
			//((CBomb_Effect*)GAMEINSTANCE->Add_GameObject<CBomb_Effect>(CURRENT_LEVEL, TEXT("Explosion"), nullptr, nullptr, false))->Set_Pos(MyPos);

			

		}
	}

	else if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::MONSTER_ATTACK)
	{
		_float fDamage = static_cast<CBullet*>(_Other_Collider->Get_Owner())->Get_Damage();

		m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -fDamage);

		if (m_pStatusCom->Get_Status().fHp <= DBL_EPSILON)
		{
			m_pStatusCom->Set_FULL_HP();
			_float3 MyPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);
			((CBomb_Effect*)GAMEINSTANCE->Add_GameObject<CBomb_Effect>(CURRENT_LEVEL, TEXT("Bomb"), nullptr, nullptr, false))->Set_Pos(MyPos);

			//m_pStatusCom->Set_FULL_HP();

			if (!m_pMyTurretList.empty())
				m_pMyTurretList.back()->Set_Dead();
			else
			{
				Set_Dead();
			}

		}
	}

	else if (COLLISION_TYPE::MONSTER == _Other_Collider->Get_Collision_Type())
	{
		m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -1.f);
		GAMEINSTANCE->Add_Shaking(0.05f, 0.01f);
		_float3 vSpeed = m_pRigid_BodyCom->Get_Vector(RIGID_BODY::SPEED);
		_float3 vDirection = m_pTransformCom->Get_State(CTransform::STATE_POSITION) - _Other_Collider->Get_Collider_Position();
		D3DXVec3Normalize(&vDirection, &vDirection);
		vDirection *= D3DXVec3Length(&vSpeed);

		m_pRigid_BodyCom->Add_Force(vDirection * 1.5f);

		if (m_pStatusCom->Get_Status().fHp <= DBL_EPSILON)
		{
			m_pStatusCom->Set_FULL_HP();
			_float3 MyPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);
			((CBomb_Effect*)GAMEINSTANCE->Add_GameObject<CBomb_Effect>(CURRENT_LEVEL, TEXT("Bomb"), nullptr, nullptr, false))->Set_Pos(MyPos);

			m_pStatusCom->Set_FULL_HP();

			if (!m_pMyTurretList.empty())
				m_pMyTurretList.back()->Set_Dead();
			else
			{
				Set_Dead();
			}

		}
	}
	
	else if (COLLISION_TYPE::OBJECT  == _Other_Collider->Get_Collision_Type())
	{
		m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -1.f);
		GAMEINSTANCE->Add_Shaking(0.05f, 0.01f);
		_float3 vSpeed = m_pRigid_BodyCom->Get_Vector(RIGID_BODY::SPEED);
		_float3 vDirection = m_pTransformCom->Get_State(CTransform::STATE_POSITION) -_Other_Collider->Get_Collider_Position();
		D3DXVec3Normalize(&vDirection, &vDirection);
		vDirection *= D3DXVec3Length(&vSpeed);
		
		m_pRigid_BodyCom->Add_Force(vDirection * 1.5f);

		if (m_pStatusCom->Get_Status().fHp <= DBL_EPSILON)
		{
			m_pStatusCom->Set_FULL_HP();
			_float3 MyPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);
			((CBomb_Effect*)GAMEINSTANCE->Add_GameObject<CBomb_Effect>(CURRENT_LEVEL, TEXT("Bomb"), nullptr, nullptr, false))->Set_Pos(MyPos);

			m_pStatusCom->Set_FULL_HP();

			if (!m_pMyTurretList.empty())
				m_pMyTurretList.back()->Set_Dead();
			else
			{
				Set_Dead();
			}

		}
	}
	else if (COLLISION_TYPE::PLAYER == _Other_Collider->Get_Collision_Type())
	{
		_float3 vSpeed = m_pRigid_BodyCom->Get_Vector(RIGID_BODY::SPEED);
		_float3 vDirection = m_pTransformCom->Get_State(CTransform::STATE_POSITION) - _Other_Collider->Get_Collider_Position();
		D3DXVec3Normalize(&vDirection, &vDirection);
		vDirection *= D3DXVec3Length(&vSpeed);

		m_pRigid_BodyCom->Add_Force(vDirection*0.5f);
	}

}

void CPlayer::On_Collision_Stay(CCollider* _Other_Collider)
{
	if (COLLISION_TYPE::MONSTER == _Other_Collider->Get_Collision_Type())
	{
		//_float3 vSpeed = m_pRigid_BodyCom->Get_Vector(RIGID_BODY::SPEED);
		_float3 vDirection = m_pTransformCom->Get_State(CTransform::STATE_POSITION) - _Other_Collider->Get_Collider_Position();
		D3DXVec3Normalize(&vDirection, &vDirection);
		//vDirection *= D3DXVec3Length(&vSpeed);

		m_pRigid_BodyCom->Add_Force(vDirection * 1.5f);
	}

}

void CPlayer::On_Collision_Exit(CCollider* _Other_Collider)
{
	int i = 0;
}

void CPlayer::OnTimerEvent(const _uint _iEventIndex)
{
	if (0 == _iEventIndex)
	{
		/*m_fTimeScale = min(1.f, CMath_Utillity::fLerp(m_fTimeScale, 1.f, GAMEINSTANCE->Get_UnScaledTimeDelta() * 10.f));

		GAMEINSTANCE->Set_TimeScale(m_fTimeScale);*/
		GAMEINSTANCE->Set_TimeScale(1.f);
	}

	if (1 == _iEventIndex)
	{
		//Set_Controller(CONTROLLER::PLAYER);
		m_pStatusCom->Set_FULL_HP();
		GAMEINSTANCE->Set_TimeScale(1.f);
		//Change_NearstPlayer();
		//Set_Dead();
	}

}

HRESULT CPlayer::SetUp_Components()
{
	m_pTransformCom = Add_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);

	m_pTargetingCom = Add_Component<CTargeting>();
	m_pTargetingCom->Set_WeakPtr(&m_pTargetingCom);
	m_pTargetingCom->Set_TargetMode(TARGETMODE::TARGET_SINGLE);

	COLLISION_TYPE eCollisionType = COLLISION_TYPE::PLAYER;
	m_pColliderCom = Add_Component<CCollider_Sphere>(&eCollisionType);
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);
	m_pColliderCom->Link_Transform(m_pTransformCom);

	m_pStateCom = Add_Component<CState_Move>();
	m_pStateCom->Set_WeakPtr(&m_pStateCom);

	m_pAI_ControllerCom = Add_Component<CAI_Controller>();
	m_pAI_ControllerCom->Set_WeakPtr(&m_pAI_ControllerCom);
	m_pAI_ControllerCom->Set_UsableStates(m_pAI_ControllerCom->Get_States_Preset_AI_Default());

	m_pPlayer_ControllerCom = Add_Component<CPlayer_Controller>();
	m_pPlayer_ControllerCom->Set_WeakPtr(&m_pPlayer_ControllerCom);

	m_pLock_ControllerCom = Add_Component<CLock_Controller>();
	WEAK_PTR(m_pLock_ControllerCom);

	SetUp_Components_For_Child();

	Set_Controller(CONTROLLER::LOCK);
	return S_OK;
}


void CPlayer::Update_PosinTarget(TARGETMODE _TargetMode)
{
	map<_float, CGameObject*>* TargetList = m_pTargetingCom->Get_Targetting();

	if (TargetList->empty())
	{
		for (auto iter = m_pMyTurretList.begin(); iter != m_pMyTurretList.end();)
		{
			if (!(*iter))
			{
				iter = m_pMyTurretList.erase(iter);
				continue;
			}

			(*iter)->Set_Player_Target(nullptr);
			iter++;
		}

		return;
	}

	vector<CGameObject*> TargetVec;

	for (auto& elem : *TargetList)
	{
		TargetVec.push_back(elem.second);
	}

	//��Ƽ Ÿ�� ���
	if (_TargetMode == TARGETMODE::TARGET_MULTIRAY)
	{
		_uint Index = 0;

		for (auto iter = m_pMyTurretList.begin(); iter != m_pMyTurretList.end();)
		{
			if (!(*iter))
			{
				iter = m_pMyTurretList.erase(iter);
				continue;
			}

			if (TargetVec[Index % TargetVec.size()])
			{
				(*iter)->Set_Player_Target(TargetVec[Index % TargetVec.size()]);
			}

			else
			{
				(*iter)->Set_Player_Target(nullptr);
			}
			

			(*iter)->Set_Player_Target(TargetVec[Index % TargetVec.size()]);
			Index++;
			iter++;
		}
	}

	//�̱� Ÿ�� ���
	if (_TargetMode == TARGETMODE::TARGET_SINGLE)
	{
		for (auto iter = m_pMyTurretList.begin(); iter != m_pMyTurretList.end();)
		{
			if (!(*iter))
			{
				iter = m_pMyTurretList.erase(iter);
				continue;
			}

			(*iter)->Set_Player_Target(TargetVec.front());

			iter++;
		}

	}

	if (_TargetMode == TARGETMODE::TARGET_MULTIWIDE)
	{
		// ��ü Ÿ���� �ڵ�
		_uint Index = 0;
		for (auto iter = m_pMyTurretList.begin(); iter != m_pMyTurretList.end();)
		{
			if (!(*iter))
			{
				iter = m_pMyTurretList.erase(iter);
				continue;
			}

			(*iter)->Set_Player_Target(TargetVec[Index % TargetVec.size()]);
			Index++;
			iter++;
		}

	}
}

_bool CPlayer::Change_NearstPlayer()
{
	map<_float, CGameObject*> NearPlayers =
		CTargeting::Get_Nearest_Target_Distance(
			GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player")),
			m_pTransformCom->Get_State(CTransform::STATE_POSITION, true),
			10000.f
			);

	//ã�� �÷��̾��� ������ �� ���� 1������ ������ �ƹ��͵� ���� ����.
	if (NearPlayers.size() <= 1)
		return false;

	//���� ������ �� �ڽ�, ���� �ǳ� ��
	auto Iter_NearPlayer = ++NearPlayers.begin();

	(*Iter_NearPlayer).second->Set_Controller(CONTROLLER::PLAYER);

	/*for (auto iter = NearPlayers.begin(); iter != NearPlayers.end();)
	{
		
		if ((*iter).second)
		{
			if ((*iter).second->Get_Enable())
			{
				(*iter).second->Set_Controller(CONTROLLER::PLAYER);
				return true;
			}
		}

		iter++;
	}*/

	//GAMEINSTANCE->Set_TimeScale(0.f);
	//GAMEINSTANCE->Add_TimerEvent(0, this, 4.f);

	//(*Iter_NearPlayer).second->Set_Controller(CONTROLLER::PLAYER);

	//CCamera* pCurCamera = GAMEINSTANCE->Get_Camera();
	//CTransform* pCurCameraTransform = nullptr;//�̰Ը³�
	//if (pCurCamera)
	//	pCurCameraTransform = pCurCamera->Get_Transform();

	//if (pCurCameraTransform)
	//{
	//	GAMEINSTANCE->Switch_Player(pCurCameraTransform, (*Iter_NearPlayer).second->Get_Component<CTransform>(), TEXT("TPS"), 1.f);
	//	//GAMEINSTANCE->Switch_Player(pCurCameraTransform, (*Iter_NearPlayer).second->Get_Component<CTransform>(), TEXT("TPS"), 1.f);
	//}

	return false;
}

void CPlayer::Update_TurretList()
{
	for (auto& elem : m_pMyTurretList)
	{
		RETURN_WEAKPTR(elem);
	}

	m_pMyTurretList.clear();

	list<CGameObject*> MyTurrets;

	function<void(const _tchar*)> InsertTurretList
		= [&](const _tchar* _Key) -> void
	{
		list<CGameObject*> TurretList = Get_Children_From_Key(_Key);

		MyTurrets.insert(MyTurrets.end(), TurretList.begin(), TurretList.end());

	};

	InsertTurretList(TEXT("Lazer_Turret"));
	InsertTurretList(TEXT("Rocket_Turret"));
	InsertTurretList(TEXT("Normal_Turret"));
	InsertTurretList(TEXT("Bayonet_Turret"));

	
	_int index = 2;

	for (auto& elem : MyTurrets)
	{
		CTurret* pTurret = static_cast<CTurret*>(elem);
		m_pMyTurretList.push_back(pTurret);
		WEAK_PTR(m_pMyTurretList.back());

		_float3 TurretPosition = m_AnchorPosition;
		_int iOffset = index / 2;

		if (index % 2 == 1)
			iOffset *= -1;


		TurretPosition.x = m_AnchorPosition.x * (_float)iOffset;

		//TurretPosition *= index / 2;

		m_pMyTurretList.back()->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, TurretPosition);

		index++;
	}

}

void CPlayer::Free()
{
	__super::Free();

	for (auto& elem : m_pMyTurretList)
	{
		RETURN_WEAKPTR(elem);
	}
}
