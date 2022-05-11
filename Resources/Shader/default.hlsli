// 쉐이더 파일 hlsl 언어
// 단계별로 일감을 던져줌

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

// 함수 - 정점 정보 변환
VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    output.pos = float4(input.pos, 1.f); // 처음 3가지 값은 그대로 받고 마지막 값만 1로 채우라
    output.color = input.color; // 받은 그대로를 반환

    return output;
}

// 함수 - 색상
float4 PS_Main(VS_OUT input) : SV_Target
{
    return input.color;
}