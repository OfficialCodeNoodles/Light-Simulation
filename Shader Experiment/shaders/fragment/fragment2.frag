#version 460 core

const int numOfParticles = 100; 

layout (location = 0) out vec4 pixelColor;

uniform sampler2D uTexture;
uniform vec2 uParticlePositions[numOfParticles];
uniform vec3 uParticleColors[numOfParticles]; 
uniform float uLightStrength; 

in vec4 position; 
in vec4 texCoord; 

struct Particle {
    vec2 position; 
    vec3 color; 
};

float distance(vec2 p1, vec2 p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)); 
}
vec3 getLightColor(in Particle particle) {
    const vec3 diffuseColor = particle.color; 
    const float scaler = uLightStrength; 

    float brightness; 

    brightness = scaler - distance(position.xy, particle.position); 
    brightness = max(brightness, 0.0); 

    return diffuseColor * (brightness / scaler); 
}

void main() {
    vec3 ambientColor = vec3(0.1, 0.1, 0.12); 
    vec3 diffuseColor = ambientColor; 

    pixelColor = texture2D(uTexture, texCoord.xy);

    for (int particleIndex = 0; particleIndex < numOfParticles; 
        ++particleIndex) {
        Particle currentParticle; 

        currentParticle.position = uParticlePositions[particleIndex];
        currentParticle.color = uParticleColors[particleIndex]; 

        vec3 localDiffuseColor = getLightColor(currentParticle);

        diffuseColor = vec3(
            max(diffuseColor.r, localDiffuseColor.r),
            max(diffuseColor.g, localDiffuseColor.g),
            max(diffuseColor.b, localDiffuseColor.b)
        );
    }

    pixelColor *= vec4(diffuseColor, 1.0); 
}