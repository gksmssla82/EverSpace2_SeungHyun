#include "stdafx.h"
#include "Level_SunPlanet.h"
#include "GameInstance.h"
#include "VenusPlanet_SkyBox.h"
#include "Default_Aim.h"
#include "Light_Moon.h"
#include "StatusBar.h"
#include "HpBar.h"
#include "ShieldBar.h"
#include "BoosterBar.h"
#include "BulletCountUI.h"
#include "BulletUI.h"
#include <TextBox.h>
#include <Quest.h>
#include <Planet_Select.h>
#include "Level_Loading.h"
#include "MovingCamera.h"
#include <SunSpaceBoss_Body.h>
#include <Enemy_Roller.h>
#include <RollerSpawn_Effect.h>
#include "Boss_HpTable.h"
#include "Boss_HpBar.h"
#include "Boss_Name.h"



CLevel_SunPlanet::CLevel_SunPlanet()
{
}

HRESULT CLevel_SunPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CVenusPlanet_SkyBox>(LEVEL_SUNPLANET, TEXT("SkyBox")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_SUNPLANET, TEXT("Aim_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVEL_SUNPLANET, TEXT("Light_Moon")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVEL_SUNPLANET, TEXT("Status_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVEL_SUNPLANET, TEXT("HP_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVEL_SUNPLANET, TEXT("Booster_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVEL_SUNPLANET, TEXT("Shield_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVEL_SUNPLANET, TEXT("NormalBullet_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVEL_SUNPLANET, TEXT("BulletCount_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_SUNPLANET, TEXT("Aim")))
		return E_FAIL;


	m_pBoss_HP_Bar = GAMEINSTANCE->Add_GameObject<CBossHpBar>(LEVEL_SUNPLANET, TEXT("Boss_HP_Bar"));
	m_pBoss_HP_Bar->Set_Enable(true);

	m_pBoss_HP_Table = GAMEINSTANCE->Add_GameObject<CBossHpTable>(LEVEL_SUNPLANET, TEXT("CBossHpTable"));
	m_pBoss_HP_Table->Set_Enable(true);

	m_pBoss_Name_Table = GAMEINSTANCE->Add_GameObject<CBossName>(LEVEL_SUNPLANET, TEXT("Boss_Name"));
	m_pBoss_Name_Table->Set_Enable(true);


	m_pTextBoxObject = GAMEINSTANCE->Add_GameObject<CTextBox>(LEVEL_SUNPLANET, TEXT("TextBox_Yang"));
	m_pTextBoxObject->Set_Enable(false);

	m_pQuestBoxObject = GAMEINSTANCE->Add_GameObject<CQuest>(LEVEL_SUNPLANET, TEXT("Quest_UI"));
	m_pQuestBoxObject->Set_Enable(false);


	m_pPlanetObject = GAMEINSTANCE->Add_GameObject<CPlanet_Select>(LEVEL_SUNPLANET, TEXT("Earth"));
	m_pPlanetObject->Set_Enable(false);


	if (!GAMEINSTANCE->Add_GameObject<CSunSpaceBoss_Body>(LEVEL_SUNPLANET, TEXT("Enemy_Boss")))
		return E_FAIL;



	GAMEINSTANCE->PlayBGM(TEXT("SunPlanet.wav"), 0.1f);
	//GAMEINSTANCE->PlaySoundW(TEXT("SunPlanet.wav"), BGM, 1.f);

	GAMEINSTANCE->Add_TimerEvent(0, this, 0.f, false, false, false);
	GAMEINSTANCE->Add_TimerEvent(1, this, 5.f, true, false, false);

	return S_OK;
}

void CLevel_SunPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	if (m_bCinematic)
	{
		m_fTime -= fTimeDelta;
		if (0.f > m_fTime)
		{
			m_bCinematic = false;
		
			if (FAILED(GAMEINSTANCE->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create((LEVEL)m_iNextLevel))))
				return;

			list<CGameObject*>* pLayer = GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player"));

			for (auto& elem : *pLayer)
			{
				if (!elem)
					break;

				elem->Set_Controller(CONTROLLER::PLAYER);
			}
		}
	}
	else if (m_bFadeIn)
	{
		GAMEINSTANCE->Add_FadeOffSet();
	}



	SunPlanet_Event(fTimeDelta);
}

HRESULT CLevel_SunPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("Satrun Planet �����Դϴ�. "));

	return S_OK;
}

