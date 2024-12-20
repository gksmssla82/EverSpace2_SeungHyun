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

	// HRESULT : 함수가 호출 이후 문제가 없이 종료될 경우 양수값을
	// 문제가 있는 상태로 종료될 경우 음수값을 반환시키기 위한 자료형

	// (그리기)장치 초기화 : 장치를 조사할 객체 생성(m_p3D) -> 장치 조사 -> 장치 제어 객체 생성(m_pDevice)
	
	// Direct3DCreate9 : LPDIRECT3D9 객체를 SDK 버전에 맞게 생성하는 함수
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9			DeviceCaps;
	// 3D렌더링에 필요한 기본적인 연산을 지원하는지 조사하여 각종 정보를 보관하기 위한 구조체
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	// FAILED 매크로 :hresult 반환타입이 음수일 경우 true
	// GetDeviceCaps : 장치 성능을 조사
	// D3DADAPTER_DEFAULT :정보를 얻으려는 기본 그래픽 카드를 의미
	// D3DDEVTYPE_HAL : HAL(hardware abstraction layer)에 저장되어 있는 장치의 필수 정보를 얻어오기 위해 넣어주는 인자값
	if (FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		MSG_BOX("GetDeviceCaps Failed"); // mfc에서만 사용가능한 메세지 박스 함수
		return E_FAIL;
	}

	DWORD	vp = 0;		// 버텍스 프로세싱 : 정점 연산 + 조명 처리

	// HAL 을 통해 조사한 장치가 하드웨어 버텍스 프로세싱을 지원하는지 판단
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;		// 그래픽 카드

	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;		// 직접 연산(CPU)

	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	SetParameters(GraphicDesc, d3dpp);

	if (FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GraphicDesc.hWnd, vp, &d3dpp, &m_pDevice)))
	{
		MSG_BOX("CreateDevice Failed"); // mfc에서만 사용가능한 메세지 박스 함수
		return E_FAIL;
	}

	*ppOut = m_pDevice;

	//Safe_AddRef(m_pDevice);

	D3DXCreateSprite(m_pDevice, &m_pSprite);
	D3DXCreateFont(m_pDevice, 20, 0, FW_BOLD, 0,
		FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("고딕"),
		&m_pFont);

	GAMEINSTANCE->Add_Timer(99);

	

	return S_OK;
}

void CGraphic_Device::SetParameters(const GRAPHICDESC& GraphicDesc, D3DPRESENT_PARAMETERS& d3dpp)
{
	d3dpp.BackBufferWidth = GraphicDesc.iWinCX;
	d3dpp.BackBufferHeight = GraphicDesc.iWinCY;

	// 후면 버퍼의 픽셀 포맷 , 32비트 포맷 사용
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	// 후면 버퍼의 개수
	d3dpp.BackBufferCount = 1;

	// 픽셀이 모여 발생하는 계단현상을 뭉개서 부드럽게 연출하는 기법(안티 엘리어싱)을 지원하는지 여부를 묻는 인자값
	// 자연스럽게 연출은 되지만 성능저하가 발생하기 때문에 사용하지 않을 예정
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	// 복사가 아닌 교체 방식을 통해 그리기와 지우기를 하게끔 만들어준다.

	// D3DSWAPEFFECT_DISCARD : 스왑 체인 방식
	// D3DSWAPEFFECT_FLIP : 버퍼 하나를 뒤집으면서 사용하는 방식
	// D3DSWAPEFFECT_COPY : 더블 버퍼링과 유사하게 복사하여 사용하는 방식

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GraphicDesc.hWnd;	// 장치를 사용할 윈도우 핸들 설정

	d3dpp.Windowed = GraphicDesc.isWindowMode; // TRUE인 경우 창모드, FALSE 전체 화면 모드

	// 스텐실 버퍼 : 반사와 같은 물체를 표현하는 버퍼
	// 깊이 버퍼(Z버퍼) : 물체의 깊이 값을 저장하여 원근감을 표현하기 위한 버퍼
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	// 전체화면 시에 사용하는 인자값
	// 창 모드 일 경우 장치가 아닌 운영체제가 재생률을 관리함
	// 전체 화면으로 변경 시 모니터 재생율에 대한 설정
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	// 재생율과 시연의 간격 설정
	// D3DPRESENT_INTERVAL_IMMEDIATE : 즉시 시연
	// D3DPRESENT_INTERVAL_DEFAULT : 적절한 간격을 DIRECTX 알아서 결정, 보통 모니터 재생율을 따라감
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

void CGraphic_Device::Render_Begin(void)
{
	// 렌더링 과정 : 후면 버퍼를 먼저 비운다(지운다)-> 후면 버퍼에 그린다-> 후면버퍼에 연결된 서피스를 전면버퍼에 연결된 서피스와 교체하여 출력한다.

	// 1인자 : 지우고자 하는 렉트의 개수
	// 2인자 : 지우고자 하는 렉트 배열의 이름(nullptr인 경우 전체 화면 영역에 해당하는 렉터라는 의미)

	//m_pDevice->Clear(0,
	//	nullptr,
	//	D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
	//	D3DCOLOR_ARGB(255, 0, 0, 255),	// 백버퍼 색상
	//	1.f, // z버퍼의 초기화 값
	//	0);	 // 스텐실 버퍼의 초기화 값

	//여기서부터 후면버퍼에 그리기 시점을 알린다.
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
			if (iter->Get_CountTime() < 0.f) // 시간만큼 돌았단 소리
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

	// 후면버퍼에 연결되어 있는 서피스와 전면 버퍼에 연결된 서피스를 교환하는 과정
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);
	// 1,2인자 : 스왑체인 기법이 D3DSWAPEFFECT_COPY가 아닌 이상 NULL
	// 3인자 : 출력 대상 윈도우 핸들, 기본 nullptr인 경우 d3dpp.hDeviceWindow을 참조
	// 4인자 :  스왑체인 기법이 D3DSWAPEFFECT_COPY가 아닌 이상 NULL
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
