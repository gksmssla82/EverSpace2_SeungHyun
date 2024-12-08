#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Engine)
class CGameObject;
END

BEGIN(Client)

class CLevel_SelectPlanet final : public CLevel
{
public:
	CLevel_SelectPlanet();
	virtual ~CLevel_SelectPlanet() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float fTimeDelta);
	virtual HRESULT Render();

	virtual void	Change_Level(void* pArg, _uint _iNextLevel) ;
	virtual HRESULT Complete_Condition() { return S_OK; }

public:
	virtual void OnTimerEvent(const _uint _iEventIndex) override;

public:
	static CLevel_SelectPlanet* Create();
	virtual void Free() override;

private:
	void SelectPlanet_Event(float fTimeDelta);

private:
	static _bool m_bFirst;





};

END

