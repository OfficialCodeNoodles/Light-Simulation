#pragma once

//Dependencies
#include <Glass/glass.hpp>

//Macros

#define mNumOfParticles 100
#define mGetStyle(fullscreen) fullscreen ? sf::Style::Fullscreen \
	: sf::Style::Default

//Globals

extern int ticks; 