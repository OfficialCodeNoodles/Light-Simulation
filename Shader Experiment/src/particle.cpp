#include "../hdr/particle.hpp"
#include "../hdr/render.hpp"

namespace engine {
	void Particle::generate() {
		position = gs::Vec2f(rand() % 1920, -(rand() % 1080) - 500.0f);
		velocity.y = static_cast<float>(rand() % 1000) / 50.0f;

		do {
			if (render::colorType == render::ColorType::Rainbow) {
				color.r = rand() % 255;
				color.g = rand() % 255;
				color.b = rand() % 255;
			}
			else {
				color = gs::Color(
					render::colorSliders[0].getPercentage(255.0f),
					render::colorSliders[1].getPercentage(255.0f),
					render::colorSliders[2].getPercentage(255.0f)
				);
			}
		} 
		while (color.r + color.g + color.b < 255.0f && 
			render::colorType == render::ColorType::Rainbow);
	}
	void Particle::generateFromMouse() {
		generate(); 

		position = gs::input::mousePosition; 
		velocity.x = (static_cast<float>(rand() % 1000) / 100.0f) - 5.0f; 
		velocity.y = -static_cast<float>(rand() % 1000) / 200.0f;
		velocity += gs::input::mouseChange; 
	}
	void Particle::update() {
		velocity.y += gravity;
		velocity.y = std::min(velocity.y, terminalVelocity); 

		position += velocity; 
	}

	bool Particle::isInBounds() const {
		if (position.y > render::window::windowSize.y + 1000.0f)
			return false; 

		return true;
	}

	Particle particles[mNumOfParticles];
	gs::Vec2f particlePositions[mNumOfParticles];
	gs::Vec3f particleColors[mNumOfParticles];
	float gravity = 0.08f;
	float terminalVelocity = 20.0f;
	GenerationType generationType = GenerationType::Automatic; 
	
	void initParticles() {
		for (int particleIndex = 0; particleIndex < mNumOfParticles;
			++particleIndex) {
			Particle& currentParticle = particles[particleIndex]; 

			currentParticle.generate(); 
		}
	}
	void updateParticles() {
		bool particleSpawned = false; 

		for (int particleIndex = 0; particleIndex < mNumOfParticles;
			++particleIndex) {
			Particle& currentParticle = particles[particleIndex]; 

			currentParticle.update(); 

			if (!currentParticle.isInBounds()) {
				if (generationType == GenerationType::Automatic)
					currentParticle.generate();
				else {
					if (gs::input::activeMouseClickL && ticks % 3 == 0 && 
						!particleSpawned) {
						currentParticle.generateFromMouse();
						particleSpawned = true; 
					}
				}
			}

			particlePositions[particleIndex] = currentParticle.position; 
			particleColors[particleIndex] = gs::Vec3f(
				static_cast<float>(currentParticle.color.r) / 255.0f, 
				static_cast<float>(currentParticle.color.g) / 255.0f,
				static_cast<float>(currentParticle.color.b) / 255.0f
			);
		}
	}
}