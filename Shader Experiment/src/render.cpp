#include "../hdr/render.hpp"

namespace engine {
	namespace render {
		namespace window {
			const gs::Vec2i windowSize = gs::Vec2i(1920, 1080);

			sf::RenderWindow* winmain = nullptr;
			bool isFullscreen;

			int framerate = 60;
			int virtualFramerate = 30;

			void create(bool fullscreen) {
				isFullscreen = fullscreen; 

				if (winmain == nullptr) {
					winmain = new sf::RenderWindow(
						sf::VideoMode(windowSize.x, windowSize.y),
						"Shader Experiment", mGetStyle(isFullscreen)
					);
				}
				else {
					winmain->create(
						sf::VideoMode(windowSize.x, windowSize.y),
						"Shader Experiment", mGetStyle(isFullscreen)
					);
				}

				initStates(); 
			}
			void initStates() {
				gs::input::setWindow(winmain); 

				winmain->setSize(gs::Vec2u(
					sf::VideoMode::getDesktopMode().width, 
					sf::VideoMode::getDesktopMode().height
				));
			}
			void update() {
				sf::Event action;

				gs::input::updateInputs(); 

				while (winmain->pollEvent(action)) {
					gs::input::updateEvents(action); 

					switch (action.type) {
					case sf::Event::Closed:
						winmain->close(); 
						break; 
					case sf::Event::KeyPressed:
						switch (action.key.code) {
						case sf::Keyboard::F11:
							create(!isFullscreen);
							break; 
						case sf::Keyboard::Escape:
							winmain->close(); 
							break; 
						}
						break; 
					}
				}
			}
			void close() {
				winmain->close(); 
			}

			void begin(gs::Color color) {
				winmain->clear(color);
			}
			void end() {
				winmain->display(); 
			}
		}

		sf::RectangleShape box;
		sf::Shader shader;
		sf::Texture texture;
		sf::Sprite sprite;
		sf::RectangleShape particleBox; 
		sf::Font font;
		gs::Text text;
		bool menuOpen = false;
		gs::Menu menu;
		gs::Button openMenuButton;
		gs::Button generationTypeButton; 
		gs::Color uiBgColor0 = gs::Color(80, 80, 90, 150);
		gs::Color uiOutlineColor0 = gs::Color(150, 150, 155);
		gs::Color inactiveTextColor = gs::Color(210, 210, 210);
		sf::RectangleShape menuBackground;
		float menuWidth = 400.0f; 
		gs::Button colorTypeButton;
		ColorType colorType = ColorType::Rainbow;
		gs::Slider colorSliders[3];
		gs::Slider lightStregthSlider;
		gs::Slider gravityStrengthSlider;
		gs::Slider terminalVelocitySlider;
		gs::Button changeFpsButton;
		gs::Button exitButton;

		void loadAssets() {
			const int vertexShaderIndex = 2; 
			const int fragmentShaderIndex = 2; 

			shader.loadFromFile(
				"./shaders/vertex/vertex" + std::to_string(vertexShaderIndex)
					+ ".vert",
				"./shaders/fragment/fragment" + std::to_string(
					fragmentShaderIndex) + ".frag"
			);
			texture.loadFromFile("wall.png");
			font.loadFromFile("font.ttf"); 
		
			handleAssets(); 
		}
		void handleAssets() {
			//box
			box.setSize(gs::Vec2f(window::windowSize.x, window::windowSize.y));
			box.setTexture(&texture);

			//text
			text.setFont(font); 

			//openMenuButton
			openMenuButton.setSize(15.0f, 120.0f);
			openMenuButton.setInactiveFillColor(uiBgColor0); 
			openMenuButton.setOutlineThickness(3.0f); 
			openMenuButton.setOutlineColor(uiOutlineColor0); 
			openMenuButton.setScaleModifiers(1.0f);
			menu.add(&openMenuButton); 

			//generationTypeButton
			generationTypeButton.setSize(320.0f, 60.0f);
			generationTypeButton.setPosition(1560.0f, 150.0f);
			generationTypeButton.setFont(font);
			generationTypeButton.setString("Change Generation Type");
			generationTypeButton.setTextScale(0.75f, 0.75f);
			generationTypeButton.setScaleModifiers(1.0f);
			generationTypeButton.setOutlineThickness(3.0f);
			generationTypeButton.setOutlineColor(uiOutlineColor0); 
			menu.add(&generationTypeButton);

			//colorTypeButton
			colorTypeButton = generationTypeButton; 
			colorTypeButton.move(0.0f, 140.0f);
			colorTypeButton.setString("Change Color Type");
			menu.add(&colorTypeButton);

			//colorSliders
			for (int colorSliderIndex = 0; colorSliderIndex < 3; 
				++colorSliderIndex) {
				gs::Slider& currentSlider = colorSliders[colorSliderIndex]; 

				currentSlider.setSize(300.0f, 10.0f);
				currentSlider.setPosition(
					1570.0f, 420.0f + (colorSliderIndex * 40.0f)
				);

				switch (colorSliderIndex) {
				case 0:
					currentSlider.setOnColor(gs::Color::Red); 
					break; 
				case 1:
					currentSlider.setOnColor(gs::Color::Green);
					break; 
				case 2:
					currentSlider.setOnColor(gs::Color::Blue);
					break; 
				}
				
				currentSlider.setPercentage(100.0f);
				
				menu.add(&currentSlider); 
			}

			//lightStrengthSlider
			lightStregthSlider.setSize(300.0f, 20.0f);
			lightStregthSlider.setPosition(1570.0f, 590.0f);
			lightStregthSlider.button.setSize(50.0f, 22.0f); 
			lightStregthSlider.setOnColor(gs::Color::White); 
			lightStregthSlider.setPercentage(50.0f); 
			menu.add(&lightStregthSlider); 

			//gravityStrengthSlider
			gravityStrengthSlider = lightStregthSlider; 
			gravityStrengthSlider.move(0.0f, 100.0f); 
			gravityStrengthSlider.setOnColor(gs::Color(255, 255, 0));
			menu.add(&gravityStrengthSlider); 

			//terminalVelocitySlider
			terminalVelocitySlider = gravityStrengthSlider; 
			terminalVelocitySlider.move(0.0f, 100.0f);
			terminalVelocitySlider.setOnColor(gs::Color(255, 0, 0));
			menu.add(&terminalVelocitySlider); 

			//changeFpsButton
			changeFpsButton = generationTypeButton;
			changeFpsButton.setSize(180.0f, 60.0f);
			changeFpsButton.move(0.0f, 700.0f);
			changeFpsButton.setString("Change Fps");
			menu.add(&changeFpsButton);

			//exitButton
			exitButton = changeFpsButton; 
			exitButton.setPosition(1630.0f, 970.0f); 
			exitButton.setString("Exit");
			menu.add(&exitButton); 

			//menuBackground
			menuBackground.setSize(gs::Vec2f(menuWidth, window::windowSize.y));
			menuBackground.setPosition(window::windowSize.x - menuWidth + 3.0f, 0.0f);
			menuBackground.setFillColor(uiBgColor0); 
			menuBackground.setOutlineThickness(3.0f);
			menuBackground.setOutlineColor(uiOutlineColor0); 

			menu.update(); 
		}

