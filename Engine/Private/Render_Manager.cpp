#include "..\Public\Render_Manager.h"
#include "GameObject.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CRender_Manager)

CRender_Manager::CRender_Manager()
{
}

HRESULT CRender_Manager::Initialize()
{
	if (!SetupTexture(&normalTex, &normalSurface)) {
		return E_FAIL;
	}
	if (!SetupTexture(&depthTex, &depthSurface)) {
		return E_FAIL;
	}
	if (!SetupTexture(&diffuseTex, &diffuseSurface)) {
		return E_FAIL;
	}
	if (!SetupTexture(&specularTex, &specularSurface)) {
		return E_FAIL;
	}
	if (!SetupTexture(&stashTex, &stashSurface)) {
		return E_FAIL;
	}
	if (!SetupTexture(&originTex, &TemporaryRenderTarget)) {
		return E_FAIL;
	}
	if (!SetupTexture(&ExtractBloomTex, &ExtractBloomSurface)) {
		return E_FAIL;
	}
	if (!SetupTexture(&BloomTex, &BloomSurface)) {
		return E_FAIL;
	}


	m_GraphicDesc = GAMEINSTANCE->Get_Graphic_Desc();

	return S_OK;
}

HRESULT CRender_Manager::Add_RenderGroup(RENDERGROUP eGroup, CGameObject* pGameObject)
{
	if ((_uint)eGroup >= (_uint)RENDERGROUP::RENDER_END ||
		nullptr == pGameObject)
		return E_FAIL;

	m_RenderObjects[(_uint)eGroup].push_back(pGameObject);
	pGameObject->Set_WeakPtr(&m_RenderObjects[(_uint)eGroup].back());

	//Safe_AddRef(pGameObject);

	return S_OK;
}

HRESULT CRender_Manager::Add_Light(CLight* pLight)
{

	m_LightComs.push_back(pLight);
	pLight->Set_WeakPtr(&m_LightComs.back());

	return S_OK;
}

HRESULT CRender_Manager::Draw_RenderGroup()
{
	DEVICE->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);

	

	//Priority_Pipeline();
	Deferred_Pipeline();

	GAMEINSTANCE->Render_Begin();
	//GAMEINSTANCE->Render_Begin();
	Foward_Pipeline();
	GAMEINSTANCE->Render_Engine();
	GAMEINSTANCE->Render_End(GAMEINSTANCE->Get_Window_Handle());

	//DEVICE->EndScene();


	return S_OK;
}

void	CRender_Manager::Add_FadeOffSet()//fade_In;
{

	fFadeOutOffset += 2.f * GAMEINSTANCE->Get_UnScaledTimeDelta();
	if (fFadeOutOffset > 1.f)
		fFadeOutOffset = 1.f;
}

void	CRender_Manager::Sub_FadeOffSet()//fade_Out
{

	fFadeOutOffset -= 1.5f * GAMEINSTANCE->Get_UnScaledTimeDelta();
	if (0.f > fFadeOutOffset)
		fFadeOutOffset = 0.f;
}



void CRender_Manager::Priority_Pipeline()
{
	DEVICE->BeginScene();

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);

	CCamera* pCamera = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA);

	if (pCamera)
		pCamera->Bind_PipeLine();


	for (auto iter = m_RenderObjects[(_uint)RENDERGROUP::RENDER_PRIORITY].begin(); iter != m_RenderObjects[(_uint)RENDERGROUP::RENDER_PRIORITY].end();)
	{
		if ((*iter))
		{
			(*iter)->Render_Begin();
 			(*iter)->Render();
			(*iter)->Return_WeakPtr(&(*iter));
		}

		iter = m_RenderObjects[(_uint)RENDERGROUP::RENDER_PRIORITY].erase(iter);
	}

	DEVICE->EndScene();
}

