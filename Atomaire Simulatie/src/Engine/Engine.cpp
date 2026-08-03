#include "Engine.h"

#include <SFML/Graphics.hpp>


void Engine::Start()
{
	// Maak een nieuw venster aan met een vaste resolutie
	sf::RenderWindow window(
		sf::VideoMode({ 1280, 720 }),
		"Atomaire Simulatie"
	);


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


		// Toon een zwart scherm
		window.clear(sf::Color::Black);

		window.display();
	}
}