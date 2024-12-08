#include "stdafx.h"
#include "Level_VenusPlanet.h"
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
#include <UITest.h>
#include <SkyBox.h>
#include "../Default/EnemySpace_Body.h"
#include "StatusBar.h"
#include "HpBar.h"
#include "BoosterBar.h"
#include "ShieldBar.h"
#include "BulletUI.h"
#include "BulletCountUI.h"
#include "AI_Friendly.h"
#include "MovingCamera.h"
#include "../Default/EnemySpace_Body.h"
#include "Kang_Ship_Body.h"
#include "Planet_Venus.h"
#include "Math_Utillity.h"
#include "Light_Moon.h"
#include <SelectPlanet_SkyBox.h>
#include "TextBox.h"
#include "Quest.h"
#include "Enemy_TagetBoard.h"
#include <VenusPlanet_SkyBox.h>
#include "Planet_Select.h"
#include "Enemy_Roller.h"


CLevel_VenusPlanet::CLevel_VenusPlanet()
{

}

HRESULT CLevel_VenusPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;




	if (!GAMEINSTANCE->Add_GameObject<CVenusPlanet_SkyBox>(LEVEL_VENUSPLANET, TEXT("SkyBox")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_VENUSPLANET, TEXT("Aim_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVEL_VENUSPLANET, TEXT("Light_Moon")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVEL_VENUSPLANET, TEXT("Status_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVEL_VENUSPLANET, TEXT("HP_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVEL_VENUSPLANET, TEXT("Booster_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVEL_VENUSPLANET, TEXT("Shield_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVEL_VENUSPLANET, TEXT("NormalBullet_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVEL_VENUSPLANET, TEXT("BulletCount_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_VENUSPLANET, TEXT("Aim")))
		return E_FAIL;

	m_pTextBoxObject = GAMEINSTANCE->Add_GameObject<CTextBox>(LEVEL_VENUSPLANET, TEXT("TextBox_Yang"));
	m_pTextBoxObject->Set_Enable(false);

	m_pQuestBoxObject = GAMEINSTANCE->Add_GameObject<CQuest>(LEVEL_VENUSPLANET, TEXT("Quest_UI"));
	m_pQuestBoxObject->Set_Enable(false);


	m_pPlanetObject = GAMEINSTANCE->Add_GameObject<CPlanet_Select>(LEVEL_VENUSPLANET, TEXT("Earth"));
	m_pPlanetObject->Set_Enable(false);

	

	GAMEINSTANCE->PlayBGM(TEXT("VenusPlanet.wav"), 0.1f);
	//GAMEINSTANCE->PlaySoundW(TEXT("VenusPlanet.wav"), BGM, 1.f);
	return S_OK;
}

void CLevel_VenusPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	/*if (m_bCinematic)
	{
		m_fTime -= fTimeDelta;
		if (0.f > m_fTime)
		{
			m_bCinematic = false;
			GAMEINSTANCE->Swap_Camera();
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
	}*/

	if (m_bCinematic)
	{
		m_fTime -= fTimeDelta;
		
		if (2.f > m_fTime)
		{
			m_pTagetObject->Get_Component<CRigid_Body>()->Set_Booster(true);

			m_pTagetObject->Get_Component<CRigid_Body>()->Add_Force(1.f * m_pTagetObject->Get_Component<CTransform>()->Get_State(CTransform::STATE_LOOK));
			
			GAMEINSTANCE->Add_Shaking(1.f, 0.1f);
			GAMEINSTANCE->Add_BlurWidth();
		
		}
		if (1.f > m_fTime)
			GAMEINSTANCE->Sub_FadeOffSet();

		if (0.f > m_fTime)
		{
			m_bCinematic = false;
			GAMEINSTANCE->Swap_Camera();
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
		}
	}
	else
	{
		GAMEINSTANCE->Add_FadeOffSet();
	}

	if (KEY_INPUT(KEY::F1, KEY_STATE::TAP))
	{
		GAMEINSTANCE->StopSound(BGM);
		GAMEINSTANCE->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_SELECTPLANET));
	}

	VenusPlanet_Event(fTimeDelta);
}

HRESULT CLevel_VenusPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("Venus Planet �����Դϴ�. "));

	return S_OK;
}

void CLevel_VenusPlanet::Change_Level(void* pArg, _uint _iNextLevel)
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
}