void CRender_Manager::Deferred_Pipeline()
{

	GRAPHICDESC Desc = GAMEINSTANCE->Get_Graphic_Desc();

	ID3DXEffect** G_Buffer = GAMEINSTANCE->Get_Shader_From_Key(TEXT("GBuffer"));
	
	if (!G_Buffer)
	{
		//GBuffer ���̴��� ã�� �� ����.
		return;
	}

	if (!GAMEINSTANCE->Get_Camera(CURRENT_CAMERA))
	{
		return;
	}


	SetMRT();
	DEVICE->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);
	DEVICE->BeginScene();
	//DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, true);

	
	_float ViewAspect = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA)->Get_Aspect();
	_float Fov = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA)->Get_Fov();
	_float TanHalfFov = tanf(Fov / 2.f);
	_float ScreenSize[2]{(float)Desc.iWinCX, (float)Desc.iWinCY};

	D3DXHANDLE worldHandle = (*G_Buffer)->GetParameterByName(0, "world");
	D3DXHANDLE viewHandle = (*G_Buffer)->GetParameterByName(0, "view");
	D3DXHANDLE projHandle = (*G_Buffer)->GetParameterByName(0, "proj");

	_float4x4 view, proj, world;
	DEVICE->GetTransform(D3DTS_VIEW, &view);
	DEVICE->GetTransform(D3DTS_PROJECTION, &proj);
	D3DXMatrixIdentity(&world);

	(*G_Buffer)->SetMatrix(viewHandle, &view);
	(*G_Buffer)->SetMatrix(projHandle, &proj);

	D3DXHANDLE hTech = 0;
	UINT numPasses = 0;

	hTech = (*G_Buffer)->GetTechniqueByName("gbufferskybox");
	(*G_Buffer)->SetTechnique(hTech);

	for (auto iter = m_RenderObjects[(_uint)RENDERGROUP::RENDER_PRIORITY].begin(); iter != m_RenderObjects[(_uint)RENDERGROUP::RENDER_PRIORITY].end();)
	{
		if ((*iter))
		{
			(*iter)->Render_Begin(G_Buffer);

			DEVICE->GetTransform(D3DTS_WORLD, &world);

			(*G_Buffer)->SetMatrix(worldHandle, &world);

			(*G_Buffer)->Begin(&numPasses, 0);
			for (_uint i = 0; i < numPasses; i++)
			{
				(*G_Buffer)->BeginPass(i);

				(*iter)->Render();

				(*G_Buffer)->EndPass();
			}
			(*G_Buffer)->End();

			(*iter)->Return_WeakPtr(&(*iter));
		}

		iter = m_RenderObjects[(_uint)RENDERGROUP::RENDER_PRIORITY].erase(iter);
	}

	DEVICE->EndScene();

	DEVICE->BeginScene();

	hTech = (*G_Buffer)->GetTechniqueByName("gbuffer");
	(*G_Buffer)->SetTechnique(hTech);

	for (auto iter = m_RenderObjects[(_uint)RENDERGROUP::RENDER_DEFERRED].begin(); iter != m_RenderObjects[(_uint)RENDERGROUP::RENDER_DEFERRED].end();)
	{

		if ((*iter))
		{
			(*iter)->Render_Begin(G_Buffer);

			DEVICE->GetTransform(D3DTS_WORLD, &world);

			(*G_Buffer)->SetMatrix(worldHandle, &world);

			(*G_Buffer)->Begin(&numPasses, 0);
			for (_uint i = 0; i < numPasses; i++)
			{
				(*G_Buffer)->BeginPass(i);

				(*iter)->Render();

				(*G_Buffer)->EndPass();
			}
			(*G_Buffer)->End();

			(*iter)->Return_WeakPtr(&(*iter));
		}
		
		iter = m_RenderObjects[(_uint)RENDERGROUP::RENDER_DEFERRED].erase(iter);
	}

	DEVICE->EndScene();	

	/* deferred shading stage */
	ResumeOriginRender();
	DEVICE->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);
	DEVICE->ColorFill(stashSurface, NULL, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));

	DEVICE->BeginScene();

	for (auto iter = m_LightComs.begin(); iter != m_LightComs.end();)
	{
		if ((*iter))
		{
			
			ID3DXEffect** LightShader = (*iter)->Get_Effect();

			D3DXHANDLE screenSizeHandle = (*LightShader)->GetParameterByName(0, "screenSize");
			D3DXHANDLE viewAspectHandle = (*LightShader)->GetParameterByName(0, "viewAspect");
			D3DXHANDLE tanHalfFovHandle = (*LightShader)->GetParameterByName(0, "tanHalfFov");

			viewHandle = (*LightShader)->GetParameterByName(0, "view");
			(*LightShader)->SetMatrix(viewHandle, &view);

			(*LightShader)->SetFloatArray(screenSizeHandle, ScreenSize, 2);
			(*LightShader)->SetFloat(viewAspectHandle, ViewAspect);
			(*LightShader)->SetFloat(tanHalfFovHandle, TanHalfFov);

			D3DXHANDLE normalHandle = (*LightShader)->GetParameterByName(0, "normalTex");
			D3DXHANDLE depthHandle = (*LightShader)->GetParameterByName(0, "depthTex");
			D3DXHANDLE diffuseHandle = (*LightShader)->GetParameterByName(0, "diffuseTex");
			D3DXHANDLE specularHandle = (*LightShader)->GetParameterByName(0, "specularTex");
			D3DXHANDLE stashHandle = (*LightShader)->GetParameterByName(0, "stashTex");

			(*LightShader)->SetTexture(normalHandle, normalTex);
			(*LightShader)->SetTexture(depthHandle, depthTex);
			(*LightShader)->SetTexture(diffuseHandle, diffuseTex);
			(*LightShader)->SetTexture(specularHandle, specularTex);
			(*LightShader)->SetTexture(stashHandle, stashTex);

			(*iter)->Bind_ConstBuffer();

			numPasses = 0;
			(*LightShader)->Begin(&numPasses, 0);

			for (_uint i = 0; i < numPasses; i++)
			{
				(*LightShader)->BeginPass(i);

				(*iter)->DrawLight();

				(*LightShader)->EndPass();
			}
			(*LightShader)->End();

			DEVICE->StretchRect(originRenderTarget, NULL, stashSurface, NULL, D3DTEXF_NONE);

			(*iter)->Return_WeakPtr(&(*iter));
		}
		
		iter = m_LightComs.erase(iter);
	}

	DEVICE->EndScene();

	

	
}

