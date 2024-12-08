#include "Graphic_Device.h"
#include "Font.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CGraphic_Device)

CGraphic_Device::CGraphic_Device()
	: m_p3D(nullptr), m_pDevice(nullptr)
{

}

HRESULT CGraphic_Device::InitDevice(const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut)
{
	m_GraphicDesc = GraphicDesc;

	// HRESULT : �Լ��� ȣ�� ���� ������ ���� ����� ��� �������
	// ������ �ִ� ���·� ����� ��� �������� ��ȯ��Ű�� ���� �ڷ���

	// (�׸���)��ġ �ʱ�ȭ : ��ġ�� ������ ��ü ����(m_p3D) -> ��ġ ���� -> ��ġ ���� ��ü ����(m_pDevice)
	
	// Direct3DCreate9 : LPDIRECT3D9 ��ü�� SDK ������ �°� �����ϴ� �Լ�
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9			DeviceCaps;
	// 3D�������� �ʿ��� �⺻���� ������ �����ϴ��� �����Ͽ� ���� ������ �����ϱ� ���� ����ü
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	// FAILED ��ũ�� :hresult ��ȯŸ���� ������ ��� true
	// GetDeviceCaps : ��ġ ������ ����
	// D3DADAPTER_DEFAULT :������ �������� �⺻ �׷��� ī�带 �ǹ�
	// D3DDEVTYPE_HAL : HAL(hardware abstraction layer)�� ����Ǿ� �ִ� ��ġ�� �ʼ� ������ ������ ���� �־��ִ� ���ڰ�
	if (FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		MSG_BOX("GetDeviceCaps Failed"); // mfc������ ��밡���� �޼��� �ڽ� �Լ�
		return E_FAIL;
	}

	DWORD	vp = 0;		// ���ؽ� ���μ��� : ���� ���� + ���� ó��

	// HAL �� ���� ������ ��ġ�� �ϵ���� ���ؽ� ���μ����� �����ϴ��� �Ǵ�
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;		// �׷��� ī��

	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;		// ���� ����(CPU)

	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	SetParameters(GraphicDesc, d3dpp);

	if (FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GraphicDesc.hWnd, vp, &d3dpp, &m_pDevice)))
	{
		MSG_BOX("CreateDevice Failed"); // mfc������ ��밡���� �޼��� �ڽ� �Լ�
		return E_FAIL;
	}

	*ppOut = m_pDevice;

	//Safe_AddRef(m_pDevice);

	D3DXCreateSprite(m_pDevice, &m_pSprite);
	D3DXCreateFont(m_pDevice, 20, 0, FW_BOLD, 0,
		FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("���"),
		&m_pFont);

	GAMEINSTANCE->Add_Timer(99);

	

	return S_OK;
}

void CGraphic_Device::SetParameters(const GRAPHICDESC& GraphicDesc, D3DPRESENT_PARAMETERS& d3dpp)
{
	d3dpp.BackBufferWidth = GraphicDesc.iWinCX;
	d3dpp.BackBufferHeight = GraphicDesc.iWinCY;

	// �ĸ� ������ �ȼ� ���� , 32��Ʈ ���� ���
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	// �ĸ� ������ ����
	d3dpp.BackBufferCount = 1;

	// �ȼ��� �� �߻��ϴ� ��������� ������ �ε巴�� �����ϴ� ���(��Ƽ �������)�� �����ϴ��� ���θ� ���� ���ڰ�
	// �ڿ������� ������ ������ �������ϰ� �߻��ϱ� ������ ������� ���� ����
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	// ���簡 �ƴ� ��ü ����� ���� �׸���� ����⸦ �ϰԲ� ������ش�.

	// D3DSWAPEFFECT_DISCARD : ���� ü�� ���
	// D3DSWAPEFFECT_FLIP : ���� �ϳ��� �������鼭 ����ϴ� ���
	// D3DSWAPEFFECT_COPY : ���� ���۸��� �����ϰ� �����Ͽ� ����ϴ� ���

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GraphicDesc.hWnd;	// ��ġ�� ����� ������ �ڵ� ����

	d3dpp.Windowed = GraphicDesc.isWindowMode; // TRUE�� ��� â���, FALSE ��ü ȭ�� ���

	// ���ٽ� ���� : �ݻ�� ���� ��ü�� ǥ���ϴ� ����
	// ���� ����(Z����) : ��ü�� ���� ���� �����Ͽ� ���ٰ��� ǥ���ϱ� ���� ����
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	// ��üȭ�� �ÿ� ����ϴ� ���ڰ�
	// â ��� �� ��� ��ġ�� �ƴ� �ü���� ������� ������
	// ��ü ȭ������ ���� �� ����� ������� ���� ����
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	// ������� �ÿ��� ���� ����
	// D3DPRESENT_INTERVAL_IMMEDIATE : ��� �ÿ�
	// D3DPRESENT_INTERVAL_DEFAULT : ������ ������ DIRECTX �˾Ƽ� ����, ���� ����� ������� ����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

void CGraphic_Device::Render_Begin(void)
{
	// ������ ���� : �ĸ� ���۸� ���� ����(�����)-> �ĸ� ���ۿ� �׸���-> �ĸ���ۿ� ����� ���ǽ��� ������ۿ� ����� ���ǽ��� ��ü�Ͽ� ����Ѵ�.

	// 1���� : ������� �ϴ� ��Ʈ�� ����
	// 2���� : ������� �ϴ� ��Ʈ �迭�� �̸�(nullptr�� ��� ��ü ȭ�� ������ �ش��ϴ� ���Ͷ�� �ǹ�)

	//m_pDevice->Clear(0,
	//	nullptr,
	//	D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
	//	D3DCOLOR_ARGB(255, 0, 0, 255),	// ����� ����
	//	1.f, // z������ �ʱ�ȭ ��
	//	0);	 // ���ٽ� ������ �ʱ�ȭ ��

	//���⼭���� �ĸ���ۿ� �׸��� ������ �˸���.
	m_pDevice->BeginScene();


	//D3DXMATRIX world;
	//
	//D3DXMatrixTranslation(&world, 100, 100, 0);
	//
	//m_pSprite->SetTransform(&world);

	
}

void CGraphic_Device::Render_Sprite()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);//2D

	if (!m_Text.empty())
	{
		_float fTextDeltaTime = GAMEINSTANCE->Compute_Timer(99);

		for (auto& iter : m_Text)
		{
			if (iter->Get_CountTime() < 0.f) // �ð���ŭ ���Ҵ� �Ҹ�
			{
				int i = 0;
			}
			else
			{
				m_pFont->DrawText(m_pSprite, iter->Get_Font().szBuff, -1, &iter->Get_Font().rcTemp, 0,
					iter->Get_Font().color);//0xFFFF0000);
				iter->Minus_CountTime(fTextDeltaTime);
			}

		}
	}



	m_pSprite->End();

}

