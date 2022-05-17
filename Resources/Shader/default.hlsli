// 쉐이더 파일 hlsl 언어
// 단계별로 일감을 던져줌

// constant buffer 를 사용하고 register(b0) 를 사용할 것이고
// 이것을 offset0 이라고 부를 것이라는 의미
cbuffer TEST_B0 : register(b0)
{
    float4 offset0; // float4 : float가 4개 묶여있는 형태
};

cbuffer MATERIAL_PARAMS : register(b1)
{
    int int_0;
    int int_1;
    int int_2;
    int int_3;
    int int_4;
    float float_0;
    float float_1;
    float float_2;
    float float_3;
    float float_4;
};

Texture2D tex_0 : register(t0);
Texture2D tex_1 : register(t1);
Texture2D tex_2 : register(t2);
Texture2D tex_3 : register(t3);
Texture2D tex_4 : register(t4);

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

// 함수 - 정점 정보 변환
VS_OUT VS_Main(VS_IN input)
{
    //VS_OUT output = (VS_OUT)0;

    //output.pos = float4(input.pos, 1.f); // 처음 3가지 값은 그대로 받고 마지막 값만 1로 채우라
    //output.pos += offset0; // 따로 넘겨준 인자로 변화가 있기를 원함
    //output.color = input.color; // 받은 그대로를 반환
    //output.color += offset1;

    VS_OUT output = (VS_OUT)0;

    output.pos = float4(input.pos, 1.f);
    // output.pos += offset0;

    output.pos.x += float_0;
    output.pos.y += float_1;
    output.pos.z += float_2;

    output.color = input.color;
    output.uv = input.uv;

    return output;
}

// 함수 - 색상
float4 PS_Main(VS_OUT input) : SV_Target
{
    float4 color = tex_0.Sample(sam_0, input.uv);
    return color;
}