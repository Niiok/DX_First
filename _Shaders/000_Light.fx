struct LightDesc
{
    float4 Ambient;
    float4 Specular;
    float3 Direction;
    float padding;
    float3 Position;
    //float padding2;
};

cbuffer CB_Light
{
    LightDesc GlobalLight;
};