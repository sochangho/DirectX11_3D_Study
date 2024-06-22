
matrix World; // 물체들의 Transform 과 관련이 있다.
matrix View;  // 카메라
matrix Projection; //카메라

Texture2D Texture0;
float3 LightDir; //조명



struct VertexInput
{
	float4 position : POSITION;
    float2 uv : TEXTCOORD;
    float3 normal : NORMAL;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
    float2 uv : TEXTCOORD;
    float3 normal : NORMAL;
};

VertexOutput VS(VertexInput input)
{
	VertexOutput output;

    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
	
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) World);  // 이동과 관련된 것 무시
    
	return output;
}


SamplerState Sampler0
{
    AddressU = Wrap;
    AddressV = Wrap;
};


float4 PS(VertexOutput input) : SV_TARGET
{    
    float3 normal = normalize(input.normal);
    float3 light = normalize(-LightDir);
   
    
    
    return Texture0.Sample(Sampler0, input.uv) * dot(light, normal) * float4(0, 1, 0, 1) * 0.8f;
}



RasterizerState FillModeWireFrame
{
    FillMode = Wireframe;
};



technique11 T0
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}

    pass P1
    {
        SetRasterizerState(FillModeWireFrame);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }

};

