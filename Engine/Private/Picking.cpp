#include "Picking.h"
#include "GameInstance.h"
#include "VIBuffer.h"
#include "Transform.h"

IMPLEMENT_SINGLETON(CPicking)

CPicking::CPicking()
{
}

HRESULT CPicking::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;

	return S_OK;
}

HRESULT CPicking::Compute_RayInWorldSpace(RAY* _Out)
{
	/* ���ý����̽� -> ���彺���̽� -> �佺���̽� -> ���������̽� -> ����Ʈ */

	/* 1. ����Ʈ ���� ���콺 ��ǥ ���ϱ� */
	POINT  ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);

	D3DVIEWPORT9   ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
	DEVICE->GetViewport(&ViewPort);

	/* 2. ���� �����̽� ���� ���콺 ��ǥ ���ϱ� */
	_float3  vProjPos;

	vProjPos.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
	vProjPos.y = ptMouse.y / -(ViewPort.Height * 0.5f) + 1.f;
	vProjPos.z = 0.0f;

	/* 3.�佺���̽����� ���콺 ��ǥ�� ������. */
	_float3		vViewPos;

	_float4x4	ProjMatrixInv;
	DEVICE->GetTransform(D3DTS_PROJECTION, &ProjMatrixInv);
	D3DXMatrixInverse(&ProjMatrixInv, nullptr, &ProjMatrixInv);
	D3DXVec3TransformCoord(&vViewPos, &vProjPos, &ProjMatrixInv);

	/* 4.���콺���̿� ���콺Pos��������.  */
	_float3		vRayDir, vRayPos;

	vRayDir = vViewPos - _float3(0.f, 0.f, 0.f);
	vRayPos = _float3(0.f, 0.f, 0.f);

	/* 5.����ΰ���. */
	_float4x4	ViewMatrixInv;
	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrixInv);
	D3DXMatrixInverse(&ViewMatrixInv, nullptr, &ViewMatrixInv);

	D3DXVec3TransformNormal(&m_vRayDir, &vRayDir, &ViewMatrixInv);
	D3DXVec3TransformCoord(&m_vRayPos, &vRayPos, &ViewMatrixInv);
	

}

_bool CPicking::Picking_VIBuffer(CVIBuffer* pVIBuffer, CTransform* pTransform, _float3* pOut)
{

	_float4x4		WorldMatrix = pTransform->Get_WorldMatrix();                 // ���� ��Ʈ���� ������
	D3DXMatrixInverse(&WorldMatrix, nullptr, &WorldMatrix);    // ����� ���� ���ý����̽��� ��

	_float3			vRayPos, vRayDir;                                           //  Ray��ġ����, Ray������� 

	D3DXVec3TransformCoord(&vRayPos, &m_vRayPos, &WorldMatrix);      // Ray��ġ���� -> ���ý����̽��κ��� 
	D3DXVec3TransformNormal(&vRayDir, &m_vRayDir, &WorldMatrix);     // Ray������� -> ���ý����̽��κ���
	D3DXVec3Normalize(&vRayDir, &vRayDir);                              // Ray������� ����ȭ

	_uint iNumFaces = pVIBuffer->Get_NumPrimitive();                           // VIBuffer���ִ� ������ �� ������
	const _float3* pVerticesPos = pVIBuffer->Get_VerticesPos();                // VIBuffer���ִ� ���ؽ� ��ġ ������

	_float  fU, fV, fDist;

	for (_uint i = 0; i < iNumFaces; ++i)                                     // ������ ����ŭ �ݺ�
	{
		_uint3 iIndices = pVIBuffer->Get_Indices(i);                    // �ش� ������ �ε��� ������

		_float3		vPickedPos;

		if (true == D3DXIntersectTri(&pVerticesPos[iIndices.ix], &pVerticesPos[iIndices.iy], &pVerticesPos[iIndices.iz], &vRayPos, &vRayDir, &fU, &fV, &fDist))
		{
			vPickedPos = vRayPos + *D3DXVec3Normalize(&vRayDir, &vRayDir) * fDist;
			D3DXVec3TransformCoord(pOut, &vPickedPos, &pTransform->Get_WorldMatrix());

			return true;
		}

	}

	return false;
}


void CPicking::Free()
{
	__super::Free();

	delete this;
}