void CRender_Manager::Foward_Pipeline()
{
	
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);

	CCamera* pCamera = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA);

	if(pCamera)
		pCamera->Bind_PipeLine();



	for (_uint i = (_uint)RENDERGROUP::RENDER_NONALPHABLEND; i < (_uint)RENDERGROUP::RENDER_UI+1; ++i)
	{
		if (i == (_uint)RENDERGROUP::RENDER_BLOOMABLE)
		{
			Bloom_Pipeline();
			continue;
		}


		if (i == (_uint)RENDERGROUP::RENDER_ALPHABLEND)
		{
			//����Ʈ�� nullptr�� �ִٸ� ��Ʈ ���� �������ش�.
			for (auto iter = m_RenderObjects[i].begin(); iter != m_RenderObjects[i].end();)
			{
				if (!(*iter))
				{
					iter = m_RenderObjects[i].erase(iter);
				}

				else
				{
					iter++;
				}
			}


			if (m_RenderObjects[i].size() > 1)
			{
				m_RenderObjects[i].sort([](CGameObject* pSour, CGameObject* pDest)
					{
						return pSour->Get_CamDistance() > pDest->Get_CamDistance();
					});
			}
		}


		for (auto iter = m_RenderObjects[i].begin(); iter != m_RenderObjects[i].end();)
		{
			if ((*iter))
			{
				(*iter)->Render_Begin();
				(*iter)->Render();
				(*iter)->Return_WeakPtr(&(*iter));
			}

			iter = m_RenderObjects[i].erase(iter);
		}

	}
	//D3DXSaveTextureToFile(TEXT("Normal.bmp"), D3DXIFF_BMP, normalTex, nullptr);
	//D3DXSaveTextureToFile(TEXT("Depth.bmp"), D3DXIFF_BMP, depthTex, nullptr);
	//D3DXSaveTextureToFile(TEXT("Diffuse.bmp"), D3DXIFF_BMP, diffuseTex, nullptr);
	//D3DXSaveTextureToFile(TEXT("ExtractBloom.bmp"), D3DXIFF_BMP, BloomTex, nullptr);
	
	

	DEVICE->StretchRect(originRenderTarget, nullptr, TemporaryRenderTarget, nullptr, D3DTEXF_LINEAR);

	Extract_Brightness();
	//�̾Ƴ� ������ ��ó��
	Apply_Blur(RENDERGROUP::RENDER_HDR, ExtractBloomTex);
	Apply_Bloom(RENDERGROUP::RENDER_BLOOM);
	//D3DXSaveTextureToFile(TEXT("HDRSurface.bmp"), D3DXIFF_BMP, BloomTex, nullptr);
	
	//DEVICE->StretchRect(originRenderTarget, nullptr, TemporaryRenderTarget, nullptr, D3DTEXF_LINEAR);

	//D3DXSaveTextureToFile(TEXT("OriginTex.bmp"), D3DXIFF_BMP, originTex, nullptr);

	
	//Apply_Blur(RENDERGROUP::RENDER_HDR, ExtractBloomTex);
	//Apply_Bloom(RENDERGROUP::RENDER_BLOOM);
	//D3DXSaveTextureToFile(TEXT("OriginTex_After_Brightness.bmp"), D3DXIFF_BMP, originTex, nullptr);
	//D3DXSaveTextureToFile(TEXT("ExtractBrightness.bmp"), D3DXIFF_BMP, ExtractBrightnessTex, nullptr);

	//Apply_Blur(RENDERGROUP::RENDER_HDR, ExtractBloomTex);
	//Apply_Bloom(RENDERGROUP::RENDER_BLOOMABLE);*/


	GAMEINSTANCE->Render_Sprite();

	DEVICE->StretchRect(originRenderTarget, nullptr, TemporaryRenderTarget, nullptr, D3DTEXF_LINEAR);
	
	Apply_BoosterBlur(RENDERGROUP::RENDER_POSTPROCCESSING, originTex);

	DEVICE->StretchRect(originRenderTarget, nullptr, TemporaryRenderTarget, nullptr, D3DTEXF_LINEAR);

	Apply_FadeOut(RENDERGROUP::RENDER_FADEOUT, originTex);
	
	
	Draw_Divide_ViewPort(RENDERGROUP::RENDER_NORMAL, normalTex);
	Draw_Divide_ViewPort(RENDERGROUP::RENDER_DEPTH, depthTex);
	Draw_Divide_ViewPort(RENDERGROUP::RENDER_DIFFUSE, diffuseTex);
	Draw_Divide_ViewPort(RENDERGROUP::RENDER_SPECULAR, specularTex);
	Draw_Divide_ViewPort(RENDERGROUP::RENDER_VIEWBLOOM, BloomTex);
	Draw_Divide_ViewPort(RENDERGROUP::RENDER_VIEWLIGHT, stashTex);

	
}

