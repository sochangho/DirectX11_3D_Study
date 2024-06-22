#include "00. Global.fx"


float3 LightDir;       // 빛의 방향
float4 LightDiffuse;   // 빛의 색상
float4 MaterialDiffuse; // 빛을 받아주는 퍼센트

Texture2D DiffuseMap;


VertexOutput VS(VertexTextureNormal input)
{
    VertexOutput output;
    output.position = mul(input.position, W);
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) W);  // 노멀을 위치 뺀 나머지를 월드 기준으로 바꾼다.

    return output;
}


//Diffuse(분산광)
//물체의 표면에서 분산되어 눈으로 바로 들어오는 빛
//각도에 따라 밝기가 다르다 (Lambert 공식)

float4 PS(VertexOutput input) : SV_TARGET
{
    
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    
    
    float value = dot(normalize(-LightDir), normalize(input.normal));
   
    
    color = color * value * LightDiffuse * MaterialDiffuse;
    
    return color;
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
};
