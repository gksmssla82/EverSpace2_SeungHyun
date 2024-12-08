#include "stdafx.h"
#include "Level_ExoPlanet.h"
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
#include "Quest.h"
#include <SelectPlanet_SkyBox.h>
#include "ExoPlanet_SkyBox.h"
#include "Rock_1.h"
#include "Rock_2.h"
#include "Rock_3.h"
#include "Rock_4.h"
#include "Enemy_Scourge.h"
#include "TextBox.h"
#include "Quest.h"
#include "Planet_Select.h"
#include "Satellite_1.h"
#include "Satellite_2.h"
#include "Satellite_3.h"
#include <time.h>


CLevel_ExoPlanet::CLevel_ExoPlanet()
{

}

HRESULT CLevel_ExoPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	

	
	if (!GAMEINSTANCE->Add_GameObject<CExoPlanet_SkyBox>(LEVEL_EXOPLANET, TEXT("SkyBox")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_EXOPLANET, TEXT("Aim_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVEL_EXOPLANET, TEXT("Light_Moon")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVEL_EXOPLANET, TEXT("Status_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVEL_EXOPLANET, TEXT("HP_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVEL_EXOPLANET, TEXT("Booster_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVEL_EXOPLANET, TEXT("Shield_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVEL_EXOPLANET, TEXT("NormalBullet_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVEL_EXOPLANET, TEXT("BulletCount_UI")))
		return E_FAIL;

	m_pTextBoxObject = GAMEINSTANCE->Add_GameObject<CTextBox>(LEVEL_EXOPLANET, TEXT("TextBox_Yang"));
	m_pTextBoxObject->Set_Enable(false);

	m_pQuestBoxObject = GAMEINSTANCE->Add_GameObject<CQuest>(LEVEL_EXOPLANET, TEXT("Quest_UI"));
	m_pQuestBoxObject->Set_Enable(false);


	m_pPlanetObject = GAMEINSTANCE->Add_GameObject<CPlanet_Select>(LEVEL_EXOPLANET, TEXT("Earth"));
	m_pPlanetObject->Set_Enable(false);

	
	for (int i = 0; i < 300; ++i)
	{
		if (!GAMEINSTANCE->Add_GameObject<CRock_1>(LEVEL_EXOPLANET, TEXT("Rock_1")))
			return E_FAIL;

		if (!GAMEINSTANCE->Add_GameObject<CRock_2>(LEVEL_EXOPLANET, TEXT("Rock_2")))
			return E_FAIL;

		if (!GAMEINSTANCE->Add_GameObject<CRock_3>(LEVEL_EXOPLANET, TEXT("Rock_3")))
			return E_FAIL;

		if (!GAMEINSTANCE->Add_GameObject<CRock_4>(LEVEL_EXOPLANET, TEXT("Rock_4")))
			return E_FAIL;
	}


	for (int i = 0; i < 2; ++i)
	{

		if (!GAMEINSTANCE->Add_GameObject<CSatellite_1>(LEVEL_EXOPLANET, TEXT("Satellite_1")))
			return E_FAIL;

		if (!GAMEINSTANCE->Add_GameObject<CSatellite_2>(LEVEL_EXOPLANET, TEXT("Satellite_2")))
			return E_FAIL;
	}
	

	if (!GAMEINSTANCE->Add_GameObject<CSatellite_3>(LEVEL_EXOPLANET, TEXT("Satellite_3")))
		return E_FAIL;


	
	GAMEINSTANCE->PlayBGM(TEXT("ExoPlanet.wav"), 0.1f);

	return S_OK;
}

void CLevel_ExoPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);		



	if (m_bCinematic)
	{
		m_fTime -= fTimeDelta;
		//Ÿ�� �̺�Ʈ ���ɾ�
		if (2.f > m_fTime)
		{
			m_pTagetObject->Get_Component<CRigid_Body>()->Set_Booster(true);

			m_pTagetObject->Get_Component<CRigid_Body>()->Add_Force(1.f * m_pTagetObject->Get_Component<CTransform>()->Get_State(CTransform::STATE_LOOK));
			
			GAMEINSTANCE->Add_Shaking(1.f, 0.1f);
			GAMEINSTANCE->Add_BlurWidth();

		}
		if (1.f > m_fTime)
			GAMEINSTANCE->Sub_FadeOffSet();

		srand(unsigned(time(NULL)));
		
		Scouge_Create(fTimeDelta);
		ExoPlanet_Event(fTimeDelta);
		//Rock_Create(fTimeDelta);


		if (0.f > m_fTime)
		{
			m_bCinematic = false;
			

			CSong_Ship_Body* pMainCharacter = nullptr;
			GAMEINSTANCE->Reset_BlurWidth();
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
		}
	}
	else
	{
		GAMEINSTANCE->Add_FadeOffSet();
	}


}

