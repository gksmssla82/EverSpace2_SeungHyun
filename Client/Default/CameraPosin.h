#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
//class CVIBuffer_Rect;
class CMesh_Cube;
class CTransform;
END

BEGIN(Client)

class CCameraPosin final : public CGameObject
{
private:
    explicit CCameraPosin();
    explicit CCameraPosin(const CCameraPosin& Prototype);
    virtual ~CCameraPosin() = default;

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
   // CVIBuffer_Rect* m_pVIBufferCom = nullptr;
    CMesh_Cube* m_pMeshCom = nullptr;

    CTransform* m_pCameraTransformCom = nullptr;

public:
    void Link_CameraTransfrom(CTransform* pTransform);

private:
    HRESULT SetUp_Components();
    void    LookAt_CamTPS();

public:
    // CGameObject��(��) ���� ��ӵ�
    static CCameraPosin* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END
