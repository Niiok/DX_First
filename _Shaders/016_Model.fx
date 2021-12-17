
//matrix World;
//matrix View;
//matrix Projection;

//Texture2D Map;
#include "000_Header.fx"
#include "000_Light.fx"
#include "000_Model.fx"

struct VertexOutput
{
	float4 Position : SV_Position0;
    float3 Normal : Normal0;
    float2 Uv : Uv0;
    //float3 Color : Color0;
};

//VertexOutput VS(VertexModel input)
//{
//	VertexOutput output;    
//    SetModelWorld(World, input);
    
//    output.Position = WorldPosition(input.Position);
//    //output.Color = GetBrushColor(output.Position.xyz);
//    //output.wPosition = output.Position;
//    output.Position = ViewProjection(output.Position); 
//    output.Normal = WorldNormal(input.Normal);
//    output.Uv = input.Uv;
    
//	return output;
//}


float4 PS(VertexOutput input) : SV_Target0
{
    //return float4(input.Normal * 0, 5f + 0.5f, 1);
    
    float4 diffuse = DiffuseMap.Sample(LinearSampler, input.Uv);
    float3 normal = normalize(input.Normal);
    float NdotL = saturate(dot(normal, -GlobalLight.Direction));
    
    //return diffuse * NdotL + float4(input.Color, 1);
    return diffuse * NdotL;
}

RasterizerState RS
{
    FillMode = Wireframe;
};

technique11 T0
{
    P_VP(P0, VS_Model, PS)
    P_VP(P1, VS_Model, PS)

    P_RS_VP(P3, RS, VS_Model, PS)
    P_RS_VP(P4, RS, VS_Model, PS)
};