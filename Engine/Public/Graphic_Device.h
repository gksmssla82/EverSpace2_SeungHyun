#pragma once

#include "Base.h"

BEGIN(Engine)


class CGraphic_Device final : public CBase
{
	DECLARE_SINGLETON(CGraphic_Device)

private:
	CGraphic_Device();
	virtual ~CGraphic_Device() = default;
	// com ��ü : ������ ��� �Ծ��� ���� �ϵ��� �����Ͽ� ���� ����� �����ϴ� ��ü

public:
	LPDIRECT3DDEVICE9*			Get_Device(void) { return &m_pDevice; }
public:
	HRESULT		InitDevice(const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut);	
	void		Render_Begin(void);
	void		Render_Sprite();
	void		Render_End(HWND hWnd = NULL);

public:
	HRESULT		Add_Text(TEXTINFO Info, float CountTime);
	D3DLIGHT9	InitLight(D3DLIGHTTYPE type);
	bool SetupEffect(const _tchar* shaderFilename, ID3DXEffect** effect);
	bool SetupTexture(IDirect3DTexture9** texture, IDirect3DSurface9** surface);

	

public:


private:
	LPDIRECT3D9				m_p3D;
	LPDIRECT3DDEVICE9		m_pDevice;

	LPD3DXFONT				m_pFont = nullptr;

	list<class CFont*>			m_Text;

	ID3DXSprite*			m_pSprite = nullptr;

	GRAPHICDESC				m_GraphicDesc;

private: /* For Light */

private:
	void		SetParameters(const GRAPHICDESC& GraphicDesc, D3DPRESENT_PARAMETERS& d3dpp);

public:
	virtual void Free();
};

END