void CLevel_VenusPlanet::VenusPlanet_Event(_float fTimeDelta)
{
	m_fTextBoxTime -= fTimeDelta;


	if (m_fTextBoxTime <= 298.f && !m_bEventCheck[0])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("�ڳװ� ����� ���� ���� ���Ϸ��ΰ�? \n ����� �ϰ� ����� ������ �ȵ鱺. "), 0);
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
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("�켱 ��ü ���� ���� �˷��ְڴ� \n �̵�Ű�� ���콺�� �̿��� ��ü�� �����ϼ�����."), 0);
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

	if (m_fTextBoxTime <= 290 && !m_bEventCheck[2])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("���� �츮�� ���� ���й������� �ڵ� ������ �����ϳ�."), 0);
	}

	if (m_fTextBoxTime <= 289.7f && !m_bEventCheck[2])
	{
		GAMEINSTANCE->StopSound(10);
	}

	if (m_fTextBoxTime <= 288 && !m_bEventCheck[2])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[2] = true;
	}

	if (m_fTextBoxTime <= 286 && !m_bEventCheck[3])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("�Ʒÿ� ������ ������ ��ġ�� ��ݽ�ų�´�\n�ڵ����� �� �̿��� ó���غ���."), 0);
	}

	if (m_fTextBoxTime <= 285.7f && !m_bEventCheck[2])
	{
		GAMEINSTANCE->StopSound(10);
	}

	if (m_fTextBoxTime <= 284.f && !m_bEventCheck[3])
	{
		m_pTextBoxObject->Set_Enable(false);

		for (int i = 0; i < 3; ++i)
		{
			CTransform* pEnemyTransform = GAMEINSTANCE->Add_GameObject<CEnemy_TagetBoard>(CURRENT_LEVEL, TEXT("Enemy_TargetBoard"))->Get_Component<CTransform>();
			_float3 SpawnPos{ 0, 0.f, 50.f };

			_float RotateX = (_float)(rand() % 361);
			_float RotateY = (_float)(rand() % 361);
			_float RotateZ = (_float)(rand() % 361);
			RotateX = D3DXToRadian(RotateX);
			RotateY = D3DXToRadian(RotateY);
			RotateZ = D3DXToRadian(RotateZ);


			SpawnPos = CMath_Utillity::Rotate_Vec3(_float3(RotateX, RotateY, RotateZ), SpawnPos);

			pEnemyTransform->Set_State(CTransform::STATE_POSITION, SpawnPos);
		}
		
		
		m_bEventCheck[3] = true;
	}
	 

	if (m_fTextBoxTime <= 284.f && !m_bEventCheck[4])
	{
		list<CGameObject*>* TargetBoards = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Enemy_TargetBoard"));
		iEnemyCount = 0;
		for (auto& elem : *TargetBoards)
		{
			if (elem->Get_Enable())
			{
				iEnemyCount++;
			}
		}

		m_pQuestBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiX, (LONG)270 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("            ���� �ӹ�\n          �Ʒ� �� �ı� \n        ���� �� : "), 0);
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
	}

	if (iEnemyCount <= 0 && m_bEventCheck[3] && !m_bEventCheck[5])
	{
		m_pQuestBoxObject->Set_Enable(false);
		m_bEventCheck[4] = true;
		
	}

	if (iEnemyCount <= 0 && m_bEventCheck[4] && !m_bEventCheck[5])
	{
		m_fTextBoxTime = 300;
		m_bEventCheck[5] = true;
	}

	if (m_fTextBoxTime <= 299 && m_bEventCheck[5] && !m_bEventCheck[6])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("���� ��±���!! \n ��ٸ� �ϴٴ°� �������."), 0);
	}

	if (m_fTextBoxTime <= 298.7 && m_bEventCheck[5] && !m_bEventCheck[6])
	{
		GAMEINSTANCE->StopSound(10);
	}

	if (m_fTextBoxTime <= 297 && m_bEventCheck[5] && !m_bEventCheck[6])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[6] = true;
	}

	
	if (m_fTextBoxTime <= 295 &&  m_bEventCheck[6] && !m_bEventCheck[7])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("���� �⵿�Ʒ��� ���ڴ� \n����Ʈ Ű�� ���� �ν��͸� ����غ���."), 0);
	}
	
	if (m_fTextBoxTime <= 294.7 && m_bEventCheck[6] && !m_bEventCheck[7])
	{
		GAMEINSTANCE->StopSound(10);
	}


	if (m_fTextBoxTime <= 293  && m_bEventCheck[6] && !m_bEventCheck[7])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[7] = true;
	}

	if (m_fTextBoxTime <= 291 && m_bEventCheck[7] && !m_bEventCheck[8])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("�������� �ؾ��� �������ʱ��� \n�� �ʿ��Ѱ� �� �˷��ذ� ������ \n���� �䰪�� �ؾ߰���?"), 0);
	}

	if (m_fTextBoxTime <= 290.7 && m_bEventCheck[7] && !m_bEventCheck[8])
	{
		GAMEINSTANCE->StopSound(10);
	}

	if (m_fTextBoxTime <= 289 && m_bEventCheck[7] && !m_bEventCheck[8])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[8] = true;
	}

	if (m_fTextBoxTime <= 287 && m_bEventCheck[8] && !m_bEventCheck[9])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("�տ� �츮 �༺ ��Ż�� �������״� 'F' Ű�� ����\n 'ũ���� ����̺�'�� ����ϰ�. "), 0);
	}

	if (m_fTextBoxTime <= 286.7 && m_bEventCheck[8] && !m_bEventCheck[9])
	{
		GAMEINSTANCE->StopSound(10);
	}

	
	if (m_fTextBoxTime <= 287 && m_bEventCheck[8] && !m_bEventCheck[9])
	{
		m_pPlanetObject->Set_Enable(true);
	}
}

CLevel_VenusPlanet* CLevel_VenusPlanet::Create()
{
	CLevel_VenusPlanet*		pInstance = new CLevel_VenusPlanet();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_RedPlanet");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_VenusPlanet::Free()
{
	__super::Free();

	delete this;
}