HRESULT CLevel_ExoPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("Exo Planet �����Դϴ�. "));



	return S_OK;
}

void CLevel_ExoPlanet::Change_Level(void* pArg, _uint _iNextLevel)
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

void CLevel_ExoPlanet::Scouge_Create(_float fTimeDelta)
{

	m_fSpawnTime -= fTimeDelta;

	CCamera* pCurrentCam = GAMEINSTANCE->Get_Camera();

	CTransform* TransformCom = pCurrentCam->Get_Target();

	CTransform* pPlayerTransformCom = TransformCom->Get_Owner()->Get_Component<CTransform>();

	if (m_fSpawnTime < 0.f)
	{

		CTransform* pEnemyTransform = GAMEINSTANCE->Add_GameObject<CEnemy_Scourge>(CURRENT_LEVEL, TEXT("Enemy_Scourge"), nullptr, nullptr, true)->Get_Component<CTransform>();
		_float3 pPlayerPos = pPlayerTransformCom->Get_World_State(CTransform::STATE_POSITION);

		_float RotateX = (_float)(rand() % 361);
		_float RotateY = (_float)(rand() % 361);
		_float RotateZ = (_float)(rand() % 361);
		RotateX = D3DXToRadian(RotateX);
		RotateY = D3DXToRadian(RotateY);
		RotateZ = D3DXToRadian(RotateZ);

		pPlayerPos = CMath_Utillity::Rotate_Vec3(_float3(RotateX, RotateY, RotateZ), pPlayerPos);
		pEnemyTransform->Set_State(CTransform::STATE_POSITION, pPlayerPos, true);

		m_fSpawnTime = 2.f;
	}

}

void CLevel_ExoPlanet::ExoPlanet_Event(_float fTimeDelta)
{
	m_fTextBoxTime -= fTimeDelta;


	if (m_fTextBoxTime <= 298.f && !m_bEventCheck[0])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("�̹� �ӹ��� ���� �༺ ���� �������� ��ŷ�ؾ��ϳ�."), 0);
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
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("�� �༺�� ���� ������� � ������ ���� ���ٰ� �����\n������ ��Ű�� �ʰ� ������ ���� �������� ��ŷ���ְ�."), 0);
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
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("�̷�! ���� ��Ų�Ͱ���\n���� �ִ��� ������ �������´� ���ѷ��ְ�! "), 0);
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

	if (m_fTextBoxTime <= 290.f && !m_bEventCheck[3])
	{
		m_pQuestBoxObject->Set_Enable(true);

		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiX, (LONG)270 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("            ���� �ӹ�\n      ���� ������ ��ŷ  \n     �����ð� (��) :"), 0);
		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiXCount, (LONG)308 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("\n  %d"), 1, (_uint)m_fMaxTime);

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

	if (m_fTextBoxTime <= 280.f && !m_bEventCheck[4])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("�̷� ��ģ�ڽĵ�! �ڻ�Ư�����ΰ� ī��ī���� �ϴٴ�.."), 0);
	}

	if (m_fTextBoxTime <= 279.7f && !m_bEventCheck[4])
	{
		GAMEINSTANCE->StopSound(10);
	}

	if (m_fTextBoxTime <= 277.f && !m_bEventCheck[4])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[4] = true;
	}

	if (m_fTextBoxTime <= 274.f && !m_bEventCheck[5])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("�����ʾ�! �ȱ׷��� � ���틚����\n�����̴´� �������ִµ�\n�� �ڻ�Ư���� ���� �Ű��� ����ϴٴ�!"), 0);
	}

	if (m_fTextBoxTime <= 273.7f && !m_bEventCheck[5])
	{
		GAMEINSTANCE->StopSound(10);
	}

	if (m_fTextBoxTime <= 271.f && !m_bEventCheck[5])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[5] = true;
	}

	if (m_fTextBoxTime <= 268 && !m_bEventCheck[6])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("������ �� ���� �簩�� ���� �������ʴ´�!"), 0);
	}

	if (m_fTextBoxTime <= 267.7 && !m_bEventCheck[6])
	{
		GAMEINSTANCE->StopSound(10);
	}

	if (m_fTextBoxTime <= 265 && !m_bEventCheck[6])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[6] = true;
	}

	if (m_fTextBoxTime <= 200 && !m_bEventCheck[7])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("��ü�� ���� �ļՉ��!!! ���� ���ѷ�!!"), 0);
	}

	if (m_fTextBoxTime <= 199.7 && !m_bEventCheck[7])
	{
		GAMEINSTANCE->StopSound(10);
	}

	if (m_fTextBoxTime <= 197 && !m_bEventCheck[7])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[7] = true;
	}

	if (m_fTextBoxTime <= 93 && !m_bEventCheck[8])
	{
		GAMEINSTANCE->PlaySoundW(TEXT("TextBox.wav"), 10, 1.f);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("�̷�.. ���ϰڳ� ������ �븮����.."), 0);
	}

	if (m_fTextBoxTime <= 92.7 && !m_bEventCheck[8])
	{
		GAMEINSTANCE->StopSound(10);
	}

	if (m_fTextBoxTime <= 90 && !m_bEventCheck[8])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[8] = true;
	}

	if (m_fMaxTime <= 0 && !m_bEventCheck[3])
	{
		m_pQuestBoxObject->Set_Enable(false);
		m_bEventCheck[3] = true;
		bExoClear = false;
		GAMEINSTANCE->Add_Text(_point{ (LONG)640, (LONG)400 }, D3DCOLOR_ARGB(255, 0, 204, 255), 3.f, TEXT("�ӹ� ����!!!"), 0);
		GAMEINSTANCE->Get_Instance()->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_SELECTPLANET));
	}
}

