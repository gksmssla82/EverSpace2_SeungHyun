#include "stdafx.h"
#include "Level_SelectPlanet.h"
#include "GameInstance.h"
#include "Level_Loading.h"
#include <time.h>
#include "Cam_FPS.h"
#include "Cam_Shoulder.h"
#include "Cam_TPS.h"
#include "MovingCamera.h"
#include "Cam_Free.h"
#include "Song_Ship_Body.h"
#include "SelectPlanet_SkyBox.h"
#include "Default_Aim.h"
#include "BoosterBar.h"
#include "StatusBar.h"
#include "HpBar.h"
#include "ShieldBar.h"
#include "BulletUI.h"
#include "BulletCountUI.h"
#include "Planet_Venus.h"
#include "Planet_Sun.h"
#include "Planet_Red.h"
#include "Planet_Magma.h"
#include "Planet_Exo.h"
#include "Light_Moon.h"
#include "Quest.h"
#include "SpaceDust_PSystem.h"
#include "TextBox.h"
#include <Bomb_Effect.h>
#include "Warring.h"
#include "Dive.h"
#include "Monster.h"
#include "Enemy_TagetBoard.h"
#include "Enemy_StagBeetle.h"
#include "Planet_Select.h"
#include "Rock_2.h"
#include "Rock_3.h"
#include "Rock_4.h"
#include "Satellite_1.h"
#include "Satellite_2.h"
#include "Satellite_3.h"
#include <Kang_Ship_Body.h>
#include "Enemy_Scourge.h"
#include "EnemySpace_Body.h"
#include "Enemy_Roller.h"
#include <Enemy_GPS.h>
#include <EnemySpace_Body.h>
#include "Satellite_3.h"
#include "Boss_HpTable.h"
#include "Boss_HpBar.h"
#include "Boss_Name.h"
#include "TransportShip_HpBar.h"
#include <SunSpaceBoss_Body.h>
#include <TextureDrawUI.h>
#include "Normal_Turret.h"

_bool CLevel_SelectPlanet::m_bFirst = false;


CLevel_SelectPlanet::CLevel_SelectPlanet()
{
}

