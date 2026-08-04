#include "Engine/Engine.h"

#include <vector>

#include <SFML/Graphics.hpp>

#include "Math/Vector2.h"
#include "Physics/Particle.h"
#include "Rendering/Renderer.h"


void Engine::Start()
{
	// Maak een nieuw venster aan met een vaste resolutie
	sf::RenderWindow window(
		sf::VideoMode({ 1280, 720 }),
		"Atomaire Simulatie"
	);


	Renderer renderer;


	// Een testdeeltje
	std::vector<Particle> particles;
	particles.push_back(Particle(Vector2(640.0, 360.0), 1.0, 20.0));


	while (window.isOpen())
	{
		// Controleer op het sluiten van het venster
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}


		renderer.Update(particles);

		window.clear(sf::Color::Black);
		renderer.Draw(window);
		window.display();
	}
}