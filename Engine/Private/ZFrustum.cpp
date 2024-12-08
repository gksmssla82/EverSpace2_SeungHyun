#include "ZFrustum.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CZFrustum)

CZFrustum::CZFrustum()
{
	ZeroMemory( m_vtx, sizeof( m_vtx[0] ) * 8 );
	ZeroMemory( m_plane, sizeof( m_plane[0] ) * 6 );
}

CZFrustum::~CZFrustum()
{
}

void CZFrustum::Update_Frustum()
{
	_float4x4 matView, matProj, mat;
	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);
	mat = matView * matProj;

	Make(&mat);
	
}

void CZFrustum::Free()
{
	delete this;
}

// ī�޶�(view) * ��������(projection)����� �Է¹޾� 6���� ����� �����.
BOOL CZFrustum::Make( D3DXMATRIX* pmatViewProj )
{
	int				i;
	D3DXMATRIX	matInv;

	// ������ı��� ��ġ�� ��� 3���� ������ǥ�� ���� (-1,-1,0) ~ (1,1,1)������ ������ �ٲ��.
	// m_vtx�� �� ���������� ��谪�� �־�д�.
	m_vtx[0].x = -1.0f;	m_vtx[0].y = -1.0f;	m_vtx[0].z = 0.0f;
	m_vtx[1].x =  1.0f;	m_vtx[1].y = -1.0f;	m_vtx[1].z = 0.0f;
	m_vtx[2].x =  1.0f;	m_vtx[2].y = -1.0f;	m_vtx[2].z = 1.0f;
	m_vtx[3].x = -1.0f;	m_vtx[3].y = -1.0f;	m_vtx[3].z = 1.0f;
	m_vtx[4].x = -1.0f;	m_vtx[4].y =  1.0f;	m_vtx[4].z = 0.0f;
	m_vtx[5].x =  1.0f;	m_vtx[5].y =  1.0f;	m_vtx[5].z = 0.0f;
	m_vtx[6].x =  1.0f;	m_vtx[6].y =  1.0f;	m_vtx[6].z = 1.0f;
	m_vtx[7].x = -1.0f;	m_vtx[7].y =  1.0f;	m_vtx[7].z = 1.0f;

	// view * proj�� ������� ���Ѵ�.
	D3DXMatrixInverse(&matInv, NULL, pmatViewProj );

	// Vertex_���� = Vertex_local * Matrix_world * Matrix_view * Matrix_Proj �ε�,
	// Vertex_world = Vertex_local * Matrix_world�̹Ƿ�,
	// Vertex_���� = Vertex_world * Matrix_view * Matrix_Proj �̴�.
	// Vertex_���� = Vertex_world * ( Matrix_view * Matrix_Proj ) ����
	// �����( Matrix_view * Matrix_Proj )^-1�� �纯�� ���ϸ�
	// Vertex_���� * �����( Matrix_view * Matrix_Proj )^-1 = Vertex_World �� �ȴ�.
	// �׷��Ƿ�, m_vtx * matInv = Vertex_world�� �Ǿ�, ������ǥ���� �������� ��ǥ�� ���� �� �ִ�.
	for( i = 0; i < 8; i++ )
		D3DXVec3TransformCoord( &m_vtx[i], &m_vtx[i], &matInv );

	// 0���� 5���� ���������� near����� ������ܰ� �����ϴ��̹Ƿ�, ���� ��ǥ�� ���ؼ� 2�� ������
	// ī�޶��� ��ǥ�� ���� �� �ִ�.(��Ȯ�� ��ġ�ϴ� ���� �ƴϴ�.)
	//m_vPos = ( m_vtx[0] + m_vtx[5] ) / 2.0f;
	
	// ����� ������ǥ�� �������� ����� �����
	// ���Ͱ� �������� ���ʿ��� �ٱ������� ������ �����̴�.
	D3DXPlaneFromPoints(&m_plane[0], m_vtx+4, m_vtx+7, m_vtx+6);	// �� ���(top)
	D3DXPlaneFromPoints(&m_plane[1], m_vtx  , m_vtx+1, m_vtx+2);	// �� ���(bottom)
	D3DXPlaneFromPoints(&m_plane[2], m_vtx  , m_vtx+4, m_vtx+5);	// �� ���(near)
	D3DXPlaneFromPoints(&m_plane[3], m_vtx+2, m_vtx+6, m_vtx+7);	// �� ���(far)
	D3DXPlaneFromPoints(&m_plane[4], m_vtx  , m_vtx+3, m_vtx+7);	// �� ���(left)
	D3DXPlaneFromPoints(&m_plane[5], m_vtx+1, m_vtx+5, m_vtx+6);	// �� ���(right)

	return TRUE;
}

/// ���� v�� �������Ҿȿ� ������ TRUE�� ��ȯ, �ƴϸ� FALSE�� ��ȯ�Ѵ�.
BOOL CZFrustum::IsIn( D3DXVECTOR3* pv )
{
	float		fDist;

	// ����� left, right, far plane�� �����Ѵ�.
	for( int i = 0 ; i < 6 ; i++ )
	{
		fDist = D3DXPlaneDotCoord( &m_plane[i], pv );
		if( fDist > PLANE_EPSILON ) return FALSE;	// plane�� normal���Ͱ� far�� ���ϰ� �����Ƿ� ����̸� ���������� �ٱ���
	}

	return TRUE;
}

/** �߽�(v)�� ������(radius)�� ���� ��豸(bounding sphere)�� �������Ҿȿ� ������
 *  TRUE�� ��ȯ, �ƴϸ� FALSE�� ��ȯ�Ѵ�.
 */
BOOL CZFrustum::IsInSphere( D3DXVECTOR3* pv, float radius )
{
	float		fDist;

	for (int i = 0; i < 6; i++)
	{
		fDist = D3DXPlaneDotCoord(&m_plane[i], pv);
		if (fDist > (radius + PLANE_EPSILON)) return FALSE;	// plane�� normal���Ͱ� far�� ���ϰ� �����Ƿ� ����̸� ���������� �ٱ���

	}
	
	return TRUE;
}

/// ���������� ȭ�鿡 �׷��ش�.
BOOL CZFrustum::Draw()
{
	D3DXMATRIX	World;
	D3DXMatrixIdentity(&World);

	DEVICE->SetTransform(D3DTS_WORLD, &World);

	WORD		index[] = { 0, 1, 2,
		0, 2, 3,
		4, 7, 6,
		4, 6, 5,
		1, 5, 6,
		1, 6, 2,
		0, 3, 7,
		0, 7, 4,
		0, 4, 5,
		0, 5, 1,
		3, 7, 6,
		3, 6, 2 };

	DEVICE->SetFVF(D3DFVF_XYZ);
	DEVICE->SetStreamSource(0, NULL, 0, sizeof(D3DXVECTOR3));
	DEVICE->SetTexture(0, NULL);
	DEVICE->SetIndices(0);
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	DEVICE->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 8, 12, index, D3DFMT_INDEX16, m_vtx, sizeof(m_vtx[0]));
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	return TRUE;
}