		void updateMenu() {
			if (menuOpen) 
				menu.update();
			else
				openMenuButton.update(); 
				
			if (openMenuButton.isSelected && openMenuButton.isClickedOn)
				menuOpen = !menuOpen; 

			if (!menuOpen) {
				openMenuButton.setPosition(
					window::windowSize.x - openMenuButton.getSize().x,
					20.0f
				);
			}
			else {
				openMenuButton.setPosition(
					window::windowSize.x - openMenuButton.getSize().x -
					menuWidth,
					20.0f
				);

				if (generationTypeButton.isSelected &&
					generationTypeButton.isClickedOn) {
					if (generationType == GenerationType::Automatic)
						generationType = GenerationType::Mouse;
					else
						generationType = GenerationType::Automatic;
				}
				else if (colorTypeButton.isSelected && colorTypeButton.isClickedOn) {
					if (colorType == ColorType::Rainbow)
						colorType = ColorType::Custom;
					else
						colorType = ColorType::Rainbow;
				}
				else if (changeFpsButton.isSelected &&
					changeFpsButton.isClickedOn) {
					if (window::virtualFramerate == 30)
						window::virtualFramerate = 60;
					else
						window::virtualFramerate = 30;
				}
				else if (exitButton.isClickedOn && exitButton.isSelected)
					window::winmain->close(); 
			}

			gravity = gravityStrengthSlider.getPercentage(0.3f); 
			terminalVelocity = terminalVelocitySlider.getPercentage(80.0f); 
		}

		void renderText(
			const std::string& string, gs::Vec2f position, float scale,
			gs::Color fillColor, float outlineThickness, gs::Color outlineColor
		) {
			text.setString(string);
			text.setPosition(position); 
			text.setScale(scale, scale); 
			text.setFillColor(fillColor); 
			text.setOutlineThickness(outlineThickness);
			text.setOutlineColor(outlineColor);

			gs::draw(window::winmain, text); 
		}
		void renderParticle(const Particle& particle) {
			particleBox.setSize(gs::Vec2f(6.0f, 6.0f));
			particleBox.setOrigin(
				particleBox.getSize().x / 2.0f,
				particleBox.getSize().y / 2.0f
			);
			particleBox.setPosition(particle.position); 
			particleBox.setFillColor(particle.color); 
			
			window::winmain->draw(particleBox); 
		}
		void renderParticles() {
			for (int particleIndex = 0; particleIndex < mNumOfParticles;
				++particleIndex) {
				Particle& currentParticle = particles[particleIndex]; 

				renderParticle(currentParticle); 
			}
		}
		void renderMenu() {
			if (menuOpen) {
				window::winmain->draw(menuBackground);

				renderText("Settings", gs::Vec2f(1630.0f, 50.0f), 1.25f);
				renderText(
					generationType == GenerationType::Automatic ? "Automatic"
					: "  Mouse", gs::Vec2f(1645.0f, 230.0f), 1.0f,
					inactiveTextColor
				);
				renderText(
					colorType == ColorType::Rainbow ? " Rainbow"
					: " Custom", gs::Vec2f(1645.0f, 230.0f + 140.0f), 1.0f,
					inactiveTextColor
				);
				renderText(
					"Light Strength", gs::Vec2f(1595.0f, 530.0f), 1.0f,
					inactiveTextColor
				);
				renderText(
					"Gravity Strength", gs::Vec2f(1575.0f, 630.0f), 1.0f,
					inactiveTextColor
				);
				renderText(
					"Terminal Velocity", gs::Vec2f(1565.0f, 730.0f), 1.0f,
					inactiveTextColor
				);
				renderText(
					std::to_string(window::virtualFramerate),
					gs::Vec2f(1785.0f, 865.0f), 1.0f, inactiveTextColor
				);

				gs::draw(window::winmain, menu);
			}
			else
				gs::draw(window::winmain, openMenuButton);
		}
	}
}