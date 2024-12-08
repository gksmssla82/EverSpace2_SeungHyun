#pragma once
#include "Client_Defines.h"
#include "Monster.h"

BEGIN(Engine)
class CMesh_SongShip;

END

BEGIN(Client)


class CSunSpaceBoss_Body final : public CMonster
{
private:
    CSunSpaceBoss_Body();
    CSunSpaceBoss_Body(const CSunSpaceBoss_Body& Prototype);
    virtual ~CSunSpaceBoss_Body() = default;

public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg)override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
    virtual HRESULT Render() override;

private:
    void Spawn_Monster(); // ���� random spawn (10��������?) ������ġ ����.
    void Rock_throw(_float fTimeDelta); // ���� random spawn (10������?) ������ġ. ���� ��ó.
    void EMP(); // �����ð� ���� �Ұ��ɻ��� �����

    void LookAtPlayer();
     

private:
    CMesh_SongShip* m_pMeshCom = nullptr;

private:
    _bool m_bSkill = false;
    _float m_fSkillTime = 3.f;
    _float m_fRadian = 0.f;

private:
    _float  m_fMonsterSpawn = 20.f;
    _float  m_fRockSpawn = 5.f;
   list<pair<_float, CGameObject*>> m_RockObjectList;

protected:
    virtual void SetUp_Components_For_Child();

public:
    virtual void On_Change_Controller(const CONTROLLER& _IsAI);

public: /* For Event Function */
    virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
    virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
    virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

public:
    static CSunSpaceBoss_Body* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END