void CRender_Manager::Bloom_Pipeline()
{
	DEVICE->SetRenderTarget(1, ExtractBloomSurface);
	DEVICE->ColorFill(ExtractBloomSurface, NULL, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));

	ID3DXEffect** ppShader = GAMEINSTANCE->Get_Shader_From_Key(TEXT("ExtractBloom"));

	if (!ppShader)
	{
		return;
	}
		

	CCamera* pCamera = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA);

	if (pCamera)
		pCamera->Bind_PipeLine();

	D3DXHANDLE hTech = 0;
	UINT numPasses = 0;

	hTech = (*ppShader)->GetTechniqueByName("DefaultTechnique");
	(*ppShader)->SetTechnique(hTech);


	D3DXHANDLE worldHandle = (*ppShader)->GetParameterByName(0, "world");
	D3DXHANDLE viewHandle = (*ppShader)->GetParameterByName(0, "view");
	D3DXHANDLE projHandle = (*ppShader)->GetParameterByName(0, "proj");

	_float4x4 view, proj, world;
	DEVICE->GetTransform(D3DTS_VIEW, &view);
	DEVICE->GetTransform(D3DTS_PROJECTION, &proj);

	(*ppShader)->SetMatrix(viewHandle, &view);
	(*ppShader)->SetMatrix(projHandle, &proj);

	for (auto iter = m_RenderObjects[(_uint)RENDERGROUP::RENDER_BLOOMABLE].begin(); iter != m_RenderObjects[(_uint)RENDERGROUP::RENDER_BLOOMABLE].end();)
	{
		if ((*iter))
		{
			
			(*iter)->Render_Begin(ppShader);

			DEVICE->GetTransform(D3DTS_WORLD, &world);

			(*ppShader)->SetMatrix(worldHandle, &world);

			(*ppShader)->Begin(&numPasses, 0);
			for (_uint i = 0; i < numPasses; i++)
			{
				(*ppShader)->BeginPass(i);

				(*iter)->Render();

				(*ppShader)->EndPass();
			}
			(*ppShader)->End();


			//(*iter)->Render();
			(*iter)->Return_WeakPtr(&(*iter));
		}

		iter = m_RenderObjects[(_uint)RENDERGROUP::RENDER_BLOOMABLE].erase(iter);
	}

	DEVICE->SetRenderTarget(1, NULL);

}

