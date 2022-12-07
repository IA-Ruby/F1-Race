#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 normal;
in vec3 color;

uniform vec3 LightPos;
uniform vec3 ViewPos;
  
void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;
  	
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
            
    float specularStrength = 0.7;
    vec3 viewDir = normalize(ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular) * color;
    FragColor = vec4(result, 1.0);
}