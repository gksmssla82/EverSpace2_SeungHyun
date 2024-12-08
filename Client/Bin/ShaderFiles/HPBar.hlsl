

// matrix
matrix world;
matrix view;
matrix proj;



float				g_Ratio;
// textureCUBE

texture		g_Texture;
sampler		DefaultSampler = sampler_state 
{	
	texture = g_Texture;
	/*ADDRESSU = WRAP;
	ADDRESSV = WRAP;*/

	MINFILTER = LINEAR;
	MAGFILTER = LINEAR;
	MIPFILTER = LINEAR;	
};



struct VS_IN
{
	float3 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

VS_OUT VS_MAIN(/* ����*/VS_IN In)
{
	VS_OUT		Out;

	vector		vPosition = mul(float4(In.vPosition, 1.f), world);
	vPosition = mul(vPosition, view);
	vPosition = mul(vPosition, proj);

	Out.vPosition = vPosition;
	Out.vTexUV = In.vTexUV;

	return Out;
}

/* ���� ������ ���ؼ� w�����⿬��. */
/* ����Ʈ ��ȯ.  */
/* �����Ͷ������Ѵ�. == �ȼ��� �����Ѵ�. */
struct PS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;	
};


vector PS_MAIN(PS_IN In) : COLOR0
{
	vector			vColor;

	//-1, 0, 1
	float Color = sign(g_Ratio - In.vTexUV.x);
	Color = max(0, Color);

	vColor = float4(Color, Color, Color, 1.f);
	

	return vColor;
}

technique			DefaultTechnique
{
	pass Default
	{

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();

		
	}
}


