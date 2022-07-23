#version 130

out vec4 position; 
out vec4 texCoord; 

void main() {
    position = gl_Vertex;
    gl_Position = gl_ModelViewProjectionMatrix * position;
    texCoord = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}