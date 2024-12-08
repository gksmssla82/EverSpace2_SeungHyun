//#pragma once
//#include "Base.h"
//
//BEGIN(Engine)
//
//class CTime_Manager final :
//    public CBase
//{
//    DECLARE_SINGLETON(CTime_Manager)
//private:
//    CTime_Manager() = default;
//    virtual ~CTime_Manager() = default;
//
//public:
//	HRESULT Add_Timer(const _tchar* pTimerTag);
//	_float Compute_Timer(const _tchar* pTimerTag);
//
//private:
//	map<const _tchar*, class CTimer*>			m_Timers;
//	typedef map<const _tchar*, class CTimer*>	TIMERS;
//
//private:
//	class CTimer* Find_Timer(const _tchar* pTimerTag);
//
//public:
//	virtual void Free();
//
//};
//
//END