#version 330 core 

flat in vec3 color;
in vec2 texCoords;
flat in float texIndex;
in vec3 fragPos;
flat in vec3 normal;

out vec4 fragColor;

uniform sampler2D textureArray[4];
uniform vec3 viewPos;

const float ambientStrength = 0.25;
const float diffuseStrength = 0.9;
const float specularStrength = 0.3;
const vec3 lightDirection = vec3(-0.4, -1.0, -0.6);
const vec3 lightColor = vec3(1.0, 1.0, 1.0);
const float shininess = 4.0;

vec3 calculateLight(vec4 texture)
{
    vec3 normal_n = normalize(normal);

    //Ambient
    vec3 ambient = ambientStrength * lightColor * texture.rgb;

    //Diffuse
    vec3 lightDir = normalize(-lightDirection); 
    float diff = max(dot(normal_n, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * diff * lightColor * texture.rgb;
    
    //Specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal_n);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor * texture.rgb;

    return (ambient + diffuse + specular);
}

void main()
{
    //Get texture
    int index = int(texIndex);
    vec4 texture = texture(textureArray[index], texCoords);

    //Calculate light
    vec3 light = calculateLight(texture);
    vec3 result = color * light;
    
    fragColor = vec4(result, 1.0f);
}