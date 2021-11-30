cbuffer CB_PerFrame
{
    matrix View;
    matrix ViewInverse;
    matrix Projection;
    matrix VP;
    
    float Time;
};

cbuffer CB_World
{
    matrix World;
};

float3 LightDirection;

Texture2D DiffuseMap;
Texture2D SpeculatMap;
Texture2D NormalMap;


SamplerState Sampler;

struct Vertex
{
    float4 Position : POSITION0;
};
struct VertexNormal
{
    float4 Position : POSITION0;
    float3 Normal : NORMAL0;
};
struct VertexColor
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
};
struct VertexColorNormal
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
    float3 Normal : NORMAL0;
};

 

struct VertexTexture
{
    float4 Position : POSITION0;
    float2 Uv : TEXCOORD0;
};
struct VertexTextureColor
{
    float4 Position : POSITION0;
    float2 Uv : TEXCOORD0;
    float4 Color : COLOR0;
};
struct VertexTextureColorNormal
{
    float4 Position : POSITION0;
    float2 Uv : TEXCOORD0;
    float4 Color : COLOR0;
    float3 Normal : NORMAL0;
};
struct VertexTextureNormal
{
    float4 Position : POSITION0;
    float2 Uv : TEXCOORD0;
    float3 Normal : NORMAL0;
};

 

struct VertexColorTextureNormal
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
    float2 Uv : TEXCOORD0;
    float3 Normal : NORMAL0;
};
struct VertexTextureNormalBlend
{
    float4 Position : POSITION0;
    float2 Uv : TEXCOORD0;
    float3 Normal : NORMAL0;
    float4 BlendIndices : BLENDINDICES0;
    float4 BlendWeights : BLENDWEIGHTS0;
};
struct VertexTextureNormalTangent
{
    float4 Position : POSITION0;
    float2 Uv : TEXCOORD0;
    float3 Normal : NORMAL0;
    float3 Tangent : TANGENT0;
};
struct VertexTextureNormalTangentBlend
{
    float4 Position : POSITION0;
    float2 Uv : TEXCOORD0;
    float3 Normal : NORMAL0;
    float4 BlendIndices : BLENDINDICES0;
    float4 BlendWeights : BLENDWEIGHTS0;
};

 

float4 WorldPosition(float4 position)
{
    return mul(position, World);
}

float4 ViewProjection(float4 position)
{
    position = mul(position, View);
    return mul(position, Projection);
}


float3 WorldNormal(float3 normal)
{
    return mul(normal, (float3x3) World);
}