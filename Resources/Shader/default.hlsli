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
    output.pos += offset0; // ���� �Ѱ��� ���ڷ� ��ȭ�� �ֱ⸦ ����
    output.color = input.color; // ���� �״�θ� ��ȯ
    output.color += offset1;

    return output;
}

// �Լ� - ����
float4 PS_Main(VS_OUT input) : SV_Target
{
    return input.color;
}