HRESULT CLevel_SelectPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	if (!m_bFirst)
	{
		//CGameObject* pPlayer = GAMEINSTANCE->Add_GameObject<CKang_Ship_Body>(LEVEL_STATIC, TEXT("Player"));
		//pPlayer->Set_Controller(CONTROLLER::AI);

		//list<CGameObject*>* pAiObect = GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player"));

		//if (!pAiObect)
		//	return E_FAIL;

		///*if (Get_Controller() == CONTROLLER::PLAYER)
		//	return;*/

		//CKang_Ship_Body* pSubPlayerCharacter = nullptr;

		//for (auto& elem : *pAiObect)
		//{
		//	pSubPlayerCharacter = dynamic_cast<CKang_Ship_Body*>(elem);

		//	if (pSubPlayerCharacter)
		//	{
		//		CCamera* pCurCamera = GAMEINSTANCE->Get_Camera();
		//		CTransform* pCurCameraTransform = nullptr;
		//		if (pCurCamera)
		//			pCurCameraTransform = pCurCamera->Get_Transform();

		//		if (pCurCameraTransform)
		//		{
		//			GAMEINSTANCE->Switch_Player(pCurCameraTransform, elem->Get_Component<CTransform>(), TEXT("TPS"), 1.f);
		//			GAMEINSTANCE->Add_TimerEvent(0, this, 1.f);
		//			break;
		//		}
		//	}
		//}

		
	}
	
	
	if (!GAMEINSTANCE->Add_GameObject<CSelectPlanet_SkyBox>(LEVEL_SELECTPLANET, TEXT("SkyBox")))
		return E_FAIL;
	/*if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_SELECTPLANET, TEXT("Aim")))
		return E_FAIL;*/

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVEL_SELECTPLANET, TEXT("Status_UI")))

		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVEL_SELECTPLANET, TEXT("HP_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVEL_SELECTPLANET, TEXT("Booster_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVEL_SELECTPLANET, TEXT("Shield_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVEL_SELECTPLANET, TEXT("NormalBullet_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVEL_SELECTPLANET, TEXT("BulletCount_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVEL_SELECTPLANET, TEXT("Light_Moon")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_REDPLANET, TEXT("Aim_UI")))
		return E_FAIL;


	//if (!GAMEINSTANCE->Add_GameObject<CPlanet_Venus>(LEVEL_SELECTPLANET, TEXT("Venus")))
	//	return E_FAIL;


	if (bSunClear == false)
	{
		if (!GAMEINSTANCE->Add_GameObject<CPlanet_Sun>(LEVEL_SELECTPLANET, TEXT("Sun")))
			return E_FAIL;
	}
	if (bRedClear == false)
	{
		if (!GAMEINSTANCE->Add_GameObject<CPlanet_Red>(LEVEL_SELECTPLANET, TEXT("Red")))
			return E_FAIL;
	}
	if (bMagmaClear == false)
	{
		if (!GAMEINSTANCE->Add_GameObject<CPlanet_Magma>(LEVEL_SELECTPLANET, TEXT("Magma")))
			return E_FAIL;
	}
	if (bExoClear == false)
	{
		if (!GAMEINSTANCE->Add_GameObject<CPlanet_Exo>(LEVEL_SELECTPLANET, TEXT("Exo")))
			return E_FAIL;
	}
	

	//if (!GAMEINSTANCE->Add_GameObject<CBossHpTable>(LEVEL_SELECTPLANET, TEXT("Boss_HP_Table")))
	//	return E_FAIL;

	////if (!GAMEINSTANCE->Add_GameObject<CBossHpBar>(LEVEL_SELECTPLANET, TEXT("Boss_HP_Bar")))
	////	return E_FAIL;

	//if (!GAMEINSTANCE->Add_GameObject<CBossName>(LEVEL_SELECTPLANET, TEXT("Boss_Name")))
	//	return E_FAIL;

	/*if (!GAMEINSTANCE->Add_GameObject<CTransportShip_HpBar>(LEVEL_SELECTPLANET, TEXT("TransportShip_HP_Bar")))
		return E_FAIL;*/


	//if (!GAMEINSTANCE->Add_GameObject<CEnemy_StagBeetle>(LEVEL_SELECTPLANET, TEXT("Enemy_StagBeetle")))
	//	return E_FAIL;
	//
	//if (!GAMEINSTANCE->Add_GameObject<CEnemy_TagetBoard>(LEVEL_SELECTPLANET, TEXT("Enemy_TagetBoard")))
	//	return E_FAIL;

	/*if (!GAMEINSTANCE->Add_GameObject<CEnemy_TagetBoard>(LEVEL_SELECTPLANET, TEXT("Enemy_TargetBoard")))
		return E_FAIL;*/

	/*if (!GAMEINSTANCE->Add_GameObject<CSatellite_1>(LEVEL_SELECTPLANET, TEXT("Satellite_1")))
		return E_FAIL;

 	//GAMEINSTANCE->Add_GameObject<CEnemy_GPS>(CURRENT_LEVEL,TEXT("GPS_Enemy"));

	if (!GAMEINSTANCE->Add_GameObject<CSatellite_2>(LEVEL_SELECTPLANET, TEXT("Satellite_2")))
		return E_FAIL;


	if (!GAMEINSTANCE->Add_GameObject<CSatellite_3>(LEVEL_SELECTPLANET, TEXT("Satellite_3")))
		return E_FAIL;*/

	//for (int i = 0; i < 10; ++i)
	//{
	//	if (!GAMEINSTANCE->Add_GameObject<CEnemy_Scourge>(LEVEL_SELECTPLANET, TEXT("Enemy_Scouge")))
	//		return E_FAIL;
	//}
    
	//for (int i = 0; i < 5; ++i)
	//{
	//	if (!GAMEINSTANCE->Add_GameObject<CEnemy_Roller>(LEVEL_SELECTPLANET, TEXT("Enemy_Roller")))
	//		return E_FAIL;
	//}


	m_pTextBoxObject = GAMEINSTANCE->Add_GameObject<CTextBox>(LEVEL_SELECTPLANET, TEXT("TextBox_Yang"));
	m_pTextBoxObject->Set_Enable(false);


	m_pQuestBoxObject = GAMEINSTANCE->Add_GameObject<CQuest>(LEVEL_SELECTPLANET, TEXT("Quest_UI"));
	m_pQuestBoxObject->Set_Enable(false);

	//GAMEINSTANCE->Add_GameObject<CEnemySpace_Body>(LEVEL_SELECTPLANET, TEXT("EnemySpace_Body"));

	//GAMEINSTANCE->Add_GameObject<CTextureDrawUI>(LEVEL_SELECTPLANET, TEXT("TextureDraw_UI"));


	//((CSpaceDust_PSystem*)GAMEINSTANCE->Add_GameObject<CSpaceDust_PSystem>(LEVEL_SELECTPLANET, TEXT("Particle")))->AddParticle(500);


	
	// �༺ 2�� ���� ����
	//srand(unsigned(time(NULL)));
	//
	//LEVEL m_eNextPlanet = LEVEL_STATIC;
	//LEVEL m_ePreNextPlanet = m_eNextPlanet;
	//
	//for (_uint i = 0; i < 2; ++i)
	//{
	//	m_eNextPlanet = (LEVEL)(rand() % (_uint)LEVEL::LEVEL_SELECTPLANET);
	//
	//	if (m_eNextPlanet == m_ePreNextPlanet)
	//	{
	//		--i;
	//		continue;
	//	}
	//	
	//	switch (m_eNextPlanet)
	//	{
	//	case  LEVEL::LEVEL_REDPLANET:
	//		if (!GAMEINSTANCE->Add_GameObject<CPlanet_Red>(LEVEL_SELECTPLANET, TEXT("Red")))
	//			return E_FAIL;
	//		break;
	//
	//	case  LEVEL::LEVEL_EXOPLANET:
	//		if (!GAMEINSTANCE->Add_GameObject<CPlanet_Exo>(LEVEL_SELECTPLANET, TEXT("Exo")))
	//			return E_FAIL;
	//		break;
	//
	//	/*case  LEVEL::LEVEL_VENUSPLANET:
	//		if (!GAMEINSTANCE->Add_GameObject<CPlanet_Venus>(LEVEL_SELECTPLANET, TEXT("Venus")))
	//			return E_FAIL;
	//		break;*/
	//
	//	case  LEVEL::LEVEL_MAGMAPLANET:
	//		if (!GAMEINSTANCE->Add_GameObject<CPlanet_Magma>(LEVEL_SELECTPLANET, TEXT("Magma")))
	//			return E_FAIL;
	//		break;
	//	}
	//
	//	m_ePreNextPlanet = m_eNextPlanet;
	//}


	


  // �������� Ŭ����� ���� �̵�
	CCamera* pCurrentCam = GAMEINSTANCE->Get_Camera();
	CTransform* TransformCom = pCurrentCam->Get_Target();

	if (TransformCom)
	{
		CTransform* pPlayerTransformCom = TransformCom->Get_Owner()->Get_Component<CTransform>();
		pPlayerTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.f, 0.f, 0.f));

		pPlayerTransformCom->Get_Owner()->Get_Component<CRigid_Body>()->Reset_Force();
	}
	
	GAMEINSTANCE->Set_TimeScale(1.0f);


	
	GAMEINSTANCE->PlayBGM(TEXT("SelectPlanet.wav"), 0.1f);

	
	return S_OK;
}