void CLevel_ExoPlanet::Rock_Create(_float fTimeDelta)
{
	/*m_fRockSqawnTime -= fTimeDelta;

	CCamera* pCurrentCam = GAMEINSTANCE->Get_Camera();

	CTransform* TransformCom = pCurrentCam->Get_Target();

	CTransform* pPlayerTransformCom = TransformCom->Get_Owner()->Get_Component<CTransform>();

	srand(unsigned(time(NULL)));

	if (TransformCom && m_fRockSqawnTime <= 0)
	{
		CTransform* pRock_1Transform = GAMEINSTANCE->Add_GameObject<CRock_1>(CURRENT_LEVEL, TEXT("Rock_1"), nullptr, nullptr, true)->Get_Component<CTransform>();
		CTransform* pRock_2Transform = GAMEINSTANCE->Add_GameObject<CRock_2>(CURRENT_LEVEL, TEXT("Rock_2"), nullptr, nullptr, true)->Get_Component<CTransform>();
		CTransform* pRock_3Transform = GAMEINSTANCE->Add_GameObject<CRock_3>(CURRENT_LEVEL, TEXT("Rock_3"), nullptr, nullptr, true)->Get_Component<CTransform>();
		CTransform* pRock_4Transform = GAMEINSTANCE->Add_GameObject<CRock_4>(CURRENT_LEVEL, TEXT("Rock_4"), nullptr, nullptr, true)->Get_Component<CTransform>();

		_float3 pPlayerPos = pPlayerTransformCom->Get_World_State(CTransform::STATE_POSITION);

		_float RotateX = (_float)(rand() % 361);
		_float RotateY = (_float)(rand() % 361);
		_float RotateZ = (_float)(rand() % 361);

		RotateX = D3DXToRadian(RotateX);
		RotateY = D3DXToRadian(RotateY);
		RotateZ = D3DXToRadian(RotateZ);

		pPlayerPos = CMath_Utillity::Rotate_Vec3(_float3(RotateX, RotateY, RotateZ), pPlayerPos);

		
		pRock_1Transform->Set_State(CTransform::STATE_POSITION, pPlayerPos, true); 
		pRock_2Transform->Set_State(CTransform::STATE_POSITION, pPlayerPos, true); 
		pRock_3Transform->Set_State(CTransform::STATE_POSITION, pPlayerPos, true); 
		pRock_4Transform->Set_State(CTransform::STATE_POSITION, pPlayerPos, true); 


	
		m_fRockSqawnTime = 1.f;
	}*/

	
}

CLevel_ExoPlanet* CLevel_ExoPlanet::Create()
{
	CLevel_ExoPlanet* pInstance = new CLevel_ExoPlanet();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_ExoPlanet");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_ExoPlanet::Free()
{
	__super::Free();

	delete this;
}



