#include "stdafx.h"
#include "Level_RedPlanet.h"
#include "GameInstance.h"
#include "LEvel_Loading.h"
#include "Song_Ship_Body.h"
#include "Monster.h"
#include "Terrain.h"
#include "Cam_Free.h"
#include "Cam_FPS.h"
#include "Cam_Shoulder.h"
#include "Cam_TPS.h"
#include <UITest.h>
#include <SkyBox.h>
#include "Default_Aim.h"
#include <TargetingBox.h>
#include <SkyBox.h>
#include "../Default/EnemySpace_Body.h"
#include "StatusBar.h"
#include "HpBar.h"
#include "BoosterBar.h"
#include "ShieldBar.h"
#include "BulletUI.h"
#include "BulletCountUI.h"
#include "AI_Friendly.h"
#include "Rock_1.h"
#include "MovingCamera.h"
#include "../Default/EnemySpace_Body.h"
#include "Kang_Ship_Body.h"
#include "Planet_Venus.h"
#include "Math_Utillity.h"
#include "Light_Moon.h"
#include "Quest.h"
#include "TextBox.h"
#include "Hong_Ship_Body.h"
#include "Shin_Ship_Body.h"
#include <SpaceDust_PSystem.h>
#include <SelectPlanet_SkyBox.h>
#include "AI_TransportShip.h"
#include "RedPlanet_SkyBox.h"
#include <Planet_Select.h>
#include "Enemy_Roller.h"
#include "Boss_HpTable.h"
#include "Boss_Name.h"
#include "TransportShip_HpBar.h"



CLevel_RedPlanet::CLevel_RedPlanet()
{

}


