#include "Engine/Engine.h"

#include <vector>

#include <SFML/Graphics.hpp>

#include "Math/Vector2.h"
#include "Physics/Particle.h"
#include "Physics/Simulation.h"
#include "Rendering/Renderer.h"


void Engine::Start()
{
	// Maak een nieuw venster aan
	sf::RenderWindow window(
		sf::VideoMode({ 1280, 720 }),
		"Atomaire Simulatie"
	);


	Renderer renderer;

	Simulation simulation(1280.0, 720.0);


	// Een testdeeltje
	Particle testParticle(Vector2(640.0, 360.0), 1.0, 20.0);
	testParticle.SetVelocity(Vector2(450.0, 290.0));
	simulation.AddParticle(testParticle);

	sf::Clock clock;


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


		// Bereken hoeveel tijd er sinds de vorige frame is verstreken
		// en voer één stap uit van de simulaite
		Real deltaTime = clock.restart().asSeconds();
		simulation.Step(deltaTime);

		renderer.Update(simulation.GetParticles());

		window.clear(sf::Color::Black);
		renderer.Draw(window);
		window.display();
	}
}