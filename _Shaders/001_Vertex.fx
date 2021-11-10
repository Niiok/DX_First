
struct VertexInput
{
	float4 Position : position0;
};

struct VertexOutput
{
	float4 Position : SV_Position0;
};

VertexOutput VS(VertexInput input)
{
	VertexOutput output;
	output.Position = input.Position;
	return output;
}

float4 PS(VertexOutput input) : SV_Target0
{
	return float4(1,0,0,1);
}

technique11 T0
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(vs_5_0, PS()));
	}
};