HRESULT CLevel_RedPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;



	//CGameObject* pPlayer = GAMEINSTANCE->Add_GameObject<CKang_Ship_Body>(LEVEL_STATIC, TEXT("Player"));
	//pPlayer->Set_Controller(CONTROLLER::AI);



	/*if (!GAMEINSTANCE->Add_GameObject<CHong_Ship_Body>(LEVEL_REDPLANET, TEXT("Player")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShin_Ship_Body>(LEVEL_REDPLANET, TEXT("Player")))
		return E_FAIL;*/

	for (int i = 0; i < 2; ++i)
	{
		CTransform* pEnemyTransform = GAMEINSTANCE->Add_GameObject<CEnemySpace_Body>(CURRENT_LEVEL, TEXT("EnemySpace_Body"))->Get_Component<CTransform>();

		_float3 SpawnPos{ 0, 0.f, 300.f };

		_float RotateX = (_float)(rand() % 361);
		_float RotateY = (_float)(rand() % 361);
		_float RotateZ = (_float)(rand() % 361);
		RotateX = D3DXToRadian(RotateX);
		RotateY = D3DXToRadian(RotateY);
		RotateZ = D3DXToRadian(RotateZ);


		SpawnPos = CMath_Utillity::Rotate_Vec3(_float3(RotateX, RotateY, RotateZ), SpawnPos);

		pEnemyTransform->Set_State(CTransform::STATE_POSITION, SpawnPos);

	}

	 if (!GAMEINSTANCE->Add_GameObject<CAI_TransportShip>(LEVEL_REDPLANET, TEXT("TransportShip")))
		return E_FAIL;

	/*for (int i = 0; i < 50; ++i)
	{
		if (!GAMEINSTANCE->Add_GameObject<CAI_Friendly>(LEVEL_REDPLANET, TEXT("AI_Friendly")))
			return E_FAIL;
	}*/


	/*for (int i = 0; i < 5; i++)
	{
		GAMEINSTANCE->Add_GameObject<CMonster>(LEVEL_GAMEPLAY, TEXT("Monster"))
			->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, _float3(i * 5.f, 0.f, 0.f));
	}*/

	if (!GAMEINSTANCE->Add_GameObject<CTerrain>(LEVEL_REDPLANET, TEXT("Terrain")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CRedPlanet_SkyBox>(LEVEL_REDPLANET, TEXT("SkyBox")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_REDPLANET, TEXT("Aim_UI")))
		return E_FAIL;

	for (int i = 0; i < 30; ++i)
	{
		if (!GAMEINSTANCE->Add_GameObject<CRock_1>(LEVEL_REDPLANET, TEXT("Rock_1")))
			return E_FAIL;
	}

	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVEL_REDPLANET, TEXT("Light_Moon")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVEL_REDPLANET, TEXT("Status_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVEL_REDPLANET, TEXT("HP_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVEL_REDPLANET, TEXT("Booster_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVEL_REDPLANET, TEXT("Shield_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVEL_REDPLANET, TEXT("NormalBullet_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVEL_REDPLANET, TEXT("BulletCount_UI")))
		return E_FAIL;

	//if (!GAMEINSTANCE->Add_GameObject<CEnemy_Roller>(LEVEL_REDPLANET, TEXT("Enemy_Roller")))
	//	return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBossHpTable>(LEVEL_REDPLANET, TEXT("Boss_HP_Table")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBossName>(LEVEL_REDPLANET, TEXT("Boss_Name")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CTransportShip_HpBar>(LEVEL_REDPLANET, TEXT("TransportShip_HpBar")))
		return E_FAIL;

	//((CSpaceDust_PSystem*)GAMEINSTANCE->Add_GameObject<CSpaceDust_PSystem>(LEVEL_REDPLANET, TEXT("Particle")))->AddParticle(500);

	m_pTextBoxObject = GAMEINSTANCE->Add_GameObject<CTextBox>(LEVEL_REDPLANET, TEXT("TextBox_Yang"));
	m_pTextBoxObject->Set_Enable(false);

	m_pQuestBoxObject = GAMEINSTANCE->Add_GameObject<CQuest>(LEVEL_REDPLANET, TEXT("Quest_UI"));
	m_pQuestBoxObject->Set_Enable(false);




	GAMEINSTANCE->PlayBGM(TEXT("RedPlanet.wav"), 0.1f);



	return S_OK;
}

void CLevel_RedPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


	
	m_fSpawnTime -= fTimeDelta;

	if (m_fSpawnTime < 0.f && m_bSpawnCheck)
	{
		
			CTransform* pEnemyTransform = GAMEINSTANCE->Add_GameObject<CEnemySpace_Body>(CURRENT_LEVEL, TEXT("EnemySpace_Body"), nullptr, nullptr, true)
											->Get_Component<CTransform>();
			_float3 SpawnPos{ 0, 0.f, 300.f };

			_float RotateX = (_float)(rand() % 361);
			_float RotateY = (_float)(rand() % 361);
			_float RotateZ = (_float)(rand() % 361);
			RotateX = D3DXToRadian(RotateX);
			RotateY = D3DXToRadian(RotateY);
			RotateZ = D3DXToRadian(RotateZ);

			SpawnPos = CMath_Utillity::Rotate_Vec3(_float3(RotateX, RotateY, RotateZ), SpawnPos);
			pEnemyTransform->Set_State(CTransform::STATE_POSITION, SpawnPos);


		

		     m_fSpawnTime = 3.f;


	}

	if (m_bCinematic)
	{
		m_fTime -= fTimeDelta;
		//Ÿ�� �̺�Ʈ ���ɾ�
		
		if (1.f > m_fTime)
			GAMEINSTANCE->Sub_FadeOffSet();


		if (0.f > m_fTime)
		{
			m_bCinematic = false;
	

			CSong_Ship_Body* pMainCharacter = nullptr;

			list<CGameObject*>* pAiObect = GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player"));

			if (!pAiObect)
				return;

			for (auto& elem : *pAiObect)
			{
				pMainCharacter = dynamic_cast<CSong_Ship_Body*>(elem);

				if (pMainCharacter)
				{
					pMainCharacter->Set_Controller(CONTROLLER::PLAYER);
					break;
				}
			}
			GAMEINSTANCE->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_SELECTPLANET));
		}
	}
	else
	{
		GAMEINSTANCE->Add_FadeOffSet();
	}

	

	if (KEY_INPUT(KEY::F1, KEY_STATE::TAP))
	{
		GAMEINSTANCE->Reset_BlurWidth();
		GAMEINSTANCE->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_SELECTPLANET));
	}


	RedPlanet_Event(fTimeDelta);



}

