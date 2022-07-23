#version 460 core

layout (location = 0) out vec4 pixelColor;

in vec2 localPosition; 
in vec2 mousePosition; 

float distance(vec2 p1, vec2 p2) {
    return sqrt(pow(p1.x - p2, 2) + pow(p1.y - p2, 2)); 
}

void main() {
    if (distance(localPosition, mousePosition) < 200.0)
        discard; 

    pixelColor = vec4(1.0, 1.0, 1.0, 1.0);
}