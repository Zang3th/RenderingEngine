#version 330 core 

flat in vec3 color;
in vec2 texCoords;
flat in float texIndex;
flat in vec3 fragPos;
flat in vec3 normal;

out vec4 fragColor;

uniform sampler2D textureArray[3];
uniform vec3 viewPos;

const float ambientStrength = 0.15;
const float diffuseStrength = 0.8;
const float specularStrength = 0.3;
const vec3 lightPos = vec3(150.0, 5000.0, 3500.0);
const vec3 lightColor = vec3(1.0, 1.0, 1.0);
const float shininess = 4.0;

vec3 calculateLight(vec4 texture)
{
    vec3 normal_n = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos); 
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    //Ambient
    vec3 ambient = ambientStrength * lightColor * texture.rgb;
    
    //Diffuse
    float diff = max(dot(lightDir, normal_n), 0.0);
    vec3 diffuse = diffuseStrength * diff * lightColor * texture.rgb;

    //Specular
    vec3 reflectDir = reflect(-lightDir, normal_n);
    float spec = pow(max(dot(normal_n, halfwayDir), 0.0), shininess);
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