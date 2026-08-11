#include "Engine/Engine.h"

#include <vector>
#include <random>

#include "Math/Vector2.h"
#include "Physics/Particle.h"


Engine::Engine(): simulation(1280.0, 720.0)
{
}


void Engine::Start()
{
	// Maak een nieuw venster aan
	window.create(
		sf::VideoMode({ 1280, 720 }),
		"Atomaire Simulatie"
	);


	simulation = Simulation(1280.0, 720.0);


	// Testdeeltjes
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<Real> posX(0.0, 1280.0);
	std::uniform_real_distribution<Real> posY(0.0, 720.0);
	std::uniform_real_distribution<Real> vel(-100.0, 100.0);

	Particle nucleus(Vector2(640.0, 360.0), 1000.0, 20.0, 1.0);
	simulation.AddParticle(nucleus);

	const int electronCount = 12;

	for (int i = 0; i < electronCount; ++i)
	{
		Particle electron(Vector2(posX(rng), posY(rng)), 1.0, 5.0, -1.0);
		electron.SetVelocity(Vector2(vel(rng), vel(rng)));

		simulation.AddParticle(electron);
	}


	Run();
}


void Engine::Run()
{
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