void CLevel_SelectPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
		
	if (m_bCinematic)
	{
		m_fTime -= fTimeDelta;

		if (2.f > m_fTime)
		{
			m_pTagetObject->Get_Component<CRigid_Body>()->Set_Booster(true);
			
			m_pTagetObject->Get_Component<CRigid_Body>()->Add_Force(1.f*m_pTagetObject->Get_Component<CTransform>()->Get_State(CTransform::STATE_LOOK));

			GAMEINSTANCE->Add_Shaking(1.f, 0.1f);
			GAMEINSTANCE->Add_BlurWidth();
		
		}

		if(1.f>m_fTime)
			GAMEINSTANCE->Sub_FadeOffSet();

		if (0.f > m_fTime)
		{
			m_bCinematic = false;
		
			GAMEINSTANCE->StopSound(BGM);
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

			GAMEINSTANCE->Reset_BlurWidth();

			if (FAILED(GAMEINSTANCE->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create((LEVEL)m_iNextLevel))))
				return;

			/*list<CGameObject*>* pLayer = GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player"));
		
			for (auto& elem : *pLayer)
			{
				if (!elem)
					break;
				
				elem->Set_Controller(CONTROLLER::PLAYER);
			}*/
		}
	}
	else
	{
		GAMEINSTANCE->Add_FadeOffSet();
	}


	 
	SelectPlanet_Event(fTimeDelta);
	

	

}

HRESULT CLevel_SelectPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("Select Planet �����Դϴ�. "));
	

	return S_OK;
}

