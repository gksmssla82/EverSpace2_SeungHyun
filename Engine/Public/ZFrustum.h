#ifndef _ZFRUSTUM_H_
#define _ZFRUSTUM_H_

#include "Base.h"

/// �������ҿ� ��Ȯ�ϰ� ���Ե��� �ʴ���, �ణ�� ������ �־ �������ҿ� ���Խ�Ű�� ���� ��
#define PLANE_EPSILON	5.0f

/**
 * �������� �ø��� �ϱ����� Ŭ����
 *
 */
class CZFrustum final : public CBase
{
	DECLARE_SINGLETON(CZFrustum)
public:
	CZFrustum();
	~CZFrustum();

public:
	void Update_Frustum();


public:
	/// ������
	
	/// ī�޶�(view) * ��������(projection)����� �Է¹޾� 6���� ����� �����.
	
	/// ���� v�� �������Ҿȿ� ������ TRUE�� ��ȯ, �ƴϸ� FALSE�� ��ȯ�Ѵ�.
	BOOL	IsIn( D3DXVECTOR3* pv );

	/** �߽�(v)�� ������(radius)�� ���� ��豸(bounding sphere)�� �������Ҿȿ� ������
	 *  TRUE�� ��ȯ, �ƴϸ� FALSE�� ��ȯ�Ѵ�.
	 */
	BOOL	IsInSphere( D3DXVECTOR3* pv, float radius );

	/// ���������� ȭ�鿡 �׷��ش�.
	BOOL	Draw();

	/// ���� ī�޶��� ������ǥ�� ����ش�.
	D3DXVECTOR3*	GetPos() { return &m_vPos; }

	void Free();
	
private:
	BOOL	Make(D3DXMATRIX* pmatViewProj);


private:
	D3DXVECTOR3	m_vtx[8];	/// ���������� ������ ���� 8��
	D3DXVECTOR3	m_vPos;		/// ���� ī�޶��� ������ǥ
	D3DXPLANE	m_plane[6];	/// ���������� �����ϴ� 6���� ���
};


#endif // _ZFRUSTUM_H_