#pragma once

#include "Base.h"
#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CLevel abstract : public CBase
{
protected:
	CLevel();
	virtual ~CLevel() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float TimeDelta);
	virtual HRESULT Render();

	virtual void Change_Level(void* pArg, _uint _iNextLevel) =0;//������ �ٲ� �� ī�޶� ������� �־���
	virtual HRESULT Complete_Condition() = 0;//������ �ٲ� ���� ���� ����/��->�����ϸ� �Ѿ�Բ�

protected:
	_float		m_fTime = 5.f;
	_float      m_fTextBoxTime = 300.f;
	_float      m_fSpawnTime = 2.f;
	_float      m_fMaxTime = 100;
	
	_bool		m_bCinematic = false;
	_bool       m_bEventCheck[20] = { false };
	_bool       m_bSpawnCheck = true;

	_uint       m_iFontiX = 1360;
	_uint       m_iFontiXCount = 1470;
	_uint       m_iEnemyCount = 0;
	_uint		m_iNextLevel = 8;

protected:
	CGameObject* m_pTextBoxObject = nullptr;
	CGameObject* m_pQuestBoxObject = nullptr;
	CGameObject* m_pTagetObject = nullptr;
	CGameObject* m_pPlanetObject = nullptr;

	CGameObject* m_pBoss = nullptr;
	CGameObject* m_pBoss_HP_Bar = nullptr;
	CGameObject* m_pBoss_HP_Table = nullptr;
	CGameObject* m_pBoss_Name_Table = nullptr;
	

public:
	virtual void Free() override;

};

END