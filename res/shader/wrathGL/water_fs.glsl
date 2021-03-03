#version 330 core 

in vec4 clipSpace;
in vec2 texCoordsOut;

out vec4 fragColor;

uniform sampler2D DuDvMap;
uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform float moveFactor;

const float waveStrength = 0.02;

void main()
{
    //Convert to normalized device space
    vec2 normalizedDeviceSpace = ((clipSpace.xy / clipSpace.w) / 2.0) + 0.5;
    vec2 reflectTexCoords = vec2(normalizedDeviceSpace.x, -normalizedDeviceSpace.y);
    vec2 refractTexCoords = vec2(normalizedDeviceSpace.x, normalizedDeviceSpace.y);

    //Distort texture coords via DuDv-Map
    vec2 distortion1 = ((texture(DuDvMap, vec2(texCoordsOut.x + moveFactor, texCoordsOut.y)).rg * 2.0) - 1.0) * waveStrength;
    vec2 distortion2 = ((texture(DuDvMap, vec2(-texCoordsOut.x + moveFactor, texCoordsOut.y + moveFactor)).rg * 2.0) - 1.0) * waveStrength;
    vec2 totalDistortion = distortion1 + distortion2;

    reflectTexCoords += totalDistortion;
    reflectTexCoords.x = clamp(reflectTexCoords.x, 0.001, 0.999); //Clamp to prevent wrapping
    reflectTexCoords.y = clamp(reflectTexCoords.y, -0.999, -0.001);
    
    refractTexCoords += totalDistortion;
    refractTexCoords = clamp(refractTexCoords, 0.001, 0.999); 

    vec4 reflectColor = texture(reflectionTexture, reflectTexCoords);
    vec4 refractColor = texture(refractionTexture, refractTexCoords);

    vec4 outColor = mix(reflectColor, refractColor, 0.5);
    fragColor = mix(outColor, vec4(0.0, 0.3, 0.5, 1.0), 0.2);
}