#version 330 core
out vec3 FragPos;
out vec3 normal;
out vec3 color;

void main(void){
    normal      = mat3(transpose(inverse(mat4(1.0)))) * gl_Normal;
    color       = vec3(gl_Color);
    
    FragPos = vec3(mat4(1.0) * gl_Vertex);

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
