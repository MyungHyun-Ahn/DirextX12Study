// ���̴� ���� hlsl ���
// �ܰ躰�� �ϰ��� ������

struct VS_IN
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float4 color : COLOR;
};

// �Լ� - ���� ���� ��ȯ
VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    output.pos = float4(input.pos, 1.f); // ó�� 3���� ���� �״�� �ް� ������ ���� 1�� ä���
    output.color = input.color; // ���� �״�θ� ��ȯ

    return output;
}

// �Լ� - ����
float4 PS_Main(VS_OUT input) : SV_Target
{
    return input.color;
}