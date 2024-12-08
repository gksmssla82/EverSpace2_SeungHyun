#include "Mesh_SongShip.h"
#include "GameInstance.h"

CMesh_SongShip::CMesh_SongShip()
{
}

CMesh_SongShip::CMesh_SongShip(const CMesh_SongShip& Prototype)
{
	*this = Prototype;

	if (!m_pMesh)
	{
		return;
	}

	ID3DXMesh* pCloneMesh = nullptr;
	m_pMesh->CloneMeshFVF(m_pMesh->GetOptions(), m_pMesh->GetFVF(), DEVICE, &pCloneMesh);
	m_pMesh = pCloneMesh;
}

HRESULT CMesh_SongShip::Initialize_Prototype()
{

	m_iNumVertices = 248;     
	m_iNumPrimitive = 104;
	m_dwFVF = VTXDEFAULT::FVF;

	m_dwNumSubsets = 1;
	if (FAILED(Create_EmptyMesh()))
	{
		MSG_BOX("Failed to Create_EmptyMesh : CMesh_Cube");
		return E_FAIL;
	}
	VTXDEFAULT* vertices = nullptr;
	m_pMesh->LockVertexBuffer(0, (void**)&vertices);

	vertices[0] = VTXDEFAULT(_float3(-1.83, 0.00, 0.33), _float3(-0.00, -0.70, -0.71), _float2(0.38, 1.00));
	vertices[1] = VTXDEFAULT(_float3(-1.00, 1.00, -0.66), _float3(-0.00, -0.70, -0.71), _float2(0.38, 0.75));
	vertices[2] = VTXDEFAULT(_float3(1.00, 1.00, -0.66), _float3(-0.00, -0.70, -0.71), _float2(0.62, 0.75));
	vertices[3] = VTXDEFAULT(_float3(1.83, 0.00, 0.33), _float3(-0.00, -0.70, -0.71), _float2(0.62, 1.00));
	vertices[4] = VTXDEFAULT(_float3(-1.00, 1.00, -0.66), _float3(0.00, -0.99, 0.12), _float2(0.38, 0.75));
	vertices[5] = VTXDEFAULT(_float3(0.00, 0.00, -8.66), _float3(0.00, -0.99, 0.12), _float2(0.50, 0.50));
	vertices[6] = VTXDEFAULT(_float3(1.00, 1.00, -0.66), _float3(0.00, -0.99, 0.12), _float2(0.62, 0.75));
	vertices[7] = VTXDEFAULT(_float3(0.00, 0.00, -8.66), _float3(0.00, 0.99, 0.12), _float2(0.50, 0.25));
	vertices[8] = VTXDEFAULT(_float3(-1.00, -1.00, -0.66), _float3(0.00, 0.99, 0.12), _float2(0.38, 0.00));
	vertices[9] = VTXDEFAULT(_float3(1.00, -1.00, -0.66), _float3(0.00, 0.99, 0.12), _float2(0.62, 0.00));
	vertices[10] = VTXDEFAULT(_float3(1.83, 0.00, 0.33), _float3(-0.83, -0.53, 0.17), _float2(0.62, 1.00));
	vertices[11] = VTXDEFAULT(_float3(1.00, 1.00, -0.66), _float3(-0.83, -0.53, 0.17), _float2(0.62, 0.75));
	vertices[12] = VTXDEFAULT(_float3(0.00, 0.00, -8.66), _float3(-0.83, -0.53, 0.17), _float2(0.88, 0.88));
	vertices[13] = VTXDEFAULT(_float3(0.00, 0.00, -8.66), _float3(0.83, -0.53, 0.17), _float2(0.12, 0.88));
	vertices[14] = VTXDEFAULT(_float3(-1.00, 1.00, -0.66), _float3(0.83, -0.53, 0.17), _float2(0.38, 0.75));
	vertices[15] = VTXDEFAULT(_float3(-1.83, 0.00, 0.33), _float3(0.83, -0.53, 0.17), _float2(0.38, 1.00));
	vertices[16] = VTXDEFAULT(_float3(0.00, 0.00, -8.66), _float3(-0.83, 0.53, 0.17), _float2(0.50, 0.25));
	vertices[17] = VTXDEFAULT(_float3(1.00, -1.00, -0.66), _float3(-0.83, 0.53, 0.17), _float2(0.62, 0.00));
	vertices[18] = VTXDEFAULT(_float3(1.83, 0.00, 0.33), _float3(-0.83, 0.53, 0.17), _float2(0.62, 0.00));
	vertices[19] = VTXDEFAULT(_float3(1.83, 0.00, 0.33), _float3(0.00, 0.70, -0.71), _float2(0.62, 0.00));
	vertices[20] = VTXDEFAULT(_float3(1.00, -1.00, -0.66), _float3(0.00, 0.70, -0.71), _float2(0.62, 0.00));
	vertices[21] = VTXDEFAULT(_float3(-1.00, -1.00, -0.66), _float3(0.00, 0.70, -0.71), _float2(0.38, 0.00));
	vertices[22] = VTXDEFAULT(_float3(-1.83, 0.00, 0.33), _float3(0.00, 0.70, -0.71), _float2(0.38, 0.00));
	vertices[23] = VTXDEFAULT(_float3(-1.83, 0.00, 0.33), _float3(0.83, 0.53, 0.17), _float2(0.38, 0.00));
	vertices[24] = VTXDEFAULT(_float3(-1.00, -1.00, -0.66), _float3(0.83, 0.53, 0.17), _float2(0.38, 0.00));
	vertices[25] = VTXDEFAULT(_float3(0.00, 0.00, -8.66), _float3(0.83, 0.53, 0.17), _float2(0.50, 0.25));
	vertices[26] = VTXDEFAULT(_float3(-4.24, 1.98, 2.21), _float3(-0.10, -0.97, 0.22), _float2(0.38, 0.88));
	vertices[27] = VTXDEFAULT(_float3(-1.00, 1.01, -0.66), _float3(-0.10, -0.97, 0.22), _float2(0.50, 0.50));
	vertices[28] = VTXDEFAULT(_float3(-2.43, 1.98, 3.06), _float3(-0.10, -0.97, 0.22), _float2(0.62, 0.75));
	vertices[29] = VTXDEFAULT(_float3(-1.00, 1.01, -0.66), _float3(0.42, 0.89, 0.17), _float2(0.50, 0.25));
	vertices[30] = VTXDEFAULT(_float3(-4.24, 1.98, 2.21), _float3(0.42, 0.89, 0.17), _float2(0.38, 0.00));
	vertices[31] = VTXDEFAULT(_float3(-2.43, 0.98, 3.06), _float3(0.42, 0.89, 0.17), _float2(0.62, 0.00));
	vertices[32] = VTXDEFAULT(_float3(-2.43, 0.98, 3.06), _float3(-0.93, -0.00, -0.36), _float2(0.62, 1.00));
	vertices[33] = VTXDEFAULT(_float3(-2.43, 1.98, 3.06), _float3(-0.93, -0.00, -0.36), _float2(0.62, 0.75));
	vertices[34] = VTXDEFAULT(_float3(-1.00, 1.01, -0.66), _float3(-0.93, -0.00, -0.36), _float2(0.88, 0.88));
	vertices[35] = VTXDEFAULT(_float3(-4.24, 1.98, 2.21), _float3(0.40, 0.89, 0.20), _float2(0.38, 0.88));
	vertices[36] = VTXDEFAULT(_float3(-7.47, 2.01, 8.48), _float3(0.40, 0.89, 0.20), _float2(0.50, 0.88));
	vertices[37] = VTXDEFAULT(_float3(-2.43, 0.98, 3.06), _float3(0.40, 0.89, 0.20), _float2(0.62, 1.00));
	vertices[38] = VTXDEFAULT(_float3(-2.43, 0.98, 3.06), _float3(-0.73, -0.00, -0.68), _float2(0.62, 1.00));
	vertices[39] = VTXDEFAULT(_float3(-7.47, 2.01, 8.48), _float3(-0.73, -0.00, -0.68), _float2(0.50, 0.88));
	vertices[40] = VTXDEFAULT(_float3(-2.43, 1.98, 3.06), _float3(-0.73, -0.00, -0.68), _float2(0.62, 0.75));
	vertices[41] = VTXDEFAULT(_float3(-2.43, 1.98, 3.06), _float3(-0.00, -1.00, 0.00), _float2(0.62, 0.75));
	vertices[42] = VTXDEFAULT(_float3(-7.47, 2.01, 8.48), _float3(-0.00, -1.00, 0.00), _float2(0.50, 0.88));
	vertices[43] = VTXDEFAULT(_float3(-4.24, 1.98, 2.21), _float3(-0.00, -1.00, 0.00), _float2(0.38, 0.88));
	vertices[44] = VTXDEFAULT(_float3(4.23, 1.98, 2.20), _float3(0.10, -0.97, 0.22), _float2(0.38, 0.88));
	vertices[45] = VTXDEFAULT(_float3(2.42, 1.98, 3.05), _float3(0.10, -0.97, 0.22), _float2(0.62, 0.75));
	vertices[46] = VTXDEFAULT(_float3(0.99, 1.01, -0.67), _float3(0.10, -0.97, 0.22), _float2(0.50, 0.50));
	vertices[47] = VTXDEFAULT(_float3(0.99, 1.01, -0.67), _float3(-0.42, 0.89, 0.17), _float2(0.50, 0.25));
	vertices[48] = VTXDEFAULT(_float3(2.42, 0.98, 3.05), _float3(-0.42, 0.89, 0.17), _float2(0.62, 0.00));
	vertices[49] = VTXDEFAULT(_float3(4.23, 1.98, 2.20), _float3(-0.42, 0.89, 0.17), _float2(0.38, 0.00));
	vertices[50] = VTXDEFAULT(_float3(2.42, 0.98, 3.05), _float3(0.93, 0.00, -0.36), _float2(0.62, 1.00));
	vertices[51] = VTXDEFAULT(_float3(0.99, 1.01, -0.67), _float3(0.93, 0.00, -0.36), _float2(0.88, 0.88));
	vertices[52] = VTXDEFAULT(_float3(2.42, 1.98, 3.05), _float3(0.93, 0.00, -0.36), _float2(0.62, 0.75));
	vertices[53] = VTXDEFAULT(_float3(4.23, 1.98, 2.20), _float3(-0.40, 0.89, 0.20), _float2(0.38, 0.88));
	vertices[54] = VTXDEFAULT(_float3(2.42, 0.98, 3.05), _float3(-0.40, 0.89, 0.20), _float2(0.62, 1.00));
	vertices[55] = VTXDEFAULT(_float3(7.46, 2.01, 8.47), _float3(-0.40, 0.89, 0.20), _float2(0.50, 0.88));
	vertices[56] = VTXDEFAULT(_float3(2.42, 0.98, 3.05), _float3(0.73, 0.00, -0.68), _float2(0.62, 1.00));
	vertices[57] = VTXDEFAULT(_float3(2.42, 1.98, 3.05), _float3(0.73, 0.00, -0.68), _float2(0.62, 0.75));
	vertices[58] = VTXDEFAULT(_float3(7.46, 2.01, 8.47), _float3(0.73, 0.00, -0.68), _float2(0.50, 0.88));
	vertices[59] = VTXDEFAULT(_float3(2.42, 1.98, 3.05), _float3(0.00, -1.00, 0.00), _float2(0.62, 0.75));
	vertices[60] = VTXDEFAULT(_float3(4.23, 1.98, 2.20), _float3(0.00, -1.00, 0.00), _float2(0.38, 0.88));
	vertices[61] = VTXDEFAULT(_float3(7.46, 2.01, 8.47), _float3(0.00, -1.00, 0.00), _float2(0.50, 0.88));
	vertices[62] = VTXDEFAULT(_float3(4.23, -1.96, 2.20), _float3(0.10, 0.97, 0.22), _float2(0.38, 0.88));
	vertices[63] = VTXDEFAULT(_float3(0.99, -0.99, -0.67), _float3(0.10, 0.97, 0.22), _float2(0.50, 0.50));
	vertices[64] = VTXDEFAULT(_float3(2.42, -1.96, 3.05), _float3(0.10, 0.97, 0.22), _float2(0.62, 0.75));
	vertices[65] = VTXDEFAULT(_float3(0.99, -0.99, -0.67), _float3(-0.42, -0.89, 0.17), _float2(0.50, 0.25));
	vertices[66] = VTXDEFAULT(_float3(4.23, -1.96, 2.20), _float3(-0.42, -0.89, 0.17), _float2(0.38, 0.00));
	vertices[67] = VTXDEFAULT(_float3(2.42, -0.96, 3.05), _float3(-0.42, -0.89, 0.17), _float2(0.62, 0.00));
	vertices[68] = VTXDEFAULT(_float3(2.42, -0.96, 3.05), _float3(0.93, 0.00, -0.36), _float2(0.62, 1.00));
	vertices[69] = VTXDEFAULT(_float3(2.42, -1.96, 3.05), _float3(0.93, 0.00, -0.36), _float2(0.62, 0.75));
	vertices[70] = VTXDEFAULT(_float3(0.99, -0.99, -0.67), _float3(0.93, 0.00, -0.36), _float2(0.88, 0.88));
	vertices[71] = VTXDEFAULT(_float3(4.23, -1.96, 2.20), _float3(-0.40, -0.89, 0.20), _float2(0.38, 0.88));
	vertices[72] = VTXDEFAULT(_float3(7.46, -1.99, 8.47), _float3(-0.40, -0.89, 0.20), _float2(0.50, 0.88));
	vertices[73] = VTXDEFAULT(_float3(2.42, -0.96, 3.05), _float3(-0.40, -0.89, 0.20), _float2(0.62, 1.00));
	vertices[74] = VTXDEFAULT(_float3(2.42, -0.96, 3.05), _float3(0.73, 0.00, -0.68), _float2(0.62, 1.00));
	vertices[75] = VTXDEFAULT(_float3(7.46, -1.99, 8.47), _float3(0.73, 0.00, -0.68), _float2(0.50, 0.88));
	vertices[76] = VTXDEFAULT(_float3(2.42, -1.96, 3.05), _float3(0.73, 0.00, -0.68), _float2(0.62, 0.75));
	vertices[77] = VTXDEFAULT(_float3(2.42, -1.96, 3.05), _float3(0.00, 1.00, 0.00), _float2(0.62, 0.75));
	vertices[78] = VTXDEFAULT(_float3(7.46, -1.99, 8.47), _float3(0.00, 1.00, 0.00), _float2(0.50, 0.88));
	vertices[79] = VTXDEFAULT(_float3(4.23, -1.96, 2.20), _float3(0.00, 1.00, 0.00), _float2(0.38, 0.88));
	vertices[80] = VTXDEFAULT(_float3(-4.24, -1.96, 2.21), _float3(-0.10, 0.97, 0.22), _float2(0.38, 0.88));
	vertices[81] = VTXDEFAULT(_float3(-2.43, -1.96, 3.06), _float3(-0.10, 0.97, 0.22), _float2(0.62, 0.75));
	vertices[82] = VTXDEFAULT(_float3(-1.00, -0.99, -0.66), _float3(-0.10, 0.97, 0.22), _float2(0.50, 0.50));
	vertices[83] = VTXDEFAULT(_float3(-1.00, -0.99, -0.66), _float3(0.42, -0.89, 0.17), _float2(0.50, 0.25));
	vertices[84] = VTXDEFAULT(_float3(-2.43, -0.96, 3.06), _float3(0.42, -0.89, 0.17), _float2(0.62, 0.00));
	vertices[85] = VTXDEFAULT(_float3(-4.24, -1.96, 2.21), _float3(0.42, -0.89, 0.17), _float2(0.38, 0.00));
	vertices[86] = VTXDEFAULT(_float3(-2.43, -0.96, 3.06), _float3(-0.93, -0.00, -0.36), _float2(0.62, 1.00));
	vertices[87] = VTXDEFAULT(_float3(-1.00, -0.99, -0.66), _float3(-0.93, -0.00, -0.36), _float2(0.88, 0.88));
	vertices[88] = VTXDEFAULT(_float3(-2.43, -1.96, 3.06), _float3(-0.93, -0.00, -0.36), _float2(0.62, 0.75));
	vertices[89] = VTXDEFAULT(_float3(-4.24, -1.96, 2.21), _float3(0.40, -0.89, 0.20), _float2(0.38, 0.88));
	vertices[90] = VTXDEFAULT(_float3(-2.43, -0.96, 3.06), _float3(0.40, -0.89, 0.20), _float2(0.62, 1.00));
	vertices[91] = VTXDEFAULT(_float3(-7.47, -1.99, 8.48), _float3(0.40, -0.89, 0.20), _float2(0.50, 0.88));
	vertices[92] = VTXDEFAULT(_float3(-2.43, -0.96, 3.06), _float3(-0.73, -0.00, -0.68), _float2(0.62, 1.00));
	vertices[93] = VTXDEFAULT(_float3(-2.43, -1.96, 3.06), _float3(-0.73, -0.00, -0.68), _float2(0.62, 0.75));
	vertices[94] = VTXDEFAULT(_float3(-7.47, -1.99, 8.48), _float3(-0.73, -0.00, -0.68), _float2(0.50, 0.88));
	vertices[95] = VTXDEFAULT(_float3(-2.43, -1.96, 3.06), _float3(-0.00, 1.00, 0.00), _float2(0.62, 0.75));
	vertices[96] = VTXDEFAULT(_float3(-4.24, -1.96, 2.21), _float3(-0.00, 1.00, 0.00), _float2(0.38, 0.88));
	vertices[97] = VTXDEFAULT(_float3(-7.47, -1.99, 8.48), _float3(-0.00, 1.00, 0.00), _float2(0.50, 0.88));
	vertices[98] = VTXDEFAULT(_float3(1.35, 0.46, -0.40), _float3(-0.40, -0.90, -0.20), _float2(0.38, 0.69));
	vertices[99] = VTXDEFAULT(_float3(0.55, 0.40, 1.02), _float3(-0.40, -0.90, -0.20), _float2(0.38, 0.31));
	vertices[100] = VTXDEFAULT(_float3(0.21, 0.65, 1.02), _float3(-0.40, -0.90, -0.20), _float2(0.40, 0.31));
	vertices[101] = VTXDEFAULT(_float3(0.52, 0.75, -0.45), _float3(-0.40, -0.90, -0.20), _float2(0.40, 0.69));
	vertices[102] = VTXDEFAULT(_float3(0.52, 0.75, -0.45), _float3(0.00, -1.00, -0.07), _float2(0.40, 0.69));
	vertices[103] = VTXDEFAULT(_float3(0.21, 0.65, 1.02), _float3(0.00, -1.00, -0.07), _float2(0.40, 0.31));
	vertices[104] = VTXDEFAULT(_float3(-0.21, 0.65, 1.02), _float3(0.00, -1.00, -0.07), _float2(0.43, 0.31));
	vertices[105] = VTXDEFAULT(_float3(-0.52, 0.75, -0.45), _float3(0.00, -1.00, -0.07), _float2(0.43, 0.69));
	vertices[106] = VTXDEFAULT(_float3(-0.52, 0.75, -0.45), _float3(0.40, -0.90, -0.20), _float2(0.43, 0.69));
	vertices[107] = VTXDEFAULT(_float3(-0.21, 0.65, 1.02), _float3(0.40, -0.90, -0.20), _float2(0.43, 0.31));
	vertices[108] = VTXDEFAULT(_float3(-0.55, 0.40, 1.02), _float3(0.40, -0.90, -0.20), _float2(0.45, 0.31));
	vertices[109] = VTXDEFAULT(_float3(-1.35, 0.46, -0.40), _float3(0.40, -0.90, -0.20), _float2(0.45, 0.69));
	vertices[110] = VTXDEFAULT(_float3(-1.35, 0.46, -0.40), _float3(0.77, -0.40, -0.49), _float2(0.45, 0.69));
	vertices[111] = VTXDEFAULT(_float3(-0.55, 0.40, 1.02), _float3(0.77, -0.40, -0.49), _float2(0.45, 0.31));
	vertices[112] = VTXDEFAULT(_float3(-0.68, 0.00, 1.02), _float3(0.77, -0.40, -0.49), _float2(0.47, 0.31));
	vertices[113] = VTXDEFAULT(_float3(-1.67, 0.00, -0.40), _float3(0.77, -0.40, -0.49), _float2(0.47, 0.69));
	vertices[114] = VTXDEFAULT(_float3(-1.67, 0.00, -0.40), _float3(0.77, 0.40, -0.49), _float2(0.47, 0.69));
	vertices[115] = VTXDEFAULT(_float3(-0.68, 0.00, 1.02), _float3(0.77, 0.40, -0.49), _float2(0.47, 0.31));
	vertices[116] = VTXDEFAULT(_float3(-0.55, -0.40, 1.02), _float3(0.77, 0.40, -0.49), _float2(0.50, 0.31));
	vertices[117] = VTXDEFAULT(_float3(-1.35, -0.46, -0.40), _float3(0.77, 0.40, -0.49), _float2(0.50, 0.69));
	vertices[118] = VTXDEFAULT(_float3(-1.35, -0.46, -0.40), _float3(0.40, 0.90, -0.20), _float2(0.50, 0.69));
	vertices[119] = VTXDEFAULT(_float3(-0.55, -0.40, 1.02), _float3(0.40, 0.90, -0.20), _float2(0.50, 0.31));
	vertices[120] = VTXDEFAULT(_float3(-0.21, -0.65, 1.02), _float3(0.40, 0.90, -0.20), _float2(0.52, 0.31));
	vertices[121] = VTXDEFAULT(_float3(-0.52, -0.75, -0.45), _float3(0.40, 0.90, -0.20), _float2(0.52, 0.69));
	vertices[122] = VTXDEFAULT(_float3(-0.52, -0.75, -0.45), _float3(0.00, 1.00, -0.07), _float2(0.52, 0.69));
	vertices[123] = VTXDEFAULT(_float3(-0.21, -0.65, 1.02), _float3(0.00, 1.00, -0.07), _float2(0.52, 0.31));
	vertices[124] = VTXDEFAULT(_float3(0.21, -0.65, 1.02), _float3(0.00, 1.00, -0.07), _float2(0.55, 0.31));
	vertices[125] = VTXDEFAULT(_float3(0.52, -0.75, -0.45), _float3(0.00, 1.00, -0.07), _float2(0.55, 0.69));
	vertices[126] = VTXDEFAULT(_float3(0.52, -0.75, -0.45), _float3(-0.40, 0.90, -0.20), _float2(0.55, 0.69));
	vertices[127] = VTXDEFAULT(_float3(0.21, -0.65, 1.02), _float3(-0.40, 0.90, -0.20), _float2(0.55, 0.31));
	vertices[128] = VTXDEFAULT(_float3(0.55, -0.40, 1.02), _float3(-0.40, 0.90, -0.20), _float2(0.57, 0.31));
	vertices[129] = VTXDEFAULT(_float3(1.35, -0.46, -0.40), _float3(-0.40, 0.90, -0.20), _float2(0.57, 0.69));
	vertices[130] = VTXDEFAULT(_float3(1.35, -0.46, -0.40), _float3(-0.77, 0.40, -0.49), _float2(0.57, 0.69));
	vertices[131] = VTXDEFAULT(_float3(0.55, -0.40, 1.02), _float3(-0.77, 0.40, -0.49), _float2(0.57, 0.31));
	vertices[132] = VTXDEFAULT(_float3(0.68, 0.00, 1.02), _float3(-0.77, 0.40, -0.49), _float2(0.60, 0.31));
	vertices[133] = VTXDEFAULT(_float3(1.67, 0.00, -0.40), _float3(-0.77, 0.40, -0.49), _float2(0.60, 0.69));
	vertices[134] = VTXDEFAULT(_float3(1.67, 0.00, -0.40), _float3(-0.77, -0.40, -0.49), _float2(0.60, 0.69));
	vertices[135] = VTXDEFAULT(_float3(0.68, 0.00, 1.02), _float3(-0.77, -0.40, -0.49), _float2(0.60, 0.31));
	vertices[136] = VTXDEFAULT(_float3(0.55, 0.40, 1.02), _float3(-0.77, -0.40, -0.49), _float2(0.62, 0.31));
	vertices[137] = VTXDEFAULT(_float3(1.35, 0.46, -0.40), _float3(-0.77, -0.40, -0.49), _float2(0.62, 0.69));
	vertices[138] = VTXDEFAULT(_float3(0.55, 0.40, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.63, 0.06));
	vertices[139] = VTXDEFAULT(_float3(0.41, 0.30, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.56, 0.11));
	vertices[140] = VTXDEFAULT(_float3(0.16, 0.48, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.52, 0.08));
	vertices[141] = VTXDEFAULT(_float3(0.21, 0.65, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.55, 0.01));
	vertices[142] = VTXDEFAULT(_float3(0.21, 0.65, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.55, 0.01));
	vertices[143] = VTXDEFAULT(_float3(0.16, 0.48, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.52, 0.08));
	vertices[144] = VTXDEFAULT(_float3(-0.16, 0.48, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.48, 0.08));
	vertices[145] = VTXDEFAULT(_float3(-0.21, 0.65, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.45, 0.01));
	vertices[146] = VTXDEFAULT(_float3(-0.21, 0.65, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.45, 0.01));
	vertices[147] = VTXDEFAULT(_float3(-0.16, 0.48, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.48, 0.08));
	vertices[148] = VTXDEFAULT(_float3(-0.41, 0.30, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.44, 0.11));
	vertices[149] = VTXDEFAULT(_float3(-0.55, 0.40, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.37, 0.06));
	vertices[150] = VTXDEFAULT(_float3(-0.55, 0.40, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.37, 0.06));
	vertices[151] = VTXDEFAULT(_float3(-0.41, 0.30, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.44, 0.11));
	vertices[152] = VTXDEFAULT(_float3(-0.50, 0.00, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.42, 0.16));
	vertices[153] = VTXDEFAULT(_float3(-0.68, 0.00, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.34, 0.16));
	vertices[154] = VTXDEFAULT(_float3(-0.68, 0.00, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.34, 0.16));
	vertices[155] = VTXDEFAULT(_float3(-0.50, 0.00, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.42, 0.16));
	vertices[156] = VTXDEFAULT(_float3(-0.41, -0.30, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.44, 0.20));
	vertices[157] = VTXDEFAULT(_float3(-0.55, -0.40, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.37, 0.25));
	vertices[158] = VTXDEFAULT(_float3(-0.55, -0.40, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.37, 0.25));
	vertices[159] = VTXDEFAULT(_float3(-0.41, -0.30, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.44, 0.20));
	vertices[160] = VTXDEFAULT(_float3(-0.16, -0.48, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.48, 0.23));
	vertices[161] = VTXDEFAULT(_float3(-0.21, -0.65, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.45, 0.30));
	vertices[162] = VTXDEFAULT(_float3(-0.21, -0.65, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.45, 0.30));
	vertices[163] = VTXDEFAULT(_float3(-0.16, -0.48, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.48, 0.23));
	vertices[164] = VTXDEFAULT(_float3(0.16, -0.48, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.52, 0.23));
	vertices[165] = VTXDEFAULT(_float3(0.21, -0.65, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.55, 0.30));
	vertices[166] = VTXDEFAULT(_float3(0.21, -0.65, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.55, 0.30));
	vertices[167] = VTXDEFAULT(_float3(0.16, -0.48, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.52, 0.23));
	vertices[168] = VTXDEFAULT(_float3(0.41, -0.30, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.56, 0.20));
	vertices[169] = VTXDEFAULT(_float3(0.55, -0.40, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.63, 0.25));
	vertices[170] = VTXDEFAULT(_float3(0.55, -0.40, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.63, 0.25));
	vertices[171] = VTXDEFAULT(_float3(0.41, -0.30, 1.02), _float3(0.00, 0.00, -1.00), _float2(0.56, 0.20));
	vertices[172] = VTXDEFAULT(_float3(0.50, 0.00, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.58, 0.16));
	vertices[173] = VTXDEFAULT(_float3(0.68, 0.00, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.66, 0.16));
	vertices[174] = VTXDEFAULT(_float3(0.68, 0.00, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.66, 0.16));
	vertices[175] = VTXDEFAULT(_float3(0.50, 0.00, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.58, 0.16));
	vertices[176] = VTXDEFAULT(_float3(0.41, 0.30, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.56, 0.11));
	vertices[177] = VTXDEFAULT(_float3(0.55, 0.40, 1.02), _float3(-0.00, -0.00, -1.00), _float2(0.63, 0.06));
	vertices[178] = VTXDEFAULT(_float3(0.41, 0.30, 0.78), _float3(-0.00, -0.00, -1.00), _float2(0.56, 0.11));
	vertices[179] = VTXDEFAULT(_float3(0.00, 0.00, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.50, 0.16));
	vertices[180] = VTXDEFAULT(_float3(0.16, 0.48, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.52, 0.08));
	vertices[181] = VTXDEFAULT(_float3(0.16, 0.48, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.52, 0.08));
	vertices[182] = VTXDEFAULT(_float3(0.00, 0.00, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.50, 0.16));
	vertices[183] = VTXDEFAULT(_float3(-0.16, 0.48, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.48, 0.08));
	vertices[184] = VTXDEFAULT(_float3(-0.16, 0.48, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.48, 0.08));
	vertices[185] = VTXDEFAULT(_float3(0.00, 0.00, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.50, 0.16));
	vertices[186] = VTXDEFAULT(_float3(-0.41, 0.30, 0.78), _float3(-0.00, -0.00, -1.00), _float2(0.44, 0.11));
	vertices[187] = VTXDEFAULT(_float3(-0.41, 0.30, 0.78), _float3(-0.00, -0.00, -1.00), _float2(0.44, 0.11));
	vertices[188] = VTXDEFAULT(_float3(0.00, 0.00, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.50, 0.16));
	vertices[189] = VTXDEFAULT(_float3(-0.50, 0.00, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.42, 0.16));
	vertices[190] = VTXDEFAULT(_float3(-0.50, 0.00, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.42, 0.16));
	vertices[191] = VTXDEFAULT(_float3(0.00, 0.00, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.50, 0.16));
	vertices[192] = VTXDEFAULT(_float3(-0.41, -0.30, 0.78), _float3(-0.00, -0.00, -1.00), _float2(0.44, 0.20));
	vertices[193] = VTXDEFAULT(_float3(-0.41, -0.30, 0.78), _float3(-0.00, -0.00, -1.00), _float2(0.44, 0.20));
	vertices[194] = VTXDEFAULT(_float3(0.00, 0.00, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.50, 0.16));
	vertices[195] = VTXDEFAULT(_float3(-0.16, -0.48, 0.78), _float3(-0.00, -0.00, -1.00), _float2(0.48, 0.23));
	vertices[196] = VTXDEFAULT(_float3(-0.16, -0.48, 0.78), _float3(-0.00, -0.00, -1.00), _float2(0.48, 0.23));
	vertices[197] = VTXDEFAULT(_float3(0.00, 0.00, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.50, 0.16));
	vertices[198] = VTXDEFAULT(_float3(0.16, -0.48, 0.78), _float3(-0.00, -0.00, -1.00), _float2(0.52, 0.23));
	vertices[199] = VTXDEFAULT(_float3(0.16, -0.48, 0.78), _float3(-0.00, -0.00, -1.00), _float2(0.52, 0.23));
	vertices[200] = VTXDEFAULT(_float3(0.00, 0.00, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.50, 0.16));
	vertices[201] = VTXDEFAULT(_float3(0.41, -0.30, 0.78), _float3(-0.00, -0.00, -1.00), _float2(0.56, 0.20));
	vertices[202] = VTXDEFAULT(_float3(0.41, -0.30, 0.78), _float3(-0.00, -0.00, -1.00), _float2(0.56, 0.20));
	vertices[203] = VTXDEFAULT(_float3(0.00, 0.00, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.50, 0.16));
	vertices[204] = VTXDEFAULT(_float3(0.50, 0.00, 0.78), _float3(-0.00, -0.00, -1.00), _float2(0.58, 0.16));
	vertices[205] = VTXDEFAULT(_float3(0.50, 0.00, 0.78), _float3(-0.00, -0.00, -1.00), _float2(0.58, 0.16));
	vertices[206] = VTXDEFAULT(_float3(0.00, 0.00, 0.78), _float3(0.00, 0.00, -1.00), _float2(0.50, 0.16));
	vertices[207] = VTXDEFAULT(_float3(0.41, 0.30, 0.78), _float3(-0.00, -0.00, -1.00), _float2(0.56, 0.11));
	vertices[208] = VTXDEFAULT(_float3(0.41, 0.30, 1.02), _float3(0.59, 0.81, 0.00), _float2(0.56, 0.11));
	vertices[209] = VTXDEFAULT(_float3(0.41, 0.30, 0.78), _float3(0.59, 0.81, 0.00), _float2(0.56, 0.11));
	vertices[210] = VTXDEFAULT(_float3(0.16, 0.48, 0.78), _float3(0.59, 0.81, 0.00), _float2(0.52, 0.08));
	vertices[211] = VTXDEFAULT(_float3(0.16, 0.48, 1.02), _float3(0.59, 0.81, 0.00), _float2(0.52, 0.08));
	vertices[212] = VTXDEFAULT(_float3(0.16, 0.48, 1.02), _float3(0.00, 1.00, 0.00), _float2(0.52, 0.08));
	vertices[213] = VTXDEFAULT(_float3(0.16, 0.48, 0.78), _float3(0.00, 1.00, 0.00), _float2(0.52, 0.08));
	vertices[214] = VTXDEFAULT(_float3(-0.16, 0.48, 0.78), _float3(0.00, 1.00, 0.00), _float2(0.48, 0.08));
	vertices[215] = VTXDEFAULT(_float3(-0.16, 0.48, 1.02), _float3(0.00, 1.00, 0.00), _float2(0.48, 0.08));
	vertices[216] = VTXDEFAULT(_float3(-0.16, 0.48, 1.02), _float3(-0.59, 0.81, 0.00), _float2(0.48, 0.08));
	vertices[217] = VTXDEFAULT(_float3(-0.16, 0.48, 0.78), _float3(-0.59, 0.81, 0.00), _float2(0.48, 0.08));
	vertices[218] = VTXDEFAULT(_float3(-0.41, 0.30, 0.78), _float3(-0.59, 0.81, 0.00), _float2(0.44, 0.11));
	vertices[219] = VTXDEFAULT(_float3(-0.41, 0.30, 1.02), _float3(-0.59, 0.81, 0.00), _float2(0.44, 0.11));
	vertices[220] = VTXDEFAULT(_float3(-0.41, 0.30, 1.02), _float3(-0.95, 0.31, 0.00), _float2(0.44, 0.11));
	vertices[221] = VTXDEFAULT(_float3(-0.41, 0.30, 0.78), _float3(-0.95, 0.31, 0.00), _float2(0.44, 0.11));
	vertices[222] = VTXDEFAULT(_float3(-0.50, 0.00, 0.78), _float3(-0.95, 0.31, 0.00), _float2(0.42, 0.16));
	vertices[223] = VTXDEFAULT(_float3(-0.50, 0.00, 1.02), _float3(-0.95, 0.31, 0.00), _float2(0.42, 0.16));
	vertices[224] = VTXDEFAULT(_float3(-0.50, 0.00, 1.02), _float3(-0.95, -0.31, 0.00), _float2(0.42, 0.16));
	vertices[225] = VTXDEFAULT(_float3(-0.50, 0.00, 0.78), _float3(-0.95, -0.31, 0.00), _float2(0.42, 0.16));
	vertices[226] = VTXDEFAULT(_float3(-0.41, -0.30, 0.78), _float3(-0.95, -0.31, 0.00), _float2(0.44, 0.20));
	vertices[227] = VTXDEFAULT(_float3(-0.41, -0.30, 1.02), _float3(-0.95, -0.31, 0.00), _float2(0.44, 0.20));
	vertices[228] = VTXDEFAULT(_float3(-0.41, -0.30, 1.02), _float3(-0.59, -0.81, 0.00), _float2(0.44, 0.20));
	vertices[229] = VTXDEFAULT(_float3(-0.41, -0.30, 0.78), _float3(-0.59, -0.81, 0.00), _float2(0.44, 0.20));
	vertices[230] = VTXDEFAULT(_float3(-0.16, -0.48, 0.78), _float3(-0.59, -0.81, 0.00), _float2(0.48, 0.23));
	vertices[231] = VTXDEFAULT(_float3(-0.16, -0.48, 1.02), _float3(-0.59, -0.81, 0.00), _float2(0.48, 0.23));
	vertices[232] = VTXDEFAULT(_float3(-0.16, -0.48, 1.02), _float3(0.00, -1.00, 0.00), _float2(0.48, 0.23));
	vertices[233] = VTXDEFAULT(_float3(-0.16, -0.48, 0.78), _float3(0.00, -1.00, 0.00), _float2(0.48, 0.23));
	vertices[234] = VTXDEFAULT(_float3(0.16, -0.48, 0.78), _float3(0.00, -1.00, 0.00), _float2(0.52, 0.23));
	vertices[235] = VTXDEFAULT(_float3(0.16, -0.48, 1.02), _float3(0.00, -1.00, 0.00), _float2(0.52, 0.23));
	vertices[236] = VTXDEFAULT(_float3(0.16, -0.48, 1.02), _float3(0.59, -0.81, 0.00), _float2(0.52, 0.23));
	vertices[237] = VTXDEFAULT(_float3(0.16, -0.48, 0.78), _float3(0.59, -0.81, 0.00), _float2(0.52, 0.23));
	vertices[238] = VTXDEFAULT(_float3(0.41, -0.30, 0.78), _float3(0.59, -0.81, 0.00), _float2(0.56, 0.20));
	vertices[239] = VTXDEFAULT(_float3(0.41, -0.30, 1.02), _float3(0.59, -0.81, 0.00), _float2(0.56, 0.20));
	vertices[240] = VTXDEFAULT(_float3(0.41, -0.30, 1.02), _float3(0.95, -0.31, 0.00), _float2(0.56, 0.20));
	vertices[241] = VTXDEFAULT(_float3(0.41, -0.30, 0.78), _float3(0.95, -0.31, 0.00), _float2(0.56, 0.20));
	vertices[242] = VTXDEFAULT(_float3(0.50, 0.00, 0.78), _float3(0.95, -0.31, 0.00), _float2(0.58, 0.16));
	vertices[243] = VTXDEFAULT(_float3(0.50, 0.00, 1.02), _float3(0.95, -0.31, 0.00), _float2(0.58, 0.16));
	vertices[244] = VTXDEFAULT(_float3(0.50, 0.00, 1.02), _float3(0.95, 0.31, 0.00), _float2(0.58, 0.16));
	vertices[245] = VTXDEFAULT(_float3(0.50, 0.00, 0.78), _float3(0.95, 0.31, 0.00), _float2(0.58, 0.16));
	vertices[246] = VTXDEFAULT(_float3(0.41, 0.30, 0.78), _float3(0.95, 0.31, 0.00), _float2(0.56, 0.11));
	vertices[247] = VTXDEFAULT(_float3(0.41, 0.30, 1.02), _float3(0.95, 0.31, 0.00), _float2(0.56, 0.11));
	m_pMesh->UnlockVertexBuffer();

	WORD* indices = 0;
	m_pMesh->LockIndexBuffer(0, (void**)&indices);

	indices[0] = 3;	indices[1] = 2;	indices[2] = 1;
	indices[3] = 3;	indices[4] = 1;	indices[5] = 0;
	indices[6] = 6;	indices[7] = 5;	indices[8] = 4;
	indices[9] = 9;	indices[10] = 8;	indices[11] = 7;
	indices[12] = 12;	indices[13] = 11;	indices[14] = 10;
	indices[15] = 15;	indices[16] = 14;	indices[17] = 13;
	indices[18] = 18;	indices[19] = 17;	indices[20] = 16;
	indices[21] = 22;	indices[22] = 21;	indices[23] = 20;
	indices[24] = 22;	indices[25] = 20;	indices[26] = 19;
	indices[27] = 25;	indices[28] = 24;	indices[29] = 23;
	indices[30] = 28;	indices[31] = 27;	indices[32] = 26;
	indices[33] = 31;	indices[34] = 30;	indices[35] = 29;
	indices[36] = 34;	indices[37] = 33;	indices[38] = 32;
	indices[39] = 37;	indices[40] = 36;	indices[41] = 35;
	indices[42] = 40;	indices[43] = 39;	indices[44] = 38;
	indices[45] = 43;	indices[46] = 42;	indices[47] = 41;
	indices[48] = 46;	indices[49] = 45;	indices[50] = 44;
	indices[51] = 49;	indices[52] = 48;	indices[53] = 47;
	indices[54] = 52;	indices[55] = 51;	indices[56] = 50;
	indices[57] = 55;	indices[58] = 54;	indices[59] = 53;
	indices[60] = 58;	indices[61] = 57;	indices[62] = 56;
	indices[63] = 61;	indices[64] = 60;	indices[65] = 59;
	indices[66] = 64;	indices[67] = 63;	indices[68] = 62;
	indices[69] = 67;	indices[70] = 66;	indices[71] = 65;
	indices[72] = 70;	indices[73] = 69;	indices[74] = 68;
	indices[75] = 73;	indices[76] = 72;	indices[77] = 71;
	indices[78] = 76;	indices[79] = 75;	indices[80] = 74;
	indices[81] = 79;	indices[82] = 78;	indices[83] = 77;
	indices[84] = 82;	indices[85] = 81;	indices[86] = 80;
	indices[87] = 85;	indices[88] = 84;	indices[89] = 83;
	indices[90] = 88;	indices[91] = 87;	indices[92] = 86;
	indices[93] = 91;	indices[94] = 90;	indices[95] = 89;
	indices[96] = 94;	indices[97] = 93;	indices[98] = 92;
	indices[99] = 97;	indices[100] = 96;	indices[101] = 95;
	indices[102] = 101;	indices[103] = 100;	indices[104] = 99;
	indices[105] = 101;	indices[106] = 99;	indices[107] = 98;
	indices[108] = 105;	indices[109] = 104;	indices[110] = 103;
	indices[111] = 105;	indices[112] = 103;	indices[113] = 102;
	indices[114] = 109;	indices[115] = 108;	indices[116] = 107;
	indices[117] = 109;	indices[118] = 107;	indices[119] = 106;
	indices[120] = 113;	indices[121] = 112;	indices[122] = 111;
	indices[123] = 113;	indices[124] = 111;	indices[125] = 110;
	indices[126] = 117;	indices[127] = 116;	indices[128] = 115;
	indices[129] = 117;	indices[130] = 115;	indices[131] = 114;
	indices[132] = 121;	indices[133] = 120;	indices[134] = 119;
	indices[135] = 121;	indices[136] = 119;	indices[137] = 118;
	indices[138] = 125;	indices[139] = 124;	indices[140] = 123;
	indices[141] = 125;	indices[142] = 123;	indices[143] = 122;
	indices[144] = 129;	indices[145] = 128;	indices[146] = 127;
	indices[147] = 129;	indices[148] = 127;	indices[149] = 126;
	indices[150] = 133;	indices[151] = 132;	indices[152] = 131;
	indices[153] = 133;	indices[154] = 131;	indices[155] = 130;
	indices[156] = 137;	indices[157] = 136;	indices[158] = 135;
	indices[159] = 137;	indices[160] = 135;	indices[161] = 134;
	indices[162] = 141;	indices[163] = 140;	indices[164] = 139;
	indices[165] = 141;	indices[166] = 139;	indices[167] = 138;
	indices[168] = 145;	indices[169] = 144;	indices[170] = 143;
	indices[171] = 145;	indices[172] = 143;	indices[173] = 142;
	indices[174] = 149;	indices[175] = 148;	indices[176] = 147;
	indices[177] = 149;	indices[178] = 147;	indices[179] = 146;
	indices[180] = 153;	indices[181] = 152;	indices[182] = 151;
	indices[183] = 153;	indices[184] = 151;	indices[185] = 150;
	indices[186] = 157;	indices[187] = 156;	indices[188] = 155;
	indices[189] = 157;	indices[190] = 155;	indices[191] = 154;
	indices[192] = 161;	indices[193] = 160;	indices[194] = 159;
	indices[195] = 161;	indices[196] = 159;	indices[197] = 158;
	indices[198] = 165;	indices[199] = 164;	indices[200] = 163;
	indices[201] = 165;	indices[202] = 163;	indices[203] = 162;
	indices[204] = 169;	indices[205] = 168;	indices[206] = 167;
	indices[207] = 169;	indices[208] = 167;	indices[209] = 166;
	indices[210] = 173;	indices[211] = 172;	indices[212] = 171;
	indices[213] = 173;	indices[214] = 171;	indices[215] = 170;
	indices[216] = 177;	indices[217] = 176;	indices[218] = 175;
	indices[219] = 177;	indices[220] = 175;	indices[221] = 174;
	indices[222] = 180;	indices[223] = 179;	indices[224] = 178;
	indices[225] = 183;	indices[226] = 182;	indices[227] = 181;
	indices[228] = 186;	indices[229] = 185;	indices[230] = 184;
	indices[231] = 189;	indices[232] = 188;	indices[233] = 187;
	indices[234] = 192;	indices[235] = 191;	indices[236] = 190;
	indices[237] = 195;	indices[238] = 194;	indices[239] = 193;
	indices[240] = 198;	indices[241] = 197;	indices[242] = 196;
	indices[243] = 201;	indices[244] = 200;	indices[245] = 199;
	indices[246] = 204;	indices[247] = 203;	indices[248] = 202;
	indices[249] = 207;	indices[250] = 206;	indices[251] = 205;
	indices[252] = 211;	indices[253] = 210;	indices[254] = 209;
	indices[255] = 211;	indices[256] = 209;	indices[257] = 208;
	indices[258] = 215;	indices[259] = 214;	indices[260] = 213;
	indices[261] = 215;	indices[262] = 213;	indices[263] = 212;
	indices[264] = 219;	indices[265] = 218;	indices[266] = 217;
	indices[267] = 219;	indices[268] = 217;	indices[269] = 216;
	indices[270] = 223;	indices[271] = 222;	indices[272] = 221;
	indices[273] = 223;	indices[274] = 221;	indices[275] = 220;
	indices[276] = 227;	indices[277] = 226;	indices[278] = 225;
	indices[279] = 227;	indices[280] = 225;	indices[281] = 224;
	indices[282] = 231;	indices[283] = 230;	indices[284] = 229;
	indices[285] = 231;	indices[286] = 229;	indices[287] = 228;
	indices[288] = 235;	indices[289] = 234;	indices[290] = 233;
	indices[291] = 235;	indices[292] = 233;	indices[293] = 232;
	indices[294] = 239;	indices[295] = 238;	indices[296] = 237;
	indices[297] = 239;	indices[298] = 237;	indices[299] = 236;
	indices[300] = 243;	indices[301] = 242;	indices[302] = 241;
	indices[303] = 243;	indices[304] = 241;	indices[305] = 240;
	indices[306] = 247;	indices[307] = 246;	indices[308] = 245;
	indices[309] = 247;	indices[310] = 245;	indices[311] = 244;
	m_pMesh->UnlockIndexBuffer();

	DWORD* attributeBuffer = 0;
	m_pMesh->LockAttributeBuffer(0, &attributeBuffer);

	for (int i = 0; i < 104; ++i)
	{
		attributeBuffer[i] = 0;
	}
	m_pMesh->UnlockAttributeBuffer();
	vector<DWORD> adjacencyBuffer(m_iNumPrimitive * 3);
	m_pMesh->GenerateAdjacency(0.f, &adjacencyBuffer[0]);

	m_pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&adjacencyBuffer[0],
		0, 0, 0
	);

	return S_OK;

}

HRESULT CMesh_SongShip::Initialize(void* pArg)
{
	return S_OK;
}

HRESULT CMesh_SongShip::Render_Mesh()
{
	DEVICE->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL);
	m_pMesh->DrawSubset(0);

	return S_OK;
}

CMesh_SongShip* CMesh_SongShip::Create()
{
	CREATE_PIPELINE(CMesh_SongShip);
}

CComponent* CMesh_SongShip::Clone(void* pArg)
{
	CLONE_PIPELINE(CMesh_SongShip);
}

void CMesh_SongShip::Free()
{
	__super::Free();

	delete this;
}