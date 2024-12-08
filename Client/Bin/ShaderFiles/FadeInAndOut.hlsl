

// matrix
matrix world;
matrix view;
matrix proj;

// textureCUBE

texture		g_Texture;
sampler		DefaultSampler = sampler_state 
{	
	texture = g_Texture;
    AddressU = clamp;
    AddressV = clamp;

	MINFILTER = LINEAR;
	MAGFILTER = LINEAR;
	MIPFILTER = None;	
};

//fade out Offset
float		FadeOuteOffSet = 1.f;//Set Value from outside


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

	vColor = tex2D(DefaultSampler, In.vTexUV);
	vColor.w = 1.f;	

	vColor *= FadeOuteOffSet;

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


