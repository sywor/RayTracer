//--------------------------------------------------------------------------------------
// BasicCompute.fx
// Direct3D 11 Shader Model 5.0 Demo
// Copyright (c) Stefan Petersson, 2012
//--------------------------------------------------------------------------------------


RWTexture2D<float4> output : register(u0);

[numthreads(32, 32, 1)]
void main( uint3 threadID : SV_DispatchThreadID )
{
	float4 white = float4(1.0f,1.0f,1.0f,1.0f);
	float m = -1.f;
	float k = 1.f / 400.f;
	float4 position = float4(0, 0, -1.0, 0);

	//float4 pixelPosition = float4(threadID.x * k + m, threadID.y * k + m, 0, 1);
	float4 pixelPosition = float4(threadID.x * k + m, threadID.y * k + m, 0, 1);
	float4 pixelNormal =  abs( normalize( pixelPosition - position ) );
	output[threadID.xy] = pixelNormal;

	//output[threadID.xy] = float4(float3(1,0,1) * (1 - length(threadID.xy - float2(400, 400)) / 400.0f), 1);
	//output[threadID.xy] = float4(threadID.xyz * k + float3(m, m, m), 1.f);
}