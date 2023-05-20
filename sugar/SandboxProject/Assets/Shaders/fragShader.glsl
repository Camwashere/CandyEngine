#version 430 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

struct Material
{
    float metallic;
    float specular;
    float roughness;
};
struct Light
{
    vec3 position;
    vec3 color;
    float ambientStrength;
};

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 viewPos;


uniform Material material;
uniform Light light;

float constant = 1.0;
float linear = .009;
float quadratic = .032;
void main()
{

    vec4 objectColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.0);

    // ambient
    vec3 ambient = light.ambientStrength * light.color;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff*light.color;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.roughness);
    vec3 specular = material.specular * spec * light.color;


    // attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0/(1.0 + 0.009 * distance + .032*(distance*distance));
    //ambient *= attenuation;
    //diffuse *= attenuation;
    //specular *= attenuation;


    vec4 lightingValue = vec4(ambient+diffuse+specular, 1.0);

    FragColor = lightingValue * objectColor;
}