void CRender_Manager::Extract_Brightness()
{
	ID3DXEffect** ppShader = GAMEINSTANCE->Get_Shader_From_Key(TEXT("ExtractBrightness"));

	if (!ppShader)
	{
		return;
	}

	DEVICE->GetRenderTarget(0, &originRenderTarget);
	DEVICE->SetRenderTarget(0, ExtractBloomSurface);
	
	//DEVICE->ColorFill(ExtractBrightnessSurface, NULL, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));

	CCamera* pCamera = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA);

	/*if (pCamera)
		pCamera->Bind_PipeLine();*/

	D3DXHANDLE hTech = 0;
	UINT numPasses = 0;

	hTech = (*ppShader)->GetTechniqueByName("DefaultTechnique");
	(*ppShader)->SetTechnique(hTech);


	/*D3DXHANDLE worldHandle = (*ppShader)->GetParameterByName(0, "world");
	D3DXHANDLE viewHandle = (*ppShader)->GetParameterByName(0, "view");
	D3DXHANDLE projHandle = (*ppShader)->GetParameterByName(0, "proj");

	_float4x4 view, proj, world;
	DEVICE->GetTransform(D3DTS_VIEW, &view);
	DEVICE->GetTransform(D3DTS_PROJECTION, &proj);

	(*ppShader)->SetMatrix(viewHandle, &view);
	(*ppShader)->SetMatrix(projHandle, &proj);*/


	D3DXHANDLE ExtractBrightnessHandle = (*ppShader)->GetParameterByName(0, "ExtractBrightnessTex");

	(*ppShader)->SetTexture(ExtractBrightnessHandle, originTex);		

	for (auto iter = m_RenderObjects[(_uint)RENDERGROUP::RENDER_BRIGHTNESS].begin(); iter != m_RenderObjects[(_uint)RENDERGROUP::RENDER_BRIGHTNESS].end();)
	{
		if ((*iter))
		{

			(*iter)->Render_Begin(ppShader);

			//DEVICE->GetTransform(D3DTS_WORLD, &world);

			//(*ppShader)->SetMatrix(worldHandle, &world);

			(*ppShader)->Begin(&numPasses, 0);
			for (_uint i = 0; i < numPasses; i++)
			{
				(*ppShader)->BeginPass(i);

				(*iter)->Render();

				(*ppShader)->EndPass();
			}
			(*ppShader)->End();


			//(*iter)->Render();
			(*iter)->Return_WeakPtr(&(*iter));
		}

		iter = m_RenderObjects[(_uint)RENDERGROUP::RENDER_BRIGHTNESS].erase(iter);
	}

	DEVICE->SetRenderTarget(0, originRenderTarget);

}