HRESULT CLevel_RedPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("Red Planet �����Դϴ�. "));

	return S_OK;
}

void CLevel_RedPlanet::Change_Level(void* pArg, _uint _iNextLevel)
{
	if (m_bCinematic)
		return;


	m_fTime = 3.f;
	m_bCinematic = true;
	m_iNextLevel = _iNextLevel;

	

	/*CGameObject* Camera_Origin = GAMEINSTANCE->Get_Camera()->Get_Owner();
	CTransform* pCameraTransform = Camera_Origin->Get_Component<CTransform>();
	GAMEINSTANCE->Update_MovingCam();
	CGameObject* Camera_Moving = GAMEINSTANCE->Get_Camera()->Get_Owner();
	CTransform* pCameraMovingTransform = Camera_Moving->Get_Component<CTransform>();

	_float3	vUp, vLook, vRight, vSpeed;

	pCameraMovingTransform->Set_State(CTransform::STATE_RIGHT, vRight = pCameraTransform->Get_State(CTransform::STATE_RIGHT));
	pCameraMovingTransform->Set_State(CTransform::STATE_UP, vUp = pCameraTransform->Get_State(CTransform::STATE_UP));
	pCameraMovingTransform->Set_State(CTransform::STATE_LOOK, vLook = pCameraTransform->Get_State(CTransform::STATE_LOOK));
	pCameraMovingTransform->Set_State(CTransform::STATE_POSITION, pCameraTransform->Get_State(CTransform::STATE_POSITION));



	static_cast<CMovingCamera*>(Camera_Moving)->Add_Movement(2.f, 0.f,
		*D3DXVec3Normalize(&vSpeed, &(-vLook)) * 1.5f, _float3(0.f, 0.f, 0.f),
		nullptr, nullptr, 0.1f, 0.f
	);

	static_cast<CMovingCamera*>(Camera_Moving)->Add_Movement(3.f, 0.f,
		_float3(0.f, 0.f, 0.f), *D3DXVec3Normalize(&vSpeed, &(-vLook)) * 4.f,
		nullptr, nullptr, 1.f, 0.05f
	);*/

}

