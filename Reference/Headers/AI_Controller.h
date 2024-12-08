#pragma once
#include "Controller.h"

BEGIN(Engine)

class CState_Move;
class CTransform;
class CTargeting;

class ENGINE_DLL CAI_Controller final : public CController
{
public:
	CAI_Controller();
	CAI_Controller(const CAI_Controller& Prototype);
	virtual ~CAI_Controller() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);

public:
	//�ش� ��Ʈ�ѷ��� ����� �� �ִ� State ����Ʈ�� �־��ش�. �������� �ش� ����Ʈ ������ �����ϰ� �ൿ�Ѵ�.
	void Set_UsableStates(const vector<STATE>& _eUsableStates);
	//���� ��� ť�� �տ� ���¸� �����Ѵ�. 
	//_BehaviorTime�� ���� ������� ����Ʈ �ൿ �ð��� ����Ѵ�.
	//_IsClearCommand�� ������ ��ϵǾ� �ִ� Ŀ�ǵ���� ������ �� ���δ�.
	void Push_Front_Command(STATE _eStates, _float _BehaviorTime = -1.f, _bool _IsClearCommand = false);

public: //�ൿ ������
	vector<STATE> Get_States_Preset_AI_Default();
	vector<STATE> Get_States_Preset_ROLLER_Default();

public:
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);

private:
	CState_Move* m_pMyState_Move = nullptr;
	CTransform* m_pMyTransform = nullptr;
	CTargeting* m_pMyTargeting = nullptr;

private:
	STATE Command_MoveTarget();
	STATE Command_Move();
	STATE Command_Attack();

protected:
	list<pair<STATE, _float>> m_CommandQueue;
	vector<STATE> m_eUsableStates[9];

	_float m_fBehaviorTime = 3.f;

public:
	//��ü�� ���°� Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
	virtual void OnEnable(void* pArg = nullptr) override;

	//��ü�� ���°� ��Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
	virtual void OnDisable() override;

private:

public:
	static CAI_Controller* Create();
	virtual CController* Clone(void* pArg) override;
	virtual void Free() override;
};

END