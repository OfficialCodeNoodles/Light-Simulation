#include "../hdr/render.hpp"

int ticks = 0; 

void updateEvents() {
	engine::render::window::update(); 

	engine::updateParticles(); 
	engine::render::updateMenu(); 
}
void updateGraphics() {
	engine::render::window::begin(); 

	engine::render::shader.setUniformArray(
		"uParticlePositions", engine::particlePositions, mNumOfParticles
	);  
	engine::render::shader.setUniformArray(
		"uParticleColors", engine::particleColors, mNumOfParticles
	);
	engine::render::shader.setUniform(
		"uLightStrength", 
		engine::render::lightStregthSlider.getPercentage(600.0f)
	);
	engine::render::window::winmain->draw(
		engine::render::box, &engine::render::shader
	);
	engine::render::renderParticles(); 
	engine::render::renderMenu();

	engine::render::window::end(); 
}

int main() {
	srand(time(0)); 
	gs::util::Clock timer; 

	engine::render::window::create(true); 
	engine::render::loadAssets(); 
	engine::initParticles(); 

	while (engine::render::window::winmain->isOpen()) {
		timer.begin(); 

		updateEvents(); 

		if (engine::render::window::virtualFramerate !=
			engine::render::window::framerate) {
			if (ticks % (engine::render::window::framerate /
				engine::render::window::virtualFramerate) == 0)
				updateGraphics(); 
		}
		else
			updateGraphics(); 

		timer.end(); 
		timer.wait(engine::render::window::framerate); 
		++ticks; 
	}

	engine::render::window::close(); 

	return 0; 
}