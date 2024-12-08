#include "..\Public\Base.h"



//CBase::CBase()
//{
//	int a = 10;
//}
//
//unsigned long CBase::AddRef()
//{
//	return ++m_dwRefCnt;	
//}
//
//unsigned long CBase::Release()
//{
//	if (0 == m_dwRefCnt)
//	{
//		Free();
//
//		delete this;
//
//		return 0;
//	}
//	else
//	{
//		return m_dwRefCnt--;
//	}
//
//
//	
//}
//
void CBase::Free()
{
	for (auto& elem : m_WeakList)
	{
		if(elem)
			(*elem) = nullptr;
	}

	m_WeakList.clear();
}

void CBase::Set_Enable(_bool _Enable, void* _Arg)
{
	if (_Enable == m_bEnable)
		return;

	m_bEnable = _Enable;
	m_bEnable ? OnEnable(_Arg) : OnDisable();
}

bool CBase::Get_Enable()
{
	return m_bEnable;
}