CLevel_RedPlanet * CLevel_RedPlanet::Create()
{
	CLevel_RedPlanet*		pInstance = new CLevel_RedPlanet();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_RedPlanet");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_RedPlanet::Free()
{
	__super::Free();

	delete this;
}

void CLevel_RedPlanet::RedPlanet_Event(float fTimeDelta)
{
	m_fTextBoxTime -= fTimeDelta;


	if (m_fTextBoxTime <= 298.f && !m_bEventCheck[0])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("Red Planet ���� ȭ������ �����ϰ� �ű�� ����\n �뺴���� ����Ѵٰ� �ϴ±���.\n ���� ���̴� ȭ������ ���������� ȣ�����ְ�. "), 0);
	}

	if (m_fTextBoxTime <= 297.7f && !m_bEventCheck[0])
	{
		GAMEINSTANCE->StopSound(10);
	}

	if (m_fTextBoxTime <= 296.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[0] = true;
	}

	if (m_fTextBoxTime <= 294.f && !m_bEventCheck[1])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("�ֺ��� ���� �ٰ����°� ������?."), 0);
	}

	if (m_fTextBoxTime <= 293.7f && !m_bEventCheck[1])
	{
		GAMEINSTANCE->StopSound(10);
	}

	if (m_fTextBoxTime <= 292.f && !m_bEventCheck[1])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[1] = true;
	}


	if (m_fTextBoxTime <= 290.f && !m_bEventCheck[2])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("����! ���濡 �� ��ü���� ���������־�! \n ���ݹٷ� ���������� �����״� ���ݸ� �����ְ�!"), 0);
	}


	if (m_fTextBoxTime <= 289.7f && !m_bEventCheck[2])
	{
		GAMEINSTANCE->StopSound(10);
	}


	if (m_fTextBoxTime <= 288.f && !m_bEventCheck[2])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[2] = true;
	}

	if (m_fTextBoxTime <= 229.f && !m_bEventCheck[3])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("���������� ���� �� �Ͱ���! ���ݸ� �� �����ְԳ�!"), 0);
	}


	if (m_fTextBoxTime <= 228.7f && !m_bEventCheck[3])
	{
		GAMEINSTANCE->StopSound(10);
	}

	if (m_fTextBoxTime <= 225.f && !m_bEventCheck[3])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[3] = true;
	}


	//////////////�������� ���� ����Ʈ ī��Ʈ 0 �ɽ� �Ʊ�AI����/////////////////// 

	if (m_fTextBoxTime <= 190.f && !m_bEventCheck[4])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("���������� �����߳�! \n ��� ���ҳ� ������ ����ڰ�!"), 0);

		m_fSpawnTime -= fTimeDelta;

		if (m_fSpawnTime < 1.7f && m_bSpawnCheck)
		{
			if (!GAMEINSTANCE->Add_GameObject<CAI_Friendly>(CURRENT_LEVEL, TEXT("AI_Friendly"), nullptr, nullptr, true))
				return;

			m_fSpawnTime = 2.0f;
		}

	}

	if (m_fTextBoxTime <= 189.7f && !m_bEventCheck[4])
	{
		GAMEINSTANCE->StopSound(10);
	}

	


	// 7�ʵ� �Ʊ����� false

	if (m_fTextBoxTime <= 183.f && !m_bEventCheck[4])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[4] = true;
	}




	if (m_fTextBoxTime <= 290.f && !m_bEventCheck[8])
	{
		m_pQuestBoxObject->Set_Enable(true);

		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiX, (LONG)270 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("            ���� �ӹ�\n�������� �������� ���� / ȭ���� ȣ�� \n      �����ð� (��) : "), 0);
		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiXCount, (LONG)308 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("    %d"), 1, (_uint)m_fMaxTime);

		if (m_iFontiX <= 1040)
		{
			m_iFontiX = 1040;
		}

		if (m_iFontiXCount <= 1150)
		{
			m_iFontiXCount = 1150;
		}
 
		m_iFontiX -= 0.8;
		m_iFontiXCount -= 0.8;
		m_fMaxTime -= fTimeDelta;
	}


	if (m_fTextBoxTime <= 190 && !m_bEventCheck[8])
	{
		m_pQuestBoxObject->Set_Enable(false);
		m_bEventCheck[8] = true;
	}


	// ������ false ����� óġ�ӹ�
	if (m_fTextBoxTime <= 190 && !m_bEventCheck[9])
	{
		
		m_pQuestBoxObject->Set_Enable(true);

		list<CGameObject*>* Enemy_SpaceBody = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("EnemySpace_Body"));
		iEnemyCount = 0;
		for (auto& elem : *Enemy_SpaceBody)
		{
			if (elem->Get_Enable())
			{
				iEnemyCount++;
			}
		}
		

		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiX, (LONG)270 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("            ���� �ӹ�  \n  ��� �� ��ü ���� / ȭ���� ȣ��\n���� �� : "), 0);
		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiXCount, (LONG)308 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("%d"), 1, (_uint)iEnemyCount);
	
		if (m_iFontiX <= 1040)
		{
			m_iFontiX = 1040;
		}

		if (m_iFontiXCount <= 1150)
		{
			m_iFontiXCount = 1150;
		}

		m_iFontiX -= 0.8;
		m_iFontiXCount -= 0.8;

		m_bSpawnCheck = false;
	}


	// (ȭ��ȣ��? ����) ����Ʈ�ڽ� �Ҹ�, ��Ʈ �Ҹ�
	if (m_fTextBoxTime <= 190 && iEnemyCount <= 0 && !m_bEventCheck[9])
	{
		m_pQuestBoxObject->Set_Enable(false);
		m_bEventCheck[9] = true;
	}



	if (m_iEnemyCount <= 0 && !m_bSpawnCheck && m_bEventCheck[9])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[6] = true;
		GAMEINSTANCE->Add_Text(_point{ (LONG)640, (LONG)400 }, D3DCOLOR_ARGB(255, 0, 204, 255), 2.f, TEXT("Red Planet �ӹ��Ϸ�!"), 0);
		bRedClear = true;
		//GAMEINSTANCE->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_SELECTPLANET));
		Change_Level(nullptr, LEVEL_SELECTPLANET);
		GAMEINSTANCE->StopAll();
	}


		
}

