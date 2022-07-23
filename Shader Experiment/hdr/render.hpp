#pragma once

//Dependencies
#include "particle.hpp"

namespace engine {
	namespace render {
		namespace window {
			extern const gs::Vec2i windowSize; 

			extern sf::RenderWindow* winmain; 
			extern bool isFullscreen;

			extern int framerate; 
			extern int virtualFramerate; 

			void create(bool fullscreen);
			void initStates(); 
			void update(); 
			void close(); 

			void begin(gs::Color color = gs::Color());
			void end(); 
		}

		extern sf::RectangleShape box; 
		extern sf::Shader shader; 
		extern sf::Texture texture;
		extern sf::Sprite sprite; 
		extern sf::RectangleShape particleBox; 
		extern sf::Font font; 
		extern gs::Text text; 
		extern bool menuOpen; 
		extern gs::Menu menu; 
		extern gs::Button openMenuButton;
		extern gs::Button generationTypeButton;
		extern gs::Color uiBgColor0;
		extern gs::Color uiOutlineColor0;
		extern gs::Color inactiveTextColor; 
		extern sf::RectangleShape menuBackground; 
		extern float menuWidth; 
		extern gs::Button colorTypeButton; 
		enum class ColorType { Rainbow, Custom };
		extern ColorType colorType; 
		extern gs::Slider colorSliders[3];
		extern gs::Slider lightStregthSlider; 
		extern gs::Slider gravityStrengthSlider; 
		extern gs::Slider terminalVelocitySlider; 
		extern gs::Button changeFpsButton;
		extern gs::Button exitButton;

		void loadAssets(); 
		void handleAssets(); 

		void updateMenu(); 

		void renderText(
			const std::string& string, gs::Vec2f position, float scale,
			gs::Color fillColor = gs::Color::White,
			float outlineThickness = 0.0f, gs::Color outlineColor = gs::Color()
		); 
		void renderParticle(const Particle& particle); 
		void renderParticles();
		void renderMenu(); 
	}
}