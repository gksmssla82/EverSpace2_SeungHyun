#pragma once
#include "Base.h"

BEGIN(Engine)

class CTransform;
class CCamera;
class CGameObject;

class CCamera_Manager :
    public CBase
{
    DECLARE_SINGLETON(CCamera_Manager)

private:
    CCamera_Manager() = default;
    virtual ~CCamera_Manager() = default;

public:
    void Register_Camera(const _tchar* _CameraTag, CCamera* _CameraCom);
    void Set_Target(CTransform* _Target = nullptr, const _tchar* _CameraTag = TEXT(""));
    CCamera* Get_Camera(const _tchar* _CameraTag = TEXT(""));
    void Set_Current_Camera(const _tchar* _CameraTag = TEXT(""));
    void Add_Shaking(_float _fOffset, _float _fInclination);

    
    void Update_MovingCam()//����� ī�޶�� �ٲ�
    {
        m_pTempCam = m_pCurrentCam;
        Set_Current_Camera(TEXT("Moving"));
    }

    void Swap_Camera()//������ ��� ������ ���� �ٽ� ���� ī�޶�� ���ƿ�
    {
        m_pCurrentCam = m_pTempCam;
    }

    void Set_MovingCam(CGameObject* _pMovingCam)//����� ī�޶� ������ ī�޶� �Ŵ����� ��������
    {
        m_pMovingCam = _pMovingCam;
    }
    CGameObject* Get_MovingCam()//���� ����� ī�޶�� ���� ������Ʈ ��ȯ
    {
        return m_pMovingCam;
    }

public:
    void    Switch_Camera(const _tchar* _CameraTag, _float _fTime);
    void    Switch_Player(CTransform* _pCurCamera, CTransform* _pNextCamera, const _tchar* _NextCameraTag, _float fTime);


public:
    void Tick(_float fTimeDelta);
    void LateTick(_float fTimeDelta);

private:
    void Clear_Empty_Camera();
   
private:
    map<const _tchar*, class CCamera*>	m_Cams;

    CGameObject* m_pMovingCam = nullptr;
    CGameObject* m_pFreeCam = nullptr;//Free Camera

    CCamera* m_pCurrentCam = nullptr;
    CCamera* m_pTempCam = nullptr;

 
public:
    virtual void Free() override;
};

END