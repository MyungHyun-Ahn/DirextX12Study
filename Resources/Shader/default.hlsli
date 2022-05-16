// ���̴� ���� hlsl ���
// �ܰ躰�� �ϰ��� ������

// constant buffer �� ����ϰ� register(b0) �� ����� ���̰�
// �̰��� offset0 �̶�� �θ� ���̶�� �ǹ�
cbuffer TEST_B0 : register(b0)
{
    float4 offset0; // float4 : float�� 4�� �����ִ� ����
};

cbuffer TEST_B1 : register(b1)
{
    float4 offset1;
};

Texture2D tex_0 : register(t0);

SamplerState sam_0 : register(s0);

struct VS_IN
{
    float3 pos : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

// �Լ� - ���� ���� ��ȯ
VS_OUT VS_Main(VS_IN input)
{
    //VS_OUT output = (VS_OUT)0;

    //output.pos = float4(input.pos, 1.f); // ó�� 3���� ���� �״�� �ް� ������ ���� 1�� ä���
    //output.pos += offset0; // ���� �Ѱ��� ���ڷ� ��ȭ�� �ֱ⸦ ����
    //output.color = input.color; // ���� �״�θ� ��ȯ
    //output.color += offset1;

    VS_OUT output = (VS_OUT)0;

    output.pos = float4(input.pos, 1.f);
    output.color = input.color;
    output.uv = input.uv;

    return output;
}

// �Լ� - ����
float4 PS_Main(VS_OUT input) : SV_Target
{
    float4 color = tex_0.Sample(sam_0, input.uv);
    return color;
}