float4x4 translationMatrix;

float4 main(float3 pos : Position) : SV_Position
{
    // identity matrix for testing if translationMatrix is working proper.
    float4x4 test = float4x4(1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 1.0f);

    float4 worldPosition = mul(translationMatrix, float4(pos, 1.0f));
    return worldPosition;
}