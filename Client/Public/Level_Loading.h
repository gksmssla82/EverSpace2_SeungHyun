#pragma once

/* �δ��� �ڿ���� �ε��ϴ� ���� ȭ�鿡 ������ �����ٲ���. */
/* �δ����� ��� ������� ������?? */
/* �� ����ϸ� ���������� ����.�� */

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)

class CLevel_Loading final : public CLevel
{
public:
	CLevel_Loading();
	virtual ~CLevel_Loading() = default;

public:
	virtual HRESULT Initialize(LEVEL eNextLevel);
	virtual void Tick(_float TimeDelta);
	virtual HRESULT Render();
	virtual void Change_Level(void* pArg, _uint _iNextLevel) {}
	virtual HRESULT Complete_Condition() { return S_OK; }


private:
	LEVEL			m_eNextLevel = LEVEL_END;
	class CLoader*	m_pLoader = nullptr;

public:
	static CLevel_Loading* Create(LEVEL eNextLevel);
	virtual void Free() override;
};

END