#pragma once

//Dependencies
#include "resources.hpp"

namespace engine {
	struct Particle {
		gs::Vec2f position;
		gs::Vec2f velocity;
		gs::Color color;

		void generate();
		void generateFromMouse(); 
		void update();

		bool isInBounds() const;
	}; 

	extern Particle particles[mNumOfParticles]; 
	extern gs::Vec2f particlePositions[mNumOfParticles];
	extern gs::Vec3f particleColors[mNumOfParticles];
	extern float gravity; 
	extern float terminalVelocity;
	enum class GenerationType { Automatic, Mouse };
	extern GenerationType generationType; 

	void initParticles(); 
	void updateParticles(); 
}