void CLevel_SelectPlanet::Change_Level(void* pArg, _uint _iNextLevel)
{
	if (m_bCinematic)
		return;


	m_fTime = 3.f;
	m_bCinematic = true;
	m_iNextLevel = _iNextLevel;

	list<CGameObject*>* pLayer = GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player"));
	for (auto& iter = pLayer->begin(); iter != pLayer->end(); ++iter)
	{
		if (CONTROLLER::PLAYER == (*iter)->Get_Controller())
		{
			
			if (m_pTagetObject)
				RETURN_WEAKPTR(m_pTagetObject);
			m_pTagetObject = *iter;
			WEAK_PTR(m_pTagetObject);


			(*iter)->Set_Controller(CONTROLLER::LOCK);
			(*iter)->Get_Component<CRigid_Body>()->Reset_Force();

			CComponent* Temp = (*iter)->Get_Component<CRigid_Body>();

			WEAK_PTR(Temp);
			if (pArg)
			{
				Temp = (*iter)->Get_Component<CTransform>();
				static_cast<CTransform*>(Temp)->LookAt((CTransform*)pArg, true);
				
			}
			RETURN_WEAKPTR(Temp);
		}
	}
	GAMEINSTANCE->Add_Shaking(0.1f, 0.f);
	/*CGameObject* Camera_Origin = GAMEINSTANCE->Get_Camera()->Get_Owner();
	CTransform* pCameraTransform = Camera_Origin->Get_Component<CTransform>();
	GAMEINSTANCE->Update_MovingCam();
	CGameObject* Camera_Moving = GAMEINSTANCE->Get_Camera()->Get_Owner();
	CTransform* pCameraMovingTransform = Camera_Moving->Get_Component<CTransform>();

	_float3	vUp, vLook, vRight,vSpeed;

	pCameraMovingTransform->Set_State(CTransform::STATE_RIGHT, vRight= pCameraTransform->Get_State(CTransform::STATE_RIGHT));
	pCameraMovingTransform->Set_State(CTransform::STATE_UP, vUp= pCameraTransform->Get_State(CTransform::STATE_UP));
	pCameraMovingTransform->Set_State(CTransform::STATE_LOOK, vLook= pCameraTransform->Get_State(CTransform::STATE_LOOK));
	pCameraMovingTransform->Set_State(CTransform::STATE_POSITION, pCameraTransform->Get_State(CTransform::STATE_POSITION));*/




	/*static_cast<CMovingCamera*>(Camera_Moving)->Add_Movement(1.f, 0.f,
		*D3DXVec3Normalize(&vSpeed, &(-vLook))*1.5f, _float3(0.f, 0.f, 0.f),
		nullptr, nullptr, 0.5f, 0.f
	);

	static_cast<CMovingCamera*>(Camera_Moving)->Add_Movement(3.f, 0.f,
		_float3(0.f,0.f,0.f), *D3DXVec3Normalize(&vSpeed, &(-vLook)),
		nullptr, nullptr, 1.f, 0.01f
	);*/

}



void CLevel_SelectPlanet::OnTimerEvent(const _uint _iEventIndex)
{
	list<CGameObject*>* pAiObect = GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player"));
	_uint i = 0;

	if (!pAiObect)
		return;

	if (0 == _iEventIndex)
	{
		CSong_Ship_Body* pMainCharacter = nullptr;

		for (auto& elem : *pAiObect)
		{
			pMainCharacter = dynamic_cast<CSong_Ship_Body*>(elem);

			if (pMainCharacter)
			{
				CCamera* pCurCamera = GAMEINSTANCE->Get_Camera();
				CTransform* pCurCameraTransform = nullptr;//�̰Ը³�
				if (pCurCamera)
					pCurCameraTransform = pCurCamera->Get_Transform();

				if (pCurCameraTransform)
				{
					GAMEINSTANCE->Switch_Player(pCurCameraTransform, elem->Get_Component<CTransform>(), TEXT("TPS"), 1.f);
				}

				break;
			}
		}
	}
}

CLevel_SelectPlanet* CLevel_SelectPlanet::Create()
{
	CLevel_SelectPlanet* pInstance = new CLevel_SelectPlanet();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_SelectPlanet");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_SelectPlanet::Free()
{
	__super::Free();

	delete this;
}

void CLevel_SelectPlanet::SelectPlanet_Event(float fTimeDelta)
{
	m_fTextBoxTime -= fTimeDelta;


	if (m_fTextBoxTime <= 297.f && !m_bEventCheck[0])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 },  D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("�츮 �༺�� �°��� ȯ���ϳ�. \n�� �༺ �ӹ��� ���� �پ��� ��� �� \n���༱�� ��ȭ�ϵ��� �ϰ�."), 0);
	}

	if (m_fTextBoxTime <= 296.7f && !m_bEventCheck[0])
	{
		GAMEINSTANCE->StopSound(10);
	}

	if (m_fTextBoxTime <= 293.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[0] = true;
	}

	if (m_fTextBoxTime <= 291.f && !m_bEventCheck[1])
	{
		m_pQuestBoxObject->Set_Enable(true);

		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiX, (LONG)280 },  D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("            ���� �ӹ�  \n�༺���� ������ ���� �������� Ŭ����"), 0);
	  
		m_iFontiX -= 0.8;

		if (m_iFontiX <= 1040)
		{
			m_iFontiX = 1040;
		}
	}

	


	if (m_bCinematic)
	{
		m_pQuestBoxObject->Set_Enable(false);
		m_bEventCheck[1] = true;
	}
}
