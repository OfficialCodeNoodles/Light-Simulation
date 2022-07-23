#version 130

uniform vec2 uMousePosition; 

out vec2 localPosition; 
out vec2 mousePosition;

void main() {
    vec4 position = gl_Vertex; 

    gl_Position = gl_ModelViewProjectionMatrix * position;  
  
    localPosition = position.xy; 
    mousePosition = uMousePosition;
}