bool CRender_Manager::SetupTexture(IDirect3DTexture9** texture, IDirect3DSurface9** surface)
{
	const GRAPHICDESC& Desc = GAMEINSTANCE->Get_Graphic_Desc();

	HRESULT hr = D3DXCreateTexture(
		DEVICE,
		Desc.iWinCX,
		Desc.iWinCY,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		texture
	);

	if (FAILED(hr)) {
		assert(false);
		return false;
	}

	(*texture)->GetSurfaceLevel(0, surface);

	return true;
}

void CRender_Manager::SetMRT()
{
	DEVICE->GetRenderTarget(0, &originRenderTarget);

	DEVICE->SetRenderTarget(0, normalSurface);
	DEVICE->SetRenderTarget(1, depthSurface);
	DEVICE->SetRenderTarget(2, diffuseSurface);
	DEVICE->SetRenderTarget(3, specularSurface);

}

void CRender_Manager::ResumeOriginRender()
{
	DEVICE->SetRenderTarget(0, originRenderTarget);

	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
	DEVICE->SetRenderTarget(3, NULL);
}

void CRender_Manager::DrawScreenQuad()
{
	DEVICE->SetStreamSource(0, vb, 0, sizeof(VTX));
	DEVICE->SetFVF(D3DFVF_XYZ);
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}

void CRender_Manager::Draw_Divide_ViewPort(RENDERGROUP _eRenderGroup, IDirect3DTexture9* _Tex)
{
	ID3DXEffect** ppShader = GAMEINSTANCE->Get_Shader_From_Key(TEXT("DrawSurface"));

	if (!ppShader)
		return;

	CCamera* pCamera = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA);	

	if (pCamera)
		pCamera->Bind_PipeLine();

	D3DXHANDLE hTech = 0;
	UINT numPasses = 0;

	hTech = (*ppShader)->GetTechniqueByName("DefaultTechnique");
	(*ppShader)->SetTechnique(hTech);

	for (auto iter = m_RenderObjects[(_uint)_eRenderGroup].begin(); iter != m_RenderObjects[(_uint)_eRenderGroup].end();)
	{
		if ((*iter))
		{
			D3DXHANDLE TextureHandle = (*ppShader)->GetParameterByName(0, "g_Texture");
			(*ppShader)->SetTexture(TextureHandle, _Tex);

			(*iter)->Render_Begin(ppShader);

			(*ppShader)->Begin(&numPasses, 0);
			for (_uint i = 0; i < numPasses; i++)
			{
				(*ppShader)->BeginPass(i);

				(*iter)->Render();

				(*ppShader)->EndPass();
			}
			(*ppShader)->End();

			
			//(*iter)->Render();
			(*iter)->Return_WeakPtr(&(*iter));
		}

		iter = m_RenderObjects[(_uint)_eRenderGroup].erase(iter);
	}

	

	
}

