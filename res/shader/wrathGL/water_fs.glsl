#version 330 core 

in vec2 texCoords;
flat in vec3 color;
in vec3 fragPos;
flat in vec3 normal;

out vec4 fragColor;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

uniform vec3 viewPos;

const float ambientStrength = 0.2;
const float diffuseStrength = 0.85;
const float specularStrength = 0.3;
const vec3 lightDirection = vec3(-0.4, -1.0, -0.6);
const vec3 lightColor = vec3(1.0, 1.0, 1.0);
const float shininess = 4.0;

vec3 calculateLight()
{
    vec3 normal_n = normalize(normal);

    //Ambient
    vec3 ambient = ambientStrength * lightColor;

    //Diffuse
    vec3 lightDir = normalize(-lightDirection); 
    float diff = max(dot(normal_n, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * diff * lightColor;
    
    //Specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal_n);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    return (ambient + diffuse + specular);
}

void main()
{
    vec3 light = calculateLight();
    vec3 result = color * light;

    vec4 reflectColor = texture(reflectionTexture, texCoords);
    vec4 refractColor = texture(refractionTexture, texCoords);
    vec4 textures = mix(reflectColor, refractColor, 0.5);

    fragColor = textures;
}