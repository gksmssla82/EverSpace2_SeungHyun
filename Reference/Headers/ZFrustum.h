#ifndef _ZFRUSTUM_H_
#define _ZFRUSTUM_H_

#include "Base.h"

/// 프러스텀에 정확하게 포함되지 않더라도, 약간의 여분을 주어서 프러스텀에 포함시키기 위한 값
#define PLANE_EPSILON	5.0f

/**
 * 프러스텀 컬링을 하기위한 클래스
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
	/// 생성자
	
	/// 카메라(view) * 프로젝션(projection)행렬을 입력받아 6개의 평면을 만든다.
	
	/// 한점 v가 프러스텀안에 있으면 TRUE를 반환, 아니면 FALSE를 반환한다.
	BOOL	IsIn( D3DXVECTOR3* pv );

	/** 중심(v)와 반지름(radius)를 갖는 경계구(bounding sphere)가 프러스텀안에 있으면
	 *  TRUE를 반환, 아니면 FALSE를 반환한다.
	 */
	BOOL	IsInSphere( D3DXVECTOR3* pv, float radius );

	/// 프러스텀을 화면에 그려준다.
	BOOL	Draw();

	/// 현재 카메라의 월드좌표를 얻어준다.
	D3DXVECTOR3*	GetPos() { return &m_vPos; }

	void Free();
	
private:
	BOOL	Make(D3DXMATRIX* pmatViewProj);


private:
	D3DXVECTOR3	m_vtx[8];	/// 프러스텀을 구성할 정점 8개
	D3DXVECTOR3	m_vPos;		/// 현재 카메라의 월드좌표
	D3DXPLANE	m_plane[6];	/// 프러스텀을 구성하는 6개의 평면
};


#endif // _ZFRUSTUM_H_