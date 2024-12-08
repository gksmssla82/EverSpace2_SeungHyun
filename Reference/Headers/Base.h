#pragma once

#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
//protected:
//	CBase();
//	virtual ~CBase() = default;
//public:
//	unsigned long AddRef();
//	unsigned long Release();
//
//protected:
//	unsigned long		m_dwRefCnt = 0;
//
public:
	template<typename T>
	void	Set_WeakPtr(T** WeakPtr)
	{
		m_WeakList.push_back((CBase**)WeakPtr);

		if (m_iLastWeakCnt + 200 <= m_WeakList.size())
		{
			printf("Warning! the instance had too many weakptrs\t %s : \t%d\n", typeid(*this).name(), m_WeakList.size());
			m_iLastWeakCnt += 200;
		}

		

	}

	//���� �������� �ν��Ͻ��� �������� ���� �����Ǵ� ��� ��� ������ ����� �մϴ�.
	//��) ���Ͱ� �÷��̾ �����Ѵ�. ���Ͱ� ���� ������ ��쿣 �÷��̾� ���� �����͸� ��� ������.
	template<typename T>
	void	Return_WeakPtr(T** WeakPtr)
	{
		m_WeakList.remove((CBase**)WeakPtr);
	}

	virtual void Free();

public:
	//�ش� ��ü�� Ȱ��ȭ ���¸� �ٲߴϴ�. Ȱ��ȭ ���°� ���Ѵٸ� OnEnable / OnDisable �̺�Ʈ �Լ��� ȣ���մϴ�.
	void Set_Enable(_bool _Enable, void* _Arg = nullptr);
	bool Get_Enable();

public:
	//��ü�� ���°� Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
	virtual void OnEnable(void* _Arg = nullptr) {};

	//��ü�� ���°� ��Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
	virtual void OnDisable() {};

	virtual void OnTimerEvent(const _uint _iEventIndex) {};

private:
	list<CBase**>	m_WeakList;
	_bool			m_bEnable = true;
	_uint			m_iLastWeakCnt = 0;
};

END

