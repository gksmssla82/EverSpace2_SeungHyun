#pragma once
#include "Base.h"

BEGIN(Engine)

class CTimer final :
    public CBase
{
private:
	CTimer();
	virtual ~CTimer() = default;

public:
	HRESULT	Initialize();
	_float Compute_Timer(void);

private:
	LARGE_INTEGER		m_CurrentTime;
	LARGE_INTEGER		m_OldTime;
	LARGE_INTEGER		m_OriginTime;

	LARGE_INTEGER		m_CpuTick;

	float				m_fTimeDelta;

public:
	static CTimer* Create();
	virtual void Free() override;


};

END