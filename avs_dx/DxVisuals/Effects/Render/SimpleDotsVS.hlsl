#ifndef AVS_SHADER
#define BIND_DOTS_POSITIONS t4
#define EFFECT_STATE 0
#endif

ByteAddressBuffer effectStates : register(t1);
StructuredBuffer<float2> positiions : register( BIND_DOTS_POSITIONS );

struct SimpleVertex
{
    float4 pos : SV_Position;
    float4 color : COLOR0;
};

SimpleVertex main( uint id : SV_VertexID )
{
    SimpleVertex r;
    r.pos = float4( positiions[ id ], 0, 1 );
    r.color = asfloat( effectStates.Load4( EFFECT_STATE ) );
    return r;
}