void CRender_Manager::Apply_Blur(RENDERGROUP _eRenderGroup, IDirect3DTexture9* _Tex)
{

	ID3DXEffect** ppShader = GAMEINSTANCE->Get_Shader_From_Key(TEXT("XBlur"));

	if (!ppShader)
		return;

	DEVICE->GetRenderTarget(0, &originRenderTarget);
	DEVICE->SetRenderTarget(0, BloomSurface);
	DEVICE->ColorFill(BloomSurface, NULL, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));

	CCamera* pCamera = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA);

	if (pCamera)
		pCamera->Bind_PipeLine();

	D3DXHANDLE hTech = 0;
	UINT numPasses = 0;

	hTech = (*ppShader)->GetTechniqueByName("DefaultTechnique");
	(*ppShader)->SetTechnique(hTech);

	for (auto iter = m_RenderObjects[(_uint)_eRenderGroup].begin(); iter != m_RenderObjects[(_uint)_eRenderGroup].end();)
	{
		if ((*iter))
		{
			D3DXHANDLE TextureHandle = (*ppShader)->GetParameterByName(0, "ForegroundTexture");
			(*ppShader)->SetTexture(TextureHandle, _Tex);
			 
			D3DXHANDLE PixelWidthHandle = (*ppShader)->GetParameterByName(0, "pixelWidth");
			(*ppShader)->SetFloat(PixelWidthHandle, 1.f / (_float)m_GraphicDesc.iWinCX * 3.f);

			(*iter)->Render_Begin(ppShader);

			(*ppShader)->Begin(&numPasses, 0);
			for (_uint i = 0; i < numPasses; i++)
			{
				(*ppShader)->BeginPass(i);

				(*iter)->Render();

				(*ppShader)->EndPass();
			}
			(*ppShader)->End();


			//(*iter)->Render();
			(*iter)->Return_WeakPtr(&(*iter));
		}

		iter = m_RenderObjects[(_uint)_eRenderGroup].erase(iter);
	}

	DEVICE->SetRenderTarget(0, originRenderTarget);
}

void CRender_Manager::Apply_Bloom(RENDERGROUP _eRenderGroup)
{
	ID3DXEffect** ppShader = GAMEINSTANCE->Get_Shader_From_Key(TEXT("Bloom"));

	if (!ppShader)
		return;

	CCamera* pCamera = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA);

	if (pCamera)
		pCamera->Bind_PipeLine();

	D3DXHANDLE hTech = 0;
	UINT numPasses = 0;

	hTech = (*ppShader)->GetTechniqueByName("DefaultTechnique");
	(*ppShader)->SetTechnique(hTech);

	for (auto iter = m_RenderObjects[(_uint)_eRenderGroup].begin(); iter != m_RenderObjects[(_uint)_eRenderGroup].end();)
	{
		if ((*iter))
		{
			D3DXHANDLE OriginalRenderTextureHandle = (*ppShader)->GetParameterByName(0, "OriginalRenderTexture");
			(*ppShader)->SetTexture(OriginalRenderTextureHandle, originTex);

			D3DXHANDLE BloomTextureHandle = (*ppShader)->GetParameterByName(0, "BloomTex");
			(*ppShader)->SetTexture(BloomTextureHandle, BloomTex);

			D3DXHANDLE BloomOriTextureHandle = (*ppShader)->GetParameterByName(0, "BloomOriTex");
			(*ppShader)->SetTexture(BloomOriTextureHandle, ExtractBloomTex);

			(*iter)->Render_Begin(ppShader);

			(*ppShader)->Begin(&numPasses, 0);
			for (_uint i = 0; i < numPasses; i++)
			{
				(*ppShader)->BeginPass(i);

				(*iter)->Render();

				(*ppShader)->EndPass();
			}
			(*ppShader)->End();


			//(*iter)->Render();
			(*iter)->Return_WeakPtr(&(*iter));
		}

		iter = m_RenderObjects[(_uint)_eRenderGroup].erase(iter);
	}
}

