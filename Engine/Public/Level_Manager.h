#pragma once

#include "Base.h"

/* ���� ���ӳ��� ��������� ������ �����Ѵ�. */
/* ������ü�ÿ� ���� ������ �����Ѵ�. */
/* ������������ ����ߴ� ��ü�� �ڿ�(���ҽ���)�� �����Ѵ�. */

BEGIN(Engine)

class CLevel_Manager final : public CBase
{
	DECLARE_SINGLETON(CLevel_Manager)
public:
	CLevel_Manager();
	virtual ~CLevel_Manager() = default;

public:
	HRESULT Open_Level(_uint iLevelID, class CLevel* pLevel);
	
	HRESULT	Register_OpenLevelEvent(_uint iLevelID, CLevel* pLevel);
	HRESULT Call_OpenLevelEvent();
	
	void Set_CurrentLevelIndex(_uint iLevelID);
	_uint Get_CurrentLevelIndex();
	CLevel* Get_CurrentLevel();
	void Tick(_float fTimeDelta);
	HRESULT Render();

private:
	class CLevel*			m_pCurrentLevel = nullptr;
	_uint					m_iCurrentLevelID = 0;
	//�ε����뵵�� ����.
	_uint					m_iCurrentLevelIndex = 0;
	
	function<HRESULT(_uint, CLevel*)> m_OpenLevelEvent = nullptr;

private:
	_uint					m_iEventLevelID = 0;
	CLevel*					m_pEventLevel = nullptr;
	_bool					m_bEvent = false;


public:
	virtual void Free() override;
};

END