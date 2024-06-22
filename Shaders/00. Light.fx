#ifndef _LIGHT_FX_
#define _LIGHT_FX_

#include "00. Global.fx"

//////////
//struct//
//////////


struct LightDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
    float3 direction;
    float padding;
};


struct MaterialDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
};


///////////////
//ConstBuffer//
//////////////

cbuffer LightBuffer
{    
    LightDesc GlobalLight;
};

cbuffer MaterialBuffer
{
    MaterialDesc Material;
};

///////////////
//SRV/////////
//////////////

Texture2D DiffuseMap;
Texture2D SpecularMap;
Texture2D NormalMap;

///////////////
//Funtion/////////
//////////////


float4 ComputeLight(float3 normal, float2 uv, float3 worldPosition)
{
    float4 ambientColor = 0;
    float4 diffuseColor = 0;
    float4 specularColor = 0;
    float4 emissiveColor = 0;
    
    ////Ambient;
        {
        float4 color = GlobalLight.ambient * Material.ambient;
        ambientColor = DiffuseMap.Sample(LinearSampler, uv) * color;
    
    }
    ////Diffuse;
    
       {    
        float4 color = DiffuseMap.Sample(LinearSampler, uv);
        
        float value = dot(normalize(-GlobalLight.direction), normalize(normal));
  
        color = color * value * GlobalLight.diffuse * Material.diffuse;
    
        diffuseColor = color;
    }
    
    
    ////Specular;
    {  
        float3 R = reflect(normalize(GlobalLight.direction), normal);
        R = normalize(R);
    
        float3 cameraPosition = CameraPosition();
        float3 E = normalize(cameraPosition - worldPosition);
    
        float specularValue = saturate(dot(R, E)); //clamp (0~1);
        
        float specular = pow(specularValue, 20);
    
        float4 color = GlobalLight.specular * Material.specular * specular;
    
        specularColor = color;
    }
    ////Emissive;
    
    {
        float3 cameraPosition = CameraPosition();
        
        float3 E = normalize(cameraPosition - worldPosition);
    
        float value = saturate(dot(E, normal));
        
        float emissive = 1.0f - value;
    
        emissive = smoothstep(0.0f, 1.0f, emissive);
    
        emissive = pow(emissive, 2);
        
        float4 color = GlobalLight.emissive * Material.emissive * emissive;
        
        emissiveColor = color;
    }

    
    return ambientColor + diffuseColor + specularColor + emissiveColor;
    
}

void ComputNormalMapping(inout float3 normal, float3 tangent, float2 uv)
{
    float4 map = NormalMap.Sample(LinearSampler, uv); // [0,255] 범위에서 [0,1]로변환
    
    if (any(map.rbg) == false)
        return;
    
    float3 N = normalize(normal); //z
    float3 T = normalize(tangent); // x
    float3 B = normalize(cross(N, T)); //y
    
    float3x3 TBN = float3x3(T, B, N);
    
    //[0,1] 범위에서 [-1,1] 범위로 변환    
    float3 tangentSpaceNormal = (map.rgb * 2.0f - 1.0f);
    
    float3 worldNormal = mul(tangentSpaceNormal, TBN);
    
    normal = worldNormal;
}


#endif

