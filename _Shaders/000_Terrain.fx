	struct BrushDesc
{
    float4 Color;
    float3 Location;
    uint Type;
    uint Range;
};

cbuffer CB_TerrainBrush
{
    BrushDesc TerrainBrush;
};

float3 GetBrushColor(float3 wPosition)
{
    [flatten]
    if (TerrainBrush.Type == 0)
        return float3(0, 0, 0);
        
    [flatten]
    if (TerrainBrush.Type == 1)
    {
        if (
            (wPosition.x >= (TerrainBrush.Location.x - TerrainBrush.Range)) &&
            (wPosition.x <= (TerrainBrush.Location.x + TerrainBrush.Range)) &&
            (wPosition.z >= (TerrainBrush.Location.z - TerrainBrush.Range)) &&
            (wPosition.z <= (TerrainBrush.Location.z + TerrainBrush.Range))
            )
        {
            return TerrainBrush.Color;
        }
    }
    
    [flatten]
    if (TerrainBrush.Type == 2)
    {
        float dx = wPosition.x - TerrainBrush.Location.x;
        float dz = wPosition.z - TerrainBrush.Location.z;
        
        float dist = sqrt(dx * dx + dz * dz);

        [flatten]
        if (dist <= TerrainBrush.Range)
            return TerrainBrush.Color;
    }

    return float3(0, 0, 0);

}