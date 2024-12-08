#pragma once

/* ȭ�鿡 �׷������� ��ü���� �׸��� ������� ��Ƽ� �����ϳ�.  */
/* ������ �ִ� ��ü���� �����Լ��� ȣ�����ֳ�. */

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CRenderer final : public CComponent
{
private:
	CRenderer();
	CRenderer(const CRenderer& Prototype);
	virtual ~CRenderer() = default;
	 
public:
	HRESULT Add_RenderGroup(RENDERGROUP	eGroup, class CGameObject* pGameObject);
	HRESULT Set_Textures_From_Key(const _tchar* _Str_Key, MEMORY_TYPE _eType = MEMORY_TYPE::MEMORY_END);
	HRESULT Bind_Texture(_uint _iIndex);
	HRESULT UnBind_Texture();
	LPDIRECT3DBASETEXTURE9 Get_Texture(_uint _iIndex);

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

public:

private:
	vector<LPDIRECT3DBASETEXTURE9>* m_ppTextures = nullptr;

public:
	static CRenderer* Create();
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END