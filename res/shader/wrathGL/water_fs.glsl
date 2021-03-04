#version 330 core 

in vec3 normal;
in vec3 toCameraVector;
in vec3 fragPos;
in vec4 clipSpace;
in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D DuDvMap;
uniform sampler2D waterNormalMap;
uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform float moveFactor;
uniform vec3 viewPos;

const float waveStrength = 0.01;
const float specularStrength = 0.2;
const vec3 lightDirection = vec3(-0.4, -1.0, -0.6);
const vec3 lightColor = vec3(1.0, 1.0, 1.0);
const float shininess = 20.0;

void main()
{
    //Convert to normalized device space
    vec2 normalizedDeviceSpace = ((clipSpace.xy / clipSpace.w) / 2.0) + 0.5;
    vec2 reflectTexCoords = vec2(normalizedDeviceSpace.x, -normalizedDeviceSpace.y);
    vec2 refractTexCoords = vec2(normalizedDeviceSpace.x, normalizedDeviceSpace.y);

    //Distort texture coords via DuDv-Map
    vec2 distortedTexCoords = texture(DuDvMap, vec2(texCoords.x + moveFactor, texCoords.y)).rg * 0.1;
    distortedTexCoords = texCoords + vec2(distortedTexCoords.x, distortedTexCoords.y + moveFactor);
    vec2 totalDistortion = (texture(DuDvMap, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength;

    reflectTexCoords += totalDistortion;
    reflectTexCoords.x = clamp(reflectTexCoords.x, 0.001, 0.999); //Clamp to prevent wrapping
    reflectTexCoords.y = clamp(reflectTexCoords.y, -0.999, -0.001);
    
    refractTexCoords += totalDistortion;
    refractTexCoords = clamp(refractTexCoords, 0.001, 0.999); 

    //Sample from reflect/refract textures at distorted coordinates
    vec4 reflectColor = texture(reflectionTexture, reflectTexCoords);
    vec4 refractColor = texture(refractionTexture, refractTexCoords);

    //Fresnel effect
    vec3 viewVector = normalize(toCameraVector);
    float refractiveFactor = dot(viewVector, normal);
    refractiveFactor = pow(refractiveFactor, 1.5); //Reflectiveness of the water

    //Sample from normal map
    vec4 normalMapColor = texture(waterNormalMap, distortedTexCoords);
    vec3 mappedNormal = vec3(normalMapColor.r * 2.0 - 1.0, normalMapColor.b, normalMapColor.g * 2.0 - 1.0);
    mappedNormal = normalize(mappedNormal);

    //Calculate specular light
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(normalize(lightDirection), mappedNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    vec4 outColor = mix(reflectColor, refractColor, refractiveFactor);
    fragColor = mix(outColor, vec4(0.0, 0.3, 0.5, 1.0), 0.2) + vec4(specular, 0.0);
}