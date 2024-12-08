#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CLight abstract :
    public CComponent
{
protected:
    CLight() = default;
    CLight(const CLight & Prototype);
    virtual ~CLight() = default;

public:
    virtual void    Bind_ConstBuffer() PURE;
    virtual void    DrawLight() PURE;
    ID3DXEffect**   Get_Effect();
    //������ ������ ����
    void            Set_Margin_Position(const _float3& _Position);
    //������ �ش� ������ �ٶ󺻴�. (Point ����)
    void            Set_LooK_Dir(const _float3& _Look);
    //������ ��� 0~2 ������ float ��
    void            Set_LightColorScale(const _float& _ColorScale);
    //������ �� RGB 0~1������ float ��
    void            Set_LightColor(const D3DXCOLOR& _Color);
    //������ ����
    void            Set_LightRange(const _float& _Range);
    //���� ����ü�� �Ű������� ���� �����Ѵ�.
    void            Set_D3DLight(const _D3DLIGHT9& _D3DLight);
    void            Set_Light_Variables(D3DXCOLOR _Color,_float _lightambient, _float _lightdiffuse, _float _lightspecular, _float3 _lightmarginposition,
        _float3 _lightdirection, _float _lightrange = 0.f, _float _lightattenuation0 = 0.f, _float _lightattenuation1 = 0.f, _float _lightattenuation2 = 0.f,
        _float _lightfalloff = 0.f, _float _lighttheta = 0.f, _float _lightphi = 0.f);
public:
    void            Set_Preset_PowLight();
    void            Set_Preset_SunLight();
    void            Set_Preset_ItemLight();


protected:
    ID3DXEffect**   m_ppLightEffect = nullptr;
    D3DLIGHT9       m_D3DLight;
    _float3         m_Margin_Position = _float3(0.f, 0.f, 0.f);
    _float          m_fColorScale = 1.f;
    _float          m_fLifeTime = 300.f;
    D3DXCOLOR       m_Color = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

};

END