void CLevel_SunPlanet::Change_Level(void* pArg, _uint _iNextLevel)
{
	if (m_bCinematic)
		return;


	m_fTime = 5.f;
	m_bCinematic = true;
	m_iNextLevel = _iNextLevel;

	list<CGameObject*>* pLayer = GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player"));
	for (auto& iter = pLayer->begin(); iter != pLayer->end(); ++iter)
	{
		if (CONTROLLER::PLAYER == (*iter)->Get_Controller())
		{


			(*iter)->Set_Controller(CONTROLLER::AI);
			CComponent* Temp = (*iter)->Get_Component<CAI_Controller>();
			WEAK_PTR(Temp);
			Temp->Set_Enable(false);
			Temp = (*iter)->Get_Component<CRigid_Body>();
			static_cast<CRigid_Body*>(Temp)->Add_Dir(CRigid_Body::SPIN, 0.f);
			static_cast<CRigid_Body*>(Temp)->Add_Dir(CRigid_Body::DOWN, 0.f);
			if (pArg)
			{
				Temp = (*iter)->Get_Component<CTransform>();
				static_cast<CTransform*>(Temp)->LookAt((CTransform*)pArg, true);
			}
			RETURN_WEAKPTR(Temp);
		}
	}

	
}

void CLevel_SunPlanet::OnTimerEvent(const _uint _iEventIndex)
{
	if(0 == _iEventIndex)
	{
		
		GAMEINSTANCE->Update_MovingCam();
		CMovingCamera* pMovingCam = (CMovingCamera*)GAMEINSTANCE->Get_Camera()->Get_Owner();

		CGameObject* pEnemyBoss = GAMEINSTANCE->Find_Layer(LEVEL_SUNPLANET, TEXT("Enemy_Boss"))->front();

		pMovingCam->Boss_Cinematic(pEnemyBoss->Get_Component<CTransform>());

	}
	else if (1 == _iEventIndex)
	{
	
		m_bFadeIn = true;
	
	}

}

void CLevel_SunPlanet::SunPlanet_Event(_float fTimeDelta)
{
	m_fTextBoxTime -= fTimeDelta;


	if (m_fTextBoxTime <= 288.f && !m_bEventCheck[0])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT(" �� �տ� ������ ��ü�� �ֳ� ! \n � ������ �μ��� �� ������ ������ !! "), 0);
	}

	if (m_fTextBoxTime <= 287.7f && !m_bEventCheck[0])
	{
		GAMEINSTANCE->StopSound(10);
	}

	if (m_fTextBoxTime <= 283.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[0] = true;
	}


	list<CGameObject*>* EnemyBoss = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Enemy_Boss"));
	if (EnemyBoss)
	{
		for (auto& elem : *EnemyBoss)
		{
			if (elem->Get_Enable() == false)
			{
				m_pBoss_HP_Bar->Set_Enable(false);
				m_pBoss_HP_Table->Set_Enable(false);
				m_pBoss_Name_Table->Set_Enable(false);

				m_fTextCount -= fTimeDelta;

				// �߰����� Ŭ����
				if (m_iSpawnCount == 0)
				{
					((CEnemy_Roller*)GAMEINSTANCE->Add_GameObject<CEnemy_Roller>(CURRENT_LEVEL, TEXT("Enemy_Roller")))
						->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION,
							elem->Get_Component<CTransform>()->Get_State(CTransform::STATE_POSITION, true));
					((CRollerSpawn_Effect*)GAMEINSTANCE->Add_GameObject<CRollerSpawn_Effect>(CURRENT_LEVEL, TEXT("RollerSpawn")))
						->Set_Pos(elem->Get_Component<CTransform>()->Get_State(CTransform::STATE_POSITION, true));
					GAMEINSTANCE->Add_TimerEvent(1, this, 0.f, false, false, false);


					GAMEINSTANCE->PlaySoundW(TEXT("RollerSpawn.wav"), 1.f);
				}

				++m_iSpawnCount;
				if (!m_bEventCheck[1])
				{
					m_pTextBoxObject->Set_Enable(true);
					GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT(" ���Կ��� ������ ���Գ� ! \n ������ ���̸� ������ �����ɼ� !! "), 0);
		
				}
			}
			if (!m_bEventCheck[1] && m_fTextCount < 0.f)
			{
				// ����
				m_pTextBoxObject->Set_Enable(false);
				m_bEventCheck[1] = true;
			}
		}
	}


	EnemyBoss = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Enemy_Roller"));

	if (EnemyBoss && !m_bRollerDie)
	{
		for (auto& elem : *EnemyBoss)
		{
			if (elem->Get_Enable() == false)
			{
				
				// �������� Ŭ����
				if (!m_bEventCheck[2])
				{
					m_pTextBoxObject->Set_Enable(true);
					GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("�ڳ� ���� ���￡�� �¸��߳� ! \n���� ���ư��� ����� ���ð� !! "), 0);
					GAMEINSTANCE->PlaySoundW(TEXT("Boss_Die.wav"), 1.f);
					m_bRollerDie = true;
					bSunClear = true;
				}

			}
		}
	}
}

CLevel_SunPlanet* CLevel_SunPlanet::Create()
{
	CLevel_SunPlanet* pInstance = new CLevel_SunPlanet();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_SatrunPlanet");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_SunPlanet::Free()
{
	__super::Free();

	delete this;
}
