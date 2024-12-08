#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CMesh_Cube;
END

BEGIN(Client)

class CEnemySpace_RightBody final :public CGameObject
{
private:
    CEnemySpace_RightBody() = default;
    CEnemySpace_RightBody(const CEnemySpace_RightBody& Prototype);
    virtual ~CEnemySpace_RightBody() = default;

public:
    // CGameObject��(��) ���� ��ӵ�
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render() override;

private:
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CMesh_Cube* m_pMeshCom = nullptr;

public:
    // CGameObject��(��) ���� ��ӵ�
    static CEnemySpace_RightBody* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END

