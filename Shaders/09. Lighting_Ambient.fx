#include "00. Global.fx"

//�ڿ��� : ������ ���� ���� ǥ���Ѵ�. 

// Ambient (�ֺ���/ ȯ�汤)
// ������ �ݻ縦 ���ļ� ������ �Һи��� ��
// ������ ���� ������ ǥ��

float4 LightAmbient; //������ü�� ������ ��Ÿ����.
float4 MaterialAmbient; //��ü�� ���� �󸶳� �޾Ƶ��̴���


VertexOutput VS(VertexTextureNormal input)
{
    VertexOutput output;
    output.position = mul(input.position, W);
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) W);

    return output;
}

Texture2D Texture0;

float4 PS(VertexOutput input) : SV_TARGET
{
    float4 color = LightAmbient * MaterialAmbient;
    
    return Texture0.Sample(LinearSampler, input.uv) * color;
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
};