void CGraphic_Device::Render_End(HWND hWnd)
{

	m_pDevice->EndScene();

	// �ĸ���ۿ� ����Ǿ� �ִ� ���ǽ��� ���� ���ۿ� ����� ���ǽ��� ��ȯ�ϴ� ����
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);
	// 1,2���� : ����ü�� ����� D3DSWAPEFFECT_COPY�� �ƴ� �̻� NULL
	// 3���� : ��� ��� ������ �ڵ�, �⺻ nullptr�� ��� d3dpp.hDeviceWindow�� ����
	// 4���� :  ����ü�� ����� D3DSWAPEFFECT_COPY�� �ƴ� �̻� NULL
}

HRESULT CGraphic_Device::Add_Text(TEXTINFO Info, float CountTime)
{
	

	for (auto& elem : m_Text)
	{
		if (elem->Get_CountTime() < 0.f)
		{
			elem->Set_Param(&Info, CountTime);
			return S_OK;
		}
	}

	CFont* Font = CFont::Create(&Info, CountTime);

	if (nullptr != Font)
		m_Text.push_back(Font);

	return S_OK;
}

D3DLIGHT9 CGraphic_Device::InitLight(D3DLIGHTTYPE type)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	D3DXCOLOR color = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);       // white
	D3DXVECTOR3 position = D3DXVECTOR3(0.f, 0.f, 5.f);
	D3DXVECTOR3 direction = D3DXVECTOR3(-1.f, -1.f, -1.f);

	light.Type = type;

	light.Ambient = color * 0.01f;
	light.Diffuse = color;
	light.Specular = color * 0.6f;

	light.Position = position;
	light.Direction = direction;

	light.Range = 8.0f;
	light.Falloff = 4.0f;

	light.Attenuation0 = 0.2f;
	light.Attenuation1 = 0.4f;
	light.Attenuation2 = 0.8f;

	light.Theta = 1.f;
	light.Phi = 2.f;

	return light;
}

bool CGraphic_Device::SetupEffect(const _tchar* shaderFilename, ID3DXEffect** effect)
{
	ID3DXBuffer* errorBuffer = 0;

	HRESULT hr = D3DXCreateEffectFromFile(
		m_pDevice,
		shaderFilename,
		0,
		0,
		D3DXSHADER_DEBUG,
		0,
		effect,
		&errorBuffer
	);

	if (errorBuffer) {
		assert(false);
	}

	if (FAILED(hr)) {
		assert(false);
	}

	return true;
}

bool CGraphic_Device::SetupTexture(IDirect3DTexture9** texture, IDirect3DSurface9** surface)
{
	HRESULT hr = D3DXCreateTexture(
		m_pDevice,
		m_GraphicDesc.iWinCX,
		m_GraphicDesc.iWinCY,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		texture
	);

	if (FAILED(hr)) {
		assert(false);
	}

	(*texture)->GetSurfaceLevel(0, surface);

	return true;	
}




void CGraphic_Device::Free()
{
	for (auto& iter : m_Text)
	{
		Safe_Release(iter);
	}
	m_Text.clear();

	m_pFont->Release();
	m_pSprite->Release();
	m_pDevice->Release();
	m_p3D->Release();

	//if (0 != Safe_Release(m_pFont))
	//	MSG_BOX("Failed To Release : Font");

	//if (0 != Safe_Release(m_pSprite))
	//	MSG_BOX("Failed To Release : Sprite");
	//
	//if (0 != Safe_Release(m_pDevice))
	//	MSG_BOX("Failed To Release : Device");

	//if (0 != Safe_Release(m_p3D))
	//	MSG_BOX("Failed To Release : SDK");

	delete this;
}