void CRender_Manager::Apply_BoosterBlur(RENDERGROUP _eRenderGroup, IDirect3DTexture9* _Tex)
{
	ID3DXEffect** ppShader = GAMEINSTANCE->Get_Shader_From_Key(TEXT("BoosterBlur"));

	if (!ppShader)
		return;

	
	fBlurWidth -= 0.0007f;
	if (0.f > fBlurWidth)
		fBlurWidth = 0.f;

	CCamera* pCamera = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA);

	if (pCamera)
		pCamera->Bind_PipeLine();

	D3DXHANDLE hTech = 0;
	UINT numPasses = 0;

	hTech = (*ppShader)->GetTechniqueByName("DefaultTechnique");
	(*ppShader)->SetTechnique(hTech);

	for (auto iter = m_RenderObjects[(_uint)_eRenderGroup].begin(); iter != m_RenderObjects[(_uint)_eRenderGroup].end();)
	{
		if ((*iter))
		{
			D3DXHANDLE TextureHandle = (*ppShader)->GetParameterByName(0, "g_Texture");
			(*ppShader)->SetTexture(TextureHandle, _Tex);

			D3DXHANDLE BlurWidthHandle = (*ppShader)->GetParameterByName(0, "blurWidth");
			(*ppShader)->SetFloat(BlurWidthHandle, fBlurWidth);

			(*iter)->Render_Begin(ppShader);

			(*ppShader)->Begin(&numPasses, 0);
			for (_uint i = 0; i < numPasses; i++)
			{
				(*ppShader)->BeginPass(i);

				(*iter)->Render();

				(*ppShader)->EndPass();
			}
			(*ppShader)->End();


			//(*iter)->Render();
			(*iter)->Return_WeakPtr(&(*iter));
		}

		iter = m_RenderObjects[(_uint)_eRenderGroup].erase(iter);
	}
}

void CRender_Manager::Apply_FadeOut(RENDERGROUP _eRenderGroup, IDirect3DTexture9* _Tex/*originTex*/)
{
	ID3DXEffect** ppShader = GAMEINSTANCE->Get_Shader_From_Key(TEXT("FadeInAndOut"));

	if (!ppShader)
		return;

	CCamera* pCamera = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA);

	if (pCamera)
		pCamera->Bind_PipeLine();

	D3DXHANDLE hTech = 0;
	UINT numPasses = 0;

	hTech = (*ppShader)->GetTechniqueByName("DefaultTechnique");
	(*ppShader)->SetTechnique(hTech);


	for (auto iter = m_RenderObjects[(_uint)_eRenderGroup].begin(); iter != m_RenderObjects[(_uint)_eRenderGroup].end();)
	{
		if ((*iter))
		{
			D3DXHANDLE TextureHandle = (*ppShader)->GetParameterByName(0, "g_Texture");
			(*ppShader)->SetTexture(TextureHandle, _Tex);

			D3DXHANDLE FadeOuteOffSetHandle = (*ppShader)->GetParameterByName(0, "FadeOuteOffSet");
			(*ppShader)->SetFloat(FadeOuteOffSetHandle, fFadeOutOffset);

			(*iter)->Render_Begin(ppShader);

			(*ppShader)->Begin(&numPasses, 0);
			for (_uint i = 0; i < numPasses; i++)
			{
				(*ppShader)->BeginPass(i);

				(*iter)->Render();

				(*ppShader)->EndPass();
			}
			(*ppShader)->End();


			//(*iter)->Render();
			(*iter)->Return_WeakPtr(&(*iter));
		}

		iter = m_RenderObjects[(_uint)_eRenderGroup].erase(iter);
	}


}

void CRender_Manager::Set_OnlyRenderTarget(IDirect3DSurface9** _ppSurface)
{
	DEVICE->SetRenderTarget(0, (*_ppSurface));

	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
	DEVICE->SetRenderTarget(3, NULL);

}

void CRender_Manager::Free()
{
	__super::Free();
	
	delete this;
}
