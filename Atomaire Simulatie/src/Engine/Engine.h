#pragma once

#include <SFML/Graphics.hpp>

#include "Physics/Simulation.h"
#include "Rendering/Renderer.h"


class Engine
{
public:

	Engine();

	void Start();

private:

	void Run();

	sf::RenderWindow window;
	Renderer renderer;
	Simulation simulation;
	sf::Clock clock;

};