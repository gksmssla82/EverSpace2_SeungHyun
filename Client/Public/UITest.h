#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
class CMesh_Test;
class CMesh_SongShip;
END

BEGIN(Client)

class CUITest final : public CGameObject
{
private:
    explicit CUITest();
    explicit CUITest(const CUITest& Prototype);
    virtual ~CUITest() = default;

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
    CVIBuffer_Rect* m_pVIBufferCom = nullptr;

private:
    HRESULT SetUp_Components();

public:
    static CUITest* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END

