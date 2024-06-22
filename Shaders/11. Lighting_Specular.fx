#include "00. Global.fx"


float3 LightDir;       // 빛의 방향

float4 LightSpecular;
float4 MaterialSpecular;

Texture2D DiffuseMap;


MeshOutput VS(VertexTextureNormal input)
{
    MeshOutput output;
    output.position = mul(input.position, W);
    output.worldPosition = input.position;
    output.position = mul(output.position, VP);
         
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) W);

    return output;
}


//Specular(반사광)
//한방향으로 완전히 반사되는 빛(Phong)

float4 PS(MeshOutput input) : SV_TARGET
{
    //반사 
    //specular
    //float R = LightDir - (2 * input.normal * dot(LightDir, input.normal));
    float3 R = reflect(normalize(LightDir), input.normal);   
    R = normalize(R);
    
    float3 cameraPosition = -V._41_42_43;      
    float3 E = normalize(cameraPosition - input.worldPosition);         
    
    float specularValue = saturate(dot(R, E)); //clamp (0~1);
    float specular = pow(specularValue, 10);
    
    float4 color = LightSpecular * MaterialSpecular * specular;
    
    return color;
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
};
